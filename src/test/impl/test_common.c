static inline void
test_binary_heap_data_randomization(struct heap_data **hd_array,
    uint32 last)
{
    uint32 idx;
    uint32 rand_idx;
    struct heap_data *bk;

    assert(NULL != hd_array);
    assert(NULL == hd_array[0]);

    idx = INDEX_ROOT;

    while (idx <= last) {
        rand_idx = rand() % idx;
        rand_idx = INDEX_INVALID == rand_idx ? INDEX_ROOT : rand_idx;

        bk = hd_array[rand_idx];
        hd_array[rand_idx] = hd_array[idx];
        hd_array[idx++] = bk;
    }
}

