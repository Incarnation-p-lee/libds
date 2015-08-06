static inline struct doubly_linked_list *
unit_test_doubly_linked_list_sample(uint32 range, uint32 node_count)
{
    struct doubly_linked_list *retval;
    struct doubly_linked_list *tmp;
    uint32 sid;
    uint32 i;

    retval = doubly_linked_list_create();
    doubly_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_initial(tmp, tmp, sid);
        doubly_linked_list_node_insert_before(retval, tmp);
        i++;
    }

    return retval;
}

static void
unit_test_doubly_linked_list_struct_field(void)
{
    uint32 sid;
    bool pass;
    struct doubly_linked_list *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xe23456fu;
    sid = 0xfade;
    pass = true;
    tmp = doubly_linked_list_create();
    while (0 != loop--) {
        doubly_linked_list_node_sid_set(tmp, sid);
        RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);

        doubly_linked_list_node_val_set(tmp, &sid);
        RESULT_CHECK_pointer(&sid, doubly_linked_list_node_val(tmp), &pass);

        doubly_linked_list_node_next_set(tmp, tmp);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);

        doubly_linked_list_node_previous_set(tmp, tmp);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);
    }

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_struct_field), pass);
}

static void
unit_test_doubly_linked_list_create(void)
{
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x923456fu;
    pass = true;
    while (0 != loop--) {
        tmp = doubly_linked_list_create();

        RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_sid(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

        doubly_linked_list_destroy(&tmp);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_create), pass);
}


static void
unit_test_doubly_linked_list_node_create(void)
{
    bool pass;
    uint32 sid;
    struct doubly_linked_list *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x923456fu;
    sid = 0xdeadu;
    pass = true;
    while (0 != loop--) {
        tmp = doubly_linked_list_node_create(&sid, sid);

        RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);
        RESULT_CHECK_pointer(&sid, doubly_linked_list_node_val(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

        doubly_linked_list_destroy(&tmp);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_node_create), pass);
}

static void
unit_test_doubly_linked_list_node_initial(void)
{
    bool pass;
    uint32 sid;
    struct doubly_linked_list *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x923456fu;
    pass = true;
    sid = 0xfadeu;
    tmp = NULL;

    doubly_linked_list_node_initial(tmp, &pass, sid);
    RESULT_CHECK_pointer(tmp, NULL, &pass);

    while (0 != loop--) {
        tmp = malloc_ds(sizeof(*tmp));
        doubly_linked_list_node_initial(tmp, &pass, sid);

        RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(tmp), &pass);

        doubly_linked_list_destroy(&tmp);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_node_initial), pass);
}

static void
unit_test_doubly_linked_list_initial(void)
{
    bool pass;
    struct doubly_linked_list *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xb23456fu;
    pass = true;
    tmp = malloc_ds(sizeof(*tmp));

    while (0 != loop--) {
        doubly_linked_list_initial(tmp);

        RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_sid(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);
    }

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_initial), pass);
}

static void
unit_test_doubly_linked_list_node_append(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *append;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x1223456u;
    head = unit_test_doubly_linked_list_sample(0x1a2E, 0x213D);
    pass = true;

    doubly_linked_list_node_append(NULL, &pass);

    while (0 != loop--) {
        next = doubly_linked_list_node_next(head);
        doubly_linked_list_node_append(head, &pass);
        append = doubly_linked_list_node_next(head);

        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(append), &pass);
        RESULT_CHECK_pointer(head, doubly_linked_list_node_previous(append), &pass);
        RESULT_CHECK_pointer(next, doubly_linked_list_node_next(append), &pass);
        RESULT_CHECK_pointer(append, doubly_linked_list_node_previous(next), &pass);
    }

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_append), pass);
}

static void
unit_test_doubly_linked_list_node_insert_before(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *copy;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    // loop = 0x1223456u;
    loop = 0x1;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x21f26, 0xbef19);
    doubly_linked_list_node_append(head, &pass);

    node = doubly_linked_list_create();
    copy = doubly_linked_list_node_copy(node);

    doubly_linked_list_node_insert_before(NULL, node);
    RESULT_CHECK_doubly_linked_list_node(copy, node, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);
    doubly_linked_list_destroy(&node);

    copy = doubly_linked_list_node_copy(head);
    doubly_linked_list_node_insert_before(head, NULL);
    RESULT_CHECK_doubly_linked_list_node(copy, head, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    while (0 != loop--) {
        node = doubly_linked_list_create();
        prev = doubly_linked_list_node_previous(head);
        doubly_linked_list_node_insert_before(head, node);
        RESULT_CHECK_pointer(node, doubly_linked_list_node_previous(head), &pass);
        RESULT_CHECK_pointer(head, doubly_linked_list_node_next(node), &pass);
        RESULT_CHECK_pointer(prev, doubly_linked_list_node_previous(node), &pass);
        RESULT_CHECK_pointer(node, doubly_linked_list_node_next(prev), &pass);
    }

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_insert_before), pass);
}

static void
unit_test_doubly_linked_list_node_insert_after(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *next;
    struct doubly_linked_list *copy;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x1223456u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x18ab, 0x2e9c);
    doubly_linked_list_node_append(head, &pass);

    node = doubly_linked_list_create();
    copy = doubly_linked_list_node_copy(node);

    doubly_linked_list_node_insert_after(NULL, node);
    RESULT_CHECK_doubly_linked_list_node(copy, node, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);
    doubly_linked_list_destroy(&node);

    copy = doubly_linked_list_node_copy(head);
    doubly_linked_list_node_insert_after(head, NULL);
    RESULT_CHECK_doubly_linked_list_node(copy, head, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    while (0 != loop--) {
        node = doubly_linked_list_create();
        next = doubly_linked_list_node_next(head);
        doubly_linked_list_node_insert_after(head, node);
        RESULT_CHECK_pointer(node, doubly_linked_list_node_next(head), &pass);
        RESULT_CHECK_pointer(head, doubly_linked_list_node_previous(node), &pass);
        RESULT_CHECK_pointer(next, doubly_linked_list_node_next(node), &pass);
        RESULT_CHECK_pointer(node, doubly_linked_list_node_previous(next), &pass);
    }

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_insert_after), pass);
}

static void
unit_test_doubly_linked_list_destroy(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x222u;
    iter = sizes;
    pass = true;
    head = NULL;
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (0 != loop--) {
        iter = sizes;
        while (iter < sizes + array_sizeof(sizes)) {
            len = *iter++;
            head = unit_test_doubly_linked_list_sample(0x16FA, len);

            doubly_linked_list_destroy(&head);
            RESULT_CHECK_pointer(NULL, head, &pass);
        }
    }

    head = doubly_linked_list_create();
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    test_result_print(SYM_2_STR(doubly_linked_list_destroy), pass);
}

static void
unit_test_doubly_linked_list_length(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x222u;
    pass = true;
    iter = sizes;
    while (0 != loop--) {
        iter = sizes;
        while (iter < sizes + array_sizeof(sizes)) {
            len = *iter++;
            head = unit_test_doubly_linked_list_sample(0x2ae8, len);
            RESULT_CHECK_uint32(len, doubly_linked_list_length(head), &pass);

            doubly_linked_list_destroy(&head);
        }
    }

    head = doubly_linked_list_create();
    RESULT_CHECK_uint32(0x1u, doubly_linked_list_length(head), &pass);
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_uint32(0x0u, doubly_linked_list_length(NULL), &pass);

    test_result_print(SYM_2_STR(doubly_linked_list_length), pass);
}

static void
unit_test_doubly_linked_list_node_by_index(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    uint32 len;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    tmp = doubly_linked_list_node_by_index(NULL, 0);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    loop = 0x22345u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x18fa, 0x23a2);
    len = doubly_linked_list_length(head);

    while (0 != loop--) {
        tmp = doubly_linked_list_node_by_index(head, 0);
        RESULT_CHECK_pointer(head, tmp, &pass);
    }

    tmp = doubly_linked_list_node_by_index(head, len);
    RESULT_CHECK_pointer(head, tmp, &pass);
    tmp = doubly_linked_list_node_by_index(head, len + 1);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(head), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_by_index), pass);
}

static void
unit_test_doubly_linked_list_contains_p(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x33456u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x1dd2, 0x28ae);
    tmp = doubly_linked_list_node_next(head);

    RESULT_CHECK_bool(false, doubly_linked_list_contains_p(NULL, tmp), &pass);

    while (0 != loop--) {
        tmp = doubly_linked_list_node_next(head);
        RESULT_CHECK_bool(true, doubly_linked_list_contains_p(head, tmp), &pass);
        tmp = doubly_linked_list_create();
        RESULT_CHECK_bool(false, doubly_linked_list_contains_p(head, tmp), &pass);
        doubly_linked_list_destroy(&tmp);
    }

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_contains_p), pass);
}

static void
unit_test_doubly_linked_list_serialize(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 *iter;
    uint32 len;
    uint32 index;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x334u;
    pass = true;
    iter = sizes;
    doubly_linked_list_serialize(NULL);

    while (0 != loop--) {
        iter = sizes;
        while (iter < sizes + array_sizeof(sizes)) {
            len = *iter++;
            head = unit_test_doubly_linked_list_sample(0x29e2, len);

            doubly_linked_list_serialize(head);
            tmp = head;
            index = 0u;
            do {
                RESULT_CHECK_uint32(index, doubly_linked_list_node_sid(tmp), &pass);
                index++;
                tmp = doubly_linked_list_node_next(tmp);
            } while (tmp != head);

            doubly_linked_list_destroy(&head);
        }
    }

    test_result_print(SYM_2_STR(doubly_linked_list_serialize), pass);
}

static void
unit_test_doubly_linked_list_node_copy(void)
{
    uint32 sid;
    bool pass;
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x5234567u;
    sid = 0xbedu;
    pass = true;
    head = doubly_linked_list_node_create(&pass, sid);

    doubly_linked_list_node_copy(NULL);
    tmp = doubly_linked_list_node_copy(head);
    while (0 != loop--) {
        doubly_linked_list_node_initial(tmp, NULL, 0x0u);
        doubly_linked_list_destroy(&tmp);
        tmp = doubly_linked_list_node_copy(head);
    }

    RESULT_CHECK_doubly_linked_list_node(tmp, head, &pass);

    doubly_linked_list_destroy(&head);
    doubly_linked_list_node_initial(tmp, NULL, 0x0u);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_copy), pass);
}

static void
unit_test_doubly_linked_list_node_remove(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    doubly_linked_list_node_remove(NULL);

    loop = 0x5234567u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x31e2, 0x28ed);
    tmp = head;
    next = head->next;

    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_remove(&head), &pass);
    RESULT_CHECK_pointer(next, head, &pass);
    doubly_linked_list_destroy(&tmp);
    doubly_linked_list_destroy(&head);

    while (0 != loop--) {
        head = doubly_linked_list_create();
        tmp = head;
        RESULT_CHECK_pointer(tmp, doubly_linked_list_node_remove(&head), &pass);
        RESULT_CHECK_pointer(NULL, head, &pass);
        doubly_linked_list_destroy(&tmp);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_node_remove), pass);
}

static void
unit_test_doubly_linked_list_node_remove_and_destroy(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    doubly_linked_list_node_remove(NULL);

    loop = 0x5234567u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x31e2, 0x28ed);
    next = head->next;

    doubly_linked_list_node_remove_and_destroy(&head);
    RESULT_CHECK_pointer(next, head, &pass);
    doubly_linked_list_destroy(&head);

    while (0 != loop--) {
        head = doubly_linked_list_create();
        doubly_linked_list_node_remove_and_destroy(&head);
        RESULT_CHECK_pointer(NULL, head, &pass);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_node_remove_and_destroy), pass);
}

static void
unit_test_doubly_linked_list_iterate(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3967u;
    pass = true;
    head = unit_test_doubly_linked_list_sample(0x1FE2, 0xBF81);

    doubly_linked_list_iterate(NULL, &linked_list_iterate_handler);
    doubly_linked_list_iterate(head, &linked_list_iterate_handler);

    tmp = head;
    do {
        RESULT_CHECK_uint32(0xdeadu, doubly_linked_list_node_sid(tmp), &pass);
        tmp = doubly_linked_list_node_next(tmp);
    } while (tmp != head);

    while (0 != loop--) {
        doubly_linked_list_iterate(head, &linked_list_iterate_handler);
    }
    doubly_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(doubly_linked_list_iterate), pass);
}

static void
unit_test_doubly_linked_list_merge(void)
{
    uint32 raw[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *head_n;
    struct doubly_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x7967u;
    pass = true;
    head = doubly_linked_list_create();
    doubly_linked_list_node_initial(head, raw, 0x0u);
    tmp = doubly_linked_list_node_create(raw + 1, 0x0u);
    doubly_linked_list_node_insert_before(head, tmp);
    tmp = doubly_linked_list_node_create(raw + 2, 0x0u);
    doubly_linked_list_node_insert_before(head, tmp);

    head_n = doubly_linked_list_create();
    doubly_linked_list_node_initial(head_n, raw + 2, 0x0u);
    tmp = doubly_linked_list_node_create(raw + 3, 0x0u);
    doubly_linked_list_node_insert_before(head_n, tmp);
    tmp = doubly_linked_list_node_create(raw + 4, 0x0u);
    doubly_linked_list_node_insert_before(head_n, tmp);

    RESULT_CHECK_pointer(NULL, doubly_linked_list_merge(NULL, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_merge(head, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_merge(NULL, head), &pass);

    head = doubly_linked_list_merge(head, head_n);
    RESULT_CHECK_uint32(0x6u, doubly_linked_list_length(head), &pass);

    while (0 != loop--) {
        head = doubly_linked_list_merge(head, head_n);
    }
    doubly_linked_list_destroy(&head);
    doubly_linked_list_destroy(&head_n);

    test_result_print(SYM_2_STR(doubly_linked_list_merge), pass);
}
