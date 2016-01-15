struct separate_chain_hash *
separate_chain_hash_create(uint32 size)
{
    struct hashing_table *table;
    struct separate_chain_hash *hash;

    hash = memory_cache_allocate(sizeof(*hash));
    if (complain_no_memory_p(hash)) {
        /*
         * Will not reach here.
         */
        return NULL;
    } else if (0 == size) {
        size = DEFAULT_CHAIN_HASH_SIZE;
    }

    table = hashing_table_create(size);
    hashing_table_load_factor_set(table, DEFAULT_LOAD_FACTOR);
    hashing_table_hash_function_set(table, hashing_function_polynomial);

    hash->table = table;

    return hash;
}

static inline struct doubly_linked_list **
separate_chain_hash_space(struct separate_chain_hash *hash)
{
    assert(NULL != hash);

    return (struct doubly_linked_list **)hashing_table_space(hash->table);
}

static inline void
separate_chain_hash_chain_destroy(struct separate_chain_hash *hash)
{
    struct doubly_linked_list **iter;

    assert(NULL != hash);

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
    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        separate_chain_hash_chain_destroy(*hash);
        hashing_table_destroy(&(*hash)->table);

        memory_cache_free(*hash);
        *hash = NULL;
    }
}

uint32
separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash)
{
    if (complain_null_pointer_p(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor_calculate(hash->table);
    }
}

static inline struct doubly_linked_list *
separate_chain_hash_chain_head(struct separate_chain_hash *hash, uint32 index)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    assert(index < table->size);

    return table->space[index];
}

static inline void
separate_chain_hash_chain_head_set(struct separate_chain_hash *hash,
    uint32 index, struct doubly_linked_list *val)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    assert(index < table->size);

    table->space[index] = val;
}

static inline uint32
separate_chain_hash_index_calculate(struct separate_chain_hash *hash, void *key)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    return table->separate_chain(key, table->size);
}

void
separate_chain_hash_insert(struct separate_chain_hash **hash, void *key)
{
    uint32 factor;
    uint32 index;
    struct doubly_linked_list *head;

    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        factor = separate_chain_hash_load_factor_calculate(*hash);
        if (factor >= separate_chain_hash_load_factor(*hash)) {
            pr_log_info("Reach the load factor limit, will rehashing.\n");
            *hash = separate_chain_hash_rehashing(hash);
        }

        index = separate_chain_hash_index_calculate(*hash, key);
        head = separate_chain_hash_chain_head(*hash, index);
        if (!head) {
            /*
             * Empty linked list
             */
            head = doubly_linked_list_node_create(key, 0x0u);
            separate_chain_hash_chain_head_set(*hash, index, head);
        } else {
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

    if (complain_null_pointer_p(hash)) {
        return NULL;
    } else {
        retval = NULL;
        index = separate_chain_hash_index_calculate(hash, key);
        head = separate_chain_hash_chain_head(hash, index);
        if (!head) {
            retval = NULL;
        } else {
            iter = head;
            do {
                if (key == doubly_linked_list_val(iter)) {
                    retval = key;
                    doubly_linked_list_remove_and_destroy(&iter);
                    break;
                }
                iter = doubly_linked_list_next(iter);
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

    if (!complain_null_pointer_p(hash)) {
        index = separate_chain_hash_index_calculate(hash, key);
        head = separate_chain_hash_chain_head(hash, index);
        if (!head) {
            retval = NULL;
        } else {
            iter = head;
            do {
                if (key == doubly_linked_list_val(iter)) {
                    retval = key;
                    break;
                }
                iter = doubly_linked_list_next(iter);
            } while (iter != head);
        }

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }
    }

    return retval;
}

static inline void
separate_chain_hash_chain_rehashing(struct doubly_linked_list *link,
    struct separate_chain_hash *hash)
{
    void *tmp;
    struct doubly_linked_list *iter;

    assert(NULL != link);
    assert(NULL != hash);

    iter = link;
    do {
        tmp = doubly_linked_list_val(iter);
        separate_chain_hash_insert(&hash, tmp);
        iter = doubly_linked_list_next(iter);
    } while (iter != link);

    return;
}

static inline void
separate_chain_hash_space_rehashing(struct separate_chain_hash *to,
    struct separate_chain_hash *from)
{
    struct doubly_linked_list **iter;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != separate_chain_hash_space(from));
    assert(NULL != separate_chain_hash_space(to));

    iter = separate_chain_hash_space(from);
    while (iter < separate_chain_hash_space(from) +
        separate_chain_hash_size(from)) {
        if (*iter) {
            separate_chain_hash_chain_rehashing(*iter, to);
        }
        iter++;
    }
}

struct separate_chain_hash *
separate_chain_hash_rehashing(struct separate_chain_hash **hash)
{
    struct separate_chain_hash *new;
    uint32 resize;

    new = NULL;

    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        resize = prime_numeral_next(separate_chain_hash_size(*hash) + 1);
        new = separate_chain_hash_create(resize);

        separate_chain_hash_space_rehashing(new, *hash);
        separate_chain_hash_destroy(hash);
    }

    return new;
}

