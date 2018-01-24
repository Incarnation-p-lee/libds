static inline bool
binary_heap_valid_ordered_func_ptr_p(void *func_ptr)
{
    void **i;

    assert_exit(NON_NULL_PTR_P(func_ptr));

    i = heap_order_func;

    while (i < heap_order_func + array_sizeof(heap_order_func)) {
        if (*i++ == func_ptr) {
            return true;
        }
    }

    return false;
}

static inline bool
binary_heap_depth_even_p(s_binary_heap_t *heap, uint32 index)
{
    uint32 depth;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    depth = binary_heap_depth(index);

    if ((depth & 0x1u) == 0u) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_depth_odd_p(s_binary_heap_t *heap, uint32 index)
{
    return !binary_heap_depth_even_p(heap, index);
}

static inline bool
min_max_heap_ordered_p(s_min_max_heap_t *heap)
{
    uint32 i;
    sint64 nice;
    s_binary_heap_t *alias;

    assert_exit(min_max_heap_legal_ip(heap));

    i = HEAP_INDEX_ROOT;
    alias = HEAP_ALIAS(heap);

    while (i <= INDEX_LAST(alias)) {
        nice = ALIAS_NICE(alias, i);

        if (binary_heap_min_max_up_unordered_p(alias, i, nice, NULL)) {
            return false;
        } else if (binary_heap_min_max_down_unordered_p(alias, i, nice, NULL)) {
            return false;
        }

        i++;
    }

    return true;
}

static inline sint32
leftist_heap_npl_default_i(s_leftist_heap_t *node)
{
    if (NULL_PTR_P(node)) {
        return -1;
    } else {
        return LEFTIST_NPL(node);
    }
}

static inline bool
leftist_heap_npl_optimize_validity_p(s_leftist_heap_t *node,
    sint32 expected)
{
    sint32 computed;

    computed = leftist_heap_npl_default_i(node);

    if (computed == expected) {
        return true;
    } else {
        return false;
    }
}

static inline bool
leftist_heap_node_heap_ordered_p(s_leftist_heap_t *node)
{
    if (leftist_heap_illegal_ip(node)) {
        return false;
    } else if (LEFTIST_LEFT(node) == NULL && LEFTIST_RIGHT(node) == NULL) {
        return true;
    } else if (LEFTIST_LEFT(node) != NULL
        && LEFTIST_NICE(node) > LEFTIST_NICE(LEFTIST_LEFT(node))) {
        return false;
    } else if (LEFTIST_RIGHT(node) != NULL
        && LEFTIST_NICE(node) > LEFTIST_NICE(LEFTIST_RIGHT(node))) {
        return false;
    } else {
        return true;
    }
}

static inline bool
leftist_heap_node_heap_unordered_p(s_leftist_heap_t *node)
{
    return !leftist_heap_node_heap_ordered_p(node);
}

static inline bool
leftist_heap_validity_p(s_leftist_heap_t *heap)
{
    if (NON_NULL_PTR_P(heap)) {
        return true;
    } else if (leftist_heap_node_heap_unordered_p(heap)) {
        return false;
    } else if (leftist_heap_node_npl_unordered_p(heap)) {
        return false;
    } else if (leftist_heap_validity_p(LEFTIST_LEFT(heap)) == false) {
        return false;
    } else if (leftist_heap_validity_p(LEFTIST_RIGHT(heap)) == false) {
        return false;
    } else {
        return true;
    }
}

