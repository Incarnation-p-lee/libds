static inline struct single_linked_list *
unit_test_single_linked_list_sample(uint32 range, uint32 node_count)
{
    struct single_linked_list *retval;
    struct single_linked_list *tmp;
    uint32 id;
    uint32 i;

    retval = single_linked_list_create();
    single_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        id = (uint32)(rand() % range);
        tmp = single_linked_list_create();
        single_linked_list_node_initial(tmp, tmp, id);
        single_linked_list_node_insert_after(retval, tmp);
        i++;
    }

    return retval;
}

static void
unit_test_single_linked_list_struct_field(void)
{
    uint32 id;
    bool pass;
    struct single_linked_list *tmp;

    id = 0xfade;
    pass = true;
    tmp = single_linked_list_create();

    single_linked_list_node_id_set(tmp, id);
    RESULT_CHECK_uint32(id, single_linked_list_node_id(tmp), &pass);

    single_linked_list_node_val_set(tmp, &id);
    RESULT_CHECK_pointer(&id, single_linked_list_node_val(tmp), &pass);

    single_linked_list_node_next_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_struct_field), pass);

    return;
}

static void
unit_test_single_linked_list_create(void)
{
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    tmp = single_linked_list_create();

    RESULT_CHECK_uint32(0x0u, single_linked_list_node_id(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_create), pass);

    return;
}

static void
unit_test_single_linked_list_node_create(void)
{
    bool pass;
    uint32 id;
    struct single_linked_list *tmp;

    pass = true;
    id = 0xdeadu;
    tmp = single_linked_list_node_create(&id, id);

    RESULT_CHECK_uint32(id, single_linked_list_node_id(tmp), &pass);
    RESULT_CHECK_pointer(&id, single_linked_list_node_val(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_node_create), pass);

    return;
}

static void
unit_test_single_linked_list_node_initial(void)
{
    bool pass;
    uint32 id;
    struct single_linked_list *tmp;

    pass = true;
    id = 0xfadeu;

    tmp = NULL;
    single_linked_list_node_initial(tmp, &pass, id);
    RESULT_CHECK_pointer(tmp, NULL, &pass);

    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_node_initial(tmp, &pass, id);

    RESULT_CHECK_uint32(id, single_linked_list_node_id(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);
    RESULT_CHECK_pointer(&pass, single_linked_list_node_val(tmp), &pass);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_node_initial), pass);
    return;
}

static void
unit_test_single_linked_list_initial(void)
{
    bool pass;
    struct single_linked_list *tmp;

    pass = true;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_initial(tmp);

    RESULT_CHECK_uint32(0x0u, single_linked_list_node_id(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_initial), pass);

    return;
}

static void
unit_test_single_linked_list_generate(void)
{
    struct single_linked_list *head;
    bool pass;
    uint32 *data;
    uint32 *tmp;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = single_linked_list_generate(NULL, 0xdeadu);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = single_linked_list_generate(data, len);

        tmp = data;
        while (tmp < data + len) {
            RESULT_CHECK_uint32(*tmp, single_linked_list_node_id(head), &pass);
            head = single_linked_list_node_next(head);
            tmp++;
        }

        RESULT_CHECK_uint32(*data, single_linked_list_node_id(head), &pass);

        free_ds(data);
        single_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(single_linked_list_generate), pass);
    return;
}

static void
unit_test_single_linked_list_node_append(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    struct single_linked_list *append;
    bool pass;
    uint32 id = 0xfadeu;

    pass = true;
    head = unit_test_single_linked_list_sample(0x1A2E, 0x213D);

    single_linked_list_node_append(NULL, id);

    next = head->next;
    single_linked_list_node_append(head, id);
    append = head->next;

    RESULT_CHECK_uint32(id, single_linked_list_node_id(append), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_node_previous(append), &pass);
    RESULT_CHECK_pointer(next, single_linked_list_node_next(append), &pass);
    RESULT_CHECK_pointer(append, single_linked_list_node_previous(next), &pass);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_append), pass);

    return;
}

static void
unit_test_single_linked_list_node_previous(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x19AB, 0x2BF3);
    single_linked_list_node_append(head, 0xdeadu);

    RESULT_CHECK_pointer(NULL, single_linked_list_node_previous(NULL), &pass);

    prev = single_linked_list_node_previous(head);
    RESULT_CHECK_pointer(prev, single_linked_list_node_previous(head), &pass);

    tmp = single_linked_list_node_next(head);
    single_linked_list_node_next_set(head, NULL);
    prev = single_linked_list_node_previous(head);
    RESULT_CHECK_pointer(NULL, prev, &pass);
    single_linked_list_node_next_set(head, tmp);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_previous), pass);

    return;
}

static void
unit_test_single_linked_list_node_insert_before(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *prev;
    struct single_linked_list *copy;
    bool pass;
    uint32 id;

    pass = true;
    id = 0xbedu;
    head = unit_test_single_linked_list_sample(0x21f26, 0xbef19);
    head = single_linked_list_create();
    single_linked_list_node_append(head, id);

    node = single_linked_list_create();
    copy = single_linked_list_node_copy(node);

    single_linked_list_node_insert_before(NULL, node);
    RESULT_CHECK_single_linked_list_node(copy, node, &pass);
    single_linked_list_node_initial(copy, NULL, 0x0u);
    single_linked_list_destroy(&copy);

    copy = single_linked_list_node_copy(head);
    single_linked_list_node_insert_before(head, NULL);
    RESULT_CHECK_single_linked_list_node(copy, head, &pass);
    single_linked_list_node_initial(copy, NULL, 0x0u);
    single_linked_list_destroy(&copy);

    prev = single_linked_list_node_previous(head);
    single_linked_list_node_insert_before(head, node);
    RESULT_CHECK_pointer(node, single_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_node_next(node), &pass);
    RESULT_CHECK_pointer(prev, single_linked_list_node_previous(node), &pass);
    RESULT_CHECK_pointer(node, single_linked_list_node_next(prev), &pass);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_insert_before), pass);
    return;
}

static void
unit_test_single_linked_list_node_insert_after(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *next;
    struct single_linked_list *copy;
    bool pass;
    uint32 id;

    pass = true;
    id = 0xfadeu;
    head = unit_test_single_linked_list_sample(0x18ab, 0x2e9c);
    single_linked_list_node_append(head, id);

    node = single_linked_list_create();
    copy = single_linked_list_node_copy(node);

    single_linked_list_node_insert_after(NULL, node);
    RESULT_CHECK_single_linked_list_node(copy, node, &pass);
    single_linked_list_node_initial(copy, NULL, 0x0u);
    single_linked_list_destroy(&copy);

    copy = single_linked_list_node_copy(head);
    single_linked_list_node_insert_after(head, NULL);
    RESULT_CHECK_single_linked_list_node(copy, head, &pass);
    single_linked_list_node_initial(copy, NULL, 0x0u);
    single_linked_list_destroy(&copy);

    next = head->next;
    single_linked_list_node_insert_after(head, node);
    RESULT_CHECK_pointer(node, single_linked_list_node_next(head), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_node_previous(node), &pass);
    RESULT_CHECK_pointer(next, single_linked_list_node_next(node), &pass);
    RESULT_CHECK_pointer(node, single_linked_list_node_previous(next), &pass);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_insert_after), pass);

    return;
}

static void
unit_test_single_linked_list_destroy(void)
{
    struct single_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = NULL;
    single_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(0x16FA, len);

        single_linked_list_destroy(&head);
        RESULT_CHECK_pointer(NULL, head, &pass);
    }

    head = single_linked_list_create();
    single_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    test_result_print(SYM_2_STR(single_linked_list_destroy), pass);

    return;
}

static void
unit_test_single_linked_list_length(void)
{
    struct single_linked_list *head;
    bool pass;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000,};

    iter = sizes;
    pass = true;
    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(0x2ae8, len);

        RESULT_CHECK_uint32(len, single_linked_list_length(head), &pass);

        single_linked_list_destroy(&head);
    }

    head = single_linked_list_create();
    RESULT_CHECK_uint32(0x1u, single_linked_list_length(head), &pass);
    single_linked_list_destroy(&head);

    RESULT_CHECK_uint32(0x0u, single_linked_list_length(NULL), &pass);

    test_result_print(SYM_2_STR(single_linked_list_length), pass);
    return;
}

static void
unit_test_single_linked_list_node_by_index(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    uint32 len;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x18fa, 0x23a2);
    len = single_linked_list_length(head);
    tmp = single_linked_list_node_by_index(head, 0);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = single_linked_list_node_by_index(head, len);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = single_linked_list_node_by_index(NULL, 0);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    tmp = single_linked_list_node_by_index(head, len + 1);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(head), &pass);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_by_index), pass);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_by_index), pass);

    return;
}

static void
unit_test_single_linked_list_node_exchange(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp_1;
    struct single_linked_list *tmp_2;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x14a2, 0x2e1d);
    tmp_1 = single_linked_list_node_previous(head);
    tmp_2 = head->next;

    single_linked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    RESULT_CHECK_pointer(tmp_2, single_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, single_linked_list_node_next(head), &pass);

    tmp_1 = head->next;
    tmp_2 = single_linked_list_node_previous(head);
    single_linked_list_node_exchange(head, head);
    RESULT_CHECK_pointer(tmp_2, single_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, single_linked_list_node_next(head), &pass);

    single_linked_list_node_exchange(head, NULL);
    RESULT_CHECK_pointer(tmp_2, single_linked_list_node_previous(head), &pass);
    RESULT_CHECK_pointer(tmp_1, single_linked_list_node_next(head), &pass);

    tmp_1 = single_linked_list_node_copy(head);
    single_linked_list_node_exchange(head, head);
    RESULT_CHECK_single_linked_list_node(tmp_1, head, &pass);
    single_linked_list_node_initial(tmp_1, NULL, 0x0u);
    single_linked_list_destroy(&tmp_1);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_node_exchange), pass);

    return;
}

static void
unit_test_single_linked_list_contains_p(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x1dd2, 0x28ae);
    tmp = head->next;

    RESULT_CHECK_bool(true, single_linked_list_contains_p(head, tmp), &pass);
    RESULT_CHECK_bool(false, single_linked_list_contains_p(NULL, tmp), &pass);

    tmp = single_linked_list_create();
    RESULT_CHECK_bool(false, single_linked_list_contains_p(head, tmp), &pass);

    single_linked_list_destroy(&tmp);
    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_contains_p), pass);

    return;
}

static void
unit_test_single_linked_list_serialize(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 *iter;
    uint32 len;
    uint32 index;

    pass = true;
    iter = sizes;
    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(0x29e2, len);

        single_linked_list_serialize(head);
        tmp = head;
        index = 0u;
        do {
            RESULT_CHECK_uint32(index, single_linked_list_node_id(tmp), &pass);
            index++;
            tmp = single_linked_list_node_next(tmp);
        } while (tmp != head);

        single_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(single_linked_list_serialize), pass);
    return;
}

static void
unit_test_single_linked_list_node_copy(void)
{
    uint32 id;
    bool pass;
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    id = 0xbedu;
    pass = true;
    head = single_linked_list_node_create(&pass, id);

    single_linked_list_node_copy(NULL);
    tmp = single_linked_list_node_copy(head);

    RESULT_CHECK_single_linked_list_node(tmp, head, &pass);

    single_linked_list_destroy(&head);
    single_linked_list_node_initial(tmp, NULL, 0x0u);
    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_node_copy), pass);
    return;
}

static void
unit_test_single_linked_list_node_remove(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x31e2, 0x28ed);
    tmp = single_linked_list_node_next(head);
    prev = single_linked_list_node_previous(head);

    single_linked_list_node_remove(NULL);

    RESULT_CHECK_pointer(tmp, single_linked_list_node_remove(head), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(prev), &pass);

    single_linked_list_destroy(&tmp);

    tmp = single_linked_list_create();
    RESULT_CHECK_pointer(NULL, single_linked_list_node_remove(tmp), &pass);

    test_result_print(SYM_2_STR(single_linked_list_remove_node), pass);

    return;
}

static void
unit_test_single_linked_list_node_lazy_remove(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0xeb28, 0xa23d);
    tmp = head->next;
    prev = single_linked_list_node_previous(head);

    single_linked_list_node_lazy_remove(NULL);
    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    single_linked_list_node_lazy_remove(head);

    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(head), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(prev), &pass);
    RESULT_CHECK_pointer(prev, single_linked_list_node_previous(tmp), &pass);

    /* Need to free the lazy node independently. */
    free_ds(head);

    single_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(single_linked_list_node_lazy_remove), pass);

    return;
}

static void
unit_test_single_linked_list_iterate(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x24E2, 0x1F82);

    single_linked_list_iterate(head, &linked_list_iterate_handler);
    single_linked_list_iterate(NULL, &linked_list_iterate_handler);

    tmp = head;
    do {
        RESULT_CHECK_uint32(0xdeadu, single_linked_list_node_id(tmp), &pass);
        tmp = single_linked_list_node_next(tmp);
    } while (tmp != head);

    single_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(single_linked_list_iterate), pass);

    return;
}

static void
unit_test_single_linked_list_join(void)
{
    uint32 raw[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf,};
    struct single_linked_list *head;
    struct single_linked_list *head_n;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = single_linked_list_create();
    single_linked_list_node_initial(head, raw, 0x0u);
    tmp = single_linked_list_node_create(raw + 1, 0x0u);
    single_linked_list_node_insert_before(head, tmp);
    tmp = single_linked_list_node_create(raw + 2, 0x0u);
    single_linked_list_node_insert_before(head, tmp);

    head_n = single_linked_list_create();
    single_linked_list_node_initial(head_n, raw + 2, 0x0u);
    tmp = single_linked_list_node_create(raw + 3, 0x0u);
    single_linked_list_node_insert_before(head_n, tmp);
    tmp = single_linked_list_node_create(raw + 4, 0x0u);
    single_linked_list_node_insert_before(head_n, tmp);

    RESULT_CHECK_pointer(NULL, single_linked_list_join(NULL, NULL), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_join(head, NULL), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_join(NULL, head), &pass);

    head = single_linked_list_join(head, head_n);
    RESULT_CHECK_uint32(0x6u, single_linked_list_length(head), &pass);

    single_linked_list_destroy(&head);
    single_linked_list_destroy(&head_n);
    test_result_print(SYM_2_STR(single_linked_list_join), pass);

    return;
}
