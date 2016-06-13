struct avl_tree *
avl_tree_create(void)
{
    struct avl_tree *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    avl_tree_initial_internal(tree, 0);

    return tree;
}

static inline void
avl_tree_initial_internal(struct avl_tree *tree, sint64 nice)
{
    assert(!complain_null_pointer_p(tree));

    tree->height = 0;
    tree->nice = nice;
    tree->left = NULL;
    tree->right = NULL;
}

void
avl_tree_initial(struct avl_tree *tree, sint64 nice)
{
    if (avl_tree_structure_legal_p(tree)) {
        avl_tree_initial_internal(tree, nice);
    }
}

static inline bool
avl_tree_structure_legal_p(struct avl_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return false;
    } else if (tree->left == tree->right && NULL != tree->left) {
        return false;
    } else if (tree->left == tree || tree->right == tree) {
        return false;
    } else {
        return true;
    }
}

static inline void
avl_tree_node_destroy(struct avl_tree *node)
{
    assert(avl_tree_structure_legal_p(node));

    memory_cache_free(node);
}

static inline void
avl_tree_destroy_internal(struct avl_tree *tree)
{
    /*
     * destroy node in post iterater order.
     * Warning: sometime if nested function call is too deepth,
     *     it may reach the default limitation of elf stack size, 8192KB.
     *     use ulimit -s unlimited or refine this function without nested.
     */
    if (tree) {
        avl_tree_destroy_internal(tree->left);
        tree->left = NULL;

        avl_tree_destroy_internal(tree->right);
        tree->right = NULL;

        avl_tree_node_destroy(tree);
    }
}

void
avl_tree_destroy(struct avl_tree **tree)
{
    if (!complain_null_pointer_p(tree) && avl_tree_structure_legal_p(*tree)) {
        avl_tree_destroy_internal(*tree);
        *tree = NULL;
    }
}

static inline struct avl_tree *
avl_tree_find_internal(struct avl_tree *tree, sint64 nice)
{
    assert(avl_tree_structure_legal_p(tree));

    while (tree) {
        if (nice < tree->nice) {
            tree = tree->left;
        } else if (nice > tree->nice) {
            tree = tree->right;
        } else {
            return tree;
        }
    }

    return NULL;
}

struct avl_tree *
avl_tree_find(struct avl_tree *tree, sint64 nice)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return avl_tree_find_internal(tree, nice);
    }
}

static inline struct avl_tree *
avl_tree_find_min_internal(struct avl_tree *tree)
{
    assert(avl_tree_structure_legal_p(tree));

    while (tree->left) {
        tree = tree->left;
    }

    return tree;
}

struct avl_tree *
avl_tree_find_min(struct avl_tree *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return avl_tree_find_min_internal(tree);
    }
}

static inline struct avl_tree *
avl_tree_find_max_internal(struct avl_tree *tree)
{
    assert(avl_tree_structure_legal_p(tree));

    while (tree->right) {
        tree = tree->right;
    }

    return tree;
}

struct avl_tree *
avl_tree_find_max(struct avl_tree *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return avl_tree_find_max_internal(tree);
    }
}

static inline bool
avl_tree_contains_p_internal(struct avl_tree *tree, struct avl_tree *node)
{
    bool retval;
    sint64 nice;
    struct avl_tree *left;
    struct avl_tree *right;

    assert(avl_tree_structure_legal_p(tree));
    assert(avl_tree_structure_legal_p(node));

    retval = false;
    nice = node->nice;

    while (tree) {
        if (node == tree) {
            return true;
        } else if (nice > tree->nice) {
            tree =  tree->right;
        } else if (nice < tree->nice) {
            tree = tree->left;
        } else {
            left = tree->left;
            right = tree->right;

            // Handle repeated nice
            if (left && nice == left->nice) {
                retval = avl_tree_contains_p_internal(left, node);
            }
            if (!retval && right && nice == right->nice) {
                retval = avl_tree_contains_p_internal(right, node);
            }

            return retval;
        }
    }

    return false;
}

bool
avl_tree_contains_p(struct avl_tree *tree, struct avl_tree *node)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return false;
    } else if (!avl_tree_structure_legal_p(node)) {
        return false;
    } else {
        return avl_tree_contains_p_internal(tree, node);
    }
}

static inline bool
avl_tree_height_balanced_p(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    assert(avl_tree_structure_legal_p(tree));

    left = avl_tree_height_internal(tree->left);
    right = avl_tree_height_internal(tree->right);
    assert(avl_tree_height_sync_with_calculated_p(tree, left, right));

    if (abs_sint32(left - right) > 1) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_node_balanced_p(struct avl_tree *node)
{
    bool balanced;

    assert(avl_tree_structure_legal_p(node));

    balanced = avl_tree_height_balanced_p(node);
    // avl_tree_node_balanced_optimize(node, balanced);

    assert(avl_tree_node_balanced_optimize_validity_p(node, balanced));

    return balanced;
}

static inline bool
avl_tree_balanced_p_internal(struct avl_tree *tree)
{
    if (!tree) {
        return true;
    } else if (!avl_tree_node_balanced_p(tree)) {
        return false;
    } else if (!avl_tree_balanced_p_internal(tree->left)) {
        return false;
    } else if (!avl_tree_balanced_p_internal(tree->right)) {
        return false;
    } else {
        return true;
    }
}

bool
avl_tree_balanced_p(struct avl_tree *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return true;
    } else {
        return avl_tree_balanced_p_internal(tree);
    }
}

static inline bool
avl_tree_doubly_child_p(struct avl_tree *tree)
{
    assert(avl_tree_structure_legal_p(tree));

    if (tree->left && tree->right) {
        return true;
    } else {
        return false;
    }
}

sint32
avl_tree_height(struct avl_tree *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return -1; // Fix-Me
    } else {
        return avl_tree_height_internal(tree);
    }
}

static inline sint32
avl_tree_height_internal(struct avl_tree *tree)
{
    if (!tree) {
        return -1;
    } else {
        return tree->height;
    }
    // avl_tree_height_internal_optimize(tree, height);
    // assert(avl_tree_height_optimize_validity_p(tree, height));
}

static inline void
avl_tree_height_update(struct avl_tree *tree)
{
    sint32 left;
    sint32 right;

    assert(avl_tree_structure_legal_p(tree));

    left = avl_tree_height_internal(tree->left);
    right = avl_tree_height_internal(tree->right);

    tree->height = MAX_S(left, right) + 1;
}

/*
 *        k1                   k2
 *       /  \                 /  \
 *      k2   c               k3   k1
 *     /  \         ==>     /    /  \
 *    k3   b               a1   b    c
 *   /
 *  a1
 * perform the singe rotation, with left hand.
 */
static inline struct avl_tree *
avl_tree_single_rotate_left(struct avl_tree *node)
{
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->left;

    assert(avl_tree_structure_legal_p(k2));
    assert(avl_tree_structure_legal_p(k2->left));
    assert(avl_tree_single_rotate_left_precondition_p(node));

    k1->left = k2->right;
    k2->right = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

    return k2;
}

/*
 *        k1                     k2
 *       /  \                   /  \
 *      c    k2                k1   k3
 *          /  \      ==>     /  \   \
 *         b    k3           c    b   a1
 *               \
 *                a1
 * perform the singe rotation, with right hand.
 */
static inline struct avl_tree *
avl_tree_single_rotate_right(struct avl_tree *node)
{
    struct avl_tree *k1;
    struct avl_tree *k2;

    assert(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->right;

    assert(avl_tree_structure_legal_p(k2));
    assert(avl_tree_structure_legal_p(k2->right));
    assert(avl_tree_single_rotate_right_precondition_p(node));

    k1->right = k2->left;
    k2->left = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

    return k2;
}

/*
 *        k1                 k3
 *       /  \               /  \
 *      k2   b             k2   k1
 *     /  \       ==>     / \     \
 *    a    k3            a   a1    b
 *        /
 *       a1
 * perform the doubly rotation, with left hand.
 */
static inline struct avl_tree *
avl_tree_doubly_rotate_left(struct avl_tree *node)
{
    struct avl_tree *k1;
    struct avl_tree *k2;
    struct avl_tree *k3;

    assert(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->left;

    assert(avl_tree_structure_legal_p(k2));
    assert(avl_tree_structure_legal_p(k2->right));
    assert(avl_tree_doubly_rotate_left_precondition_p(node));

    k3 = k2->right;

    k2->right = k3->left;
    k1->left = k3->right;

    k3->left = k2;
    k3->right = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

    return k3;
}

/*
 *        k1                   k3
 *       /  \                 /  \
 *      a    k2              k1   k2
 *          / \     ==>     / \     \
 *         k3  b           a   a1    b
 *        /
 *       a1
 * perform the doubly rotation, with right hand.
 */
static inline struct avl_tree *
avl_tree_doubly_rotate_right(struct avl_tree *node)
{
    struct avl_tree *k1;
    struct avl_tree *k2;
    struct avl_tree *k3;

    assert(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->right;

    assert(avl_tree_structure_legal_p(k2));
    assert(avl_tree_structure_legal_p(k2->left));
    assert(avl_tree_doubly_rotate_right_precondition_p(node));

    k3 = k2->left;

    k2->left = k3->right;
    k1->right = k3->left;

    k3->right = k2;
    k3->left = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

    return k3;
}

static inline void
avl_tree_rotate_left(struct avl_tree **tree)
{
    sint32 l_ht;
    sint32 r_ht;
    struct avl_tree *left;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_structure_legal_p((*tree)->left));

    left = (*tree)->left;
    l_ht = avl_tree_height_internal(left->left);
    r_ht = avl_tree_height_internal(left->right);

    if (l_ht >= r_ht) {
        /*
         *      k1   <== *tree
         *     /  \
         *    k2   c
         *   /  \
         *  k3   b
         */
        *tree = avl_tree_single_rotate_left(*tree);
    } else {
        /*
         *     k1   <== *tree
         *    /  \
         *   k2   c
         *    \
         *     k3
        */
        *tree =  avl_tree_doubly_rotate_left(*tree);
    }
}

static inline void
avl_tree_rotate_right(struct avl_tree **tree)
{
    sint32 l_ht;
    sint32 r_ht;
    struct avl_tree *right;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_structure_legal_p((*tree)->right));

    right = (*tree)->right;
    l_ht = avl_tree_height_internal(right->left);
    r_ht = avl_tree_height_internal(right->right);

    if (r_ht >= l_ht) {
        /*
         * k1      <== *tree
         *   \
         *    k2
         *     \
         *      k3
         */
        *tree = avl_tree_single_rotate_right(*tree);
    } else {
        /*
         * k1
         *   \
         *    k2
         *   /
         * k3
         */
        *tree = avl_tree_doubly_rotate_right(*tree);
    }
}


static inline struct avl_tree *
avl_tree_insert_internal(struct avl_tree **tree, struct avl_tree *node)
{
    sint64 nice;
    struct avl_tree *avl;
    struct avl_tree *tmp;
    struct avl_tree *inserted;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_structure_legal_p(node));
    assert(avl_tree_balanced_p(*tree));
    assert(avl_tree_ordered_p(*tree));
    assert(0 == node->height);

    avl = *tree;
    inserted = node;
    nice = node->nice;

    if (nice < avl->nice) {
        if (NULL == avl->left) {
            avl->left = node;
        } else {
            inserted = avl_tree_insert_internal(&avl->left, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_left(tree);
            }
        }
        avl_tree_height_update(avl);
    } else if (nice > avl->nice) {
        if (NULL == avl->right) {
            avl->right = node;
        } else {
            inserted = avl_tree_insert_internal(&avl->right, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_right(tree);
            }
        }
        avl_tree_height_update(avl);
    } else if (avl == node) {
        pr_log_info("Insert node exist, nothing will be done.\n");
        inserted = NULL;
    } else {
        if (NULL == avl->left) {
            avl->left = node;
        } else if (NULL == avl->right) {
            avl->right = node;
        } else {
            // Always inserted repeated value to left
            inserted = avl_tree_insert_internal(&avl->left, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_left(tree);
            }
        }
        avl_tree_height_update(avl);
    }

    assert(avl_tree_ordered_p(*tree));
    assert(avl_tree_balanced_p(*tree));

    return inserted;
}

/*
 * If INVALID input
 *     return INVALID_PTR
 * else If node exist in given tree
 *     return NULL
 * else
 *     return node
 */
struct avl_tree *
avl_tree_insert(struct avl_tree **tree, struct avl_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!avl_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else if (!avl_tree_structure_legal_p(node)) {
        return INVALID_PTR;
    } else {
        node->height = 0;
        return avl_tree_insert_internal(tree, node);
    }
}

static inline void
avl_tree_lt_doubly_child_strip(struct avl_tree **pre, struct avl_tree *node)
{
    assert(!complain_null_pointer_p(pre));
    assert(avl_tree_structure_legal_p(*pre));
    assert(avl_tree_structure_legal_p(node));
    assert(*pre == node);

    if (NULL != node->left) {
        *pre = node->left;
    } else {
        *pre = node->right;
    }

    node->left = NULL;
    node->right = NULL;
}

static inline void
avl_tree_doubly_child_strip(struct avl_tree **node_pre)
{
    sint32 l_ht;
    sint32 r_ht;
    struct avl_tree *avl;

    assert(!complain_null_pointer_p(node_pre));
    assert(avl_tree_structure_legal_p(*node_pre));

    avl = *node_pre;
    l_ht = avl_tree_height_internal(avl->left);
    r_ht = avl_tree_height_internal(avl->right);

    if (l_ht < r_ht) {
        avl_tree_doubly_child_strip_from_max(node_pre);
    } else {
        avl_tree_doubly_child_strip_from_min(node_pre);
    }
}

static inline void
avl_tree_swap_child(struct avl_tree *a, struct avl_tree *b)
{
     void *tmp;
     sint32 height;

     assert(avl_tree_structure_legal_p(a));
     assert(avl_tree_structure_legal_p(b));

     tmp = a->left;
     a->left = b->left;
     b->left = tmp;

     tmp = a->right;
     a->right = b->right;
     b->right = tmp;

     height = a->height;
     a->height = b->height;
     b->height = height;
}

static inline struct avl_tree **
avl_tree_find_ptr_to_max(struct avl_tree **tree)
{
    struct avl_tree *avl;
    struct avl_tree **max;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_doubly_child_p(*tree));

    max = tree;
    avl = *max;

    while (NULL != avl->right) {
        max = &avl->right;
        avl = *max;
    }

    return max;
}

static inline struct avl_tree **
avl_tree_find_ptr_to_min(struct avl_tree **tree)
{
    struct avl_tree *avl;
    struct avl_tree **min;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_doubly_child_p(*tree));

    min = tree;
    avl = *min;

    while (NULL != avl->left) {
        min = &avl->left;
        avl = *min;
    }

    return min;
}

static inline void
avl_tree_doubly_child_strip_from_max(struct avl_tree **node_pre)
{
    void *tmp;
    struct avl_tree *avl;
    struct avl_tree *max;
    struct avl_tree **max_pre;

    assert(!complain_null_pointer_p(node_pre));
    assert(avl_tree_structure_legal_p(*node_pre));
    assert(avl_tree_doubly_child_p(*node_pre));

    avl = *node_pre;

    if (!avl->left->right) {
         *node_pre = avl->left;
         tmp = avl->left->left;
         avl->left->right = avl->right;
         avl->left->left = avl;

         avl->left = tmp;
         avl->right = NULL;
    } else {
         max_pre = avl_tree_find_ptr_to_max(&avl->left);
         max = *max_pre;

         avl_tree_swap_child(avl, max);
         *max_pre = avl;
         *node_pre = max;
    }

    avl_tree_remove_internal(&max->left, avl);
}

static inline void
avl_tree_doubly_child_strip_from_min(struct avl_tree **node_pre)
{
    void *tmp;
    struct avl_tree *avl;
    struct avl_tree *min;
    struct avl_tree **min_pre;

    assert(!complain_null_pointer_p(node_pre));
    assert(avl_tree_structure_legal_p(*node_pre));
    assert(avl_tree_doubly_child_p(*node_pre));

    avl = *node_pre;

    if (!avl->right->left) {
         *node_pre = avl->right;
         tmp = avl->right->right;
         avl->right->left = avl->left;
         avl->right->right = avl;

         avl->right = tmp;
         avl->left = NULL;
    } else {
         min_pre = avl_tree_find_ptr_to_min(&avl->right);
         min = *min_pre;

         avl_tree_swap_child(avl, min);
         *min_pre = avl;
         *node_pre = min;
    }

    avl_tree_remove_internal(&min->right, avl);
}

static inline struct avl_tree *
avl_tree_remove_internal(struct avl_tree **tree, struct avl_tree *node)
{
    sint64 nice;
    struct avl_tree *avl;
    struct avl_tree *removed;

    assert(!complain_null_pointer_p(tree));
    assert(avl_tree_structure_legal_p(*tree));
    assert(avl_tree_balanced_p(*tree));
    assert(avl_tree_ordered_p(*tree));
    assert(avl_tree_structure_legal_p(node));

    avl = *tree;
    removed = NULL;
    nice = avl_tree_nice(node);

    if (nice < avl->nice) {
        if (NULL == avl->left) {
            pr_log_warn("Failed to find the node in given tree.\n");
            return NULL;
        } else {
            removed = avl_tree_remove_internal(&avl->left, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_right(tree);
            }
            avl_tree_height_update(avl);
        }
    } else if (nice > avl->nice) {
        if (NULL == avl->right) {
            pr_log_warn("Failed to find the node in given tree.\n");
            return NULL;
        } else {
            removed = avl_tree_remove_internal(&avl->right, node);
            if (!avl_tree_node_balanced_p(avl)) {
                 avl_tree_rotate_left(tree);
            }
            avl_tree_height_update(avl);
        }
    } else if (node != avl) {
        if (avl->left && nice == avl->left->nice) {
            removed = avl_tree_remove_internal(&avl->left, node);
            avl_tree_height_update(avl);
        }
        if (!removed && avl->right && nice == avl->right->nice) {
            removed = avl_tree_remove_internal(&avl->right, node);
            avl_tree_height_update(avl);
        }
        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }
    } else {
        removed = node;
        if (avl_tree_doubly_child_p(node)) {
            avl_tree_doubly_child_strip(tree);
        } else {
            avl_tree_lt_doubly_child_strip(tree, node);
        }
        avl_tree_height_update(avl);
    }

    assert(avl_tree_balanced_p(*tree));
    assert(avl_tree_ordered_p(*tree));

    return removed;
}

/*
 * If INVALID input
 *     return INVALID_PTR
 * else If node _DO_ _NOT_ exist in given tree
 *     return NULL
 * else
 *     return node
 */
struct avl_tree *
avl_tree_remove(struct avl_tree **tree, struct avl_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!avl_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else if (!avl_tree_structure_legal_p(node)) {
        return INVALID_PTR;
    } else {
        return avl_tree_remove_internal(tree, node);
    }
}

static inline void
avl_tree_iterate_internal(struct avl_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert(LEGAL_ORDER_P(order));
    assert(!complain_null_pointer_p(handle));

    if (tree) {
        if (ORDER_PRE == order) {
            handle(tree);
        }

        avl_tree_iterate_internal(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(tree);
        }

        avl_tree_iterate_internal(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(tree);
        }
    }
}

void
avl_tree_iterate(struct avl_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (complain_null_pointer_p(handle)) {
        return;
    } else if (!avl_tree_structure_legal_p(tree)) {
        return;
    } else if (!LEGAL_ORDER_P(order)) {
        pr_log_warn("Invalid value of enum ITER_ORDER.\n");
        return;
    } else {
        avl_tree_iterate_internal(tree, handle, order);
    }
}

