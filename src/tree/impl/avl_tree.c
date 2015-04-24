struct avl_tree *
avl_tree_create(void)
{
    return avl_tree_node_create(NULL, (sint64)0);
}

struct avl_tree *
avl_tree_node_create(void *val, sint64 nice)
{
    struct binary_search_tree *node = binary_search_tree_node_create(val, nice);
    node->height = 0;
    return (struct avl_tree *)node;
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
    if (node) {
        avl_tree_height_set(node, 0u);
        binary_search_tree_node_initial(avl_tree_ptr_avl2bst(node), val, nice);
    }

    return;
}

static inline struct avl_tree *
avl_tree_ptr_bst2avl(struct binary_search_tree *node)
{
    return (struct avl_tree *)node;
}

static inline struct binary_search_tree *
avl_tree_ptr_avl2bst(struct avl_tree *node)
{
    return (struct binary_search_tree *)node;
}

void
avl_tree_destroy(struct avl_tree **root)
{
    binary_search_tree_destroy((struct binary_search_tree **)root);
    return;
}

struct avl_tree *
avl_tree_node_find(struct avl_tree *root, sint64 nice)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find(avl_tree_ptr_avl2bst(root), nice));
}

struct avl_tree *
avl_tree_node_find_min(struct avl_tree *root)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find_min(avl_tree_ptr_avl2bst(root)));
}

struct avl_tree *
avl_tree_node_find_max(struct avl_tree *root)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find_max(avl_tree_ptr_avl2bst(root)));
}

bool
avl_tree_node_contain_p(struct avl_tree *root, struct avl_tree *node)
{
    return binary_search_tree_node_contain_p(avl_tree_ptr_avl2bst(root),
        avl_tree_ptr_avl2bst(node));
}

bool
avl_tree_balanced_p(struct avl_tree *root)
{
    sint32 left;
    sint32 right;
    void *tmp;

    if (root) {
        tmp = avl_tree_node_child_left(root);
        left = binary_search_tree_height(tmp);
        tmp = avl_tree_node_child_right(root);
        right = binary_search_tree_height(tmp);
        if (abs(left - right) > 1) {
            return false;
        } else {
            if (!avl_tree_balanced_p(avl_tree_node_child_left(root))) {
                return false;
            } else if (!avl_tree_balanced_p(avl_tree_node_child_right(root))) {
                return false;
            } else {
                return true;
            }
        }
    }

    return true;
}

static inline struct avl_tree *
avl_tree_node_child_left(struct avl_tree *node)
{
    assert(NULL != node);

    return node->b_node.avl_left;
}

static inline void
avl_tree_node_child_left_set(struct avl_tree *node, void *val)
{
    assert(NULL != node);

    node->b_node.avl_left = val;
}

static inline struct avl_tree *
avl_tree_node_child_right(struct avl_tree *node)
{
    assert(NULL != node);

    return node->b_node.avl_right;
}

static inline void
avl_tree_node_child_right_set(struct avl_tree *node, void *val)
{
    assert(NULL != node);

    node->b_node.avl_right = val;
}

static inline void
avl_tree_height_update(struct avl_tree *node)
{
   sint32 left;
   sint32 right;

   assert(NULL != node);

   left = avl_tree_height_internal(avl_tree_node_child_left(node));
   right = avl_tree_height_internal(avl_tree_node_child_right(node));

   avl_tree_height_set(node, MAX_S(left, right) + 1);
   return;
}

/*
 * If the inserted node matching following case:
 *        k1                   k2
 *       /  \                 /  \
 *      k2   c               a    k1
 *     /  \         ==>     /    /  \
 *    a    b               a1   b    c
 *   /
 *  a1 <-- [inserted node]
 * perform the singe rotation, with left hand.
 */
static inline struct avl_tree *
avl_tree_single_rotate_left(struct avl_tree *k1)
{
    struct avl_tree *k2;

    k2 = avl_tree_node_child_left(k1);

    avl_tree_node_child_left_set(k1, avl_tree_node_child_right(k2));
    avl_tree_node_child_right_set(k2, k1);

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

    return k2;
}

/*
 * If the inserted node matching following case:
 *        k1                     k2
 *       /  \                   /  \
 *      c    k2                k1   a
 *          /  \      ==>     /  \   \
 *         b    a            c    b   a1
 *               \
 *                a1 <-- [inserted node]
 * perform the singe rotation, with right hand.
 */
static inline struct avl_tree *
avl_tree_single_rotate_right(struct avl_tree *k1)
{
    struct avl_tree *k2;

    k2 = avl_tree_node_child_right(k1);

    avl_tree_node_child_right_set(k1, avl_tree_node_child_left(k2));
    avl_tree_node_child_left_set(k2, k1);

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
 *
 * This process can be finished by 2 steps.
 * <1>. Single right rotation on k2.
 * <2>. Single left rotation on k1.
 *        k1                   k1                 k3
 *       /  \                 /  \               /  \
 *      k2   b               k3   b             k2  k1
 *     /  \         ==>     /          ==>     / \    \
 *    a    k3              k2                 a  a1    b
 *        /               / \
 *       a1              a  a1
 */
static inline struct avl_tree *
avl_tree_doubly_rotate_left(struct avl_tree *k1)
{
    struct avl_tree *tmp;

    tmp = avl_tree_single_rotate_right(avl_tree_node_child_left(k1));
    avl_tree_node_child_left_set(k1, tmp);

    return avl_tree_single_rotate_left(k1);
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
 *
 * This process can be finished by 2 steps.
 * <1>. Single left rotation on k2.
 * <2>. Single right rotation on k1.
 *        k1                   k1                   k3
 *       /  \                 /  \                 /  \
 *      a    k2              a    k3              k1  k2
 *          / \     ==>          / \     ==>     / \    \
 *         k3  b                a1  k2          a  a1    b
 *        /                          \
 *       a1                           b
 */
static inline struct avl_tree *
avl_tree_doubly_rotate_right(struct avl_tree *k1)
{
    struct avl_tree *tmp;

    tmp = avl_tree_single_rotate_left(avl_tree_node_child_right(k1));
    avl_tree_node_child_right_set(k1, tmp);

    return avl_tree_single_rotate_right(k1);
}

static inline bool
avl_tree_balanced_internal_p(struct avl_tree *node)
{
    struct avl_tree *left;
    struct avl_tree *right;

    left = avl_tree_node_child_left(node);
    right = avl_tree_node_child_right(node);

    if (0x1u < abs(avl_tree_height_internal(left)
        - avl_tree_height_internal(right))) {
        return false;
    } else {
        return true;
    }
}

static inline sint64
avl_tree_node_nice(struct avl_tree *node)
{
    assert(NULL != node);

    return node->b_node.chain.nice;
}

static inline void
avl_tree_node_nice_set(struct avl_tree *node, sint64 nice)
{
    assert(NULL != node);

    node->b_node.chain.nice = nice;
}

static inline bool
avl_tree_node_leaf_p(struct avl_tree *node)
{
    assert(NULL != node);

    if (NULL == avl_tree_node_child_left(node)
        && NULL == avl_tree_node_child_right(node)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_node_child_doubly_p(struct avl_tree *node)
{
    assert(NULL != node);

    if (NULL != avl_tree_node_child_left(node)
        && NULL != avl_tree_node_child_right(node)) {
        return true;
    } else {
        return false;
    }
}

static inline void
avl_tree_node_remove_rotate_left(struct avl_tree **root, struct avl_tree *node)
{
    struct avl_tree *tmp;

    assert(root && node);

    tmp = avl_tree_node_child_left(node);
    assert(!avl_tree_node_leaf_p(tmp));

    if (NULL != avl_tree_node_child_left(node)) {
        *root = avl_tree_single_rotate_left(*root);
    } else {
        *root = avl_tree_doubly_rotate_left(*root);
    }
}

static inline void
avl_tree_node_remove_rotate_right(struct avl_tree **root, struct avl_tree *node)
{
    struct avl_tree *tmp;

    assert(root && node);

    tmp = avl_tree_node_child_right(node);
    assert(!avl_tree_node_leaf_p(tmp));

    if (NULL != avl_tree_node_child_right(node)) {
        *root = avl_tree_single_rotate_right(*root);
    } else {
        *root = avl_tree_doubly_rotate_right(*root);
    }
}

static inline void
avl_tree_node_insert_rotate_left(struct avl_tree **root, struct avl_tree *node)
{
     if (avl_tree_node_nice(node) <
         avl_tree_node_nice(avl_tree_node_child_left(*root))) {
         *root = avl_tree_single_rotate_left(*root);
     } else {
         *root =  avl_tree_doubly_rotate_left(*root);
     }
}

static inline void
avl_tree_node_insert_rotate_right(struct avl_tree **root, struct avl_tree *node)
{
     if (avl_tree_node_nice(node) >
         avl_tree_node_nice(avl_tree_node_child_right(*root))) {
         *root = avl_tree_single_rotate_right(*root);
     } else {
         *root = avl_tree_doubly_rotate_right(*root);
     }
}

static inline void
avl_tree_node_child_lt_doubly_strip(struct avl_tree **pre,
    struct avl_tree *node)
{
    assert(NULL != node);

    *pre = avl_tree_node_child_left(node) ? avl_tree_node_child_left(node) :
        avl_tree_node_child_right(node);
}

static inline sint64
avl_tree_node_child_doubly_strip(struct avl_tree **pre, struct avl_tree *node)
{
    sint32 left;
    sint32 right;

    assert(pre && node);

    left = avl_tree_height_internal(avl_tree_node_child_left(node));
    right = avl_tree_height_internal(avl_tree_node_child_right(node));

    if (left > right) {
        return avl_tree_node_child_doubly_strip_from_min(pre, node);
    } else {
        return avl_tree_node_child_doubly_strip_from_max(pre, node);
    }
}

static inline struct avl_tree *
avl_tree_node_find_min_parent(struct avl_tree *root)
{
    register struct avl_tree **tmp;

    assert(NULL != root);

    if (avl_tree_node_leaf_p(root)) {
        return NULL;
    } else if (NULL == avl_tree_node_child_left(root)) {
        return root;
    }

    tmp = &root;
    while (!avl_tree_node_leaf_p(avl_tree_node_child_left(*tmp))) {
        tmp = &(*tmp)->b_node.avl_left;
    }

    return *tmp;
}

static inline struct avl_tree *
avl_tree_node_find_max_parent(struct avl_tree *root)
{
    struct avl_tree *max;

    assert(NULL != root);
    assert(NULL != avl_tree_node_child_right(root));

    max = avl_tree_node_child_right(root);
    while (NULL != avl_tree_node_child_right(max)) {
        root = max;
        max = avl_tree_node_child_right(max);
    }
    return root;
}

static inline sint64
avl_tree_node_child_doubly_strip_from_max(struct avl_tree **pre,
    struct avl_tree *node)
{
    struct avl_tree *max;
    struct avl_tree *max_parent;
    struct avl_tree *tmp;

    max_parent = avl_tree_node_find_max_parent(node);
    max = avl_tree_node_child_right(max_parent);

    /* Fake one placeholder node for keeping balance */
    tmp = avl_tree_node_create(NULL, avl_tree_node_nice(max) + 1);
    avl_tree_node_child_right_set(max_parent, tmp);

    *pre = max;
    avl_tree_node_child_left_set(max, avl_tree_node_child_left(node));
    avl_tree_node_child_right_set(max, avl_tree_node_child_right(node));
    /* Clear children pointer of node */
    avl_tree_node_child_left_set(node, NULL);
    avl_tree_node_child_right_set(node, NULL);

    return avl_tree_node_nice(tmp);;
}

static inline sint64
avl_tree_node_child_doubly_strip_from_min(struct avl_tree **pre,
    struct avl_tree *node)
{
    struct avl_tree *min;
    struct avl_tree *min_parent;
    struct avl_tree *tmp;

    min_parent = avl_tree_node_find_min_parent(node);
    min = avl_tree_node_child_left(min_parent);

    /* Fake one placeholder node for keeping balance */
    tmp = avl_tree_node_create(NULL, avl_tree_node_nice(min) - 1);
    avl_tree_node_child_left_set(min_parent, tmp);

    *pre = min;
    avl_tree_node_child_left_set(min, avl_tree_node_child_left(node));
    avl_tree_node_child_right_set(min, avl_tree_node_child_right(node));
    /* Clear children pointer of node */
    avl_tree_node_child_left_set(node, NULL);
    avl_tree_node_child_right_set(node, NULL);

    return avl_tree_node_nice(tmp);
}

static inline void
avl_tree_node_destroy(struct avl_tree *node)
{
    doubly_linked_list_destroy(&node->b_node.chain.link);
    free_ds(node);
}

/*
 * remove one node if given root avl tree
 * @root: the pointer of given tree
 * @nice: the nice value of the node
 *
 */
void
avl_tree_node_remove(struct avl_tree **root, sint64 nice)
{
    struct avl_tree *node;

    if (root && *root) {
        node = *root;
        if (nice < avl_tree_node_nice(node)) {
            avl_tree_node_remove(&node->b_node.avl_left, nice);
            /* The left child-tree */
            if (!avl_tree_balanced_internal_p(node)) {
                avl_tree_node_remove_rotate_right(root, node);
            }
        } else if (nice > avl_tree_node_nice(node)) {
            avl_tree_node_remove(&node->b_node.avl_right, nice);
            /* The right child-tree */
            if (!avl_tree_balanced_internal_p(node)) {
                avl_tree_node_remove_rotate_left(root, node);
            }
        } else {
            if (avl_tree_node_child_doubly_p(node)) {
                /* Exchange the node, and remove the fake one */
                nice = avl_tree_node_child_doubly_strip(root, node);
                avl_tree_node_remove(root, nice);
            } else {
                avl_tree_node_child_lt_doubly_strip(root, node);
            }
            avl_tree_node_destroy(node);
            /* No need update height here for only one child for removed node */
            return;
        }
        assert(avl_tree_balanced_p(*root));
        avl_tree_height_update(*root);
    }
    return;
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
    if (root && node && *root) {
        if (avl_tree_node_nice(node) < avl_tree_node_nice(*root)) {
            if (!avl_tree_node_child_left(*root)) {
                avl_tree_node_child_left_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_left, node);
            }
            /* The left child-tree */
            if (!avl_tree_balanced_internal_p(*root)) {
                avl_tree_node_insert_rotate_left(root, node);
            }
        } else if (avl_tree_node_nice(node) > avl_tree_node_nice(*root)) {
            if (!avl_tree_node_child_right(*root)) {
                avl_tree_node_child_right_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_right, node);
            }
            /* The right child-tree */
            if (!avl_tree_balanced_internal_p(*root)) {
                avl_tree_node_insert_rotate_right(root, node);
            }
        } else {
            if (*root != node) {
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
    binary_search_tree_iterate(avl_tree_ptr_avl2bst(root), handle, order);
    return;
}

static inline sint32
avl_tree_height_internal(struct avl_tree *node)
{
    return node ? node->b_node.height : -1;
}

static inline void
avl_tree_height_set(struct avl_tree *node, sint32 height)
{
    node->b_node.height = height;
}

sint32
avl_tree_height(struct avl_tree *root)
{
    return binary_search_tree_height(avl_tree_ptr_avl2bst(root));
}
