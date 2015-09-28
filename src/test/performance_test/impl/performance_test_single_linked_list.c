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

static void
performance_test_single_linked_list_create(uint32 count)
{
    struct single_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_create();
        single_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(single_linked_list_create),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_create(uint32 count)
{
    struct single_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_node_create(&count, count);
        single_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(single_linked_list_node_create),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_initial(uint32 count)
{
    struct single_linked_list *tmp;

    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_initial(tmp, tmp, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_initial(uint32 count)
{
    struct single_linked_list *tmp;

    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_initial(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(single_linked_list_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_append(uint32 count)
{
    struct single_linked_list *tmp;

    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_append(tmp, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_append),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_previous(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;

    head = test_single_linked_list_sample(0x92A, 0x742);
    prev = head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        prev = single_linked_list_node_previous(prev);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_previous),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_insert_before(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    head = test_single_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_create();
        single_linked_list_node_insert_before(head, tmp);
        single_linked_list_node_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_insert_before),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_insert_after(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    head = test_single_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_create();
        single_linked_list_node_insert_after(head, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_insert_after),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_destroy(uint32 count)
{
    struct single_linked_list *head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_single_linked_list_sample(0x22, 0x9);
        single_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(single_linked_list_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_length(uint32 count)
{
    struct single_linked_list *head;

    head = test_single_linked_list_sample(0xe3e, 0x9a7);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_length(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(single_linked_list_length),
        performance_test_time_stamp_period());
}

static void
performance_test_single_linked_list_node_by_index(uint32 count)
{
    struct single_linked_list *head;
    uint32 length;

    head = test_single_linked_list_sample(0xfde, 0x4af);
    length = single_linked_list_length(head);
    length /= 2;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_by_index(head, length);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(single_linked_list_node_by_index),
        performance_test_time_stamp_period());
}
