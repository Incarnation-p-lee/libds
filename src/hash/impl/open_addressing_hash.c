struct open_addressing_hash *
open_addressing_hash_create(uint32 size)
{
    struct hashing_table *table;
    struct open_addressing_hash *hash;

    hash = memory_cache_allocate(sizeof(*hash));
    if (complain_no_memory_p(hash)) {
        /*
         * Will not reach here.
         */
        return NULL;
    } else if (0 == size) {
        size = DEFAULT_CHAIN_HASH_SIZE;
        pr_log_warn("Hash table size not specified, use default size.\n");
    }

    /*
     * open addressing requires prime table size.
     */
    table = hashing_table_create(prime_numeral_next(size));
    hashing_table_load_factor_set(table, OPEN_ADDRESSING_HASH_LOAD_FACTOR);
    hashing_table_hash_function_set(table, hashing_function_open_addressing);

    hash->table = table;

    return hash;
}

void
open_addressing_hash_destroy(struct open_addressing_hash **hash)
{
    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        hashing_table_destroy(&(*hash)->table);

        memory_cache_free(*hash);
        *hash = NULL;
    }

    return;
}

uint32
open_addressing_hash_load_factor_calculate(struct open_addressing_hash *hash)
{
    if (complain_null_pointer_p(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor_calculate(hash->table);
    }
}

static inline uint32
open_addressing_hash_index_calculate(struct open_addressing_hash *hash,
    void *key, uint32 iter)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    return table->open_addressing(key, table->size, iter);
}

static inline void *
open_addressing_hash_node(struct open_addressing_hash *hash, uint32 index)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    assert(index < table->size);

    return table->space[index];
}

static inline void
open_addressing_hash_node_set(struct open_addressing_hash *hash,
    uint32 index, void *val)
{
    struct hashing_table *table;

    assert(NULL != hash);
    assert(NULL != hash->table);

    table = hash->table;
    assert(index < table->size);

    table->space[index] = val;
}

void
open_addressing_hash_insert(struct open_addressing_hash **hash, void *key)
{
    uint32 factor;
    uint32 index;
    uint32 iter;

    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        factor = open_addressing_hash_load_factor_calculate(*hash);
        if (factor >= open_addressing_hash_load_factor(*hash)) {
            pr_log_info("Reach the load factor limit, will rehashing.\n");
            *hash = open_addressing_hash_rehashing(hash);
        }

        iter = 0;
        do {
            assert(iter < open_addressing_hash_limit(*hash));

            index = open_addressing_hash_index_calculate(*hash, key, iter++);
        } while (NULL != open_addressing_hash_node(*hash, index));
        open_addressing_hash_node_set(*hash, index, key);
    }
}

void *
open_addressing_hash_remove(struct open_addressing_hash *hash, void *key)
{
    void *retval;
    uint32 index;
    uint32 iter;

    retval = NULL;

    if (!complain_null_pointer_p(hash)) {
        iter = 0;
        do {
            assert(iter < open_addressing_hash_limit(hash));

            index = open_addressing_hash_index_calculate(hash, key, iter++);
            retval = open_addressing_hash_node(hash, index);
            if (key == retval) {
                retval = key;
                break;
            }
        } while (NULL != retval);

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        } else {
            open_addressing_hash_node_set(hash, index, NULL);
        }
    }

    return retval;
}

void *
open_addressing_hash_find(struct open_addressing_hash *hash, void *key)
{
    void *retval;
    uint32 index;
    uint32 iter;

    retval = NULL;

    if (!complain_null_pointer_p(hash)) {
        iter = 0;
        do {
            assert(iter < open_addressing_hash_limit(hash));

            index = open_addressing_hash_index_calculate(hash, key, iter++);
            retval = open_addressing_hash_node(hash, index);
            if (key == retval) {
                retval = key;
                break;
            }
        } while (NULL != retval);

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }
    }

    return retval;
}

static inline void **
open_addressing_hash_space(struct open_addressing_hash *hash)
{
    assert(NULL != hash);

    return hashing_table_space(hash->table);
}

static inline void
open_addressing_hash_space_rehashing(struct open_addressing_hash *to,
    struct open_addressing_hash *from)
{
    void **iter;

    assert(NULL != to);
    assert(NULL != from);
    assert(NULL != open_addressing_hash_space(to));
    assert(NULL != open_addressing_hash_space(from));

    iter = open_addressing_hash_space(from);
    while (iter < open_addressing_hash_space(from) +
        open_addressing_hash_size(from)) {
        if (*iter) {
            open_addressing_hash_insert(&to, *iter);
        }
        iter++;
    }

    return;
}

struct open_addressing_hash *
open_addressing_hash_rehashing(struct open_addressing_hash **hash)
{
    struct open_addressing_hash *new;
    uint32 resize;

    new = NULL;

    if (!complain_null_pointer_p(hash) && !complain_null_pointer_p(*hash)) {
        resize = prime_numeral_next(open_addressing_hash_size(*hash) + 1);
        new = open_addressing_hash_create(resize);
        open_addressing_hash_space_rehashing(new, *hash);
        open_addressing_hash_destroy(hash);
    }

    return new;
}

