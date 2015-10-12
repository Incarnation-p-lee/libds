static inline void
performance_test_maximal_heap_struc_field(uint32 count)
{
    uint32 index;
    struct maximal_heap *heap;

    index = HEAP_ROOT_INDEX;
    heap = test_maximal_heap_sample(0x231, 0x123);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_link_set(heap, index, maximal_heap_link(heap, index));
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(maximal_heap_struc_field),
        performance_test_time_stamp_period());
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

    performance_test_result_print(SYM_2_STR(maximal_heap_create),
        performance_test_time_stamp_period());
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

    performance_test_result_print(SYM_2_STR(maximal_heap_destroy),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_empty_p),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_full_p),
        performance_test_time_stamp_period());
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

    performance_test_result_print(SYM_2_STR(maximal_heap_cleanup),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_find),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_find_max),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_insert),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_remove_max),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_remove_max_and_destroy),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_remove),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_remove_and_destroy),
        performance_test_time_stamp_period());
}

static inline void
performance_test_maximal_heap_node_decrease_nice(uint32 count)
{
    uint32 index;
    struct maximal_heap *heap;

    index = HEAP_ROOT_INDEX;
    count = count >> 6;
    count = 0 == count ? 1000 : count;

    heap = test_maximal_heap_sample(count * 4, count * 2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        maximal_heap_node_decrease_nice(heap, index++, 1);
    }

    PERFORMANCE_TEST_ENDPOINT;

    maximal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(maximal_heap_node_decrease_nice),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(maximal_heap_node_increase_nice),
        performance_test_time_stamp_period());
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
    chain_array = malloc_ds(chain_size * sizeof(chain_array[0]));

    chain_array[0] = NULL;
    memcpy(chain_array, heap->alias->base, chain_size * sizeof(chain_array[0]));

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        test_binary_heap_collision_chain_randomization(chain_array, INDEX_LAST(heap->alias));
        build = maximal_heap_build(chain_array, chain_size);

        free_ds(build->alias);
        free_ds(build);
    }

    PERFORMANCE_TEST_ENDPOINT;

    free_ds(chain_array);
    maximal_heap_destroy(&heap);
    performance_test_result_print(SYM_2_STR(maximal_heap_build),
        performance_test_time_stamp_period());
}

