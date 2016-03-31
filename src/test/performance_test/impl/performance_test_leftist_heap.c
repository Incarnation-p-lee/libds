static inline void
performance_test_leftist_heap_struct_field(uint32 count)
{
    struct leftist_heap *heap;

    heap = test_leftist_heap_sample(0x2a1, 0x1d3);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        leftist_heap_nice_set(heap, leftist_heap_nice(heap));
        leftist_heap_npl_set(heap, leftist_heap_npl(heap));
        leftist_heap_val_set(heap, leftist_heap_val(heap));
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_struct_field);
}

static inline void
performance_test_leftist_heap_create(uint32 count)
{
    struct leftist_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = leftist_heap_create();
        leftist_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(leftist_heap_create);
}

static inline void
performance_test_leftist_heap_node_create(uint32 count)
{
    struct leftist_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = leftist_heap_node_create(NULL, 0, 0);
        leftist_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(leftist_heap_node_create);
}

static inline void
performance_test_leftist_heap_destroy(uint32 count)
{
    struct leftist_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = test_leftist_heap_sample(0x123, 0x7);
        leftist_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(leftist_heap_destroy);
}

static inline void
performance_test_leftist_heap_get_min(uint32 count)
{
    struct leftist_heap *heap;

    heap = test_leftist_heap_sample(0x2123, 0x1ec7);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        leftist_heap_get_min(heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_get_min);
}

static inline void
performance_test_leftist_heap_insert(uint32 count)
{
    struct leftist_heap *heap;

    heap = leftist_heap_create();
    /*
     * For sometime too deep nested loop may reach the limit of stack 8KB.
     */
    count = count >> 2;
    count = count == 0 ? 10000 : count;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = leftist_heap_insert(heap, NULL, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_insert);
}

static inline void
performance_test_leftist_heap_merge(uint32 count)
{
    struct leftist_heap *heap;
    struct leftist_heap *tmp;

    heap = test_leftist_heap_sample(0xf, 0xa);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = test_leftist_heap_sample(0xf, 0x4);
        heap = leftist_heap_merge(heap, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_merge);
}

static inline void
performance_test_leftist_heap_remove_min(uint32 count)
{
    struct leftist_heap *heap;
    struct leftist_heap *tmp;

    heap = test_leftist_heap_sample(0xf2d8, 0xa32a);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = leftist_heap_remove_min(&heap);
        leftist_heap_destroy(&tmp);
        tmp = leftist_heap_node_create(NULL, 0, count);
        heap = leftist_heap_merge(heap, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_remove_min);
}

static inline void
performance_test_leftist_heap_remove_min_and_destroy(uint32 count)
{
    struct leftist_heap *heap;
    struct leftist_heap *tmp;

    heap = test_leftist_heap_sample(0xf2d8, 0xa32a);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        leftist_heap_remove_min_and_destroy(&heap);
        tmp = leftist_heap_node_create(NULL, 0, count);
        heap = leftist_heap_merge(heap, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    leftist_heap_destroy(&heap);
    PERFORMANCE_TEST_RESULT(leftist_heap_remove_min_and_destroy);
}

