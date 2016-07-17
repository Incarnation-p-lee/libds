static inline uint32
open_addressing_hash_limit(struct open_addressing_hash *hash)
{
    uint32 limit;

    assert_exit(open_addressing_hash_structure_legal_p(hash));

    limit = hash->table->size * hash->table->load_factor;
    limit = limit / 100u;

    return limit;
}

