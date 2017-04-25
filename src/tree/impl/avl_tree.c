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
    assert_exit(!NULL_PTR_P(tree));

    tree->height = 0;
    tree->nice = nice;
    tree->left = tree->right = NULL;
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
    if (NULL_PTR_P(tree)) {
        return false;
    } else if (tree->left == tree->right && NULL != tree->left) {
        return false;
    } else if (tree->left == tree || tree->right == tree) {
        return false;
    } else {
        return true;
    }
}

static inline bool
avl_tree_structure_illegal_p(s_avl_tree_t *tree)
{
    return !avl_tree_structure_legal_p(tree);
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
    if (!NULL_PTR_P(tree) && avl_tree_structure_legal_p(*tree)) {
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
avl_tree_contains_repeated_ip(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    sint64 nice;
    s_avl_tree_t *node_i;
    s_array_queue_t *repeated_queue;

    assert_exit(avl_tree_structure_legal_p(tree));
    assert_exit(avl_tree_structure_legal_p(node));
    assert_exit(tree->nice == node->nice);

    node_i = tree;
    nice = node->nice;

    repeated_queue = array_queue_create();
    array_queue_enter(repeated_queue, node_i);

    while (!array_queue_empty_p(repeated_queue)) {
        node_i = array_queue_leave(repeated_queue);

        if (node == node_i) {
            array_queue_destroy(&repeated_queue);
            return true;
        } else {
            if (node_i->left && node_i->left->nice == nice) {
                array_queue_enter(repeated_queue, node_i->left);
            }

            if (node_i->right && node_i->right->nice == nice) {
                array_queue_enter(repeated_queue, node_i->right);
            }
        }
    }

    array_queue_destroy(&repeated_queue);
    return false;
}

static inline bool
avl_tree_contains_ip(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    sint64 nice;
    s_avl_tree_t *node_tmp;

    assert_exit(avl_tree_structure_legal_p(tree));
    assert_exit(avl_tree_structure_legal_p(node));

    node_tmp = tree;
    nice = node->nice;

    while (node_tmp) {
        if (node_tmp == node) {
            return true;
        } else if (node_tmp->nice < nice) {
            node_tmp = node_tmp->right;
        } else if (node_tmp->nice > nice) {
            node_tmp = node_tmp->left;
        } else {
            return avl_tree_contains_repeated_ip(node_tmp, node);
        }
    }

    return false;
}

bool
avl_tree_contains_p(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    if (avl_tree_structure_illegal_p(tree)) {
        return false;
    } else if (avl_tree_structure_illegal_p(node)) {
        return false;
    } else {
        return avl_tree_contains_ip(tree, node);
    }
}

static inline bool
avl_tree_node_unbalanced_p(s_avl_tree_t *node)
{
    assert_exit(avl_tree_structure_legal_p(node));

    return !avl_tree_height_balanced_opt_p(node);
}

static inline bool
avl_tree_balanced_ip(s_avl_tree_t *tree)
{
    s_avl_tree_t *node;
    s_array_queue_t *node_queue;

    assert_exit(avl_tree_structure_legal_p(tree));

    node = tree;
    node_queue = array_queue_create();
    array_queue_enter(node_queue, node);

    while (!array_queue_empty_p(node_queue)) {
         node = array_queue_leave(node_queue);

         if (avl_tree_node_unbalanced_p(node)) {
             array_queue_destroy(&node_queue);
             return false;
         } else {
             if (node->left) {
                 array_queue_enter(node_queue, node->left);
             }

             if (node->right) {
                 array_queue_enter(node_queue, node->right);
             }
         }
    }

    array_queue_destroy(&node_queue);
    return true;
}

bool
avl_tree_balanced_p(s_avl_tree_t *tree)
{
    if (avl_tree_structure_illegal_p(tree)) {
        return true;
    } else {
        return avl_tree_balanced_ip(tree);
    }
}

static inline bool
avl_tree_node_doubly_child_p(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    if (tree->left && tree->right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_node_leaf_p(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_p(tree));

    if (tree->left) {
        return false;
    } else if (tree->right) {
        return false;
    } else {
        return true;
    }
}

sint32
avl_tree_height(s_avl_tree_t *tree)
{
    if (avl_tree_structure_illegal_p(tree)) {
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
 */
static inline void
avl_tree_balance_rotate_left_to_left(s_avl_tree_t **tree)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->left));
    assert_exit(avl_tree_structure_legal_p((*tree)->left->left));
    assert_exit(avl_tree_node_unbalanced_p(*tree));

    k1 = *tree;
    k2 = k1->left;


    k1->left = k2->right;
    k2->right = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

    *tree = k2;
}

/*
 *        k1                     k2
 *       /  \                   /  \
 *      c    k2                k1   k3
 *          /  \      ==>     /  \   \
 *         b    k3           c    b   a1
 *               \
 *                a1
 */
static inline void
avl_tree_balance_rotate_right_to_right(s_avl_tree_t **tree)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->right));
    assert_exit(avl_tree_structure_legal_p((*tree)->right->right));
    assert_exit(avl_tree_node_unbalanced_p(*tree));

    k1 = *tree;
    k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);

    *tree = k2;
}

/*
 *        k1                 k3
 *       /  \               /  \
 *      k2   b             k2   k1
 *     /  \       ==>     / \     \
 *    a    k3            a   a1    b
 *        /
 *       a1
 */
static inline void
avl_tree_balance_rotate_left_to_right(s_avl_tree_t **tree)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;
    s_avl_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->left));
    assert_exit(avl_tree_structure_legal_p((*tree)->left->right));
    assert_exit(avl_tree_node_unbalanced_p(*tree));

    k1 = *tree;
    k2 = k1->left;

    k3 = k2->right;
    k2->right = k3->left;
    k1->left = k3->right;

    k3->left = k2;
    k3->right = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

    *tree = k3;
}

/*
 *        k1                   k3
 *       /  \                 /  \
 *      a    k2              k1   k2
 *          / \     ==>     / \     \
 *         k3  b           a   a1    b
 *        /
 *       a1
 */
static inline void
avl_tree_balance_rotate_right_to_left(s_avl_tree_t **tree)
{
    s_avl_tree_t *k1;
    s_avl_tree_t *k2;
    s_avl_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p((*tree)->right));
    assert_exit(avl_tree_structure_legal_p((*tree)->right->left));
    assert_exit(avl_tree_node_unbalanced_p(*tree));


    k1 = *tree;
    k2 = k1->right;

    k3 = k2->left;
    k2->left = k3->right;
    k1->right = k3->left;

    k3->right = k2;
    k3->left = k1;

    avl_tree_height_update(k1);
    avl_tree_height_update(k2);
    avl_tree_height_update(k3);

    *tree = k3;
}

static inline void
avl_tree_balance_rotate_i(s_avl_tree_t **tree, uint32 path_type)
{
    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));

    switch (path_type) {
        case PATH_LEFT_TO_LEFT:
            avl_tree_balance_rotate_left_to_left(tree);
            break;
        case PATH_LEFT_TO_RIGHT:
            avl_tree_balance_rotate_left_to_right(tree);
            break;
        case PATH_RIGHT_TO_LEFT:
            avl_tree_balance_rotate_right_to_left(tree);
            break;
        case PATH_RIGHT_TO_RIGHT:
            avl_tree_balance_rotate_right_to_right(tree);
            break;
        default:
            assert_not_reached("Unexpected value of enum tree_path_type.\n");
            break;
    }
}

static inline void
avl_tree_balance_rotate(s_array_stack_t *path_stack)
{
    uint32 path_type;
    s_avl_tree_t **iterator;

    assert_exit(array_stack_structure_legal_p(path_stack));

    while (array_stack_size(path_stack) >= 2) {
        iterator = array_stack_pop(path_stack);
        path_type = TREE_PATH_TYPE(iterator);
        iterator = TREE_PATH_DECODE(iterator);
        avl_tree_height_update(*iterator);

        iterator = array_stack_top(path_stack);
        path_type = path_type + (TREE_PATH_TYPE(iterator) << 1);
        iterator = TREE_PATH_DECODE(iterator);
        avl_tree_height_update(*iterator);

        if (avl_tree_node_unbalanced_p(*iterator)) {
            avl_tree_balance_rotate_i(iterator, path_type);
        }
    }
}

static inline s_avl_tree_t *
avl_tree_insert_i(s_avl_tree_t **tree, s_avl_tree_t *inserted)
{
    s_array_stack_t *path_stack;
    s_avl_tree_t *avl, **iterator;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_structure_legal_p(inserted));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));

    iterator = tree;
    avl = *iterator;
    path_stack = array_stack_create();

    while (avl) {
        if (inserted == avl) {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            array_stack_destroy(&path_stack);
            return NULL;
        } else if (inserted->nice <= avl->nice) { /* involve nice repeated */
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
            iterator = &avl->left;
        } else {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
            iterator = &avl->right;
        }

        avl = *iterator;
    }

    *iterator = inserted; /* insert the node */
    avl_tree_height_update(inserted);

    avl_tree_balance_rotate(path_stack);
    array_stack_destroy(&path_stack);

    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    return inserted;
}

s_avl_tree_t *
avl_tree_insert(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_p(*tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_p(node)) {
        return PTR_INVALID;
    } else {
        return avl_tree_insert_i(tree, node);
    }
}

static inline s_avl_tree_t **
avl_tree_find_ptr_to_max(s_avl_tree_t **tree)
{
    s_avl_tree_t *avl;
    s_avl_tree_t **max;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_node_doubly_child_p(*tree));

    max = tree;
    avl = *max;

    while (avl->right != NULL) {
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

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_node_doubly_child_p(*tree));

    min = tree;
    avl = *min;

    while (NULL != avl->left) {
        min = &avl->left;
        avl = *min;
    }

    return min;
}

static inline void
avl_tree_node_children_swap(s_avl_tree_t *a, s_avl_tree_t *b)
{
    assert_exit(avl_tree_structure_legal_p(a));
    assert_exit(avl_tree_structure_legal_p(b));

    SWAP(a->left, b->left);
    SWAP(a->right, b->right);
}

static inline void
avl_tree_node_right_swap_path_update(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    array_stack_push(path_stack, TREE_PATH_R_ENCODE(node));

    node = &(*node)->right;
    avl = *node;

    while (avl->left) {
        array_stack_push(path_stack, TREE_PATH_L_ENCODE(node));

        node = &avl->left;
        avl = *node;
    }
}

static inline s_avl_tree_t **
avl_tree_node_doubly_child_right_swap_to_left(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t **min;
    s_avl_tree_t *avl_min;
    s_avl_tree_t *removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    removed = *node;
    min = avl_tree_find_ptr_to_min(&removed->right);
    avl_min = *min;

    if (removed->right == avl_min) {
        /*
         *       /                    /
         *     removed              avl_min
         *     /    \               /    \
         *    y     avl_min  -->   y     removed
         *             \                   \
         *              x                   x
         */
         removed->right = avl_min->right;
         avl_min->right = removed;
         avl_min->left = removed->left;
         removed->left = NULL;

         *node = avl_min;
    } else {
        avl_tree_node_children_swap(avl_min, removed);

        *node = avl_min;
        *min = removed;
    }

    avl_tree_node_right_swap_path_update(node, path_stack);

    if (removed->right) {
        return avl_tree_node_sinlge_child_right_swap_to_leaf(min, path_stack);
    } else {
        return min;
    }
}

static inline void
avl_tree_node_leaf_strip(s_avl_tree_t **node, s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;
    s_avl_tree_t **iterator;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(avl_tree_node_leaf_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    *node = NULL; /* remove the node */

    if (array_stack_empty_p(path_stack)) { /* only one node of given tree */
        return;
    }

    iterator = TREE_PATH_DECODE(array_stack_pop(path_stack));
    avl = *iterator;

    if (avl_tree_node_unbalanced_p(avl) && avl->left) {
        array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
        iterator = &avl->left;

        if (avl->left->right) {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
        } else {
            assert_exit(avl->left->left);
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
        }
    } else if (avl_tree_node_unbalanced_p(avl) && avl->right) {
        array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
        iterator = &avl->right;

        if (avl->right->left) {
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
        } else {
            assert_exit(avl->right->right);
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
        }
    }

    avl_tree_balance_rotate(path_stack);
}

static inline s_avl_tree_t **
avl_tree_node_sinlge_child_left_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;
    s_avl_tree_t *leaf;
    s_avl_tree_t **removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    avl = *node;

    assert_exit(avl->right == NULL);
    assert_exit(avl_tree_node_leaf_p(avl->left));
    /*
     *      /          /
     *    avl         x
     *    /    -->   /
     *   x          avl
     */
    leaf = avl->left;
    removed = &leaf->left;

    leaf->left = avl;
    *node = leaf;
    avl->left = NULL;

    array_stack_push(path_stack, TREE_PATH_L_ENCODE(node));

    return removed;
}

static inline s_avl_tree_t **
avl_tree_node_sinlge_child_right_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;
    s_avl_tree_t *leaf;
    s_avl_tree_t **removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    avl = *node;

    assert_exit(avl->left == NULL);
    assert_exit(avl_tree_node_leaf_p(avl->right));
    /*
     *    \         \
     *    avl        x
     *      \  -->    \
     *       x         avl
     */
    leaf = avl->right;
    removed = &leaf->right;

    leaf->right = avl;
    *node = leaf;
    avl->right = NULL;

    array_stack_push(path_stack, TREE_PATH_R_ENCODE(node));

    return removed;
}

static inline void
avl_tree_node_left_swap_path_update(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    array_stack_push(path_stack, TREE_PATH_L_ENCODE(node));

    node = &(*node)->left;
    avl = *node;

    while (avl->right) {
        array_stack_push(path_stack, TREE_PATH_R_ENCODE(node));

        node = &avl->right;
        avl = *node;
    }
}

static inline s_avl_tree_t **
avl_tree_node_doubly_child_left_swap_to_left(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t **max;
    s_avl_tree_t *avl_max;
    s_avl_tree_t *removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    removed = *node;
    max = avl_tree_find_ptr_to_max(&removed->left);
    avl_max = *max;

    if (removed->left == avl_max) {
        /*
         *       \                   \
         *      removed           avl_max
         *      /     \           /     \
         *   avl_max   y  -->   removed  y
         *   /                  /
         *  x                  x
         */
        removed->left = avl_max->left;
        avl_max->left = removed;
        avl_max->right = removed->right;
        removed->right = NULL;

        *node = avl_max;
    } else {
        avl_tree_node_children_swap(avl_max, removed);

        *node = avl_max;
        *max = removed;
    }

    avl_tree_node_left_swap_path_update(node, path_stack);

    if (removed->left) {
        return avl_tree_node_sinlge_child_left_swap_to_leaf(max, path_stack);
    } else {
        return max;
    }
}

static inline s_avl_tree_t **
avl_tree_node_doubly_child_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(avl_tree_node_doubly_child_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    avl = *node;

    if (avl_tree_height_opt(avl->left) > avl_tree_height_opt(avl->right)) {
        return avl_tree_node_doubly_child_left_swap_to_left(node, path_stack);
    } else {
        return avl_tree_node_doubly_child_right_swap_to_left(node, path_stack);
    }
}

static inline void
avl_tree_node_strip(s_avl_tree_t **node, s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    avl = *node;

    if (avl_tree_node_doubly_child_p(avl)) {
        node = avl_tree_node_doubly_child_swap_to_leaf(node, path_stack);
    } else if (avl->left) {
        node = avl_tree_node_sinlge_child_left_swap_to_leaf(node, path_stack);
    } else if (avl->right) {
        node = avl_tree_node_sinlge_child_right_swap_to_leaf(node, path_stack);
    }

    avl_tree_node_leaf_strip(node, path_stack);
}

static inline s_avl_tree_t *
avl_tree_remove_i(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    s_array_stack_t *path_stack;
    s_avl_tree_t *avl, **iterator;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_p(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_structure_legal_p(node));

    iterator = tree;
    avl = *iterator;
    path_stack = array_stack_create();

    while (avl) {
        if (node == avl) {
            avl_tree_node_strip(iterator, path_stack);
            break;
        } else if (node->nice <= avl->nice) {
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
            iterator = &avl->left;
        } else if (node->nice > avl->nice) {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
            iterator = &avl->right;
        }

        avl = *iterator;
    }

    array_stack_destroy(&path_stack);

    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));

    return avl;
}

s_avl_tree_t *
avl_tree_remove(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_p(*tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_p(node)) {
        return PTR_INVALID;
    } else {
        return avl_tree_remove_i(tree, node);
    }
}

static inline void
avl_tree_iterate_i(s_avl_tree_t *tree, void (*handler)(void *))
{
    s_avl_tree_t *avl_node;
    s_array_queue_t *queue_slave;
    s_array_queue_t *queue_master;

    assert_exit(NON_NULL_PTR_P(handler));
    assert_exit(avl_tree_structure_legal_p(tree));

    queue_slave = array_queue_create();
    queue_master = array_queue_create();
    array_queue_enter(queue_master, tree);

    while (!array_queue_empty_p(queue_master)) {
        while (!array_queue_empty_p(queue_master)) {
            avl_node = array_queue_leave(queue_master);
            handler(avl_node);

            if (avl_node->left) {
                array_queue_enter(queue_slave, avl_node->left);
            }
            if (avl_node->right) {
                array_queue_enter(queue_slave, avl_node->right);
            }
        }
        swap_pointer((void **)&queue_master, (void **)&queue_slave);
    }

    array_queue_destroy(&queue_slave);
    array_queue_destroy(&queue_master);
}

void
avl_tree_iterate(s_avl_tree_t *tree, void (*handler)(void *))
{
    if (NULL_PTR_P(handler)) {
        return;
    } else if (avl_tree_structure_illegal_p(tree)) {
        return;
    } else {
        avl_tree_iterate_i(tree, handler);
    }
}

