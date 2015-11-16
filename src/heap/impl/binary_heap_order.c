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

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

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
        assert(!binary_heap_nice_repeated_p(heap, parent, nice));
        assert(!binary_heap_nice_repeated_p(heap, small_child, nice));

        return true;
    }

HEAP_UNORDERED:
    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

/*
 * Heap-order, maximal heap
 * If nice put into index position ordered
 *     Return true, or false.
 */
static inline bool
binary_heap_maximal_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 big_child;
    uint32 parent;
    uint32 next;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    big_child = binary_heap_child_big_nice_index(heap, index);

    if (INDEX_INVALID != parent && HEAP_NICE(heap, parent) < nice) {
        next = parent;
        goto HEAP_UNORDERED;
    } else if (INDEX_INVALID != big_child
        && HEAP_NICE(heap, big_child) > nice) {
        next = big_child;
        goto HEAP_UNORDERED;
    } else {
        assert(!binary_heap_nice_repeated_p(heap, parent, nice));
        assert(!binary_heap_nice_repeated_p(heap, big_child, nice));

        return true;
    }

HEAP_UNORDERED:
    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

static inline bool
binary_heap_range_ordered_p(struct binary_heap *heap, uint32 up_index,
    uint32 down_index, sint64 nice, uint32 *tgt_index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, up_index));
    assert(binary_heap_index_legal_p(heap, down_index));
    assert(nice != HEAP_NICE(heap, up_index));
    assert(nice != HEAP_NICE(heap, down_index));

    if (HEAP_NICE(heap, down_index) > nice) {
        if (tgt_index) {
            *tgt_index = down_index;
        }

        return false;
    } else if (HEAP_NICE(heap, up_index) < nice) {
        if (tgt_index) {
            *tgt_index = up_index;
        }

        return false;
    } else {
        return true;
    }
}

static inline bool
binary_heap_min_max_root_ordered_p(struct binary_heap *heap,
    sint64 nice, uint32 *tgt_index)
{
    uint32 grandson;

    assert(binary_heap_structure_legal_p(heap));

    grandson = binary_heap_grandchild_small_nice_index(heap, INDEX_ROOT);

    if ((INDEX_INVALID == grandson)
        || (HEAP_NICE(heap, grandson) > nice)) {
        return true;
    } else if (tgt_index) {
        *tgt_index = grandson;
    }

    return false;
}

static inline bool
binary_heap_min_max_root_parent_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 parent;
    uint32 grandson;

    assert(binary_heap_structure_legal_p(heap));
    assert(INDEX_ROOT == INDEX_PARENT(index));

    parent = INDEX_ROOT;
    grandson = binary_heap_grandchild_big_nice_index(heap, index);

    assert(nice != HEAP_NICE(heap, parent));

    if ((INDEX_INVALID == grandson && HEAP_NICE(heap, parent) < nice)
        || (INDEX_INVALID != grandson && HEAP_NICE(heap, grandson) < nice)) {
        return true;
    } else if (INDEX_INVALID == grandson && tgt_index) {
        *tgt_index = INDEX_ROOT;
    } else if (tgt_index) {
        assert(nice != HEAP_NICE(heap, grandson));
        /*
         * min_max_heap percolate down at first
         */
        *tgt_index = grandson;
    }

    return false;
}

static inline bool
binary_heap_min_max_no_child_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 depth;
    uint32 parent;
    uint32 up_idx;
    uint32 down_idx;
    uint32 grandparent;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(INDEX_INVALID != INDEX_GD_PARENT(index));
    assert(!binary_heap_node_child_exist_p(heap, index));

    parent = INDEX_PARENT(index);
    grandparent = INDEX_GD_PARENT(index);
    depth = binary_heap_node_depth(index);

    assert(nice != HEAP_NICE(heap, parent));
    assert(nice != HEAP_NICE(heap, grandparent));

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

    return binary_heap_range_ordered_p(heap, up_idx, down_idx, nice, tgt_index);
}

static inline uint32
binary_heap_min_max_ordered_target_index(struct binary_heap *heap,
    uint32 grandparent, sint64 nice, uint32 grandson)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, grandparent));
    assert(binary_heap_index_legal_p(heap, grandson));

    /*
     * percolate to less distance node.
     */
    if (SINT64_ABS(HEAP_NICE(heap, grandparent) - nice)
        < SINT64_ABS(HEAP_NICE(heap, grandson) - nice)) {
        return grandparent;
    } else {
        return grandson;
    }
}

static inline bool
binary_heap_min_max_nice_ordered_p(struct binary_heap *heap, sint64 nice,
    uint32 up_index, uint32 down_index, uint32 grandson, uint32 depth)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, up_index));
    assert(binary_heap_index_legal_p(heap, down_index));
    assert(binary_heap_index_legal_p(heap, grandson));

    if (!binary_heap_range_ordered_p(heap, up_index, down_index, nice, NULL)) {
        return false;
    } else if (UINT32_IDX_BIT(depth, 0) && HEAP_NICE(heap, grandson) > nice) {
        return false;
    } else if (!UINT32_IDX_BIT(depth, 0) && HEAP_NICE(heap, grandson) < nice) {
        return false;
    } else {
        return true;
    }
}

/*
 * If nice put into index position ordered
 *     Return true, or false
 * min_max heap may lose the concept of percolate up and down
 */
static inline bool
binary_heap_min_max_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 depth;
    uint32 parent;
    uint32 grandparent;
    uint32 grandson;
    uint32 up_idx;
    uint32 down_idx;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    if (INDEX_ROOT == index) {
        return binary_heap_min_max_root_ordered_p(heap, nice, tgt_index);
    } else if (INDEX_ROOT == INDEX_PARENT(index)) {
        return binary_heap_min_max_root_parent_ordered_p(heap, index, nice,
            tgt_index);
    } else if (!binary_heap_node_child_exist_p(heap, index)) {
        return binary_heap_min_max_no_child_ordered_p(heap, index, nice,
            tgt_index);
    } else {
        depth = binary_heap_node_depth(index);
        parent = INDEX_PARENT(index);
        grandparent = INDEX_GD_PARENT(index);

        if (0x1u == UINT32_IDX_BIT(depth, 0)) {
            up_idx = grandparent;
            down_idx = parent;
            grandson = binary_heap_grandchild_big_nice_index(heap, index);
        } else {
            up_idx = parent;
            down_idx = grandparent;
            grandson = binary_heap_grandchild_small_nice_index(heap, index);
        }

        assert(HEAP_NICE(heap, grandson) > HEAP_NICE(heap, down_idx));
        assert(HEAP_NICE(heap, grandson) < HEAP_NICE(heap, up_idx));
        assert(HEAP_NICE(heap, grandson) != nice);

        if (binary_heap_min_max_nice_ordered_p(heap, nice, up_idx, down_idx,
            grandson, depth)) {
            return true;
        } else {
            *tgt_index = binary_heap_min_max_ordered_target_index(heap,
                grandparent, nice, grandson);
            assert(binary_heap_index_legal_p(heap, *tgt_index));
            return false;
        }
    }
}

