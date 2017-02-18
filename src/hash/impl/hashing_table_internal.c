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

