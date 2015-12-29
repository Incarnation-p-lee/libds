static void
unit_test_doubly_linked_list_struct_field(void)
{
    bool pass;
    struct doubly_linked_list *tmp;

    pass = true;
    tmp = doubly_linked_list_create();

    doubly_linked_list_val_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_val(tmp), &pass);

    doubly_linked_list_next_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_next(tmp), &pass);

    doubly_linked_list_previous_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_struct_field, pass);
}

static void
unit_test_doubly_linked_list_create(void)
{
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;

    tmp = doubly_linked_list_create();

    RESULT_CHECK_pointer(tmp, doubly_linked_list_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_create, pass);
}

static void
unit_test_doubly_linked_list_initial(void)
{
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;

    tmp = memory_cache_allocate(sizeof(*tmp));

    doubly_linked_list_initial(tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_initial, pass);
}

static void
unit_test_doubly_linked_list_node_create(void)
{
    bool pass;
    struct doubly_linked_list *tmp;

    pass = true;

    tmp = doubly_linked_list_node_create(&tmp);

    RESULT_CHECK_pointer(&tmp, doubly_linked_list_val(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_node_create, pass);
}

static void
unit_test_doubly_linked_list_insert_before(void)
{
    bool pass;
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *inserted;

    pass = true;
    head = test_doubly_linked_list_sample(0x3f26, 0x1f19);

    doubly_linked_list_insert_before(NULL, &pass);
    prev = doubly_linked_list_previous(head);
    RESULT_CHECK_pointer(prev, doubly_linked_list_previous(head), &pass);

    prev = doubly_linked_list_previous(head);
    doubly_linked_list_insert_before(head, &pass);
    inserted = doubly_linked_list_previous(head);

    RESULT_CHECK_pointer(prev, doubly_linked_list_previous(inserted), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_next(inserted), &pass);
    RESULT_CHECK_pointer(inserted, doubly_linked_list_previous(head), &pass);
    RESULT_CHECK_pointer(inserted, doubly_linked_list_next(prev), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(inserted), &pass);

    doubly_linked_list_destroy(&head);
    UNIT_TEST_RESULT(doubly_linked_list_insert_before, pass);
}

static void
unit_test_doubly_linked_list_insert_after(void)
{
    bool pass;
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *inserted;

    pass = true;
    head = test_doubly_linked_list_sample(0x3f26, 0x1f19);

    doubly_linked_list_insert_after(NULL, &pass);
    next = doubly_linked_list_next(head);
    RESULT_CHECK_pointer(next, doubly_linked_list_next(head), &pass);

    next = doubly_linked_list_next(head);
    doubly_linked_list_insert_after(head, &pass);
    inserted = doubly_linked_list_next(head);

    RESULT_CHECK_pointer(next, doubly_linked_list_next(inserted), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_previous(inserted), &pass);
    RESULT_CHECK_pointer(inserted, doubly_linked_list_next(head), &pass);
    RESULT_CHECK_pointer(inserted, doubly_linked_list_previous(next), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(inserted), &pass);

    doubly_linked_list_destroy(&head);
    UNIT_TEST_RESULT(doubly_linked_list_insert_after, pass);
}

static void
unit_test_doubly_linked_list_destroy(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};

    iter = sizes;
    pass = true;
    head = NULL;
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    iter = sizes;
    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = test_doubly_linked_list_sample(0x316FA, len);

        doubly_linked_list_destroy(&head);
        RESULT_CHECK_pointer(NULL, head, &pass);
    }

    head = doubly_linked_list_create();
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    UNIT_TEST_RESULT(doubly_linked_list_destroy, pass);
}

static void
unit_test_doubly_linked_list_length(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};

    pass = true;
    iter = sizes;

    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = test_doubly_linked_list_sample(0x2e8, len);
        RESULT_CHECK_uint32(len, doubly_linked_list_length(head), &pass);

        doubly_linked_list_destroy(&head);
    }

    head = doubly_linked_list_create();
    RESULT_CHECK_uint32(0x1u, doubly_linked_list_length(head), &pass);
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_uint32(0x0u, doubly_linked_list_length(NULL), &pass);

    UNIT_TEST_RESULT(doubly_linked_list_length, pass);
}

static void
unit_test_doubly_linked_list_node_by_index(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    uint32 len;
    bool pass;

    tmp = doubly_linked_list_node_by_index(NULL, 0);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    pass = true;
    head = test_doubly_linked_list_sample(0x8fa, 0x3a2);
    len = doubly_linked_list_length(head);

    tmp = doubly_linked_list_node_by_index(head, 0);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = doubly_linked_list_node_by_index(head, len);
    RESULT_CHECK_pointer(head, tmp, &pass);
    tmp = doubly_linked_list_node_by_index(head, len + 1);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_next(head), &pass);

    doubly_linked_list_destroy(&head);
    UNIT_TEST_RESULT(doubly_linked_list_node_by_index, pass);
}

static void
unit_test_doubly_linked_list_contains_p(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = test_doubly_linked_list_sample(0x1dd2, 0x28ae);
    tmp = doubly_linked_list_next(head);

    RESULT_CHECK_bool(false, doubly_linked_list_contains_p(NULL, tmp), &pass);

    tmp = doubly_linked_list_next(head);
    RESULT_CHECK_bool(true, doubly_linked_list_contains_p(head, tmp), &pass);
    tmp = doubly_linked_list_create();
    RESULT_CHECK_bool(false, doubly_linked_list_contains_p(head, tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    doubly_linked_list_destroy(&head);
    UNIT_TEST_RESULT(doubly_linked_list_contains_p, pass);
}

static void
unit_test_doubly_linked_list_node_copy(void)
{
    bool pass;
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    pass = true;
    head = doubly_linked_list_node_create(&pass);

    doubly_linked_list_node_copy(NULL);
    tmp = doubly_linked_list_node_copy(head);

    RESULT_CHECK_doubly_linked_list_node(tmp, head, &pass);
    doubly_linked_list_next_set(tmp, tmp);
    doubly_linked_list_previous_set(tmp, tmp);

    doubly_linked_list_destroy(&head);
    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_node_copy, pass);
}

static void
unit_test_doubly_linked_list_remove(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *tmp;
    bool pass;

    doubly_linked_list_remove(NULL);

    pass = true;
    head = test_doubly_linked_list_sample(0x31e2, 0x28ed);
    tmp = head;
    next = head->next;

    RESULT_CHECK_pointer(tmp, doubly_linked_list_remove(&head), &pass);
    RESULT_CHECK_pointer(next, head, &pass);
    doubly_linked_list_destroy(&tmp);
    doubly_linked_list_destroy(&head);

    head = doubly_linked_list_create();
    tmp = head;
    RESULT_CHECK_pointer(tmp, doubly_linked_list_remove(&head), &pass);
    RESULT_CHECK_pointer(NULL, head, &pass);

    doubly_linked_list_destroy(&tmp);
    UNIT_TEST_RESULT(doubly_linked_list_remove, pass);
}

static void
unit_test_doubly_linked_list_remove_and_destroy(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    bool pass;

    doubly_linked_list_remove(NULL);

    pass = true;
    head = test_doubly_linked_list_sample(0x31e2, 0x28ed);
    next = head->next;

    doubly_linked_list_remove_and_destroy(&head);
    RESULT_CHECK_pointer(next, head, &pass);
    doubly_linked_list_destroy(&head);

    head = doubly_linked_list_create();
    doubly_linked_list_remove_and_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    UNIT_TEST_RESULT(doubly_linked_list_remove_and_destroy, pass);
}

static void
unit_test_doubly_linked_list_iterate(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 refer;

    pass = true;
    refer = 0;
    head = test_doubly_linked_list_sample(0x1F2, 0x381);

    doubly_linked_list_iterate(NULL, &linked_list_iterate_handler);

    tmp = head;
    do {
        doubly_linked_list_val_set(tmp, &refer);
        tmp = doubly_linked_list_next(tmp);
    } while (tmp != head);

    tmp = head;
    doubly_linked_list_iterate(head, &linked_list_iterate_handler);
    RESULT_CHECK_uint32(refer, doubly_linked_list_length(head), &pass);

    doubly_linked_list_destroy(&head);
    UNIT_TEST_RESULT(doubly_linked_list_iterate, pass);
}

static void
unit_test_doubly_linked_list_merge(void)
{
    uint32 raw[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x1};
    struct doubly_linked_list *head;
    struct doubly_linked_list *head_n;
    bool pass;

    pass = true;
    head = doubly_linked_list_node_create(raw);
    doubly_linked_list_insert_before(head, raw + 1);
    doubly_linked_list_insert_before(head, raw + 2);

    head_n = doubly_linked_list_node_create(raw + 3);
    doubly_linked_list_insert_before(head_n, raw + 4);
    doubly_linked_list_insert_before(head_n, raw + 5);

    RESULT_CHECK_pointer(NULL, doubly_linked_list_merge(NULL, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_merge(head, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_merge(NULL, head), &pass);

    head = doubly_linked_list_merge(head, head_n);
    RESULT_CHECK_uint32(0x6u, doubly_linked_list_length(head), &pass);

    head = doubly_linked_list_merge(head, head_n);

    doubly_linked_list_destroy(&head);
    doubly_linked_list_destroy(&head_n);
    UNIT_TEST_RESULT(doubly_linked_list_merge, pass);
}

