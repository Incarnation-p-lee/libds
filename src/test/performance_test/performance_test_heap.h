#ifndef HAVE_DEFINED_PERFORMANCE_TEST_HEAP_H
#define HAVE_DEFINED_PERFORMANCE_TEST_HEAP_H

#define PT_HEAP_create(name)                     \
static inline void                               \
ptest_##name##_heap_create(uint32 count)         \
{                                                \
    struct HEAP *heap;                           \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        heap = HEAP_create(0x1e3);               \
        HEAP_destroy(&heap);                     \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    PERFORMANCE_TEST_RESULT(name##_heap_create); \
}

#define PT_HEAP_destroy(name)                     \
static inline void                                \
ptest_##name##_heap_destroy(uint32 count)         \
{                                                 \
    struct HEAP *heap;                            \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        heap = TEST_HEAP_sample(0x34a, 0x7);      \
        HEAP_destroy(&heap);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_heap_destroy); \
}

#define PT_HEAP_empty_p(name)                     \
static inline void                                \
ptest_##name##_heap_empty_p(uint32 count)         \
{                                                 \
    struct HEAP *heap;                            \
                                                  \
    heap = TEST_HEAP_sample(0x34a, 0x2c8);        \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        HEAP_empty_p(heap);                       \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    HEAP_destroy(&heap);                          \
    PERFORMANCE_TEST_RESULT(name##_heap_empty_p); \
}

#define PT_HEAP_full_p(name)                     \
static inline void                               \
ptest_##name##_heap_full_p(uint32 count)         \
{                                                \
    struct HEAP *heap;                           \
                                                 \
    heap = TEST_HEAP_sample(0x34a, 0x2c8);       \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        HEAP_full_p(heap);                       \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    HEAP_destroy(&heap);                         \
    PERFORMANCE_TEST_RESULT(name##_heap_full_p); \
}

#define PT_HEAP_cleanup(name)                     \
static inline void                                \
ptest_##name##_heap_cleanup(uint32 count)         \
{                                                 \
    struct HEAP *heap;                            \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        heap = TEST_HEAP_sample(0x34a, 0x8);      \
        HEAP_cleanup(heap);                       \
        HEAP_destroy(&heap);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_heap_cleanup); \
}

#define PT_HEAP_get_min(name)                     \
static inline void                                \
ptest_##name##_heap_get_min(uint32 count)         \
{                                                 \
    struct HEAP *heap;                            \
                                                  \
    heap = TEST_HEAP_sample(0x334a, 0xfd8);       \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        HEAP_get_min(heap);                       \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    HEAP_destroy(&heap);                          \
    PERFORMANCE_TEST_RESULT(name##_heap_get_min); \
}

#define PT_HEAP_get_max(name)                     \
static inline void                                \
ptest_##name##_heap_get_max(uint32 count)         \
{                                                 \
    struct HEAP *heap;                            \
                                                  \
    heap = TEST_HEAP_sample(0x334a, 0xfd8);       \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        HEAP_get_max(heap);                       \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    HEAP_destroy(&heap);                          \
    PERFORMANCE_TEST_RESULT(name##_heap_get_max); \
}

#define PT_HEAP_insert(name)                     \
static inline void                               \
ptest_##name##_heap_insert(uint32 count)         \
{                                                \
    struct HEAP *heap;                           \
                                                 \
    count = count >> 5;                          \
    count = 0 == count ? 1000 : count;           \
                                                 \
    heap = HEAP_create(count);                   \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        HEAP_insert(heap, &count, count);        \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    HEAP_destroy(&heap);                         \
    PERFORMANCE_TEST_RESULT(name##_heap_insert); \
}

#define PT_HEAP_remove_min(name)                     \
static inline void                                   \
ptest_##name##_heap_remove_min(uint32 count)         \
{                                                    \
    struct HEAP *heap;                               \
                                                     \
    count = count >> 6;                              \
    count = 0 == count ? 1000 : count;               \
    heap = TEST_HEAP_sample(count * 4, count * 2);   \
                                                     \
    PERFORMANCE_TEST_CHECKPOINT;                     \
                                                     \
    while (count--) {                                \
        HEAP_remove_min(heap);                       \
    }                                                \
                                                     \
    PERFORMANCE_TEST_ENDPOINT;                       \
                                                     \
    HEAP_destroy(&heap);                             \
    PERFORMANCE_TEST_RESULT(name##_heap_remove_min); \
}

#define PT_HEAP_remove_max(name)                     \
static inline void                                   \
ptest_##name##_heap_remove_max(uint32 count)         \
{                                                    \
    struct HEAP *heap;                               \
                                                     \
    count = count >> 6;                              \
    count = 0 == count ? 1000 : count;               \
    heap = TEST_HEAP_sample(count * 4, count * 2);   \
                                                     \
    PERFORMANCE_TEST_CHECKPOINT;                     \
                                                     \
    while (count--) {                                \
        HEAP_remove_max(heap);                       \
    }                                                \
                                                     \
    PERFORMANCE_TEST_ENDPOINT;                       \
                                                     \
    HEAP_destroy(&heap);                             \
    PERFORMANCE_TEST_RESULT(name##_heap_remove_max); \
}

#define PT_HEAP_remove(name)                       \
static inline void                                 \
ptest_##name##_heap_remove(uint32 count)           \
{                                                  \
    struct HEAP *heap;                             \
                                                   \
    count = count >> 6;                            \
    count = 0 == count ? 1000 : count;             \
                                                   \
    heap = TEST_HEAP_sample(count * 4, count * 2); \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        HEAP_remove(heap, count);                  \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    HEAP_destroy(&heap);                           \
    PERFORMANCE_TEST_RESULT(name##_heap_remove);   \
}

#define PT_HEAP_decrease_nice(name)                     \
static inline void                                      \
ptest_##name##_heap_decrease_nice(uint32 count)         \
{                                                       \
    uint32 index;                                       \
    struct HEAP *heap;                                  \
                                                        \
    index = INDEX_ROOT;                                 \
    count = count >> 6;                                 \
    count = 0 == count ? 1000 : count;                  \
    heap = TEST_HEAP_sample(count * 4, count * 2);      \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    while (count--) {                                   \
        HEAP_decrease_nice(heap, index++, 1);           \
    }                                                   \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    HEAP_destroy(&heap);                                \
    PERFORMANCE_TEST_RESULT(name##_heap_decrease_nice); \
}

#define PT_HEAP_increase_nice(name)                     \
static inline void                                      \
ptest_##name##_heap_increase_nice(uint32 count)         \
{                                                       \
    struct HEAP *heap;                                  \
                                                        \
    count = count >> 6;                                 \
    count = 0 == count ? 1000 : count;                  \
    heap = TEST_HEAP_sample(count * 4, count * 2);      \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    while (count--) {                                   \
        HEAP_increase_nice(heap, count, 1);             \
    }                                                   \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    HEAP_destroy(&heap);                                \
    PERFORMANCE_TEST_RESULT(name##_heap_increase_nice); \
}

#define PT_HEAP_build(name)                                          \
static inline void                                                   \
ptest_##name##_heap_build(uint32 count)                              \
{                                                                    \
    uint32 size;                                                     \
    struct HEAP *heap;                                               \
    struct HEAP *build;                                              \
    struct heap_data **hd_array;                                     \
                                                                     \
    heap = TEST_HEAP_sample(0x12f, 0xa1);                            \
    size = HEAP_size(heap) + 1;                                      \
                                                                     \
    hd_array = memory_cache_allocate(size * sizeof(hd_array[0]));    \
    hd_array[0] = NULL;                                              \
    memcpy(hd_array, heap->alias->base, size * sizeof(hd_array[0])); \
    PERFORMANCE_TEST_CHECKPOINT;                                     \
                                                                     \
    while (count--) {                                                \
        test_binary_heap_data_randomization(hd_array,                \
            INDEX_LAST(heap->alias));                                \
        build = HEAP_build(hd_array, size);                          \
                                                                     \
        memory_cache_free(build->alias);                             \
        memory_cache_free(build);                                    \
    }                                                                \
                                                                     \
    PERFORMANCE_TEST_ENDPOINT;                                       \
                                                                     \
    memory_cache_free(hd_array);                                     \
    HEAP_destroy(&heap);                                             \
    PERFORMANCE_TEST_RESULT(name##_heap_build);                      \
}

#endif

