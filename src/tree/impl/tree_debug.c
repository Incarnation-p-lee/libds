static inline bool
avl_tree_height_sync_with_calculated_p(struct avl_tree *node,
    sint32 left, sint32 right)
{
    assert(NULL != node);

    if (left != binary_search_tree_height_internal(node->alias.left)) {
        goto MISS_MATCH;
    }

    if (right != binary_search_tree_height_internal(node->alias.right)) {
        goto MISS_MATCH;
    }

    return true;

MISS_MATCH:
    pr_log_debug("Illegal height of avl tree, use re-calculated.\n");
    return false;
}

static inline bool
avl_tree_single_rotate_left_precondition_p(struct binary_search_tree *k1)
{
    sint32 left;
    sint32 right;
    struct binary_search_tree *k2;

    k2 = k1->left;

    assert(NULL != k1);
    assert(NULL != k2);

    avl_tree_height_internal(avl_tree_ptr_container_of(k2->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(k2->right), &right);

    if (left < right) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_single_rotate_right_precondition_p(struct binary_search_tree *k1)
{
    sint32 left;
    sint32 right;
    struct binary_search_tree *k2;

    assert(NULL != k1);
    assert(NULL != k1->right);

    k2 = k1->right;

    avl_tree_height_internal(avl_tree_ptr_container_of(k2->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(k2->right), &right);

    if (right < left) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_doubly_rotate_left_precondition_p(struct binary_search_tree *k1)
{
    sint32 left;
    sint32 right;
    struct binary_search_tree *k2;

    assert(NULL != k1);
    assert(NULL != k1->left);

    k2 = k1->left;

    avl_tree_height_internal(avl_tree_ptr_container_of(k2->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(k2->right), &right);

    if (left < right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_doubly_rotate_right_precondition_p(struct binary_search_tree *k1)
{
    sint32 left;
    sint32 right;
    struct binary_search_tree *k2;

    assert(NULL != k1);
    assert(NULL != k1->right);

    k2 = k1->right;

    avl_tree_height_internal(avl_tree_ptr_container_of(k2->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(k2->right), &right);

    if (left > right) {
        return true;
    } else {
        return false;
    }
}

