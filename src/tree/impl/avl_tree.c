struct avl_tree *
avl_tree_create(void)
{
    struct avl_tree *tree;

    tree = malloc_ds(sizeof(*tree));
    if (!tree) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        tree->alias.height = 0;
        binary_search_tree_initial_internal(&tree->b_tree);
    }

    return tree;
}

struct avl_tree *
avl_tree_node_create(void *val, sint64 nice)
{
    struct avl_tree *node;

    node = malloc_ds(sizeof(*node));
    if (!node) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        node->height = 0;
        binary_search_tree_node_initial_internal(&node->b_tree, val, nice);
    }

    return node;
}

void
avl_tree_initial(struct avl_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } eles {
        node->height = 0;
        binary_search_tree_initial_internal(&node->b_tree);
    }
}

void
avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node->height = 0;
        binary_search_tree_node_initial_internal(node->b_tree, val, nice);
    }
}

static inline void
avl_tree_node_destroy(struct avl_tree *node)
{
    assert(NULL != node);
    assert(NULL == avl_tree_child_left(node));
    assert(NULL == avl_tree_child_right(node));

    doubly_linked_list_destroy(&node->b_tree.chain.link);
    free_ds(node);
}

static inline void
avl_tree_destroy_internal(struct avl_tree **tree)
{
    if (*tree && tree) {
        /*
         * destroy node in post iterater order.
         */
        avl_tree_destroy_internal(&(*tree)->b_tree.left);
        avl_tree_destroy_internal(&(*tree)->b_tree.right);
        avl_tree_node_destroy(*tree);
        *tree = NULL;
    }
}

void
avl_tree_destroy(struct avl_tree **tree)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        avl_tree_destroy_internal(tree);
    }
}

static inline struct avl_tree *
avl_tree_container_of(struct binary_search_tree *node)
{
    if (NULL == node) {
        return NULL;
    } else {
        return CONTAINER_OF(node, struct avl_tree, b_tree);
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
        found = binary_search_tree_node_find_internal(tree->b_tree, nice);
        return avl_tree_container_of(found);
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
        found = binary_search_tree_node_find_min_internal(tree->b_tree);
        return avl_tree_container_of(found);
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
        found = binary_search_tree_node_find_max_internal(tree->b_tree);
        return avl_tree_container_of(found);
    }
}

bool
avl_tree_node_contains_p(struct avl_tree *tree, struct avl_tree *node)
{
    if (!tree || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_search_tree_node_contains_p_internal(&tree->b_tree,
            &node->b_tree);
    }
}

static inline bool
avl_tree_balanced_internal_p(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    if (tree) {
        avl_tree_height_internal(&tree->b_tree, &left);
        avl_tree_height_internal(&tree->b_tree, &right);

        assert(avl_tree_child_height_sync_with_calculated_p(tree, left, right));

        if (abs(left - right) > 1) {
            return false;
        } else {
            if (!avl_tree_balanced_internal_p(
                avl_tree_node_container_of(tree->b_tree.left))) {
                return false;
            } else if (!avl_tree_balanced_internal_p(
                avl_tree_node_container_of(tree->b_tree.right))) {
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
static inline struct avl_tree *
avl_tree_single_rotate_left(struct avl_tree *k1)
{
    struct avl_tree *k2;

    k2 = avl_tree_child_left(k1);

    /*
     * k3 here.
     */
    assert(NULL != avl_tree_child_left(k2));
    assert(NULL != k1);
    assert(NULL != k2);
    assert(avl_tree_single_rotate_left_precondition_p(k1));

    avl_tree_child_left_set(k1, avl_tree_child_right(k2));
    avl_tree_child_right_set(k2, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

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
static inline struct avl_tree *
avl_tree_single_rotate_right(struct avl_tree *k1)
{
    struct avl_tree *k2;

    k2 = avl_tree_child_right(k1);

    /*
     * k3 here.
     */
    assert(NULL != avl_tree_child_right(k2));
    assert(NULL != k1);
    assert(NULL != k2);
    assert(avl_tree_single_rotate_right_precondition_p(k1));

    avl_tree_child_right_set(k1, avl_tree_child_left(k2));
    avl_tree_child_left_set(k2, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

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
static inline struct avl_tree *
avl_tree_doubly_rotate_left(struct avl_tree *k1)
{
    struct avl_tree *k2;
    struct avl_tree *k3;

    k2 = avl_tree_child_left(k1);
    k3 = avl_tree_child_right(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_doubly_rotate_left_precondition_p(k1));

    avl_tree_child_right_set(k2, avl_tree_child_left(k3));
    avl_tree_child_left_set(k1, avl_tree_child_right(k3));

    avl_tree_child_left_set(k3, k2);
    avl_tree_child_right_set(k3, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

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
static inline struct avl_tree *
avl_tree_doubly_rotate_right(struct avl_tree *k1)
{
    struct avl_tree *k2;
    struct avl_tree *k3;

    k2 = avl_tree_child_right(k1);
    k3 = avl_tree_child_left(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_doubly_rotate_right_precondition_p(k1));

    avl_tree_child_left_set(k2, avl_tree_child_right(k3));
    avl_tree_child_right_set(k1, avl_tree_child_left(k3));

    avl_tree_child_right_set(k3, k2);
    avl_tree_child_left_set(k3, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

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

/*
 * Remove a node with given nice has two child, the node may do one
 * swap operation instead change tree pointers.
 */
static inline struct avl_tree *
avl_tree_node_remove_internal(struct binary_search_tree **tree, sint64 nice)
{
    struct binary_search_tree *node;
    struct binary_search_tree *removed;
    struct avl_tree *avl_node;

    if (tree && *tree) {
        node = *tree;
        avl_node = avl_tree_container_of(node);

        if (nice < node->chain.nice) {
            removed = avl_tree_node_remove_internal(&node->left, nice);
            /* 
             * the left child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_node)) {
                avl_tree_node_remove_rotate_right(tree, node);
            }
            avl_tree_height_update(avl_node);
        } else if (nice > node->chain.nice) {
            removed = avl_tree_node_remove_internal(&node->right, nice);
            /* 
             * the right child-tree.
             */
            if (!avl_tree_balanced_on_height_p(avl_node)) {
                avl_tree_node_remove_rotate_left(tree, node);
            }
            avl_tree_height_update(avl_node);
        } else {
            /*
             * find the target nice, strip the node.
             */
            if (binary_search_tree_node_child_doubly_p(node)) {
                removed = avl_tree_node_child_doubly_strip(node);
            } else {
                binary_search_tree_node_child_lt_doubly_strip(tree, node);
                removed = node;
            }
        }

        return removed;
    }

    return NULL;
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
    struct avl_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        removed = avl_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }

        return removed;
    }
}

void
avl_tree_node_remove_and_destroy(struct avl_tree **tree, sint64 nice)
{
    struct avl_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = avl_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        } else {
            avl_tree_node_destroy(removed);
        }
    }
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
    if (!tree || !node || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (avl_tree_node_nice(node) < avl_tree_node_nice(*tree)) {
            if (!avl_tree_child_left(*tree)) {
                avl_tree_child_left_set(*tree, node);
            } else {
                node = avl_tree_node_insert(&(*tree)->b_node.avl_left, node);
                /* 
                 * the left child-tree.
                 */
                if (!avl_tree_balanced_on_height_p(*tree)) {
                    avl_tree_node_insert_rotate_left(tree, node);
                }
            }
        } else if (avl_tree_node_nice(node) > avl_tree_node_nice(*tree)) {
            if (!avl_tree_child_right(*tree)) {
                avl_tree_child_right_set(*tree, node);
            } else {
                node = avl_tree_node_insert(&(*tree)->b_node.avl_right, node);
                /* 
                 * the right child-tree.
                 */
                if (!avl_tree_balanced_on_height_p(*tree)) {
                    avl_tree_node_insert_rotate_right(tree, node);
                }
            }
        } else {
            /*
             * insert node exist alreay.
             */
            if (*tree == node) {
                pr_log_info("Insert node exist, nothing will be done.\n");
            } else {
                doubly_linked_list_merge((*tree)->b_node.chain.link,
                    node->b_node.chain.link);
            }
            return *tree;
        }

        avl_tree_height_update(*tree);
        return node;
    }

    return NULL;
}

void
avl_tree_iterate(struct avl_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    binary_search_tree_iterate(avl_tree_ptr_to_bin(tree), handle, order);
    return;
}

static inline void
avl_tree_height_internal_default(struct avl_tree *node, sint32 *height)
{
    assert(NULL != height);

    if (!node) {
        *height = -1;
    } else {
        *height = node->b_node.height;
    }

    return;
}

