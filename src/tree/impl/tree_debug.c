// #if defined DEBUG
#if 0
static inline bool
avl_tree_child_height_sync_with_calculated_p(struct avl_tree *node,
    sint32 *left, sint32 *right)
{
    struct avl_tree *tmp;

    assert(NULL != node);
    assert(NULL != left);
    assert(NULL != right);

    tmp = avl_tree_child_left(node);
    if (*left != binary_search_tree_height_internal(&tmp->b_tree)) {
        goto MISS_MATCH:
    }

    tmp = avl_tree_child_right(node);
    if (*right != binary_search_tree_height_internal(&tmp->b_tree)) {
        goto MISS_MATCH:
    }

    return true;

MISS_MATCH:
    pr_log_debug("Illegal height of avl tree, use re-calculated.\n");
    return false;
}

static inline bool
avl_tree_single_rotate_left_precondition_p(struct avl_tree *k1)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k2;

    k2 = avl_tree_child_left(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    avl_tree_height_internal(avl_tree_child_left(k2), &left);
    avl_tree_height_internal(avl_tree_child_right(k2), &right);

    if (left < right) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_single_rotate_right_precondition_p(struct avl_tree *k1)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k2;

    k2 = avl_tree_child_right(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    avl_tree_height_internal(avl_tree_child_left(k2), &left);
    avl_tree_height_internal(avl_tree_child_right(k2), &right);

    if (right < left) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_doubly_rotate_left_precondition_p(struct avl_tree *k1)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k2;

    k2 = avl_tree_child_left(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    avl_tree_height_internal(avl_tree_child_left(k2), &left);
    avl_tree_height_internal(avl_tree_child_right(k2), &right);

    if (left < right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_doubly_rotate_right_precondition_p(struct avl_tree *k1)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k2;

    k2 = avl_tree_child_right(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    avl_tree_height_internal(avl_tree_child_left(k2), &left);
    avl_tree_height_internal(avl_tree_child_right(k2), &right);

    if (left > right) {
        return true;
    } else {
        return false;
    }
}

#endif
