/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_percolate_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *child)
{
    uint32 small_child;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_node_child_exist_p(heap, index));

    small_child = binary_heap_child_small_nice_index(heap, index);
    if (child) {
        *child = small_child;
    }

    return HEAP_NICE(heap, small_child) > nice ? true : false;
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_percolate_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice)
{
    uint32 parent;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);

    parent = INDEX_PARENT(index);

    return HEAP_NICE(heap, parent) < nice ? true : false;
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_maximal_percolate_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *child)
{
    uint32 big_child;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_node_child_exist_p(heap, index));

    big_child = binary_heap_child_big_nice_index(heap, index);
    if (child) {
        *child = big_child;
    }

    return HEAP_NICE(heap, big_child) < nice ? true : false;
}

/*
 * If nice put into index position ordered.
 *     Return true, or false.
 */
static inline bool
binary_heap_maximal_percolate_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice)
{
    uint32 parent;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);

    parent = INDEX_PARENT(index);

    return HEAP_NICE(heap, parent) > nice ? true : false;
}

