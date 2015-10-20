/*
 * Heap-order, minimal heap
 * If nice put into index position ordered
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 small_child;
    uint32 parent;
    uint32 next;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);

    parent = INDEX_PARENT(index);
    small_child = binary_heap_child_small_nice_index(heap, index);

    if (INDEX_INVALID != parent && HEAP_NICE(heap, parent) > nice) {
        next = parent;
        goto HEAP_UNORDERED;
    } else if (INDEX_INVALID != small_child
        && HEAP_NICE(heap, small_child) < nice) {
        next = small_child;
        goto HEAP_UNORDERED;
    } else {
        assert(nice != HEAP_NICE(heap, parent));
        assert(nice != HEAP_NICE(heap, small_child));

        return true;
    }

HEAP_UNORDERED:
    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
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
    assert(HEAP_ROOT_INDEX != index);

    parent = INDEX_PARENT(index);
    assert(nice != HEAP_NICE(heap, parent));

    if (HEAP_NICE(heap, parent) < nice) {
        return true;
    } else {
        if (next) {
            *next = parent;
        }

        return false;
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
    assert(nice != HEAP_NICE(heap, big_child));

    if (HEAP_NICE(heap, big_child) < nice) {
        return true;
    } else {
        if (next) {
            *next = big_child;
        }

        return false;
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
    assert(HEAP_ROOT_INDEX != index);

    parent = INDEX_PARENT(index);
    assert(nice != HEAP_NICE(heap, parent));

    if (HEAP_NICE(heap, parent) > nice) {
        return true;
    } else {
        if (next) {
            *next = parent;
        }

        return false;
    }
}

static inline bool
binary_heap_range_ordered_p(struct binary_heap *heap, uint32 up_idx,
    uint32 down_idx, sint64 nice, uint32 *next)
{
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != up_idx);
    assert(INDEX_INVALID != down_idx);
    assert(nice != HEAP_NICE(heap, up_idx));
    assert(nice != HEAP_NICE(heap, down_idx));

    if (HEAP_NICE(heap, down_idx) > nice) {
        if (next) {
            *next = down_idx;
        }

        return false;
    } else if (HEAP_NICE(heap, up_idx) < nice) {
        if (next) {
            *next = up_idx;
        }

        return false;
    } else {
        return true;
    }
}

/*
 * If nice put into index position ordered
 *     Return true, or false
 */
static inline bool
binary_heap_min_max_percolate_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 child;
    uint32 grandson;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(binary_heap_node_child_exist_p(heap, index));

    child = INDEX_LEFT_CHILD(index);
    grandson = INDEX_LEFT_CHILD(child);
    assert(nice != HEAP_NICE(heap, child));


    if (grandson > INDEX_LAST(heap)) {
    } else {

    }

    return false;
}

/*
 * If nice put into index position ordered
 *     Return true, or false
 * min_max heap may lose the concept of percolate up and down
 */
static inline bool
binary_heap_min_max_percolate_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *next)
{
    uint32 depth;
    uint32 parent;
    uint32 grandparent;
    uint32 up_idx;
    uint32 down_idx;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(INDEX_INVALID != index);
    assert(HEAP_ROOT_INDEX != index);

    parent = INDEX_PARENT(index);
    assert(nice != HEAP_NICE(heap, parent));

    if (HEAP_ROOT_INDEX == parent && HEAP_NICE(heap, parent) < nice) {
        return true;
    } else if (HEAP_ROOT_INDEX == parent) {
        if (next) {
            *next = HEAP_ROOT_INDEX;
        }

        return false;
    } else {
        grandparent = INDEX_PARENT(parent);
        assert(nice != HEAP_NICE(heap, grandparent));
        depth = binary_heap_node_depth(index);

        if (0x1u == UINT32_IDX_BIT(depth, 0)) {
            /*
             * index located at odd depth
             *     heap-ordered should be: parent < index < grandparent
             */
            up_idx = grandparent;
            down_idx = parent;
        } else {
            /*
             * index located at even depth
             *     heap-ordered should be: grandparent < index < parent
             */
            up_idx = parent;
            down_idx = grandparent;
        }

        return binary_heap_range_ordered_p(heap, up_idx, down_idx, nice, next);
    }
}


