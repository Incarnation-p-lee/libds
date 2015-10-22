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

    if (INDEX_INVALID == index && index > INDEX_LAST(heap)) {
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
binary_heap_nice_repeated_p(struct binary_heap *heap,
    uint32 parent, uint32 small_child, sint64 nice)
{
    assert(NULL != heap);
    assert(NULL != heap->base);

    if (INDEX_INVALID == parent && INDEX_INVALID == small_child) {
        return false;
    } else if (INDEX_INVALID != parent && nice == HEAP_NICE(heap, parent)) {
        return true;
    } else if (INDEX_INVALID != small_child
        && nice == HEAP_NICE(heap, small_child)) {
        return true;
    } else {
        return false;
    }
}

