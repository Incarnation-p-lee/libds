static inline bool
binary_search_tree_ordered_p(struct binary_search_tree *tree)
{
    struct binary_search_tree *left;
    struct binary_search_tree *right;

    if (!tree) {
        return true;
    } else {
        left = tree->left;
        right = tree->right;

        if (left && tree->nice < left->nice) {
            return false;
        } else if (right && tree->nice > right->nice) {
            return false;
        } else {
            if (!binary_search_tree_ordered_p(left)) {
                return false;
            } else {
                return binary_search_tree_ordered_p(right);
            }
        }
    }
}

static inline bool
avl_tree_ordered_p(struct avl_tree *tree)
{
    struct avl_tree *left;
    struct avl_tree *right;

    if (!tree) {
        return true;
    } else {
        left = tree->left;
        right = tree->right;

        if (left && tree->nice < left->nice) {
            return false;
        } else if (right && tree->nice > right->nice) {
            return false;
        } else {
            if (!avl_tree_ordered_p(left)) {
                return false;
            } else {
                return avl_tree_ordered_p(right);
            }
        }
    }
}

static inline sint32
avl_tree_height_calculate(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    if (!tree) {
        return -1;
    } else {
        left = avl_tree_height_calculate(tree->left);
        right = avl_tree_height_calculate(tree->right);

        return MAX_S32(left, right) + 1;
    }
}

static inline bool
avl_tree_height_sync_with_calculated_p(struct avl_tree *tree,
    sint32 left, sint32 right)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    if (left == avl_tree_height_calculate(tree->left)
        && right == avl_tree_height_calculate(tree->right)) {
        return true;
    } else {
        pr_log_debug("Illegal height of avl tree with calculated.\n");
        return false;
    }
}

static inline bool
avl_tree_single_rotate_left_precondition_p(struct avl_tree *node)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(avl_tree_structure_legal_p(node->left));

    k1 = node;
    k2 = k1->left;

    left = avl_tree_height_internal(k2->left);
    right = avl_tree_height_internal(k2->right);

    if (left < right) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_single_rotate_right_precondition_p(struct avl_tree *node)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(avl_tree_structure_legal_p(node->right));

    k1 = node;
    k2 = k1->right;

    left = avl_tree_height_internal(k2->left);
    right = avl_tree_height_internal(k2->right);

    if (right < left) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_doubly_rotate_left_precondition_p(struct avl_tree *node)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(avl_tree_structure_legal_p(node->left));

    k1 = node;
    k2 = k1->left;

    left = avl_tree_height_internal(k2->left);
    right = avl_tree_height_internal(k2->right);

    if (left < right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_doubly_rotate_right_precondition_p(struct avl_tree *node)
{
    sint32 left;
    sint32 right;
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(avl_tree_structure_legal_p(node->right));

    k1 = node;
    k2 = k1->right;

    left = avl_tree_height_internal(k2->left);
    right = avl_tree_height_internal(k2->right);

    if (left > right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_left_optimize_validity_p(struct avl_tree *node,
    void *expected)
{
    void *computed;

    assert_exit(avl_tree_structure_legal_p(node));

    computed = node->left;

    if (computed == expected) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_right_optimize_validity_p(struct avl_tree *node,
    void *expected)
{
    void *computed;

    assert_exit(avl_tree_structure_legal_p(node));

    computed = node->right;

    if (computed == expected) {
        return true;
    } else {
        return false;
    }
}

static inline sint32
avl_tree_height_internal(struct avl_tree *tree)
{
    if (!tree) {
        return -1;
    } else {
        return tree->height;
    }
}

static inline bool
avl_tree_height_opt_validity_p(struct avl_tree *tree,
    sint32 expected)
{
    sint32 computed;

    computed = avl_tree_height_internal(tree);

    if (computed == expected) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_height_balanced_p(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    assert_exit(avl_tree_structure_legal_p(tree));

    left = avl_tree_height_opt(tree->left);
    right = avl_tree_height_opt(tree->right);
    assert_exit(avl_tree_height_sync_with_calculated_p(tree, left, right));

    if (abs_sint32(left - right) > 1) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_balanced_optimize_validity_p(struct avl_tree *tree, bool expected)
{
    bool computed;

    assert_exit(avl_tree_structure_legal_p(tree));

    computed = avl_tree_height_balanced_p(tree);

    if (computed == expected) {
        return true;
    } else {
        return false;
    }
}

static inline bool
splay_tree_ordered_p(struct splay_tree *tree)
{
    struct splay_tree *left;
    struct splay_tree *right;

    if (!tree) {
        return true;
    } else {
        left = tree->left;
        right = tree->right;

        if (left && tree->nice < left->nice) {
            return false;
        } else if (right && tree->nice > right->nice) {
            return false;
        } else {
            if (!splay_tree_ordered_p(left)) {
                return false;
            } else {
                return splay_tree_ordered_p(right);
            }
        }
    }
}

