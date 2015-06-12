struct open_addressing_hash *
open_addressing_hash_create(uint32 size)
{
    struct open_addressing_hash *hash;

    hash = malloc_ds(sizeof(*hash));
    if (!hash) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        if (0 == size) {
            size = DEFAULT_CHAIN_HASH_SIZE;
            pr_log_warn("Hash table size not specified, use default size.\n");
        }

        hash->size = size;
        hash->load_factor = OPEN_ADDRESSING_HASH_LOAD_FACTOR;
        hash->func = hashing_function_open_addressing;
        open_addressing_hash_chain_initial(hash);
    }

    return hash;
}

static inline void
open_addressing_hash_chain_initial(struct open_addressing_hash *hash)
{
    struct doubly_linked_list **iter;

    assert(NULL != hash);

    hash->space = malloc_ds(sizeof(**hash->space) * hash->size);
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
