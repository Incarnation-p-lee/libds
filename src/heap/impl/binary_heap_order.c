static inline bool
binary_heap_ordered_p(s_binary_heap_t *heap, void *heap_order)
{
    uint32 i;
    bool (*order)(s_binary_heap_t *, uint32, sint64, uint32 *);

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(heap_order));

    i = HEAP_INDEX_ROOT;
    order = heap_order;

    while (i <= INDEX_LAST(heap)) {
        if ((*order)(heap, i, ALIAS_NICE(heap, i), NULL) == false) {
            return false;
        }

        i++;
    }

    return true;
}

/*
 * Heap-order, minimal heap
 * If nice put into index position ordered
 *     Return true, or false.
 */
static inline bool
binary_heap_minimal_ordered_p(s_binary_heap_t *heap, uint32 index, sint64 nice,
    uint32 *tgt_index)
{
    uint32 small, parent, next;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    small = binary_heap_child_min_nice_index(heap, index);

    if (parent != HEAP_INDEX_INVALID && ALIAS_NICE(heap, parent) > nice) {
        next = parent;
    } else if (small != HEAP_INDEX_INVALID && ALIAS_NICE(heap, small) < nice) {
        next = small;
    } else {
        return true;
    }

    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

/*
 * Only for Build heap, as it need percolate down
 */
static inline bool
binary_heap_minimal_percolate_down(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    uint32 next, small;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    small = binary_heap_child_min_nice_index(heap, index);

    if (small != HEAP_INDEX_INVALID && ALIAS_NICE(heap, small) < nice) {
        next = small;

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
binary_heap_maximal_ordered_p(s_binary_heap_t *heap, uint32 index, sint64 nice,
    uint32 *tgt_index)
{
    uint32 big, parent, next;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    big = binary_heap_child_max_nice_index(heap, index);

    if (parent != HEAP_INDEX_INVALID && ALIAS_NICE(heap, parent) < nice) {
        next = parent;
    } else if (big != HEAP_INDEX_INVALID && ALIAS_NICE(heap, big) > nice) {
        next = big;
    } else {
        return true;
    }

    if (tgt_index) {
        *tgt_index = next;
    }

    return false;
}

/*
 * Only for Build heap, as it need percolate down
 */
static inline bool
binary_heap_maximal_percolate_down(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    uint32 next, big_child;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    big_child = binary_heap_child_max_nice_index(heap, index);

    if (big_child != HEAP_INDEX_INVALID && ALIAS_NICE(heap, big_child) > nice) {
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
binary_heap_min_max_up_ordered_p(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    uint32 gdp; /* grandparent */
    uint32 tgt, depth, parent;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    parent = INDEX_PARENT(index);
    gdp = INDEX_GD_PARENT(index);

    if (parent == HEAP_INDEX_INVALID) {
        return true;
    } else if (gdp == HEAP_INDEX_INVALID
        && ALIAS_NICE(heap, HEAP_INDEX_ROOT) <= nice) {
        return true;
    } else if (gdp == HEAP_INDEX_INVALID
        && ALIAS_NICE(heap, HEAP_INDEX_ROOT) > nice) {
        tgt = HEAP_INDEX_ROOT;
    } else {
        depth = binary_heap_depth(index);
        if (depth % 2) { /* max level */
            if (nice > ALIAS_NICE(heap, gdp)) {
                tgt = gdp;
            } else if (nice < ALIAS_NICE(heap, parent)) {
                tgt = parent;
            } else {
                return true;
            }
        } else { /* min level */
            if (nice < ALIAS_NICE(heap, gdp)) {
                tgt = gdp;
            } else if (nice > ALIAS_NICE(heap, parent)) {
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
binary_heap_min_max_up_unordered_p(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    return !binary_heap_min_max_up_ordered_p(heap, index, nice, tgt_index);
}

static inline bool
binary_heap_min_max_down_ordered_p(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    uint32 tgt, depth, child_index;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_depth(index);

    if (INDEX_LEFT(index) > INDEX_LAST(heap)) {
        return true;
    } else {
        if (depth % 2) { /* max level */
            child_index = binary_heap_gdp_randchild_max_nice_index(heap, index);

            if (nice < ALIAS_NICE(heap, child_index)) {
                tgt = child_index;
            } else {
                return true;
            }
        } else { /* min level */
            child_index = binary_heap_gdp_randchild_min_nice_index(heap, index);

            if (nice > ALIAS_NICE(heap, child_index)) {
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

static inline bool
binary_heap_min_max_down_unordered_p(s_binary_heap_t *heap, uint32 index,
    sint64 nice, uint32 *tgt_index)
{
    return !binary_heap_min_max_down_ordered_p(heap, index, nice, tgt_index);
}

