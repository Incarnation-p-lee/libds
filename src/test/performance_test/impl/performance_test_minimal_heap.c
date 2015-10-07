static inline void
performance_test_minimal_heap_struc_field(uint32 count)
{
    uint32 index;
    struct minimal_heap *heap;

    index = HEAP_ROOT_INDEX;
    heap = test_minimal_heap_sample(0x231, 0x123);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_link_set(heap, index, minimal_heap_link(heap, index));
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_struc_field),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_create(uint32 count)
{
    struct minimal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = minimal_heap_create(0x1e3);
        minimal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(minimal_heap_create),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_destroy(uint32 count)
{
    struct minimal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_minimal_heap_sample(0x34a, 0x7);
        minimal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(minimal_heap_destroy),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_empty_p(uint32 count)
{
    struct minimal_heap *heap;

    heap = test_minimal_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_empty_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_empty_p),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_full_p(uint32 count)
{
    struct minimal_heap *heap;

    heap = test_minimal_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_full_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_full_p),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_cleanup(uint32 count)
{
    struct minimal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_minimal_heap_sample(0x34a, 0x8);
        minimal_heap_cleanup(heap);
        minimal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(minimal_heap_cleanup),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_find(uint32 count)
{
    struct minimal_heap *heap;

    heap = test_minimal_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_find(heap, 0x601);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_find),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_find_min(uint32 count)
{
    struct minimal_heap *heap;

    heap = test_minimal_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_find_min(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_find_min),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_insert(uint32 count)
{
    struct minimal_heap *heap;

    count = count >> 5;
    count = 0 == count ? 1000 : count;

    heap = minimal_heap_create(count);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_insert(heap, &count, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_insert),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_remove_min(uint32 count)
{
    struct minimal_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = minimal_heap_node_remove_min(heap);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_remove_min),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_remove_min_and_destroy(uint32 count)
{
    struct minimal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_remove_min_and_destroy(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_remove_min_and_destroy),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_remove(uint32 count)
{
    struct minimal_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = minimal_heap_node_remove(heap, count);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_remove),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_remove_and_destroy(uint32 count)
{
    struct minimal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_remove_and_destroy(heap, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_remove_and_destroy),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_decrease_nice(uint32 count)
{
    uint32 index;
    struct minimal_heap *heap;

    index = HEAP_ROOT_INDEX;
    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_decrease_nice(heap, index++, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_decrease_nice),
        performance_test_time_stamp_period());
}

static inline void
performance_test_minimal_heap_node_increase_nice(uint32 count)
{
    struct minimal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_minimal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        minimal_heap_node_increase_nice(heap, count, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    minimal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(minimal_heap_node_increase_nice),
        performance_test_time_stamp_period());
}

