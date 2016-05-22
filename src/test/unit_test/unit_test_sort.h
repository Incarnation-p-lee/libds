#ifndef HAVE_DEFINED_UNIT_TEST_SORT_H
#define HAVE_DEFINED_UNIT_TEST_SORT_H

#define UT_SORT(name)                                                       \
static void                                                                 \
utest_##name##_sort(void)                                                   \
{                                                                           \
    bool pass;                                                              \
    uint32 size;                                                            \
    uint32 csize;                                                           \
    void *data;                                                             \
    void *compare;                                                          \
                                                                            \
    pass = true;                                                            \
    size = 0x1ed8;                                                          \
    data = test_uint32_data_array(size);                                    \
    compare = &test_sort_compare_u32;                                       \
                                                                            \
    SORT(NULL, size, size, compare);                                        \
    SORT(data, size, size, NULL);                                           \
    SORT(data, 0, size, compare);                                           \
    SORT(data, size, 0, compare);                                           \
                                                                            \
    csize = sizeof(uint32);                                                 \
    SORT(data, size, csize, compare);                                       \
    RESULT_CHECK_bool(true, sort_data_sorted_p(data, size, csize, compare), \
        &pass);                                                             \
    memory_cache_dp_free(data);                                                \
                                                                            \
    data = test_sort_data_array(size);                                      \
    csize = sizeof(struct test_sort_data);                                  \
    compare = &test_sort_compare_struct;                                    \
    SORT(data, size, csize, compare);                                       \
    RESULT_CHECK_bool(true, sort_data_sorted_p(data, size, csize, compare), \
        &pass);                                                             \
    memory_cache_dp_free(data);                                                \
                                                                            \
    data = test_sort_data_ptr_array(size);                                  \
    csize = sizeof(struct test_sort_data *);                                \
    compare = &test_sort_compare_ptr;                                       \
    SORT(data, size, csize, compare);                                       \
    RESULT_CHECK_bool(true, sort_data_sorted_p(data, size, csize, compare), \
        &pass);                                                             \
    test_sort_data_ptr_array_destroy(data, size);                           \
                                                                            \
    UNIT_TEST_RESULT(name##_sort, pass);                                    \
}

#endif

