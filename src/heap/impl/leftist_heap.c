static inline struct leftist_heap *
leftist_heap_create_internal(void *val, sint32 npl, sint64 nice)
{
    struct leftist_heap *heap;

    assert(NPL_NULL != npl);

    heap = malloc_ds(sizeof(*heap));

    if (!complain_no_memory_p(heap)) {
        heap->npl = npl;
        heap->data.nice = nice;
        heap->data.val = val;

        heap->left = NULL;
        heap->right = NULL;
    }

    return heap;
}

struct leftist_heap *
leftist_heap_create(void)
{
    return leftist_heap_create_internal(NULL, 0, 0);
}

struct leftist_heap *
leftist_heap_node_create(void *val, sint32 nlp, sint64 nice)
{
    return leftist_heap_create_internal(val, nlp, nice);
}

static inline void
leftist_heap_destroy_internal(struct leftist_heap *heap)
{
    if (heap) {
        leftist_heap_destroy_internal(leftist_heap_left(heap));
        leftist_heap_destroy_internal(leftist_heap_right(heap));

        free_ds(heap);
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

static inline void *
leftist_heap_node_get_min_internal(struct leftist_heap *heap)
{
    assert(leftist_heap_structure_legal_p(heap));

    return heap->data.val;
}

void *
leftist_heap_node_get_min(struct leftist_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        return leftist_heap_node_get_min_internal(heap);
    }
}

/*
 * _RETURN_ the new leftist heap.
 */
struct leftist_heap *
leftist_heap_insert(struct leftist_heap *heap, void *val, sint64 nice)
{
    struct leftist_heap *node;

    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        node = leftist_heap_create_internal(val, 0, nice);
        return leftist_heap_merge_internal(heap, node);
    }
}

static inline void
leftist_heap_node_npl_update(struct leftist_heap *node)
{
    sint32 npl_l;
    sint32 npl_r;

    assert(leftist_heap_structure_legal_p(node));

    npl_l = leftist_heap_npl_internal(node->left);
    npl_r = leftist_heap_npl_internal(node->right);

    leftist_heap_npl_set(node, MIN_S(npl_l, npl_r) + 1);
}

static inline bool
leftist_heap_node_npl_ordered_p(struct leftist_heap *node)
{
    assert(NULL != node);

    if (leftist_heap_npl_internal(node->left)
        >= leftist_heap_npl_internal(node->right)) {
        return true;
    } else {
        return false;
    }
}

static inline void
leftist_heap_node_child_swap(struct leftist_heap *node)
{
    struct leftist_heap *tmp;

    assert(NULL != node);

    tmp = node->left;
    node->left = node->right;
    node->right = tmp;
}

static inline struct leftist_heap *
leftist_heap_merge_from_right(struct leftist_heap *heap,
    struct leftist_heap *merge)
{
    struct leftist_heap *retval;
    struct leftist_heap *tmp;
    struct leftist_heap **major;
    struct leftist_heap *minor;

    assert(leftist_heap_structure_legal_p(heap));
    assert(leftist_heap_structure_legal_p(merge));

    if (leftist_heap_nice(heap) <= leftist_heap_nice(merge)) {
        retval = heap;
        major = &heap;
        minor = merge;
    } else {
        retval = merge;
        major = &merge;
        minor = heap;
    }

    while (minor) {
        if (!*major) {
            *major = minor;
            break;
        } else if (leftist_heap_nice(*major) <= leftist_heap_nice(minor)) {
            major = &(*major)->right;
        } else {
            tmp = *major;
            *major = minor;
            major = &minor->right;
            minor = tmp;
        }
    }

    return retval;
}

static inline void
leftist_heap_reorder_from_right(struct leftist_heap *heap)
{
    if (heap) {
        leftist_heap_reorder_from_right(leftist_heap_right(heap));
        leftist_heap_node_npl_update(heap);
        if (!leftist_heap_node_npl_ordered_p(heap)) {
            leftist_heap_node_child_swap(heap);
        }
    }
}

static inline struct leftist_heap *
leftist_heap_merge_internal(struct leftist_heap *heap,
    struct leftist_heap *merge)
{
    struct leftist_heap *retval;

    assert(NULL != heap);
    assert(NULL != merge);
    assert(leftist_heap_validity_p(heap));
    assert(leftist_heap_validity_p(merge));

    retval = leftist_heap_merge_from_right(heap, merge);
    leftist_heap_reorder_from_right(retval);

    assert(leftist_heap_validity_p(retval));

    return retval;
}

/*
 * _RETURN_ the new leftist heap.
 */
struct leftist_heap *
leftist_heap_merge(struct leftist_heap *heap, struct leftist_heap *merge)
{
    if (complain_null_pointer_p(heap) && complain_null_pointer_p(merge)) {
        return NULL;
    } else if (NULL == heap) {
        return merge;
    } else {
        return leftist_heap_merge_internal(heap, merge);
    }
}

/*
 * _RETURN_ the removed leftist heap node.
 */
struct leftist_heap *
leftist_heap_remove_min(struct leftist_heap **heap)
{
    struct leftist_heap *removed;
    struct leftist_heap *left;
    struct leftist_heap *right;

    if (complain_null_pointer_p(heap) || complain_null_pointer_p(*heap)) {
        return NULL;
    } else {
        removed = *heap;
        left = removed->left;
        right = removed->right;

        *heap = leftist_heap_merge_internal(left, right);

        removed->left = NULL;
        removed->right = NULL;
        return removed;
    }
}

static inline sint32
leftist_heap_npl_internal(struct leftist_heap *node)
{
    sint32 npl;

    leftist_heap_npl_optimize(node, npl);
    assert(leftist_heap_npl_optimize_validity_p(node, npl));

    return npl;
}

