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
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    return !binary_heap_depth_even_p(heap, index);
}

static inline bool
binary_heap_ordered_p(s_binary_heap_t *heap, void *heap_order)
{
    uint32 index;
    bool (*order)(s_binary_heap_t *, uint32, sint64, uint32 *);

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(heap_order));

    index = INDEX_ROOT;
    order = heap_order;

    while (index <= INDEX_LAST(heap)) {
        if ((*order)(heap, index, ALIAS_NICE(heap, index), NULL) == false) {
            return false;
        }

        index++;
    }

    return true;
}

static inline bool
minimal_heap_ordered_p(s_minimal_heap_t *heap)
{
    s_binary_heap_t *alias;

    assert_exit(minimal_heap_legal_ip(heap));

    alias = HEAP_ALIAS(heap);

    return binary_heap_ordered_p(alias, &binary_heap_minimal_ordered_p);
}

static inline bool
maximal_heap_ordered_p(s_maximal_heap_t *heap)
{
    s_binary_heap_t *alias;

    assert_exit(maximal_heap_legal_ip(heap));

    alias = HEAP_ALIAS(heap);

    return binary_heap_ordered_p(alias, &binary_heap_maximal_ordered_p);
}

static inline bool
min_max_heap_ordered_p(s_min_max_heap_t *heap)
{
    sint64 nice;
    uint32 index;
    s_binary_heap_t *alias;

    assert_exit(NON_NULL_PTR_P(heap));
    assert_exit(NON_NULL_PTR_P(heap->alias));

    index = INDEX_ROOT;
    alias = heap->alias;

    while (index <= INDEX_LAST(alias)) {
        nice = ALIAS_NICE(alias, index);

        if (!binary_heap_min_max_up_ordered_p(alias, index, nice, NULL)) {
            return false;
        } else if (!binary_heap_min_max_down_ordered_p(alias, index, nice,
            NULL)) {
            return false;
        }

        index++;
    }

    return true;
}

static inline bool
leftist_heap_structure_legal_p(s_leftist_heap_t *heap)
{
    if (NULL_PTR_P(heap)) {
        return false;
    } else if (NULL != heap->left && heap->left == heap->right) {
        return false;
    } else {
        return true;
    }
}

static inline sint32
leftist_heap_npl_internal_default(struct leftist_heap *node)
{
    if (!node) {
        return -1;
    } else {
        return node->npl;
    }
}

static inline bool
leftist_heap_npl_optimize_validity_p(struct leftist_heap *node,
    sint32 expected)
{
    sint32 computed;

    computed = leftist_heap_npl_internal_default(node);

    if (computed == expected) {
        return true;
    } else {
        dp_printf("[32mexpected[0m: %d\n", expected);
        dp_printf("[31mcomputed[0m: %d\n", computed);
        return false;
    }
}

static inline bool
leftist_heap_node_heap_ordered_p(struct leftist_heap *node)
{
    if (!node) {
        return true;
    } else if (NULL == node->left && NULL == node->right) {
        return true;
    } else if (NULL != node->left
        && node->data.nice > node->left->data.nice) {
        return false;
    } else if (NULL != node->right
        && node->data.nice > node->right->data.nice) {
        return false;
    } else {
        return true;
    }
}

static inline bool
leftist_heap_validity_p(struct leftist_heap *heap)
{
    if (!heap) {
        return true;
    } else if (!leftist_heap_node_heap_ordered_p(heap)) {
        return false;
    } else if (!leftist_heap_node_npl_ordered_p(heap)) {
        return false;
    } else if (!leftist_heap_validity_p(heap->left)) {
        return false;
    } else if (!leftist_heap_validity_p(heap->right)) {
        return false;
    } else {
        return true;
    }
}

