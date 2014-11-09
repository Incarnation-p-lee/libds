#include "test_array_stack.c"

void
stack_unit_test(void)
{
    array_stack_unit_test();
    return;
}

static void
array_stack_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_dlinked_list_initial,
        &test_dlinked_list_generate,
        &test_dlinked_list_append_node,
        &test_dlinked_list_next_node,
        &test_dlinked_list_previous_node,
        &test_dlinked_list_insert_before,
        &test_dlinked_list_insert_after,
        &test_dlinked_list_destroy,
        &test_dlinked_list_length,
        &test_dlinked_list_get_node_by_index,
        &test_dlinked_list_exchange_node,
        &test_dlinked_list_is_contains,
        &test_dlinked_list_serialize,
        &test_dlinked_list_remove_node,
        &test_dlinked_list_lazy_remove_node,
        &test_dlinker_list_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n\n  >> Doubly Linked List Unit Test <<\n\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n\n");
    return;
}
