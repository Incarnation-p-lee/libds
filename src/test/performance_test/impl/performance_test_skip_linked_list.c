static void
performance_test_skip_linked_list_struct_field(uint32 count)
{
    struct skip_linked_list *list;

    list = skip_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_node_key_set(list, 0xadeu);
        skip_linked_list_node_val_set(list, &count);
        skip_linked_list_node_next_set(list, NULL);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_struct_field),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_create(uint32 count)
{
    struct skip_linked_list *list;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = skip_linked_list_create();
        skip_linked_list_destroy(&list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(skip_linked_list_create),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_initial(uint32 count)
{
    struct skip_linked_list *list;

    list = skip_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_initial(list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_create(uint32 count)
{
    struct skip_linked_list *list;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = skip_linked_list_node_create(&count, 0xfadeu);
        skip_linked_list_destroy(&list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(skip_linked_list_node_create),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_initial(uint32 count)
{
    struct skip_linked_list *list;

    list = skip_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_node_initial(list, list, 0xdeadu);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_destroy(uint32 count)
{
    struct skip_linked_list *list;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = test_skip_linked_list_sample(0x45, 0xf);
        skip_linked_list_destroy(&list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(skip_linked_list_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_length(uint32 count)
{
    struct skip_linked_list *list;

    list = test_skip_linked_list_sample(0xf45, 0x334);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_length(list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_length),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_find_key(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_node_create(list, key);
    skip_linked_list_node_insert(&list, tmp);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_node_find_key(list, key);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_find_key),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_key_contains_p(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_node_create(list, key);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_key_contains_p(list, tmp->key);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&tmp);
    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_key_contains_p),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_insert(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0x1, 0x1);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_node_create(list, key);
        skip_linked_list_node_insert(&list, tmp);
        skip_linked_list_node_remove_and_destroy(&list,
            skip_linked_list_node_key(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_insert),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_by_index(uint32 count)
{
    struct skip_linked_list *list;

    list = test_skip_linked_list_sample(0xe12, 0x245);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_node_by_index(list, count % 2);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_by_index),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_remove(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;

    list = test_skip_linked_list_sample(0x9e12, 0x1845);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_node_remove(&list, skip_linked_list_node_key(list));
        skip_linked_list_node_insert(&list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_remove),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_node_remove_and_destroy(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfedf;
    list = test_skip_linked_list_sample(0x912, 0x345);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_node_create(list, key++);
        skip_linked_list_node_remove_and_destroy(&list, skip_linked_list_node_key(list));
        skip_linked_list_node_insert(&list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_node_remove_and_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_iterate(uint32 count)
{
    struct skip_linked_list *list;

    list = test_skip_linked_list_sample(0x912, 0x345);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_iterate(list, &linked_list_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    performance_test_result_print(SYM_2_STR(skip_linked_list_iterate),
        performance_test_time_stamp_period());
}

static void
performance_test_skip_linked_list_merge(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = test_skip_linked_list_sample(0x912, 0x12);
        tmp = skip_linked_list_node_create(list, 0xdefe);
        list = skip_linked_list_merge(list, tmp);

        skip_linked_list_destroy(&list);
        skip_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(skip_linked_list_merge),
        performance_test_time_stamp_period());
}

