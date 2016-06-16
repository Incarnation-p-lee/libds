void
binary_search_tree_node_nice_set(struct binary_search_tree *tree, sint64 nice)
{
    tree->nice = nice;
}

sint64
binary_search_tree_nice(struct binary_search_tree *tree)
{
    return tree->nice;
}

struct binary_search_tree *
binary_search_tree_left(struct binary_search_tree *tree)
{
    return tree->left;
}

struct binary_search_tree *
binary_search_tree_right(struct binary_search_tree *tree)
{
    return tree->right;
}

void
binary_search_tree_left_set(struct binary_search_tree *tree,
    struct binary_search_tree *left)
{
    tree->left = left;
}

void
binary_search_tree_right_set(struct binary_search_tree *tree,
    struct binary_search_tree *right)
{
    tree->right = right;
}

struct binary_search_tree *
binary_search_tree_create(void)
{
    struct binary_search_tree *tree;

    tree = memory_cache_allocate(sizeof(*tree));
    binary_search_tree_initial_internal(tree, 0);

    return tree;
}

static inline void
binary_search_tree_initial_internal(struct binary_search_tree *tree,
    sint64 nice)
{
    assert(!complain_null_pointer_p(tree));

    tree->left = NULL;
    tree->right = NULL;
    tree->nice = nice;
}

void
binary_search_tree_initial(struct binary_search_tree *tree, sint64 nice)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        binary_search_tree_initial_internal(tree, nice);
    }
}

static inline bool
binary_search_tree_structure_legal_p(struct binary_search_tree *tree)
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
binary_search_tree_node_destroy(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    memory_cache_free(node);
}

static inline void
binary_search_tree_destroy_internal(struct binary_search_tree **tree)
{
    if (*tree && tree) {
        /*
         * destroy node in post iterater order.
         * Warning: sometime if nested function call is too deepth,
         *     it may reach the default limitation of elf stack size, 8192KB.
         *     use ulimit -s unlimited or refine this function without nested.
         */
        binary_search_tree_destroy_internal(&(*tree)->left);
        binary_search_tree_destroy_internal(&(*tree)->right);
        binary_search_tree_node_destroy(*tree);
        *tree = NULL;
    }
}

void
binary_search_tree_destroy(struct binary_search_tree **tree)
{
    if (complain_null_pointer_p(tree)) {
        return;
    } else if (binary_search_tree_structure_legal_p(*tree)) {
        binary_search_tree_destroy_internal(tree);
    }
}

static inline struct binary_search_tree *
binary_search_tree_find_internal(struct binary_search_tree *tree,
    sint64 nice)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        while (tree) {
            if (nice > binary_search_tree_nice(tree)) {
                tree = tree->right;
            } else if (nice < binary_search_tree_nice(tree)) {
                tree = tree->left;
            } else {
                return tree;
            }
        }

        return NULL;
    }
}

struct binary_search_tree *
binary_search_tree_find(struct binary_search_tree *tree, sint64 nice)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_find_internal(tree, nice);
    }
}

static inline struct binary_search_tree *
binary_search_tree_find_min_internal(struct binary_search_tree *tree)
{
    assert(binary_search_tree_structure_legal_p(tree));

    while (tree->left) {
        tree = tree->left;
    }

    return tree;
}

struct binary_search_tree  *
binary_search_tree_find_min(struct binary_search_tree *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_find_min_internal(tree);
    }
}

static inline struct binary_search_tree *
binary_search_tree_find_max_internal(struct binary_search_tree *tree)
{
    assert(binary_search_tree_structure_legal_p(tree));

    while (tree->right) {
        tree = tree->right;
    }

    return tree;
}

struct binary_search_tree *
binary_search_tree_find_max(struct binary_search_tree *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_find_max_internal(tree);
    }
}

static inline sint32
binary_search_tree_height_internal(struct binary_search_tree *tree)
{
    sint32 left;
    sint32 right;

    if (!tree) {
        return -1;
    } else {
        left = binary_search_tree_height_internal(tree->left);
        right = binary_search_tree_height_internal(tree->right);

        return MAX_S32(left, right) + 1;
    }
}

sint32
binary_search_tree_height(struct binary_search_tree *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return -1;
    } else {
        return binary_search_tree_height_internal(tree);
    }
}

static inline bool
binary_search_tree_contains_p_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    bool retval;
    sint64 nice;
    struct binary_search_tree *left;
    struct binary_search_tree *right;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(binary_search_tree_structure_legal_p(node));

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
                retval = binary_search_tree_contains_p_internal(left, node);
            }
            if (!retval && right && nice == right->nice) {
                retval = binary_search_tree_contains_p_internal(right, node);
            }

            return retval;
        }
    }

    return false;
}

bool
binary_search_tree_contains_p(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return false;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return false;
    } else {
        return binary_search_tree_contains_p_internal(tree, node);
    }
}

static inline struct binary_search_tree *
binary_search_tree_insert_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    sint64 nice;
    struct binary_search_tree **iter;
    struct binary_search_tree *binary;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));
    assert(binary_search_tree_structure_legal_p(node));

    iter = tree;
    nice = node->nice;

    while (*iter) {
        if (nice > (*iter)->nice) {
            iter = &(*iter)->right;
            direct++;
        } else if (nice < (*iter)->nice) {
            iter = &(*iter)->left;
            direct--;
        } else if (node != *iter) {
            binary = *iter;

            if (direct > 0) { // If right is heavy, inserted to left.
                node->left = binary;
                node->right = binary->right;
                binary->right = NULL;
                *iter = node;
            } else {
                node->left = binary->left;
                node->right = binary;
                binary->left = NULL;
                *iter = node;
            }

            direct = 0;
            break;
        } else {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            return NULL;
        }
    }

    if (!*iter) {
        *iter = node;
    }

    assert(binary_search_tree_ordered_p(*tree));
    return node;
}

struct binary_search_tree *
binary_search_tree_insert(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(*tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_insert_internal(tree, node);
    }
}

static inline bool
binary_search_tree_doubly_child_p(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    if (node->left && node->right) {
        return true;
    } else {
        return false;
    }
}

static inline struct binary_search_tree **
binary_search_tree_find_ptr_to_max(struct binary_search_tree **tree)
{
    struct binary_search_tree **max;
    struct binary_search_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));

    max = tree;
    node = *max;

    while (NULL != node->right) {
        max = &node->right;
        node = *max;
    }

    return max;
}

static inline struct binary_search_tree **
binary_search_tree_find_ptr_to_min(struct binary_search_tree **tree)
{
    struct binary_search_tree **min;
    struct binary_search_tree *node;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));

    min = tree;
    node = *min;

    while (NULL != node->left) {
        min = &node->left;
        node = *min;
    }

    return min;
}

static inline void
binary_search_tree_swap_child(struct binary_search_tree *a,
    struct binary_search_tree *b)
{
    void *tmp;

    assert(binary_search_tree_structure_legal_p(a));
    assert(binary_search_tree_structure_legal_p(b));

    tmp = a->left;
    a->left = b->left;
    b->left = tmp;

    tmp = a->right;
    a->right = b->right;
    b->right = tmp;
}

static inline void
binary_search_tree_lt_doubly_child_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    assert(!complain_null_pointer_p(pre));
    assert(binary_search_tree_structure_legal_p(node));
    assert(binary_search_tree_structure_legal_p(*pre));
    assert(!binary_search_tree_doubly_child_p(node));
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
binary_search_tree_child_strip_from_max(struct binary_search_tree **node_pre)
{
    struct binary_search_tree *binary;
    struct binary_search_tree *max;
    struct binary_search_tree **max_pre;

    assert(!complain_null_pointer_p(node_pre));
    assert(binary_search_tree_structure_legal_p(*node_pre));
    assert(binary_search_tree_doubly_child_p(*node_pre));

    binary = *node_pre;

    if (!binary->left->right) {
        // short cut here
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
binary_search_tree_child_strip_from_min(struct binary_search_tree **node_pre)
{
    struct binary_search_tree *binary;
    struct binary_search_tree *min;
    struct binary_search_tree **min_pre;

    assert(!complain_null_pointer_p(node_pre));
    assert(binary_search_tree_structure_legal_p(*node_pre));
    assert(binary_search_tree_doubly_child_p(*node_pre));

    binary = *node_pre;

    if (!binary->right->left) {
        // short cut here
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
binary_search_tree_doubly_child_strip(struct binary_search_tree **node_pre)
{
    assert(!complain_null_pointer_p(node_pre));
    assert(binary_search_tree_structure_legal_p(*node_pre));
    assert(binary_search_tree_doubly_child_p(*node_pre));

    if (direct > 0) {
        binary_search_tree_child_strip_from_max(node_pre);
    } else {
        binary_search_tree_child_strip_from_min(node_pre);
    }

    direct = 0;
}

static inline struct binary_search_tree *
binary_search_tree_remove_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    sint64 nice;
    struct binary_search_tree *n;
    struct binary_search_tree *removed;
    struct binary_search_tree **pre;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));
    assert(binary_search_tree_ordered_p(*tree));
    assert(binary_search_tree_ordered_p(*tree));
    assert(binary_search_tree_structure_legal_p(node));

    pre = tree;
    n = *pre;
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
                removed = binary_search_tree_remove_internal(&n->left, node);
            }
            if (NULL == removed && n->right && nice == n->right->nice) {
                removed = binary_search_tree_remove_internal(&n->right, node);
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

    assert(binary_search_tree_ordered_p(*tree));
    return removed;
}

struct binary_search_tree *
binary_search_tree_remove(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(*tree)) {
        return PTR_INVALID;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return PTR_INVALID;
    } else {
        return binary_search_tree_remove_internal(tree, node);
    }
}

static inline void
binary_search_tree_iterate_internal(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert(LEGAL_ORDER_P(order));
    assert(!complain_null_pointer_p(handle));

    if (tree) {
        if (ORDER_PRE == order) {
            handle(tree);
        }

        binary_search_tree_iterate_internal(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(tree);
        }

        binary_search_tree_iterate_internal(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(tree);
        }
    }
}

void
binary_search_tree_iterate(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (complain_null_pointer_p(handle)) {
        return;
    } else if (!binary_search_tree_structure_legal_p(tree)) {
        return;
    } else if (!LEGAL_ORDER_P(order)) {
        pr_log_warn("Invalid value of enum ITER_ORDER.\n");
        return;
    } else {
        binary_search_tree_iterate_internal(tree, handle, order);
    }
}

