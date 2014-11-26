#include "impl/test_array_queue.c"

void
queue_unit_test(void)
{
    array_queue_unit_test();
    return;
}

static void
array_queue_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_array_queue_create,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Array Queue Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}
