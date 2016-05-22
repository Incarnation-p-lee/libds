static inline uint32
open_addressing_hash_limit(struct open_addressing_hash *hash)
{
    uint32 limit;

    dp_assert(NULL != hash);

    limit = open_addressing_hash_size(hash) * open_addressing_hash_load_factor(hash);
    limit = limit / 100u;

    return limit;
}

