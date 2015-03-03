struct avl_tree *
avl_tree_create(void)
{
    return avl_tree_node_create(NULL, (sint64)0);
}

struct avl_tree *
avl_tree_node_create(void *val, sint64 nice)
{
    return avl_tree_ptr_bst2avl(binary_search_tree_node_create(val, nice));
}

void
avl_tree_initial(struct avl_tree *root)
{
    avl_tree_node_initial(root, NULL, (sint64)0);
    return;
}

void
avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice)
{
    if (node) {
        node->b_node.height = 1u;
        binary_search_tree_node_initial(avl_tree_ptr_avl2bst(node), val, nice);
    }

    return;
}

static inline struct avl_tree *
avl_tree_ptr_bst2avl(struct binary_search_tree *node)
{
    return (struct avl_tree *)node;
}

static inline struct binary_search_tree *
avl_tree_ptr_avl2bst(struct avl_tree *node)
{
    return (struct binary_search_tree *)node;
}

void
avl_tree_destroy(struct avl_tree **root)
{
    binary_search_tree_destroy((struct binary_search_tree **)root);
    return;
}

struct avl_tree *
avl_tree_node_find(struct avl_tree *root, sint64 nice)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find(avl_tree_ptr_avl2bst(root), nice));
}

struct avl_tree *
avl_tree_node_find_min(struct avl_tree *root)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find_min(avl_tree_ptr_avl2bst(root)));
}

struct avl_tree *
avl_tree_node_find_max(struct avl_tree *root)
{
    return avl_tree_ptr_bst2avl(
        binary_search_tree_node_find_max(avl_tree_ptr_avl2bst(root)));
}
