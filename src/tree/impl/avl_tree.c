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
    return node->b_node.avl_left;
}

static inline void
avl_tree_node_child_left_set(struct avl_tree *node, void *val)
{
    node->b_node.avl_left = val;
}

static inline struct avl_tree *
avl_tree_node_child_right(struct avl_tree *node)
{
    return node->b_node.avl_right;
}

static inline void
avl_tree_node_child_right_set(struct avl_tree *node, void *val)
{
    node->b_node.avl_right = val;
}

static inline void
avl_tree_height_update(struct avl_tree *node)
{
   sint32 left;
   sint32 right;

   left = avl_tree_height_get(avl_tree_node_child_left(node));
   right = avl_tree_height_get(avl_tree_node_child_right(node));

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

    if (0x1u < abs(avl_tree_height_get(left) - avl_tree_height_get(right))) {
        return false;
    } else {
        return true;
    }
}

static inline sint64
avl_tree_node_nice_get(struct avl_tree *node)
{
    return node->b_node.chain.nice;
}

static inline void
avl_tree_node_nice_set(struct avl_tree *node, sint64 nice)
{
    node->b_node.chain.nice = nice;
}

static inline void
avl_tree_rotate_left(struct avl_tree **root, struct avl_tree *node)
{
     if (avl_tree_node_nice_get(node) <
         avl_tree_node_nice_get(avl_tree_node_child_left(*root))) {
         *root = avl_tree_single_rotate_left(*root);
     } else {
         *root =  avl_tree_doubly_rotate_left(*root);
     }
}

static inline void
avl_tree_rotate_right(struct avl_tree **root, struct avl_tree *node)
{
     if (avl_tree_node_nice_get(node) >
         avl_tree_node_nice_get(avl_tree_node_child_right(*root))) {
         *root = avl_tree_single_rotate_right(*root);
     } else {
         *root = avl_tree_doubly_rotate_right(*root);
     }
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
        if (avl_tree_node_nice_get(node) < avl_tree_node_nice_get(*root)) {
            if (!avl_tree_node_child_left(*root)) {
                avl_tree_node_child_left_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_left, node);
            }
            /* The left child-tree */
            if (!avl_tree_balanced_internal_p(*root)) {
                avl_tree_rotate_left(root, node);
            }
        } else if (avl_tree_node_nice_get(node) > avl_tree_node_nice_get(*root)) {
            if (!avl_tree_node_child_right(*root)) {
                avl_tree_node_child_right_set(*root, node);
            } else {
                node = avl_tree_node_insert(&(*root)->b_node.avl_right, node);
            }
            /* The right child-tree */
            if (!avl_tree_balanced_internal_p(*root)) {
                avl_tree_rotate_right(root, node);
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
avl_tree_height_get(struct avl_tree *node)
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
    return avl_tree_height_get(root);
}
