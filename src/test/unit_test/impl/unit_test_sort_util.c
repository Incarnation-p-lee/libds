static inline struct utest_sort_data *
utest_sort_data_array(uint32 size)
{
    uint32 i;
    struct utest_sort_data *retval;

    assert(!complain_zero_size_p(size));

    retval = memory_cache_allocate(sizeof(*retval) * size);

    i = 0;
    while (i < size) {
        retval[i].val = random_uint32_with_limit(0x7FFFFF);
        i++;
    }

    return retval;
}

static inline struct utest_sort_data **
utest_sort_data_ptr_array(uint32 size)
{
    uint32 i;
    struct utest_sort_data **retval;

    assert(!complain_zero_size_p(size));

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
utest_sort_data_ptr_array_destroy(struct utest_sort_data **data, uint32 size)
{
    uint32 i;

    assert(!complain_null_pointer_p(data));
    assert(!complain_zero_size_p(size));

    i = 0;
    while (i < size) {
        memory_cache_free(data[i]);
        i++;
    }

    memory_cache_free(data);
}

static inline sint32
utest_sort_compare_u32(const void *a, const void *b)
{
    uint32 *ua;
    uint32 *ub;

    assert(!complain_null_pointer_p((void *)a));
    assert(!complain_null_pointer_p((void *)b));

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
utest_sort_compare_struct(const void *a, const void *b)
{
    struct utest_sort_data *pa;
    struct utest_sort_data *pb;

    assert(!complain_null_pointer_p((void *)a));
    assert(!complain_null_pointer_p((void *)b));

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
utest_sort_compare_ptr(const void *a, const void *b)
{
    struct utest_sort_data *sa;
    struct utest_sort_data *sb;

    assert(!complain_null_pointer_p((void *)a));
    assert(!complain_null_pointer_p((void *)b));

    sa = *(struct utest_sort_data **)a;
    sb = *(struct utest_sort_data **)b;

    if (sa->val > sb->val) {
        return 1;
    } else if (sa->val < sb->val) {
        return -1;
    } else {
        return 0;
    }
}

