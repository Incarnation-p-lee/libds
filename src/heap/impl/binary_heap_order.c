/*
 * HEAP_NICE_UPPER_LMT is allowed to nice for remove one node from heap.
 */
static inline bool
binary_heap_order_minimal(struct binary_heap *heap, uint32 index, sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_LOWER_LMT < nice);

    return HEAP_NICE(heap, index) > nice ? true : false;
}

/*
 * HEAP_NICE_LOWER_LMT is allowed to nice for remove one node from heap.
 */
static inline bool
binary_heap_order_maximal(struct binary_heap *heap, uint32 index, sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_UPPER_LMT > nice);

    return HEAP_NICE(heap, index) < nice ? true : false;
}

static inline sint64
binary_heap_order_percolate_down_nice_limit(void *ordering)
{
    assert(NULL != ordering);
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    if (ordering == &binary_heap_order_minimal) {
        return HEAP_NICE_UPPER_LMT;
    } else if (ordering == &binary_heap_order_maximal) {
        return HEAP_NICE_LOWER_LMT;
    } else {
        assert_not_reached();
        return 0;
    }
}

