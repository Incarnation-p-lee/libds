s_avl_tree_t *
avl_tree_left(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_p(tree)) {
        return tree->left;
    } else {
        return PTR_INVALID;
    }
}

s_avl_tree_t *
avl_tree_right(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_p(tree)) {
        return tree->right;
    } else {
        return PTR_INVALID;
    }
}

s_avl_tree_t *
avl_tree_create(void)
{
    s_avl_tree_t *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    avl_tree_initial_i(tree, 0);

    return tree;
}

sint64
avl_tree_nice(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_p(tree)) {
        return tree->nice;
    } else {
        return TREE_NICE_INVALID;
    }
}

static inline void
avl_tree_initial_i(s_avl_tree_t *tree, sint64 nice)
{
    assert_exit(!complain_null_pointer_p(tree));

    tree->height = 0;
    tree->nice = nice;
    tree->left = NULL;
    tree->right = NULL;
}

void
avl_tree_initial(s_avl_tree_t *tree, sint64 nice)
{
    if (!complain_null_pointer_p(tree)) {
        avl_tree_initial_i(tree, nice);
    }
}

static inline bool
avl_tree_structure_legal_p(s_avl_tree_t *tree)
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
avl_tree_destroy_i(s_avl_tree_t *tree)
{
    s_array_queue_t *queue;
    s_avl_tree_t *avl_node;

    assert_exit(avl_tree_structure_legal_p(tree));

    queue = array_queue_create();
    array_queue_enter(queue, tree);

    while (!array_queue_empty_p(queue)) {
        avl_node = array_queue_leave(queue);

        if (avl_node->left != NULL) {
            array_queue_enter(queue, avl_node->left);
        }

        if (avl_node->right != NULL) {
            array_queue_enter(queue, avl_node->right);
        }

        memory_cache_free(avl_node);
    }

    array_queue_destroy(&queue);
}

void
avl_tree_destroy(s_avl_tree_t **tree)
{
    if (complain_null_pointer_p(tree)) {
        return;
    } else if (avl_tree_structure_legal_p(*tree)) {
        avl_tree_destroy_i(*tree);
        *tree = NULL;
    }
}

static inline s_avl_tree_t *
avl_tree_find_i(s_avl_tree_t *tree, sint64 nice)
{
    assert_exit(avl_tree_structure_legal_p(tree));

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

s_avl_tree_t *
avl_tree_find(s_avl_tree_t *tree, sint64 nice)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_i(tree, nice);
    }
}

static inline s_avl_tree_t *
avl_tree_find_min_i(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    while (tree->left) {
        tree = tree->left;
    }

    return tree;
}

s_avl_tree_t *
avl_tree_find_min(s_avl_tree_t *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_min_i(tree);
    }
}

static inline s_avl_tree_t *
avl_tree_find_max_i(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    while (tree->right) {
        tree = tree->right;
    }

    return tree;
}

s_avl_tree_t *
avl_tree_find_max(s_avl_tree_t *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_max_i(tree);
    }
}

static inline bool
avl_tree_contains_ip(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    bool retval;
    s_avl_tree_t *left;
    s_avl_tree_t *right;

    assert_exit(avl_tree_structure_legal_p(tree));
    assert_exit(avl_tree_structure_legal_p(node));

    retval = false;

    while (tree) {
        if (node == tree) {
            return true;
        } else if (node->nice > tree->nice) {
            tree =  tree->right;
        } else if (node->nice < tree->nice) {
            tree = tree->left;
        } else {
            left = tree->left;
            right = tree->right;

            // Handle nice repeated node
            if (left && node->nice == left->nice) {
                retval = avl_tree_contains_ip(left, node);
            }
            if (!retval && right && node->nice == right->nice) {
                retval = avl_tree_contains_ip(right, node);
            }

            return retval;
        }
    }

    return false;
}

bool
avl_tree_contains_p(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return false;
    } else if (!avl_tree_structure_legal_p(node)) {
        return false;
    } else {
        return avl_tree_contains_ip(tree, node);
    }
}

static inline bool
avl_tree_node_balanced_p(s_avl_tree_t *node)
{
    assert_exit(avl_tree_structure_legal_p(node));

    return avl_tree_height_balanced_opt_p(node);
}

static inline bool
avl_tree_balanced_ip(s_avl_tree_t *tree)
{
    if (!tree) {
        return true;
    } else if (!avl_tree_node_balanced_p(tree)) {
        return false;
    } else if (!avl_tree_balanced_ip(tree->left)) {
        return false;
    } else if (!avl_tree_balanced_ip(tree->right)) {
        return false;
    } else {
        return true;
    }
}

bool
avl_tree_balanced_p(s_avl_tree_t *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return true;
    } else {
        return avl_tree_balanced_ip(tree);
    }
}

static inline bool
avl_tree_doubly_child_p(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    if (tree->left && tree->right) {
        return true;
    } else {
        return false;
    }
}

sint32
avl_tree_height(s_avl_tree_t *tree)
{
    if (!avl_tree_structure_legal_p(tree)) {
        return -1;
    } else {
        return avl_tree_height_opt(tree);
    }
}

static inline void
avl_tree_height_update(s_avl_tree_t *tree)
{
    sint32 left;
    sint32 right;

    assert_exit(avl_tree_structure_legal_p(tree));
    // Also height_update_opt

    left = avl_tree_height_opt(tree->left);
    right = avl_tree_height_opt(tree->right);

    tree->height = MAX_S32(left, right) + 1;
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
static inline s_avl_tree_t *
avl_tree_single_rotate_left(s_avl_tree_t *node)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;

    assert_exit(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->left;

    assert_exit(avl_tree_structure_legal_p(k2));
    assert_exit(avl_tree_structure_legal_p(k2->left));
    assert_exit(avl_tree_single_rotate_left_precondition_p(node));

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
static inline s_avl_tree_t *
avl_tree_single_rotate_right(s_avl_tree_t *node)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;

    assert_exit(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->right;

    assert_exit(avl_tree_structure_legal_p(k2));
    assert_exit(avl_tree_structure_legal_p(k2->right));
    assert_exit(avl_tree_single_rotate_right_precondition_p(node));

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
static inline s_avl_tree_t *
avl_tree_doubly_rotate_left(s_avl_tree_t *node)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;
    s_avl_tree_t *k3;

    assert_exit(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->left;

    assert_exit(avl_tree_structure_legal_p(k2));
    assert_exit(avl_tree_structure_legal_p(k2->right));
    assert_exit(avl_tree_doubly_rotate_left_precondition_p(node));

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
static inline s_avl_tree_t *
avl_tree_doubly_rotate_right(s_avl_tree_t *node)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;
    s_avl_tree_t *k3;

    assert_exit(avl_tree_structure_legal_p(node));

    k1 = node;
    k2 = k1->right;

    assert_exit(avl_tree_structure_legal_p(k2));
    assert_exit(avl_tree_structure_legal_p(k2->left));
    assert_exit(avl_tree_doubly_rotate_right_precondition_p(node));

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
avl_tree_rotate_left(s_avl_tree_t **tree)
{
    sint32 left_height;
    sint32 right_height;
    s_avl_tree_t *left;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->left));

    left = (*tree)->left;
    left_height = avl_tree_height_opt(left->left);
    right_height = avl_tree_height_opt(left->right);

    if (left_height >= right_height) {
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
avl_tree_rotate_right(s_avl_tree_t **tree)
{
    sint32 left_height;
    sint32 right_height;
    s_avl_tree_t *right;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->right));

    right = (*tree)->right;
    left_height = avl_tree_height_opt(right->left);
    right_height = avl_tree_height_opt(right->right);

    if (right_height >= left_height) {
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


static inline s_avl_tree_t *
avl_tree_insert_i(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    s_avl_tree_t *avl;
    s_avl_tree_t *inserted;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));

    avl = *tree;
    inserted = node;

    if (avl == node) {
        pr_log_info("Insert node exist, nothing will be done.\n");
        return NULL;
    } else if (node->nice <= avl->nice) { // Always inserted repeated value to left
        if (NULL == avl->left) {
            avl->left = node;
        } else {
            inserted = avl_tree_insert_i(&avl->left, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_left(tree);
            }
        }
    } else { // node->nice > avl->nice
        if (NULL == avl->right) {
            avl->right = node;
        } else {
            inserted = avl_tree_insert_i(&avl->right, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_right(tree);
            }
        }
    }

    avl_tree_height_update(avl);
    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    return inserted;
}

s_avl_tree_t *
avl_tree_insert(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    if (complain_null_pointer_p(tree)) {
        return PTR_INVALID;
    } else if (!avl_tree_structure_legal_p(*tree)) {
        return PTR_INVALID;
    } else if (!avl_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return avl_tree_insert_i(tree, node);
    }
}

static inline void
avl_tree_lt_doubly_child_strip(s_avl_tree_t **pre, s_avl_tree_t *node)
{
    assert_exit(!complain_null_pointer_p(pre));
    assert_exit(avl_tree_structure_legal_p(*pre));
    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(*pre == node);

    if (NULL != node->left) {
        *pre = node->left;
    } else {
        *pre = node->right;
    }

    node->left = NULL;
    node->right = NULL;
}

static inline void
avl_tree_doubly_child_strip(s_avl_tree_t **node_pre)
{
    sint32 left_height;
    sint32 right_height;
    s_avl_tree_t *avl;

    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(avl_tree_structure_legal_p(*node_pre));

    avl = *node_pre;
    left_height = avl_tree_height_opt(avl->left);
    right_height = avl_tree_height_opt(avl->right);

    if (left_height < right_height) {
        avl_tree_doubly_child_strip_from_max(node_pre);
    } else {
        avl_tree_doubly_child_strip_from_min(node_pre);
    }
}

// Fix me cmpxchange ?
static inline void
avl_tree_swap_child(s_avl_tree_t *a, s_avl_tree_t *b)
{
    void *tmp;
    sint32 height;

    assert_exit(avl_tree_structure_legal_p(a));
    assert_exit(avl_tree_structure_legal_p(b));

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

static inline s_avl_tree_t **
avl_tree_find_ptr_to_max(s_avl_tree_t **tree)
{
    s_avl_tree_t *avl;
    s_avl_tree_t **max;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_doubly_child_p(*tree));

    max = tree;
    avl = *max;

    while (NULL != avl->right) {
        max = &avl->right;
        avl = *max;
    }

    return max;
}

static inline s_avl_tree_t **
avl_tree_find_ptr_to_min(s_avl_tree_t **tree)
{
    s_avl_tree_t *avl;
    s_avl_tree_t **min;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_doubly_child_p(*tree));

    min = tree;
    avl = *min;

    while (NULL != avl->left) {
        min = &avl->left;
        avl = *min;
    }

    return min;
}

static inline void
avl_tree_doubly_child_strip_from_max(s_avl_tree_t **node_pre)
{
    void *tmp;
    s_avl_tree_t *avl;
    s_avl_tree_t *max;
    s_avl_tree_t **max_pre;

    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(avl_tree_structure_legal_p(*node_pre));
    assert_exit(avl_tree_doubly_child_p(*node_pre));

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

    avl_tree_remove_i(&max->left, avl);
}

static inline void
avl_tree_doubly_child_strip_from_min(s_avl_tree_t **node_pre)
{
    void *tmp;
    s_avl_tree_t *avl;
    s_avl_tree_t *min;
    s_avl_tree_t **min_pre;

    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(avl_tree_structure_legal_p(*node_pre));
    assert_exit(avl_tree_doubly_child_p(*node_pre));

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

    avl_tree_remove_i(&min->right, avl);
}

static inline s_avl_tree_t *
avl_tree_remove_i(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    s_avl_tree_t *avl;
    s_avl_tree_t *removed;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_structure_legal_p(node));

    avl = *tree;
    removed = NULL;

    if (node->nice < avl->nice) {
        if (NULL == avl->left) {
            pr_log_warn("Failed to find the node in given tree.\n");
            return NULL;
        } else {
            removed = avl_tree_remove_i(&avl->left, node);
            if (!avl_tree_node_balanced_p(avl)) {
                avl_tree_rotate_right(tree);
            }
            avl_tree_height_update(avl);
        }
    } else if (node->nice > avl->nice) {
        if (NULL == avl->right) {
            pr_log_warn("Failed to find the node in given tree.\n");
            return NULL;
        } else {
            removed = avl_tree_remove_i(&avl->right, node);
            if (!avl_tree_node_balanced_p(avl)) {
                 avl_tree_rotate_left(tree);
            }
            avl_tree_height_update(avl);
        }
    } else if (node != avl) {
        if (avl->left && node->nice == avl->left->nice) {
            removed = avl_tree_remove_i(&avl->left, node);
            avl_tree_height_update(avl);
        }
        if (!removed && avl->right && node->nice == avl->right->nice) {
            removed = avl_tree_remove_i(&avl->right, node);
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

    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));

    return removed;
}

s_avl_tree_t *
avl_tree_remove(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    if (complain_null_pointer_p(tree)) {
        return PTR_INVALID;
    } else if (!avl_tree_structure_legal_p(*tree)) {
        return PTR_INVALID;
    } else if (!avl_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return avl_tree_remove_i(tree, node);
    }
}

static inline void
avl_tree_iterate_i(s_avl_tree_t *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert_exit(LEGAL_ORDER_P(order));
    assert_exit(!complain_null_pointer_p(handle));

    if (tree) {
        if (ORDER_PRE == order) {
            handle(tree);
        }

        avl_tree_iterate_i(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(tree);
        }

        avl_tree_iterate_i(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(tree);
        }
    }
}

void
avl_tree_iterate(s_avl_tree_t *tree,
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
        avl_tree_iterate_i(tree, handle, order);
    }
}

