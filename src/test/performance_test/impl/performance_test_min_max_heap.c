static inline void
performance_test_min_max_heap_struct_field(uint32 count)
{
    uint32 index;
    struct min_max_heap *heap;

    index = INDEX_ROOT;
    heap = test_min_max_heap_sample(0x2310, 0x1230);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_link_set(heap, index, min_max_heap_link(heap, index));
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_struct_field);
}

static inline void
performance_test_min_max_heap_create(uint32 count)
{
    struct min_max_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = min_max_heap_create(0x2e3);
        min_max_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(min_max_heap_create);
}

static inline void
performance_test_min_max_heap_destroy(uint32 count)
{
    struct min_max_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_min_max_heap_sample(0x34a, 0x7);
        min_max_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(min_max_heap_destroy);
}

static inline void
performance_test_min_max_heap_empty_p(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_empty_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_empty_p);
}

static inline void
performance_test_min_max_heap_full_p(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_full_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_full_p);
}

static inline void
performance_test_min_max_heap_cleanup(uint32 count)
{
    struct min_max_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_min_max_heap_sample(0x34a, 0x8);
        min_max_heap_cleanup(heap);
        min_max_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(min_max_heap_cleanup);
}

static inline void
performance_test_min_max_heap_node_find(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_find(heap, 0x601);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_find);
}

static inline void
performance_test_min_max_heap_node_find_min(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_find_min(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_find_min);
}

static inline void
performance_test_min_max_heap_node_find_max(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_find_max(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_find_max);
}

static inline void
performance_test_min_max_heap_node_insert(uint32 count)
{
    struct min_max_heap *heap;

    count = count >> 5;
    count = 0 == count ? 1000 : count;

    heap = min_max_heap_create(count);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_insert(heap, &count, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_insert);
}

static inline void
performance_test_min_max_heap_node_depth(uint32 count)
{
    struct min_max_heap *heap;

    heap = test_min_max_heap_sample(0x334a, 0x1fd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_depth(heap, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_depth);
}

static inline void
performance_test_min_max_heap_node_remove_min(uint32 count)
{
    struct min_max_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = min_max_heap_node_remove_min(heap);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove_min);
}

static inline void
performance_test_min_max_heap_node_remove_max(uint32 count)
{
    struct min_max_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = min_max_heap_node_remove_max(heap);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove_max);
}

static inline void
performance_test_min_max_heap_node_remove_min_and_destroy(uint32 count)
{
    struct min_max_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_remove_min_and_destroy(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove_min_and_destroy);
}

static inline void
performance_test_min_max_heap_node_remove(uint32 count)
{
    struct min_max_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = min_max_heap_node_remove(heap, count);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove);
}

static inline void
performance_test_min_max_heap_node_remove_and_destroy(uint32 count)
{
    struct min_max_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_remove_and_destroy(heap, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove_and_destroy);
}

static inline void
performance_test_min_max_heap_node_remove_max_and_destroy(uint32 count)
{
    struct min_max_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_remove_max_and_destroy(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_remove_max_and_destroy);
}

static inline void
performance_test_min_max_heap_node_decrease_nice(uint32 count)
{
    uint32 index;
    struct min_max_heap *heap;

    index = INDEX_ROOT;
    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_decrease_nice(heap, index++, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_decrease_nice);
}

static inline void
performance_test_min_max_heap_node_increase_nice(uint32 count)
{
    struct min_max_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_min_max_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        min_max_heap_node_increase_nice(heap, count, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    min_max_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(min_max_heap_node_increase_nice);
}

