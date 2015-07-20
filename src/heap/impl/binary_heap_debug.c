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

    if (HEAP_ROOT_INDEX == index) {
        return true;
    } else if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
        if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice ||
            HEAP_NICE(heap, INDEX_RIGHT_CHILD(index)) < nice) {
            return false;
        } else {
            return true;
        }
    } else if (INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap)) {
        if (HEAP_NICE(heap, INDEX_LEFT_CHILD(index)) < nice) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

#endif
