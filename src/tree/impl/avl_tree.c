struct avl_tree *
avl_tree_create(void)
{
    return avl_tree_node_create(NULL, (sint64)0);
}

struct avl_tree *
avl_tree_node_create(void *val, sint64 nice)
{
    struct avl_tree *node;

    node = avl_tree_ptr_to_avl(binary_search_tree_node_create(val, nice));
    avl_tree_height_set(node, 0x0);

    return node;
}

void
avl_tree_initial(struct avl_tree *root)
{
    avl_tree_node_initial(root, NULL, (sint64)0);

    return;
}

void
avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        avl_tree_height_set(node, 0x0);
        binary_search_tree_node_initial(avl_tree_ptr_to_bin(node), val, nice);
    }

    return;
}

static inline void
avl_tree_node_child_clean(struct avl_tree *node)
{
    assert(NULL != node);

    avl_tree_child_left_set(node, NULL);
    avl_tree_child_right_set(node, NULL);

    return;
}

void
avl_tree_destroy(struct avl_tree **root)
{
    binary_search_tree_destroy((struct binary_search_tree **)root);

    return;
}

static inline void
avl_tree_node_destroy(struct avl_tree *node)
{
    assert(NULL != node);

    doubly_linked_list_destroy(&node->b_node.chain.link);
    free_ds(node);
}

struct avl_tree *
avl_tree_node_find(struct avl_tree *root, sint64 nice)
{
    return avl_tree_ptr_to_avl(
        binary_search_tree_node_find(avl_tree_ptr_to_bin(root), nice));
}

struct avl_tree *
avl_tree_node_find_min(struct avl_tree *root)
{
    return avl_tree_ptr_to_avl(
        binary_search_tree_node_find_min(avl_tree_ptr_to_bin(root)));
}

struct avl_tree *
avl_tree_node_find_max(struct avl_tree *root)
{
    return avl_tree_ptr_to_avl(
        binary_search_tree_node_find_max(avl_tree_ptr_to_bin(root)));
}

bool
avl_tree_node_contains_p(struct avl_tree *root, struct avl_tree *node)
{
    return binary_search_tree_node_contains_p(avl_tree_ptr_to_bin(root),
        avl_tree_ptr_to_bin(node));
}

static inline void
avl_tree_child_height_sync_with_calculated(struct avl_tree *root,
    sint32 *left, sint32 *right)
{
    struct avl_tree *tmp;
    sint32 height;

    assert(NULL != root);
    assert(NULL != left);
    assert(NULL != right);

    tmp = avl_tree_child_left(root);
    height = binary_search_tree_height_internal(avl_tree_ptr_to_bin(tmp));
    if (*left != height) {
        pr_log_debug("Illegal height of avl tree, use re-calculated.\n");
        *left = height;
    }

    tmp = avl_tree_child_right(root);
    height = binary_search_tree_height_internal(avl_tree_ptr_to_bin(tmp));
    if (*right != height) {
        pr_log_debug("Illegal height of avl tree, use re-calculated.\n");
        *right = height;
    }

    return;
}

static inline bool
avl_tree_balanced_internal_p(struct avl_tree *root)
{
    sint32 left;
    sint32 right;

    if (root) {
        avl_tree_height_internal(avl_tree_child_left(root), &left);
        avl_tree_height_internal(avl_tree_child_right(root), &right);
        avl_tree_child_height_sync(root, &left, &right);

        if (abs(left - right) > 1) {
            return false;
        } else {
            if (!avl_tree_balanced_internal_p(avl_tree_child_left(root))) {
                return false;
            } else if (!avl_tree_balanced_internal_p(avl_tree_child_right(root))) {
                return false;
            } else {
                return true;
            }
        }
    }

    return true;
}

bool
avl_tree_balanced_p(struct avl_tree *root)
{
    if (!root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return avl_tree_balanced_internal_p(root);
    }
}

static inline void
avl_tree_height_update(struct avl_tree *node)
{
   sint32 left;
   sint32 right;

   assert(NULL != node);

   avl_tree_height_internal(avl_tree_child_left(node), &left);
   avl_tree_height_internal(avl_tree_child_right(node), &right);

   avl_tree_height_set(node, MAX_S(left, right) + 1);
   return;
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

    DEBUG_CODE(
        sint32 left;
        sint32 right;
    );

    k2 = avl_tree_child_left(k1);

    DEBUG_CODE(
        avl_tree_height_internal(avl_tree_child_left(k2), &left);
        avl_tree_height_internal(avl_tree_child_right(k2), &right);
        assert(left >= right);
    );

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != avl_tree_child_left(k2)); /* k3 */

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

    DEBUG_CODE(
        sint32 left;
        sint32 right;
    );

    k2 = avl_tree_child_right(k1);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != avl_tree_child_right(k2)); /* k3 */

    DEBUG_CODE(
        avl_tree_height_internal(avl_tree_child_left(k2), &left);
        avl_tree_height_internal(avl_tree_child_right(k2), &right);
        assert(right >= left);
    );

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

    DEBUG_CODE(
        sint32 left;
        sint32 right;
    );

    k2 = avl_tree_child_left(k1);
    k3 = avl_tree_child_right(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    DEBUG_CODE(
        avl_tree_height_internal(avl_tree_child_left(k2), &left);
        avl_tree_height_internal(avl_tree_child_right(k2), &right);
        assert(left < right);
    );

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

    DEBUG_CODE(
        sint32 left;
        sint32 right;
    );

    k2 = avl_tree_child_right(k1);
    k3 = avl_tree_child_left(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    DEBUG_CODE(
        avl_tree_height_internal(avl_tree_child_left(k2), &left);
        avl_tree_height_internal(avl_tree_child_right(k2), &right);
        assert(left > right);
    );

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
avl_tree_balanced_on_height_internal_default(struct avl_tree *node, bool *b)
{
    struct avl_tree *left;
    struct avl_tree *right;
    sint32 hght_left;
    sint32 hght_right;

    left = avl_tree_child_left(node);
    right = avl_tree_child_right(node);

    avl_tree_height_internal(left, &hght_left);
    avl_tree_height_internal(right, &hght_right);

    if (0x1u < abs(hght_left - hght_right)) {
        *b = false;
    } else {
        *b = true;
    }
}

static inline bool
avl_tree_balanced_on_height_p(struct avl_tree *node)
{
    bool balanced;

    assert(NULL != node);

    avl_tree_balanced_on_height_internal(node, &balanced);

    return balanced;
}

static inline bool
avl_tree_node_leaf_p(struct avl_tree *node)
{
    assert(NULL != node);

    if (NULL == avl_tree_child_left(node)
        && NULL == avl_tree_child_right(node)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_node_child_doubly_p(struct avl_tree *node)
{
    assert(NULL != node);

    if (NULL != avl_tree_child_left(node)
        && NULL != avl_tree_child_right(node)) {
        return true;
    } else {
        return false;
    }
}

static inline void
avl_tree_node_remove_rotate_left(struct avl_tree **root, struct avl_tree *node)
{
    struct avl_tree *tmp;
    sint32 left;
    sint32 right;

    assert(NULL != root);
    assert(NULL != node);

    tmp = avl_tree_child_left(node);
    assert(!avl_tree_node_leaf_p(tmp));

    avl_tree_height_internal(avl_tree_child_left(tmp), &left);
    avl_tree_height_internal(avl_tree_child_right(tmp), &right);

    if (left >= right) {
        /*
         *     k1
         *    /
         *   k2
         *  /
         * k3
         * Include k2->left == k2->right
         */
        *root = avl_tree_single_rotate_left(*root);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
         * Only if k2->left < k2->right
        */
        *root = avl_tree_doubly_rotate_left(*root);
    }
}

static inline void
avl_tree_node_remove_rotate_right(struct avl_tree **root, struct avl_tree *node)
{
    struct avl_tree *tmp;
    sint32 left;
    sint32 right;

    assert(NULL != root);
    assert(NULL != node);

    tmp = avl_tree_child_right(node);
    assert(!avl_tree_node_leaf_p(tmp));

    avl_tree_height_internal(avl_tree_child_left(tmp), &left);
    avl_tree_height_internal(avl_tree_child_right(tmp), &right);

    if (left <= right) {
        /*
         * k1
         *   \
         *    k2
         *     \
         *      k3
         * Include k2->left == k2->right
         */
        *root = avl_tree_single_rotate_right(*root);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         * Only if k2->left > k2->right
         */
        *root = avl_tree_doubly_rotate_right(*root);
    }
}

static inline void
avl_tree_node_insert_rotate_left(struct avl_tree **root, struct avl_tree *node)
{
    assert(NULL != root);
    assert(NULL != node);

    if (avl_tree_node_nice(node) <
        avl_tree_node_nice(avl_tree_child_left(*root))) {
        /*
         *     k1
         *    /
         *   k2
         *  /
         * k3
         */
        *root = avl_tree_single_rotate_left(*root);
    } else {
        /*
         *     k1
         *    /
         *   k2
         *    \
         *     k3
        */
        *root =  avl_tree_doubly_rotate_left(*root);
    }
}

static inline void
avl_tree_node_insert_rotate_right(struct avl_tree **root, struct avl_tree *node)
{
    assert(NULL != root);
    assert(NULL != node);

    if (avl_tree_node_nice(node) >
        avl_tree_node_nice(avl_tree_child_right(*root))) {
        /*
         * k1
         *   \
         *    k2
         *     \
         *      k3
         */
        *root = avl_tree_single_rotate_right(*root);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         */
        *root = avl_tree_doubly_rotate_right(*root);
    }
}

static inline void
avl_tree_node_child_lt_doubly_strip(struct avl_tree **pre,
    struct avl_tree *node)
{
    assert(NULL != node);
    assert(NULL != pre);
    assert(!avl_tree_node_child_doubly_p(node));

    if (NULL != avl_tree_child_left(node)) {
        *pre = avl_tree_child_left(node);
    } else {
        *pre = avl_tree_child_right(node);
    }

    avl_tree_node_child_clean(node);
}

static inline struct avl_tree *
avl_tree_node_child_doubly_strip(struct avl_tree *node)
{
    sint32 left;
    sint32 right;

    assert(NULL != node);

    avl_tree_height_internal(avl_tree_child_left(node), &left);
    avl_tree_height_internal(avl_tree_child_right(node), &right);

    if (left > right) {
        /* 
         * left child max node
          */
        return avl_tree_node_child_doubly_strip_from_max(node);
    } else {
        /*
         * right child min node 
         */
        return avl_tree_node_child_doubly_strip_from_min(node);
    }
}

static inline struct avl_tree **
avl_tree_right_child_find_min_with_parent(struct avl_tree *root,
    struct avl_tree **min)
{
    struct avl_tree *right;
    struct avl_tree **parent;

    right = avl_tree_child_right(root);
    parent = &root->b_node.avl_right;

    assert(NULL != right);
    assert(NULL != root);
    assert(!avl_tree_node_leaf_p(root));

    while (NULL != avl_tree_child_left(right)) {
        parent = &right->b_node.avl_left;
        right = avl_tree_child_left(right);
    }

    *min = right;
    return parent;
}

static inline struct avl_tree **
avl_tree_left_child_find_max_with_parent(struct avl_tree *root,
    struct avl_tree **max)
{
    struct avl_tree *left;
    struct avl_tree **parent;

    left = avl_tree_child_left(root);
    parent = &root->b_node.avl_left;

    assert(NULL != left);
    assert(NULL != root);
    assert(!avl_tree_node_leaf_p(root));

    while (NULL != avl_tree_child_right(left)) {
        parent = &left->b_node.avl_right;
        left = avl_tree_child_right(left);
    }

    *max = left;
    return parent;
}

/*
 * copy all field from node to tgt, except height value.
 */
static inline void
avl_tree_node_collision_chain_copy(struct collision_chain *tgt,
    struct collision_chain *node)
{
    assert(NULL != tgt);
    assert(NULL != node);
    assert(tgt != node);

    tgt->nice = node->nice;
    tgt->link = node->link;
}

static inline void
avl_tree_node_collision_chain_swap(struct collision_chain *m_node,
    struct collision_chain *n_node)
{
    struct collision_chain tmp;

    assert(NULL != m_node);
    assert(NULL != n_node);
    assert(m_node != n_node);

    avl_tree_node_collision_chain_copy(&tmp, n_node);
    avl_tree_node_collision_chain_copy(n_node, m_node);
    avl_tree_node_collision_chain_copy(m_node, &tmp);
}

static inline struct avl_tree *
avl_tree_node_child_doubly_strip_from_max(struct avl_tree *node)
{
    struct avl_tree *max;
    struct avl_tree **max_parent;
    sint64 nice_bk;

    assert(NULL != node);
    // Fixme, add nice assert for limit

    max_parent = avl_tree_left_child_find_max_with_parent(node, &max);
    assert(max == *max_parent);

    /* 
     * 1. exchange node and max.
     * 2. set node nice to max nice + 1.
     * 3. remove the swapped node.
     */
    nice_bk = avl_tree_node_nice(node);
    avl_tree_node_collision_chain_swap(&node->b_node.chain, &max->b_node.chain);
    avl_tree_node_nice_set(max, avl_tree_node_nice(node) + 1);
    avl_tree_node_remove_internal(&node->b_node.avl_left, avl_tree_node_nice(max));

    /*
     * resume nice.
     */
    avl_tree_node_nice_set(max, nice_bk);

    return max;
}

static inline struct avl_tree *
avl_tree_node_child_doubly_strip_from_min(struct avl_tree *node)
{
    struct avl_tree *min;
    struct avl_tree **min_parent;
    sint64 nice_bk;

    assert(NULL != node);
    // Fixme, add nice assert for limit

    min_parent = avl_tree_right_child_find_min_with_parent(node, &min);
    assert(min == *min_parent);

    /* 
     * 1. exchange node and mix.
     * 2. set node nice to mix nice - 1.
     * 3. remove the swapped node.
     */
    nice_bk = avl_tree_node_nice(node);
    avl_tree_node_collision_chain_swap(&node->b_node.chain, &min->b_node.chain);
    avl_tree_node_nice_set(min, avl_tree_node_nice(node) - 1);
    avl_tree_node_remove_internal(&node->b_node.avl_right, avl_tree_node_nice(min));

    /*
     * resume nice.
     */
    avl_tree_node_nice_set(min, nice_bk);

    return min;
}

static inline struct avl_tree *
avl_tree_node_remove_internal(struct avl_tree **root, sint64 nice)
{
    struct avl_tree *node;
    struct avl_tree *removed;

    if (root && *root) {
        node = *root;
        if (nice < avl_tree_node_nice(node)) {
            removed = avl_tree_node_remove_internal(&node->b_node.avl_left, nice);
            /* The left child-tree */
            if (!avl_tree_balanced_on_height_p(node)) {
                avl_tree_node_remove_rotate_right(root, node);
            }
            avl_tree_height_update(node);
        } else if (nice > avl_tree_node_nice(node)) {
            removed = avl_tree_node_remove_internal(&node->b_node.avl_right, nice);
            /* The right child-tree */
            if (!avl_tree_balanced_on_height_p(node)) {
                avl_tree_node_remove_rotate_left(root, node);
            }
            avl_tree_height_update(node);
        } else {
            if (avl_tree_node_child_doubly_p(node)) {
                removed = avl_tree_node_child_doubly_strip(node);
            } else {
                avl_tree_node_child_lt_doubly_strip(root, node);
                removed = node;
            }
        }

        return removed;
    }

    return NULL;
}

/*
 * remove one node if given root avl tree
 * @root: the pointer of given tree
 * @nice: the nice value of the node
 * _RETURN_: the removed node.
 *
 */
struct avl_tree *
avl_tree_node_remove(struct avl_tree **root, sint64 nice)
{
    struct avl_tree *removed;

    if (!root || !*root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = avl_tree_node_remove_internal(root, nice);
        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }

        return removed;
    }

    return NULL;
}

/*
 * insert one node into given root avl tree
 * @root: the pointer of given tree
 * @node: the pointer of the node
 *
 * RETURN the pointer of inserted node of the binary search tree
 *        If root is NULL or node is NULL, RETURN NULL.
 */
struct avl_tree *
avl_tree_node_insert(struct avl_tree **root, struct avl_tree *node)
{
    if (!root || !node || !*root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (avl_tree_node_nice(node) < avl_tree_node_nice(*root)) {
            if (!avl_tree_child_left(*root)) {
                avl_tree_child_left_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_left, node);
                /* The left child-tree */
                if (!avl_tree_balanced_on_height_p(*root)) {
                    avl_tree_node_insert_rotate_left(root, node);
                }
            }
        } else if (avl_tree_node_nice(node) > avl_tree_node_nice(*root)) {
            if (!avl_tree_child_right(*root)) {
                avl_tree_child_right_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_right, node);
                /* The right child-tree */
                if (!avl_tree_balanced_on_height_p(*root)) {
                    avl_tree_node_insert_rotate_right(root, node);
                }
            }
        } else {
            if (*root == node) {
                pr_log_info("Insert node exist, nothing will be done.\n");
            } else {
                doubly_linked_list_merge((*root)->b_node.chain.link,
                    node->b_node.chain.link);
            }
            return *root;
        }

        avl_tree_height_update(*root);
        return node;
    }

    return NULL;
}

void
avl_tree_iterate(struct avl_tree *root,
    void (*handle)(void *), enum ITER_ORDER order)
{
    binary_search_tree_iterate(avl_tree_ptr_to_bin(root), handle, order);
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

