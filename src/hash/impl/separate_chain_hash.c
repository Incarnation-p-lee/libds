uint32
separate_chain_hash_size(s_separate_chain_hash_t *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return HASH_SIZE_INVALID;
    } else {
        return hash->table->size;
    }
}

uint32
separate_chain_hash_load_factor(s_separate_chain_hash_t *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return HASH_LD_FTR_INVALID;
    } else {
        return hash->table->load_factor;
    }
}

static inline s_separate_chain_hash_t *
separate_chain_hash_create_i(uint32 size)
{
    s_separate_chain_hash_t *hash;

    hash = memory_cache_allocate(sizeof(*hash));
    if (complain_zero_size_p(size)) {
        size = SPT_CHN_HASH_SIZE_DFT;
    }

    hash->table = hashing_table_create(size);
    hash->table->load_factor = SPT_CHN_HASH_LOAD_FTR;
    hash->table->func = &hashing_function_polynomial;

    return hash;
}


s_separate_chain_hash_t *
separate_chain_hash_create(uint32 size)
{
    return separate_chain_hash_create_i(size);
}

static inline bool
separate_chain_hash_structure_legal_p(s_separate_chain_hash_t *hash)
{
    if (complain_null_pointer_p(hash)) {
        return false;
    } else {
        return hashing_table_structure_legal_p(hash->table);
    }
}

static inline s_separate_chain_t *
separate_chain_create(void *val)
{
    s_separate_chain_t *chain;

    chain = memory_cache_allocate(sizeof(*chain));
    chain->val = val;

    doubly_linked_list_initial(&chain->list);
    return chain;
}

static inline bool
separate_chain_structure_legal_p(s_separate_chain_t *chain)
{
    if (complain_null_pointer_p(chain)) {
        return false;
    } else if (!doubly_linked_list_structure_legal_p(&chain->list)) {
        return false;
    } else {
        return true;
    }
}

static inline s_separate_chain_t *
separate_chain_next(s_separate_chain_t *chain)
{
    ptr_t offset;

    if (!chain) {
        return NULL;
    } else {
        offset = (ptr_t)&chain->list - (ptr_t)chain;
        return (void *)((ptr_t)chain->list.next - offset);
    }
}

static inline s_separate_chain_t *
separate_chain_ptr_to_chain(s_doubly_linked_list_t *node)
{
    if (!node) {
        return NULL;
    } else {
        return CONTAINER_OF(node, s_separate_chain_t, list);
    }
}

static inline void
separate_chain_destroy(s_separate_chain_t *chain)
{
    s_separate_chain_t *tmp;
    s_separate_chain_t *next;

    assert_exit(separate_chain_structure_legal_p(chain));

    tmp = chain;
    do {
        next = separate_chain_next(tmp);
        memory_cache_free(tmp);
        tmp = next;
    } while (tmp != chain);
}

static inline void
separate_chain_hash_chain_destroy(s_separate_chain_hash_t *hash)
{
    void *chain;
    void **chain_array;

    assert_exit(separate_chain_hash_structure_legal_p(hash));

    chain_array = hash->table->space;
    while (chain_array < hash->table->space + hash->table->size) {
        chain = *chain_array;
        if (chain) {
            separate_chain_destroy(chain);
        }
        chain_array++;
    }
}

void
separate_chain_hash_destroy(s_separate_chain_hash_t **hash)
{
    if (complain_null_pointer_p(hash)) {
        return;
    } else if (!separate_chain_hash_structure_legal_p(*hash)) {
        return;
    } else {
        separate_chain_hash_chain_destroy(*hash);
        hashing_table_destroy(&(*hash)->table);
        memory_cache_free(*hash);

        *hash = NULL;
    }
}

uint32
separate_chain_hash_load_factor_calculate(s_separate_chain_hash_t *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor_calculate(hash->table);
    }
}

static inline uint32
separate_chain_hash_index_calculate(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;

    assert_exit(separate_chain_hash_structure_legal_p(hash));

    index = hash->table->separate_chain(key, hash->table->size);

    assert_exit(index < hash->table->size);
    return index;
}

static inline void *
separate_chain_hash_insert_i(s_separate_chain_hash_t **hash, void *key)
{
    uint32 index;
    uint32 factor;
    s_separate_chain_t *tmp;
    s_separate_chain_t *head;

    assert_exit(!complain_null_pointer_p(key));
    assert_exit(!complain_null_pointer_p(hash));
    assert_exit(separate_chain_hash_structure_legal_p(*hash));

    factor = separate_chain_hash_load_factor_calculate(*hash);
    if (factor >= (*hash)->table->load_factor) {
        pr_log_info("Reach the load factor limit, will rehashing.\n");
        *hash = separate_chain_hash_rehashing(hash);
    }

    tmp = separate_chain_create(key);
    index = separate_chain_hash_index_calculate(*hash, key);
    head = (*hash)->table->space[index];

    if (!head) {
        (*hash)->table->space[index] = tmp;
    } else {
        doubly_linked_list_insert_after(&head->list, &tmp->list);
    }

    return key;
}

void *
separate_chain_hash_insert(s_separate_chain_hash_t **hash, void *key)
{
    if (complain_null_pointer_p(hash)) {
        return PTR_INVALID;
    } else if (!separate_chain_hash_structure_legal_p(*hash)) {
        return PTR_INVALID;
    } else if (complain_null_pointer_p(*hash)) {
        return PTR_INVALID;
    } else if (complain_null_pointer_p(key)) {
        return PTR_INVALID;
    } else {
        return separate_chain_hash_insert_i(hash, key);
    }
}

void *
separate_chain_hash_remove(s_separate_chain_hash_t *hash, void *key)
{
    void *retval;
    uint32 index;
    s_doubly_linked_list_t *removed, *list;
    s_separate_chain_t *head, *chain, *next;

    if (!separate_chain_hash_structure_legal_p(hash)) {
        return PTR_INVALID;
    } else if (complain_null_pointer_p(key)) {
        return PTR_INVALID;
    } else {
        list = retval = NULL;
        index = separate_chain_hash_index_calculate(hash, key);
        head = hash->table->space[index];

        if (head) {
            chain = head;
            do {
                next = separate_chain_next(chain);
                if (key == chain->val) {
                    retval = key;
                    list = &chain->list;
                    removed = doubly_linked_list_remove(&list);
                    memory_cache_free(separate_chain_ptr_to_chain(removed));

                    chain = separate_chain_ptr_to_chain(list);
                    hash->table->space[index] = chain;
                    return retval;
                }
                chain = next;
            } while (chain != head);
        }

        pr_log_warn("Failed to find key in hash table.\n");
        return NULL;
    }
}

void *
separate_chain_hash_find(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;
    s_separate_chain_t *head;
    s_separate_chain_t *chain;

    if (!separate_chain_hash_structure_legal_p(hash)) {
        return PTR_INVALID;
    } else if (complain_null_pointer_p(key)) {
        return PTR_INVALID;
    } else {
        index = separate_chain_hash_index_calculate(hash, key);
        head = hash->table->space[index];

        if (head) {
            chain = head;
            do {
                if (key == chain->val) {
                    return key;
                }
                chain = separate_chain_next(chain);
            } while (chain != head);
        }

        pr_log_info("Not such a key in given hash.\n");
        return NULL;
    }
}

static inline void
separate_chain_hash_space_rehashing(s_separate_chain_hash_t *to,
    s_separate_chain_hash_t *from)
{
    void **chain;
    s_separate_chain_t *head, *list;;

    assert_exit(separate_chain_hash_structure_legal_p(to));
    assert_exit(separate_chain_hash_structure_legal_p(from));

    chain = from->table->space;

    while (chain < from->table->space + from->table->size) {
        if (*chain) {
            head = list = *chain;
            do {
                separate_chain_hash_insert_i(&to, list->val);
                list = separate_chain_next(list);
            } while (head != list);
        }
        chain++;
    }
}

s_separate_chain_hash_t *
separate_chain_hash_rehashing(s_separate_chain_hash_t **hash)
{
    uint32 resize;
    s_separate_chain_hash_t *new;

    if (complain_null_pointer_p(hash)) {
        return PTR_INVALID;
    } else if (!separate_chain_hash_structure_legal_p(*hash)) {
        return PTR_INVALID;
    } else {
        resize = prime_numeral_next((*hash)->table->size + 1);
        new = separate_chain_hash_create_i(resize);

        separate_chain_hash_space_rehashing(new, *hash);
        separate_chain_hash_destroy(hash);

        return new;
    }
}

