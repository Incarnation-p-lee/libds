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
    sint64 nice, void *ordering)
{
    bool (*order)(struct binary_heap *, uint32, sint64);

    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    order = ordering;

    if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
        /*
         * index node has child here.
         * minimal, nice[index] < nice
         * maximal, nice[index] > nice
         */
        if (!(*order)(heap, INDEX_LEFT_CHILD(index), nice)
            || !(*order)(heap, INDEX_RIGHT_CHILD(index), nice)) {
            return false;
        } else {
            return true;
        }
    } else if (INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap)) {
        /*
         * index node has one child here.
         */
        if (!(*order)(heap, INDEX_LEFT_CHILD(index), nice)) {
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
 * HEAP_NICE_UPPER_LMT/HEAP_NICE_LOWER_LMT is allowed to nice
 * for remove one node from heap.
 */
static inline bool
binary_heap_percolate_down_precondition_p(struct binary_heap *heap,
    uint32 index, sint64 nice, void *ordering)
{
    bool (*order)(struct binary_heap *, uint32, sint64);

    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    order = ordering;

    if (HEAP_ROOT_INDEX == index) {
        return true;
    } else if (!(*order)(heap, INDEX_PARENT(index), nice)) {
        /*
         * minimal, nice[index] > nice
         * maximal, nice[index] < nice
         */
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

static inline bool
binary_heap_percolate_function_pointer_valid_p(void *func_ptr)
{
    assert(NULL != func_ptr);

    if (func_ptr == &binary_heap_percolate_up
        || func_ptr == &binary_heap_percolate_down) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_percolate_direction_consistent_with_ordering_p(struct binary_heap *heap,
    uint32 index, sint64 new_nice, void *ordering, void *percolate)
{
    bool (*order)(struct binary_heap *, uint32, sint64);
    bool consistent;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(NULL != heap->base[index]);
    assert(0 != index && index <= INDEX_LAST(heap));
    assert(binary_heap_order_function_pointer_valid_p(ordering));
    assert(binary_heap_percolate_function_pointer_valid_p(percolate));
    assert(HEAP_NICE_LOWER_LMT < new_nice && HEAP_NICE_UPPER_LMT > new_nice);

    order = ordering;
    consistent = (*order)(heap, index, new_nice);

    if (percolate == &binary_heap_percolate_up) {
        return consistent;
    } else if (percolate == &binary_heap_percolate_down) {
        return !consistent;
    } else {
        assert_not_reached();
    }
}

#endif
