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

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

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

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

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

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

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

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

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
binary_heap_min_max_up_ordered_p(struct binary_heap *heap,
    uint32 index, sint64 nice, uint32 *tgt_index)
{
    uint32 tgt;
    uint32 depth;
    uint32 parent;
    uint32 gdp_randparent;

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    gdp_randparent = INDEX_GD_PARENT(index);

    if (INDEX_INVALID == parent) {
        return true;
    } else if (INDEX_INVALID == gdp_randparent
        && HEAP_NICE(heap, INDEX_ROOT) <= nice) {
        return true;
    } else if (INDEX_INVALID == gdp_randparent
        && HEAP_NICE(heap, INDEX_ROOT) > nice) {
        tgt = INDEX_ROOT;
    } else {
        depth = binary_heap_depth(index);
        if (depth % 2) {
            // max level;
            if (nice > HEAP_NICE(heap, gdp_randparent)) {
                tgt = gdp_randparent;
            } else if (nice < HEAP_NICE(heap, parent)) {
                tgt = parent;
            } else {
                return true;
            }
        } else {
            // min level;
            if (nice < HEAP_NICE(heap, gdp_randparent)) {
                tgt = gdp_randparent;
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

    assert_exit(binary_heap_structure_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_depth(index);

    if (INDEX_L_CHILD(index) > INDEX_LAST(heap)) {
        return true;
    } else {
        if (depth % 2) {
            // max level
            child_index = binary_heap_gdp_randchild_max_nice_index(heap, index);
            if (nice < HEAP_NICE(heap, child_index)) {
                tgt = child_index;
            } else {
                return true;
            }
        } else {
            // min level
            child_index = binary_heap_gdp_randchild_min_nice_index(heap, index);
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

