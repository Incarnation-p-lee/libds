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
    assert_exit(!NULL_PTR_P(tree));

    tree->nice = nice;
    tree->left = tree->right = NULL;

    assert_exit(binary_search_tree_structure_legal_p(tree));
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
    if (NULL_PTR_P(tree)) {
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

    assert_exit(!NULL_PTR_P(tree));
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

    assert_exit(!NULL_PTR_P(tree));
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
binary_search_tree_lt_doubly_child_strip(s_binary_search_tree_t **binary_node)
{
    s_binary_search_tree_t *node_strip;

    assert_exit(!complain_null_pointer_p(binary_node));
    assert_exit(binary_search_tree_structure_legal_p(*binary_node));
    assert_exit(!binary_search_tree_doubly_child_p(*binary_node));

    node_strip = *binary_node;

    if (node_strip->left != NULL) {
        *binary_node = node_strip->left;
    } else {
        *binary_node = node_strip->right;
    }

    node_strip->left = node_strip->right = NULL;
}

static inline void
binary_search_tree_child_strip_from_max(s_binary_search_tree_t **binary_node)
{
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t *max;
    s_binary_search_tree_t **max_node;

    assert_exit(!complain_null_pointer_p(binary_node));
    assert_exit(binary_search_tree_structure_legal_p(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    binary = *binary_node;

    if (!binary->left->right) { // short cut here
        *binary_node = binary->left;
        binary->left->right = binary->right;
        binary->left = binary->right = NULL;
    } else {
        max_node = binary_search_tree_find_ptr_to_max(&binary->left);
        max = *max_node;

        binary_search_tree_swap_child(binary, max);
        *max_node = binary;
        *binary_node = max;
        binary_search_tree_lt_doubly_child_strip(max_node);
    }
}

static inline void
binary_search_tree_child_strip_from_min(s_binary_search_tree_t **binary_node)
{
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t *min;
    s_binary_search_tree_t **min_node;

    assert_exit(!complain_null_pointer_p(binary_node));
    assert_exit(binary_search_tree_structure_legal_p(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    binary = *binary_node;

    if (!binary->right->left) { // short cut here
        *binary_node = binary->right;
        binary->right->left = binary->left;
        binary->left = binary->right = NULL;
    } else {
        min_node = binary_search_tree_find_ptr_to_min(&binary->right);
        min = *min_node;

        binary_search_tree_swap_child(binary, min);
        *min_node = binary;
        *binary_node = min;

        binary_search_tree_lt_doubly_child_strip(min_node);
    }
}

static inline void
binary_search_tree_doubly_child_strip(s_binary_search_tree_t **binary_node,
    sint32 direction)
{
    assert_exit(!complain_null_pointer_p(binary_node));
    assert_exit(binary_search_tree_structure_legal_p(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    if (direction > 0) {
        binary_search_tree_child_strip_from_max(binary_node);
    } else {
        binary_search_tree_child_strip_from_min(binary_node);
    }
}

static inline void
binary_search_tree_child_strip(s_binary_search_tree_t **binary_node,
    sint32 direction)
{
    assert_exit(!complain_null_pointer_p(binary_node));
    assert_exit(binary_search_tree_structure_legal_p(*binary_node));

    if (binary_search_tree_doubly_child_p(*binary_node)) {
        binary_search_tree_doubly_child_strip(binary_node, direction);
    } else {
        binary_search_tree_lt_doubly_child_strip(binary_node);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_repeated_remove(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node, sint32 direction)
{
    sint64 nice;
    s_array_queue_t *queue;
    s_binary_search_tree_t **iterator;
    s_binary_search_tree_t *binary_node, *removed_node;

    assert_exit(!NULL_PTR_P(tree));
    assert_exit(binary_search_tree_structure_legal_p(node));
    assert_exit(binary_search_tree_structure_legal_p(*tree));
    assert_exit(binary_search_tree_ordered_p(*tree));
    assert_exit((*tree)->nice == node->nice);
    assert_exit(*tree != node);

    iterator = tree;
    removed_node = NULL;

    nice = node->nice;
    queue = array_queue_create();
    array_queue_enter(queue, iterator);

    while (!array_queue_empty_p(queue)) {
         iterator = array_queue_leave(queue);
         binary_node = *iterator;
         if (binary_node == node) {
             removed_node = node;
             binary_search_tree_child_strip(iterator, direction);
             break;
         } else if (binary_node->left && binary_node->left->nice == nice) {
             direction--;
             array_queue_enter(queue, &binary_node->left);
         } else if (binary_node->right && binary_node->right->nice == nice) {
             direction++;
             array_queue_enter(queue, &binary_node->right);
         }
    }

    array_queue_destroy(&queue);
    return removed_node;
}

static inline s_binary_search_tree_t *
binary_search_tree_remove_i(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node)
{
    sint32 direction;
    s_binary_search_tree_t **iterator;
    s_binary_search_tree_t *binary_node, *removed_node;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(binary_search_tree_structure_legal_p(*tree));
    assert_exit(binary_search_tree_ordered_p(*tree));
    assert_exit(binary_search_tree_structure_legal_p(node));

    direction = 0;
    removed_node = NULL;
    iterator = tree;
    binary_node = *tree;

    while (binary_node) {
        if (node->nice > binary_node->nice) {
            direction++;
            iterator = &binary_node->right;
        } else if (node->nice < binary_node->nice) {
            direction--;
            iterator = &binary_node->left;
        } else if (node == binary_node) {
            removed_node = node;
            binary_search_tree_child_strip(iterator, direction);
            break;
        } else {
            removed_node = binary_search_tree_repeated_remove(iterator, node, direction);
            break;
        }
        binary_node = *iterator;
    }

    if (removed_node == NULL) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert_exit(binary_search_tree_ordered_p(*tree));
    return removed_node;
}

s_binary_search_tree_t *
binary_search_tree_remove(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node)
{
    if (NULL_PTR_P(tree)) {
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
binary_search_tree_iterate_i(s_binary_search_tree_t *tree, void (*handler)(void *))
{
    s_array_queue_t *queue_slave;
    s_array_queue_t *queue_master;
    s_binary_search_tree_t *binary_node;

    assert_exit(!complain_null_pointer_p(handler));
    assert_exit(binary_search_tree_structure_legal_p(tree));

    queue_slave = array_queue_create();
    queue_master = array_queue_create();
    array_queue_enter(queue_master, tree);

    while (!array_queue_empty_p(queue_master)) {
        while (!array_queue_empty_p(queue_master)) {
            binary_node = array_queue_leave(queue_master);
            handler(binary_node);

            if (binary_node->left) {
                array_queue_enter(queue_slave, binary_node->left);
            }
            if (binary_node->right) {
                array_queue_enter(queue_slave, binary_node->right);
            }
        }
        swap_pointer((void **)&queue_master, (void **)&queue_slave);
    }

    array_queue_destroy(&queue_slave);
    array_queue_destroy(&queue_master);
}

void
binary_search_tree_iterate(s_binary_search_tree_t *tree, void (*handler)(void *))
{
    if (NULL_PTR_P(handler)) {
        return;
    } else if (!binary_search_tree_structure_legal_p(tree)) {
        return;
    } else {
        binary_search_tree_iterate_i(tree, handler);
    }
}

