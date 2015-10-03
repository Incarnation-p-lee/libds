static void
performance_test_doubly_linked_list_struct_field(uint32 count)
{
    uint32 sid;
    struct doubly_linked_list *tmp;

    sid = 0xfade;
    tmp = doubly_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_node_sid_set(tmp, sid);
        doubly_linked_list_node_val_set(tmp, &sid);
        doubly_linked_list_node_next_set(tmp, tmp);
        doubly_linked_list_node_previous_set(tmp, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_struct_field),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_create(uint32 count)
{
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_create();
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_linked_list_create),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_create(uint32 count)
{
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_node_create(&count, count);
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_create),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_initial(uint32 count)
{
    struct doubly_linked_list *tmp;

    tmp = doubly_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_node_initial(tmp, tmp, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_initial(uint32 count)
{
    struct doubly_linked_list *tmp;

    tmp = doubly_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_initial(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_append(uint32 count)
{
    struct doubly_linked_list *tmp;

    tmp = doubly_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_node_append(tmp, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&tmp);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_append),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_insert_before(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = test_doubly_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_insert_before(head, tmp);
        doubly_linked_list_node_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_insert_before),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_insert_after(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = test_doubly_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_insert_after(head, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_insert_after),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_destroy(uint32 count)
{
    struct doubly_linked_list *head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_doubly_linked_list_sample(0x22, 0x9);
        doubly_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_linked_list_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_length(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xe3e, 0x9a7);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_length(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_length),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_by_index(uint32 count)
{
    struct doubly_linked_list *head;
    uint32 length;

    head = test_doubly_linked_list_sample(0xfde, 0x4af);
    length = doubly_linked_list_length(head);
    length /= 2;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_node_by_index(head, length);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_by_index),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_contains_p(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = test_doubly_linked_list_sample(0xfde, 0x4af);
    tmp = head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_contains_p(head, tmp);
        tmp = doubly_linked_list_node_next(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_contains_p),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_serialize(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xf92, 0x434);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_serialize(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_serialize),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_copy(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = doubly_linked_list_node_create(&count, 0u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_node_copy(head);
        doubly_linked_list_node_next_set(tmp, tmp);
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_copy),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_remove(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *removed;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = doubly_linked_list_node_remove(&head);
        doubly_linked_list_node_insert_before(head, removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_remove),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_node_remove_and_destroy(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_remove_and_destroy(&head);
        doubly_linked_list_node_insert_after(head, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_node_remove_and_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_iterate(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_iterate(head, &linked_list_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    performance_test_result_print(SYM_2_STR(doubly_linked_list_iterate),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_linked_list_merge(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_doubly_linked_list_sample(0xe0d, 0xd);
        tmp = test_doubly_linked_list_sample(0xfe0d, 0xf);
        doubly_linked_list_merge(head, tmp);
        doubly_linked_list_destroy(&tmp);
        doubly_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_linked_list_merge),
        performance_test_time_stamp_period());
}
