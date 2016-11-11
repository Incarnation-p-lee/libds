static inline struct hashing_table *
hashing_table_create(uint32 size)
{
    struct hashing_table *hash;

    assert_exit(!complain_zero_size_p(size));

    hash = memory_cache_allocate(sizeof(*hash));
    hash->size = size;
    hashing_table_initial(hash);

    return hash;
}

static inline bool
hashing_table_structure_legal_p(struct hashing_table *hash)
{
    if (NULL_PTR_P(hash)) {
        return false;
    } else if (NULL_PTR_P(hash->space)) {
        return false;
    } else if (NULL_PTR_P(hash->func)) {
        return false;
    } else if (complain_zero_size_p(hash->size)) {
        return false;
    } else if (hash->load_factor > 100) {
        return false;
    } else {
        return true;
    }
}

static inline void
hashing_table_initial(struct hashing_table *hash)
{
    void **iter;

    assert_exit(!NULL_PTR_P(hash));

    hash->space = memory_cache_allocate(sizeof(*hash->space) * hash->size);

    iter = hash->space;
    while (iter < hash->space + hash->size) {
        *iter++ = NULL;
    }
}

static inline void
hashing_table_hash_function_set(struct hashing_table *hash, void *func)
{
    assert_exit(!NULL_PTR_P(func));
    assert_exit(!NULL_PTR_P(hash));

    hash->func = func;
}

static inline void **
hashing_table_space(struct hashing_table *hash)
{
    assert_exit(hashing_table_structure_legal_p(hash));

    return hash->space;
}

static inline void
hashing_table_destroy(struct hashing_table **hash)
{
    assert_exit(!NULL_PTR_P(hash));
    assert_exit(hashing_table_structure_legal_p(*hash));

    memory_cache_free((*hash)->space);
    memory_cache_free((*hash));
    *hash = NULL;
}

static inline uint32
hashing_table_load_factor_calculate(struct hashing_table *hash)
{
    uint32 retval;
    void **iter;

    assert_exit(hashing_table_structure_legal_p(hash));

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

