static void
test_dlinked_list_create(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = dlinked_list_create();
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp && tmp->previous == tmp) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_create), is_passed);
    return;
}


static void
test_dlinked_list_node_create(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = dlinked_list_node_create(&is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp
            && tmp->previous == tmp && tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_node_create), is_passed);
    return;
}

static void
test_dlinked_list_node_initial(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    dlinked_list_node_initial(tmp, &is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp
            && tmp->previous == tmp && tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_node_initial), is_passed);
    return;
}

static void
test_dlinked_list_node_set_val(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    dlinked_list_node_initial(tmp, NULL, 0u);
    dlinked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_node_set_val), is_passed);
    return;
}

static void
test_dlinked_list_node_get_val(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    dlinked_list_node_initial(tmp, NULL, 0u);
    dlinked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (&is_passed == dlinked_list_node_get_val(tmp)) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_node_get_val), is_passed);
    return;
}

static void
test_dlinked_list_initial(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    dlinked_list_initial(tmp);
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp && tmp->previous == tmp) {
            is_passed = true;
        }
    }
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_initial), is_passed);
    return;
}

static void
test_dlinked_list_generate(void)
{
    struct doubly_linked_list *head;
    bool is_passed;
    uint32 *data;
    uint32 *tmp;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = dlinked_list_generate(data, len);

        tmp = data;
        while (tmp < data + len) {
            if (*tmp++ != head->id) {
                is_passed = false;
                break;
            }
            head = head->next;
        }
        if (*data != head->id) {
            is_passed = false;
        }
        free_ds(data);
        dlinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(dlinked_list_generate), is_passed);
    return;
}

static void
test_dlinked_list_node_append(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *append;
    bool is_passed;
    uint32 tmp = 0xAu;

    head = dlinked_list_create();
    is_passed = false;
    next = head->next;

    dlinked_list_node_append(head, tmp);
    append = head->next;
    if (append->id == tmp && append->previous == next
        && next->previous == append && append->next == next) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_node_append), is_passed);
    return;
}

static void
test_dlinked_list_node_next(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    bool is_passed;

    is_passed = false;
    head = dlinked_list_create();
    dlinked_list_node_append(head, 0xDEADu);

    next = dlinked_list_node_next(head);
    if (next == head->next) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->next = NULL;
    next = dlinked_list_node_next(head);
    if (NULL != next) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(dlinked_list_node_next), is_passed);
    return;
}

static void
test_dlinked_list_node_previous(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    bool is_passed;

    is_passed = false;
    head = dlinked_list_create();
    dlinked_list_node_append(head, 0xDEADu);

    prev = dlinked_list_node_previous(head);
    if (prev == head->previous) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->previous = NULL;
    prev = dlinked_list_node_previous(head);
    if (NULL != prev) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(dlinked_list_node_previous), is_passed);
    return;
}

static void
test_dlinked_list_node_insert_before(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *prev;
    bool is_passed;
    int mark;

    is_passed = false;
    mark = 0xDEADu;
    head = dlinked_list_create();
    dlinked_list_node_append(head, mark);

    prev = head->previous;
    node = dlinked_list_create();
    dlinked_list_node_insert_before(head, node);
    if (head->previous == node && node->next == head
        && node->previous == prev && prev->next == node) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_node_insert_before), is_passed);
    return;
}

static void
test_dlinked_list_node_insert_after(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *next;
    bool is_passed;
    uint32 mark;

    is_passed = false;
    mark = 0xDEADu;
    head = dlinked_list_create();
    dlinked_list_node_append(head, mark);

    next = head->next;
    node = dlinked_list_create();
    dlinked_list_node_insert_after(head, node);
    if (head->next == node && node->previous == head
        && node->next == next && next->previous == node) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_node_insert_after), is_passed);
    return;
}

static void
test_dlinked_list_destroy(void)
{
    struct doubly_linked_list *head;
    bool is_passed;
    uint32 *data;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = dlinked_list_generate(data, len);

        free_ds(data);
        dlinked_list_destroy(&head);
        if (NULL != head) {
            is_passed = false;
        }
    }

    head = dlinked_list_create();
    dlinked_list_destroy(&head);
    if (NULL != head) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(dlinked_list_destroy), is_passed);
    return;
}

static void
test_dlinked_list_length(void)
{
    struct doubly_linked_list *head;
    bool is_passed;
    uint32 *data;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = (uint32 *)int_array_generate(len);
        head = dlinked_list_generate(data, len);

        if (len != dlinked_list_length(head)) {
            is_passed = false;
        }

        free_ds(data);
        dlinked_list_destroy(&head);
    }

    head = dlinked_list_create();
    if (1u != dlinked_list_length(head)) {
        is_passed = false;
    }
    dlinked_list_destroy(&head);

    if (0u != dlinked_list_length(NULL)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(dlinked_list_length), is_passed);
    return;
}

static void
test_dlinked_list_node_get_by_index(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = dlinked_list_node_get_by_index(head, 0);
    if (head != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_node_get_by_index(head, -1);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_node_get_by_index(NULL, 0);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_node_get_by_index(head, sizeof(raw) / sizeof(raw[0]));
    if (head != tmp) {
        is_passed = false;
    }

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_node_get_by_index), is_passed);
    return;
}

static void
test_dlinked_list_node_exchange(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp_1;
    struct doubly_linked_list *tmp_2;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp_1 = head->previous;
    tmp_2 = head->next;

    dlinked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    if (head->previous != tmp_2 || head->next != tmp_1) {
        is_passed = false;
    }

    tmp_1 = head->next;
    tmp_2 = head->previous;
    dlinked_list_node_exchange(head, head);
    if (tmp_1 != head->next || tmp_2 != head->previous) {
        is_passed = false;
    }

    dlinked_list_node_exchange(head, NULL);
    if (tmp_1 != head->next || tmp_2 != head->previous) {
        is_passed = false;
    }

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_node_exchange), is_passed);
    return;
}

static void
test_dlinked_list_contains_p(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    if (true != dlinked_list_contains_p(head, tmp)) {
        is_passed = false;
    }

    if (false != dlinked_list_contains_p(NULL, tmp)) {
        is_passed = false;
    }

    tmp = dlinked_list_create();
    if (false != dlinked_list_contains_p(head, tmp)) {
        is_passed = false;
    }
    dlinked_list_destroy(&tmp);

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_contains_p), is_passed);
    return;
}

static void
test_dlinked_list_serialize(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 *iter;
    uint32 *raw;
    uint32 len;
    uint32 index;

    is_passed = true;
    iter = sizes;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        raw = (uint32 *)int_array_generate(len);
        head = dlinked_list_generate(raw, len);

        dlinked_list_serialize(head);
        tmp = head;
        index = 0u;
        do {
            if (tmp->id != index) {
                is_passed = false;
                break;
            }
            index++;
            tmp = tmp->next;
        } while (tmp != head);

        free_ds(raw);
        dlinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(dlinked_list_serialize), is_passed);
    return;
}

static void
test_dlinked_list_node_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = head->previous;

    if (tmp != dlinked_list_node_remove(head)) {
        is_passed = false;
    }

    if (tmp != prev->next) {
        is_passed = false;
    }

    dlinked_list_destroy(&tmp);

    tmp = dlinked_list_create();
    if (NULL != dlinked_list_node_remove(tmp)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(dlinked_list_node_remove), is_passed);
    return;
}

static void
test_dlinked_list_node_lazy_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = head->previous;

    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    dlinked_list_node_lazy_remove(head);
    if (tmp != head->next && prev != head->previous) {
        is_passed = false;
    }

    if (prev->next != tmp && tmp->previous != prev) {
        is_passed = false;
    }

    /* Need to free the lazy node independently. */
    free_ds(head);
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_node_lazy_remove), is_passed);
    return;
}

static void
test_dlinker_list_iterate(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));

    dlinked_list_iterate(head, &dlinked_list_iterate_handler);

    tmp = head;
    do {
        if (tmp->id != 0xDEADu) {
            is_passed = false;
            break;
        }
        tmp = tmp->next;
    } while (tmp != head);

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_iterate_node), is_passed);
    return;
}

static void
test_dlinked_list_join(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *head_n;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_create();
    dlinked_list_node_initial(head, raw, 0x0u);
    tmp = dlinked_list_node_create(raw + 1, 0x0u);
    dlinked_list_node_insert_before(head, tmp);
    tmp = dlinked_list_node_create(raw + 2, 0x0u);
    dlinked_list_node_insert_before(head, tmp);

    head_n = dlinked_list_create();
    dlinked_list_node_initial(head_n, raw + 2, 0x0u);
    tmp = dlinked_list_node_create(raw + 3, 0x0u);
    dlinked_list_node_insert_before(head_n, tmp);
    tmp = dlinked_list_node_create(raw + 4, 0x0u);
    dlinked_list_node_insert_before(head_n, tmp);

    if (NULL != dlinked_list_join(NULL, NULL)) {
        is_passed = false;
    }

    if (head != dlinked_list_join(head, NULL)) {
        is_passed = false;
    }

    if (head != dlinked_list_join(NULL, head)) {
        is_passed = false;
    }

    head = dlinked_list_join(head, head_n);
    if (0x6u != dlinked_list_length(head)) {
        is_passed = false;
    }

    dlinked_list_destroy(&head);
    dlinked_list_destroy(&head_n);

    test_result_print(SYM_2_STR(dlinked_list_join), is_passed);
    return;
}
