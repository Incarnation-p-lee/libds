static inline bool
binary_heap_valid_ordered_func_ptr_p(void *func_ptr)
{
    void **iter;

    assert(NULL != func_ptr);

    iter = heap_order_func;
    while (iter < heap_order_func + array_sizeof(heap_order_func)) {
        if (*iter++ == func_ptr) {
            return true;
        }
    }

    return false;
}

static inline bool
binary_heap_node_contains_with_null_p(struct binary_heap *heap, sint64 nice)
{
    register uint32 index;

    assert(binary_heap_structure_legal_p(heap));

    index = INDEX_FIRST;

    while (index <= INDEX_LAST(heap)) {
        if (HEAP_CHAIN(heap, index) && nice == HEAP_NICE(heap, index)) {
            return true;
        }

        index++;
    }

    return false;
}

static inline bool
binary_heap_nice_legal_p(sint64 nice)
{
    if (nice > HEAP_NICE_LOWER_LMT && nice < HEAP_NICE_UPPER_LMT) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_index_legal_p(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));

    if (INDEX_INVALID == index || index > INDEX_LAST(heap)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_heap_structure_legal_p(struct binary_heap *heap)
{
    if (NULL != heap && NULL != heap->base) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_nice_repeated_p(struct binary_heap *heap, uint32 index, sint64 nice)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_nice_legal_p(nice));

    if (INDEX_INVALID == index) {
        return false;
    } else if (nice == HEAP_NICE(heap, index)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_node_depth_even_p(struct binary_heap *heap, uint32 index)
{
    uint32 depth;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_node_depth(index);

    return 0u == (depth & 0x1u) ? true : false;
}

static inline bool
binary_heap_node_depth_odd_p(struct binary_heap *heap, uint32 index)
{
    uint32 depth;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_node_depth(index);

    return 1u == (depth & 0x1u) ? true : false;
}

static inline bool
binary_heap_ordered_p(struct binary_heap *heap, void *heap_order)
{
    uint32 index;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_valid_ordered_func_ptr_p(heap_order));

    index = INDEX_ROOT;
    order = heap_order;

    while (index <= INDEX_LAST(heap)) {
        if (!(*order)(heap, index, HEAP_NICE(heap, index), NULL)) {
            return false;
        }
        index++;
    }

    return true;
}

