void
binary_search_tree_nice_set(s_binary_search_tree_t *tree, sint64 nice)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        tree->nice = nice;
    }
}

sint64
binary_search_tree_nice(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        return tree->nice;
    } else {
        return TREE_NICE_INVALID;
    }
}

s_binary_search_tree_t *
binary_search_tree_left(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        return tree->left;
    } else {
        return PTR_INVALID;
    }
}

s_binary_search_tree_t *
binary_search_tree_right(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        return tree->right;
    } else {
        return PTR_INVALID;
    }
}

s_binary_search_tree_t *
binary_search_tree_create(void)
{
    s_binary_search_tree_t *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    binary_search_tree_initial_i(tree, 0);

    return tree;
}

static inline void
binary_search_tree_initial_i(s_binary_search_tree_t *tree, sint64 nice)
{
    assert_exit(!complain_null_pointer_p(tree));

    tree->nice = nice;
    tree->left = tree->right = NULL;
}

void
binary_search_tree_initial(s_binary_search_tree_t *tree, sint64 nice)
{
    if (!complain_null_pointer_p(tree)) {
        binary_search_tree_initial_i(tree, nice);
    }
}

static inline bool
binary_search_tree_structure_legal_p(s_binary_search_tree_t *tree)
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
binary_search_tree_destroy_i(s_binary_search_tree_t *tree)
{
    s_array_queue_t *queue;
    s_binary_search_tree_t *binary_node;

    assert_exit(binary_search_tree_structure_legal_p(tree));

    queue = array_queue_create();
    array_queue_enter(queue, tree);

    while (!array_queue_empty_p(queue)) {
        binary_node = array_queue_leave(queue);

        if (binary_node->left != NULL) {
            array_queue_enter(queue, binary_node->left);
        }

        if (binary_node->right != NULL) {
            array_queue_enter(queue, binary_node->right);
        }

        memory_cache_free(binary_node);
    }

    array_queue_destroy(&queue);
}

void
binary_search_tree_destroy(s_binary_search_tree_t **tree)
{
    if (complain_null_pointer_p(tree)) {
        return;
    } else if (binary_search_tree_structure_legal_p(*tree)) {
        binary_search_tree_destroy_i(*tree);
        *tree = NULL;
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_i(s_binary_search_tree_t *tree, sint64 nice)
{
    sint64 node_nice;

    assert_exit(binary_search_tree_structure_legal_p(tree));

    while (tree) {
        node_nice = tree->nice;
        if (nice > node_nice) {
            tree = tree->right;
        } else if (nice < node_nice) {
            tree = tree->left;
        } else {
            return tree;
        }
    }

    return NULL;
}

s_binary_search_tree_t *
binary_search_tree_find(s_binary_search_tree_t *tree, sint64 nice)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_i(tree, nice);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_min_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_p(tree));

    while (tree->left) {
        tree = tree->left;
    }

    return tree;
}

s_binary_search_tree_t  *
binary_search_tree_find_min(s_binary_search_tree_t *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_min_i(tree);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_max_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_p(tree));

    while (tree->right) {
        tree = tree->right;
    }

    return tree;
}

s_binary_search_tree_t *
binary_search_tree_find_max(s_binary_search_tree_t *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_max_i(tree);
    }
}

static inline sint32
binary_search_tree_height_i(s_binary_search_tree_t *tree)
{
    sint32 left;
    sint32 right;

    if (!tree) {
        return -1;
    } else {
        left = binary_search_tree_height_i(tree->left);
        right = binary_search_tree_height_i(tree->right);

        return MAX_S32(left, right) + 1;
    }
}

sint32
binary_search_tree_height(s_binary_search_tree_t *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return -1;
    } else {
        return binary_search_tree_height_i(tree);
    }
}

static inline bool
binary_search_tree_contains_p_i(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    bool retval;
    s_binary_search_tree_t *left, *right;

    assert_exit(binary_search_tree_structure_legal_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(node));

    retval = false;

    while (tree) {
        if (node == tree) {
            return true;
        } else if (node->nice > tree->nice) {
            tree = tree->right;
        } else if (node->nice < tree->nice) {
            tree = tree->left;
        } else {
            left = tree->left;
            right = tree->right;

            if (left && node->nice == left->nice) { // Handle repeated nice
                retval = binary_search_tree_contains_p_i(left, node);
            }
            if (!retval && right && node->nice == right->nice) {
                retval = binary_search_tree_contains_p_i(right, node);
            }

            return retval;
        }
    }

    return false;
}

bool
binary_search_tree_contains_p(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return false;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return false;
    } else {
        return binary_search_tree_contains_p_i(tree, node);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_insert_i(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    sint64 nice;
    sint32 path_direction;
    s_binary_search_tree_t *binary_node;
    s_binary_search_tree_t **iterator_node;

    assert_exit(binary_search_tree_structure_legal_p(tree));
    assert_exit(binary_search_tree_ordered_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(node));

    nice = node->nice;
    path_direction = 0;
    iterator_node = &tree;

    while (*iterator_node) {
        binary_node = *iterator_node;
        if (nice < binary_node->nice) {
            path_direction--;
            iterator_node = &binary_node->left;
        } else if (nice > binary_node->nice) {
            path_direction++;
            iterator_node = &binary_node->right;
        } else if (binary_node == node) {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            return NULL;
        } else {
            if (path_direction > 0) { // If right is heavy, inserted to left.
                node->left = binary_node->left;
                binary_node->left = node;
                node->right = NULL;
            } else {
                node->right = binary_node->right;
                binary_node->right = node;
                node->left = NULL;
            }

            assert_exit(binary_search_tree_ordered_p(tree));
            return node;
        }
    }

    *iterator_node = node;

    assert_exit(binary_search_tree_ordered_p(tree));
    return node;
}

s_binary_search_tree_t *
binary_search_tree_insert(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_insert_i(tree, node);
    }
}

static inline bool
binary_search_tree_doubly_child_p(s_binary_search_tree_t *node)
{
    assert_exit(binary_search_tree_structure_legal_p(node));

    if (node->left && node->right) {
        return true;
    } else {
        return false;
    }
}

static inline s_binary_search_tree_t **
binary_search_tree_find_ptr_to_max(s_binary_search_tree_t **tree)
{
    s_binary_search_tree_t **max;
    s_binary_search_tree_t *node;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(*tree));

    max = tree;
    node = *max;

    while (NULL != node->right) {
        max = &node->right;
        node = *max;
    }

    return max;
}

static inline s_binary_search_tree_t **
binary_search_tree_find_ptr_to_min(s_binary_search_tree_t **tree)
{
    s_binary_search_tree_t **min;
    s_binary_search_tree_t *node;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(*tree));

    min = tree;
    node = *min;

    while (NULL != node->left) {
        min = &node->left;
        node = *min;
    }

    return min;
}

static inline void
binary_search_tree_swap_child(s_binary_search_tree_t *a,
    s_binary_search_tree_t *b)
{
    void *tmp;

    assert_exit(binary_search_tree_structure_legal_p(a));
    assert_exit(binary_search_tree_structure_legal_p(b));

    tmp = a->left;
    a->left = b->left;
    b->left = tmp;

    tmp = a->right;
    a->right = b->right;
    b->right = tmp;
}

static inline void
binary_search_tree_lt_doubly_child_strip(s_binary_search_tree_t **pre,
    s_binary_search_tree_t *node)
{
    assert_exit(!complain_null_pointer_p(pre));
    assert_exit(binary_search_tree_structure_legal_p(node));
    assert_exit(binary_search_tree_structure_legal_p(*pre));
    assert_exit(!binary_search_tree_doubly_child_p(node));
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
binary_search_tree_child_strip_from_max(s_binary_search_tree_t **node_pre)
{
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t *max;
    s_binary_search_tree_t **max_pre;

    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(binary_search_tree_structure_legal_p(*node_pre));
    assert_exit(binary_search_tree_doubly_child_p(*node_pre));

    binary = *node_pre;
    if (!binary->left->right) {                      // short cut here
        *node_pre = binary->left;
        binary->left->right = binary->right;
        binary->left = binary->right = NULL;
    } else {
        max_pre = binary_search_tree_find_ptr_to_max(&binary->left);
        max = *max_pre;

        binary_search_tree_swap_child(binary, max);
        *max_pre = binary;
        *node_pre = max;

        binary_search_tree_lt_doubly_child_strip(max_pre, binary);
    }
}

static inline void
binary_search_tree_child_strip_from_min(s_binary_search_tree_t **node_pre)
{
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t *min;
    s_binary_search_tree_t **min_pre;

    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(binary_search_tree_structure_legal_p(*node_pre));
    assert_exit(binary_search_tree_doubly_child_p(*node_pre));

    binary = *node_pre;

    if (!binary->right->left) {                      // short cut here
        *node_pre = binary->right;
        binary->right->left = binary->left;
        binary->left = binary->right = NULL;
    } else {
        min_pre = binary_search_tree_find_ptr_to_min(&binary->right);
        min = *min_pre;

        binary_search_tree_swap_child(binary, min);
        *min_pre = binary;
        *node_pre = min;

        binary_search_tree_lt_doubly_child_strip(min_pre, binary);
    }
}

static inline void
binary_search_tree_doubly_child_strip(s_binary_search_tree_t **node_pre)
{
    assert_exit(!complain_null_pointer_p(node_pre));
    assert_exit(binary_search_tree_structure_legal_p(*node_pre));
    assert_exit(binary_search_tree_doubly_child_p(*node_pre));

    if (direct > 0) {
        binary_search_tree_child_strip_from_max(node_pre);
    } else {
        binary_search_tree_child_strip_from_min(node_pre);
    }
    direct = 0;
}

static inline s_binary_search_tree_t *
binary_search_tree_remove_i(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node)
{
    sint64 nice;
    s_binary_search_tree_t *n;
    s_binary_search_tree_t *removed;
    s_binary_search_tree_t **pre;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(*tree));
    assert_exit(binary_search_tree_ordered_p(*tree));
    assert_exit(binary_search_tree_ordered_p(*tree));
    assert_exit(binary_search_tree_structure_legal_p(node));

    n = *(pre = tree);
    nice = node->nice;
    removed = NULL;

    while (n) {
        if (nice > n->nice) {
            pre = &n->right;
            direct++;
        } else if (nice < n->nice) {
            pre = &n->left;
            direct--;
        } else if (node != n) {
            if (n->left && nice == n->left->nice) {
                removed = binary_search_tree_remove_i(&n->left, node);
            }
            if (NULL == removed && n->right && nice == n->right->nice) {
                removed = binary_search_tree_remove_i(&n->right, node);
            }
            break;
        } else if (binary_search_tree_doubly_child_p(n)) {
            binary_search_tree_doubly_child_strip(pre);
            return n;
        } else {
            binary_search_tree_lt_doubly_child_strip(pre, n);
            return n;
        }
        n = *pre;
    }

    if (NULL == removed) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert_exit(binary_search_tree_ordered_p(*tree));
    return removed;
}

s_binary_search_tree_t *
binary_search_tree_remove(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node)
{
    if (complain_null_pointer_p(tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(*tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_remove_i(tree, node);
    }
}

static inline void
binary_search_tree_iterate_i(s_binary_search_tree_t *tree,
    void (*handle)(void *), e_iter_order_t order)
{
    assert_exit(LEGAL_ORDER_P(order));
    assert_exit(!complain_null_pointer_p(handle));

    if (tree) {
        if (ORDER_PRE == order) {
            handle(tree);
        }

        binary_search_tree_iterate_i(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(tree);
        }

        binary_search_tree_iterate_i(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(tree);
        }
    }
}

void
binary_search_tree_iterate(s_binary_search_tree_t *tree,
    void (*handle)(void *), e_iter_order_t order)
{
    if (complain_null_pointer_p(handle)) {
        return;
    } else if (!LEGAL_ORDER_P(order)) {
        pr_log_warn("Invalid value of enum ITER_ORDER.\n");
    } else if (binary_search_tree_structure_legal_p(tree)) {
        binary_search_tree_iterate_i(tree, handle, order);
    }
}

