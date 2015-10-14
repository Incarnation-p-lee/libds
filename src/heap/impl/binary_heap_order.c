/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_percolate_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 small_child;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_node_child_exist_p(heap, index));

    small_child = binary_heap_child_small_nice_index(heap, index);

    if (HEAP_NICE(heap, small_child) > nice) {
        return true;
    } else if (HEAP_NICE(heap, small_child) < nice) {
        if (next) {
            *next = small_child;
        }

        return false;
    } else {
        assert_not_reached();
    }
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_percolate_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 parent;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);

    parent = INDEX_PARENT(index);

    if (HEAP_NICE(heap, parent) < nice) {
        return true;
    } else if (HEAP_NICE(heap, parent) > nice) {
        if (next) {
            *next = parent;
        }

        return false;
    } else {
        assert_not_reached();
    }
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_maximal_percolate_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 big_child;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_node_child_exist_p(heap, index));

    big_child = binary_heap_child_big_nice_index(heap, index);

    if (HEAP_NICE(heap, big_child) < nice) {
        return true;
    } else if (HEAP_NICE(heap, big_child) > nice) {
        if (next) {
            *next = big_child;
        }

        return false;
    } else {
        assert_not_reached();
    }
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_maximal_percolate_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 parent;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);

    parent = INDEX_PARENT(index);

    if (HEAP_NICE(heap, parent) > nice) {
        return true;
    } else if (HEAP_NICE(heap, parent) < nice) {
        if (next) {
            *next = parent;
        }

        return false;
    } else {
        assert_not_reached();
    }
}

