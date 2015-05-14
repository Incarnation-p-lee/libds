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
avl_tree_node_contain_p(struct avl_tree *root, struct avl_tree *node)
{
    return binary_search_tree_node_contain_p(avl_tree_ptr_to_bin(root),
        avl_tree_ptr_to_bin(node));
}

static inline bool
avl_tree_balanced_internal_p(struct avl_tree *root)
{
    sint32 left;
    sint32 right;
    struct avl_tree *tmp;

    if (root) {
        tmp = avl_tree_child_left(root);
        left = binary_search_tree_height_internal(avl_tree_ptr_to_bin(tmp));
        tmp = avl_tree_child_right(root);
        right = binary_search_tree_height_internal(avl_tree_ptr_to_bin(tmp));

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

   left = avl_tree_height_internal(avl_tree_child_left(node));
   right = avl_tree_height_internal(avl_tree_child_right(node));

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
    struct avl_tree *k3;

    k2 = avl_tree_child_left(k1);
    k3 = avl_tree_child_left(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_height_internal(avl_tree_child_left(k2))
        >= avl_tree_height_internal(avl_tree_child_right(k2)));

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
    struct avl_tree *k3;

    k2 = avl_tree_child_right(k1);
    k3 = avl_tree_child_right(k2);

    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);
    assert(avl_tree_height_internal(avl_tree_child_right(k2))
        >= avl_tree_height_internal(avl_tree_child_left(k2)));

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
    assert(avl_tree_height_internal(avl_tree_child_left(k2))
        < avl_tree_height_internal(avl_tree_child_right(k2)));

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
    assert(avl_tree_height_internal(avl_tree_child_right(k2))
        < avl_tree_height_internal(avl_tree_child_left(k2)));

    avl_tree_child_left_set(k2, avl_tree_child_right(k3));
    avl_tree_child_right_set(k1, avl_tree_child_left(k3));

    avl_tree_child_right_set(k3, k2);
    avl_tree_child_left_set(k3, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

    return k3;
}

static inline bool
avl_tree_balanced_on_height_p(struct avl_tree *node)
{
    struct avl_tree *left;
    struct avl_tree *right;

    assert(NULL != node);

    left = avl_tree_child_left(node);
    right = avl_tree_child_right(node);

    if (0x1u < abs(avl_tree_height_internal(left)
        - avl_tree_height_internal(right))) {
        return false;
    } else {
        return true;
    }
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

    left = avl_tree_height_internal(avl_tree_child_left(tmp));
    right = avl_tree_height_internal(avl_tree_child_right(tmp));

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

    left = avl_tree_height_internal(avl_tree_child_left(tmp));
    right = avl_tree_height_internal(avl_tree_child_right(tmp));

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

    *pre = avl_tree_child_left(node) ? avl_tree_child_left(node) :
        avl_tree_child_right(node);
}

static inline void
avl_tree_node_child_doubly_strip(struct avl_tree **pre, struct avl_tree *node)
{
    sint32 left;
    sint32 right;

    assert(NULL != node);
    assert(NULL != pre);

    left = avl_tree_height_internal(avl_tree_child_left(node));
    right = avl_tree_height_internal(avl_tree_child_right(node));

    if (left > right) {
        avl_tree_node_child_doubly_strip_from_max(pre, node);
    } else {
        avl_tree_node_child_doubly_strip_from_min(pre, node);
    }
}

static inline struct avl_tree *
avl_tree_node_find_min_parent(struct avl_tree *root)
{
    register struct avl_tree *parent;

    assert(NULL != root);
    assert(!avl_tree_node_leaf_p(root));
    assert(NULL != avl_tree_child_left(root));

    while (NULL != avl_tree_child_left(root)) {
        parent = root;
        root = avl_tree_child_left(root);
    }

    return parent;
}

static inline struct avl_tree *
avl_tree_node_find_max_parent(struct avl_tree *root)
{
    struct avl_tree *parent;

    assert(NULL != root);
    assert(!avl_tree_node_leaf_p(root));
    assert(NULL != avl_tree_child_right(root));

    while (NULL != avl_tree_child_right(root)) {
        parent = root;
        root = avl_tree_child_right(root);
    }

    return parent;
}

static inline void
avl_tree_node_child_doubly_strip_from_max(struct avl_tree **pre,
    struct avl_tree *node)
{
    struct avl_tree *max;
    struct avl_tree *max_parent;
    struct avl_tree *tmp;

    assert(NULL != pre);
    assert(NULL != node);

    max_parent = avl_tree_node_find_max_parent(avl_tree_child_left(node));
    max = avl_tree_child_right(max_parent);

    /* Fake one placeholder node for keeping balance */
    tmp = avl_tree_node_create(NULL, avl_tree_node_nice(max) + 1);
    avl_tree_child_left_set(tmp, avl_tree_child_left(max));
    avl_tree_child_right_set(max_parent, tmp);
    avl_tree_height_set(max, avl_tree_height(node));

    *pre = max;
    avl_tree_child_left_set(max, avl_tree_child_left(node));
    avl_tree_child_right_set(max, avl_tree_child_right(node));

    /* Clear children pointer of node */
    avl_tree_node_child_clean(node);

    avl_tree_node_remove_internal(&max->b_node.avl_left, avl_tree_node_nice(tmp));
    avl_tree_node_destroy(tmp);

    return;
}

static inline void
avl_tree_node_child_doubly_strip_from_min(struct avl_tree **pre,
    struct avl_tree *node)
{
    struct avl_tree *min;
    struct avl_tree *min_parent;
    struct avl_tree *tmp;

    assert(NULL != pre);
    assert(NULL != node);

    min_parent = avl_tree_node_find_min_parent(avl_tree_child_right(node));
    min = avl_tree_child_left(min_parent);

    /* Fake one placeholder node for keeping balance */
    tmp = avl_tree_node_create(NULL, avl_tree_node_nice(min) - 1);
    avl_tree_child_right_set(tmp, avl_tree_child_right(min));
    avl_tree_child_left_set(min_parent, tmp);

    avl_tree_height_set(min, avl_tree_height(node));
    *pre = min;
    avl_tree_child_left_set(min, avl_tree_child_left(node));
    avl_tree_child_right_set(min, avl_tree_child_right(node));

    /* Clear children pointer of node */
    avl_tree_node_child_clean(node);

    /* destroy the fake node */
    avl_tree_node_remove_internal(&min->b_node.avl_right, avl_tree_node_nice(tmp));
    avl_tree_node_destroy(tmp);

    return;
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
            removed = node;
            if (avl_tree_node_child_doubly_p(node)) {
                /* Exchange the node, and remove the fake placeholder node */
                avl_tree_node_child_doubly_strip(root, node);
            } else {
                avl_tree_node_child_lt_doubly_strip(root, node);
            }
        }

        if (NULL != removed) {
            avl_tree_node_child_clean(removed);
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
                doubly_linked_list_join((*root)->b_node.chain.link,
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

static inline sint32
avl_tree_height_internal(struct avl_tree *node)
{
    return node ? node->b_node.height : -1;
}

