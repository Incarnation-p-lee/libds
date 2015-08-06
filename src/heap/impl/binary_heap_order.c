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

static inline bool
binary_heap_order_maximal(struct binary_heap *heap, uint32 index, sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);

    return HEAP_NICE(heap, index) < nice ? true : false;
}

