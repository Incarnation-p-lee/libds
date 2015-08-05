#if defined(DEBUG)

static inline bool
binary_heap_node_contains_with_hole_p(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(NULL != heap);

    index = INDEX_FIRST;
    while (index <= INDEX_LAST(heap)) {
        if (NULL != HEAP_CHAIN(heap, index) && nice == HEAP_NICE(heap, index)) {
            return true;
        }
        index++;
    }

    return false;
}

static inline bool
binary_heap_percolate_up_precondition_p(struct binary_heap *heap, uint32 index,
    sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));

    if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
        /*
         * index node has child here.
         */
        if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice
            || HEAP_NICE(heap, INDEX_RIGHT_CHILD(index)) < nice) {
            return false;
        } else {
            return true;
        }
    } else if (INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap)) {
        /*
         * index node has one child here.
         */
        if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice) {
            return false;
        } else {
            return true;
        }
    } else {
        /*
         * index node has no child here.
         */
        return true;
    }
}

/*
 * HEAP_NICE_UPPER_LMT is allowed to nice for remove one node from heap.
 */
static inline bool
binary_heap_percolate_down_precondition_p(struct binary_heap *heap,
    uint32 index, sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_LOWER_LMT < nice);
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));

    if (HEAP_ROOT_INDEX == index) {
        return true;
    } else if (HEAP_NICE(heap, INDEX_PARENT(index)) < nice) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_order_function_pointer_valid_p(void *func_ptr)
{
    void **iter;

    assert(NULL != func_ptr);

    iter = order_func_list;
    while (iter < order_func_list + array_sizeof(order_func_list)) {
        if (*iter++ == func_ptr) {
            return true;
        }
    }

    return false;
}

#endif
