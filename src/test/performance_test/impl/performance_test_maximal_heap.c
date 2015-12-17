static inline void
performance_test_maximal_heap_struct_field(uint32 count)
{
    uint32 index;
    struct maximal_heap *heap;

    index = INDEX_ROOT;
    heap = test_maximal_heap_sample(0x231, 0x123);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_link_set(heap, index, maximal_heap_link(heap, index));
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_struct_field);
}

static inline void
performance_test_maximal_heap_create(uint32 count)
{
    struct maximal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = maximal_heap_create(0x1e3);
        maximal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(maximal_heap_create);
}

static inline void
performance_test_maximal_heap_destroy(uint32 count)
{
    struct maximal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_maximal_heap_sample(0x34a, 0x7);
        maximal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(maximal_heap_destroy);
}

static inline void
performance_test_maximal_heap_empty_p(uint32 count)
{
    struct maximal_heap *heap;

    heap = test_maximal_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_empty_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_empty_p);
}

static inline void
performance_test_maximal_heap_full_p(uint32 count)
{
    struct maximal_heap *heap;

    heap = test_maximal_heap_sample(0x34a, 0x2c8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_full_p(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_full_p);
}

static inline void
performance_test_maximal_heap_cleanup(uint32 count)
{
    struct maximal_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_maximal_heap_sample(0x34a, 0x8);
        maximal_heap_cleanup(heap);
        maximal_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(maximal_heap_cleanup);
}

static inline void
performance_test_maximal_heap_node_find(uint32 count)
{
    struct maximal_heap *heap;

    heap = test_maximal_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_find(heap, 0x601);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_find);
}

static inline void
performance_test_maximal_heap_node_find_max(uint32 count)
{
    struct maximal_heap *heap;

    heap = test_maximal_heap_sample(0x334a, 0xfd8);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_find_max(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_find_max);
}

static inline void
performance_test_maximal_heap_node_insert(uint32 count)
{
    struct maximal_heap *heap;

    count = count >> 5;
    count = 0 == count ? 1000 : count;

    heap = maximal_heap_create(count);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_insert(heap, &count, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_insert);
}

static inline void
performance_test_maximal_heap_node_remove_max(uint32 count)
{
    struct maximal_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = maximal_heap_node_remove_max(heap);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_remove_max);
}

static inline void
performance_test_maximal_heap_node_remove_max_and_destroy(uint32 count)
{
    struct maximal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_remove_max_and_destroy(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_remove_max_and_destroy);
}

static inline void
performance_test_maximal_heap_node_remove(uint32 count)
{
    struct maximal_heap *heap;
    struct doubly_linked_list *removed;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = maximal_heap_node_remove(heap, count);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_remove);
}

static inline void
performance_test_maximal_heap_node_remove_and_destroy(uint32 count)
{
    struct maximal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_remove_and_destroy(heap, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_remove_and_destroy);
}

static inline void
performance_test_maximal_heap_node_decrease_nice(uint32 count)
{
    uint32 index;
    struct maximal_heap *heap;

    index = INDEX_ROOT;
    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_decrease_nice(heap, index++, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_decrease_nice);
}

static inline void
performance_test_maximal_heap_node_increase_nice(uint32 count)
{
    struct maximal_heap *heap;

    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_increase_nice(heap, count, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_node_increase_nice);
}

static inline void
performance_test_maximal_heap_build(uint32 count)
{
    uint32 chain_size;
    struct maximal_heap *heap;
    struct maximal_heap *build;
    struct collision_chain **chain_array;

    heap = test_maximal_heap_sample(0x12f, 0xa1);
    chain_size = maximal_heap_size(heap) + 1;
    chain_array = memory_cache_allocate(chain_size * sizeof(chain_array[0]));

    chain_array[0] = NULL;
    memcpy(chain_array, heap->alias->base, chain_size * sizeof(chain_array[0]));

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        test_binary_heap_collision_chain_randomization(chain_array, INDEX_LAST(heap->alias));
        build = maximal_heap_build(chain_array, chain_size);

        memory_cache_free(build->alias);
        memory_cache_free(build);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(chain_array);
    maximal_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(maximal_heap_build);
}

