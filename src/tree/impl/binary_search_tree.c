struct binary_search_tree *
binary_search_tree_create(void)
{
    return binary_search_tree_create_internal();
}

struct binary_search_tree *
binary_search_tree_node_create(void *val, sint64 nice)
{
    return binary_search_tree_node_create_internal(val, nice);
}

void
binary_search_tree_initial(struct binary_search_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_initial_internal(tree);
    }
}

void
binary_search_tree_node_initial(struct binary_search_tree *node,
    void *val, sint64 nice)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_node_initial_internal(node, val, nice);
    }
}

void
binary_search_tree_destroy(struct binary_search_tree **tree)
{
    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_search_tree_destroy_internal(tree);
    }
}

struct binary_search_tree *
binary_search_tree_node_find(struct binary_search_tree *tree, sint64 nice)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_internal(tree, nice);
    }
}

struct binary_search_tree  *
binary_search_tree_node_find_min(struct binary_search_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_min_internal(tree);
    }
}

struct binary_search_tree *
binary_search_tree_node_find_max(struct binary_search_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_find_max_internal(tree);
    }
}

sint32
binary_search_tree_height(struct binary_search_tree *tree)
{
    if (!tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return -1;
    } else {
        return binary_search_tree_height_internal(tree);
    }
}

bool
binary_search_tree_node_contains_p(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (!tree || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_search_tree_node_contains_p_internal(tree, node);
    }

}

struct binary_search_tree *
binary_search_tree_node_insert(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (!node || !tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_search_tree_node_insert_internal(tree, node);
    }

}

struct binary_search_tree *
binary_search_tree_node_remove(struct binary_search_tree **tree, sint64 nice)
{
    struct binary_search_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        removed = binary_search_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        }

        return removed;
    }
}

void
binary_search_tree_node_remove_and_destroy(struct binary_search_tree **tree,
    sint64 nice)
{
    struct binary_search_tree *removed;

    if (!tree || !*tree) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = binary_search_tree_node_remove_internal(tree, nice);

        if (removed) {
            binary_search_tree_node_destroy(removed);
        }
    }
}

void
binary_search_tree_iterate(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (!tree || !handle) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (!LEGAL_ORDER_P(order)) {
            pr_log_warn("Invalid value of enum ITER_ORDER.\n");
        } else {
            binary_search_tree_iterate_internal(tree, handle, order);
        }
    }
}

