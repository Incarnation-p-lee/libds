static void
performance_test_single_linked_list_struct_field(uint32 count)
{
    uint32 sid;
    struct single_linked_list *tmp;

    sid = 0xfade;
    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_sid_set(tmp, sid);
        single_linked_list_node_val_set(tmp, &sid);
        single_linked_list_node_next_set(tmp, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(single_linked_list_struct_field),
        performance_test_time_stamp_period());
}

