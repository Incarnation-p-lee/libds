static void
test_slinked_list_create(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = slinked_list_create();
    if (tmp) {
        if (tmp->index == 0 && tmp->next == tmp
            && slinked_list_previous_node(tmp) == tmp) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_create), is_passed);
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
        if (tmp->index == 0 && tmp->next == tmp
            && slinked_list_previous_node(tmp) == tmp) {
            is_passed = true;
        }
    }
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_initial), is_passed);
    return;
}

static void
test_slinked_list_generate(void)
{
    struct single_linked_list *head;
    bool is_passed;
    int *data;
    int *tmp;
    int *iter;
    int len;
    int sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = int_array_generate(len);
        head = slinked_list_generate(data, len);

        tmp = data;
        while (tmp < data + len) {
            if (*tmp++ != head->index) {
                is_passed = false;
                break;
            }
            head = head->next;
        }
        if (*data != head->index) {
            is_passed = false;
        }
        free_ds(data);
        slinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(slinked_list_generate), is_passed);
    return;
}

static void
test_slinked_list_append_node(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    struct single_linked_list *append;
    bool is_passed;
    int tmp = 0xA;

    head = slinked_list_create();
    is_passed = false;
    next = head->next;

    slinked_list_append_node(head, tmp);
    append = head->next;
    if (append->index == tmp && slinked_list_previous_node(append) == next
        && slinked_list_previous_node(next) == append && append->next == next) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_append_node), is_passed);
    return;
}

static void
test_slinked_list_next_node(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    bool is_passed;

    is_passed = false;
    head = slinked_list_create();
    slinked_list_append_node(head, 0xDEAD);

    next = slinked_list_next_node(head);
    if (next == head->next) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    head = (struct single_linked_list *)malloc_ds(sizeof(*head));
    head->next = NULL;
    next = slinked_list_next_node(head);
    if (NULL != next) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(slinked_list_next_node), is_passed);
    return;
}

static void
test_slinked_list_previous_node(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    bool is_passed;

    is_passed = false;
    head = slinked_list_create();
    slinked_list_append_node(head, 0xDEAD);

    prev = slinked_list_previous_node(head);
    if (prev == slinked_list_previous_node(head)) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    head = (struct single_linked_list *)malloc_ds(sizeof(*head));
    head->next = NULL;
    prev = slinked_list_previous_node(head);
    if (NULL != prev) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(slinked_list_previous_node), is_passed);
    return;
}

static void
test_slinked_list_insert_before(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *prev;
    bool is_passed;
    int mark;

    is_passed = false;
    mark = 0xDEAD;
    head = slinked_list_create();
    slinked_list_append_node(head, mark);

    prev = slinked_list_previous_node(head);
    node = slinked_list_create();
    slinked_list_insert_before(head, node);
    if (slinked_list_previous_node(head) == node && node->next == head
        && slinked_list_previous_node(node) == prev && prev->next == node) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_insert_before), is_passed);
    return;
}

static void
test_slinked_list_insert_after(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *next;
    bool is_passed;
    int mark;

    is_passed = false;
    mark = 0xDEAD;
    head = slinked_list_create();
    slinked_list_append_node(head, mark);

    next = head->next;
    node = slinked_list_create();
    slinked_list_insert_after(head, node);
    if (head->next == node && slinked_list_previous_node(node) == head
        && node->next == next && slinked_list_previous_node(next) == node) {
        is_passed = true;
    }
    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_insert_after), is_passed);
    return;
}

static void
test_slinked_list_destroy(void)
{
    struct single_linked_list *head;
    bool is_passed;
    int *data;
    int *iter;
    int len;
    int sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = int_array_generate(len);
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
    int *data;
    int *iter;
    int len;
    int sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = int_array_generate(len);
        head = slinked_list_generate(data, len);

        if (len != slinked_list_length(head)) {
            is_passed = false;
        }

        free_ds(data);
        slinked_list_destroy(&head);
    }

    head = slinked_list_create();
    if (1 != slinked_list_length(head)) {
        is_passed = false;
    }
    slinked_list_destroy(&head);

    if (0 != slinked_list_length(NULL)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(slinked_list_length), is_passed);
    return;
}

static void
test_slinked_list_get_node_by_index(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = slinked_list_get_node_by_index(head, 0);
    if (head != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_get_node_by_index(head, -1);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_get_node_by_index(NULL, 0);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = slinked_list_get_node_by_index(head, sizeof(raw) / sizeof(raw[0]));
    if (head != tmp) {
        is_passed = false;
    }

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_get_node_by_index), is_passed);
    return;
}

static void
test_slinked_list_exchange_node(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp_1;
    struct single_linked_list *tmp_2;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp_1 = slinked_list_previous_node(head);
    tmp_2 = head->next;

    slinked_list_exchange_node(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    if (slinked_list_previous_node(head) != tmp_2 || head->next != tmp_1) {
        is_passed = false;
    }

    tmp_1 = head->next;
    tmp_2 = slinked_list_previous_node(head);
    slinked_list_exchange_node(head, head);
    if (tmp_1 != head->next || tmp_2 != slinked_list_previous_node(head)) {
        is_passed = false;
    }

    slinked_list_exchange_node(head, NULL);
    if (tmp_1 != head->next || tmp_2 != slinked_list_previous_node(head)) {
        is_passed = false;
    }

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_exchange_node), is_passed);
    return;
}

static void
test_slinked_list_is_contains(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    if (true != slinked_list_is_contains(head, tmp)) {
        is_passed = false;
    }

    if (false != slinked_list_is_contains(NULL, tmp)) {
        is_passed = false;
    }

    tmp = slinked_list_create();
    if (false != slinked_list_is_contains(head, tmp)) {
        is_passed = false;
    }
    slinked_list_destroy(&tmp);

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_is_contains), is_passed);
    return;
}

static void
test_slinked_list_serialize(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;
    int sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    int *iter;
    int *raw;
    int len;
    int index;

    is_passed = true;
    iter = sizes;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        raw = int_array_generate(len);
        head = slinked_list_generate(raw, len);

        slinked_list_serialize(head);
        tmp = head;
        index = 0;
        do {
            if (tmp->index != index) {
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
test_slinked_list_remove_node(void)
{

    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = slinked_list_previous_node(head);

    if (tmp != slinked_list_remove_node(head)) {
        is_passed = false;
    }

    if (tmp != prev->next) {
        is_passed = false;
    }

    slinked_list_destroy(&tmp);

    tmp = slinked_list_create();
    if (NULL != slinked_list_remove_node(tmp)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(slinked_list_remove_node), is_passed);
    return;
}

static void
test_slinked_list_lazy_remove_node(void)
{

    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = slinked_list_previous_node(head);

    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    slinked_list_lazy_remove_node(head);
    if (tmp != head->next && prev != slinked_list_previous_node(head)) {
        is_passed = false;
    }

    if (prev->next != tmp && slinked_list_previous_node(tmp) != prev) {
        is_passed = false;
    }

    /* Need to free the lazy node independently. */
    free_ds(head);
    slinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(slinked_list_lazy_remove_node), is_passed);
    return;
}

static void
test_slinker_list_iterate(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = slinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));

    slinked_list_iterate(head, &slinked_list_iterate_handler);

    tmp = head;
    do {
        if (tmp->index != 0xDAED) {
            is_passed = false;
        }
        tmp = tmp->next;
    } while (tmp != head);

    slinked_list_destroy(&head);

    test_result_print(SYM_2_STR(slinked_list_iterate_node), is_passed);
    return;
}
