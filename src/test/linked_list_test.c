void
linked_list_unit_test(void)
{
    doubly_linked_list_unit_test();
    return;
}

static void
doubly_linked_list_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_dlinked_list_initial,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Doubly Linked List Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n\n");
    return;
}

static void
test_dlinked_list_initial(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = dlinked_list_initial();
    if (tmp) {
        if (tmp->index == 0 && tmp->next == tmp && tmp->previous == tmp) {
            is_passed = true;
        }
    }

    test_result_print(SYM_2_STR(dlinked_list_initial), is_passed);
    return;
}
