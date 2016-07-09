uint32
separate_chain_hash_size(struct separate_chain_hash *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return HASH_SIZE_INVALID;
    } else {
        return hash->table->size;
    }
}

uint32
separate_chain_hash_load_factor(struct separate_chain_hash *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return HASH_LD_FTR_INVALID;
    } else {
        return hash->table->load_factor;
    }
}

struct separate_chain_hash *
separate_chain_hash_create(uint32 size)
{
    struct hashing_table *table;
    struct separate_chain_hash *hash;

    hash = memory_cache_allocate(sizeof(*hash));
    if (complain_zero_size_p(size)) {
        size = SPT_CHN_HASH_SIZE_DFT;
    }

    table = hashing_table_create(size);
    table->load_factor = SPT_CHN_HASH_LOAD_FTR;
    table->func = &hashing_function_polynomial;
    hash->table = table;

    return hash;
}

static inline bool
separate_chain_hash_structure_legal_p(struct separate_chain_hash *hash)
{
    if (complain_null_pointer_p(hash)) {
        return false;
    } else {
        return hashing_table_structure_legal_p(hash->table);
    }
}

static inline struct doubly_linked_list **
separate_chain_hash_space(struct separate_chain_hash *hash)
{
    dp_assert(separate_chain_hash_structure_legal_p(hash));

    return (struct doubly_linked_list **)hashing_table_space(hash->table);
}

static inline void
separate_chain_hash_chain_destroy(struct separate_chain_hash *hash)
{
    struct doubly_linked_list **iter;

    dp_assert(separate_chain_hash_structure_legal_p(hash));

    iter = separate_chain_hash_space(hash);
    while (iter < separate_chain_hash_space(hash) +
        separate_chain_hash_size(hash)) {
        if (*iter) {
           doubly_linked_list_destroy(iter);
        }
        iter++;
    }
}

void
separate_chain_hash_destroy(struct separate_chain_hash **hash)
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
separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash)
{
    if (!separate_chain_hash_structure_legal_p(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor_calculate(hash->table);
    }
}

static inline struct doubly_linked_list *
separate_chain_hash_chain_head(struct separate_chain_hash *hash, uint32 index)
{
    struct hashing_table *table;

    dp_assert(separate_chain_hash_structure_legal_p(hash));

    table = hash->table;
    return table->space[index];
}

static inline void
separate_chain_hash_chain_head_set(struct separate_chain_hash *hash,
    uint32 index, struct doubly_linked_list *val)
{
    struct hashing_table *table;

    dp_assert(separate_chain_hash_structure_legal_p(hash));
    dp_assert(index < hash->table->size);

    table = hash->table;
    table->space[index] = val;
}

static inline uint32
separate_chain_hash_index_calculate(struct separate_chain_hash *hash, void *key)
{
    struct hashing_table *table;

    dp_assert(separate_chain_hash_structure_legal_p(hash));

    table = hash->table;
    return table->separate_chain(key, table->size);
}

void
separate_chain_hash_insert(struct separate_chain_hash **hash, void *key)
{
    uint32 factor;
    uint32 index;
    struct doubly_linked_list *head;

    if (complain_null_pointer_p(hash)) {
        return;
    } else if (separate_chain_hash_structure_legal_p(*hash)) {
        factor = separate_chain_hash_load_factor_calculate(*hash);
        if (factor >= separate_chain_hash_load_factor(*hash)) {
            pr_log_info("Reach the load factor limit, will rehashing.\n");
            *hash = separate_chain_hash_rehashing(hash);
        }

        index = separate_chain_hash_index_calculate(*hash, key);
        head = separate_chain_hash_chain_head(*hash, index);

        if (!head) {
            head = doubly_linked_list_create();
            separate_chain_hash_chain_head_set(*hash, index, head);
        } else {
            // Fix-Me, bug here.
            doubly_linked_list_insert_after(head, key);
        }
    }
}

void *
separate_chain_hash_remove(struct separate_chain_hash *hash, void *key)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *iter;
    void *retval;
    uint32 index;

    if (!separate_chain_hash_structure_legal_p(hash)) {
        return NULL;
    } else {
        retval = NULL;
        index = separate_chain_hash_index_calculate(hash, key);
        head = separate_chain_hash_chain_head(hash, index);

        if (!head) {
            return NULL;
        } else {
            iter = head;
            do {
                if (key == iter->val) {
                    retval = key;
                    doubly_linked_list_remove(&iter);
                    break;
                }
                iter = iter->next;
            } while (iter != head);

            separate_chain_hash_chain_head_set(hash, index, iter);
        }

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }

        return retval;
    }
}

void *
separate_chain_hash_find(struct separate_chain_hash *hash, void *key)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *iter;
    void *retval;
    uint32 index;

    retval = NULL;

    if (!separate_chain_hash_structure_legal_p(hash)) {
        return NULL;
    } else {
        index = separate_chain_hash_index_calculate(hash, key);
        head = separate_chain_hash_chain_head(hash, index);

        if (!head) {
            return NULL;
        } else {
            iter = head;
            do {
                if (key == iter->val) {
                    retval = key;
                    break;
                }
                iter = iter->next;
            } while (iter != head);
        }

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }

        return retval;
    }
}

static inline void
separate_chain_hash_chain_rehashing(struct doubly_linked_list *link,
    struct separate_chain_hash *hash)
{
    void *tmp;
    struct doubly_linked_list *iter;

    dp_assert(!complain_null_pointer_p(link));
    dp_assert(separate_chain_hash_structure_legal_p(hash));

    iter = link;
    do {
        tmp = iter->val;
        separate_chain_hash_insert(&hash, tmp);
        iter = iter->next;
    } while (iter != link);
}

static inline void
separate_chain_hash_space_rehashing(struct separate_chain_hash *to,
    struct separate_chain_hash *from)
{
    uint32 size;
    struct doubly_linked_list **iter;

    dp_assert(!complain_null_pointer_p(to));
    dp_assert(!complain_null_pointer_p(from));
    dp_assert(!complain_null_pointer_p(separate_chain_hash_space(to)));
    dp_assert(!complain_null_pointer_p(separate_chain_hash_space(from)));

    iter = separate_chain_hash_space(from);
    size = separate_chain_hash_size(from);

    while (iter < separate_chain_hash_space(from) + size) {
        if (*iter) {
            separate_chain_hash_chain_rehashing(*iter, to);
        }
        iter++;
    }
}

struct separate_chain_hash *
separate_chain_hash_rehashing(struct separate_chain_hash **hash)
{
    uint32 resize;
    struct separate_chain_hash *new;

    if (complain_null_pointer_p(hash)) {
        return NULL;
    } else if (!separate_chain_hash_structure_legal_p(*hash)) {
        return NULL;
    } else {
        resize = prime_numeral_next(separate_chain_hash_size(*hash) + 1);
        new = separate_chain_hash_create(resize);

        separate_chain_hash_space_rehashing(new, *hash);
        separate_chain_hash_destroy(hash);

        return new;
    }
}

