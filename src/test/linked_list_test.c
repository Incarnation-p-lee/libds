void
linked_list_unit_test(void)
{
    doubly_linked_list_unit_test();
    return;
}

static void
doubly_linked_list_unit_test(void)
{
    void (*all_tests[])(void) = {
#if 1
        &test_dlinked_list_initial,
        &test_dlinked_list_generate,
        &test_dlinked_list_append_node,
        &test_dlinked_list_next_node,
        &test_dlinked_list_previous_node,
        &test_dlinked_list_insert_before,
        &test_dlinked_list_insert_after,
        &test_dlinked_list_destroy,
        &test_dlinked_list_length,
        &test_dlinked_list_get_node_by_index,
        &test_dlinked_list_exchange_node,
        &test_dlinked_list_is_contains,
        &test_dlinked_list_serialize,
        &test_dlinked_list_remove_node,
        &test_dlinked_list_lazy_remove_node,
#else
#endif
    };
    register void (**iter)(void);

    fprintf(stdout, "\n\n  >> Doubly Linked List Unit Test <<\n\n");
    iter = all_tests;
    while (iter < all_tests + sizeof(all_tests) / sizeof(all_tests[0])) {
        (*iter++)();
    }

    fprintf(stdout, "  >> Test Finished.\n\n");
    return;
}

static void
test_dlinked_list_initial(void)
{
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = dlinked_list_initial();
    if (tmp) {
        if (tmp->index == 0 && tmp->next == tmp && tmp->previous == tmp) {
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
        head = dlinked_list_generate(data, len);

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
        dlinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(dlinked_list_generate), is_passed);
    return;
}

static void
test_dlinked_list_append_node(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    struct doubly_linked_list *append;
    bool is_passed;
    int tmp = 0xA;

    head = dlinked_list_initial();
    is_passed = false;
    next = head->next;

    dlinked_list_append_node(head, tmp);
    append = head->next;
    if (append->index == tmp && append->previous == next
        && next->previous == append && append->next == next) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_append_node), is_passed);
    return;
}

static void
test_dlinked_list_next_node(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *next;
    bool is_passed;

    is_passed = false;
    head = dlinked_list_initial();
    dlinked_list_append_node(head, 0xDEAD);

    next = dlinked_list_next_node(head);
    if (next == head->next) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    head = (struct doubly_linked_list *)malloc_ds(sizeof(*head));
    head->next = NULL;
    next = dlinked_list_next_node(head);
    if (NULL != next) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(dlinked_list_next_node), is_passed);
    return;
}

static void
test_dlinked_list_previous_node(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    bool is_passed;

    is_passed = false;
    head = dlinked_list_initial();
    dlinked_list_append_node(head, 0xDEAD);

    prev = dlinked_list_previous_node(head);
    if (prev == head->previous) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    head = (struct doubly_linked_list *)malloc_ds(sizeof(*head));
    head->previous = NULL;
    prev = dlinked_list_previous_node(head);
    if (NULL != prev) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(dlinked_list_previous_node), is_passed);
    return;
}

static void
test_dlinked_list_insert_before(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *prev;
    bool is_passed;
    int mark;

    is_passed = false;
    mark = 0xDEAD;
    head = dlinked_list_initial();
    dlinked_list_append_node(head, mark);

    prev = head->previous;
    node = dlinked_list_initial();
    dlinked_list_insert_before(head, node);
    if (head->previous == node && node->next == head
        && node->previous == prev && prev->next == node) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_insert_before), is_passed);
    return;
}

static void
test_dlinked_list_insert_after(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *node;
    struct doubly_linked_list *next;
    bool is_passed;
    int mark;

    is_passed = false;
    mark = 0xDEAD;
    head = dlinked_list_initial();
    dlinked_list_append_node(head, mark);

    next = head->next;
    node = dlinked_list_initial();
    dlinked_list_insert_after(head, node);
    if (head->next == node && node->previous == head
        && node->next == next && next->previous == node) {
        is_passed = true;
    }
    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_insert_after), is_passed);
    return;
}

static void
test_dlinked_list_destroy(void)
{
    struct doubly_linked_list *head;
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
        head = dlinked_list_generate(data, len);

        free_ds(data);
        dlinked_list_destroy(&head);
        if (NULL != head) {
            is_passed = false;
        }
    }

    head = dlinked_list_initial();
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
    int *data;
    int *iter;
    int len;
    int sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        data = int_array_generate(len);
        head = dlinked_list_generate(data, len);

        if (len != dlinked_list_length(head)) {
            is_passed = false;
        }

        free_ds(data);
        dlinked_list_destroy(&head);
    }

    head = dlinked_list_initial();
    if (1 != dlinked_list_length(head)) {
        is_passed = false;
    }
    dlinked_list_destroy(&head);

    if (0 != dlinked_list_length(NULL)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(dlinked_list_length), is_passed);
    return;
}

static void
test_dlinked_list_get_node_by_index (void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = dlinked_list_get_node_by_index(head, 0);
    if (head != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_get_node_by_index(head, -1);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_get_node_by_index(NULL, 0);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = dlinked_list_get_node_by_index(head, sizeof(raw) / sizeof(raw[0]));
    if (head != tmp) {
        is_passed = false;
    }

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_get_node_by_index), is_passed);
    return;
}

static void
test_dlinked_list_exchange_node(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp_1;
    struct doubly_linked_list *tmp_2;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp_1 = head->previous;
    tmp_2 = head->next;

    dlinked_list_exchange_node(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    if (head->previous != tmp_2 || head->next != tmp_1) {
        is_passed = false;
    }

    tmp_1 = head->next;
    tmp_2 = head->previous;
    dlinked_list_exchange_node(head, head);
    if (tmp_1 != head->next || tmp_2 != head->previous) {
        is_passed = false;
    }

    dlinked_list_exchange_node(head, NULL);
    if (tmp_1 != head->next || tmp_2 != head->previous) {
        is_passed = false;
    }

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_exchange_node), is_passed);
    return;
}

static void
test_dlinked_list_is_contains(void)
{
    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    if (true != dlinked_list_is_contains(head, tmp)) {
        is_passed = false;
    }

    if (false != dlinked_list_is_contains(NULL, tmp)) {
        is_passed = false;
    }

    tmp = dlinked_list_initial();
    if (false != dlinked_list_is_contains(head, tmp)) {
        is_passed = false;
    }
    dlinked_list_destroy(&tmp);

    dlinked_list_destroy(&head);

    test_result_print(SYM_2_STR(dlinked_list_is_contains), is_passed);
    return;
}

static void
test_dlinked_list_serialize(void)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;
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
        head = dlinked_list_generate(raw, len);

        dlinked_list_serialize(head);
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
        dlinked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(dlinked_list_serialize), is_passed);
    return;
}

static void
test_dlinked_list_remove_node(void)
{

    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct doubly_linked_list *head;
    struct doubly_linked_list *prev;
    struct doubly_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = dlinked_list_generate(raw, sizeof(raw) / sizeof(raw[0]));
    tmp = head->next;
    prev = head->previous;

    if (tmp != dlinked_list_remove_node(head)) {
        is_passed = false;
    }

    if (tmp != prev->next) {
        is_passed = false;
    }

    dlinked_list_destroy(&tmp);

    tmp = dlinked_list_initial();
    if (NULL != dlinked_list_remove_node(tmp)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(dlinked_list_remove_node), is_passed);
    return;
}

static void
test_dlinked_list_lazy_remove_node(void)
{

    int raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
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
    dlinked_list_lazy_remove_node(head);
    if (tmp != head->next && prev != head->previous) {
        is_passed = false;
    }

    if (prev->next != tmp && tmp->previous != prev) {
        is_passed = false;
    }

    /* Need to free the lazy node independently. */
    free_ds(head);
    dlinked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(dlinked_list_lazy_remove_node), is_passed);
    return;
}


static int *
int_array_generate(int size)
{
    int *raw;
    register int *iter;

    raw = NULL;
    if (size > 0) {
        raw = (int *)malloc_ds(sizeof(*raw) * size);
        if (raw) {
            iter = raw;
            while (iter < raw + size) {
                *iter++ = rand();
            }
        }
    }

    return raw;
}
