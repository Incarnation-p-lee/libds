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

static inline sint64 *
test_sint64_data_array(uint32 size)
{
    uint32 i;
    sint64 *retval;

    assert(!complain_zero_size_p(size));

    i = 0;
    retval = memory_cache_allocate(sizeof(*retval) * size);

    while (i < size) {
        retval[i++] = random_sint64();
    }

    return retval;
}

static inline uint32 *
test_uint32_data_array(uint32 size)
{
    uint32 i;
    uint32 *retval;

    assert(!complain_zero_size_p(size));

    i = 0;
    retval = memory_cache_allocate(sizeof(*retval) * size);

    while (i < size) {
        retval[i++] = random_uint32_with_limit(0xF);
    }

    return retval;
}

static inline sint64
test_sint64_data_sum(sint64 *data, int m, int n, int size)
{
    uint32 i;
    sint64 retval;

    assert(m <= n && n < size);
    assert(!complain_zero_size_p(size));
    assert(!complain_null_pointer_p(data));

    i = m;
    retval = 0;

    while (i <= n) {
        retval += data[i++];
    }

    return retval;
}

