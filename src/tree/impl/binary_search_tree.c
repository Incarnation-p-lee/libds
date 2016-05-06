struct binary_search_tree *
binary_search_tree_create(void)
{
    return binary_search_tree_create_internal();
}

void
binary_search_tree_initial(struct binary_search_tree *tree, sint64 nice)
{
    if (binary_search_tree_structure_legal_p(tree)) {
        binary_search_tree_initial_internal(tree, nice);
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

struct binary_search_tree *
binary_search_tree_find(struct binary_search_tree *tree, sint64 nice)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_find_internal(tree, nice);
    }
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

struct binary_search_tree *
binary_search_tree_find_max(struct binary_search_tree *tree)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else {
        return binary_search_tree_find_max_internal(tree);
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

struct binary_search_tree *
binary_search_tree_insert(struct binary_search_tree *tree,
    struct binary_search_tree *node)
{
    if (!binary_search_tree_structure_legal_p(tree)) {
        return NULL;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return NULL;
    } else {
        return binary_search_tree_insert_internal(tree, node);
    }
}

void *
binary_search_tree_remove(struct binary_search_tree **tree,
    struct binary_search_tree *node)
{
    if (complain_null_pointer_p(tree)) {
        return INVALID_PTR;
    } else if (!binary_search_tree_structure_legal_p(*tree)) {
        return INVALID_PTR;
    } else if (!binary_search_tree_structure_legal_p(node)) {
        return INVALID_PTR;
    } else {
        return binary_search_tree_remove_internal(tree, node);
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

