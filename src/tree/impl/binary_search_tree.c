struct binary_search_tree *
binary_search_tree_create(void)
{
    return binary_search_tree_node_create(NULL, (sint64)0);
}

struct binary_search_tree *
binary_search_tree_node_create(void *val, sint64 nice)
{
    struct binary_search_tree *node;

    node = malloc_ds(sizeof(*node));
    if (!node) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        node->chain.link = malloc_ds(sizeof(*node->chain.link));
        if (!node->chain.link) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            binary_search_tree_node_initial(node, val, nice);
        }
    }

    return node;
}

void
binary_search_tree_initial(struct binary_search_tree *root)
{
    binary_search_tree_node_initial(root, NULL, (sint64)0);
    return;
}

void
binary_search_tree_node_initial(struct binary_search_tree *node,
    void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_child_left_set(node, NULL);
        binary_search_tree_child_right_set(node, NULL);
        binary_search_tree_node_nice_set(node, nice);
        doubly_linked_list_initial(node->chain.link);
        doubly_linked_list_node_val_set(node->chain.link, val);
    }

    return;
}

static void inline
binary_search_tree_node_destroy(struct binary_search_tree *node)
{
    assert(NULL != node);

    doubly_linked_list_destroy(&node->chain.link);
    free_ds(node);
}

static inline void
binary_search_tree_destroy_internal(struct binary_search_tree **root)
{
    if (*root && root) {
        /* post-order */
        binary_search_tree_destroy_internal(&(*root)->left);
        binary_search_tree_destroy_internal(&(*root)->right);
        binary_search_tree_node_destroy(*root);
        *root = NULL;
    }
}

void
binary_search_tree_destroy(struct binary_search_tree **root)
{
    if (!root || !*root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_destroy_internal(root);
    }

    return;
}

static inline struct binary_search_tree *
binary_search_tree_node_find_internal(struct binary_search_tree *root,
    sint64 nice)
{
    if (!root) {
        return NULL;
    } else {
        if (nice > binary_search_tree_node_nice(root)) {
            return binary_search_tree_node_find_internal(root->right, nice);
        } else if (nice < binary_search_tree_node_nice(root)) {
            return binary_search_tree_node_find_internal(root->left, nice);
        } else {
            return root;
        }
    }
}

struct binary_search_tree *
binary_search_tree_node_find(struct binary_search_tree *root, sint64 nice)
{
    if (!root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_internal(root, nice);
    }
}

static inline struct binary_search_tree *
binary_search_tree_node_find_min_internal(struct binary_search_tree *root)
{
    assert(NULL != root);

    if (!root->left) {
        return root;
    } else {
        return binary_search_tree_node_find_min_internal(root->left);
    }
}

struct binary_search_tree  *
binary_search_tree_node_find_min(struct binary_search_tree *root)
{
    if (!root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_min_internal(root);
    }
}

static inline struct binary_search_tree *
binary_search_tree_node_find_max_internal(struct binary_search_tree *root)
{
    assert(NULL != root);

    if (!root->right) {
        return root;
    } else {
        return binary_search_tree_node_find_max_internal(root->right);
    }
}

struct binary_search_tree *
binary_search_tree_node_find_max(struct binary_search_tree *root)
{
    if (!root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_max_internal(root);
    }
}

static inline sint32
binary_search_tree_height_internal(struct binary_search_tree *root)
{
    sint32 height;
    sint32 left;
    sint32 right;

    height = -1;
    if (root) {
        left = binary_search_tree_height_internal(root->left);
        right = binary_search_tree_height_internal(root->right);
        height = MAX_S(left, right) + 1;
    }

    return height;
}

sint32
binary_search_tree_height(struct binary_search_tree *root)
{
    if (!root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return -1;
    } else {
        return binary_search_tree_height_internal(root);
    }
}

bool
binary_search_tree_node_contains_p(struct binary_search_tree *root,
    struct binary_search_tree *node)
{
    register struct binary_search_tree **iter;

    if (!root || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = &root;
        while (*iter) {
            if (node == *iter) {
                return true;
            } else {
                if (node->chain.nice > (*iter)->chain.nice) {
                    iter = &(*iter)->right;
                } else if (node->chain.nice < (*iter)->chain.nice) {
                    iter = &(*iter)->left;
                } else {
                    return false;
                }
            }
        }
    }

    return false;
}

/*
 * insert one node into given root binary search tree
 * @root: the pointer of given tree
 * @node: the pointer of the node
 *
 * RETURN the pointer of inserted node of the binary search tree
 *        If root is NULL or node is NULL, RETURN NULL.
 */
struct binary_search_tree *
binary_search_tree_node_insert(struct binary_search_tree *root,
    struct binary_search_tree *node)
{
    register struct binary_search_tree **iter;

    if (!node || !root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = &root;
        while (*iter) {
            if (node->chain.nice > (*iter)->chain.nice) {
                iter = &(*iter)->right;
            } else if (node->chain.nice < (*iter)->chain.nice) {
                iter = &(*iter)->left;
            } else if (*iter != node) {
                doubly_linked_list_merge((*iter)->chain.link, node->chain.link);
                return *iter;
            } else {
                pr_log_info("Insert node exist, nothing will be done.\n");
                return *iter;
            }
        }

        return *iter = node;
    }

    return NULL;
}

static inline void
binary_search_tree_node_child_lt_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    assert(NULL != node);
    assert(NULL != pre);

    *pre = node->left ? node->left : node->right;
}

static inline void
binary_search_tree_node_child_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    struct binary_search_tree *min;
    struct binary_search_tree **min_pre;

    assert(NULL != node);
    assert(NULL != pre);

    min = binary_search_tree_child_right(node);
    while (min->left) {
        min_pre = &min->left;
        min = *min_pre;
    }

    binary_search_tree_node_child_lt_doubly_strip(min_pre, min);
    *pre = min;
    min->left = node->left;
    min->right = node->right;
    node->left = node->right = NULL;
    return;
}

static inline bool
binary_search_tree_node_child_doubly_p(struct binary_search_tree *node)
{
    assert(NULL != node);

    if (NULL != node->left && NULL != node->right) {
        return true;
    } else {
        return false;
    }
}

struct binary_search_tree *
binary_search_tree_node_remove(struct binary_search_tree **root, sint64 nice)
{
    register struct binary_search_tree *iter;
    register struct binary_search_tree **pre;

    if (!root || !*root) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = *root;
        pre = root;
        while (iter) {
            if (nice > iter->chain.nice) {
                pre = &iter->right;
            } else if (nice < iter->chain.nice) {
                pre = &iter->left;
            } else if (binary_search_tree_node_child_doubly_p(iter)) {
                binary_search_tree_node_child_doubly_strip(pre, iter);
                break;
            } else {
                binary_search_tree_node_child_lt_doubly_strip(pre, iter);
                break;
            }
            iter = *pre;
        }
        if (!iter) {
            pr_log_warn("Failed to find the node in given tree.\n");
        } else {
            iter->left = iter->right = NULL;
        }

        return iter;
    }

    return NULL;
}

void
binary_search_tree_iterate(struct binary_search_tree *root,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (!root || !handle) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (!LEGAL_ORDER_P(order)) {
            pr_log_warn("Invalid value of enum ITER_ORDER.\n");
        } else {
            binary_search_tree_iterate_internal(root, handle, order);
        }
    }
}

static inline void
binary_search_tree_iterate_internal(struct binary_search_tree *root,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (root) {
        if (ORDER_PRE == order) {
            doubly_linked_list_iterate(root->chain.link, handle);
        }

        binary_search_tree_iterate_internal(root->left, handle, order);

        if (ORDER_IN == order) {
            doubly_linked_list_iterate(root->chain.link, handle);
        }

        binary_search_tree_iterate_internal(root->right, handle, order);

        if (ORDER_POST == order) {
            doubly_linked_list_iterate(root->chain.link, handle);
        }
    }
}
