static inline struct avl_tree *
test_avl_tree_sample(uint64 range, uint32 node_count)
{
    struct binary_search_tree *retval;
    struct binary_search_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = binary_search_tree_create();
    binary_search_tree_node_initial(retval, retval, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_node_create(NULL, 0x0);
        binary_search_tree_node_initial(tmp, tmp, nice);
        binary_search_tree_node_insert(retval, &tmp);
        i++;
    }

    return (struct avl_tree *)retval;
}

static void
test_avl_tree_create(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_create), is_passed);
    return;
}

static void
test_avl_tree_node_create(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_node_create(&is_passed, 0xdead);

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0xdead != tmp->b_node.chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_node_create), is_passed);
    return;
}

static void
test_avl_tree_initial(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_initial(tmp);
    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    } else if (0 != tmp->b_node.height) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_initial), is_passed);
    return;
}

static void
test_avl_tree_node_initial(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_node_initial(tmp, &is_passed, 0xdead);
    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0xdead != tmp->b_node.chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    } else if (0 != tmp->b_node.height) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_node_initial), is_passed);
    return;
}
