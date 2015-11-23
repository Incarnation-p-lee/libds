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
    if (!complain_null_pointer_p(tree)) {
        binary_search_tree_initial_internal(tree);
    }
}

void
binary_search_tree_node_initial(struct binary_search_tree *node,
    void *val, sint64 nice)
{
    if (!complain_null_pointer_p(node)) {
        binary_search_tree_node_initial_internal(node, val, nice);
    }
}

void
binary_search_tree_destroy(struct binary_search_tree **tree)
{
    if (!complain_null_pointer_p(tree) && !complain_null_pointer_p(*tree)) {
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
    if (complain_null_pointer_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_node_find_min_internal(tree);
    }
}

struct binary_search_tree *
binary_search_tree_node_find_max(struct binary_search_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_node_find_max_internal(tree);
    }
}

sint32
binary_search_tree_height(struct binary_search_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return -1;
    } else {
        return binary_search_tree_height_internal(tree);
    }
}

bool
binary_search_tree_node_contains_p(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (complain_null_pointer_p(tree) || complain_null_pointer_p(node)) {
        return false;
    } else {
        return binary_search_tree_node_contains_p_internal(tree, node);
    }
}

struct binary_search_tree *
binary_search_tree_node_insert(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (complain_null_pointer_p(tree) || complain_null_pointer_p(node)) {
        return NULL;
    } else {
        return binary_search_tree_node_insert_internal(tree, node);
    }

}

struct binary_search_tree *
binary_search_tree_node_remove(struct binary_search_tree **tree, sint64 nice)
{
    struct binary_search_tree *removed;

    if (complain_null_pointer_p(tree) || complain_null_pointer_p(*tree)) {
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

    if (!complain_null_pointer_p(tree) && !complain_null_pointer_p(*tree)) {
        removed = binary_search_tree_node_remove_internal(tree, nice);

        if (NULL == removed) {
            pr_log_warn("Failed to find the node in given tree.\n");
        } else {
            binary_search_tree_node_destroy(removed);
        }
    }
}

void
binary_search_tree_iterate(struct binary_search_tree *tree,
    void (*handle)(void *), enum ITER_ORDER order)
{
    if (!complain_null_pointer_p(tree) && !complain_null_pointer_p(handle)) {
        if (!LEGAL_ORDER_P(order)) {
            pr_log_warn("Invalid value of enum ITER_ORDER.\n");
        } else {
            binary_search_tree_iterate_internal(tree, handle, order);
        }
    }
}

