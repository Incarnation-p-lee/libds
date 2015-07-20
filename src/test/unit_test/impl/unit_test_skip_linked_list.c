static inline struct skip_linked_list *
unit_test_skip_linked_list_sample(uint32 range, uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;
    uint32 i;

    assert(0 != range);
    assert(0 != count);

    list = skip_linked_list_create();
    skip_linked_list_node_initial(list, list, 0);

    i = 1;
    while (i < count) {
        key = (sint32)(rand() % range) - (sint32)range / 2;
        if (!skip_linked_list_contains_p(list, key)) {
            tmp = skip_linked_list_node_create(NULL, key);
            skip_linked_list_node_val_set(tmp, tmp);
            skip_linked_list_node_insert(&list, tmp);
        }
        i++;
    }

    return list;
}

static void
unit_test_skip_linked_list_struct_field(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xa234567u;
    pass = true;
    key = 0xfade;
    list = skip_linked_list_create();

    while (loop--) {
        skip_linked_list_node_key_set(list, key);
        RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);

        skip_linked_list_node_val_set(list, &pass);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);

        skip_linked_list_node_next_set(list, NULL);
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_next(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_struct_field), pass);
    return;
}

static void
unit_test_skip_linked_list_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567;
    pass = true;

    while (loop--) {
        list = skip_linked_list_create();
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);
        skip_linked_list_destroy(&list);
    }

    test_result_print(SYM_2_STR(skip_linked_list_create), pass);
    return;
}

static void
unit_test_skip_linked_list_initial(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf234567;
    pass = true;
    list = NULL;
    skip_linked_list_initial(list);

    list = skip_linked_list_create();
    while (loop--) {
        skip_linked_list_initial(list);
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_initial), pass);
    return;
}

static void
unit_test_skip_linked_list_node_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567;
    pass = true;
    key = -1;

    while (loop--) {
        list = skip_linked_list_node_create(&pass, key);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);
        skip_linked_list_destroy(&list);
    }

    test_result_print(SYM_2_STR(skip_linked_list_node_create), pass);
    return;
}

static void
unit_test_skip_linked_list_node_initial(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf234567;
    pass = true;
    list = NULL;
    skip_linked_list_node_initial(list, &pass, 1);

    list = skip_linked_list_create();
    while (loop--) {
        skip_linked_list_node_initial(list, &pass, (sint32)loop);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(loop, skip_linked_list_node_key(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_initial), pass);
    return;
}

static void
unit_test_skip_linked_list_destroy(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12;
    pass = true;
    list = NULL;

    skip_linked_list_destroy(&list);

    while (loop--) {
        list = unit_test_skip_linked_list_sample(0x6245, 0x3034);
        skip_linked_list_destroy(&list);
        RESULT_CHECK_pointer(NULL, list, &pass);
    }

    test_result_print(SYM_2_STR(skip_linked_list_destroy), pass);
    return;
}
