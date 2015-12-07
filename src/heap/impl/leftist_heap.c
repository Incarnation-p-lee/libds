static inline struct leftist_heap *
leftist_heap_create_internal(void *val, sint32 npl)
{
    struct leftist_heap *heap;

    assert(NPL_NULL != npl);

    heap = malloc_ds(sizeof(*heap));

    if (!complain_no_memory_p(heap)) {
        heap->alias.chain.link = malloc_ds(sizeof(*heap->alias.chain.link));

        if (!complain_no_memory_p(heap->alias.chain.link)) {
            heap->alias.left = NULL;
            heap->alias.right = NULL;
            heap->npl = npl;

            doubly_linked_list_initial(heap->alias.chain.link);
            doubly_linked_list_node_val_set(heap->alias.chain.link, val);
        }
    }

    return heap;
}

struct leftist_heap *
leftist_heap_create(void)
{
    return leftist_heap_create_internal(NULL, 0);
}

struct leftist_heap *
leftist_heap_node_create(void *val, sint32 nlp)
{
    return leftist_heap_create_internal(val, nlp);
}

static inline void
leftist_heap_node_destroy(struct leftist_heap *node)
{
    assert(NULL != node);
    assert(NULL == leftist_heap_left(node));
    assert(NULL == leftist_heap_right(node));

    doubly_linked_list_destroy(&node->alias.chain.link);
    free_ds(node);
}

static inline void
leftist_heap_destroy_internal(struct leftist_heap *heap)
{
    if (heap) {
        leftist_heap_destroy_internal(leftist_heap_left(heap));
        leftist_heap_destroy_internal(leftist_heap_left(heap));

        heap->alias.left = NULL;
        heap->alias.right = NULL;
        leftist_heap_node_destroy(heap);
    }
}

void
leftist_heap_destroy(struct leftist_heap **heap)
{
    if (!complain_null_pointer_p(heap) && !complain_null_pointer_p(*heap)) {
        leftist_heap_destroy_internal(*heap);
        *heap = NULL;
    }
}

struct leftist_heap *
leftist_heap_ptr_binary_to_leftist(struct binary_search_tree *node)
{
    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        return CONTAINER_OF(node, struct leftist_heap, alias);
    }
}

struct leftist_heap *
leftist_heap_node_find(struct leftist_heap *heap, sint64 nice)
{
    struct binary_search_tree *found;

    if (complain_null_pointer_p(heap)) {
        return false;
    } else {
        found = binary_search_tree_node_find(&heap->alias, nice);
        return leftist_heap_ptr_to_leftist(found);
    }
}

static inline struct doubly_linked_list *
leftist_heap_node_find_min_internal(struct leftist_heap *heap)
{
    assert(leftist_heap_structure_legal_p(heap));

    return heap->alias.chain.link;
}

struct doubly_linked_list *
leftist_heap_node_find_min(struct leftist_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        return leftist_heap_node_find_min_internal(heap);
    }
}

void
leftist_heap_node_insert(struct leftist_heap *heap, void *val, sint64 nice)
{
    if (complain_null_pointer_p(heap)) {
        return;
    } else {
        // leftist_heap_node_insert_internal(heap, val, nice);
        return;
    }
}

static inline void
leftist_heap_node_npl_update(struct leftist_heap *node)
{
    sint32 l_npl;
    sint32 r_npl;

    assert(leftist_heap_structure_legal_p(node));

    l_npl = leftist_heap_npl_internal(leftist_heap_left(node));
    r_npl = leftist_heap_npl_internal(leftist_heap_right(node));

    leftist_heap_npl_set(node, MIN_S(l_npl, r_npl) + 1);
}

static inline bool
leftist_heap_node_ordered_p(struct leftist_heap *node)
{
    assert(NULL != node);

    if (leftist_heap_npl_internal(leftist_heap_left(node))
        >= leftist_heap_npl_internal(leftist_heap_right(node))) {
        return true;
    } else {
        return false;
    }
}

static inline void
leftist_heap_node_child_swap(struct leftist_heap *node)
{
    struct binary_search_tree *tmp;

    assert(NULL != node);

    tmp = node->alias.left;
    node->alias.left = node->alias.right;
    node->alias.right = tmp;
}

static inline struct leftist_heap *
leftist_heap_merge_from_right(struct leftist_heap *heap,
    struct leftist_heap *merge)
{
    struct leftist_heap *tmp;
    struct leftist_heap *touched;
    struct leftist_heap *retval;

    assert(leftist_heap_structure_legal_p(heap));
    assert(leftist_heap_structure_legal_p(merge));

    retval = leftist_heap_node_nice(heap) > leftist_heap_node_nice(merge) ?
        merge : heap;

    while (heap && merge) {
        if (leftist_heap_node_nice(heap) < leftist_heap_node_nice(merge)) {
            touched = heap;
            tmp = leftist_heap_right(heap);
            heap->alias.right = &merge->alias;
            heap = tmp;
        } else {
            touched = merge;
            tmp = leftist_heap_right(merge);
            merge->alias.right = &heap->alias;
            merge = tmp;
        }

        leftist_heap_node_npl_update(touched);
    }

    return retval;
}

static inline void
leftist_heap_reorder_from_right(struct leftist_heap *heap)
{
    if (heap) {
        leftist_heap_reorder_from_right(leftist_heap_right(heap));
        if (!leftist_heap_node_ordered_p(heap)) {
            leftist_heap_node_child_swap(heap);
        }
    }
}

static inline struct leftist_heap *
leftist_heap_merge_internal(struct leftist_heap *heap,
    struct leftist_heap *merge)
{
    struct leftist_heap *tmp;
    struct leftist_heap *right_h;
    struct leftist_heap *right_m;
    struct leftist_heap *retval;

    assert(NULL != heap);
    assert(NULL != merge);

    right_h = leftist_heap_right(heap);
    right_m = leftist_heap_right(merge);
    tmp = leftist_heap_merge_from_right(right_h, right_m);

    if (leftist_heap_node_nice(heap) < leftist_heap_node_nice(merge)) {
        heap->alias.right = &merge->alias;
        merge->alias.right = &tmp->alias;
        retval = heap;
    } else {
        merge->alias.right = &heap->alias;
        heap->alias.right = &tmp->alias;
        retval = merge;
    }

    leftist_heap_reorder_from_right(retval);

    return retval;
}

struct leftist_heap *
leftist_heap_merge(struct leftist_heap *heap, struct leftist_heap *merge)
{
    if (NULL == heap) {
        return merge;
    } else if (NULL != merge) {
        return leftist_heap_merge_internal(heap, merge);
    } else {
        return NULL;
    }
}

static inline struct leftist_heap *
leftist_heap_ptr_to_leftist(struct binary_search_tree *node)
{
    struct leftist_heap *heap;

    leftist_heap_ptr_binary_to_leftist_optimize(node, heap);
    assert(leftist_heap_ptr_to_avl_optimize_validity_p(node, heap));

    return heap;
}

static inline struct leftist_heap *
leftist_heap_left(struct leftist_heap *node)
{
    struct leftist_heap *left;

    assert(NULL != node);
    leftist_heap_left_optimize(node, left);
    assert(leftist_heap_left_optimize_validity_p(node, left));

    return left;
}

static inline struct leftist_heap *
leftist_heap_right(struct leftist_heap *node)
{
    struct leftist_heap *right;

    assert(NULL != node);
    leftist_heap_right_optimize(node, right);
    assert(leftist_heap_right_optimize_validity_p(node, right));

    return right;
}

static inline sint32
leftist_heap_npl_internal(struct leftist_heap *node)
{
    sint32 npl;

    leftist_heap_npl_optimize(node, npl);
    assert(leftist_heap_npl_optimize_validity_p(node, npl));

    return npl;
}

