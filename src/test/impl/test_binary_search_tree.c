static void
test_binary_search_tree_create(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_create();

    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0 != tmp->chain.nice
        || NULL != doubly_linked_list_node_get_val(&tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_destory(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_create), is_passed);
    return;
}
