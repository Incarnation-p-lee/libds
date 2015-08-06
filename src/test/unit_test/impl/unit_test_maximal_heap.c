static inline struct maximal_heap *
unit_test_maximal_heap_sample(uint64 range, uint32 size)
{
    struct maximal_heap *heap;
    sint64 nice;
    uint32 i;

    assert(0 != size);

    heap = maximal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
        maximal_heap_node_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline void
unit_test_maximal_heap_struc_field(void)
{
    bool pass;
    uint32 loop;
    uint32 index;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x1234567;
    index = 1;
    heap = unit_test_maximal_heap_sample(0x3DA2, 0x2F23);

    while (loop--) {
        RESULT_CHECK_uint32(heap->bin_heap->size, maximal_heap_size(heap), &pass);
        RESULT_CHECK_uint32(heap->bin_heap->capacity, maximal_heap_capacity(heap), &pass);
        RESULT_CHECK_sint64(heap->bin_heap->base[index]->nice,
            maximal_heap_nice(heap, index), &pass);
        RESULT_CHECK_pointer(heap->bin_heap->base[index]->link,
            maximal_heap_link(heap, index), &pass);
        tmp = maximal_heap_link(heap, index);
        RESULT_CHECK_pointer(NULL, maximal_heap_link_set(heap, index, NULL), &pass);
        RESULT_CHECK_pointer(tmp, maximal_heap_link_set(heap, index, tmp), &pass);
    }

    maximal_heap_destroy(&heap);
    test_result_print(SYM_2_STR(maximal_heap_struc_field), pass);
}

static inline void
unit_test_maximal_heap_create(void)
{
    bool pass;
    uint32 loop;
    uint32 capacity;
    struct maximal_heap *heap;
    struct collision_chain **iter;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0xA234u;
    capacity = 0u;

    heap = maximal_heap_create(capacity++);
    maximal_heap_destroy(&heap);

    while (loop--) {
        heap = maximal_heap_create(capacity);
        RESULT_CHECK_uint32(capacity, maximal_heap_capacity(heap), &pass);
        RESULT_CHECK_uint32(0u, maximal_heap_size(heap), &pass);

        iter = heap->bin_heap->base;
        while (iter < heap->bin_heap->base + u_offset(heap->bin_heap->capacity, 1)) {
            RESULT_CHECK_pointer(NULL, *iter++, &pass);
        }

        maximal_heap_destroy(&heap);
        capacity++;
    }

    test_result_print(SYM_2_STR(maximal_heap_create), pass);
}

static inline void
unit_test_maximal_heap_destroy(void)
{
    bool pass;
    uint32 loop;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x12345u;
    heap = NULL;

    maximal_heap_destroy(&heap);

    while (loop--) {
        heap = maximal_heap_create(loop);
        maximal_heap_destroy(&heap);
        RESULT_CHECK_pointer(NULL, heap, &pass);
    }

    test_result_print(SYM_2_STR(maximal_heap_destroy), pass);
}

static inline void
unit_test_maximal_heap_empty_p(void)
{
    bool pass;
    uint32 loop;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x1A345u;
    heap = NULL;

    RESULT_CHECK_bool(false, maximal_heap_empty_p(heap), &pass);

    heap = unit_test_maximal_heap_sample(0x2234, 0x1234);
    RESULT_CHECK_bool(false, maximal_heap_empty_p(heap), &pass);
    maximal_heap_destroy(&heap);

    while (loop--) {
        heap = maximal_heap_create(loop);
        RESULT_CHECK_bool(true, maximal_heap_empty_p(heap), &pass);
        maximal_heap_destroy(&heap);
    }

    test_result_print(SYM_2_STR(maximal_heap_empty_p), pass);
}

static inline void
unit_test_maximal_heap_full_p(void)
{
    bool pass;
    uint32 loop;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x1A345u;
    heap = NULL;

    RESULT_CHECK_bool(true, maximal_heap_full_p(heap), &pass);

    heap = unit_test_maximal_heap_sample(0x1, 0x1);
    RESULT_CHECK_bool(true, maximal_heap_full_p(heap), &pass);
    maximal_heap_destroy(&heap);

    while (loop--) {
        heap = maximal_heap_create(loop);
        RESULT_CHECK_bool(false, maximal_heap_full_p(heap), &pass);
        maximal_heap_destroy(&heap);
    }

    test_result_print(SYM_2_STR(maximal_heap_full_p), pass);
}

static inline void
unit_test_maximal_heap_cleanup(void)
{
    bool pass;
    uint32 loop;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x3u;
    heap = NULL;

    maximal_heap_cleanup(heap);

    while (loop--) {
        heap = unit_test_maximal_heap_sample(0xe345, 0x804E);
        maximal_heap_cleanup(heap);

        RESULT_CHECK_bool(false, maximal_heap_full_p(heap), &pass);
        RESULT_CHECK_bool(true, maximal_heap_empty_p(heap), &pass);
        maximal_heap_destroy(&heap);
    }

    test_result_print(SYM_2_STR(maximal_heap_cleanup), pass);
}

static inline void
unit_test_maximal_heap_node_find(void)
{
    bool pass;
    uint32 loop;
    uint32 index;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x12345678u;
    index = 1u;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, maximal_heap_node_find(heap, index), &pass);

    heap = unit_test_maximal_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(maximal_heap_link(heap, index),
        maximal_heap_node_find(heap, maximal_heap_nice(heap, index)), &pass);
    index = 0x144Eu;
    RESULT_CHECK_pointer(NULL, maximal_heap_node_find(heap, (sint64)index), &pass);

    index = 0x2u;
    while (loop--) {
        RESULT_CHECK_pointer(maximal_heap_link(heap, index),
            maximal_heap_node_find(heap, maximal_heap_nice(heap, index)), &pass);
    }

    maximal_heap_destroy(&heap);
    test_result_print(SYM_2_STR(maximal_heap_node_find), pass);
}

static inline void
unit_test_maximal_heap_node_find_max(void)
{
    bool pass;
    uint32 loop;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x22345678u;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, maximal_heap_node_find_max(heap), &pass);

    heap = unit_test_maximal_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(maximal_heap_link(heap, 1u),
        maximal_heap_node_find_max(heap), &pass);

    while (loop--) {
        RESULT_CHECK_pointer(maximal_heap_link(heap, 1u),
            maximal_heap_node_find_max(heap), &pass);
    }

    maximal_heap_destroy(&heap);
    test_result_print(SYM_2_STR(maximal_heap_node_find_max), pass);
}

static inline void
unit_test_maximal_heap_node_insert(void)
{
    bool pass;
    uint32 loop;
    uint32 size;
    struct maximal_heap *heap;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0xA234;
    heap = NULL;

    maximal_heap_node_insert(heap, &pass, 0u);

    heap = unit_test_maximal_heap_sample(0x1345, 0x104E);
    while (loop--) {
        if (maximal_heap_node_find(heap, loop)) {
            maximal_heap_node_insert(heap, &pass, loop);
        } else {
            size = maximal_heap_size(heap);
            maximal_heap_node_insert(heap, &pass, loop);
            RESULT_CHECK_uint32(size + 1, maximal_heap_size(heap), &pass);
        }
    }

    maximal_heap_destroy(&heap);
    test_result_print(SYM_2_STR(maximal_heap_node_insert), pass);
}

// static inline void
// unit_test_minimal_heap_node_remove_min(void)
// {
//     bool pass;
//     uint32 loop;
//     struct minimal_heap *heap;
//     struct doubly_linked_list *minimal;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x123;
//     heap = NULL;
// 
//     minimal_heap_node_remove_min(heap);
// 
//     heap = unit_test_minimal_heap_sample(0x14235, 0x10D4E);
//     while (loop--) {
//         minimal = minimal_heap_node_find_min(heap);
//         RESULT_CHECK_pointer(minimal, minimal_heap_node_remove_min(heap), &pass);
//         doubly_linked_list_destroy(&minimal);
//     }
//     minimal_heap_destroy(&heap);
// 
//     test_result_print(SYM_2_STR(minimal_heap_node_remove_min), pass);
//     return;
// }
// 
// static inline void
// unit_test_minimal_heap_node_remove_min_and_destroy(void)
// {
//     bool pass;
//     uint32 loop;
//     uint32 size;
//     struct minimal_heap *heap;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x123;
//     heap = NULL;
// 
//     minimal_heap_node_remove_min_and_destroy(heap);
// 
//     heap = unit_test_minimal_heap_sample(0x14235, 0x10D4E);
//     size = minimal_heap_size(heap);
// 
//     while (loop--) {
//         minimal_heap_node_find_min(heap);
//         minimal_heap_node_remove_min_and_destroy(heap);
//         size--;
//         RESULT_CHECK_uint32(size, minimal_heap_size(heap), &pass);
//     }
// 
//     minimal_heap_destroy(&heap);
//     test_result_print(SYM_2_STR(minimal_heap_node_remove_min_and_destroy), pass);
// }
// 
// static inline void
// unit_test_minimal_heap_node_decrease_nice(void)
// {
//     bool pass;
//     uint32 loop;
//     uint32 offset;
//     sint64 nice;
//     struct minimal_heap *heap;
//     struct doubly_linked_list *tmp;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x12;
//     heap = NULL;
//     offset = 0;
// 
//     minimal_heap_node_decrease_nice(heap, 0, offset);
// 
//     heap = unit_test_minimal_heap_sample(0xf345, 0xf2E0);
//     minimal_heap_node_decrease_nice(heap, 0, offset);
//     offset = 0x1234;
// 
//     while (loop--) {
//         tmp = minimal_heap_node_find(heap, loop);
//         if (tmp) {
//             nice = (sint64)loop - offset;
//             if (!minimal_heap_node_find(heap, nice)) {
//                 minimal_heap_node_decrease_nice(heap, loop, offset);
//                 RESULT_CHECK_pointer(tmp, minimal_heap_node_find(heap, nice), &pass);
//             } else {
//                 minimal_heap_node_decrease_nice(heap, loop, offset);
//             }
//         } else {
//             minimal_heap_node_decrease_nice(heap, loop, offset);
//         }
//     }
//     minimal_heap_destroy(&heap);
// 
//     test_result_print(SYM_2_STR(minimal_heap_node_decrease_nice), pass);
//     return;
// }
// 
// static inline void
// unit_test_minimal_heap_node_increase_nice(void)
// {
//     bool pass;
//     uint32 loop;
//     uint32 offset;
//     sint64 nice;
//     struct minimal_heap *heap;
//     struct doubly_linked_list *tmp;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x12;
//     heap = NULL;
//     offset = 0;
// 
//     minimal_heap_node_increase_nice(heap, 0, offset);
// 
//     heap = unit_test_minimal_heap_sample(0xe942, 0xb73a);
//     minimal_heap_node_increase_nice(heap, 0, offset);
//     offset = 0x1234;
// 
//     while (loop--) {
//         tmp = minimal_heap_node_find(heap, loop);
//         if (tmp) {
//             nice = (sint64)loop + offset;
//             if (!minimal_heap_node_find(heap, nice)) {
//                 minimal_heap_node_increase_nice(heap, loop, offset);
//                 RESULT_CHECK_pointer(tmp, minimal_heap_node_find(heap, nice), &pass);
//             } else {
//                 minimal_heap_node_increase_nice(heap, loop, offset);
//             }
//         } else {
//             minimal_heap_node_increase_nice(heap, loop, offset);
//         }
//     }
//     minimal_heap_destroy(&heap);
// 
//     test_result_print(SYM_2_STR(minimal_heap_node_increase_nice), pass);
//     return;
// }
// 
// static inline void
// unit_test_minimal_heap_node_remove(void)
// {
//     bool pass;
//     uint32 loop;
//     sint64 nice;
//     struct minimal_heap *heap;
//     struct doubly_linked_list *tmp;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x12;
//     heap = NULL;
// 
//     minimal_heap_node_remove(heap, 0);
// 
//     heap = unit_test_minimal_heap_sample(0xe942, 0xb73a);
//     nice = 0x12345;
//     RESULT_CHECK_pointer(NULL, minimal_heap_node_remove(heap, nice), &pass);
// 
//     nice = 0x45;
//     while (loop--) {
//         tmp = minimal_heap_node_find(heap, nice);
//         if (tmp) {
//             RESULT_CHECK_pointer(tmp, minimal_heap_node_remove(heap, nice), &pass);
//             doubly_linked_list_destroy(&tmp);
//         } else {
//             RESULT_CHECK_pointer(NULL, minimal_heap_node_remove(heap, nice), &pass);
//         }
//         nice--;
//     }
//     minimal_heap_destroy(&heap);
// 
//     test_result_print(SYM_2_STR(minimal_heap_node_remove), pass);
//     return;
// }
// 
// static inline void
// unit_test_minimal_heap_node_remove_and_destroy(void)
// {
//     bool pass;
//     uint32 loop;
//     sint64 nice;
//     struct minimal_heap *heap;
//     struct doubly_linked_list *tmp;
// 
//     TEST_PERFORMANCE_CHECKPOINT;
// 
//     pass = true;
//     loop = 0x12;
//     heap = NULL;
// 
//     minimal_heap_node_remove(heap, 0);
// 
//     heap = unit_test_minimal_heap_sample(0xe942, 0xb73a);
//     nice = 0x12345;
//     minimal_heap_node_remove_and_destroy(heap, nice);
// 
//     nice = 0x45;
//     while (loop--) {
//         tmp = minimal_heap_node_find(heap, nice);
//         if (tmp) {
//             minimal_heap_node_remove_and_destroy(heap, nice);
//             RESULT_CHECK_pointer(NULL, minimal_heap_node_find(heap, nice), &pass);
//         }
//         nice--;
//     }
//     minimal_heap_destroy(&heap);
// 
//     test_result_print(SYM_2_STR(minimal_heap_node_remove_and_destroy), pass);
//     return;
// }
// 
