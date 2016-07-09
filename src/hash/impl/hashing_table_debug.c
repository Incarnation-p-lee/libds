static inline uint32
open_addressing_hash_limit(struct open_addressing_hash *hash)
{
    uint32 limit;

    assert(!complain_null_pointer_p(hash));

    limit = hash->table->size * hash->table->load_factor;
    limit = limit / 100u;

    return limit;
}

