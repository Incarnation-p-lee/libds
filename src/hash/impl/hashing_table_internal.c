static inline s_hashing_table_t *
hashing_table_create(uint32 size)
{
    s_hashing_table_t *table;

    assert_exit(!complain_zero_size_p(size));

    table = memory_cache_allocate(sizeof(*table));

    table->load.size = size;
    table->load.amount = 0;

    hashing_table_initial(table);

    return table;
}

static inline bool
hashing_table_structure_legal_p(s_hashing_table_t *table)
{
    if (NULL_PTR_P(table)) {
        return false;
    } else if (NULL_PTR_P(table->space)) {
        return false;
    } else if (NULL_PTR_P(table->func)) {
        return false;
    } else if (complain_zero_size_p(table->load.size)) {
        return false;
    } else if (table->load.peak > 100) {
        return false;
    } else {
        return true;
    }
}

static inline void
hashing_table_initial(s_hashing_table_t *table)
{
    uint32 size;

    assert_exit(NON_NULL_PTR_P(table));

    size = sizeof(*table->space) * table->load.size;

    table->space = memory_cache_allocate(size);
    dp_memset(table->space, 0, size);
}

static inline void
hashing_table_hash_function_set(s_hashing_table_t *table, void *func)
{
    assert_exit(!NULL_PTR_P(func));
    assert_exit(!NULL_PTR_P(table));

    table->func = func;
}

static inline void **
hashing_table_space(s_hashing_table_t *table)
{
    assert_exit(hashing_table_structure_legal_p(table));

    return table->space;
}

static inline void
hashing_table_destroy(s_hashing_table_t **table)
{
    assert_exit(!NULL_PTR_P(table));
    assert_exit(hashing_table_structure_legal_p(*table));

    memory_cache_free((*table)->space);
    memory_cache_free((*table));
    *table = NULL;
}

static inline uint32
hashing_table_load_factor(s_hashing_table_t *table)
{
    uint32 load_factor;

    assert_exit(hashing_table_structure_legal_p(table));

    load_factor = HASHING_TABLE_LOAD_FACTOR(table);
    assert_exit(load_factor == hashing_table_load_factor_calculate(table));

    return load_factor;
}

