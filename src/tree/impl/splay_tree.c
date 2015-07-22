struct splay_tree *
splay_tree_create(void)
{
    return splay_tree_node_create(NULL, (sint64)0);
}

struct splay_tree *
splay_tree_node_create(void *val, sint64 nice)
{
    return splay_tree_ptr_to_splay(binary_search_tree_node_create(val, nice));
}

void
splay_tree_initial(struct splay_tree *tree)
{
    splay_tree_node_initial(tree, NULL, (sint64)0);

    return;
}

void
splay_tree_node_initial(struct splay_tree *node, void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_node_initial(splay_tree_ptr_to_bin(node), val, nice);
    }

    return;
}

void
splay_tree_destroy(struct splay_tree **tree)
{
    binary_search_tree_destroy((struct binary_search_tree **)tree);
    return;
}

static void inline
splay_tree_splaying_root_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_left(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    /*
     *     k1          k2
     *    /  \        /  \
     *   k2   c  =>  a    k1
     *  /  \             /  \
     * a    b           b    c
     */
    splay_tree_child_left_set(k1, splay_tree_child_right(k2));
    splay_tree_child_right_set(k2, k1);

    *tree = k2;
}

static void inline
splay_tree_splaying_root_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_right(k1);

    assert(NULL != k1);
    assert(NULL != k2);

    /*
     *   k1               k2
     *  /  \             /  \
     * a    k2    =>    k1   c
     *     /  \        /  \
     *    b    c      a    b
     */
    splay_tree_child_right_set(k1, splay_tree_child_left(k2));
    splay_tree_child_left_set(k2, k1);

    *tree = k2;
}

static void inline
splay_tree_single_splaying_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_left(k1);
    k3 = splay_tree_child_left(k2);

    /*
     *     k1      k3
     *    /          \
     *   k2    =>     k2
     *  /              \
     * k3               k1
     */
    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    splay_tree_child_left_set(k1, splay_tree_child_right(k2));

    splay_tree_child_left_set(k2, splay_tree_child_right(k3));
    splay_tree_child_right_set(k2, k1);

    splay_tree_child_right_set(k3, k2);

    *tree = k3;
}

static void inline
splay_tree_single_splaying_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_right(k1);
    k3 = splay_tree_child_right(k2);

    /*
     * k1              k3
     *  \             /
     *   k2    =>    k2
     *    \         /
     *     k3      k1
     */
    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    splay_tree_child_right_set(k1, splay_tree_child_left(k2));

    splay_tree_child_right_set(k2, splay_tree_child_left(k3));
    splay_tree_child_left_set(k2, k1);

    splay_tree_child_left_set(k3, k2);

    *tree = k3;
}

static void inline
splay_tree_doubly_splaying_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_left(k1);
    k3 = splay_tree_child_right(k2);

    /*
     *   k1        k3
     *  /         /  \
     * k2    =>  k2  k1
     *  \
     *   k3
     */
    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    splay_tree_child_left_set(k1, splay_tree_child_right(k3));
    splay_tree_child_right_set(k2, splay_tree_child_left(k3));

    splay_tree_child_left_set(k3, k2);
    splay_tree_child_right_set(k3, k1);

    *tree = k3;
}

static void inline
splay_tree_doubly_splaying_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(NULL != tree);

    k1 = *tree;
    k2 = splay_tree_child_right(k1);
    k3 = splay_tree_child_left(k2);

    /*
     * k1          k3
     *  \         /  \
     *   k2  =>  k1  k2
     *  /
     * k3
     */
    assert(NULL != k1);
    assert(NULL != k2);
    assert(NULL != k3);

    splay_tree_child_right_set(k1, splay_tree_child_left(k3));
    splay_tree_child_left_set(k2, splay_tree_child_right(k3));

    splay_tree_child_left_set(k3, k1);
    splay_tree_child_right_set(k3, k2);

    *tree = k3;
}

static void inline
splay_tree_node_splaying_left(struct splay_tree **tree,
    sint64 nice, struct splay_tree *root)
{
    struct splay_tree *left_child;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != root);

    left_child = splay_tree_child_left(*tree);

    assert(NULL != left_child);

    /* If the parent of found node is root node */
    if (nice == splay_tree_node_nice(left_child) && *tree == root) {
        splay_tree_splaying_root_left(tree);

        assert(nice == splay_tree_node_nice(*tree));
    } else if (nice != splay_tree_node_nice(left_child)) {
        assert(splay_tree_child_has_nice_p(left_child, nice));

        if (NULL != splay_tree_child_left(left_child)
            && nice == splay_tree_node_nice(splay_tree_child_left(left_child))) {
            splay_tree_single_splaying_left(tree);
        } else if (NULL != splay_tree_child_right(left_child)
            && nice == splay_tree_node_nice(splay_tree_child_right(left_child))) {
            splay_tree_doubly_splaying_left(tree);
        } else {
            assert_not_reached();
        }

        assert(nice == splay_tree_node_nice(*tree));
    } else {
        /* if left_child == nice, and *tree != root, nothing need to do */
        ;
    }
}

static void inline
splay_tree_node_splaying_right(struct splay_tree **tree,
    sint64 nice, struct splay_tree *root)
{
    struct splay_tree *right_child;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != root);

    right_child = splay_tree_child_right(*tree);

    assert(NULL != right_child);

    /* If the parent of found node is root node */
    if (nice == splay_tree_node_nice(right_child) && *tree == root) {
        splay_tree_splaying_root_right(tree);

        assert(nice == splay_tree_node_nice(*tree));
    } else if (nice != splay_tree_node_nice(right_child)) {
        assert(splay_tree_child_has_nice_p(right_child, nice));

        if (NULL != splay_tree_child_right(right_child)
            && nice == splay_tree_node_nice(splay_tree_child_right(right_child))) {
            splay_tree_single_splaying_right(tree);
        } else if (NULL != splay_tree_child_left(right_child)
            && nice == splay_tree_node_nice(splay_tree_child_left(right_child))) {
            splay_tree_doubly_splaying_right(tree);
        } else {
            assert_not_reached();
        }

        assert(nice == splay_tree_node_nice(*tree));
    } else {
        /* if right_child == nice, and *tree != root, nothing need to do */
        ;
    }
}

static inline struct splay_tree *
splay_tree_node_find_internal(struct splay_tree **tree, sint64 nice,
    struct splay_tree *root)
{
    struct splay_tree *node;

    node = *tree;
    if (*tree) {
        if (nice < splay_tree_node_nice(node)) {
            node = splay_tree_node_find_internal(&node->b_node.splay_left, nice, root);

            if (NULL != node && NULL != splay_tree_child_left(*tree)) {
                splay_tree_node_splaying_left(tree, nice, root);
            }
        } else if (nice > splay_tree_node_nice(node)) {
            node = splay_tree_node_find_internal(&node->b_node.splay_right, nice, root);

            if (NULL != node && NULL != splay_tree_child_right(*tree)) {
                splay_tree_node_splaying_right(tree, nice, root);
            }
        }
    }

    return node;
}

struct splay_tree *
splay_tree_node_find(struct splay_tree **tree, sint64 nice)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return splay_tree_node_find_internal(tree, nice, *tree);
    }
}

static inline struct splay_tree *
splay_tree_node_find_min_internal(struct splay_tree **tree,
    struct splay_tree *root)
{
    struct splay_tree *node;

    assert(NULL != tree);

    node = *tree;
    if (NULL != splay_tree_child_left(node)) {
        node = splay_tree_node_find_min_internal(&node->b_node.splay_left, root);
        splay_tree_node_splaying_left(tree, splay_tree_node_nice(node), root);
    }

    return node;
}

struct splay_tree *
splay_tree_node_find_min(struct splay_tree **tree)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return splay_tree_node_find_min_internal(tree, *tree);
    }
}

static inline struct splay_tree *
splay_tree_node_find_max_internal(struct splay_tree **tree,
    struct splay_tree *root)
{
    struct splay_tree *node;

    assert(NULL != tree);

    node = *tree;
    if (NULL != splay_tree_child_right(node)) {
        node = splay_tree_node_find_max_internal(&node->b_node.splay_right, root);
        splay_tree_node_splaying_right(tree, splay_tree_node_nice(node), root);
    }

    return node;
}

struct splay_tree *
splay_tree_node_find_max(struct splay_tree **tree)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return splay_tree_node_find_max_internal(tree, *tree);
    }
}

sint32
splay_tree_height(struct splay_tree *tree)
{
    return binary_search_tree_height(splay_tree_ptr_to_bin(tree));
}

bool
splay_tree_node_contains_p(struct splay_tree *tree, struct splay_tree *node)
{
    return binary_search_tree_node_contains_p(splay_tree_ptr_to_bin(tree),
        splay_tree_ptr_to_bin(node));
}

static inline bool
splay_tree_node_leaf_p(struct splay_tree *node)
{
    assert(NULL != node);

    if (NULL == splay_tree_child_left(node)
        && NULL == splay_tree_child_right(node)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
splay_tree_child_has_nice_p(struct splay_tree *node, sint64 nice)
{
    struct splay_tree *left;
    struct splay_tree *right;

    assert(NULL != node);
    assert(!splay_tree_node_leaf_p(node));

    left = splay_tree_child_left(node);
    right = splay_tree_child_right(node);

    if (NULL != left && nice == splay_tree_node_nice(left)) {
        return true;
    } else if (NULL != right && nice == splay_tree_node_nice(right)) {
        return true;
    } else {
        return false;
    }
}

/*
 * insert one node into given tree splay tree
 * @tree: the pointer of given tree
 * @node: the pointer of the node
 *
 * RETURN the pointer of inserted node of the binary search tree
 *        If tree is NULL or node is NULL, RETURN NULL.
 */
struct splay_tree *
splay_tree_node_insert(struct splay_tree **tree, struct splay_tree *node)
{
    if (!tree || !*tree || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        binary_search_tree_node_insert(
                splay_tree_ptr_to_bin(*tree), splay_tree_ptr_to_bin(node));
        return splay_tree_node_find(tree, splay_tree_node_nice(node));
    }
}

/*
 * remove one node if given tree splay tree
 * @tree: the pointer of given tree
 * @nice: the nice value of the node
 *
 * RETURN the pointer of the removed node, if NULL or no such nice
 *    RETURN NULL.
 */
struct splay_tree *
splay_tree_node_remove(struct splay_tree **tree, sint64 nice)
{
    struct binary_search_tree **tmp;

    tmp = (struct binary_search_tree **)tree;

    return splay_tree_ptr_to_splay(binary_search_tree_node_remove(tmp, nice));
}

void
splay_tree_iterate(struct splay_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    binary_search_tree_iterate(splay_tree_ptr_to_bin(tree), handle, order);
    return;
}

