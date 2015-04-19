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
        single_linked_list_node_insert_before(retval, tmp);
        i++;
    }

    return retval;
}


static void
unit_test_single_linked_list_create(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = single_linked_list_create();
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp
            && single_linked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_create), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_create(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = single_linked_list_node_create(&is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp
            && tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_node_create), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_initial(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_node_initial(tmp, &is_passed, 0xdeadu);
    if (tmp) {
        if (tmp->id == 0xdeadu && tmp->next == tmp && tmp->val == &is_passed
            && single_linked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_node_initial), is_passed);
    return;
}

static void
unit_test_single_linked_list_initial(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_initial(tmp);
    if (tmp) {
        if (tmp->id == 0u && tmp->next == tmp
            && single_linked_list_node_previous(tmp) == tmp) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_initial), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_set_val(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_node_initial(tmp, NULL, 0u);
    single_linked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (tmp->val == &is_passed) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_node_set_val), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_get_val(void)
{
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = false;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_node_initial(tmp, NULL, 0u);
    single_linked_list_node_set_val(tmp, &is_passed);
    if (tmp) {
        if (&is_passed == single_linked_list_node_get_val(tmp)) {
            is_passed = true;
        }
    }
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_node_get_val), is_passed);
    return;
}

static void
unit_test_single_linked_list_generate(void)
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
        head = single_linked_list_generate(data, len);

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
        single_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(single_linked_list_generate), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_append(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    struct single_linked_list *append;
    bool is_passed;
    uint32 tmp = 0xAu;

    head = unit_test_single_linked_list_sample(0x1A2E, 0x213D);
    is_passed = false;
    next = head->next;

    single_linked_list_node_append(head, tmp);
    append = head->next;
    if (append->id == tmp && append->next == next
        && single_linked_list_node_previous(append) == head
        && single_linked_list_node_previous(next) == append) {
        is_passed = true;
    }
    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_node_append), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_next(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    bool is_passed;

    is_passed = false;
    head = unit_test_single_linked_list_sample(0x2D34, 0x3A89);
    single_linked_list_node_append(head, 0xDEADu);

    next = single_linked_list_node_next(head);
    if (next == head->next) {
        is_passed = true;
    }
    single_linked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->next = NULL;
    next = single_linked_list_node_next(head);
    if (NULL != next) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(single_linked_list_node_next), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_previous(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    bool is_passed;

    is_passed = false;
    head = unit_test_single_linked_list_sample(0x19AB, 0x2BF3);
    single_linked_list_node_append(head, 0xDEADu);

    prev = single_linked_list_node_previous(head);
    if (prev == single_linked_list_node_previous(head)) {
        is_passed = true;
    }
    single_linked_list_destroy(&head);

    head = malloc_ds(sizeof(*head));
    head->next = NULL;
    prev = single_linked_list_node_previous(head);
    if (NULL != prev) {
        is_passed = false;
    }
    free_ds(head);

    test_result_print(SYM_2_STR(single_linked_list_node_previous), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_insert_before(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *prev;
    bool is_passed;
    uint32 mark;

    is_passed = false;
    mark = 0xDEADu;
    head = unit_test_single_linked_list_sample(0x1CE5, 0x37A8);
    single_linked_list_node_append(head, mark);

    prev = single_linked_list_node_previous(head);
    node = single_linked_list_create();
    single_linked_list_node_insert_before(head, node);
    if (single_linked_list_node_previous(head) == node && node->next == head
        && single_linked_list_node_previous(node) == prev && prev->next == node) {
        is_passed = true;
    }
    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_node_insert_before), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_insert_after(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *next;
    bool is_passed;
    uint32 mark;

    is_passed = false;
    mark = 0xDEADu;
    head = unit_test_single_linked_list_sample(0x18AB, 0x2E9C);
    single_linked_list_node_append(head, mark);

    next = head->next;
    node = single_linked_list_create();
    single_linked_list_node_insert_after(head, node);
    if (head->next == node && single_linked_list_node_previous(node) == head
        && node->next == next && single_linked_list_node_previous(next) == node) {
        is_passed = true;
    }
    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_node_insert_after), is_passed);
    return;
}

static void
unit_test_single_linked_list_destroy(void)
{
    struct single_linked_list *head;
    bool is_passed;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(len, 0x16FA);

        single_linked_list_destroy(&head);
        if (NULL != head) {
            is_passed = false;
        }
    }

    head = single_linked_list_create();
    single_linked_list_destroy(&head);
    if (NULL != head) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(single_linked_list_destroy), is_passed);
    return;
}

static void
unit_test_single_linked_list_length(void)
{
    struct single_linked_list *head;
    bool is_passed;
    uint32 *iter;
    uint32 len;
    uint32 sizes[] = {1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000,};

    iter = sizes;
    is_passed = true;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(0x2AE8, len);

        if (len != single_linked_list_length(head)) {
            is_passed = false;
        }

        single_linked_list_destroy(&head);
    }

    head = single_linked_list_create();
    if (1u != single_linked_list_length(head)) {
        is_passed = false;
    }
    single_linked_list_destroy(&head);

    if (0u != single_linked_list_length(NULL)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(single_linked_list_length), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_get_by_index(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x18FA, 0x23A2);
    tmp = single_linked_list_node_get_by_index(head, 0u);
    if (head != tmp) {
        is_passed = false;
    }

    tmp = single_linked_list_node_get_by_index(head, -1);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = single_linked_list_node_get_by_index(NULL, 0u);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = single_linked_list_node_get_by_index(head,
        single_linked_list_length(head) - 1);
    if (head != tmp->next) {
        is_passed = false;
    }

    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_node_get_by_index), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_exchange(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp_1;
    struct single_linked_list *tmp_2;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x14A2, 0x2E1D);
    tmp_1 = single_linked_list_node_previous(head);
    tmp_2 = head->next;

    single_linked_list_node_exchange(tmp_1, tmp_2);
    /* ->tmp_1->head->tmp_2-> =>
       ->tmp_2->head->tmp_1->    */
    if (single_linked_list_node_previous(head) != tmp_2 || head->next != tmp_1) {
        is_passed = false;
    }

    tmp_1 = head->next;
    tmp_2 = single_linked_list_node_previous(head);
    single_linked_list_node_exchange(head, head);
    if (tmp_1 != head->next || tmp_2 != single_linked_list_node_previous(head)) {
        is_passed = false;
    }

    single_linked_list_node_exchange(head, NULL);
    if (tmp_1 != head->next || tmp_2 != single_linked_list_node_previous(head)) {
        is_passed = false;
    }

    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_node_exchange), is_passed);
    return;
}

static void
unit_test_single_linked_list_contains_p(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x1DD2, 0x28AE);
    tmp = head->next;
    if (true != single_linked_list_contains_p(head, tmp)) {
        is_passed = false;
    }

    if (false != single_linked_list_contains_p(NULL, tmp)) {
        is_passed = false;
    }

    tmp = single_linked_list_create();
    if (false != single_linked_list_contains_p(head, tmp)) {
        is_passed = false;
    }
    single_linked_list_destroy(&tmp);

    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_contains_p), is_passed);
    return;
}

static void
unit_test_single_linked_list_serialize(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;
    uint32 sizes[] = {1, 10, 100, 1000, 10000, 100000,};
    uint32 *iter;
    uint32 len;
    uint32 index;

    is_passed = true;
    iter = sizes;
    while (iter < sizes + sizeof(sizes) / sizeof(sizes[0])) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(len, 0x29E2);

        single_linked_list_serialize(head);
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

        single_linked_list_destroy(&head);
    }

    test_result_print(SYM_2_STR(single_linked_list_serialize), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_remove(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x31E2, 0x28ED);
    tmp = head->next;
    prev = single_linked_list_node_previous(head);

    if (tmp != single_linked_list_node_remove(head)) {
        is_passed = false;
    }

    if (tmp != prev->next) {
        is_passed = false;
    }

    single_linked_list_destroy(&tmp);

    tmp = single_linked_list_create();
    if (NULL != single_linked_list_node_remove(tmp)) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(single_linked_list_remove_node), is_passed);
    return;
}

static void
unit_test_single_linked_list_node_lazy_remove(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x1AEE, 0x23EA);
    tmp = head->next;
    prev = single_linked_list_node_previous(head);

    /* ->head->tmp->node-> =>
       ->head->node->
          tmp->node           */
    single_linked_list_node_lazy_remove(head);
    if (tmp != head->next && prev != single_linked_list_node_previous(head)) {
        is_passed = false;
    }

    if (prev->next != tmp && single_linked_list_node_previous(tmp) != prev) {
        is_passed = false;
    }

    /* Need to free the lazy node independently. */
    free_ds(head);
    single_linked_list_destroy(&tmp);

    test_result_print(SYM_2_STR(single_linked_list_node_lazy_remove), is_passed);
    return;
}

static void
unit_test_single_linked_list_iterate(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
    head = unit_test_single_linked_list_sample(0x24E2, 0x1F82);

    single_linked_list_iterate(head, &linked_list_iterate_handler);

    tmp = head;
    do {
        if (tmp->id != 0xDEADu) {
            is_passed = false;
        }
        tmp = tmp->next;
    } while (tmp != head);

    single_linked_list_destroy(&head);

    test_result_print(SYM_2_STR(single_linked_list_iterate), is_passed);
    return;
}

static void
unit_test_single_linked_list_join(void)
{
    uint32 raw[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF,};
    struct single_linked_list *head;
    struct single_linked_list *head_n;
    struct single_linked_list *tmp;
    bool is_passed;

    is_passed = true;
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

    if (NULL != single_linked_list_join(NULL, NULL)) {
        is_passed = false;
    }

    if (head != single_linked_list_join(head, NULL)) {
        is_passed = false;
    }

    if (head != single_linked_list_join(NULL, head)) {
        is_passed = false;
    }

    head = single_linked_list_join(head, head_n);
    if (0x6u != single_linked_list_length(head)) {
        is_passed = false;
    }

    single_linked_list_destroy(&head);
    single_linked_list_destroy(&head_n);

    test_result_print(SYM_2_STR(single_linked_list_join), is_passed);
    return;
}
