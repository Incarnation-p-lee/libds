static inline void
binary_search_tree_balanced_node_height(struct binary_search_tree *tree,
    sint32 *height)
{
    assert(NULL != height);

    if (!tree) {
        *height = -1;
    } else {
        *height = tree->height;
    }
}

static inline void
binary_search_tree_balanced_remove_rotate_left(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    struct binary_search_tree *tmp;
    sint32 left;
    sint32 right;

    tmp = node->left;

    assert(NULL != tree);
    assert(NULL != node);
    assert(!binary_search_tree_node_leaf_p(tmp));

    binary_search_tree_balanced_node_height(tmp->left, &left);
    binary_search_tree_balanced_node_height(tmp->right, &right);

    if (left >= right) {
        /*
         *     k1
         *    /
         *   k2
         *  /
         * k3
         * Include k2->left == k2->right
         */
        *tree = binary_search_tree_balanced_single_rotate_left(*tree);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
         * Only if k2->left < k2->right
        */
        *tree = binary_search_tree_balanced_doubly_rotate_left(*tree);
    }
}

static inline void
binary_search_tree_balanced_remove_rotate_right(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    struct binary_search_tree *tmp;
    sint32 left;
    sint32 right;

    tmp = node->right;

    assert(NULL != tree);
    assert(NULL != node);
    assert(!binary_search_tree_node_leaf_p(tmp));

    binary_search_tree_balanced_node_height(tmp->left, &left);
    binary_search_tree_balanced_node_height(tmp->right, &right);

    if (left <= right) {
        /*
         * k1
         *   \
         *    k2
         *     \
         *      k3
         * Include k2->left == k2->right
         */
        *tree = binary_search_tree_balanced_single_rotate_right(*tree);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         * Only if k2->left > k2->right
         */
        *tree = binary_search_tree_balanced_doubly_rotate_right(*tree);
    }
}

static inline void
binary_search_tree_balanced_insert_rotate_left(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    assert(NULL != tree);
    assert(NULL != node);

    if (node->chain.nice < (*tree)->left->chain.nice) {
        /*
         *     k1
         *    /
         *   k2
         *  /
         * k3
         */
        *tree = binary_search_tree_balanced_single_rotate_left(*tree);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
        */
        *tree =  binary_search_tree_balanced_doubly_rotate_left(*tree);
    }
}

static inline void
binary_search_tree_balanced_insert_rotate_right(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    assert(NULL != tree);
    assert(NULL != node);

    if (node->chain.nice > (*tree)->right->chain.nice) {
        /*
         * k1
         *   \
         *    k2
         *     \
         *      k3
         */
        *tree = binary_search_tree_balanced_single_rotate_right(*tree);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         */
        *tree = binary_search_tree_balanced_doubly_rotate_right(*tree);
    }
}

static inline void
binary_search_tree_balanced_child_lt_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    assert(NULL != node);
    assert(NULL != pre);
    assert(!binary_search_tree_child_doubly_p(node));

    if (NULL != node->left) {
        *pre = node->left;
    } else {
        *pre = node->right;
    }
}

static inline struct binary_search_tree *
binary_search_tree_balanced_child_doubly_strip(struct binary_search_tree *node)
{
    sint32 left;
    sint32 right;

    assert(NULL != node);

    binary_search_tree_balanced_node_height(node->left, &left);
    binary_search_tree_balanced_node_height(node->right, &right);

    if (left > right) {
        /* 
         * left child max node
          */
        return binary_search_tree_balanced_child_doubly_strip_from_max(node);
    } else {
        /*
         * right child min node
         */
        return binary_search_tree_balanced_child_doubly_strip_from_min(node);
    }
}

static inline struct binary_search_tree **
binary_search_tree_balanced_right_child_find_min_with_parent(
    struct binary_search_tree *tree,
    struct binary_search_tree **min)
{
    struct binary_search_tree *right;
    struct binary_search_tree **parent;

    right = tree->right;
    parent = &tree->right;

    assert(NULL != right);
    assert(NULL != tree);
    assert(NULL != parent);
    assert(!binary_search_tree_node_leaf_p(tree));

    while (NULL != right->left) {
        parent = &right->left;
        right = right->left;
    }

    *min = right;
    return parent;
}

static inline struct binary_search_tree **
binary_search_tree_balanced_left_child_find_max_with_parent(
    struct binary_search_tree *tree,
    struct binary_search_tree **max)
{
    struct binary_search_tree *left;
    struct binary_search_tree **parent;

    left = tree->left;
    parent = &tree->left;

    assert(NULL != left);
    assert(NULL != tree);
    assert(NULL != parent);
    assert(!binary_search_tree_node_leaf_p(tree));

    while (NULL != left->right) {
        parent = &left->right;
        left = left->right;
    }

    *max = left;
    return parent;
}


static inline struct binary_search_tree *
binary_search_tree_balanced_child_doubly_strip_from_max(
    struct binary_search_tree *node)
{
    struct binary_search_tree *max;
    struct binary_search_tree **max_parent;
    sint64 nice_bk;

    assert(NULL != node);
    // Fixme, add nice assert for limit

    max_parent = binary_search_tree_balanced_left_child_find_max_with_parent(
        node, &max);
    assert(max == *max_parent);

    /* 
     * 1. exchange node and max.
     * 2. set node nice to max nice + 1.
     * 3. remove the swapped node.
     */
    nice_bk = node->chain.nice
    binary_search_tree_node_collision_chain_swap(&node->b_node.chain, &max->b_node.chain);
    max->chain.nice = node->chain.nice + 1;
    binary_search_tree_node_remove_internal(&node->b_node.avl_left, binary_search_tree_node_nice(max));

    /*
     * resume nice.
     */
    max->chain.nice = nice_bk;

    return max;
}

static inline struct binary_search_tree *
binary_search_tree_node_child_doubly_strip_from_min(
    struct binary_search_tree *node)
{
    struct binary_search_tree *min;
    struct binary_search_tree **min_parent;
    sint64 nice_bk;

    assert(NULL != node);
    // Fixme, add nice assert for limit

    min_parent = binary_search_tree_right_child_find_min_with_parent(node, &min);
    assert(min == *min_parent);

    /* 
     * 1. exchange node and mix.
     * 2. set node nice to mix nice - 1.
     * 3. remove the swapped node.
     */
    nice_bk = binary_search_tree_node_nice(node);
    binary_search_tree_node_collision_chain_swap(&node->b_node.chain, &min->b_node.chain);
    binary_search_tree_node_nice_set(min, binary_search_tree_node_nice(node) - 1);
    /*
     * call remove internal for update height.
     */
    binary_search_tree_remove_internal(&node->right, binary_search_tree_node_nice(min));

    /*
     * resume nice.
     */
    binary_search_tree_node_nice_set(min, nice_bk);

    return min;
}

static inline bool
binary_search_tree_balanced_on_height_p(struct binary_search_tree *tree)
{
    assert(NULL != tree);

    return binary_search_tree_balanced_on_height_p_default(tree);
}

static inline bool
binary_search_tree_balanced_on_height_p_default(struct avl_tree *tree)
{
    struct avl_tree *left;
    struct avl_tree *right;
    sint32 hght_left;
    sint32 hght_right;

    assert(NULL != tree);

    left = avl_tree_child_left(tree);
    right = avl_tree_child_right(tree);

    avl_tree_height_internal(left, &hght_left);
    avl_tree_height_internal(right, &hght_right);

    if (0x1 < abs(hght_left - hght_right)) {
        return false;
    } else {
        return true;
    }
}

static inline struct binary_search_tree *
binary_search_tree_balanced_remove(struct binary_search_tree **tree, sint64 nice)
{
    struct binary_search_tree *node;
    struct binary_search_tree *removed;

    if (tree && *tree) {
        node = *tree;

        if (nice < node->chain.nice) {
            removed = binary_search_tree_balanced_remove(&node->left, nice);
            /* 
             * the left child-tree.
             */
            if (!binary_search_tree_balanced_on_height_p(node)) {
                binary_search_tree_balanced_remove_rotate_right(tree, node);
            }

            binary_search_tree_balanced_height_update(node);
        } else if (nice > node->chain.nice) {
            removed = binary_search_tree_balanced_remove(&node->right, nice);
            /* 
             * the right child-tree.
             */
            if (!avl_tree_balanced_on_height_p(node)) {
                avl_tree_node_remove_rotate_left(tree, node);
            }

            binary_search_tree_balanced_height_update(node);
        } else {
            /*
             * find the target nice, strip the node.
             */
            if (binary_search_tree_node_child_doubly_p(node)) {
                removed = binary_search_tree_balanced_child_doubly_strip(node);
            } else {
                binary_search_tree_balanced_child_lt_doubly_strip(tree, node);
                removed = node;
            }
        }

        return removed;
    }

    return NULL;
}

static inline void
binary_search_tree_balanced_height_update(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    assert(NULL != tree);

    binary_search_tree_balanced_node_height(tree->left, &left);
    binary_search_tree_balanced_node_height(tree->right, &right);

    tree->height = MAX_S(left, right) + 1;
}

