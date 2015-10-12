static inline void
test_binary_heap_collision_chain_randomization(struct collision_chain **chain_array,
    uint32 last)
{
    uint32 idx;
    uint32 rand_idx;
    struct collision_chain *chain_bk;

    assert(NULL != chain_array);
    assert(NULL == chain_array[0]);

    idx = HEAP_ROOT_INDEX;

    while (idx <= last) {
        rand_idx = rand() % idx;
        rand_idx = INDEX_INVALID == rand_idx ? HEAP_ROOT_INDEX : rand_idx;

        chain_bk = chain_array[rand_idx];
        chain_array[rand_idx] = chain_array[idx];
        chain_array[idx++] = chain_bk;
    }
}

