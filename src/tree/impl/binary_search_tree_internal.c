static inline struct binary_search_tree *
binary_search_tree_create_internal(void)
{
    struct binary_search_tree *node;

    node = memory_cache_allocate(sizeof(*node));
    node->data = memory_cache_allocate(sizeof(*node->data));

    return node;
}

static inline void
binary_search_tree_initial_internal(struct binary_search_tree *tree,
    sint64 nice, void *val)
{
    assert(!complain_null_pointer_p(node));

    node->left = NULL;
    node->right = NULL;
    node->data->nice = nice;
    node->data->val = val;
}

static inline void
binary_search_tree_structure_legal_p(struct binary_search_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return false;
    } else if (complain_null_pointer_p(tree->data)) {
        return false;
    } else if (tree->left == tree->right && NULL != tree->left) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_search_tree_ordered_p(struct binary_search_tree *tree)
{
    struct binary_search_tree *left;
    struct binary_search_tree *right;

    if (!tree) {
        return true;
    } else {
        left = binary_search_tree_left(tree);
        right = binary_search_tree_right(tree);

        if (left && tree->data->nice < left->data->nice) {
            return false;
        } else if (right && tree->data->nice > right->data->nice) {
            return false;
        } else {
            if (!binary_search_tree_ordered_p(left)) {
                return false;
            } else {
                return binary_search_tree_ordered_p(right);
            }
        }
    }
}

static inline void
binary_search_tree_node_destroy(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    memory_cache_free(node->data);
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
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        while (!tree->left) {
            tree = tree->left;
        }

        return tree;
    }
}

static inline struct binary_search_tree *
binary_search_tree_find_max_internal(struct binary_search_tree *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        while (!tree->right) {
            tree = tree->right;
        }

        return tree;
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

        return MAX_S(left, right) + 1;
    }
}

static inline bool
binary_search_tree_contains_p_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    sint64 nice;
    struct binary_search_tree *left;
    struct binary_search_tree *right;
    struct binary_search_tree **iter;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(binary_search_tree_structure_legal_p(node));

    iter = &tree;
    nice = node->data->nice;

    while (*iter) {
        if (node == *iter) {
            return true;
        } else {
            if (nice > (*iter)->data->nice) {
                iter = &(*iter)->right;
            } else if (nice < (*iter)->data->nice) {
                iter = &(*iter)->left;
            } else {
                left = (*iter)->left;
                right = (*iter)->right;

                // Handle repeated nice
                if (left && nice == left->data->nice) {
                    return binary_search_tree_contains_p_internal(left, node);
                } else if (right && nice == right->data->nice) {
                    return binary_search_tree_contains_p_internal(right, node);
                } else {
                    return false;
                }
            }
        }
    }

    return false;
}

static inline struct binary_search_tree *
binary_search_tree_insert_internal(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    sint64 nice;
    sint64 left_h;
    sint64 right_h;
    struct binary_search_tree **iter;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(binary_search_tree_structure_legal_p(node));

    iter = &tree;
    nice = node->data->nice;
    while (*iter) {
        if (nice > (*iter)->data->nice) {
            iter = &(*iter)->right;
        } else if (nice < (*iter)->data->nice) {
            iter = &(*iter)->left;
        } else if (*iter != node) {
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

            goto DONE:
        } else {
            pr_log_info("Insert node exist, nothing will be done.\n");
            goto DONE:
        }
    }
    *iter = node;

DONE:
    assert(binary_search_tree_ordered_p(tree));
    return node;
}

static inline void
binary_search_tree_data_copy(struct nv_data *tgt, struct nv_data *node)
{
    assert(tgt != node);
    assert(!complain_null_pointer_p(tgt));
    assert(!complain_null_pointer_p(node));

    tgt->nice = node->nice;
    tgt->val = node->val;
}

static inline void
binary_search_tree_data_swap(struct nv_data *m, struct nv_data *n)
{
    struct nv_data tmp;

    assert(m != n);
    assert(!complain_null_pointer_p(m));
    assert(!complain_null_pointer_p(n));

    binary_search_tree_data_copy(&tmp, n);
    binary_search_tree_data_copy(n, m);
    binary_search_tree_data_copy(m, &tmp);
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

static inline void *
binary_search_tree_child_lt_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    void *val;

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

    val = binary_search_tree_val(node);
    binary_search_tree_child_clean(node);
    memory_cache_free(node->data);
    memory_cache_free(node);

    return val;
}

/*
 * strip from the min node of right child tree.
 */
static inline struct binary_search_tree *
binary_search_tree_child_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    struct binary_search_tree *min;
    struct binary_search_tree **min_ptr;

    assert(!complain_null_pointer_p(pre));
    assert(binary_search_tree_structure_legal_p(*pre));
    assert(binary_search_tree_structure_legal_p(node));
    assert(binary_search_tree_doubly_child_p(node));
    assert(binary_search_tree_contains_p_internal(*pre, node));

    // Take the minimal node of right child
    min_ptr = binary_search_tree_find_ptr_to_min(&node->right);
    min = *min_ptr;

    // swap content of node instead of pointers change.
    binary_search_tree_data_swap(node->data, min->data);
    return binary_search_tree_child_lt_doubly_strip(min_ptr, min);
}

static inline void
binary_search_tree_child_clean(struct binary_search_tree *node)
{
    assert(binary_search_tree_structure_legal_p(node));

    node->left = NULL;
    node->right = NULL;
}

static inline void *
binary_search_tree_remove_internal(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    void *val;
    sint64 nice;
    struct binary_search_tree *iter;
    struct binary_search_tree **pre;

    assert(!complain_null_pointer_p(tree));
    assert(binary_search_tree_structure_legal_p(*tree));

    val = INVALID_PTR;
    pre = tree;
    iter = *tree;
    nice = node->data->nice;

    while (iter) {
        if (nice > iter->data->nice) {
            pre = &iter->right;
        } else if (nice < iter->data->nice) {
            pre = &iter->left;
        } else if (node != iter) {
            if (nice == binary_search_tree_nice(iter->left)) {
                val = binary_search_tree_remove_internal(&iter->left, node);
            } else if (nice == binary_search_tree_nice(iter->right)) {
                val = binary_search_tree_remove_internal(&iter->right, node);
            } else {
                break;
            }
        } else if (binary_search_tree_doubly_child_p(iter)) {
            val = binary_search_tree_child_doubly_strip(pre, iter);
        } else {
            val = binary_search_tree_child_lt_doubly_strip(pre, iter);
        }
        iter = *pre;
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
            handle(binary_search_tree_val(tree));
        }

        binary_search_tree_iterate_internal(tree->left, handle, order);

        if (ORDER_IN == order) {
            handle(binary_search_tree_val(tree));
        }

        binary_search_tree_iterate_internal(tree->right, handle, order);

        if (ORDER_POST == order) {
            handle(binary_search_tree_val(tree));
        }
    }
}

static inline struct binary_search_tree *
binary_search_tree_left_find_max(struct binary_search_tree *tree)
{
    struct binary_search_tree *left;

    assert(binary_search_tree_structure_legal_p(tree));
    assert(!complain_null_pointer_p(tree->left));

    left = tree->left;

    while (NULL != left->right) {
        left = left->right;
    }

    return left;
}

static inline struct binary_search_tree *
binary_search_tree_right_find_min(struct binary_search_tree *tree)
{
    struct binary_search_tree *right;

    assert(NULL != tree);
    assert(NULL != tree->right);

    right = tree->right;

    while (NULL != right->left) {
        right = right->left;
    }

    return right;
}

