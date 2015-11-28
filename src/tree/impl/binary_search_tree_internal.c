static inline struct binary_search_tree *
binary_search_tree_create_internal(void)
{
    return binary_search_tree_node_create_internal(NULL, (sint64)0);
}

static inline struct binary_search_tree *
binary_search_tree_node_create_internal(void *val, sint64 nice)
{
    struct binary_search_tree *node;

    node = malloc_ds(sizeof(*node));
    if (!complain_no_memory_p(node)) {
        node->chain.link = malloc_ds(sizeof(*node->chain.link));

        if (!complain_no_memory_p(node->chain.link)) {
            binary_search_tree_node_initial_internal(node, val, nice);
        }
    }

    return node;
}

static inline void
binary_search_tree_initial_internal(struct binary_search_tree *tree)
{
    binary_search_tree_node_initial_internal(tree, NULL, (sint64)0);
}

static inline void
binary_search_tree_node_initial_internal(struct binary_search_tree *node,
    void *val, sint64 nice)
{
    assert(NULL != node);

    node->left = NULL;
    node->right = NULL;
    node->chain.nice = nice;

    doubly_linked_list_initial(node->chain.link);
    doubly_linked_list_node_val_set(node->chain.link, val);
}

static inline void
binary_search_tree_node_destroy(struct binary_search_tree *node)
{
    assert(NULL != node);

    doubly_linked_list_destroy(&node->chain.link);
    free_ds(node);
}

static inline void
binary_search_tree_destroy_internal(struct binary_search_tree **tree)
{
    if (*tree && tree) {
        /*
         * destroy node in post iterater order.
         * Warning: sometime if nested function call is too deepth,
         *     it may reach the default limitation of elf stack size, 8192KB.
         *     use ulimit -s unlimited or refine this function without nested.
         */
        binary_search_tree_destroy_internal(&(*tree)->left);
        binary_search_tree_destroy_internal(&(*tree)->right);
        binary_search_tree_node_destroy(*tree);
        *tree = NULL;
    }
}

static inline struct binary_search_tree *
binary_search_tree_node_find_internal(struct binary_search_tree *tree,
    sint64 nice)
{
    if (!tree) {
        return NULL;
    } else {
        if (nice > binary_search_tree_node_nice(tree)) {
            return binary_search_tree_node_find_internal(tree->right, nice);
        } else if (nice < binary_search_tree_node_nice(tree)) {
            return binary_search_tree_node_find_internal(tree->left, nice);
        } else {
            return tree;
        }
    }
}

static inline struct binary_search_tree *
binary_search_tree_node_find_min_internal(struct binary_search_tree *tree)
{
    assert(NULL != tree);

    if (!tree->left) {
        return tree;
    } else {
        return binary_search_tree_node_find_min_internal(tree->left);
    }
}

static inline struct binary_search_tree *
binary_search_tree_node_find_max_internal(struct binary_search_tree *tree)
{
    assert(NULL != tree);

    if (!tree->right) {
        return tree;
    } else {
        return binary_search_tree_node_find_max_internal(tree->right);
    }
}

static inline sint32
binary_search_tree_height_internal(struct binary_search_tree *tree)
{
    sint32 left;
    sint32 right;

    if (!tree) {
        return -1;
    } else {
        left = binary_search_tree_height_internal(tree->left);
        right = binary_search_tree_height_internal(tree->right);
        return MAX_S(left, right) + 1;
    }
}

static inline bool
binary_search_tree_node_contains_p_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    register struct binary_search_tree **iter;

    assert(NULL != tree);
    assert(NULL != node);

    iter = &tree;
    while (*iter) {
        if (node == *iter) {
            return true;
        } else {
            if (node->chain.nice > (*iter)->chain.nice) {
                iter = &(*iter)->right;
            } else if (node->chain.nice < (*iter)->chain.nice) {
                iter = &(*iter)->left;
            } else {
                /*
                 * same nice value do not means been contained in tree.
                 */
                return false;
            }
        }
    }

    return false;
}

/*
 * insert one node into given tree binary search tree
 * @tree: the pointer of given tree
 * @node: the pointer of the node
 *
 * RETURN the pointer of inserted node of the binary search tree
 *        If tree is NULL or node is NULL, RETURN NULL.
 */
static inline struct binary_search_tree *
binary_search_tree_node_insert_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    register struct binary_search_tree **iter;

    assert(NULL != tree);
    assert(NULL != node);

    iter = &tree;
    while (*iter) {
        if (node->chain.nice > (*iter)->chain.nice) {
            iter = &(*iter)->right;
        } else if (node->chain.nice < (*iter)->chain.nice) {
            iter = &(*iter)->left;
        } else if (*iter != node) {
            doubly_linked_list_merge((*iter)->chain.link, node->chain.link);
            return *iter;
        } else {
            pr_log_info("Insert node exist, nothing will be done.\n");
            return *iter;
        }
    }

    return *iter = node;
}

static inline void
binary_search_tree_node_chain_copy(struct collision_chain *tgt,
    struct collision_chain *node)
{
    assert(NULL != tgt);
    assert(NULL != node);
    assert(tgt != node);

    tgt->nice = node->nice;
    tgt->link = node->link;
}

static inline void
binary_search_tree_node_chain_swap(struct collision_chain *m,
    struct collision_chain *n)
{
    struct collision_chain tmp;

    assert(NULL != m);
    assert(NULL != n);
    assert(m!= n);

    binary_search_tree_node_chain_copy(&tmp, n);
    binary_search_tree_node_chain_copy(n, m);
    binary_search_tree_node_chain_copy(m, &tmp);
}

static inline bool
binary_search_tree_node_child_doubly_p(struct binary_search_tree *node)
{
    assert(NULL != node);

    if (node->left && node->right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_search_tree_node_leaf_p(struct binary_search_tree *node)
{
    assert(NULL != node);

    if (NULL == node->left && NULL == node->right) {
        return true;
    } else {
        return false;
    }
}

/*
 * find the pointer points the left/right pointer
 * of parent node which contains max node.
 */
static inline struct binary_search_tree **
binary_search_tree_node_find_ptr_to_max(struct binary_search_tree **tree)
{
    struct binary_search_tree **max;
    struct binary_search_tree *node;

    max = tree;
    node = *max;

    assert(NULL != tree);
    assert(NULL != node);

    while (NULL != node->right) {
        max = &node->right;
        node = *max;
    }

    return max;
}

/*
 * find the pointer points the left/right pointer
 * of parent node which contains min node.
 */
static inline struct binary_search_tree **
binary_search_tree_node_find_ptr_to_min(struct binary_search_tree **tree)
{
    struct binary_search_tree **min;
    struct binary_search_tree *node;

    min = tree;
    node = *min;

    assert(NULL != tree);
    assert(NULL != node);

    while (NULL != node->left) {
        min = &node->left;
        node = *min;
    }

    return min;
}

static inline void
binary_search_tree_node_child_lt_doubly_strip(struct binary_search_tree **pre,
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

    binary_search_tree_node_child_clean(node);
}

/*
 * strip from the min node of right child tree.
 */
static inline struct binary_search_tree *
binary_search_tree_node_child_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    struct binary_search_tree *min;
    struct binary_search_tree **min_ptr;
    sint64 nice_bk;

    assert(NULL != node);
    assert(NULL != pre);
    assert(binary_search_tree_child_doubly_p(node));

    min_ptr = binary_search_tree_node_find_ptr_to_min(&node->right);
    min = *min_ptr;
    nice_bk = node->chain.nice;

    /*
     * swap context of node instead of pointers change.
     */
    binary_search_tree_node_collision_chain_swap(&node->chain, &min->chain);
    min->chain.nice = TREE_NICE_MINUS_LMT;
    binary_search_tree_node_child_lt_doubly_strip(min_ptr, min);

    min->chain.nice = nice_bk;

    return min;
}

/*
 * copy collusuib chain from node to tgt.
 */
static inline void
binary_search_tree_node_collision_chain_copy(struct collision_chain *tgt,
    struct collision_chain *node)
{
    assert(NULL != tgt);
    assert(NULL != node);
    assert(tgt != node);

    tgt->nice = node->nice;
    tgt->link = node->link;
}

static inline void
binary_search_tree_node_collision_chain_swap(struct collision_chain *m_node,
    struct collision_chain *n_node)
{
    struct collision_chain tmp;

    assert(NULL != m_node);
    assert(NULL != n_node);
    assert(m_node != n_node);

    binary_search_tree_node_collision_chain_copy(&tmp, n_node);
    binary_search_tree_node_collision_chain_copy(n_node, m_node);
    binary_search_tree_node_collision_chain_copy(m_node, &tmp);
}

static inline bool
binary_search_tree_child_doubly_p(struct binary_search_tree *node)
{
    assert(NULL != node);

    if (NULL != node->left && NULL != node->right) {
        return true;
    } else {
        return false;
    }
}

static inline void
binary_search_tree_node_child_clean(struct binary_search_tree *node)
{
    assert(NULL != node);

    node->left = NULL;
    node->right = NULL;
}

static inline struct binary_search_tree *
binary_search_tree_node_remove_internal(struct binary_search_tree **tree,
    sint64 nice)
{
    register struct binary_search_tree *iter;
    register struct binary_search_tree **pre;

    assert(NULL != tree);
    assert(NULL != *tree);

    iter = *tree;
    pre = tree;

    while (iter) {
        if (nice > iter->chain.nice) {
            pre = &iter->right;
        } else if (nice < iter->chain.nice) {
            pre = &iter->left;
        } else if (binary_search_tree_child_doubly_p(iter)) {
            return binary_search_tree_node_child_doubly_strip(pre, iter);
        } else {
            binary_search_tree_node_child_lt_doubly_strip(pre, iter);
            return iter;
        }
        iter = *pre;
    }

    return NULL;
}

static inline void
binary_search_tree_iterate_internal(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert(LEGAL_ORDER_P(order));

    if (tree && handle) {
        if (ORDER_PRE == order) {
            doubly_linked_list_iterate(tree->chain.link, handle);
        }

        binary_search_tree_iterate_internal(tree->left, handle, order);

        if (ORDER_IN == order) {
            doubly_linked_list_iterate(tree->chain.link, handle);
        }

        binary_search_tree_iterate_internal(tree->right, handle, order);

        if (ORDER_POST == order) {
            doubly_linked_list_iterate(tree->chain.link, handle);
        }
    }
}

static inline struct binary_search_tree *
binary_search_tree_left_child_find_max(struct binary_search_tree *tree)
{
    struct binary_search_tree *left;

    assert(NULL != tree);
    assert(NULL != tree->left);

    left = tree->left;

    while (NULL != left->right) {
        left = left->right;
    }

    return left;
}

static inline struct binary_search_tree *
binary_search_tree_right_child_find_min(struct binary_search_tree *tree)
{
    struct binary_search_tree *right;

    assert(NULL != tree);
    assert(NULL != tree->right);

    right = tree->right;

    while (NULL != right->left) {
        right = right->left;
    }

    return right;
}

