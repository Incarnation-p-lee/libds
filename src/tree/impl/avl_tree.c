struct avl_tree *
avl_tree_create(void)
{
    struct avl_tree *tree;

    tree = malloc_ds(sizeof(*tree));
    if (!tree) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        tree->height = 0;
        tree->alias.chain.link = malloc_ds(sizeof(*tree->alias.chain.link));

        if (!tree->alias.chain.link) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            binary_search_tree_initial_internal(&tree->alias);
        }
    }

    return tree;
}

struct avl_tree *
avl_tree_node_create(void *val, sint64 nice)
{
    struct avl_tree *tree;

    tree = malloc_ds(sizeof(*tree));
    if (!tree) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        tree->height = 0;
        tree->alias.chain.link = malloc_ds(sizeof(*tree->alias.chain.link));

        if (!tree->alias.chain.link) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            binary_search_tree_node_initial_internal(&tree->alias, val, nice);
        }
    }

    return tree;
}

void
avl_tree_initial(struct avl_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tree->height = 0;
        binary_search_tree_initial_internal(&tree->alias);
    }
}

void
avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node->height = 0;
        binary_search_tree_node_initial_internal(&node->alias, val, nice);
    }
}

static inline void
avl_tree_node_destroy(struct avl_tree *node)
{
    assert(NULL != node);
    assert(NULL == avl_tree_child_left(node));
    assert(NULL == avl_tree_child_right(node));

    doubly_linked_list_destroy(&node->alias.chain.link);
    free_ds(node);
}

static inline void
avl_tree_destroy_internal(struct avl_tree *tree)
{
    if (tree) {
        /*
         * destroy node in post iterater order.
         */
        avl_tree_destroy_internal(avl_tree_child_left(tree));
        avl_tree_destroy_internal(avl_tree_child_right(tree));
        avl_tree_child_left_set(tree, NULL);
        avl_tree_child_right_set(tree, NULL);
        avl_tree_node_destroy(tree);
    }
}

void
avl_tree_destroy(struct avl_tree **tree)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        avl_tree_destroy_internal(*tree);
        *tree = NULL;
    }
}

struct avl_tree *
avl_tree_ptr_container_of(struct binary_search_tree *node)
{
    if (!node) {
        return NULL;
    } else {
        return CONTAINER_OF(node, struct avl_tree, alias);
    }
}

struct avl_tree *
avl_tree_node_find(struct avl_tree *tree, sint64 nice)
{
    struct binary_search_tree *found;

    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        found = binary_search_tree_node_find_internal(&tree->alias, nice);
        return avl_tree_ptr_container_of(found);
    }
}

struct avl_tree *
avl_tree_node_find_min(struct avl_tree *tree)
{
    struct binary_search_tree *found;

    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        found = binary_search_tree_node_find_min_internal(&tree->alias);
        return avl_tree_ptr_container_of(found);
    }
}

struct avl_tree *
avl_tree_node_find_max(struct avl_tree *tree)
{
    struct binary_search_tree *found;

    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        found = binary_search_tree_node_find_max_internal(&tree->alias);
        return avl_tree_ptr_container_of(found);
    }
}

bool
avl_tree_node_contains_p(struct avl_tree *tree, struct avl_tree *node)
{
    if (!tree || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_search_tree_node_contains_p_internal(&tree->alias,
            &node->alias);
    }
}

static inline bool
avl_tree_balanced_internal_p(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    if (tree) {
        avl_tree_height_internal(avl_tree_child_left(tree), &left);
        avl_tree_height_internal(avl_tree_child_right(tree), &right);

        assert(avl_tree_height_sync_with_calculated_p(tree, left, right));

        if (abs(left - right) > 1) {
            return false;
        } else {
            if (!avl_tree_balanced_internal_p(avl_tree_child_left(tree))) {
                return false;
            } else if (!avl_tree_balanced_internal_p(avl_tree_child_right(tree))) {
                return false;
            } else {
                return true;
            }
        }
    }

    return true;
}

bool
avl_tree_balanced_p(struct avl_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return avl_tree_balanced_internal_p(tree);
    }
}

static inline void
avl_tree_height_update(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    assert(NULL != tree);

    avl_tree_height_internal(avl_tree_child_left(tree), &left);
    avl_tree_height_internal(avl_tree_child_right(tree), &right);

    tree->height = MAX_S(left, right) + 1;
}

/*
 * If the inserted node matching following case:
 *        k1                   k2
 *       /  \                 /  \
 *      k2   c               k3   k1
 *     /  \         ==>     /    /  \
 *    k3   b               a1   b    c
 *   /
 *  a1 <-- [inserted node]
 * perform the singe rotation, with left hand.
 */
static inline struct binary_search_tree *
avl_tree_balance_single_rotate_left(struct binary_search_tree *k1)
{
    struct binary_search_tree *k2;

    assert(NULL != k1);

    k2 = k1->left;

    assert(NULL != k2);
    assert(NULL != k2->left);
    assert(avl_tree_single_rotate_left_precondition_p(k1));

    k1->left = k2->right;
    k2->right = k1;

    avl_tree_height_update(avl_tree_ptr_container_of(k1));
    avl_tree_height_update(avl_tree_ptr_container_of(k2));

    return k2;
}

/*
 * If the inserted node matching following case:
 *        k1                     k2
 *       /  \                   /  \
 *      c    k2                k1   k3
 *          /  \      ==>     /  \   \
 *         b    k3           c    b   a1
 *               \
 *                a1 <-- [inserted node]
 * perform the singe rotation, with right hand.
 */
static inline struct binary_search_tree *
avl_tree_balance_single_rotate_right(struct binary_search_tree *k1)
{
    struct binary_search_tree *k2;

    assert(NULL != k1);

    k2 = k1->right;

    assert(NULL != k2);
    assert(NULL != k2->right);
    assert(avl_tree_single_rotate_right_precondition_p(k1));

    k1->right = k2->left;
    k2->left = k1;

    avl_tree_height_update(avl_tree_ptr_container_of(k1));
    avl_tree_height_update(avl_tree_ptr_container_of(k2));

    return k2;
}

/*
 * If the inserted node matching following case:
 *        k1                   k3
 *       /  \                 /  \
 *      k2   b               k2   k1
 *     /  \         ==>     / \     \
 *    a    k3              a   a1    b
 *        /
 *       a1 <-- [inserted node]
 * perform the doubly rotation, with left hand.
 */
static inline struct binary_search_tree *
avl_tree_balance_doubly_rotate_left(struct binary_search_tree *k1)
{
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;

    assert(NULL != k1);

    k2 = k1->left;
    k3 = k2->right;

    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_doubly_rotate_left_precondition_p(k1));

    k2->right = k3->left;
    k1->left = k3->right;

    k3->left = k2;
    k3->right = k1;

    avl_tree_height_update(avl_tree_ptr_container_of(k1));
    avl_tree_height_update(avl_tree_ptr_container_of(k2));
    avl_tree_height_update(avl_tree_ptr_container_of(k3));

    return k3;
}

/*
 * If the inserted node matching following case:
 *        k1                   k3
 *       /  \                 /  \
 *      a    k2              k1   k2
 *          / \     ==>     / \     \
 *         k3  b           a   a1    b
 *        /
 *       a1 <-- [inserted node]
 * perform the doubly rotation, with right hand.
 */
static inline struct binary_search_tree *
avl_tree_balance_doubly_rotate_right(struct binary_search_tree *k1)
{
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;

    assert(NULL != k1);

    k2 = k1->right;
    k3 = k2->left;

    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_doubly_rotate_right_precondition_p(k1));

    k2->left = k3->right;
    k1->right = k3->left;

    k3->right = k2;
    k3->left = k1;

    avl_tree_height_update(avl_tree_ptr_container_of(k1));
    avl_tree_height_update(avl_tree_ptr_container_of(k2));
    avl_tree_height_update(avl_tree_ptr_container_of(k3));

    return k3;
}

static inline void
avl_tree_balanced_on_height_internal_default(struct avl_tree *tree, bool *b)
{
    struct avl_tree *left;
    struct avl_tree *right;
    sint32 hght_left;
    sint32 hght_right;

    left = avl_tree_child_left(tree);
    right = avl_tree_child_right(tree);

    avl_tree_height_internal(left, &hght_left);
    avl_tree_height_internal(right, &hght_right);

    if (0x1 < abs(hght_left - hght_right)) {
        *b = false;
    } else {
        *b = true;
    }
}

static inline bool
avl_tree_balanced_on_height_p(struct avl_tree *tree)
{
    bool balanced;

    assert(NULL != tree);

    avl_tree_balanced_on_height_internal(tree, &balanced);

    return balanced;
}

static inline void
avl_tree_balance_remove_rotate_right(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    sint32 left;
    sint32 right;
    struct binary_search_tree *tmp;

    assert(NULL != tree);
    assert(NULL != node);
    assert(!binary_search_tree_node_leaf_p(node->right));

    tmp = node->right;

    avl_tree_height_internal(avl_tree_ptr_container_of(tmp->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(tmp->right), &right);

    if (left <= right) {
        /*
         * k1
         *   \
         *    k2
         *     \
         *      k3
         * Include k2->left == k2->right
         */
        *tree = avl_tree_balance_single_rotate_right(*tree);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         * Only if k2->left > k2->right
         */
        *tree = avl_tree_balance_doubly_rotate_right(*tree);
    }
}

/*
 * Remove a node with given nice has two child, the node may do one
 * swap operation instead change tree pointers.
 */
static inline struct binary_search_tree *
avl_tree_node_remove_internal(struct binary_search_tree **tree, sint64 nice)
{
    struct binary_search_tree *node;
    struct binary_search_tree *removed;

    if (!tree || !*tree) {
        return NULL;
    } else {
        node = *tree;
        if (nice < node->chain.nice) {
            removed = avl_tree_node_remove_internal(&node->left, nice);
            /* 
             * the left child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_tree_ptr_container_of(node))) {
                avl_tree_balance_remove_rotate_right(tree, node);
            }

            avl_tree_height_update(avl_tree_ptr_container_of(node));
        } else if (nice > node->chain.nice) {
            removed = avl_tree_node_remove_internal(&node->right, nice);
            /* 
             * the right child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_tree_ptr_container_of(node))) {
                avl_tree_balance_remove_rotate_left(tree, node);
            }
            avl_tree_height_update(avl_tree_ptr_container_of(node));
        } else {
            /*
             * find the target nice, strip the node.
             */
            if (binary_search_tree_node_child_doubly_p(node)) {
                removed = avl_tree_balance_child_doubly_strip(node);
            } else {
                binary_search_tree_node_child_lt_doubly_strip(tree, node);
                removed = node;
            }
        }

        return removed;
    }
}

/*
 * remove one node if given tree avl tree
 * @tree: the pointer of given tree
 * @nice: the nice value of the node
 * _RETURN_: the removed node.
 *
 */
struct avl_tree *
avl_tree_node_remove(struct avl_tree **tree, sint64 nice)
{
    struct binary_search_tree *tmp;
    struct binary_search_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        tmp = &(*tree)->alias;
        removed = avl_tree_node_remove_internal(&tmp, nice);
        *tree = avl_tree_ptr_container_of(tmp);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }

        return avl_tree_ptr_container_of(removed);
    }
}

void
avl_tree_node_remove_and_destroy(struct avl_tree **tree, sint64 nice)
{
    struct binary_search_tree *tmp;
    struct binary_search_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = &(*tree)->alias;
        removed = avl_tree_node_remove_internal(&tmp, nice);
        *tree = avl_tree_ptr_container_of(tmp);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        } else {
            avl_tree_node_destroy(avl_tree_ptr_container_of(removed));
        }
    }
}

static inline struct binary_search_tree *
avl_tree_node_insert_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    assert(NULL != tree);
    assert(NULL != node);

    if (node->chain.nice < (*tree)->chain.nice) {
        if (!(*tree)->left) {
            (*tree)->left = node;
        } else {
            node = avl_tree_node_insert_internal(&(*tree)->left, node);
            /* 
             * the left child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_tree_ptr_container_of(*tree))) {
                avl_tree_balance_insert_rotate_left(tree, node);
            }
        }
    } else if (node->chain.nice > (*tree)->chain.nice) {
        if (!(*tree)->right) {
            (*tree)->right = node;
        } else {
            node = avl_tree_node_insert_internal(&(*tree)->right, node);
            /* 
             * the right child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_tree_ptr_container_of(*tree))) {
                avl_tree_balance_insert_rotate_right(tree, node);
            }
        }
    } else {
        /*
         * insert node exist already.
         */
        if (*tree == node) {
            pr_log_info("Insert node exist, nothing will be done.\n");
        } else {
            doubly_linked_list_merge((*tree)->chain.link, node->chain.link);
        }

        return *tree;
    }

    avl_tree_height_update(avl_tree_ptr_container_of(*tree));

    return node;
}

/*
 * insert one node into given tree avl tree
 * @tree: the pointer of given tree
 * @node: the pointer of the node
 *
 * RETURN the pointer of inserted node of the binary search tree
 *        If tree is NULL or node is NULL, RETURN NULL.
 */
struct avl_tree *
avl_tree_node_insert(struct avl_tree **tree, struct avl_tree *node)
{
    struct binary_search_tree *tmp;
    struct binary_search_tree *inserted;

    if (!tree || !node || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        tmp = &(*tree)->alias;
        inserted = avl_tree_node_insert_internal(&tmp, &node->alias);
        *tree = avl_tree_ptr_container_of(tmp);

        return avl_tree_ptr_container_of(inserted);
    }
}

void
avl_tree_iterate(struct avl_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_iterate(&tree->alias, handle, order);
    }
}

static inline void
avl_tree_height_internal_default(struct avl_tree *node, sint32 *height)
{
    assert(NULL != height);

    if (!node) {
        *height = -1;
    } else {
        *height = node->height;
    }
}

static inline void
avl_tree_balance_remove_rotate_left(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    struct binary_search_tree *tmp;
    sint32 left;
    sint32 right;

    assert(NULL != tree);
    assert(NULL != node->left);
    assert(!binary_search_tree_node_leaf_p(node->left));

    tmp = node->left;

    avl_tree_height_internal(avl_tree_ptr_container_of(tmp->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(tmp->right), &right);

    if (left >= right) {
        /*
         *     k1
         *    /
         *   k2
         *  /
         * k3
         * Include k2->left == k2->right
         */
        *tree = avl_tree_balance_single_rotate_left(*tree);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
         * Only if k2->left < k2->right
        */
        *tree = avl_tree_balance_doubly_rotate_left(*tree);
    }
}


static inline void
avl_tree_balance_insert_rotate_left(struct binary_search_tree **tree,
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
        *tree = avl_tree_balance_single_rotate_left(*tree);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
        */
        *tree =  avl_tree_balance_doubly_rotate_left(*tree);
    }
}

static inline void
avl_tree_balance_insert_rotate_right(struct binary_search_tree **tree,
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
        *tree = avl_tree_balance_single_rotate_right(*tree);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         */
        *tree = avl_tree_balance_doubly_rotate_right(*tree);
    }
}

static inline struct binary_search_tree *
avl_tree_balance_child_doubly_strip(struct binary_search_tree *node)
{
    sint32 left;
    sint32 right;

    assert(NULL != node);

    avl_tree_height_internal(avl_tree_ptr_container_of(node->left), &left);
    avl_tree_height_internal(avl_tree_ptr_container_of(node->right), &right);

    if (left > right) {
        /* 
         * left child max node
          */
        return avl_tree_balance_child_doubly_strip_from_max(node);
    } else {
        /*
         * right child min node
         */
        return avl_tree_balance_child_doubly_strip_from_min(node);
    }
}

static inline struct binary_search_tree *
avl_tree_balance_child_doubly_strip_from_max(struct binary_search_tree *node)
{
    struct binary_search_tree *max;

    assert(NULL != node);

    max = binary_search_tree_left_child_find_max(node);

    /* 
     * 1. exchange node and max.
     * 2. remove the swapped node from node->left sub-tree.
     */
    binary_search_tree_node_collision_chain_swap(&node->chain, &max->chain);
    avl_tree_node_remove_internal(&node->left, max->chain.nice);

    return max;
}

static inline struct binary_search_tree *
avl_tree_balance_child_doubly_strip_from_min(struct binary_search_tree *node)
{
    struct binary_search_tree *min;

    assert(NULL != node);

    min = binary_search_tree_right_child_find_min(node);

    /* 
     * 1. exchange node and mix.
     * 2. remove the swapped node from node->right sub-tree.
     */
    binary_search_tree_node_collision_chain_swap(&node->chain, &min->chain);
    avl_tree_node_remove_internal(&node->right, min->chain.nice);

    return min;
}

static inline bool
avl_tree_balanced_on_height_p_default(struct avl_tree *tree)
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

