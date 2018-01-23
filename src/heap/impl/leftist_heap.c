s_leftist_heap_t *
leftist_heap_left(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return LEFTIST_LEFT(heap);
    }
}

s_leftist_heap_t *
leftist_heap_right(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return LEFTIST_RIGHT(heap);
    }
}

void
leftist_heap_nice_set(s_leftist_heap_t *heap, sint64 nice)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return;
    } else {
        DATA_NICE(LEFTIST_DATA(heap)) = nice;
    }
}

void
leftist_heap_npl_set(s_leftist_heap_t *heap, sint32 npl)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return;
    } else {
        LEFTIST_NPL(heap) = npl;
    }
}

sint64
leftist_heap_nice(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return HEAP_NICE_INVALID;
    } else {
        return DATA_NICE(LEFTIST_DATA(heap));
    }
}

sint32
leftist_heap_npl(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return NPL_INVALID;
    } else {
        return LEFTIST_NPL(heap);
    }
}

void *
leftist_heap_val(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return DATA_VAL(LEFTIST_DATA(heap));
    }
}

void
leftist_heap_val_set(s_leftist_heap_t *heap, void *val)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return;
    } else {
        DATA_VAL(LEFTIST_DATA(heap)) = val;
    }
}

static inline bool
leftist_heap_legal_ip(s_leftist_heap_t *heap)
{
    if (NULL_PTR_P(heap)) {
        return false;
    } else if (LEFTIST_LEFT(heap) != NULL
        && LEFTIST_LEFT(heap) == LEFTIST_RIGHT(heap)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
leftist_heap_illegal_ip(s_leftist_heap_t *heap)
{
    return !leftist_heap_legal_ip(heap);
}

bool
leftist_heap_legal_p(s_leftist_heap_t *heap)
{
    return leftist_heap_legal_ip(heap);
}

bool
leftist_heap_illegal_p(s_leftist_heap_t *heap)
{
    return leftist_heap_illegal_ip(heap);
}

static inline s_leftist_heap_t *
leftist_heap_create_i(void *val, sint32 npl, sint64 nice)
{
    s_heap_data_t *data;
    s_leftist_heap_t *heap;

    assert_exit(npl != NPL_NULL);

    heap = memory_cache_allocate(sizeof(*heap));
    data = LEFTIST_DATA(heap);

    LEFTIST_NPL(heap) = npl;
    LEFTIST_LEFT(heap) = LEFTIST_RIGHT(heap) = NULL;

    DATA_VAL(data) = val;
    DATA_NICE(data) = nice;

    return heap;
}

s_leftist_heap_t *
leftist_heap_create(void)
{
    return leftist_heap_create_i(NULL, 0, 0);
}

s_leftist_heap_t *
leftist_heap_node_create(void *val, sint32 nlp, sint64 nice)
{
    return leftist_heap_create_i(val, nlp, nice);
}

static inline void
leftist_heap_node_destroy(s_leftist_heap_t *heap)
{
    assert_exit(leftist_heap_legal_ip(heap));

    memory_cache_free(heap);
}

static inline void
leftist_heap_destroy_i(s_leftist_heap_t *heap)
{
    s_array_queue_t *queue;
    s_leftist_heap_t *node;

    assert_exit(leftist_heap_legal_ip(heap));

    queue = array_queue_create();
    array_queue_enter(queue, heap);

    while (!array_queue_empty_p(queue)) {
        node = array_queue_leave(queue);

        if (LEFTIST_LEFT(node) != NULL) {
            array_queue_enter(queue, LEFTIST_LEFT(node));
        }

        if (LEFTIST_RIGHT(node) != NULL) {
            array_queue_enter(queue, LEFTIST_RIGHT(node));
        }

        leftist_heap_node_destroy(node);
    }

    array_queue_destroy(&queue);
}

void
leftist_heap_destroy(s_leftist_heap_t **heap)
{
    if (NULL_PTR_P(heap)) {
        return;
    } else if (LEFTIST_HEAP_ILLEGAL_P(*heap)) {
        return;
    } else {
        leftist_heap_destroy_i(*heap);

        *heap = NULL;
    }
}

static inline void *
leftist_heap_get_min_i(s_leftist_heap_t *heap)
{
    assert_exit(leftist_heap_legal_p(heap));

    return DATA_VAL(LEFTIST_DATA(heap));
}

void *
leftist_heap_get_min(s_leftist_heap_t *heap)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return leftist_heap_get_min_i(heap);
    }
}

/*
 * _RETURN_ the new leftist heap.
 */
s_leftist_heap_t *
leftist_heap_insert(s_leftist_heap_t *heap, void *val, sint64 nice)
{
    s_leftist_heap_t *node;

    if (LEFTIST_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        node = leftist_heap_create_i(val, 0, nice);

        return leftist_heap_merge_i(heap, node);
    }
}

static inline void
leftist_heap_node_npl_update(s_leftist_heap_t *node)
{
    sint32 left;
    sint32 right;

    assert_exit(leftist_heap_legal_p(node));

    left = leftist_heap_npl_i(LEFTIST_LEFT(node));
    right = leftist_heap_npl_i(LEFTIST_RIGHT(node));

    LEFTIST_NPL(node) = MIN_S32(left, right) + 1;
}

static inline bool
leftist_heap_node_npl_ordered_p(s_leftist_heap_t *node)
{
    s_leftist_heap_t *left, *right;

    assert_exit(NON_NULL_PTR_P(node));

    left = LEFTIST_LEFT(node);
    right = LEFTIST_RIGHT(node);

    if (leftist_heap_npl_i(left) >= leftist_heap_npl_i(right)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
leftist_heap_node_npl_unordered_p(s_leftist_heap_t *node)
{
    return !leftist_heap_node_npl_ordered_p(node);
}

static inline void
leftist_heap_node_child_swap(s_leftist_heap_t *node)
{
    s_leftist_heap_t *tmp;

    assert_exit(leftist_heap_legal_ip(node));

    tmp = LEFTIST_LEFT(node);
    LEFTIST_LEFT(node) = LEFTIST_RIGHT(node);
    LEFTIST_RIGHT(node) = tmp;
}

static inline s_leftist_heap_t *
leftist_heap_merge_from_right(s_leftist_heap_t *heap, s_leftist_heap_t *merge)
{
    s_leftist_heap_t **major;
    s_leftist_heap_t *retval, *tmp, *minor;

    assert_exit(leftist_heap_legal_ip(heap));
    assert_exit(leftist_heap_legal_ip(merge));

    if (DATA_NICE(LEFTIST_DATA(heap)) <= DATA_NICE(LEFTIST_DATA(merge))) {
        retval = heap;
        major = &heap;
        minor = merge;
    } else {
        retval = merge;
        major = &merge;
        minor = heap;
    }

    while (minor) {
        if (*major == NULL) {
            *major = minor;
            break;
        }

        if (DATA_NICE(LEFTIST_DATA(*major)) <= DATA_NICE(LEFTIST_DATA(minor))) {
            major = &(*major)->right;
        } else {
            tmp = *major;
            *major = minor;
            major = &LEFTIST_RIGHT(minor);
            minor = tmp;
        }
    }

    return retval;
}

static inline void
leftist_heap_reorder_from_right(s_leftist_heap_t *heap)
{
    if (heap == NULL) {
        return;
    }

    leftist_heap_reorder_from_right(heap->right);
    leftist_heap_node_npl_update(heap);

    if (leftist_heap_node_npl_unordered_p(heap)) {
        leftist_heap_node_child_swap(heap);
    }
}

static inline s_leftist_heap_t *
leftist_heap_merge_i(s_leftist_heap_t *heap, s_leftist_heap_t *merge)
{
    s_leftist_heap_t *retval;

    assert_exit(leftist_heap_legal_ip(heap));
    assert_exit(leftist_heap_legal_ip(merge));
    assert_exit(leftist_heap_validity_p(heap));
    assert_exit(leftist_heap_validity_p(merge));

    retval = leftist_heap_merge_from_right(heap, merge);
    leftist_heap_reorder_from_right(retval);

    assert_exit(leftist_heap_validity_p(retval));

    return retval;
}

/*
 * _RETURN_ the new leftist heap.
 */
s_leftist_heap_t *
leftist_heap_merge(s_leftist_heap_t *heap, s_leftist_heap_t *merge)
{
    if (LEFTIST_HEAP_ILLEGAL_P(heap) && LEFTIST_HEAP_ILLEGAL_P(merge)) {
        return PTR_INVALID;
    } else if (heap == NULL) {
        return merge;
    } else if (merge == NULL) {
        return heap;
    } else {
        return leftist_heap_merge_i(heap, merge);
    }
}

static inline s_leftist_heap_t *
leftist_heap_remove_min_i(s_leftist_heap_t **heap)
{
    s_leftist_heap_t *removed, *left, *right;

    assert_exit(NON_NULL_PTR_P(heap));
    assert_exit(leftist_heap_legal_p(*heap));

    removed = *heap;
    left = LEFTIST_LEFT(removed);
    right = LEFTIST_RIGHT(removed);

    if (left == NULL) {
        *heap = right;
    } else if (right == NULL) {
        *heap = left;
    } else {
        *heap = leftist_heap_merge_i(left, right);
    }

    LEFTIST_LEFT(removed) = LEFTIST_RIGHT(removed) = NULL;

    return removed;
}

/*
 * _RETURN_ the removed leftist heap node.
 */
s_leftist_heap_t *
leftist_heap_remove_min(s_leftist_heap_t **heap)
{
    if (NULL_PTR_P(heap) || LEFTIST_HEAP_ILLEGAL_P(*heap)) {
        return PTR_INVALID;
    } else {
        return leftist_heap_remove_min_i(heap);
    }
}

void
leftist_heap_remove_min_and_destroy(s_leftist_heap_t **heap)
{
    s_leftist_heap_t *node;

    if (NULL_PTR_P(heap)) {
        return;
    } else if (LEFTIST_HEAP_ILLEGAL_P(*heap)) {
        return;
    } else {
        node = leftist_heap_remove_min_i(heap);
        leftist_heap_node_destroy(node);
    }
}

static inline sint32
leftist_heap_npl_i(s_leftist_heap_t *node)
{
    sint32 npl;

    leftist_heap_npl_optimize(node, npl);

    assert_exit(leftist_heap_npl_optimize_validity_p(node, npl));

    return npl;
}

