static inline bool
binary_heap_percolate_up_precondition_p(struct binary_heap *heap, uint32 index,
    sint64 nice, void *ordering)
{
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_up_ordered_p(ordering));

    if (!binary_heap_node_child_exist_p(heap, index)) {
        return true;
    } else if (ordering == &binary_heap_minimal_percolate_up_ordered_p) {
        if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
            if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) > nice
                && HEAP_NICE(heap, INDEX_RIGHT_CHILD(index)) > nice) {
                return true;
            } else {
                return false;
            }
        } else if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) > nice) {
            return true;
        } else {
            return false;
        }
    } else if (ordering == &binary_heap_maximal_percolate_up_ordered_p) {
        if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
            if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice
                && HEAP_NICE(heap, INDEX_RIGHT_CHILD(index)) < nice) {
                return true;
            } else {
                return false;
            }
        } else if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice) {
            return true;
        } else {
            return false;
        }
        return true;
    } else {
        assert_not_reached();
        return false;
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
    assert(INDEX_INVALID != index);
    assert(NULL != heap);
    assert(NULL != heap->base);

    if (HEAP_ROOT_INDEX == index) {
        return true;
    } else if (ordering == &binary_heap_minimal_percolate_down_ordered_p) {
        return HEAP_NICE(heap, INDEX_PARENT(index)) < nice ? true : false;
    } else if (ordering == &binary_heap_maximal_percolate_down_ordered_p) {
        return HEAP_NICE(heap, INDEX_PARENT(index)) > nice ? true : false;
    } else {
        assert_not_reached();
        return false;
    }
}

static inline bool
binary_heap_up_ordered_p(void *func_ptr)
{
    void **iter;

    assert(NULL != func_ptr);

    iter = up_order_func;
    while (iter < up_order_func + array_sizeof(up_order_func)) {
        if (*iter++ == func_ptr) {
            return true;
        }
    }

    return false;
}

static inline bool
binary_heap_down_ordered_p(void *func_ptr)
{
    void **iter;

    assert(NULL != func_ptr);

    iter = down_order_func;
    while (iter < down_order_func + array_sizeof(down_order_func)) {
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

