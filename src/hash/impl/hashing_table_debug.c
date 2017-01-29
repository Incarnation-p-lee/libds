static inline uint32
open_addressing_hash_limit(s_open_addressing_hash_t *hash)
{
    uint32 limit;

    assert_exit(open_addressing_hash_structure_legal_p(hash));

    limit = hash->table->load.size * hash->table->load.peak;
    limit = limit / 100u;

    return limit;
}

static inline uint32
hashing_table_load_factor_calculate(s_hashing_table_t *table)
{
    void **iter;
    uint32 load_factor;

    assert_exit(hashing_table_structure_legal_p(table));

    load_factor = 0u;
    iter = table->space;

    while (iter < table->space + table->load.size) {
        if (NULL != *iter) {
            load_factor++;
        }

        iter++;
    }

    return (load_factor * 100 / table->load.size);
}

