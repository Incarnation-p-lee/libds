s_avl_tree_t *
avl_tree_left(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_ip(tree)) {
        return tree->left;
    } else {
        return PTR_INVALID;
    }
}

s_avl_tree_t *
avl_tree_right(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_ip(tree)) {
        return tree->right;
    } else {
        return PTR_INVALID;
    }
}

sint64
avl_tree_nice(s_avl_tree_t *tree)
{
    if (avl_tree_structure_legal_ip(tree)) {
        return tree->nice;
    } else {
        return TREE_NICE_INVALID;
    }
}

s_doubly_linked_list_t *
avl_tree_val_list(s_avl_tree_t *tree)
{
    if (avl_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return tree->list;
    }
}

static inline s_doubly_linked_list_t *
avl_tree_val_list_i(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_ip(tree));

    return tree->list;
}

s_avl_tree_t *
avl_tree_create(void *val, sint64 nice)
{
    s_avl_tree_t *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    tree->list = doubly_linked_list_create();

    avl_tree_initial_i(tree, val, nice);

    return tree;
}

static inline void
avl_tree_initial_i(s_avl_tree_t *tree, void *val, sint64 nice)
{
    assert_exit(NON_NULL_PTR_P(tree));

    tree->height = 0;
    tree->nice = nice;
    tree->left = tree->right = NULL;

    doubly_linked_list_val_set(tree->list, val);
}

void
avl_tree_initial(s_avl_tree_t *tree, void *val, sint64 nice)
{
    if (NON_NULL_PTR_P(tree)) {
        avl_tree_initial_i(tree, val, nice);
    }
}

bool
avl_tree_structure_legal_p(s_avl_tree_t *tree)
{
    return avl_tree_structure_legal_ip(tree);
}

static inline bool
avl_tree_structure_legal_ip(s_avl_tree_t *tree)
{
    if (NULL_PTR_P(tree)) {
        return false;
    } else if (tree->left == tree->right && NULL != tree->left) {
        return false;
    } else if (tree->left == tree || tree->right == tree) {
        return false;
    } else if (doubly_linked_list_structure_illegal_p(tree->list)) {
        return false;
    } else {
        return true;
    }
}

bool
avl_tree_structure_illegal_p(s_avl_tree_t *tree)
{
    return avl_tree_structure_illegal_ip(tree);
}

static inline bool
avl_tree_structure_illegal_ip(s_avl_tree_t *tree)
{
    return !avl_tree_structure_legal_ip(tree);
}

static inline void
avl_tree_destroy_i(s_avl_tree_t *tree)
{
    s_array_queue_t *queue;
    s_avl_tree_t *avl_node;

    assert_exit(avl_tree_structure_legal_ip(tree));

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

        doubly_linked_list_destroy(&avl_node->list);
        memory_cache_free(avl_node);
    }

    array_queue_destroy(&queue);
}

void
avl_tree_destroy(s_avl_tree_t **tree)
{
    if (!NULL_PTR_P(tree) && avl_tree_structure_legal_ip(*tree)) {
        avl_tree_destroy_i(*tree);
        *tree = NULL;
    }
}

static inline s_avl_tree_t *
avl_tree_find_i(s_avl_tree_t *tree, sint64 nice)
{
    s_avl_tree_t *avl;

    assert_exit(avl_tree_structure_legal_ip(tree));

    avl = tree;

    while (avl) {
        if (nice < avl->nice) {
            avl = avl->left;
        } else if (nice > avl->nice) {
            avl = avl->right;
        } else {
            return avl;
        }
    }

    return NULL;
}

s_avl_tree_t *
avl_tree_find(s_avl_tree_t *tree, sint64 nice)
{
    if (avl_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_i(tree, nice);
    }
}

static inline s_avl_tree_t *
avl_tree_find_min_i(s_avl_tree_t *tree)
{
    s_avl_tree_t *avl;

    assert_exit(avl_tree_structure_legal_ip(tree));

    avl = tree;

    while (avl->left) {
        avl = avl->left;
    }

    return avl;
}

s_avl_tree_t *
avl_tree_find_min(s_avl_tree_t *tree)
{
    if (avl_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_min_i(tree);
    }
}

static inline s_avl_tree_t *
avl_tree_find_max_i(s_avl_tree_t *tree)
{
    s_avl_tree_t *avl;

    assert_exit(avl_tree_structure_legal_ip(tree));

    avl = tree;

    while (avl->right) {
        avl = avl->right;
    }

    return avl;
}

s_avl_tree_t *
avl_tree_find_max(s_avl_tree_t *tree)
{
    if (avl_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return avl_tree_find_max_i(tree);
    }
}

static inline bool
avl_tree_contains_ip(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    sint64 nice;
    s_avl_tree_t *node_tmp;

    assert_exit(avl_tree_structure_legal_ip(tree));
    assert_exit(avl_tree_structure_legal_ip(node));

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
            return false;
        }
    }

    return false;
}

bool
avl_tree_contains_p(s_avl_tree_t *tree, s_avl_tree_t *node)
{
    if (avl_tree_structure_illegal_ip(tree)) {
        return false;
    } else if (avl_tree_structure_illegal_ip(node)) {
        return false;
    } else {
        return avl_tree_contains_ip(tree, node);
    }
}

static inline bool
avl_tree_node_unbalanced_p(s_avl_tree_t *node)
{
    assert_exit(avl_tree_structure_legal_ip(node));

    return !avl_tree_height_balanced_opt_p(node);
}

static inline bool
avl_tree_balanced_ip(s_avl_tree_t *tree)
{
    s_avl_tree_t *node;
    s_array_queue_t *node_queue;

    assert_exit(avl_tree_structure_legal_ip(tree));

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
    if (avl_tree_structure_illegal_ip(tree)) {
        return true;
    } else {
        return avl_tree_balanced_ip(tree);
    }
}

static inline bool
avl_tree_node_doubly_child_p(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_ip(tree));

    if (tree->left && tree->right) {
        return true;
    } else {
        return false;
    }
}

static inline bool
avl_tree_node_leaf_p(s_avl_tree_t *tree)
{
    assert_exit(avl_tree_structure_legal_ip(tree));

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
    return avl_tree_height_opt(tree);
}

static inline void
avl_tree_height_update(s_avl_tree_t *tree)
{
    sint32 left;
    sint32 right;

    assert_exit(avl_tree_structure_legal_ip(tree));

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
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_structure_legal_ip((*tree)->left));
    assert_exit(avl_tree_structure_legal_ip((*tree)->left->left));
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
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_structure_legal_ip((*tree)->right));
    assert_exit(avl_tree_structure_legal_ip((*tree)->right->right));
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
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_structure_legal_ip((*tree)->left));
    assert_exit(avl_tree_structure_legal_ip((*tree)->left->right));
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
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_structure_legal_ip((*tree)->right));
    assert_exit(avl_tree_structure_legal_ip((*tree)->right->left));
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
avl_tree_insert_rotate_i(s_avl_tree_t **tree, uint32 path_type)
{
    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_ip(*tree));

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
avl_tree_insert_rotate(s_array_stack_t *path_stack)
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
            avl_tree_insert_rotate_i(iterator, path_type);
        }
    }
}

static inline void
avl_tree_node_merge(s_avl_tree_t *merged, s_avl_tree_t *node)
{
    s_doubly_linked_list_t *node_new;
    s_doubly_linked_list_t *node_tmp;
    s_doubly_linked_list_t *node_limit;

    assert_exit(avl_tree_structure_legal_ip(merged));
    assert_exit(avl_tree_structure_legal_ip(node));
    assert_exit(avl_tree_nice(merged) == avl_tree_nice(node));

    node_limit = node_tmp = avl_tree_val_list_i(node);

    do {
        node_new = doubly_linked_list_create();
        doubly_linked_list_val_set(node_new, doubly_linked_list_val(node_tmp));

        doubly_linked_list_insert_before(merged->list, node_new);
        node_tmp = doubly_linked_list_next(node_tmp);
    } while (node_tmp != node_limit);
}

static inline s_avl_tree_t *
avl_tree_insert_i(s_avl_tree_t **tree, s_avl_tree_t *inserted)
{
    s_array_stack_t *path_stack;
    s_avl_tree_t *avl, **iterator;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_structure_legal_ip(inserted));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));

    iterator = tree;
    avl = *iterator;
    path_stack = array_stack_create();

    while (avl) {
        if (inserted == avl) {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            array_stack_destroy(&path_stack);
            return inserted;
        } else if (inserted->nice < avl->nice) { /* involve nice repeated */
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
            iterator = &avl->left;
        } else if (inserted->nice > avl->nice) {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
            iterator = &avl->right;
        } else { /* the same nice, merge to avl node */
            avl_tree_node_merge(avl, inserted);
            array_stack_destroy(&path_stack);
            return avl;
        }

        avl = *iterator;
    }

    *iterator = inserted; /* insert the node */

    avl_tree_insert_rotate(path_stack);
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
    } else if (avl_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_ip(node)) {
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
    assert_exit(avl_tree_structure_legal_ip(*tree));

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
    assert_exit(avl_tree_structure_legal_ip(*tree));

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
    assert_exit(avl_tree_structure_legal_ip(a));
    assert_exit(avl_tree_structure_legal_ip(b));

    SWAP(a->left, b->left);
    SWAP(a->right, b->right);
}

static inline void
avl_tree_node_right_swap_path_update(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    array_stack_push(path_stack, node);

    node = &(*node)->right;
    avl = *node;

    while (avl->left) {
        array_stack_push(path_stack, node);

        node = &avl->left;
        avl = *node;
    }
}

static inline s_avl_tree_t **
avl_tree_node_doubly_child_right_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t **min;
    s_avl_tree_t *avl_min;
    s_avl_tree_t *removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(avl_tree_node_doubly_child_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    removed = *node;
    min = avl_tree_find_ptr_to_min(&removed->right);
    avl_min = *min;

    if (removed->right != avl_min) {
        avl_tree_node_children_swap(avl_min, removed);

        *node = avl_min;
        *min = removed;
    } else {
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
        min = &avl_min->right;
    }


    avl_tree_node_right_swap_path_update(node, path_stack);

    if (removed->right) {
        return avl_tree_node_sinlge_child_right_swap_to_leaf(min, path_stack);
    } else {
        return min;
    }
}

static inline void
avl_tree_remove_rotate_i(s_avl_tree_t **tree)
{
    s_avl_tree_t *avl;
    sint32 left, right;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_node_unbalanced_p(*tree));

    avl = *tree;
    left = avl_tree_height_opt(avl->left);
    right = avl_tree_height_opt(avl->right);

    if (left > right) {
        left = avl_tree_height_opt(avl->left->left);
        right = avl_tree_height_opt(avl->left->right);

        if (left >= right) {
            avl_tree_balance_rotate_left_to_left(tree);
        } else {
            avl_tree_balance_rotate_left_to_right(tree);
        }
    } else {
        left = avl_tree_height_opt(avl->right->left);
        right = avl_tree_height_opt(avl->right->right);

        if (right >= left) {
            avl_tree_balance_rotate_right_to_right(tree);
        } else {
            avl_tree_balance_rotate_right_to_left(tree);
        }
    }
}

static inline void
avl_tree_remove_rotate(s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;
    s_avl_tree_t **iterator;

    assert_exit(array_stack_structure_legal_p(path_stack));

    while (!array_stack_empty_p(path_stack)) {
        iterator = array_stack_pop(path_stack);

        avl = *iterator;
        avl_tree_height_update(avl);

        if (avl_tree_node_unbalanced_p(avl)) {
            avl_tree_remove_rotate_i(iterator);
        }
    }
}

static inline void
avl_tree_node_leaf_strip(s_avl_tree_t **node, s_array_stack_t *path_stack)
{

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(avl_tree_node_leaf_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    *node = NULL; /* remove the node */
    avl_tree_remove_rotate(path_stack);
}

static inline s_avl_tree_t **
avl_tree_node_sinlge_child_left_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;
    s_avl_tree_t *leaf;
    s_avl_tree_t **removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
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

    array_stack_push(path_stack, node);

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
    assert_exit(avl_tree_structure_legal_ip(*node));
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

    array_stack_push(path_stack, node);

    return removed;
}

static inline void
avl_tree_node_left_swap_path_update(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    array_stack_push(path_stack, node);

    node = &(*node)->left;
    avl = *node;

    while (avl->right) {
        array_stack_push(path_stack, node);

        node = &avl->right;
        avl = *node;
    }
}

static inline s_avl_tree_t **
avl_tree_node_doubly_child_left_swap_to_leaf(s_avl_tree_t **node,
    s_array_stack_t *path_stack)
{
    s_avl_tree_t **max;
    s_avl_tree_t *avl_max;
    s_avl_tree_t *removed;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(avl_tree_node_doubly_child_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    removed = *node;
    max = avl_tree_find_ptr_to_max(&removed->left);
    avl_max = *max;

    if (removed->left != avl_max) {
        avl_tree_node_children_swap(avl_max, removed);

        *node = avl_max;
        *max = removed;
    } else {
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
        max = &avl_max->left;
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
    assert_exit(avl_tree_structure_legal_ip(*node));
    assert_exit(avl_tree_node_doubly_child_p(*node));
    assert_exit(array_stack_structure_legal_p(path_stack));

    avl = *node;

    if (avl_tree_height_opt(avl->left) >= avl_tree_height_opt(avl->right)) {
        return avl_tree_node_doubly_child_left_swap_to_leaf(node, path_stack);
    } else {
        return avl_tree_node_doubly_child_right_swap_to_leaf(node, path_stack);
    }
}

static inline void
avl_tree_node_strip(s_avl_tree_t **node, s_array_stack_t *path_stack)
{
    s_avl_tree_t *avl;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(avl_tree_structure_legal_ip(*node));
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
    s_avl_tree_t *avl, *removed;
    s_avl_tree_t **iterator;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(avl_tree_structure_legal_ip(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_structure_legal_ip(node));

    removed = NULL;
    iterator = tree;
    avl = *iterator;
    path_stack = array_stack_create();

    while (avl) {
        if (node->nice < avl->nice) {
            array_stack_push(path_stack, iterator);
            iterator = &avl->left;
        } else if (node->nice > avl->nice) {
            array_stack_push(path_stack, iterator);
            iterator = &avl->right;
        } else if (node == avl) {
            removed = node;
            avl_tree_node_strip(iterator, path_stack);
            break;
        } else { /* node not in given tree */
            break;
        }

        avl = *iterator;
    }

    array_stack_destroy(&path_stack);

    if (removed == NULL) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert_exit(avl_tree_ordered_p(*tree));
    assert_exit(avl_tree_balanced_p(*tree));
    return removed;
}

s_avl_tree_t *
avl_tree_remove(s_avl_tree_t **tree, s_avl_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else if (avl_tree_structure_illegal_ip(node)) {
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
    assert_exit(avl_tree_structure_legal_ip(tree));

    queue_slave = array_queue_create();
    queue_master = array_queue_create();
    array_queue_enter(queue_master, tree);

    while (!array_queue_empty_p(queue_master)) {
        avl_node = array_queue_leave(queue_master);
        handler(avl_node);

        if (avl_node->left) {
            array_queue_enter(queue_slave, avl_node->left);
        }

        if (avl_node->right) {
            array_queue_enter(queue_slave, avl_node->right);
        }

        if (array_queue_empty_p(queue_master)) {
            swap_pointer((void **)&queue_master, (void **)&queue_slave);
        }
    }

    array_queue_destroy(&queue_slave);
    array_queue_destroy(&queue_master);
}

void
avl_tree_iterate(s_avl_tree_t *tree, void (*handler)(void *))
{
    if (NULL_PTR_P(handler)) {
        return;
    } else if (avl_tree_structure_illegal_ip(tree)) {
        return;
    } else {
        avl_tree_iterate_i(tree, handler);
    }
}

