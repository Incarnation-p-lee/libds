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
    small_child = binary_heap_child_min_nice_index(heap, index);

    if (INDEX_INVALID != parent && HEAP_NICE(heap, parent) > nice) {
        next = parent;
        goto HEAP_UNORDERED;
    } else if (INDEX_INVALID != small_child
        && HEAP_NICE(heap, small_child) < nice) {
        next = small_child;
        goto HEAP_UNORDERED;
    } else {
        return true;
    }

HEAP_UNORDERED:
    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

/*
 * Only for Build heap, as it need percolate down
 */
static inline bool
binary_heap_minimal_percolate_down(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 next;
    uint32 small_child;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    small_child = binary_heap_child_min_nice_index(heap, index);

    if (INDEX_INVALID != small_child
        && HEAP_NICE(heap, small_child) < nice) {
        next = small_child;

        if (tgt_index) {
            *tgt_index = next;
        }

        return false;
    } else {
        return true;
    }
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
    big_child = binary_heap_child_max_nice_index(heap, index);

    if (INDEX_INVALID != parent && HEAP_NICE(heap, parent) < nice) {
        next = parent;
        goto HEAP_UNORDERED;
    } else if (INDEX_INVALID != big_child
        && HEAP_NICE(heap, big_child) > nice) {
        next = big_child;
        goto HEAP_UNORDERED;
    } else {
        return true;
    }

HEAP_UNORDERED:
    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

/*
 * Only for Build heap, as it need percolate down
 */
static inline bool
binary_heap_maximal_percolate_down(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 next;
    uint32 big_child;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    big_child = binary_heap_child_max_nice_index(heap, index);

    if (INDEX_INVALID != big_child
        && HEAP_NICE(heap, big_child) > nice) {
        next = big_child;

        if (tgt_index) {
            *tgt_index = next;
        }

        return false;
    } else {
        return true;
    }
}

static inline bool
binary_heap_range_ordered_p(struct binary_heap *heap, uint32 up_index,
    uint32 down_index, sint64 nice, uint32 *tgt_index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, up_index));
    assert(binary_heap_index_legal_p(heap, down_index));

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

    grandson = binary_heap_grandchild_min_nice_index(heap, INDEX_ROOT);

    if ((INDEX_INVALID == grandson)
        || (HEAP_NICE(heap, grandson) >= nice)) {
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
    grandson = binary_heap_grandchild_max_nice_index(heap, index);

    if ((INDEX_INVALID == grandson && HEAP_NICE(heap, parent) <= nice)
        || (INDEX_INVALID != grandson && HEAP_NICE(heap, grandson) <= nice)) {
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
    uint32 up_index;
    uint32 down_index;
    uint32 grandparent;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(INDEX_INVALID != INDEX_GD_PARENT(index));
    assert(!binary_heap_child_exist_p(heap, index));

    parent = INDEX_PARENT(index);
    grandparent = INDEX_GD_PARENT(index);
    depth = binary_heap_depth(index);

    if (0x1u == UINT32_IDX_BIT(depth, 0)) {
        /*
         * index located at odd depth
         *     heap-ordered should be: parent < index < grandparent
         */
        up_index = grandparent;
        down_index = parent;
    } else {
        /*
         * index located at even depth
         *     heap-ordered should be: grandparent < index < parent
         */
        up_index = parent;
        down_index = grandparent;
    }

    return binary_heap_range_ordered_p(heap, up_index, down_index, nice, tgt_index);
}

static inline void
binary_heap_min_max_ordered_target_index(struct binary_heap *heap, uint32 index,
    sint64 nice, uint32 grandson, uint32 *tgt_index)
{
    uint32 grandparent;
    sint64 gap_up;
    sint64 gap_down;

    assert(!complain_null_pointer_p(tgt_index));
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    grandparent = INDEX_GD_PARENT(index);
    gap_up = SINT64_ABS(HEAP_NICE(heap, grandparent) - nice);
    gap_down = SINT64_ABS(HEAP_NICE(heap, grandson) - nice);

    if (gap_up > gap_down) {
        *tgt_index = grandson;
    } else {
        *tgt_index = grandparent;
    }
}

static inline bool
binary_heap_min_max_ordered_p_internal(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 depth;
    uint32 up_index;
    uint32 down_index;
    uint32 grandson;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_depth(index);

    if (0x1u == UINT32_IDX_BIT(depth, 0)) {
        up_index = INDEX_GD_PARENT(index);
        down_index = INDEX_PARENT(index);
        grandson = binary_heap_grandchild_max_nice_index(heap, index);
    } else {
        up_index = INDEX_PARENT(index);
        down_index = INDEX_GD_PARENT(index);
        grandson = binary_heap_grandchild_min_nice_index(heap, index);
    }

    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_index_legal_p(heap, up_index));
    assert(binary_heap_index_legal_p(heap, down_index));
    assert(HEAP_NICE(heap, grandson) >= HEAP_NICE(heap, down_index));
    assert(HEAP_NICE(heap, grandson) <= HEAP_NICE(heap, up_index));

    if (!binary_heap_range_ordered_p(heap, up_index, down_index, nice, NULL)) {
        if (tgt_index) {
             binary_heap_min_max_ordered_target_index(heap,
                index, nice, grandson, tgt_index);
        }

        return false;
    } else if (UINT32_IDX_BIT(depth, 0) && HEAP_NICE(heap, grandson) <= nice) {
        return true;
    } else if (!UINT32_IDX_BIT(depth, 0) && HEAP_NICE(heap, grandson) >= nice) {
        return true;
    } else if (tgt_index) {
        *tgt_index = grandson;
    }

    return false;
}

static inline bool
binary_heap_min_max_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 tgt;
    uint32 depth;
    uint32 parent;
    uint32 grandparent;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    grandparent = INDEX_GD_PARENT(index);

    if (INDEX_INVALID == parent) {
        return true;
    } else if (INDEX_INVALID == grandparent
        && HEAP_NICE(heap, INDEX_ROOT) <= nice) {
        return true;
    } else if (INDEX_INVALID == grandparent
        && HEAP_NICE(heap, INDEX_ROOT) > nice) {
        tgt = INDEX_ROOT;
    } else {
        depth = binary_heap_depth(index);
        if (depth % 2) {
            // max level;
            if (nice > HEAP_NICE(heap, grandparent)) {
                tgt = grandparent;
            } else if (nice < HEAP_NICE(heap, parent)) {
                tgt = parent;
            } else {
                return true;
            }
        } else {
            // min level;
            if (nice < HEAP_NICE(heap, grandparent)) {
                tgt = grandparent;
            } else if (nice > HEAP_NICE(heap, parent)) {
                tgt = parent;
            } else {
                return true;
            }
        }
    }

    if (tgt_index) {
        *tgt_index = tgt;
    }

    return false;
}

static inline bool
binary_heap_min_max_down_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 tgt;
    uint32 depth;
    uint32 child_index;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_depth(index);

    if (INDEX_L_CHILD(index) > INDEX_LAST(heap)) {
        return true;
    } else {
        if (depth % 2) {
            // max level
            child_index = binary_heap_grandchild_max_nice_index(heap, index);
            if (nice < HEAP_NICE(heap, child_index)) {
                tgt = child_index;
            } else {
                return true;
            }
        } else {
            // min level
            child_index = binary_heap_grandchild_min_nice_index(heap, index);
            if (nice > HEAP_NICE(heap, child_index)) {
                tgt = child_index;
            } else {
                return true;
            }
        }
    }

    if (tgt_index) {
        *tgt_index = tgt;
    }

    return false;
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
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    if (INDEX_ROOT == index) {
        return binary_heap_min_max_root_ordered_p(heap, nice, tgt_index);
    } else if (INDEX_ROOT == INDEX_PARENT(index)) {
        return binary_heap_min_max_root_parent_ordered_p(heap, index, nice,
            tgt_index);
    } else if (!binary_heap_child_exist_p(heap, index)) {
        return binary_heap_min_max_no_child_ordered_p(heap, index, nice,
            tgt_index);
    } else {
        return binary_heap_min_max_ordered_p_internal(heap, index, nice,
            tgt_index);
    }
}

