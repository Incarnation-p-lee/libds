static inline struct hashing_table *
hashing_table_create(uint32 size)
{
    struct hashing_table *hash;

    hash = malloc_ds(sizeof(*hash));
    if (!hash) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        assert(0 != size);

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
    register uint32 retval;
    register void **iter;

    assert(NULL != hash);
    assert(NULL != hash->space);

    retval = 0u;
    iter = hash->space;

    while (iter < hash->space + hash->size) {
        if (NULL != *iter) {
            retval++;
        }
        iter++;
    }

    return (retval * 100 / hash->size);
}

