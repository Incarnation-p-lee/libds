#include "impl/test_doubly_linked_list.c"
#include "impl/test_single_linked_list.c"

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
        &test_dlinked_list_initial,
        &test_dlinked_list_node_initial,
        &test_dlinked_list_create,
        &test_dlinked_list_node_create,
        &test_dlinked_list_node_set_val,
        &test_dlinked_list_node_get_val,
        &test_dlinked_list_generate,
        &test_dlinked_list_node_append,
        &test_dlinked_list_node_next,
        &test_dlinked_list_node_previous,
        &test_dlinked_list_node_insert_before,
        &test_dlinked_list_node_insert_after,
        &test_dlinked_list_destroy,
        &test_dlinked_list_length,
        &test_dlinked_list_node_get_by_index,
        &test_dlinked_list_node_exchange,
        &test_dlinked_list_contains_p,
        &test_dlinked_list_serialize,
        &test_dlinked_list_node_remove,
        &test_dlinked_list_node_lazy_remove,
        &test_dlinker_list_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Doubly Linked List Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}

static void
single_linked_list_unit_test(void)
{
    void (*all_tests[])(void) = {
        &test_slinked_list_initial,
        &test_slinked_list_node_initial,
        &test_slinked_list_create,
        &test_slinked_list_node_create,
        &test_slinked_list_node_set_val,
        &test_slinked_list_node_get_val,
        &test_slinked_list_generate,
        &test_slinked_list_node_append,
        &test_slinked_list_node_next,
        &test_slinked_list_node_previous,
        &test_slinked_list_node_insert_before,
        &test_slinked_list_node_insert_after,
        &test_slinked_list_destroy,
        &test_slinked_list_length,
        &test_slinked_list_node_get_by_index,
        &test_slinked_list_node_exchange,
        &test_slinked_list_contains_p,
        &test_slinked_list_serialize,
        &test_slinked_list_node_remove,
        &test_slinked_list_node_lazy_remove,
        &test_slinker_list_iterate,
    };
    register void (**iter)(void);

    fprintf(stdout, "\n  >> Single Linked List Unit Test <<\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n");
    return;
}

static sint32 *
int_array_generate(sint32 size)
{
    sint32 *raw;
    register sint32 *iter;

    raw = NULL;
    if (size > 0) {
        raw = (sint32 *)malloc_ds(sizeof(*raw) * size);
        if (raw) {
            iter = raw;
            while (iter < raw + size) {
                *iter++ = rand();
            }
        }
    }

    return raw;
}
