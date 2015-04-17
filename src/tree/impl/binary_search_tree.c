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
    if (node) {
        node->left = NULL;
        node->right = NULL;
        node->chain.nice = nice;
        doubly_linked_list_initial(node->chain.link);
        doubly_linked_list_node_set_val(node->chain.link, val);
    }

    return;
}

static void inline
binary_search_tree_node_destroy(struct binary_search_tree *node)
{
    doubly_linked_list_destroy(&node->chain.link);
    free_ds(node);
}

void
binary_search_tree_destroy(struct binary_search_tree **root)
{
    if (root && *root) {
        /* post-order */
        binary_search_tree_destroy(&(*root)->left);
        binary_search_tree_destroy(&(*root)->right);
        binary_search_tree_node_destroy(*root);
        *root = NULL;
    }

    return;
}

struct binary_search_tree *
binary_search_tree_node_find(struct binary_search_tree *root, sint64 nice)
{
    if (root) {
        if (nice > root->chain.nice) {
            return binary_search_tree_node_find(root->right, nice);
        } else if (nice < root->chain.nice) {
            return binary_search_tree_node_find(root->left, nice);
        } else {
            return root;
        }
    }

    return NULL;
}

struct binary_search_tree  *
binary_search_tree_node_find_min(struct binary_search_tree *root)
{
    if (root) {
        if (root->left) {
            return binary_search_tree_node_find_min(root->left);
        } else {
            return root;
        }
    }

    return NULL;
}


struct binary_search_tree *
binary_search_tree_node_find_max(struct binary_search_tree *root)
{
    if (root) {
        if (root->right) {
            return binary_search_tree_node_find_max(root->right);
        } else {
            return root;
        }
    }

    return NULL;
}


sint32
binary_search_tree_height(struct binary_search_tree *root)
{
    sint32 height;
    sint32 left;
    sint32 right;

    height = -1;
    if (root) {
        left = binary_search_tree_height(root->left);
        right = binary_search_tree_height(root->right);
        height = MAX_S(left, right) + 1;
    }

    return height;
}


bool
binary_search_tree_node_contain_p(struct binary_search_tree *root,
    struct binary_search_tree *node)
{
    register struct binary_search_tree **iter;

    if (root && node) {
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

    if (node && root) {
        iter = &root;
        while (*iter) {
            if (node->chain.nice > (*iter)->chain.nice) {
                iter = &(*iter)->right;
            } else if (node->chain.nice < (*iter)->chain.nice) {
                iter = &(*iter)->left;
            } else {
                if (*iter != node) {
                    doubly_linked_list_join((*iter)->chain.link, node->chain.link);
                }
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
    *pre = node->left ? node->left : node->right;
}

static inline void
binary_search_tree_node_child_doubly_strip(struct binary_search_tree **pre,
    struct binary_search_tree *node)
{
    struct binary_search_tree *min;
    struct binary_search_tree **min_pre;

    min = node;
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

void
binary_search_tree_node_remove(struct binary_search_tree **root, sint64 nice)
{
    register struct binary_search_tree *iter;
    register struct binary_search_tree **pre;

    if (root) {
        iter = *root;
        pre = root;
        while (iter) {
            if (nice > iter->chain.nice) {
                pre = &iter->right;
            } else if (nice < iter->chain.nice) {
                pre = &iter->left;
            } else if (binary_search_tree_node_child_doubly_p(iter)) {
                binary_search_tree_node_child_doubly_strip(pre, iter);
                binary_search_tree_node_destroy(iter);
                break;
            } else {
                binary_search_tree_node_child_lt_doubly_strip(pre, iter);
                binary_search_tree_node_destroy(iter);
                break;
            }
            iter = *pre;
        }
    }
    return;
}

void
binary_search_tree_iterate(struct binary_search_tree *root,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (root && handle) {
        if (LEGAL_ORDER_P(order)) {
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
