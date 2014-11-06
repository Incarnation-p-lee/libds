#include "test_doubly_linked_list.c"
#include "test_single_linked_list.c"


void
linked_list_unit_test(void)
{
    doubly_linked_list_unit_test();
    single_linked_list_unit_test();
    return;
}

static void
doubly_linked_list_unit_test(void)
{
    void (*all_tests[])(void) = {
#if 1
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
        &test_dlinker_list_iterate_node,
#else
#endif
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

static void
single_linked_list_unit_test(void)
{
    void (*all_tests[])(void) = {
#if 1
        &test_slinked_list_initial,
        &test_slinked_list_generate,
        &test_slinked_list_append_node,
        &test_slinked_list_next_node,
        &test_slinked_list_previous_node,
        &test_slinked_list_insert_before,
        &test_slinked_list_insert_after,
        &test_slinked_list_destroy,
        &test_slinked_list_length,
        &test_slinked_list_get_node_by_index,
        &test_slinked_list_exchange_node,
        &test_slinked_list_is_contains,
        &test_slinked_list_serialize,
        &test_slinked_list_remove_node,
        &test_slinked_list_lazy_remove_node,
        &test_slinker_list_iterate_node,
#else
#endif
    };
    register void (**iter)(void);

    fprintf(stdout, "\n\n  >> Single Linked List Unit Test <<\n\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n\n");
    return;
}

static int *
int_array_generate(int size)
{
    int *raw;
    register int *iter;

    raw = NULL;
    if (size > 0) {
        raw = (int *)malloc_ds(sizeof(*raw) * size);
        if (raw) {
            iter = raw;
            while (iter < raw + size) {
                *iter++ = rand();
            }
        }
    }

    return raw;
}
