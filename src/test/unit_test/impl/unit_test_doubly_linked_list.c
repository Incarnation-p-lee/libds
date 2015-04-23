static inline struct doubly_linked_list *
unit_test_doubly_linked_list_sample(uint32 range, uint32 node_count)
{
    struct doubly_linked_list *retval;
    struct doubly_linked_list *tmp;
    uint32 id;
    uint32 i;

    retval = doubly_linked_list_create();
    doubly_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        id = (uint32)(rand() % range);
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_initial(tmp, tmp, id);
        doubly_linked_list_node_insert_before(retval, tmp);
        i++;
    }

    return retval;
}

static void
unit_test_doubly_linked_list_struct_field(void)
{
    uint32 id;
    bool pass;
    struct doubly_linked_list *tmp;

    id = 0xfade;
    pass = true;
    tmp = doubly_linked_list_create();

    doubly_linked_list_node_id_set(tmp, id);
    RESULT_CHECK_uint32(id, doubly_linked_list_node_id_get(tmp), &pass);

    doubly_linked_list_node_val_set(tmp, &id);
    RESULT_CHECK_pointer(&id, doubly_linked_list_node_val_get(tmp), &pass);

    doubly_linked_list_node_next_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(tmp), &pass);

    doubly_linked_list_node_previous_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous_get(tmp), &pass);

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

    RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_id_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous_get(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_create), pass);

    return;
}


static void
unit_test_doubly_linked_list_node_create(void)
{
    bool pass;
    uint32 id;
    struct doubly_linked_list *tmp;

    id = 0xdeadu;
    pass = true;
    tmp = doubly_linked_list_node_create(&id, id);

    RESULT_CHECK_uint32(id, doubly_linked_list_node_id_get(tmp), &pass);
    RESULT_CHECK_pointer(&id, doubly_linked_list_node_val_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous_get(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_node_create), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_initial(void)
{
    bool pass;
    uint32 id;
    struct doubly_linked_list *tmp;

    pass = true;
    id = 0xfadeu;

    tmp = NULL;
    doubly_linked_list_node_initial(tmp, &pass, id);
    RESULT_CHECK_pointer(tmp, NULL, &pass);

    tmp = malloc_ds(sizeof(*tmp));
    doubly_linked_list_node_initial(tmp, &pass, id);

    RESULT_CHECK_uint32(id, doubly_linked_list_node_id_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous_get(tmp), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val_get(tmp), &pass);

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

    RESULT_CHECK_uint32(0x0u, doubly_linked_list_node_id_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(tmp), &pass);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_previous_get(tmp), &pass);

    doubly_linked_list_destroy(&tmp);
    test_result_print(SYM_2_STR(doubly_linked_list_initial), pass);

    return;
}

static void
unit_test_doubly_linked_list_generate(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *data;
    uint32 *tmp;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = doubly_linked_list_generate(NULL, 0xdeadu);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = doubly_linked_list_generate(data, len);

        tmp = data;
        while (tmp < data + len) {
            RESULT_CHECK_uint32(*tmp, doubly_linked_list_node_id_get(head), &pass);
            head = doubly_linked_list_node_next_get(head);
            tmp++;
        }

        RESULT_CHECK_uint32(*data, doubly_linked_list_node_id_get(head), &pass);

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
    uint32 id = 0xfadeu;

    head = doubly_linked_list_create();
    pass = true;

    doubly_linked_list_node_append(NULL, id);

    next = head->next;
    doubly_linked_list_node_append(head, id);
    append = head->next;

    RESULT_CHECK_uint32(id, doubly_linked_list_node_id_get(append), &pass);
    RESULT_CHECK_pointer(next, doubly_linked_list_node_previous_get(append), &pass);
    RESULT_CHECK_pointer(next, doubly_linked_list_node_next_get(append), &pass);
    RESULT_CHECK_pointer(append, doubly_linked_list_node_previous_get(next), &pass);

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
    uint32 id;

    pass = true;
    id = 0xbeadu;
    head = doubly_linked_list_create();
    doubly_linked_list_node_append(head, id);

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

    prev = head->previous;
    doubly_linked_list_node_insert_before(head, node);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_previous_get(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_next_get(node), &pass);
    RESULT_CHECK_pointer(prev, doubly_linked_list_node_previous_get(node), &pass);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_next_get(prev), &pass);

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
    uint32 id;

    pass = true;
    id = 0xbedu;
    head = doubly_linked_list_create();
    doubly_linked_list_node_append(head, id);

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

    next = head->next;
    doubly_linked_list_node_insert_after(head, node);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_next_get(head), &pass);
    RESULT_CHECK_pointer(head, doubly_linked_list_node_previous_get(node), &pass);
    RESULT_CHECK_pointer(next, doubly_linked_list_node_next_get(node), &pass);
    RESULT_CHECK_pointer(node, doubly_linked_list_node_previous_get(next), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_insert_after), pass);

    return;
}

static void
unit_test_doubly_linked_list_destroy(void)
{
    struct doubly_linked_list *head;
    bool pass;
    uint32 *data;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    pass = true;

    head = NULL;
    doubly_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = doubly_linked_list_generate(data, len);

        free_ds(data);
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
    uint32 *data;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    pass = true;
    iter = sizes;

    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = doubly_linked_list_generate(data, len);

        RESULT_CHECK_uint32(len, doubly_linked_list_length(head), &pass);

        free_ds(data);
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
unit_test_doubly_linked_list_node_get_by_index(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = doubly_linked_list_generate(raw, array_sizeof(raw));
    tmp = doubly_linked_list_node_get_by_index(head, 0);
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = doubly_linked_list_node_get_by_index(head, array_sizeof(raw));
    RESULT_CHECK_pointer(head, tmp, &pass);

    tmp = doubly_linked_list_node_get_by_index(NULL, 0);
    RESULT_CHECK_pointer(NULL, tmp, &pass);

    tmp = doubly_linked_list_node_get_by_index(head, array_sizeof(raw) + 1);
    RESULT_CHECK_pointer(tmp, doubly_linked_list_node_next_get(head), &pass);

    doubly_linked_list_destroy(&head);
    test_result_print(SYM_2_STR(doubly_linked_list_node_get_by_index), pass);

    return;
}

static void
unit_test_doubly_linked_list_node_exchange(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp_1;
    struct doubly_linked_list *tmp_2;
    bool pass;

    pass = true;
    head = doubly_linked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp_1 = head->previous;
    tmp_2 = head->next;

    doubly_linked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous_get(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next_get(head), &pass);

    tmp_1 = head->next;
    tmp_2 = head->previous;
    doubly_linked_list_node_exchange(head, head);
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous_get(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next_get(head), &pass);

    doubly_linked_list_node_exchange(head, NULL);
    RESULT_CHECK_pointer(tmp_2, doubly_linked_list_node_previous_get(head), &pass);
    RESULT_CHECK_pointer(tmp_1, doubly_linked_list_node_next_get(head), &pass);

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
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = doubly_linked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;

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
    uint32 *raw;
    uint32 len;
    uint32 index;

    pass = true;
    iter = sizes;
    doubly_linked_list_serialize(NULL);

    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        raw = (uint32 *)int_array_generate(len);
        head = doubly_linked_list_generate(raw, len);

        doubly_linked_list_serialize(head);
        tmp = head;
        index = 0u;
        do {
            RESULT_CHECK_uint32(index, doubly_linked_list_node_id_get(tmp), &pass);
            index++;
            tmp = doubly_linked_list_node_next_get(tmp);
        } while (tmp != head);

        free_ds(raw);
        doubly_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(doubly_linked_list_serialize), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = doubly_linked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = head->previous;

    if (tmp != doubly_linked_list_node_remove(head)) {
        pass = false;
    }

    if (tmp != prev->next) {
        pass = false;
    }

    doubly_linked_list_destroy(&tmp);

    tmp = doubly_linked_list_create();
    if (NULL != doubly_linked_list_node_remove(tmp)) {
        pass = false;
    }

    test_result_print(SYM_2_STR(doubly_linked_list_node_remove), pass);
    return;
}

static void
unit_test_doubly_linked_list_node_lazy_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool pass;

    pass = true;
    head = doubly_linked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = head->previous;

    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    doubly_linked_list_node_lazy_remove(head);
    if (tmp != head->next && prev != head->previous) {
        pass = false;
    }

    if (prev->next != tmp && tmp->previous != prev) {
        pass = false;
    }

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

    doubly_linked_list_iterate(head, &linked_list_iterate_handler);

    tmp = head;
    do {
        if (tmp->id != 0xDEADu) {
            pass = false;
            break;
        }
        tmp = tmp->next;
    } while (tmp != head);

    doubly_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(doubly_linked_list_iterate), pass);
    return;
}

static void
unit_test_doubly_linked_list_join(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
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

    if (NULL != doubly_linked_list_join(NULL, NULL)) {
        pass = false;
    }

    if (head != doubly_linked_list_join(head, NULL)) {
        pass = false;
    }

    if (head != doubly_linked_list_join(NULL, head)) {
        pass = false;
    }

    head = doubly_linked_list_join(head, head_n);
    if (0x6u != doubly_linked_list_length(head)) {
        pass = false;
    }

    doubly_linked_list_destroy(&head);
    doubly_linked_list_destroy(&head_n);

    test_result_print(SYM_2_STR(doubly_linked_list_join), pass);
    return;
}
