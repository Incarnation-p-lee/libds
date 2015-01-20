static void
test_slinked_list_create(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = slinked_list_create();
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp
            && slinked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_create), is_passed);
    return;
}

static void
test_slinked_list_node_create(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = slinked_list_node_create(&is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp
            && tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_node_create), is_passed);
    return;
}

static void
test_slinked_list_node_initial(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    slinked_list_node_initial(tmp, &is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp && tmp->val == &is_passed
            && slinked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_node_initial), is_passed);
    return;
}

static void
test_slinked_list_initial(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    slinked_list_initial(tmp);
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp
            && slinked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_initial), is_passed);
    return;
}

static void
test_slinked_list_node_set_val(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    slinked_list_node_initial(tmp, NULL, 0u);
    slinked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_node_set_val), is_passed);
    return;
}

static void
test_slinked_list_node_get_val(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    slinked_list_node_initial(tmp, NULL, 0u);
    slinked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (&is_passed == slinked_list_node_get_val(tmp)) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_node_get_val), is_passed);
    return;
}

static void
test_slinked_list_generate(void)
{
    struct single_linked_list *head;
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
        head = slinked_list_generate(data, len);

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
        slinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(slinked_list_generate), is_passed);
    return;
}

static void
test_slinked_list_node_append(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    struct single_linked_list *append;
    bool is_passed;
    uint32 tmp = 0xAu;

    head = slinked_list_create();
    is_passed = false;
    next = head->next;

    slinked_list_node_append(head, tmp);
    append = head->next;
    if (append->id == tmp && slinked_list_node_previous(append) == next
        && slinked_list_node_previous(next) == append && append->next == next) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_node_append), is_passed);
    return;
}

static void
test_slinked_list_node_next(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    bool is_passed;

    is_passed = false;
    head = slinked_list_create();
    slinked_list_node_append(head, 0xDEADu);

    next = slinked_list_node_next(head);
    if (next == head->next) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->next = NULL;
    next = slinked_list_node_next(head);
    if (NULL != next) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(slinked_list_node_next), is_passed);
    return;
}

static void
test_slinked_list_node_previous(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    bool is_passed;

    is_passed = false;
    head = slinked_list_create();
    slinked_list_node_append(head, 0xDEADu);

    prev = slinked_list_node_previous(head);
    if (prev == slinked_list_node_previous(head)) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->next = NULL;
    prev = slinked_list_node_previous(head);
    if (NULL != prev) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(slinked_list_node_previous), is_passed);
    return;
}

static void
test_slinked_list_node_insert_before(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *prev;
    bool is_passed;
    uint32 mark;

    is_passed = false;
    mark = 0xDEADu;
    head = slinked_list_create();
    slinked_list_node_append(head, mark);

    prev = slinked_list_node_previous(head);
    node = slinked_list_create();
    slinked_list_node_insert_before(head, node);
    if (slinked_list_node_previous(head) == node && node->next == head
        && slinked_list_node_previous(node) == prev && prev->next == node) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_node_insert_before), is_passed);
    return;
}

static void
test_slinked_list_node_insert_after(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *next;
    bool is_passed;
    uint32 mark;

    is_passed = false;
    mark = 0xDEADu;
    head = slinked_list_create();
    slinked_list_node_append(head, mark);

    next = head->next;
    node = slinked_list_create();
    slinked_list_node_insert_after(head, node);
    if (head->next == node && slinked_list_node_previous(node) == head
        && node->next == next && slinked_list_node_previous(next) == node) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_node_insert_after), is_passed);
    return;
}

static void
test_slinked_list_destroy(void)
{
    struct single_linked_list *head;
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
        head = slinked_list_generate(data, len);

        free_ds(data);
        slinked_list_destroy(&head);
        if (NULL != head) {
            is_passed = false;
        }
    }

    head = slinked_list_create();
    slinked_list_destroy(&head);
    if (NULL != head) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(slinked_list_destroy), is_passed);
    return;
}

static void
test_slinked_list_length(void)
{
    struct single_linked_list *head;
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
        head = slinked_list_generate(data, len);

        if (len != slinked_list_length(head)) {
            is_passed = false;
        }

        free_ds(data);
        slinked_list_destroy(&head);
    }

    head = slinked_list_create();
    if (1u != slinked_list_length(head)) {
        is_passed = false;
    }
    slinked_list_destroy(&head);

    if (0u != slinked_list_length(NULL)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(slinked_list_length), is_passed);
    return;
}

static void
test_slinked_list_node_get_by_index(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = slinked_list_node_get_by_index(head, 0u);
    if (head != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_node_get_by_index(head, -1);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_node_get_by_index(NULL, 0u);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_node_get_by_index(head, sizeof(raw) / sizeof(raw[0]));
    if (head != tmp) {
        is_passed = false;
    }

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_node_get_by_index), is_passed);
    return;
}

static void
test_slinked_list_node_exchange(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp_1;
    struct single_linked_list *tmp_2;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp_1 = slinked_list_node_previous(head);
    tmp_2 = head->next;

    slinked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    if (slinked_list_node_previous(head) != tmp_2 || head->next != tmp_1) {
        is_passed = false;
    }

    tmp_1 = head->next;
    tmp_2 = slinked_list_node_previous(head);
    slinked_list_node_exchange(head, head);
    if (tmp_1 != head->next || tmp_2 != slinked_list_node_previous(head)) {
        is_passed = false;
    }

    slinked_list_node_exchange(head, NULL);
    if (tmp_1 != head->next || tmp_2 != slinked_list_node_previous(head)) {
        is_passed = false;
    }

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_node_exchange), is_passed);
    return;
}

static void
test_slinked_list_contains_p(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    if (true != slinked_list_contains_p(head, tmp)) {
        is_passed = false;
    }

    if (false != slinked_list_contains_p(NULL, tmp)) {
        is_passed = false;
    }

    tmp = slinked_list_create();
    if (false != slinked_list_contains_p(head, tmp)) {
        is_passed = false;
    }
    slinked_list_destroy(&tmp);

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_contains_p), is_passed);
    return;
}

static void
test_slinked_list_serialize(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
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
        head = slinked_list_generate(raw, len);

        slinked_list_serialize(head);
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
        slinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(slinked_list_serialize), is_passed);
    return;
}

static void
test_slinked_list_node_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = slinked_list_node_previous(head);

    if (tmp != slinked_list_node_remove(head)) {
        is_passed = false;
    }

    if (tmp != prev->next) {
        is_passed = false;
    }

    slinked_list_destroy(&tmp);

    tmp = slinked_list_create();
    if (NULL != slinked_list_node_remove(tmp)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(slinked_list_remove_node), is_passed);
    return;
}

static void
test_slinked_list_node_lazy_remove(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = slinked_list_node_previous(head);

    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    slinked_list_node_lazy_remove(head);
    if (tmp != head->next && prev != slinked_list_node_previous(head)) {
        is_passed = false;
    }

    if (prev->next != tmp && slinked_list_node_previous(tmp) != prev) {
        is_passed = false;
    }

    /* Need to free the lazy node independently. */
    free_ds(head);
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_node_lazy_remove), is_passed);
    return;
}

static void
test_slinker_list_iterate(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));

    slinked_list_iterate(head, &slinked_list_iterate_handler);

    tmp = head;
    do {
        if (tmp->id != 0xDAEDu) {
            is_passed = false;
        }
        tmp = tmp->next;
    } while (tmp != head);

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_iterate), is_passed);
    return;
}
