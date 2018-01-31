void
binary_search_tree_nice_set(s_binary_search_tree_t *tree, sint64 nice)
{
    if (binary_search_tree_structure_legal_ip(tree)) {
        tree->nice = nice;
    }
}

static inline sint64
binary_search_tree_nice_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_ip(tree));

    return tree->nice;
}

static inline s_binary_search_tree_t *
binary_search_tree_left_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_ip(tree));

    return tree->left;
}

static inline s_binary_search_tree_t *
binary_search_tree_right_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_ip(tree));

    return tree->right;
}

sint64
binary_search_tree_nice(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return TREE_NICE_INVALID;
    } else {
        return binary_search_tree_nice_i(tree);
    }
}

s_binary_search_tree_t *
binary_search_tree_left(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_left_i(tree);
    }
}

s_binary_search_tree_t *
binary_search_tree_right(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_right_i(tree);
    }
}

s_doubly_linked_list_t *
binary_search_tree_val_list(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_val_list_i(tree);
    }
}

static inline s_doubly_linked_list_t *
binary_search_tree_val_list_i(s_binary_search_tree_t *tree)
{
    assert_exit(binary_search_tree_structure_legal_ip(tree));

    return tree->list;
}

s_binary_search_tree_t *
binary_search_tree_create(void *val, sint64 nice)
{
    s_binary_search_tree_t *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    tree->list = doubly_linked_list_create();

    binary_search_tree_initial_i(tree, val, nice);

    return tree;
}

static inline void
binary_search_tree_initial_i(s_binary_search_tree_t *tree, void *val,
    sint64 nice)
{
    assert_exit(NON_NULL_PTR_P(tree));

    tree->nice = nice;
    tree->left = tree->right = NULL;

    doubly_linked_list_val_set(tree->list, val);
}

void
binary_search_tree_initial(s_binary_search_tree_t *tree, void *val, sint64 nice)
{
    if (NON_NULL_PTR_P(tree)) {
        binary_search_tree_initial_i(tree, val, nice);
    }
}

static inline bool
binary_search_tree_structure_legal_ip(s_binary_search_tree_t *tree)
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

bool
binary_search_tree_structure_legal_p(s_binary_search_tree_t *tree)
{
    return binary_search_tree_structure_legal_ip(tree);
}

static inline bool
binary_search_tree_structure_illegal_ip(s_binary_search_tree_t *tree)
{
    return !binary_search_tree_structure_legal_ip(tree);
}

bool
binary_search_tree_structure_illegal_p(s_binary_search_tree_t *tree)
{
    return binary_search_tree_structure_illegal_ip(tree);
}

static inline void
binary_search_tree_destroy_i(s_binary_search_tree_t *tree)
{
    s_array_queue_t *queue;
    s_binary_search_tree_t *binary_node;

    assert_exit(binary_search_tree_structure_legal_ip(tree));

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

        doubly_linked_list_destroy(&binary_node->list);
        memory_cache_free(binary_node);
    }

    array_queue_destroy(&queue);
}

void
binary_search_tree_destroy(s_binary_search_tree_t **tree)
{
    if (NULL_PTR_P(tree)) {
        return;
    } else if (binary_search_tree_structure_legal_ip(*tree)) {
        binary_search_tree_destroy_i(*tree);
        *tree = NULL;
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_i(s_binary_search_tree_t *tree, sint64 nice)
{
    s_binary_search_tree_t *binary;

    assert_exit(binary_search_tree_structure_legal_ip(tree));

    binary = tree;

    while (binary) {
        if (nice < binary->nice) {
            binary = binary->left;
        } else if (nice > binary->nice) {
            binary = binary->right;
        } else {
            return binary;
        }
    }

    return NULL;
}

s_binary_search_tree_t *
binary_search_tree_find(s_binary_search_tree_t *tree, sint64 nice)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_i(tree, nice);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_min_i(s_binary_search_tree_t *tree)
{
    s_binary_search_tree_t *binary;

    assert_exit(binary_search_tree_structure_legal_ip(tree));

    binary = tree;

    while (binary->left) {
        binary = binary->left;
    }

    return binary;
}

s_binary_search_tree_t *
binary_search_tree_find_min(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_min_i(tree);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_find_max_i(s_binary_search_tree_t *tree)
{
    s_binary_search_tree_t *binary;

    assert_exit(binary_search_tree_structure_legal_ip(tree));

    binary = tree;

    while (binary->right) {
        binary = binary->right;
    }

    return binary;
}

s_binary_search_tree_t *
binary_search_tree_find_max(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_find_max_i(tree);
    }
}

static inline sint32
binary_search_tree_height_i(s_binary_search_tree_t *tree)
{
    sint32 height;
    s_binary_search_tree_t *binary_node;
    s_array_queue_t *queue_master, *queue_slave;

    if (!tree) {
        return -1;
    } else {
        height = -1;
        binary_node = tree;

        queue_slave = array_queue_create();
        queue_master = array_queue_create();
        array_queue_enter(queue_master, binary_node);

        while (!array_queue_empty_p(queue_master)) {
            binary_node = array_queue_leave(queue_master);

            if (binary_node->left) {
                array_queue_enter(queue_slave, binary_node->left);
            }

            if (binary_node->right) {
                array_queue_enter(queue_slave, binary_node->right);
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
binary_search_tree_height(s_binary_search_tree_t *tree)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return -1;
    } else {
        return binary_search_tree_height_i(tree);
    }
}

static inline bool
binary_search_tree_contains_ip(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    sint64 nice;
    s_binary_search_tree_t *binary_node;

    assert_exit(binary_search_tree_structure_legal_ip(tree));
    assert_exit(binary_search_tree_structure_legal_ip(node));

    binary_node = tree;
    nice = node->nice;

    while (binary_node) {
        if (binary_node == node) {
            return true;
        } else if (nice < binary_node->nice) {
            binary_node = binary_node->left;
        } else if (nice > binary_node->nice) {
            binary_node = binary_node->right;
        } else {
            return false;
        }
    }

    return false;
}

bool
binary_search_tree_contains_p(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return false;
    } else if (binary_search_tree_structure_illegal_ip(node)) {
        return false;
    } else {
        return binary_search_tree_contains_ip(tree, node);
    }
}

static inline void
binary_search_tree_node_merge(s_binary_search_tree_t *merged,
    s_binary_search_tree_t *node)
{
    s_doubly_linked_list_t *node_new;
    s_doubly_linked_list_t *node_tmp;
    s_doubly_linked_list_t *node_limit;

    assert_exit(binary_search_tree_structure_legal_ip(merged));
    assert_exit(binary_search_tree_structure_legal_ip(node));
    assert_exit(merged->nice == node->nice);

    node_limit = node_tmp = binary_search_tree_val_list_i(node);

    do {
        node_new = doubly_linked_list_create();
        doubly_linked_list_val_set(node_new, doubly_linked_list_val(node_tmp));

        doubly_linked_list_insert_before(merged->list, node_new);
        node_tmp = doubly_linked_list_next(node_tmp);
    } while (node_tmp != node_limit);
}

static inline s_binary_search_tree_t *
binary_search_tree_insert_i(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *inserted)
{
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t **iterator;

    assert_exit(binary_search_tree_structure_legal_ip(tree));
    assert_exit(binary_search_tree_structure_legal_ip(inserted));
    assert_exit(binary_search_tree_ordered_p(tree));

    iterator = &tree;
    binary = *iterator;

    while (binary) {
        if (inserted == binary) {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            return inserted;
        } else if (inserted->nice < binary->nice) {
            iterator = &binary->left;
        } else if (inserted->nice > binary->nice) {
            iterator= &binary->right;
        } else { /* the same nice, merge to one node */
            binary_search_tree_node_merge(binary, inserted);
            return binary;
        }

        binary = *iterator;
    }

    *iterator = inserted;
    assert_exit(binary_search_tree_ordered_p(tree));

    return inserted;
}

s_binary_search_tree_t *
binary_search_tree_insert(s_binary_search_tree_t *tree,
    s_binary_search_tree_t *node)
{
    if (binary_search_tree_structure_illegal_ip(tree)) {
        return PTR_INVALID;
    } else if (binary_search_tree_structure_illegal_ip(node)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_insert_i(tree, node);
    }
}

static inline bool
binary_search_tree_doubly_child_p(s_binary_search_tree_t *node)
{
    assert_exit(binary_search_tree_structure_legal_ip(node));

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

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(binary_search_tree_structure_legal_ip(*tree));

    max = tree;
    node = *max;

    while (node->right) {
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

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(binary_search_tree_structure_legal_ip(*tree));

    min = tree;
    node = *min;

    while (node->left) {
        min = &node->left;
        node = *min;
    }

    return min;
}

static inline void
binary_search_tree_swap_child(s_binary_search_tree_t *a,
    s_binary_search_tree_t *b)
{
    assert_exit(binary_search_tree_structure_legal_ip(a));
    assert_exit(binary_search_tree_structure_legal_ip(b));

    SWAP(a->left, b->left);
    SWAP(a->right, b->right);
}

static inline void
binary_search_tree_lt_doubly_child_strip(s_binary_search_tree_t **node)
{
    s_binary_search_tree_t *node_strip;

    assert_exit(NON_NULL_PTR_P(node));
    assert_exit(binary_search_tree_structure_legal_ip(*node));
    assert_exit(!binary_search_tree_doubly_child_p(*node));

    node_strip = *node;

    if (node_strip->left) {
        *node = node_strip->left;
    } else {
        *node = node_strip->right;
    }

    node_strip->left = node_strip->right = NULL;
}

static inline void
binary_search_tree_child_left_strip(s_binary_search_tree_t **binary_node)
{
    s_binary_search_tree_t *max;
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t **max_node;

    assert_exit(NON_NULL_PTR_P(binary_node));
    assert_exit(binary_search_tree_structure_legal_ip(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    binary = *binary_node;

    if (binary->left->right == NULL) { /* short cut here */
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
binary_search_tree_child_right_strip(s_binary_search_tree_t **binary_node)
{
    s_binary_search_tree_t *min;
    s_binary_search_tree_t *binary;
    s_binary_search_tree_t **min_node;

    assert_exit(NON_NULL_PTR_P(binary_node));
    assert_exit(binary_search_tree_structure_legal_ip(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    binary = *binary_node;

    if (binary->right->left == NULL) { /* short cut here */
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
    assert_exit(NON_NULL_PTR_P(binary_node));
    assert_exit(binary_search_tree_structure_legal_ip(*binary_node));
    assert_exit(binary_search_tree_doubly_child_p(*binary_node));

    if (direction > 0) {
        binary_search_tree_child_left_strip(binary_node);
    } else {
        binary_search_tree_child_right_strip(binary_node);
    }
}

static inline void
binary_search_tree_child_strip(s_binary_search_tree_t **binary_node,
    sint32 direction)
{
    assert_exit(NON_NULL_PTR_P(binary_node));
    assert_exit(binary_search_tree_structure_legal_ip(*binary_node));

    if (binary_search_tree_doubly_child_p(*binary_node)) {
        binary_search_tree_doubly_child_strip(binary_node, direction);
    } else {
        binary_search_tree_lt_doubly_child_strip(binary_node);
    }
}

static inline s_binary_search_tree_t *
binary_search_tree_remove_i(s_binary_search_tree_t **tree,
    s_binary_search_tree_t *node)
{
    sint32 direction;
    s_binary_search_tree_t **iterator;
    s_binary_search_tree_t *binary_node, *removed_node;

    assert_exit(NON_NULL_PTR_P(tree));
    assert_exit(binary_search_tree_structure_legal_ip(*tree));
    assert_exit(binary_search_tree_ordered_p(*tree));
    assert_exit(binary_search_tree_structure_legal_ip(node));

    direction = 0;
    iterator = tree;
    removed_node = NULL;
    binary_node = *tree;

    while (binary_node) {
        if (node->nice < binary_node->nice) {
            direction--;
            iterator = &binary_node->left;
        } else if (node->nice > binary_node->nice) {
            direction++;
            iterator = &binary_node->right;
        } else if (node == binary_node) {
            removed_node = node;
            binary_search_tree_child_strip(iterator, direction);
            break;
        } else { /* node not in given tree */
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
    } else if (binary_search_tree_structure_illegal_ip(*tree)) {
        return PTR_INVALID;
    } else if (binary_search_tree_structure_illegal_ip(node)) {
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

    assert_exit(NON_NULL_PTR_P(handler));
    assert_exit(binary_search_tree_structure_legal_ip(tree));

    queue_slave = array_queue_create();
    queue_master = array_queue_create();
    array_queue_enter(queue_master, tree);

    while (!array_queue_empty_p(queue_master)) {
        binary_node = array_queue_leave(queue_master);
        handler(binary_node);

        if (binary_node->left) {
            array_queue_enter(queue_slave, binary_node->left);
        }

        if (binary_node->right) {
            array_queue_enter(queue_slave, binary_node->right);
        }

        if (array_queue_empty_p(queue_master)) {
            swap_pointer((void **)&queue_master, (void **)&queue_slave);
        }
    }

    array_queue_destroy(&queue_slave);
    array_queue_destroy(&queue_master);
}

void
binary_search_tree_iterate(s_binary_search_tree_t *tree, void (*handler)(void *))
{
    if (NULL_PTR_P(handler)) {
        return;
    } else if (binary_search_tree_structure_illegal_ip(tree)) {
        return;
    } else {
        binary_search_tree_iterate_i(tree, handler);
    }
}

