#include "impl/test_array_stack.c"
#include "impl/test_linked_stack.c"

void
stack_unit_test(void)
{
    array_stack_unit_test();
    linked_stack_unit_test();
    return;
}

static void
array_stack_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_array_stack_create,
        &test_array_stack_destroy,
        &test_array_stack_space_expand,
        &test_array_stack_full_p,
        &test_array_stack_capacity,
        &test_array_stack_space_rest,
        &test_array_stack_push,
        &test_array_stack_pop,
        &test_array_stack_empty_p,
        &test_array_stack_cleanup,
        &test_array_stack_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Array Stack Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}

static void
linked_stack_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_linked_stack_create,
        &test_linked_stack_destroy,
        &test_linked_stack_space_expand,
        &test_linked_stack_full_p,
        &test_linked_stack_space_rest,
        &test_linked_stack_capacity,
        &test_linked_stack_push,
        &test_linked_stack_pop,
        &test_linked_stack_empty_p,
        &test_linked_stack_cleanup,
        &test_linked_stack_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Linked Stack Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}
