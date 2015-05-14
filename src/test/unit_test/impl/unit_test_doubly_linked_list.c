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

    sid = 0xfade;
    pass = true;
    tmp = doubly_linked_list_create();

    doubly_linked_list_node_sid_set(tmp, sid);
    RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);

    doubly_linked_list_node_val_set(tmp, &sid);
    RESULT_CHECK_pointer(&sid, doubly_linked_list_node_val(tmp), &pass);

    doubly_linked_list_node_next_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);

    doubly_linked_list_node_previous_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_struct_field), pass);

    return;
}

static void
unit_test_doubly_linked_list_create(void)
{
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    tmp = doubly_linked_list_create();

    RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_create), pass);

    return;
}


static void
unit_test_doubly_linked_list_node_create(void)
{
    bool pass;
    uint32 sid;
    struct doubly_linked_list *tmp;

    sid = 0xdeadu;
    pass = true;
    tmp = doubly_linked_list_node_create(&sid, sid);

    RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(&sid, doubly_linked_list_node_val(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_create), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_initial(void)
{
    bool pass;
    uint32 sid;
    struct doubly_linked_list *tmp;

    pass = true;
    sid = 0xfadeu;

    tmp = NULL;
    doubly_linked_list_node_initial(tmp, &pass, sid);
    RESULT_CHECK_pointer(tmp, NULL, &pass);

    tmp = malloc_ds(sizeof(*tmp));
    doubly_linked_list_node_initial(tmp, &pass, sid);

    RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_initial), pass);

    return;
}

static void
unit_test_doubly_linked_list_initial(void)
{
    bool pass;
    struct doubly_linked_list *tmp;

    pass = true;
    tmp = malloc_ds(sizeof(*tmp));
    doubly_linked_list_initial(tmp);

    RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_initial), pass);

    return;
}

static void
unit_test_doubly_linked_list_generate(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *tmp;
    uint32 *iter;
    uint32 *data;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = doubly_linked_list_generate(NULL, 0xdeadu);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = doubly_linked_list_generate(data, len);

        tmp = data;
        while (tmp < data + len) {
            RESULT_CHECK_uint32(*tmp, doubly_linked_list_node_sid(head), &pass);
            head = doubly_linked_list_node_next(head);
            tmp++;
        }

        RESULT_CHECK_uint32(*data, doubly_linked_list_node_sid(head), &pass);

        free_ds(data);
        doubly_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_generate), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_append(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *append;
    bool pass;
    uint32 sid = 0xfadeu;

    head = unit_test_doubly_linked_list_sample(0x1a2E, 0x213D);
    pass = true;

    doubly_linked_list_node_append(NULL, sid);

    next = doubly_linked_list_node_next(head);
    doubly_linked_list_node_append(head, sid);
    append = doubly_linked_list_node_next(head);

    RESULT_CHECK_uint32(sid, doubly_linked_list_node_sid(append), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_previous(append), &pass);
    RESULT_CHECK_pointer(next, doubly_linked_list_node_next(append), &pass);
    RESULT_CHECK_pointer(append, doubly_linked_list_node_previous(next), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_append), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_insert_before(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *copy;
    bool pass;
    uint32 sid;

    pass = true;
    sid = 0xbeadu;
    head = unit_test_doubly_linked_list_sample(0x21f26, 0xbef19);
    doubly_linked_list_node_append(head, sid);

    node = doubly_linked_list_create();
    copy = doubly_linked_list_node_copy(node);

    doubly_linked_list_node_insert_before(NULL, node);
    RESULT_CHECK_doubly_linked_list_node(copy, node, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    copy = doubly_linked_list_node_copy(head);
    doubly_linked_list_node_insert_before(head, NULL);
    RESULT_CHECK_doubly_linked_list_node(copy, head, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    prev = doubly_linked_list_node_previous(head);
    doubly_linked_list_node_insert_before(head, node);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_next(node), &pass);
    RESULT_CHECK_pointer(prev, doubly_linked_list_node_previous(node), &pass);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_next(prev), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_insert_before), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_insert_after(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *next;
    struct doubly_linked_list *copy;
    bool pass;
    uint32 sid;

    pass = true;
    sid = 0xbedu;
    head = unit_test_doubly_linked_list_sample(0x18ab, 0x2e9c);
    doubly_linked_list_node_append(head, sid);

    node = doubly_linked_list_create();
    copy = doubly_linked_list_node_copy(node);

    doubly_linked_list_node_insert_after(NULL, node);
    RESULT_CHECK_doubly_linked_list_node(copy, node, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    copy = doubly_linked_list_node_copy(head);
    doubly_linked_list_node_insert_after(head, NULL);
    RESULT_CHECK_doubly_linked_list_node(copy, head, &pass);
    doubly_linked_list_node_initial(copy, NULL, 0x0u);
    doubly_linked_list_destroy(&copy);

    next = doubly_linked_list_node_next(head);
    doubly_linked_list_node_insert_after(head, node);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_next(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_previous(node), &pass);
    RESULT_CHECK_pointer(next, doubly_linked_list_node_next(node), &pass);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_previous(next), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_insert_after), pass);

    return;
}

static void
unit_test_doubly_linked_list_destroy(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = NULL;
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_doubly_linked_list_sample(0x16FA, len);

        doubly_linked_list_destroy(&head);
        RESULT_CHECK_pointer(NULL, head, &pass);
    }

    head = doubly_linked_list_create();
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    test_result_print(SYM_2_STR(doubly_linked_list_destroy), pass);

    return;
}

static void
unit_test_doubly_linked_list_length(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    pass = true;
    iter = sizes;

    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_doubly_linked_list_sample(0x2ae8, len);

        RESULT_CHECK_uint32(len, doubly_linked_list_length(head), &pass);

        doubly_linked_list_destroy(&head);
    }

    head = doubly_linked_list_create();
    RESULT_CHECK_uint32(0x1u, doubly_linked_list_length(head), &pass);
    doubly_linked_list_destroy(&head);

    RESULT_CHECK_uint32(0x0u, doubly_linked_list_length(NULL), &pass);

    test_result_print(SYM_2_STR(doubly_linked_list_length), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_by_index(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    uint32 len;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0x18fa, 0x23a2);
    len = doubly_linked_list_length(head);
    tmp = doubly_linked_list_node_by_index(head, 0);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = doubly_linked_list_node_by_index(head, len);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = doubly_linked_list_node_by_index(NULL, 0);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    tmp = doubly_linked_list_node_by_index(head, len + 1);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(head), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_by_index), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_exchange(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp_1;
    struct doubly_linked_list *tmp_2;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0x14a2, 0x2e1d);
    tmp_1 = doubly_linked_list_node_previous(head);
    tmp_2 = doubly_linked_list_node_next(head);

    doubly_linked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next(head), &pass);

    tmp_1 = doubly_linked_list_node_next(head);
    tmp_2 = doubly_linked_list_node_previous(head);
    doubly_linked_list_node_exchange(head, head);
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next(head), &pass);

    doubly_linked_list_node_exchange(head, NULL);
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next(head), &pass);

    tmp_1 = doubly_linked_list_node_copy(head);
    doubly_linked_list_node_exchange(head, head);
    RESULT_CHECK_doubly_linked_list_node(tmp_1, head, &pass);
    doubly_linked_list_node_initial(tmp_1, NULL, 0x0u);
    doubly_linked_list_destroy(&tmp_1);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_exchange), pass);

    return;
}

static void
unit_test_doubly_linked_list_contains_p(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0x1dd2, 0x28ae);
    tmp = doubly_linked_list_node_next(head);

    RESULT_CHECK_bool(true, doubly_linked_list_contains_p(head, tmp), &pass);
    RESULT_CHECK_bool(false, doubly_linked_list_contains_p(NULL, tmp), &pass);

    tmp = doubly_linked_list_create();
    RESULT_CHECK_bool(false, doubly_linked_list_contains_p(head, tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_contains_p), pass);

    return;
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

    pass = true;
    iter = sizes;
    doubly_linked_list_serialize(NULL);

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

    test_result_print(SYM_2_STR(doubly_linked_list_serialize), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_copy(void)
{
    uint32 sid;
    bool pass;
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    sid = 0xbedu;
    pass = true;
    head = doubly_linked_list_node_create(&pass, sid);

    doubly_linked_list_node_copy(NULL);
    tmp = doubly_linked_list_node_copy(head);

    RESULT_CHECK_doubly_linked_list_node(tmp, head, &pass);

    doubly_linked_list_destroy(&head);
    doubly_linked_list_node_initial(tmp, NULL, 0x0u);
    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_copy), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_remove(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0x31e2, 0x28ed);
    tmp = doubly_linked_list_node_next(head);
    prev = doubly_linked_list_node_previous(head);

    doubly_linked_list_node_remove(NULL);

    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_remove(&head), &pass);
    RESULT_CHECK_pointer(NULL, head, &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(prev), &pass);

    doubly_linked_list_destroy(&tmp);

    tmp = doubly_linked_list_create();
    RESULT_CHECK_pointer(NULL, doubly_linked_list_node_remove(&tmp), &pass);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    test_result_print(SYM_2_STR(doubly_linked_list_node_remove), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_lazy_remove(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0xeb28, 0xa23d);
    prev = doubly_linked_list_node_previous(head);
    tmp = doubly_linked_list_node_next(head);

    doubly_linked_list_node_lazy_remove(NULL);

    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_lazy_remove(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_next(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next(prev), &pass);
    RESULT_CHECK_pointer(prev, doubly_linked_list_node_previous(tmp), &pass);

    /* Need to free the lazy node independently. */
    free_ds(head);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_lazy_remove), pass);

    return;
}

static void
unit_test_doubly_linked_list_iterate(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_doubly_linked_list_sample(0x1FE2, 0xBF81);

    doubly_linked_list_iterate(NULL, &linked_list_iterate_handler);
    doubly_linked_list_iterate(head, &linked_list_iterate_handler);

    tmp = head;
    do {
        RESULT_CHECK_uint32(0xdeadu, doubly_linked_list_node_sid(tmp), &pass);
        tmp = doubly_linked_list_node_next(tmp);
    } while (tmp != head);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_iterate), pass);

    return;
}

static void
unit_test_doubly_linked_list_join(void)
{
    uint32 raw[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *head_n;
    struct doubly_linked_list *tmp;
    bool pass;

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

    RESULT_CHECK_pointer(NULL, doubly_linked_list_join(NULL, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_join(head, NULL), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_join(NULL, head), &pass);

    head = doubly_linked_list_join(head, head_n);
    RESULT_CHECK_uint32(0x6u, doubly_linked_list_length(head), &pass);

    doubly_linked_list_destroy(&head);
    doubly_linked_list_destroy(&head_n);
    test_result_print(SYM_2_STR(doubly_linked_list_join), pass);

    return;
}
