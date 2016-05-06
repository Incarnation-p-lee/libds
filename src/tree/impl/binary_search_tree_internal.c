static inline struct binary_search_tree *
binary_search_tree_create_internal(void)
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

static inline bool
binary_search_tree_structure_legal_p(struct binary_search_tree *tree)
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

static inline struct binary_search_tree *
binary_search_tree_find_min_internal(struct binary_search_tree *tree)
{
    assert(binary_search_tree_structure_legal_p(tree));

    while (tree->left) {
        tree = tree->left;
    }

    return tree;
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

        return MAX_S(left, right) + 1;
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
    struct binary_search_tree **iter;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(binary_search_tree_structure_legal_p(node));

    retval = false;
    iter = &tree;
    nice = node->nice;

    while (*iter) {
        if (node == *iter) {
            return true;
        } else if (nice > (*iter)->nice) {
            iter = &(*iter)->right;
        } else if (nice < (*iter)->nice) {
            iter = &(*iter)->left;
        } else {
            left = (*iter)->left;
            right = (*iter)->right;

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

static inline bool
binary_search_tree_node_balanced_p(struct binary_search_tree *node)
{
    sint32 left;
    sint32 right;

    assert(binary_search_tree_structure_legal_p(node));

    left = binary_search_tree_height_internal(node->left);
    right = binary_search_tree_height_internal(node->right);

    if (abs_sint32(left - right) > 1) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_search_tree_balanced_p(struct binary_search_tree *tree)
{
    bool retval;

    if (NULL == tree) {
        return true;
    } else if (!binary_search_tree_node_balanced_p(tree)) {
        return false;
    } else if (!binary_search_tree_balanced_p(tree->left)) {
        return false;
    } else if (!binary_search_tree_balanced_p(tree->right)) {
        return false;
    } else {
        return true;
    }
}

// static inline struct binary_search_tree *
// binary_search_tree_balanced_insert(struct binary_search_tree *tree,
//     struct binary_search_tree *node)
// {
//     sint64 nice;
//     struct binary_search_tree **node;
// 
//     assert(binary_search_tree_structure_legal_p(tree));
//     assert(binary_search_tree_structure_legal_p(node));
//     assert(binary_search_tree_balanced_p(tree));
// 
//     node = &tree;
//     nice = node->data->nice;
// 
//     if (nice > (*node)->data->nice) {
//     } else if (nice < (*node)->data->nice) {
//     } else {
//     }
// }

static inline struct binary_search_tree *
binary_search_tree_insert_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    sint32 left_h;
    sint32 right_h;
    sint64 nice;
    struct binary_search_tree **iter;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(binary_search_tree_structure_legal_p(node));

    iter = &tree;
    nice = node->nice;

    while (*iter) {
        if (nice > (*iter)->nice) {
            iter = &(*iter)->right;
        } else if (nice < (*iter)->nice) {
            iter = &(*iter)->left;
        } else if (node != *iter) {
            left_h = binary_search_tree_height_internal((*iter)->left);
            right_h = binary_search_tree_height_internal((*iter)->right);

            if (left_h < right_h) {
                node->left = (*iter)->left;
                node->right = NULL;
                (*iter)->left = node;
            } else {
                node->right = (*iter)->right;
                node->left = NULL;
                (*iter)->right = node;
            }
            break;
        } else {
            pr_log_warn("Insert node exist, nothing will be done.\n");
            break;
        }
    }

    if (!*iter) {
        *iter = node;
    }

    assert(binary_search_tree_ordered_p(tree));
    return node;
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

static inline bool
binary_search_tree_leaf_p(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    if (NULL == node->left && NULL == node->right) {
        return true;
    } else {
        return false;
    }
}

/*
 * find the pointer points the left/right pointer
 * of parent node which contains max node.
 */
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

/*
 * find the pointer points the left/right pointer
 * of parent node which contains min node.
 */
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
binary_search_tree_child_lt_doubly_strip(struct binary_search_tree **pre,
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

    binary_search_tree_child_clean(node);
}

static inline void
binary_search_tree_node_swap(struct binary_search_tree *a,
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

/*
 * strip from the min node of right child tree.
 */
static inline void
binary_search_tree_child_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    sint32 left_h;
    sint32 right_h;
    struct binary_search_tree *aim;
    struct binary_search_tree **aim_ptr;

    assert(!complain_null_pointer_p(pre));
    assert(binary_search_tree_structure_legal_p(*pre));
    assert(binary_search_tree_structure_legal_p(node));
    assert(binary_search_tree_doubly_child_p(node));
    assert(binary_search_tree_contains_p_internal(*pre, node));

    left_h = binary_search_tree_height_internal(node->left);
    right_h = binary_search_tree_height_internal(node->right);

    if (left_h > right_h) {
        aim_ptr = binary_search_tree_find_ptr_to_max(&node->left);
    } else {
        aim_ptr = binary_search_tree_find_ptr_to_min(&node->right);
    }
    aim = *aim_ptr;

    binary_search_tree_node_swap(node, aim);
    *pre = aim;
    *aim_ptr = node;

    binary_search_tree_child_lt_doubly_strip(aim_ptr, node);
}

static inline void
binary_search_tree_child_clean(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    node->left = NULL;
    node->right = NULL;
}

static inline struct binary_search_tree *
binary_search_tree_remove_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    sint64 nice;
    struct binary_search_tree *n;
    struct binary_search_tree *val;
    struct binary_search_tree **pre;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));
    assert(binary_search_tree_structure_legal_p(node));

    pre = tree;
    n = *pre;
    nice = node->nice;
    val = INVALID_PTR;

    while (n) {
        if (nice > n->nice) {
            pre = &n->right;
        } else if (nice < n->nice) {
            pre = &n->left;
        } else if (node != n) {
            if (n->left && nice == n->left->nice) {
                val = binary_search_tree_remove_internal(&n->left, node);
            }
            if (INVALID_PTR == val && n->right && nice == n->right->nice) {
                val = binary_search_tree_remove_internal(&n->right, node);
            }
            break;
        } else if (binary_search_tree_doubly_child_p(n)) {
            binary_search_tree_child_doubly_strip(pre, n);
            return n;
        } else {
            binary_search_tree_child_lt_doubly_strip(pre, n);
            return n;
        }
        n = *pre;
    }

    if (INVALID_PTR == val) {
        pr_log_warn("Failed to find the node in given tree.\n");
    }

    assert(binary_search_tree_ordered_p(*tree));
    return val;
}

static inline void
binary_search_tree_iterate_internal(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    assert(LEGAL_ORDER_P(order));

    if (tree && handle) {
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

// static inline struct binary_search_tree *
// binary_search_tree_left_find_max(struct binary_search_tree *tree)
// {
//     struct binary_search_tree *left;
// 
//     assert(binary_search_tree_structure_legal_p(tree));
//     assert(!complain_null_pointer_p(tree->left));
// 
//     left = tree->left;
// 
//     while (NULL != left->right) {
//         left = left->right;
//     }
// 
//     return left;
// }
// 
// static inline struct binary_search_tree *
// binary_search_tree_right_find_min(struct binary_search_tree *tree)
// {
//     struct binary_search_tree *right;
// 
//     assert(NULL != tree);
//     assert(NULL != tree->right);
// 
//     right = tree->right;
// 
//     while (NULL != right->left) {
//         right = right->left;
//     }
// 
//     return right;
// }

