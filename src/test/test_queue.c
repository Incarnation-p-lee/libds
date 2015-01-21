#include "impl/test_array_queue.c"
#include "impl/test_stacked_queue.c"
#include "impl/test_doubly_end_queue.c"

void
queue_unit_test(void)
{
    array_queue_unit_test();
    stacked_queue_unit_test();
    doubly_end_queue_unit_test();
    return;
}

static void
array_queue_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_array_queue_create,
        &test_array_queue_destroy,
        &test_array_queue_space_expand,
        &test_array_queue_capacity,
        &test_array_queue_space_rest,
        &test_array_queue_full_p,
        &test_array_queue_empty_p,
        &test_array_queue_enter,
        &test_array_queue_leave,
        &test_array_queue_cleanup,
        &test_array_queue_iterate,
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

static void
stacked_queue_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_stacked_queue_create,
        &test_stacked_queue_destroy,
        &test_stacked_queue_space_expand,
        &test_stacked_queue_capacity,
        &test_stacked_queue_space_rest,
        &test_stacked_queue_full_p,
        &test_stacked_queue_empty_p,
        &test_stacked_queue_enter,
        &test_stacked_queue_leave,
        &test_stacked_queue_cleanup,
        &test_stacked_queue_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Stacked Queue Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}

static void
doubly_end_queue_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_doubly_end_queue_create,
        &test_doubly_end_queue_destroy,
        &test_doubly_end_queue_length,
        &test_doubly_end_queue_empty_p,
        &test_doubly_end_queue_head_enter,
        &test_doubly_end_queue_tail_enter,
        &test_doubly_end_queue_head_leave,
        &test_doubly_end_queue_tail_leave,
        &test_doubly_end_queue_cleanup,
        &test_doubly_end_queue_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Doubly End Queue Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}
