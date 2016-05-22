static inline bool
avl_tree_height_sync_with_calculated_p(struct avl_tree *node,
    sint32 left, sint32 right)
{
    dp_assert(NULL != node);

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

    dp_assert(NULL != k1);
    dp_assert(NULL != k2);

    left = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->left));
    right = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->right));

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

    dp_assert(NULL != k1);
    dp_assert(NULL != k1->right);

    k2 = k1->right;

    left = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->left));
    right = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->right));

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

    dp_assert(NULL != k1);
    dp_assert(NULL != k1->left);

    k2 = k1->left;

    left = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->left));
    right = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->right));

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

    dp_assert(NULL != k1);
    dp_assert(NULL != k1->right);

    k2 = k1->right;

    left = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->left));
    right = avl_tree_height_internal(avl_tree_ptr_to_avl(k2->right));

    if (left > right) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mleft [0m: %d\n", left);
        dp_fprintf(stdout, "[31mright[0m: %d\n", right);
        return false;
    }
}

static inline bool
avl_tree_ptr_to_avl_optimize_validity_p(struct binary_search_tree *node,
    void *expected)
{
    void *computed;

    computed = avl_tree_ptr_binary_to_avl(node);

    if (computed == expected) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mexpected[0m: %p\n", expected);
        dp_fprintf(stdout, "[31mcomputed[0m: %p\n", computed);
        return false;
    }
}

static inline bool
avl_tree_left_optimize_validity_p(struct avl_tree *node,
    void *expected)
{
    void *computed;

    computed = avl_tree_child_left(node);

    if (computed == expected) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mexpected[0m: %p\n", expected);
        dp_fprintf(stdout, "[31mcomputed[0m: %p\n", computed);
        return false;
    }
}

static inline bool
avl_tree_right_optimize_validity_p(struct avl_tree *node,
    void *expected)
{
    void *computed;

    computed = avl_tree_child_right(node);

    if (computed == expected) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mexpected[0m: %p\n", expected);
        dp_fprintf(stdout, "[31mcomputed[0m: %p\n", computed);
        return false;
    }
}

static inline sint32
avl_tree_height_internal_default(struct avl_tree *node)
{
    if (!node) {
        return -1;
    } else {
        return node->height;
    }
}

static inline bool
avl_tree_height_optimize_validity_p(struct avl_tree *tree,
    sint32 expected)
{
    sint32 computed;

    computed = avl_tree_height_internal_default(tree);

    if (computed == expected) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mexpected[0m: %d\n", expected);
        dp_fprintf(stdout, "[31mcomputed[0m: %d\n", computed);
        return false;
    }
}

static inline bool
avl_tree_node_balanced_optimize_validity_p(struct avl_tree *node, bool expected)
{
    bool computed;

    computed = avl_tree_node_balanced_default_p(node);

    if (computed == expected) {
        return true;
    } else {
        dp_fprintf(stdout, "[32mexpected[0m: %s\n",
            expected == true ? "true" : "false");
        dp_fprintf(stdout, "[31mcomputed[0m: %s\n",
            computed == true ? "true" : "false");
        return false;
    }
}

