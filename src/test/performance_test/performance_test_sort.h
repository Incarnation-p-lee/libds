#ifndef HAVE_DEFINED_PERFORMANCE_TEST_SORT_H
#define HAVE_DEFINED_PERFORMANCE_TEST_SORT_H

#define PT_SORT(name)                                   \
static void                                             \
ptest_##name##_sort(uint32 count)                       \
{                                                       \
    uint32 size;                                        \
    void *data;                                         \
    void *compare;                                      \
                                                        \
    size = 0xe312;                                      \
    data = test_uint32_data_array(size);                \
    compare = &test_sort_compare_u32;                   \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    SORT(data, size, sizeof(uint32), compare);          \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    memory_cache_dp_free(data);                            \
    PERFORMANCE_TEST_RESULT(name##_sort);               \
}

#endif

