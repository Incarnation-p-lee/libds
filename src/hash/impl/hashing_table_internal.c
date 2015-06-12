static inline struct hashing_table *
hashing_table_create(uint32 size)
{
    struct hashing_table *hash;

    hash = malloc_ds(sizeof(*hash));
    if (!hash) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        if (0 == size) {
            size = DEFAULT_CHAIN_HASH_SIZE;
            pr_log_warn("Hash table size not specified, use default size.\n");
        }

        hash->size = size;
        hashing_table_initial(hash);
    }

    return hash;
}

static inline void
hashing_table_initial(struct hashing_table *hash)
{
    void **iter;

    assert(NULL != hash);

    hash->space = malloc_ds(sizeof(*hash->space) * hash->size);
    if (!hash->space) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        iter = hash->space;
        while (iter < hash->space + hash->size) {
            *iter++ = NULL;
        }
    }

    return;
}

static inline void
hashing_table_hash_function_set(struct hashing_table *hash, void *func)
{
    assert(NULL != hash);
    assert(NULL != func);

    hash->func = func;
}

static inline void **
hashing_table_space(struct hashing_table *hash)
{
    assert(NULL != hash);
    assert(NULL != hash->space);

    return hash->space;
}

static inline void
hashing_table_destroy(struct hashing_table **hash)
{
    assert(NULL != hash);
    assert(NULL != *hash);
    assert(NULL != (*hash)->space);

    free_ds((*hash)->space);
    free_ds(*hash);
    *hash = NULL;
}

static inline uint32
hashing_table_load_factor_calculate(struct hashing_table *hash)
{
    uint32 retval;
    void **iter;

    retval = 0u;
    if (!hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = hash->space;
        if (!iter) {
            pr_log_warn("Destroyed data structure.\n");
        } else {
            retval = 0u;
            while (iter < hash->space + hash->size) {
                if (NULL != *iter) {
                    retval++;
                }
                iter++;
            }
        }

        retval = (retval * 100 / hash->size);
    }

    return retval;
}

