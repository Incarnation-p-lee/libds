uint32
separate_chain_hash_size(s_separate_chain_hash_t *hash)
{
    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return HASH_SIZE_INVALID;
    } else {
        return hash->table->load.size;
    }
}

uint32
separate_chain_hash_load_factor_peak(s_separate_chain_hash_t *hash)
{
    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return HASH_LD_FTR_INVALID;
    } else {
        return hash->table->load.peak;
    }
}

static inline s_separate_chain_hash_t *
separate_chain_hash_create_i(uint32 size)
{
    s_separate_chain_hash_t *hash;

    hash = memory_cache_allocate(sizeof(*hash));

    if (complain_zero_size_p(size)) {
        size = SPT_CHN_HASH_SIZE_DFT;
        pr_log_warn("Hash table size not specified, use default size.\n");
    }

    hash->table = hashing_table_create(size);
    hash->table->func = &hashing_function_polynomial;
    hash->table->load.peak = SPT_CHN_HASH_LOAD_FTR;

    return hash;
}


s_separate_chain_hash_t *
separate_chain_hash_create(uint32 size)
{
    if (size == 0) {
        return PTR_INVALID;
    } else {
        return separate_chain_hash_create_i(size);
    }
}

static inline bool
separate_chain_hash_structure_illegal_p(s_separate_chain_hash_t *hash)
{
    return !separate_chain_hash_structure_legal_p(hash);
}

static inline bool
separate_chain_hash_structure_legal_p(s_separate_chain_hash_t *hash)
{
    if (NULL_PTR_P(hash)) {
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
    if (NULL_PTR_P(chain)) {
        return false;
    } else if (doubly_linked_list_structure_illegal_p(&chain->list)) {
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
    assert_exit(NON_NULL_PTR_P(node));

    return CONTAINER_OF(node, s_separate_chain_t, list);
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

    while (chain_array < hash->table->space + hash->table->load.size) {
        chain = *chain_array;

        if (chain) {
            separate_chain_destroy(chain);
        }

        chain_array++;
    }
}

static inline void
separate_chain_hash_destroy_i(s_separate_chain_hash_t *hash)
{
    assert_exit(separate_chain_hash_structure_legal_p(hash));

    separate_chain_hash_chain_destroy(hash);
    hashing_table_destroy(&hash->table);

    memory_cache_free(hash);
}


void
separate_chain_hash_destroy(s_separate_chain_hash_t **hash)
{
    if (NULL_PTR_P(hash)) {
        return;
    } else if (SEPARATE_CHAIN_HASH_ILLEGAL_P(*hash)) {
        return;
    } else {
        separate_chain_hash_destroy_i(*hash);
        *hash = NULL;
    }
}

uint32
separate_chain_hash_load_factor(s_separate_chain_hash_t *hash)
{
    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor(hash->table);
    }
}

static inline uint32
separate_chain_hash_index_calculate(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;

    assert_exit(separate_chain_hash_structure_legal_p(hash));

    index = hash->table->separate_chain(key, hash->table->load.size);

    assert_exit(index < hash->table->load.size);
    return index;
}

static inline void *
separate_chain_hash_insert_i(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;
    uint32 factor;
    s_separate_chain_t *head;
    s_separate_chain_t *chain_tmp;

    assert_exit(!NULL_PTR_P(key));
    assert_exit(separate_chain_hash_structure_legal_p(hash));

    factor = hashing_table_load_factor(hash->table);

    if (factor >= hash->table->load.peak) {
        pr_log_info("Reach the load factor limit, will rehashing.\n");
        separate_chain_hash_rehashing_i(hash);
    }

    chain_tmp = separate_chain_create(key);
    index = separate_chain_hash_index_calculate(hash, key);
    head = hash->table->space[index];

    if (!head) {
        hash->table->load.amount++;
        hash->table->space[index] = chain_tmp;
    } else {
        doubly_linked_list_insert_after(&head->list, &chain_tmp->list);
    }

    return key;
}

void *
separate_chain_hash_insert(s_separate_chain_hash_t *hash, void *key)
{
    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
        return PTR_INVALID;
    } else {
        return separate_chain_hash_insert_i(hash, key);
    }
}

static inline void *
separate_chain_hash_remove_i(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;
    s_doubly_linked_list_t *removed, *list;
    s_separate_chain_t *head, *chain, *next;

    assert_exit(NON_NULL_PTR_P(key));
    assert_exit(separate_chain_hash_structure_legal_p(hash));

    index = separate_chain_hash_index_calculate(hash, key);
    head = hash->table->space[index];

    if (head) {
        chain = head;

        do {
            next = separate_chain_next(chain);

            if (key == chain->val) {
                list = &chain->list;
                removed = doubly_linked_list_remove(&list);
                memory_cache_free(separate_chain_ptr_to_chain(removed));

                if (list) {
                    hash->table->space[index] = separate_chain_ptr_to_chain(list);
                } else {
                    hash->table->space[index] = NULL;
                    hash->table->load.amount--;
                }

                return key;
            }

            chain = next;
        } while (chain != head);
    }

    pr_log_warn("Failed to find key in hash table.\n");
    return NULL;
}

void *
separate_chain_hash_remove(s_separate_chain_hash_t *hash, void *key)
{
    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
        return PTR_INVALID;
    } else {
        return separate_chain_hash_remove_i(hash, key);
    }
}

void *
separate_chain_hash_find(s_separate_chain_hash_t *hash, void *key)
{
    uint32 index;
    s_separate_chain_t *head;
    s_separate_chain_t *chain;

    if (SEPARATE_CHAIN_HASH_ILLEGAL_P(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
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
separate_chain_hash_rehashing_i(s_separate_chain_hash_t *hash)
{
    void **chain;
    uint32 new_size;
    s_separate_chain_t *head, *list;
    s_separate_chain_hash_t *new_hash;

    assert_exit(separate_chain_hash_structure_legal_p(hash));

    new_size = prime_numeral_next(hash->table->load.size + 1);
    new_hash = separate_chain_hash_create_i(new_size);

    chain = hash->table->space;

    while (chain < hash->table->space + hash->table->load.size) {
        if (*chain) {
            head = list = *chain;

            do {
                separate_chain_hash_insert_i(new_hash, list->val);
                list = separate_chain_next(list);
            } while (head != list);
        }

        chain++;
    }

    /* swap space of hash and new */
    chain = hash->table->space;
    hash->table->space = new_hash->table->space;
    new_hash->table->space = chain;

    new_hash->table->load.size = hash->table->load.size;
    hash->table->load.size = new_size;

    separate_chain_hash_destroy_i(new_hash);
}

void
separate_chain_hash_rehashing(s_separate_chain_hash_t *hash)
{
    if (SEPARATE_CHAIN_HASH_LEGAL_P(hash)) {
        separate_chain_hash_rehashing_i(hash);
    }
}

