sint64
splay_tree_nice(struct splay_tree *tree)
{
    if (!splay_tree_structure_legal_p(tree)) {
        return (sint64)1 << 63;
    } else {
        return tree->nice;
    }
}

struct splay_tree *
splay_tree_left(struct splay_tree *tree)
{
    if (!splay_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return tree->left;
    }
}

struct splay_tree *
splay_tree_right(struct splay_tree *tree)
{
    if (!splay_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return tree->right;
    }
}

static inline bool
splay_tree_structure_legal_p(struct splay_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return false;
    } else if (tree->left == tree->right && NULL != tree->left) {
        return false;
    } else {
        return true;
    }
}

static inline void
splay_tree_initial_internal(struct splay_tree *tree, sint64 nice)
{
     assert(splay_tree_structure_legal_p(tree));

     tree->left = NULL;
     tree->right = NULL;
     tree->nice = nice;
}

struct splay_tree *
splay_tree_create(void)
{
    struct splay_tree *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    splay_tree_initial_internal(tree, (sint64)0);

    return tree;
}

void
splay_tree_initial(struct splay_tree *tree, sint64 nice)
{
    if (splay_tree_structure_legal_p(tree)) {
        splay_tree_initial_internal(tree, nice);
    }
}

static inline void
splay_tree_node_destroy(struct splay_tree *node)
{
    assert(splay_tree_structure_legal_p(node));
    assert(NULL == node->left);
    assert(NULL == node->right);

    memory_cache_free(node);
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
        splay_tree_destroy_internal(tree->left);
        splay_tree_destroy_internal(tree->right);

        tree->left = NULL;
        tree->right = NULL;

        splay_tree_node_destroy(tree);
    }
}

void
splay_tree_destroy(struct splay_tree **tree)
{
    if (complain_null_pointer_p(tree)) {
        return;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return;
    } else {
        splay_tree_destroy_internal(*tree);
        *tree = NULL;
    }
}

static inline struct splay_tree *
splay_tree_find_internal(struct splay_tree **tree, sint64 nice,
    struct splay_tree *root)
{
    struct splay_tree *splay;
    struct splay_tree *found;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(root));

    found = NULL;
    splay = *tree;

    if (complain_null_pointer_p(splay)) {
        return NULL;
    } else {
        if (nice < splay->nice) {
            found = splay_tree_find_internal(&splay->left, nice, root);
            if (NULL != found) {
                splay_tree_balance_splaying_left(tree, root, found);
            }
        } else if (nice > splay->nice) {
            found = splay_tree_find_internal(&splay->right, nice, root);
            if (NULL != found) {
                splay_tree_balance_splaying_right(tree, root, found);
            }
        } else {
            found = splay;
        }

        return found;
    }
}

struct splay_tree *
splay_tree_find(struct splay_tree **tree, sint64 nice)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else {
        return splay_tree_find_internal(tree, nice, *tree);
    }
}

static inline struct splay_tree *
splay_tree_find_min_internal(struct splay_tree **tree,
    struct splay_tree *root)
{
    struct splay_tree *min;
    struct splay_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p(root));

    node = *tree;

    if (NULL == node->left) {
        return node;
    } else {
        min = splay_tree_find_min_internal(&node->left, root);

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
splay_tree_find_min(struct splay_tree **tree)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else {
        return splay_tree_find_min_internal(tree, *tree);
    }
}

static inline struct splay_tree *
splay_tree_find_max_internal(struct splay_tree **tree,
    struct splay_tree *root)
{
    struct splay_tree *max;
    struct splay_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p(root));

    node = *tree;

    if (NULL == node->right) {
        return node;
    } else {
        max = splay_tree_find_max_internal(&node->right, root);

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
splay_tree_find_max(struct splay_tree **tree)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else {
        return splay_tree_find_max_internal(tree, *tree);
    }
}

static inline void
splay_tree_balance_splaying_left(struct splay_tree **tree,
    struct splay_tree *root, struct splay_tree *target)
{
    struct splay_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p(root));
    assert(splay_tree_structure_legal_p(target));
    assert(splay_tree_structure_legal_p((*tree)->left));

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
splay_tree_balance_splaying_right(struct splay_tree **tree,
    struct splay_tree *root, struct splay_tree *target)
{
    struct splay_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p(root));
    assert(splay_tree_structure_legal_p(target));
    assert(splay_tree_structure_legal_p((*tree)->right));

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
splay_tree_balance_root_splaying_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->left));

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
splay_tree_balance_root_splaying_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->right));

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
splay_tree_balance_single_splaying_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->left));
    assert(splay_tree_structure_legal_p((*tree)->left->left));

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
splay_tree_balance_single_splaying_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->right));
    assert(splay_tree_structure_legal_p((*tree)->right->right));

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
splay_tree_balance_doubly_splaying_left(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->left));
    assert(splay_tree_structure_legal_p((*tree)->left->right));

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
splay_tree_balance_doubly_splaying_right(struct splay_tree **tree)
{
    struct splay_tree *k1;
    struct splay_tree *k2;
    struct splay_tree *k3;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_structure_legal_p((*tree)->right));
    assert(splay_tree_structure_legal_p((*tree)->right->left));

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

static inline sint32
splay_tree_height_internal(struct splay_tree *tree)
{
    sint32 left;
    sint32 right;

    if (!tree) {
        return -1;
    } else {
        left = splay_tree_height_internal(tree->left);
        right = splay_tree_height_internal(tree->right);

        return MAX_S(left, right) + 1;
    }
}

sint32
splay_tree_height(struct splay_tree *tree)
{
    if (!splay_tree_structure_legal_p(tree)) {
        return -1;
    } else {
        return splay_tree_height_internal(tree);
    }
}

static inline bool
splay_tree_contains_p_internal(struct splay_tree *tree, struct splay_tree *node)
{
    bool retval;
    sint64 nice;
    struct splay_tree *left;
    struct splay_tree *right;

    assert(splay_tree_structure_legal_p(tree));
    assert(splay_tree_structure_legal_p(node));

    retval = false;
    nice = node->nice;

    while (tree) {
        if (node == tree) {
            return true;
        } else if (nice > tree->nice) {
            tree = tree->right;
        } else if (nice < tree->nice) {
            tree = tree->left;
        } else {
            left = tree->left;
            right = tree->right;

            // Handle repeated nice
            if (left && nice == left->nice) {
                retval = splay_tree_contains_p_internal(left, node);
            }
            if (!retval && right && nice == right->nice) {
                retval = splay_tree_contains_p_internal(right, node);
            }

            return retval;
        }
    }

    return false;
}

bool
splay_tree_contains_p(struct splay_tree *tree, struct splay_tree *node)
{
    if (!splay_tree_structure_legal_p(tree)) {
        return false;
    } else if (!splay_tree_structure_legal_p(node)) {
        return false;
    } else {
        return splay_tree_contains_p_internal(tree, node);
    }
}

static inline struct splay_tree *
splay_tree_insert_internal(struct splay_tree **tree,
    struct splay_tree *node, struct splay_tree *root)
{
    struct splay_tree *splay;
    struct splay_tree *inserted;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_ordered_p(*tree));
    assert(splay_tree_structure_legal_p(node));
    assert(splay_tree_structure_legal_p(root));

    if (!*tree) {
        return *tree = node;
    } else {
        splay = *tree;
        if (node->nice < splay->nice) {
            inserted = splay_tree_insert_internal(&splay->left, node, root);
            splay_tree_balance_splaying_left(tree, root, inserted);
        } else if (node->nice > splay->nice) {
            inserted = splay_tree_insert_internal(&splay->right, node, root);
            splay_tree_balance_splaying_right(tree, root, inserted);
        } else if (splay != node) {
            // Repeated nice, insert it to right
            inserted = splay_tree_insert_internal(&splay->right, node, root);
            splay_tree_balance_splaying_right(tree, root, inserted);
        } else {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            return NULL;
        }

        assert(splay_tree_ordered_p(*tree));
        return inserted;
    }
}

struct splay_tree *
splay_tree_insert(struct splay_tree **tree, struct splay_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(node)) {
        return INVALID_PTR;
    } else {
        return splay_tree_insert_internal(tree, node, *tree);
    }
}

static inline bool
splay_tree_doubly_child_p(struct splay_tree *node)
{
    assert(splay_tree_structure_legal_p(node));

    if (node->left && node->right) {
        return true;
    } else {
        return false;
    }
}

static inline void
splay_tree_lt_doubly_child_strip(struct splay_tree **pre,
    struct splay_tree *node)
{
    assert(!complain_null_pointer_p(pre));
    assert(splay_tree_structure_legal_p(node));
    assert(splay_tree_structure_legal_p(*pre));
    assert(!splay_tree_doubly_child_p(node));
    assert(*pre == node);

    if (NULL != node->left) {
        *pre = node->left;
    } else {
        *pre = node->right;
    }

    node->left = NULL;
    node->right = NULL;
}

static inline struct splay_tree **
splay_tree_find_ptr_to_min(struct splay_tree **tree)
{
    struct splay_tree **min;
    struct splay_tree *splay;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));

    min = tree;
    splay = *min;

    while (splay->left) {
        min = &splay->left;
        splay = *min;
    }

    return min;
}

static inline void
splay_tree_swap_child(struct splay_tree *a, struct splay_tree *b)
{
    void *tmp;

    assert(splay_tree_structure_legal_p(a));
    assert(splay_tree_structure_legal_p(b));

    tmp = a->left;
    a->left = b->left;
    b->left = tmp;

    tmp = a->right;
    a->right = b->right;
    b->right = tmp;
}

static inline void
splay_tree_doubly_child_strip(struct splay_tree **pre)
{
    struct splay_tree *splay;
    struct splay_tree *min;
    struct splay_tree **min_pre;

    assert(!complain_null_pointer_p(pre));
    assert(splay_tree_structure_legal_p(*pre));
    assert(splay_tree_doubly_child_p(*pre));

    splay = *pre;

    if (!splay->right->left) {
        // short cut here
        *pre = splay->right;
        splay->right->left = splay->left;
        splay->left = splay->right = NULL;
    } else {
        min_pre = splay_tree_find_ptr_to_min(&splay->right);
        min = *min_pre;

        splay_tree_swap_child(splay, min);
        *min_pre = splay;
        *pre = min;

        splay_tree_lt_doubly_child_strip(min_pre, splay);
    }
}

static inline struct splay_tree *
splay_tree_remove_internal(struct splay_tree **tree,
    struct splay_tree *node)
{
    struct splay_tree *splay;
    struct splay_tree *removed;
    struct splay_tree **pre;

    assert(!complain_null_pointer_p(tree));
    assert(splay_tree_structure_legal_p(*tree));
    assert(splay_tree_ordered_p(*tree));
    assert(splay_tree_structure_legal_p(node));

    pre = tree;
    splay = *pre;
    removed = NULL;

    while (splay) {
        if (node->nice > splay->nice) {
            pre = &splay->right;
        } else if (node->nice < splay->nice) {
            pre = &splay->left;
        } else if (splay != node) {
            if (splay->left && node->nice == splay->left->nice) {
                removed = splay_tree_remove_internal(&splay->left, node);
            }
            if (!removed && splay->right && node->nice == splay->right->nice) {
                removed = splay_tree_remove_internal(&splay->right, node);
            }
            break;
        } else if (splay_tree_doubly_child_p(splay)) {
            splay_tree_doubly_child_strip(pre);
            return splay;
        } else {
            splay_tree_lt_doubly_child_strip(pre, splay);
            return splay;
        }
        splay = *pre;
    }

    if (NULL == removed) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert(splay_tree_ordered_p(*tree));
    return removed;
}

struct splay_tree *
splay_tree_remove(struct splay_tree **tree, struct splay_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else if (!splay_tree_structure_legal_p(node)) {
        return INVALID_PTR;
    } else {
        return splay_tree_remove_internal(tree, node);
    }
}

static inline void
splay_tree_iterate_internal(struct splay_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert(LEGAL_ORDER_P(order));
    assert(!complain_null_pointer_p(handle));

    if (tree) {
        if (ORDER_PRE == order) {
            handle(tree);
        }

        splay_tree_iterate_internal(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(tree);
        }

        splay_tree_iterate_internal(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(tree);
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
        splay_tree_iterate_internal(tree, handle, order);
    }
}

