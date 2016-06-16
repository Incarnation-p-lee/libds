static inline struct leftist_heap *
leftist_heap_create_internal(void *val, sint32 npl, sint64 nice)
{
    struct leftist_heap *heap;

    dp_assert(NPL_NULL != npl);

    heap = memory_cache_allocate(sizeof(*heap));

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
leftist_heap_left(struct leftist_heap *heap)
{
    return heap->left;
}

struct leftist_heap *
leftist_heap_right(struct leftist_heap *heap)
{
    return heap->right;
}

void
leftist_heap_nice_set(struct leftist_heap *heap, sint64 nice)
{
    heap->data.nice = nice;
}

void
leftist_heap_npl_set(struct leftist_heap *heap, sint32 npl)
{
    heap->npl = npl;
}

sint64
leftist_heap_nice(struct leftist_heap *heap)
{
    return heap->data.nice;
}

sint32
leftist_heap_npl(struct leftist_heap *heap)
{
    return heap->npl;
}

void *
leftist_heap_val(struct leftist_heap *heap)
{
    return heap->data.val;
}

void
leftist_heap_val_set(struct leftist_heap *heap, void *val)
{
    heap->data.val = val;
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
        leftist_heap_destroy_internal(heap->left);
        leftist_heap_destroy_internal(heap->right);

        memory_cache_free(heap);
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
leftist_heap_get_min_internal(struct leftist_heap *heap)
{
    dp_assert(leftist_heap_structure_legal_p(heap));

    return heap->data.val;
}

void *
leftist_heap_get_min(struct leftist_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        return leftist_heap_get_min_internal(heap);
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

    dp_assert(leftist_heap_structure_legal_p(node));

    npl_l = leftist_heap_npl_internal(node->left);
    npl_r = leftist_heap_npl_internal(node->right);

    node->npl = MIN_S32(npl_l, npl_r) + 1;
}

static inline bool
leftist_heap_node_npl_ordered_p(struct leftist_heap *node)
{
    dp_assert(NULL != node);

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

    dp_assert(NULL != node);

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

    dp_assert(leftist_heap_structure_legal_p(heap));
    dp_assert(leftist_heap_structure_legal_p(merge));

    if (heap->data.nice <= merge->data.nice) {
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
        } else if ((*major)->data.nice <= minor->data.nice) {
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
        leftist_heap_reorder_from_right(heap->right);
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

    dp_assert(NULL != heap);
    dp_assert(NULL != merge);
    dp_assert(leftist_heap_validity_p(heap));
    dp_assert(leftist_heap_validity_p(merge));

    retval = leftist_heap_merge_from_right(heap, merge);
    leftist_heap_reorder_from_right(retval);

    dp_assert(leftist_heap_validity_p(retval));

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
    } else if (NULL == merge) {
        return heap;
    } else {
        return leftist_heap_merge_internal(heap, merge);
    }
}

static inline struct leftist_heap *
leftist_heap_remove_min_internal(struct leftist_heap **heap)
{
    struct leftist_heap *removed;
    struct leftist_heap *left;
    struct leftist_heap *right;

    dp_assert(NULL != heap);
    dp_assert(leftist_heap_structure_legal_p(*heap));

    removed = *heap;
    left = removed->left;
    right = removed->right;

    if (NULL == left) {
        *heap = right;
    } else if (NULL == right) {
        *heap = left;
    } else {
        *heap = leftist_heap_merge_internal(left, right);
    }

    removed->left = NULL;
    removed->right = NULL;
    return removed;
}

/*
 * _RETURN_ the removed leftist heap node.
 */
struct leftist_heap *
leftist_heap_remove_min(struct leftist_heap **heap)
{
    if (complain_null_pointer_p(heap) || complain_null_pointer_p(*heap)) {
        return NULL;
    } else {
        return leftist_heap_remove_min_internal(heap);
    }
}

void
leftist_heap_remove_min_and_destroy(struct leftist_heap **heap)
{
    if (!complain_null_pointer_p(heap) && !complain_null_pointer_p(*heap)) {
        memory_cache_free(leftist_heap_remove_min_internal(heap));
    }
}

static inline sint32
leftist_heap_npl_internal(struct leftist_heap *node)
{
    sint32 npl;

    leftist_heap_npl_optimize(node, npl);
    dp_assert(leftist_heap_npl_optimize_validity_p(node, npl));

    return npl;
}

