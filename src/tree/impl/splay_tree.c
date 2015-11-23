struct splay_tree *
splay_tree_create(void)
{
    struct splay_tree *tree;

    tree = malloc_ds(sizeof(*tree));
    if (!tree) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        tree->alias.chain.link = malloc_ds(sizeof(*tree->alias.chain.link));

        if (!tree->alias.chain.link) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            binary_search_tree_initial_internal(&tree->alias);
        }
    }

    return tree;
}

struct splay_tree *
splay_tree_node_create(void *val, sint64 nice)
{
    struct splay_tree *tree;

    tree = malloc_ds(sizeof(*tree));
    if (!tree) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
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
splay_tree_initial(struct splay_tree *tree)
{
    splay_tree_node_initial(tree, NULL, (sint64)0);
}

void
splay_tree_node_initial(struct splay_tree *node, void *val, sint64 nice)
{
    if (!complain_null_pointer_p(node)) {
        binary_search_tree_node_initial(&node->alias, val, nice);
    }
}

struct splay_tree *
splay_tree_ptr_container_of(struct binary_search_tree *node)
{
    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        return CONTAINER_OF(node, struct splay_tree, alias);
    }
}

static inline void
splay_tree_node_destroy(struct splay_tree *node)
{
    assert(NULL != node);
    assert(NULL == splay_tree_child_left(node));
    assert(NULL == splay_tree_child_right(node));

    doubly_linked_list_destroy(&node->alias.chain.link);
    free_ds(node);
}

static inline void
splay_tree_destroy_internal(struct splay_tree *tree)
{
    if (tree) {
        /*
         * destroy node in post iterater order.
         * Warning: sometime if nested function call is too deepth,
         *     it may reach the default limitation of elf stack size, 8192KB.
         *     use ulimit -s unlimited or refine this function without nested.
         */
        splay_tree_destroy_internal(splay_tree_child_left(tree));
        splay_tree_destroy_internal(splay_tree_child_right(tree));
        tree->alias.left = NULL;
        tree->alias.right = NULL;
        splay_tree_node_destroy(tree);
    }
}

void
splay_tree_destroy(struct splay_tree **tree)
{
    if (!complain_null_pointer_p(tree) && !complain_null_pointer_p(*tree)) {
        splay_tree_destroy_internal(*tree);
        *tree = NULL;
    }

}

static inline struct binary_search_tree *
splay_tree_node_find_internal(struct binary_search_tree **tree, sint64 nice,
    struct binary_search_tree *root)
{
    struct binary_search_tree *node;
    struct binary_search_tree *found;

    node = *tree;

    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        if (nice < node->chain.nice) {
            found = splay_tree_node_find_internal(&node->left, nice, root);

            if (NULL != found) {
                splay_tree_balance_splaying_left(tree, root, found);
            }
        } else if (nice > node->chain.nice) {
            found = splay_tree_node_find_internal(&node->right, nice, root);

            if (NULL != found) {
                splay_tree_balance_splaying_right(tree, root, found);
            }
        } else {
            found = node;
        }

        return found;
    }
}

struct splay_tree *
splay_tree_node_find(struct splay_tree **tree, sint64 nice)
{
    struct binary_search_tree *root;
    struct binary_search_tree *found;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)) {
        return NULL;
    } else {
        root = &(*tree)->alias;
        found = splay_tree_node_find_internal(&root, nice, root);
        *tree = splay_tree_ptr_container_of(root);

        return splay_tree_ptr_container_of(found);
    }
}

static inline struct binary_search_tree *
splay_tree_node_find_min_internal(struct binary_search_tree **tree,
    struct binary_search_tree *root)
{
    struct binary_search_tree *min;
    struct binary_search_tree *node;

    assert(NULL != tree);
    assert(NULL != *tree);

    node = *tree;

    if (NULL == node->left) {
        return node;
    } else {
        min = splay_tree_node_find_min_internal(&node->left, root);

        if (node->left->left) {
            splay_tree_balance_single_splaying_left(tree);
        } else if (node == root) {
            splay_tree_balance_root_splaying_left(tree);
        } else {
            assert(min == node->left);
            /*
             *       / 
             *     node
             *     /
             *   min
             *   /
             */
            return min;
        }

        assert(*tree == min);
        return min;
    }
}

struct splay_tree *
splay_tree_node_find_min(struct splay_tree **tree)
{
    struct binary_search_tree *root;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)) {
        return NULL;
    } else {
        root = &(*tree)->alias;
        root = splay_tree_node_find_min_internal(&root, root);
        *tree = splay_tree_ptr_container_of(root);

        return *tree;
    }
}

static inline struct binary_search_tree *
splay_tree_node_find_max_internal(struct binary_search_tree **tree,
    struct binary_search_tree *root)
{
    struct binary_search_tree *max;
    struct binary_search_tree *node;

    assert(NULL != tree);
    assert(NULL != *tree);

    node = *tree;

    if (NULL == node->right) {
        return node;
    } else {
        max = splay_tree_node_find_max_internal(&node->right, root);

        if (node->right->right) {
            splay_tree_balance_single_splaying_right(tree);
        } else if (node == root) {
            splay_tree_balance_root_splaying_right(tree);
        } else {
            assert(max == node->right);
            /*
             *       / 
             *     node
             *     /
             *   min
             *   /
             */
            return max;
        }

        assert(*tree == max);
        return max;
    }
}

struct splay_tree *
splay_tree_node_find_max(struct splay_tree **tree)
{
    struct binary_search_tree *root;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)) {
        return NULL;
    } else {
        root = &(*tree)->alias;
        root = splay_tree_node_find_max_internal(&root, root);
        *tree = splay_tree_ptr_container_of(root);

        return *tree;
    }
}

static inline void
splay_tree_balance_splaying_left(struct binary_search_tree **tree,
    struct binary_search_tree *root,
    struct binary_search_tree *target)
{
    struct binary_search_tree *node;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != (*tree)->left);
    assert(NULL != root);
    assert(NULL != target);

    node = *tree;

    if (node == root && node->left == target) {
        /*
         *    root  <- node
         *     /
         *  target
         */
        splay_tree_balance_root_splaying_left(tree);
    } else if (node->left->left == target) {
        splay_tree_balance_single_splaying_left(tree);
    } else if (node->left->right == target) {
        splay_tree_balance_doubly_splaying_left(tree);
    } else {
        assert(target == node->left);
        return;
    }

    assert(target == *tree);
}

static inline void
splay_tree_balance_splaying_right(struct binary_search_tree **tree,
    struct binary_search_tree *root,
    struct binary_search_tree *target)
{
    struct binary_search_tree *node;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != (*tree)->right);
    assert(NULL != root);
    assert(NULL != target);

    node = *tree;

    if (node == root && node->right == target) {
        /*
         *  root  <- node
         *     \
         *    target
         */
        splay_tree_balance_root_splaying_right(tree);
    } else if (node->right->left == target) {
        splay_tree_balance_doubly_splaying_right(tree);
    } else if (node->right->right == target) {
        splay_tree_balance_single_splaying_right(tree);
    } else {
        assert(target == node->right);
        return;
    }

    assert(target == *tree);
}

static void inline
splay_tree_balance_root_splaying_left(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != (*tree)->left);

    k1 = *tree;
    k2 = k1->left;
    /*
     *     k1          k2
     *    /  \        /  \
     *   k2   c  =>  a    k1
     *  /  \             /  \
     * a    b           b    c
     */
    k1->left = k2->right;
    k2->right = k1;

    *tree = k2;
}

static void inline
splay_tree_balance_root_splaying_right(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;

    assert(NULL != tree);
    assert(NULL != *tree);
    assert(NULL != (*tree)->right);

    k1 = *tree;
    k2 = k1->right;
    /*
     *   k1               k2
     *  /  \             /  \
     * a    k2    =>    k1   c
     *     /  \        /  \
     *    b    c      a    b
     */
    k1->right = k2->left;
    k2->left = k1;

    *tree = k2;
}

static void inline
splay_tree_balance_single_splaying_left(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;

    assert(NULL != tree);
    assert(NULL != (*tree));
    assert(NULL != (*tree)->left);
    assert(NULL != (*tree)->left->left);

    k1 = *tree;
    k2 = k1->left;
    k3 = k2->left;
    /*
     *        k1            k3
     *       /  \          /  \
     *      k2   d   =>   a    k2
     *     /  \               /  \
     *    k3   c             b    k1
     *   /  \                    /  \
     *  a    b                  c    d
     */
    k1->left = k2->right;
    k2->left = k3->right;
    k2->right = k1;
    k3->right = k2;

    *tree = k3;
}

static void inline
splay_tree_balance_single_splaying_right(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;


    assert(NULL != tree);
    assert(NULL != (*tree));
    assert(NULL != (*tree)->right);
    assert(NULL != (*tree)->right->right);

    k1 = *tree;
    k2 = k1->right;
    k3 = k2->right;
    /*
     *     k1                 k3
     *    / \                /  \
     *   a   k2      =>     k2   d
     *      /  \           /  \
     *     b    k3        k1   c
     *         /  \      /  \
     *        c    d    a    b
     */
    k1->right = k2->left;
    k2->right = k3->left;
    k2->left = k1;
    k3->left = k2;

    *tree = k3;
}

static void inline
splay_tree_balance_doubly_splaying_left(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;

    assert(NULL != tree);
    assert(NULL != (*tree));
    assert(NULL != (*tree)->left);
    assert(NULL != (*tree)->left->right);

    k1 = *tree;
    k2 = k1->left;
    k3 = k2->right;
    /*
     *     k1            k3
     *    /  \          /  \
     *   k2   d  =>    k2   k1
     *  / \           / \   / \
     * a   k3        a   b c   d
     *    /  \
     *   b    c
     */
    k1->left = k3->right;
    k2->right = k3->left;
    k3->left = k2;
    k3->right = k1;

    *tree = k3;
}

static void inline
splay_tree_balance_doubly_splaying_right(struct binary_search_tree **tree)
{
    struct binary_search_tree *k1;
    struct binary_search_tree *k2;
    struct binary_search_tree *k3;

    assert(NULL != tree);
    assert(NULL != (*tree));
    assert(NULL != (*tree)->right);
    assert(NULL != (*tree)->right->left);

    k1 = *tree;
    k2 = k1->right;
    k3 = k2->left;
    /*
     *    k1              k3
     *   / \             /  \
     *  a   k2    =>    k1   k2
     *     /  \        / \   / \
     *    k3   c      a   b c   d
     *   /  \
     *  b    c
     */
    k1->right = k3->left;
    k2->left = k3->right;
    k3->left = k1;
    k3->right = k2;

    *tree = k3;
}

sint32
splay_tree_height(struct splay_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return -1;
    } else {
        return binary_search_tree_height_internal(&tree->alias);
    }
}

bool
splay_tree_node_contains_p(struct splay_tree *tree, struct splay_tree *node)
{
    if (complain_null_pointer_p(tree) || complain_null_pointer_p(node)) {
        return false;
    } else {
        return binary_search_tree_node_contains_p_internal(&tree->alias,
            &node->alias);
    }
}

static inline struct binary_search_tree *
splay_tree_node_insert_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node,
    struct binary_search_tree *root)
{
    struct binary_search_tree *tmp;
    struct binary_search_tree *inserted;

    tmp = *tree;

    if (!tmp) {
        *tree = node;
        return node;
    } else {
        if (node->chain.nice < tmp->chain.nice) {
            inserted = splay_tree_node_insert_internal(&tmp->left, node, root);
            splay_tree_balance_splaying_left(tree, root, inserted);
        } else if (node->chain.nice > tmp->chain.nice) {
            inserted = splay_tree_node_insert_internal(&tmp->right, node, root);
            splay_tree_balance_splaying_right(tree, root, inserted);
        } else {
            doubly_linked_list_merge(tmp->chain.link, node->chain.link);
            inserted = tmp;
        }

        return inserted;
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
    struct binary_search_tree *tmp;
    struct binary_search_tree *inserted;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)
        || complain_null_pointer_p(node)) {
        return NULL;
    } else {
        tmp = &(*tree)->alias;
        inserted = splay_tree_node_insert_internal(&tmp, &node->alias, tmp);
        *tree = splay_tree_ptr_container_of(tmp);

        return splay_tree_ptr_container_of(inserted);
    }
}

struct splay_tree *
splay_tree_node_remove_internal(struct splay_tree **tree, sint64 nice)
{
    struct binary_search_tree *tmp;
    struct binary_search_tree *removed;

    assert(NULL != tree);
    assert(NULL != *tree);

    tmp = &(*tree)->alias;
    removed = binary_search_tree_node_remove_internal(&tmp, nice);
    *tree = splay_tree_ptr_container_of(tmp);

    return removed ? splay_tree_ptr_container_of(removed) : NULL;
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
    struct splay_tree *removed;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)) {
        return NULL;
    } else {
        removed = splay_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }

        return removed;
    }
}

void
splay_tree_node_remove_and_destroy(struct splay_tree **tree, sint64 nice)
{
    struct splay_tree *removed;

    if (!complain_null_pointer_p(tree) && !complain_null_pointer_p(*tree)) {
        removed = splay_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        } else {
            splay_tree_node_destroy(removed);
        }
    }
}

void
splay_tree_iterate(struct splay_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (complain_null_pointer_p(tree) || complain_null_pointer_p(handle)) {
        return;
    } else if (!LEGAL_ORDER_P(order)) {
        pr_log_warn("illegal oder type of iterate.\n");
    } else {
        binary_search_tree_iterate_internal(&tree->alias, handle, order);
    }
}

