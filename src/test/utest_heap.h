#ifndef HAVE_DEFINED_UNIT_TEST_HEAP_H
#define HAVE_DEFINED_UNIT_TEST_HEAP_H

#define UT_HEAP_structure_legal_p(name)                               \
static inline bool                                                    \
utest_##name##_heap_structure_legal_p(struct name##_heap *heap)       \
{                                                                     \
    bool result;                                                      \
                                                                      \
    assert_exit(!NULL_PTR_P(heap));                           \
                                                                      \
    result = true;                                                    \
                                                                      \
    RESULT_CHECK_NOT_EQUAL_pointer(NULL, heap->alias, &result);       \
    RESULT_CHECK_NOT_EQUAL_pointer(NULL, heap->alias->base, &result); \
                                                                      \
    return result;                                                    \
}

#define UT_HEAP_create(name)                                      \
static inline void                                                \
utest_##name##_heap_create(void)                                  \
{                                                                 \
    bool pass;                                                    \
    uint32 capacity;                                              \
    struct HEAP *heap;                                            \
                                                                  \
    pass = true;                                                  \
    capacity = 0u;                                                \
                                                                  \
    heap = HEAP_create(capacity++);                               \
    HEAP_destroy(&heap);                                          \
                                                                  \
    heap = HEAP_create(capacity);                                 \
    RESULT_CHECK_bool(true, HEAP_structure_legal_p(heap), &pass); \
                                                                  \
    HEAP_destroy(&heap);                                          \
    UNIT_TEST_RESULT(name##_heap_create, pass);                   \
}

#define UT_HEAP_destroy(name)                    \
static inline void                               \
utest_##name##_heap_destroy(void)                \
{                                                \
    bool pass;                                   \
    struct HEAP *heap;                           \
                                                 \
    pass = true;                                 \
    heap = NULL;                                 \
                                                 \
    HEAP_destroy(&heap);                         \
    heap = HEAP_create(0u);                      \
                                                 \
    HEAP_destroy(&heap);                         \
    RESULT_CHECK_pointer(NULL, heap, &pass);     \
                                                 \
    UNIT_TEST_RESULT(name##_heap_destroy, pass); \
}

#define UT_HEAP_empty_p(name)                            \
static inline void                                       \
utest_##name##_heap_empty_p(void)                        \
{                                                        \
    bool pass;                                           \
    struct HEAP *heap;                                   \
                                                         \
    pass = true;                                         \
    heap = NULL;                                         \
                                                         \
    RESULT_CHECK_bool(false, HEAP_empty_p(heap), &pass); \
                                                         \
    heap = TEST_HEAP_sample(0x2234, 0x142);              \
    RESULT_CHECK_bool(false, HEAP_empty_p(heap), &pass); \
    HEAP_destroy(&heap);                                 \
                                                         \
    heap = HEAP_create(0u);                              \
    RESULT_CHECK_bool(true, HEAP_empty_p(heap), &pass);  \
                                                         \
    HEAP_destroy(&heap);                                 \
    UNIT_TEST_RESULT(name##_heap_empty_p, pass);         \
}

#define UT_HEAP_full_p(name)                            \
static inline void                                      \
utest_##name##_heap_full_p(void)                        \
{                                                       \
    bool pass;                                          \
    struct HEAP *heap;                                  \
                                                        \
    pass = true;                                        \
    heap = NULL;                                        \
                                                        \
    RESULT_CHECK_bool(true, HEAP_full_p(heap), &pass);  \
                                                        \
    heap = TEST_HEAP_sample(0x1, 0x1);                  \
    RESULT_CHECK_bool(true, HEAP_full_p(heap), &pass);  \
    HEAP_destroy(&heap);                                \
                                                        \
    heap = HEAP_create(0u);                             \
    RESULT_CHECK_bool(false, HEAP_full_p(heap), &pass); \
                                                        \
    HEAP_destroy(&heap);                                \
    UNIT_TEST_RESULT(name##_heap_full_p, pass);         \
}

#define UT_HEAP_cleanup(name)                           \
static inline void                                      \
utest_##name##_heap_cleanup(void)                       \
{                                                       \
    bool pass;                                          \
    struct HEAP *heap;                                  \
                                                        \
    pass = true;                                        \
    heap = NULL;                                        \
                                                        \
    HEAP_cleanup(heap);                                 \
                                                        \
    heap = TEST_HEAP_sample(0x3345, 0x104E);            \
    HEAP_cleanup(heap);                                 \
                                                        \
    RESULT_CHECK_bool(false, HEAP_full_p(heap), &pass); \
    RESULT_CHECK_bool(true, HEAP_empty_p(heap), &pass); \
                                                        \
    HEAP_destroy(&heap);                                \
    UNIT_TEST_RESULT(name##_heap_cleanup, pass);        \
}

#define UT_HEAP_get_min(name)                              \
static inline void                                         \
utest_##name##_heap_get_min(void)                          \
{                                                          \
    bool pass;                                             \
    void *val;                                             \
    struct HEAP *heap;                                     \
                                                           \
    pass = true;                                           \
    heap = NULL;                                           \
                                                           \
    RESULT_CHECK_pointer(NULL, HEAP_get_min(heap), &pass); \
                                                           \
    heap = TEST_HEAP_sample(0x1345, 0x104E);               \
    val = HEAP_val(heap, HEAP_IDX_ROOT);                   \
    RESULT_CHECK_pointer(val, HEAP_get_min(heap), &pass);  \
                                                           \
    HEAP_destroy(&heap);                                   \
    UNIT_TEST_RESULT(name##_heap_get_min, pass);           \
}

#define UT_HEAP_get_max(name)                              \
static inline void                                         \
utest_##name##_heap_get_max(void)                          \
{                                                          \
    bool pass;                                             \
    void *val;                                             \
    struct HEAP *heap;                                     \
                                                           \
    pass = true;                                           \
    heap = NULL;                                           \
                                                           \
    RESULT_CHECK_pointer(NULL, HEAP_get_max(heap), &pass); \
                                                           \
    heap = TEST_HEAP_sample(0x1345, 0x104E);               \
    val = HEAP_val(heap, HEAP_IDX_ROOT);                      \
    RESULT_CHECK_pointer(val, HEAP_get_max(heap), &pass);  \
                                                           \
    HEAP_destroy(&heap);                                   \
    UNIT_TEST_RESULT(name##_heap_get_max, pass);           \
}

#define UT_HEAP_insert(name)                                   \
static inline void                                             \
utest_##name##_heap_insert(void)                               \
{                                                              \
    bool pass;                                                 \
    uint32 count;                                              \
    uint32 size;                                               \
    struct HEAP *heap;                                         \
                                                               \
    pass = true;                                               \
    heap = NULL;                                               \
    count = 0x82;                                              \
                                                               \
    HEAP_insert(heap, &pass, 0u);                              \
                                                               \
    heap = TEST_HEAP_sample(0x345, 0x44E);                     \
                                                               \
    while (count--) {                                          \
        size = HEAP_size(heap);                                \
        HEAP_insert(heap, &pass, count);                       \
        RESULT_CHECK_uint32(size + 1, HEAP_size(heap), &pass); \
    }                                                          \
                                                               \
    HEAP_destroy(&heap);                                       \
    UNIT_TEST_RESULT(name##_heap_insert, pass);                \
}

#define UT_HEAP_remove(name)                                            \
static inline void                                                      \
utest_##name##_heap_remove(void)                                        \
{                                                                       \
    bool pass;                                                          \
    void *val;                                                          \
    uint32 index;                                                       \
    struct HEAP *heap;                                                  \
                                                                        \
    pass = true;                                                        \
    heap = NULL;                                                        \
    HEAP_remove(heap, 0);                                               \
                                                                        \
    index = 0x12345;                                                    \
    heap = TEST_HEAP_sample(0x942, 0x73a);                              \
    RESULT_CHECK_pointer(PTR_INVALID, HEAP_remove(heap, index), &pass); \
                                                                        \
    index = 0x2;                                                        \
    val = HEAP_val(heap, index);                                        \
    RESULT_CHECK_pointer(val, HEAP_remove(heap, index), &pass);         \
                                                                        \
    index = 0x323;                                                      \
    val = HEAP_val(heap, index);                                        \
    RESULT_CHECK_pointer(val, HEAP_remove(heap, index), &pass);         \
                                                                        \
    index = 0x423;                                                      \
    val = HEAP_val(heap, index);                                        \
    RESULT_CHECK_pointer(val, HEAP_remove(heap, index), &pass);         \
                                                                        \
    index = 0x6;                                                        \
    val = HEAP_val(heap, index);                                        \
    RESULT_CHECK_pointer(val, HEAP_remove(heap, index), &pass);         \
                                                                        \
    index = 0x212;                                                      \
    val = HEAP_val(heap, index);                                        \
    RESULT_CHECK_pointer(val, HEAP_remove(heap, index), &pass);         \
                                                                        \
    HEAP_destroy(&heap);                                                \
    UNIT_TEST_RESULT(name##_heap_remove, pass);                         \
}

#define UT_HEAP_remove_min(name)                             \
static inline void                                           \
utest_##name##_heap_remove_min(void)                         \
{                                                            \
    bool pass;                                               \
    void *tmp;                                               \
    struct HEAP *heap;                                       \
                                                             \
    pass = true;                                             \
    heap = NULL;                                             \
                                                             \
    HEAP_remove_min(heap);                                   \
                                                             \
    heap = TEST_HEAP_sample(0x1435, 0x104E);                 \
    tmp = HEAP_get_min(heap);                                \
    RESULT_CHECK_pointer(tmp, HEAP_remove_min(heap), &pass); \
                                                             \
    HEAP_destroy(&heap);                                     \
    UNIT_TEST_RESULT(name##_heap_remove_min, pass);          \
}

#define UT_HEAP_remove_max(name)                             \
static inline void                                           \
utest_##name##_heap_remove_max(void)                         \
{                                                            \
    bool pass;                                               \
    void *tmp;                                               \
    struct HEAP *heap;                                       \
                                                             \
    pass = true;                                             \
    heap = NULL;                                             \
                                                             \
    HEAP_remove_max(heap);                                   \
                                                             \
    heap = TEST_HEAP_sample(0x1435, 0x1D4E);                 \
    tmp = HEAP_get_max(heap);                                \
    RESULT_CHECK_pointer(tmp, HEAP_remove_max(heap), &pass); \
                                                             \
    HEAP_destroy(&heap);                                     \
    UNIT_TEST_RESULT(name##_heap_remove_max, pass);          \
}

#define UT_HEAP_build(name)                                             \
static inline void                                                      \
utest_##name##_heap_build(void)                                         \
{                                                                       \
    bool pass;                                                          \
    uint32 size;                                                        \
    struct HEAP *heap;                                                  \
    struct HEAP *build;                                                 \
    struct heap_data **hd_array;                                        \
                                                                        \
    pass = true;                                                        \
    heap = NULL;                                                        \
    hd_array = NULL;                                                    \
                                                                        \
    RESULT_CHECK_pointer(PTR_INVALID, HEAP_build(hd_array, 2), &pass);  \
    heap = TEST_HEAP_sample(0x122f, 0x32a);                             \
    RESULT_CHECK_pointer(PTR_INVALID, HEAP_build(hd_array, 0), &pass);  \
                                                                        \
    size = HEAP_size(heap) + 1;                                         \
    hd_array = memory_cache_allocate(size * sizeof(hd_array[0]));       \
                                                                        \
    hd_array[0] = NULL;                                                 \
    dp_memcpy(hd_array, heap->alias->base, size * sizeof(hd_array[0])); \
                                                                        \
    test_binary_heap_data_randomization(hd_array, INDEX_LAST(heap));    \
    build = HEAP_build(hd_array, size);                                 \
                                                                        \
    RESULT_CHECK_bool(true, TEST_HEAP_ordered_p(build), &pass);         \
                                                                        \
    memory_cache_free(build->alias);                                    \
    memory_cache_free(build);                                           \
    memory_cache_free(hd_array);                                        \
    HEAP_destroy(&heap);                                                \
    UNIT_TEST_RESULT(name##_heap_build, pass);                          \
}

#endif

