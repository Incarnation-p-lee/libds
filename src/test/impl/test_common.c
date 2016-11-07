static inline void
test_binary_heap_data_randomization(struct heap_data **hd_array,
    uint32 last)
{
    uint32 idx;
    uint32 rand_idx;
    struct heap_data *bk;

    assert_exit(NULL != hd_array);
    assert_exit(NULL == hd_array[0]);

    idx = HEAP_IDX_ROOT;

    while (idx <= last) {
        rand_idx = dp_rand() % idx;

        if (HEAP_IDX_INVALID == rand_idx) {
            rand_idx = HEAP_IDX_ROOT;
        }

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

    assert_exit(!complain_zero_size_p(size));

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

    assert_exit(!complain_zero_size_p(size));

    i = 0;
    retval = memory_cache_allocate(sizeof(*retval) * size);

    while (i < size) {
        retval[i++] = random_uint32_with_limit(0x7FFFFF);
    }

    return retval;
}

static inline sint64
test_sint64_data_sum(sint64 *data, int m, int n, int size)
{
    uint32 i;
    sint64 retval;

    assert_exit(m <= n && n < size);
    assert_exit(!complain_zero_size_p(size));
    assert_exit(!NULL_PTR_P(data));

    i = m;
    retval = 0;

    while (i <= n) {
        retval += data[i++];
    }

    return retval;
}

static inline struct test_sort_data *
test_sort_data_array(uint32 size)
{
    uint32 i;
    struct test_sort_data *retval;

    assert_exit(!complain_zero_size_p(size));

    retval = memory_cache_allocate(sizeof(*retval) * size);

    i = 0;
    while (i < size) {
        retval[i].val = random_uint32_with_limit(0x7FFFFF);
        i++;
    }

    return retval;
}

static inline struct test_sort_data **
test_sort_data_ptr_array(uint32 size)
{
    uint32 i;
    struct test_sort_data **retval;

    assert_exit(!complain_zero_size_p(size));

    retval = memory_cache_allocate(sizeof(*retval) * size);

    i = 0;
    while (i < size) {
        retval[i] = memory_cache_allocate(sizeof(retval[i]));
        retval[i]->val = random_uint32_with_limit(0x7FFFFF);
        i++;
    }

    return retval;
}

static inline void
test_sort_data_ptr_array_destroy(struct test_sort_data **data, uint32 size)
{
    uint32 i;

    assert_exit(!NULL_PTR_P(data));
    assert_exit(!complain_zero_size_p(size));

    i = 0;
    while (i < size) {
        memory_cache_free(data[i]);
        i++;
    }

    memory_cache_free(data);
}

static inline sint32
test_sort_compare_u32(const void *a, const void *b)
{
    uint32 *ua;
    uint32 *ub;

    assert_exit(!NULL_PTR_P((void *)a));
    assert_exit(!NULL_PTR_P((void *)b));

    ua = (void *)a;
    ub = (void *)b;

    if (*ua > *ub) {
        return 1;
    } else if (*ua < *ub) {
        return -1;
    } else {
        return 0;
    }
}

static inline sint32
test_sort_compare_struct(const void *a, const void *b)
{
    struct test_sort_data *pa;
    struct test_sort_data *pb;

    assert_exit(!NULL_PTR_P((void *)a));
    assert_exit(!NULL_PTR_P((void *)b));

    pa = (void *)a;
    pb = (void *)b;

    if (pa->val > pb->val) {
        return 1;
    } else if (pa->val < pb->val) {
        return -1;
    } else {
        return 0;
    }
}

static inline sint32
test_sort_compare_ptr(const void *a, const void *b)
{
    struct test_sort_data *sa;
    struct test_sort_data *sb;

    assert_exit(!NULL_PTR_P((void *)a));
    assert_exit(!NULL_PTR_P((void *)b));

    sa = *(struct test_sort_data **)a;
    sb = *(struct test_sort_data **)b;

    if (sa->val > sb->val) {
        return 1;
    } else if (sa->val < sb->val) {
        return -1;
    } else {
        return 0;
    }
}

