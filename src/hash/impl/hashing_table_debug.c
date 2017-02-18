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

static inline bool
open_addressing_hash_structure_legal_p(s_open_addressing_hash_t *hash)
{
    if (NULL_PTR_P(hash)) {
        return false;
    } else {
        return hashing_table_structure_legal_p(hash->table);
    }
}

static inline bool
open_addressing_hash_structure_illegal_p(s_open_addressing_hash_t *hash)
{
    if (NULL_PTR_P(hash)) {
        return false;
    } else {
        return !hashing_table_structure_legal_p(hash->table);
    }
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

