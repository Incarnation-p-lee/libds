sint64
splay_tree_nice(s_splay_tree_t *tree)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return TREE_NICE_INVALID;
    } else {
        return tree->nice;
    }
}

s_splay_tree_t *
splay_tree_left(s_splay_tree_t *tree)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return tree->left;
    }
}

s_splay_tree_t *
splay_tree_right(s_splay_tree_t *tree)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return tree->right;
    }
}

static inline s_doubly_linked_list_t *
splay_tree_val_list_i(s_splay_tree_t *tree)
{
    assert_exit(splay_tree_structure_legal_ip(tree));

    return tree->list;
}

s_doubly_linked_list_t *
splay_tree_val_list(s_splay_tree_t *tree)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return splay_tree_val_list_i(tree);
    }
}

bool
splay_tree_structure_legal_p(s_splay_tree_t *tree)
{
    return splay_tree_structure_legal_ip(tree);
}

bool
splay_tree_structure_illegal_p(s_splay_tree_t *tree)
{
    return splay_tree_structure_illegal_ip(tree);
}

static inline bool
splay_tree_structure_legal_ip(s_splay_tree_t *tree)
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
splay_tree_structure_illegal_ip(s_splay_tree_t *tree)
{
    return !splay_tree_structure_legal_ip(tree);
}

static inline void
splay_tree_initial_i(s_splay_tree_t *tree, void *val, sint64 nice)
{
    assert_exit(NON_NULL_PTR_P(tree));

    tree->nice = nice;
    tree->left = tree->right = NULL;

    doubly_linked_list_val_set(tree->list, val);
}

s_splay_tree_t *
splay_tree_create(void *val, sint64 nice)
{
    s_splay_tree_t *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    tree->list = doubly_linked_list_create();

    splay_tree_initial_i(tree, val, nice);

    return tree;
}

void
splay_tree_initial(s_splay_tree_t *tree, void *val, sint64 nice)
{
    if (NON_NULL_PTR_P(tree)) {
        splay_tree_initial_i(tree, val, nice);
    }
}

static inline void
splay_tree_destroy_i(s_splay_tree_t *tree)
{
    s_array_queue_t *queue;
    s_splay_tree_t *splay_node;

    assert_exit(splay_tree_structure_legal_ip(tree));

    queue = array_queue_create();
    array_queue_enter(queue, tree);

    while (!array_queue_empty_p(queue)) {
        splay_node = array_queue_leave(queue);

        if (splay_node->left != NULL) {
            array_queue_enter(queue, splay_node->left);
        }
        if (splay_node->right != NULL) {
            array_queue_enter(queue, splay_node->right);
        }

        doubly_linked_list_destroy(&splay_node->list);
        memory_cache_free(splay_node);
    }

    array_queue_destroy(&queue);
}

void
splay_tree_destroy(s_splay_tree_t **tree)
{
    if (NULL_PTR_P(tree)) {
        return;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return;
    } else {
        splay_tree_destroy_i(*tree);
        *tree = NULL;
    }
}

static inline s_splay_tree_t *
splay_tree_find_i(s_splay_tree_t **tree, sint64 nice)
{
    s_splay_tree_t **iterator;
    s_splay_tree_t *splay_node;
    s_array_stack_t *path_stack;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    iterator = tree;
    splay_node = *tree;
    path_stack = array_stack_create();

    while (splay_node) {
        if (nice < splay_node->nice) {
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
            iterator = &splay_node->left;
        } else if (nice > splay_node->nice) {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
            iterator = &splay_node->right;
        } else {
            splay_tree_splaying(path_stack);
            assert_exit(*tree = splay_node);
            break;

        }
        splay_node = *iterator;
    }

    array_stack_destroy(&path_stack);
    return splay_node;
}

s_splay_tree_t *
splay_tree_find(s_splay_tree_t **tree, sint64 nice)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else {
        return splay_tree_find_i(tree, nice);
    }
}

static inline s_splay_tree_t *
splay_tree_find_min_i(s_splay_tree_t **tree)
{
    s_splay_tree_t *min_node;
    s_splay_tree_t **iterator;
    s_array_stack_t *path_stack;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    iterator = tree;
    min_node = *tree;
    path_stack = array_stack_create();

    while (min_node->left) {
        array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
        iterator = &min_node->left;
        min_node = *iterator;
    }

    splay_tree_splaying(path_stack);
    array_stack_destroy(&path_stack);

    assert_exit(*tree == min_node);
    return min_node;
}

s_splay_tree_t *
splay_tree_find_min(s_splay_tree_t **tree)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else {
        return splay_tree_find_min_i(tree);
    }
}

static inline s_splay_tree_t *
splay_tree_find_max_i(s_splay_tree_t **tree)
{
    s_splay_tree_t *max_node;
    s_splay_tree_t **iterator;
    s_array_stack_t *path_stack;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    iterator = tree;
    max_node = *tree;
    path_stack = array_stack_create();

    while (max_node->right) {
        array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
        iterator = &max_node->right;
        max_node = *iterator;
    }

    splay_tree_splaying(path_stack);
    array_stack_destroy(&path_stack);

    assert_exit(*tree == max_node);
    return max_node;
}

s_splay_tree_t *
splay_tree_find_max(s_splay_tree_t **tree)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else {
        return splay_tree_find_max_i(tree);
    }
}

/*
 *        k1            k3
 *       /  \          /  \
 *      k2   d   =>   a    k2
 *     /  \               /  \
 *    k3   c             b    k1
 *   /  \                    /  \
 *  a    b                  c    d
 */
static inline void
splay_tree_splaying_left_to_left(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;
    s_splay_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->left));
    assert_exit(splay_tree_structure_legal_ip((*tree)->left->left));

    k1 = *tree;
    k2 = k1->left;
    k3 = k2->left;

    k1->left = k2->right;
    k2->left = k3->right;
    k2->right = k1;
    k3->right = k2;

    *tree = k3;
}

/*
 *     k1            k3
 *    /  \          /  \
 *   k2   d  =>    k2   k1
 *  / \           / \   / \
 * a   k3        a   b c   d
 *    /  \
 *   b    c
 */
static inline void
splay_tree_splaying_left_to_right(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;
    s_splay_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->left));
    assert_exit(splay_tree_structure_legal_ip((*tree)->left->right));

    k1 = *tree;
    k2 = k1->left;
    k3 = k2->right;

    k1->left = k3->right;
    k2->right = k3->left;
    k3->left = k2;
    k3->right = k1;

    *tree = k3;
}

/*
 *    k1              k3
 *   / \             /  \
 *  a   k2    =>    k1   k2
 *     /  \        / \   / \
 *    k3   c      a   b c   d
 *   /  \
 *  b    c
 */
static inline void
splay_tree_splaying_right_to_left(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;
    s_splay_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->right));
    assert_exit(splay_tree_structure_legal_ip((*tree)->right->left));

    k1 = *tree;
    k2 = k1->right;
    k3 = k2->left;

    k1->right = k3->left;
    k2->left = k3->right;
    k3->left = k1;
    k3->right = k2;

    *tree = k3;
}

/*
 *     k1                 k3
 *    / \                /  \
 *   a   k2      =>     k2   d
 *      /  \           /  \
 *     b    k3        k1   c
 *         /  \      /  \
 *        c    d    a    b
 */
static inline void
splay_tree_splaying_right_to_right(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;
    s_splay_tree_t *k3;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->right));
    assert_exit(splay_tree_structure_legal_ip((*tree)->right->right));

    k1 = *tree;
    k2 = k1->right;
    k3 = k2->right;

    k1->right = k2->left;
    k2->right = k3->left;
    k2->left = k1;
    k3->left = k2;

    *tree = k3;
}

static inline void
splay_tree_splaying_i(s_splay_tree_t **tree, uint32 path_mask)
{
    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    switch (path_mask) {
        case PATH_LEFT_TO_LEFT:
            splay_tree_splaying_left_to_left(tree);
            break;
        case PATH_LEFT_TO_RIGHT:
            splay_tree_splaying_left_to_right(tree);
            break;
        case PATH_RIGHT_TO_LEFT:
            splay_tree_splaying_right_to_left(tree);
            break;
        case PATH_RIGHT_TO_RIGHT:
            splay_tree_splaying_right_to_right(tree);
            break;
        default:
            assert_not_reached("Unexpected value of enum tree_path_type.\n");
            break;
    }
}

/*
 *     k1          k2
 *    /  \        /  \
 *   k2   c  =>  a    k1
 *  /  \             /  \
 * a    b           b    c
 */
static inline void
splay_tree_splaying_root_left(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->left));

    k1 = *tree;
    k2 = k1->left;

    k1->left = k2->right;
    k2->right = k1;

    *tree = k2;
}


/*
 *   k1               k2
 *  /  \             /  \
 * a    k2    =>    k1   c
 *     /  \        /  \
 *    b    c      a    b
 */
static inline void
splay_tree_splaying_root_right(s_splay_tree_t **tree)
{
    s_splay_tree_t *k1;
    s_splay_tree_t *k2;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_structure_legal_ip((*tree)->right));

    k1 = *tree;
    k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;

    *tree = k2;
}

static inline void
splay_tree_splaying_root(s_splay_tree_t **tree, uint32 path_mask)
{

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    switch (path_mask) {
        case PATH_LEFT:
            splay_tree_splaying_root_left(tree);
            break;
        case PATH_RIGHT:
            splay_tree_splaying_root_right(tree);
            break;
        default:
            assert_not_reached("Unexpected value of enum tree_path_type.\n");
            break;
    }
}

static inline void
splay_tree_splaying(s_array_stack_t *path_stack)
{
    uint32 path_mask;
    s_splay_tree_t **iterator;

    assert_exit(array_stack_structure_legal_p(path_stack));

    while (array_stack_size(path_stack) >= 2) {
        iterator = array_stack_pop(path_stack);
        path_mask = TREE_PATH_TYPE(iterator);

        iterator = array_stack_pop(path_stack);
        path_mask = path_mask + (TREE_PATH_TYPE(iterator) << 1);

        iterator = TREE_PATH_DECODE(iterator);
        splay_tree_splaying_i(iterator, path_mask);
    }

    if (array_stack_size(path_stack) == 1) {
        iterator = array_stack_pop(path_stack);
        path_mask = TREE_PATH_TYPE(iterator);

        iterator = TREE_PATH_DECODE(iterator);
        splay_tree_splaying_root(iterator, path_mask);
    }
}

static inline sint32
splay_tree_height_i(s_splay_tree_t *tree)
{
    sint32 height;
    s_splay_tree_t *splay_node;
    s_array_queue_t *queue_master, *queue_slave;

    if (!tree) {
        return -1;
    } else {
        height = -1;
        splay_node = tree;

        queue_slave = array_queue_create();
        queue_master = array_queue_create();
        array_queue_enter(queue_master, splay_node);

        while (!array_queue_empty_p(queue_master)) {
            splay_node = array_queue_leave(queue_master);

            if (splay_node->left) {
                array_queue_enter(queue_slave, splay_node->left);
            }

            if (splay_node->right) {
                array_queue_enter(queue_slave, splay_node->right);
            }

            if (array_queue_empty_p(queue_master)) {
                height++;
                swap_pointer((void **)&queue_master, (void **)&queue_slave);
            }
        }

        array_queue_destroy(&queue_master);
        array_queue_destroy(&queue_slave);

        return height;
    }
}

sint32
splay_tree_height(s_splay_tree_t *tree)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return -1;
    } else {
        return splay_tree_height_i(tree);
    }
}

static inline bool
splay_tree_contains_ip(s_splay_tree_t *tree, s_splay_tree_t *node)
{
    sint64 nice;
    s_splay_tree_t *splay_node;

    assert_exit(splay_tree_structure_legal_ip(tree));
    assert_exit(splay_tree_structure_legal_ip(node));

    splay_node = tree;
    nice = node->nice;

    while (splay_node) {
        if (splay_node == node) {
            return true;
        } else if (splay_node->nice < nice) {
            splay_node = splay_node->right;
        } else if (splay_node->nice > nice) {
            splay_node = splay_node->left;
        } else {
            return false;
        }
    }

    return false;
}

bool
splay_tree_contains_p(s_splay_tree_t *tree, s_splay_tree_t *node)
{
    if (splay_tree_structure_illegal_ip(tree)) {
        return false;
    } else if (splay_tree_structure_illegal_ip(node)) {
        return false;
    } else {
        return splay_tree_contains_ip(tree, node);
    }
}

static inline void
splay_tree_node_merge(s_splay_tree_t *merged, s_splay_tree_t *node)
{
    s_doubly_linked_list_t *node_new;
    s_doubly_linked_list_t *node_tmp;
    s_doubly_linked_list_t *node_limit;

    assert_exit(splay_tree_structure_legal_ip(merged));
    assert_exit(splay_tree_structure_legal_ip(node));
    assert_exit(merged->nice == node->nice);

    node_limit = node_tmp = splay_tree_val_list_i(node);

    do {
        node_new = doubly_linked_list_create();
        doubly_linked_list_val_set(node_new, doubly_linked_list_val(node_tmp));

        doubly_linked_list_insert_before(merged->list, node_new);
        node_tmp = doubly_linked_list_next(node_tmp);
    } while (node_tmp != node_limit);
}

static inline s_splay_tree_t *
splay_tree_insert_i(s_splay_tree_t **tree, s_splay_tree_t *node)
{
    s_array_stack_t *path_stack;
    s_splay_tree_t *splay_node, **iterator;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(node));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_ordered_p(*tree));

    iterator = tree;
    splay_node = *iterator;
    path_stack = array_stack_create();

    while (splay_node) {
        if (node == splay_node) {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            array_stack_destroy(&path_stack);
            return splay_node;
        } else if (node->nice < splay_node->nice) {
            array_stack_push(path_stack, TREE_PATH_L_ENCODE(iterator));
            iterator = &splay_node->left;
        } else if (node->nice > splay_node->nice) {
            array_stack_push(path_stack, TREE_PATH_R_ENCODE(iterator));
            iterator = &splay_node->right;
        } else {
            splay_tree_node_merge(splay_node, node);
            splay_tree_splaying(path_stack);
            array_stack_destroy(&path_stack);
            return splay_node;
        }

        splay_node = *iterator;
    }

    *iterator = node;
    splay_tree_splaying(path_stack);
    array_stack_destroy(&path_stack);

    assert_exit(*tree == node);
    assert_exit(splay_tree_ordered_p(*tree));

    return node;
}

s_splay_tree_t *
splay_tree_insert(s_splay_tree_t **tree, s_splay_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(node)) {
        return PTR_INVALID;
    } else {
        return splay_tree_insert_i(tree, node);
    }
}

static inline bool
splay_tree_doubly_child_p(s_splay_tree_t *node)
{
    assert_exit(splay_tree_structure_legal_ip(node));

    if (node->left && node->right) {
        return true;
    } else {
        return false;
    }
}

static inline void
splay_tree_lt_doubly_child_strip(s_splay_tree_t **splay_node)
{
    s_splay_tree_t *node_strip;

    assert_exit(NON_NULL_PTR_P(splay_node));
    assert_exit(splay_tree_structure_legal_ip(*splay_node));

    node_strip = *splay_node;

    if (node_strip->left != NULL) {
        *splay_node = node_strip->left;
    } else {
        *splay_node = node_strip->right;
    }

    node_strip->left =  node_strip->right = NULL;
}

static inline s_splay_tree_t **
splay_tree_find_ptr_to_min(s_splay_tree_t **tree)
{
    s_splay_tree_t **min;
    s_splay_tree_t *splay;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    min = tree;
    splay = *tree;

    while (splay->left) {
        min = &splay->left;
        splay = *min;
    }

    return min;
}

static inline s_splay_tree_t **
splay_tree_find_ptr_to_max(s_splay_tree_t **tree)
{
    s_splay_tree_t **max;
    s_splay_tree_t *splay;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));

    max = tree;
    splay = *tree;

    while (splay->right) {
        max = &splay->right;
        splay = *max;
    }

    return max;
}

static inline void
splay_tree_swap_child(s_splay_tree_t *a, s_splay_tree_t *b)
{
    assert_exit(splay_tree_structure_legal_ip(a));
    assert_exit(splay_tree_structure_legal_ip(b));

    SWAP(a->left, b->left);
    SWAP(a->right, b->right);
}

static inline void
splay_tree_doubly_child_left_strip(s_splay_tree_t **splay_node)
{
    s_splay_tree_t *min;
    s_splay_tree_t *splay;
    s_splay_tree_t **min_node;

    assert_exit(NON_NULL_PTR_P(splay_node));
    assert_exit(splay_tree_structure_legal_ip(*splay_node));
    assert_exit(splay_tree_doubly_child_p(*splay_node));

    splay = *splay_node;

    if (splay->right->left == NULL) { /* short cut here */
        *splay_node = splay->right;
        splay->right->left = splay->left;
        splay->left = splay->right = NULL;
    } else {
        min_node = splay_tree_find_ptr_to_min(&splay->right);
        min = *min_node;

        splay_tree_swap_child(splay, min);
        *min_node = splay;
        *splay_node = min;

        splay_tree_lt_doubly_child_strip(min_node);
    }
}

static inline void
splay_tree_doubly_child_right_strip(s_splay_tree_t **splay_node)
{
    s_splay_tree_t *splay;
    s_splay_tree_t *max;
    s_splay_tree_t **max_node;

    assert_exit(NON_NULL_PTR_P(splay_node));
    assert_exit(splay_tree_structure_legal_ip(*splay_node));
    assert_exit(splay_tree_doubly_child_p(*splay_node));

    splay = *splay_node;

    if (splay->left->right == NULL) { /* short cut here */
        *splay_node = splay->left;
        splay->left->right = splay->right;
        splay->left = splay->right = NULL;
    } else {
        max_node = splay_tree_find_ptr_to_max(&splay->left);
        max = *max_node;

        splay_tree_swap_child(splay, max);
        *max_node = splay;
        *splay_node = max;

        splay_tree_lt_doubly_child_strip(max_node);
    }
}

static inline void
splay_tree_doubly_child_strip(s_splay_tree_t **splay_node, sint32 direction)
{
    assert_exit(NON_NULL_PTR_P(splay_node));
    assert_exit(splay_tree_structure_legal_ip(*splay_node));
    assert_exit(splay_tree_doubly_child_p(*splay_node));

    if (direction > 0) {
        splay_tree_doubly_child_right_strip(splay_node);
    } else {
        splay_tree_doubly_child_left_strip(splay_node);
    }
}

static inline void
splay_tree_child_strip(s_splay_tree_t **splay_node, sint32 direction)
{
    assert_exit(NON_NULL_PTR_P(splay_node));
    assert_exit(splay_tree_structure_legal_ip(*splay_node));

    if (splay_tree_doubly_child_p(*splay_node)) {
        splay_tree_doubly_child_strip(splay_node, direction);
    } else {
        splay_tree_lt_doubly_child_strip(splay_node);
    }
}

static inline s_splay_tree_t *
splay_tree_remove_i(s_splay_tree_t **tree, s_splay_tree_t *node)
{
    sint32 direction;
    s_splay_tree_t **iterator;
    s_splay_tree_t *removed_node, *splay_node;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(splay_tree_structure_legal_ip(*tree));
    assert_exit(splay_tree_ordered_p(*tree));
    assert_exit(splay_tree_structure_legal_ip(node));

    direction = 0;
    iterator = tree;
    splay_node = *tree;
    removed_node = NULL;

    while (splay_node) {
        if (node->nice > splay_node->nice) {
            direction++;
            iterator = &splay_node->right;
        } else if (node->nice < splay_node->nice) {
            direction--;
            iterator = &splay_node->left;
        } else if (node == splay_node) {
            removed_node = node;
            splay_tree_child_strip(iterator, direction);
            break;
        } else { /* node not in given tree */
            break;
        }

        splay_node = *iterator;
    }

    if (removed_node == NULL) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert_exit(splay_tree_ordered_p(*tree));
    return removed_node;
}

s_splay_tree_t *
splay_tree_remove(s_splay_tree_t **tree, s_splay_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else if (splay_tree_structure_illegal_ip(node)) {
        return PTR_INVALID;
    } else {
        return splay_tree_remove_i(tree, node);
    }
}

static inline void
splay_tree_iterate_i(s_splay_tree_t *tree, void (*handler)(void *))
{
    s_array_queue_t *queue;
    s_splay_tree_t *splay_node;

    assert_exit(NON_NULL_PTR_P(handler));
    assert_exit(splay_tree_structure_legal_ip(tree));

    queue = array_queue_create();
    array_queue_enter(queue, tree);

    while (!array_queue_empty_p(queue)) {
        splay_node = array_queue_leave(queue);
        handler(splay_node);

        if (splay_node->left) {
            array_queue_enter(queue, splay_node->left);
        }

        if (splay_node->right) {
            array_queue_enter(queue, splay_node->right);
        }
    }

    array_queue_destroy(&queue);
}

void
splay_tree_iterate(s_splay_tree_t *tree, void (*handler)(void *))
{
    if (NULL_PTR_P(handler)) {
        return;
    } else if (splay_tree_structure_illegal_ip(tree)) {
        return;
    } else {
        splay_tree_iterate_i(tree, handler);
    }
}

