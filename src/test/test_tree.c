#include "impl/test_binary_search_tree.c"

void
tree_unit_test(void)
{
    binary_search_tree_unit_test();
    return;
}

static void
binary_search_tree_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_binary_search_tree_create,
        &test_binary_search_tree_node_create,
        &test_binary_search_tree_initial,
        &test_binary_search_tree_node_initial,
        &test_binary_search_tree_destroy,
        &test_binary_search_tree_node_find,
        &test_binary_search_tree_node_find_min,
        &test_binary_search_tree_node_find_max,
        &test_binary_search_tree_node_contain_p,
        &test_binary_search_tree_node_insert,
        &test_binary_search_tree_node_remove,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Binary Search Tree Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}
