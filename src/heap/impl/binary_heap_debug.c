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

#endif
