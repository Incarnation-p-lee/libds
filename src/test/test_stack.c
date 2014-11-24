#include "test_array_stack.c"
#include "test_linked_stack.c"

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
        &test_array_stack_expand_space,
        &test_array_stack_is_full,
        &test_array_stack_capacity,
        &test_array_stack_rest_space,
        &test_array_stack_push,
        &test_array_stack_pop,
        &test_array_stack_is_empty,
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
        &test_linked_stack_expand_space,
        &test_linked_stack_is_full,
        &test_linked_stack_rest_space,
        &test_linked_stack_capacity,
        &test_linked_stack_push,
        &test_linked_stack_pop,
        &test_linked_stack_is_empty,
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
