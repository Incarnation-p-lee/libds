static inline struct single_linked_list *
unit_test_single_linked_list_sample(uint32 range, uint32 node_count)
{
    struct single_linked_list *retval;
    struct single_linked_list *tmp;
    uint32 sid;
    uint32 i;

    retval = single_linked_list_create();
    single_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = single_linked_list_create();
        single_linked_list_node_initial(tmp, tmp, sid);
        single_linked_list_node_insert_after(retval, tmp);
        i++;
    }

    return retval;
}

static void
unit_test_single_linked_list_struct_field(void)
{
    uint32 sid;
    bool pass;
    struct single_linked_list *tmp;

    sid = 0xfade;
    pass = true;
    tmp = single_linked_list_create();

    single_linked_list_node_sid_set(tmp, sid);
    RESULT_CHECK_uint32(sid, single_linked_list_node_sid(tmp), &pass);

    single_linked_list_node_val_set(tmp, &sid);
    RESULT_CHECK_pointer(&sid, single_linked_list_node_val(tmp), &pass);

    single_linked_list_node_next_set(tmp, tmp);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);

    single_linked_list_destroy(&tmp);
    unit_test_result_print(SYM_2_STR(single_linked_list_struct_field), pass);
}

static void
unit_test_single_linked_list_create(void)
{
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    tmp = single_linked_list_create();

    single_linked_list_destroy(&tmp);

    tmp = single_linked_list_create();
    RESULT_CHECK_uint32(0x0u, single_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    unit_test_result_print(SYM_2_STR(single_linked_list_create), pass);
}

static void
unit_test_single_linked_list_node_create(void)
{
    bool pass;
    uint32 sid;
    struct single_linked_list *tmp;

    pass = true;
    sid = 0xdeadu;

    tmp = single_linked_list_node_create(&sid, sid);
    single_linked_list_destroy(&tmp);

    tmp = single_linked_list_node_create(&sid, sid);
    RESULT_CHECK_uint32(sid, single_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(&sid, single_linked_list_node_val(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_create), pass);
}

static void
unit_test_single_linked_list_node_initial(void)
{
    bool pass;
    uint32 sid;
    struct single_linked_list *tmp;

    pass = true;
    sid = 0xfadeu;

    tmp = NULL;
    single_linked_list_node_initial(tmp, &pass, sid);
    RESULT_CHECK_pointer(tmp, NULL, &pass);

    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_node_initial(tmp, &pass, sid);

    RESULT_CHECK_uint32(sid, single_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);
    RESULT_CHECK_pointer(&pass, single_linked_list_node_val(tmp), &pass);

    single_linked_list_destroy(&tmp);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_initial), pass);
}

static void
unit_test_single_linked_list_initial(void)
{
    bool pass;
    struct single_linked_list *tmp;

    pass = true;
    tmp = malloc_ds(sizeof(*tmp));
    single_linked_list_initial(tmp);

    RESULT_CHECK_uint32(0x0u, single_linked_list_node_sid(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_next(tmp), &pass);
    RESULT_CHECK_pointer(tmp, single_linked_list_node_previous(tmp), &pass);

    single_linked_list_destroy(&tmp);
    unit_test_result_print(SYM_2_STR(single_linked_list_initial), pass);
}

static void
unit_test_single_linked_list_node_append(void)
{
    struct single_linked_list *head;
    struct single_linked_list *next;
    struct single_linked_list *append;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0xa1A2E, 0x9213D);
    single_linked_list_node_append(NULL, &pass);

    next = single_linked_list_node_next(head);
    single_linked_list_node_append(head, &pass);
    append = single_linked_list_node_next(head);

    RESULT_CHECK_pointer(&pass, single_linked_list_node_val(append), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_node_previous(append), &pass);
    RESULT_CHECK_pointer(next, single_linked_list_node_next(append), &pass);
    RESULT_CHECK_pointer(append, single_linked_list_node_previous(next), &pass);

    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_append), pass);
}

static void
unit_test_single_linked_list_node_previous(void)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x9AB, 0xBF3);
    single_linked_list_node_append(head, &pass);
    RESULT_CHECK_pointer(NULL, single_linked_list_node_previous(NULL), &pass);

    prev = single_linked_list_node_previous(head);
    RESULT_CHECK_pointer(prev, single_linked_list_node_previous(head), &pass);

    tmp = single_linked_list_node_next(head);
    single_linked_list_node_next_set(head, NULL);
    prev = single_linked_list_node_previous(head);
    RESULT_CHECK_pointer(NULL, prev, &pass);
    single_linked_list_node_next_set(head, tmp);

    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_previous), pass);
}

static void
unit_test_single_linked_list_node_insert_before(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *prev;
    struct single_linked_list *copy;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0xa26, 0x239);
    single_linked_list_node_append(head, &pass);

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

    node = single_linked_list_create();
    single_linked_list_node_insert_before(head, node);

    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_insert_before), pass);
}

static void
unit_test_single_linked_list_node_insert_after(void)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    struct single_linked_list *next;
    struct single_linked_list *copy;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0xF18AB, 0x82E9C);
    single_linked_list_node_append(head, &pass);

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

    next = single_linked_list_node_next(head);
    single_linked_list_node_insert_after(head, node);
    RESULT_CHECK_pointer(node, single_linked_list_node_next(head), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_node_previous(node), &pass);
    RESULT_CHECK_pointer(next, single_linked_list_node_next(node), &pass);
    RESULT_CHECK_pointer(node, single_linked_list_node_previous(next), &pass);

    node = single_linked_list_create();
    single_linked_list_node_insert_after(head, node);

    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_insert_after), pass);
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
        head = unit_test_single_linked_list_sample(0x816FA, len);

        single_linked_list_destroy(&head);
        RESULT_CHECK_pointer(NULL, head, &pass);
    }

    head = single_linked_list_create();
    single_linked_list_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    unit_test_result_print(SYM_2_STR(single_linked_list_destroy), pass);
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
        head = unit_test_single_linked_list_sample(0xE2AE8, len);

        RESULT_CHECK_uint32(len, single_linked_list_length(head), &pass);
        single_linked_list_destroy(&head);
    }

    head = single_linked_list_create();
    RESULT_CHECK_uint32(0x1u, single_linked_list_length(head), &pass);
    single_linked_list_destroy(&head);
    RESULT_CHECK_uint32(0x0u, single_linked_list_length(NULL), &pass);

    unit_test_result_print(SYM_2_STR(single_linked_list_length), pass);
}

static void
unit_test_single_linked_list_node_by_index(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    uint32 len;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0xFAA, 0x9A8);
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
    unit_test_result_print(SYM_2_STR(single_linked_list_node_by_index), pass);
}

static void
unit_test_single_linked_list_contains_p(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x1DD2, 0x2AE2);
    tmp = single_linked_list_node_next(head);

    RESULT_CHECK_bool(true, single_linked_list_contains_p(head, tmp), &pass);
    RESULT_CHECK_bool(false, single_linked_list_contains_p(NULL, tmp), &pass);

    tmp = single_linked_list_create();
    RESULT_CHECK_bool(false, single_linked_list_contains_p(head, tmp), &pass);

    single_linked_list_destroy(&tmp);
    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_contains_p), pass);
}

static void
unit_test_single_linked_list_serialize(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};
    uint32 *iter;
    uint32 len;
    uint32 index;

    pass = true;
    iter = sizes;
    while (iter < sizes + array_sizeof(sizes)) {
        len = *iter++;
        head = unit_test_single_linked_list_sample(0x9E2, len);
        single_linked_list_serialize(head);

        tmp = head;
        index = 0u;
        do {
            RESULT_CHECK_uint32(index, single_linked_list_node_sid(tmp), &pass);
            index++;
            tmp = single_linked_list_node_next(tmp);
        } while (tmp != head);

        single_linked_list_destroy(&head);
    }

    unit_test_result_print(SYM_2_STR(single_linked_list_serialize), pass);
}

static void
unit_test_single_linked_list_node_copy(void)
{
    uint32 sid;
    bool pass;
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    sid = 0xbedu;
    pass = true;
    head = single_linked_list_node_create(&pass, sid);

    single_linked_list_node_copy(NULL);

    tmp = single_linked_list_node_copy(head);
    RESULT_CHECK_single_linked_list_node(tmp, head, &pass);
    single_linked_list_node_initial(tmp, NULL, 0x0u);

    single_linked_list_destroy(&tmp);
    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_copy), pass);
}

static void
unit_test_single_linked_list_node_remove(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    struct single_linked_list ref;
    bool pass;

    single_linked_list_node_remove(NULL);

    pass = true;
    head = single_linked_list_create();
    ref.sid = head->sid;
    ref.val = head->val;

    tmp = single_linked_list_node_remove(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);
    RESULT_CHECK_uint32(ref.sid, tmp->sid, &pass);
    RESULT_CHECK_pointer(ref.val, tmp->val, &pass);
    single_linked_list_destroy(&tmp);

    head = unit_test_single_linked_list_sample(0x32, 0xF);

    ref.sid = head->sid;
    ref.val = head->val;
    tmp = single_linked_list_node_remove(&head);
    RESULT_CHECK_uint32(ref.sid, tmp->sid, &pass);
    RESULT_CHECK_pointer(ref.val, tmp->val, &pass);

    single_linked_list_destroy(&tmp);
    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_node_remove), pass);
}

static void
unit_test_single_linked_list_node_remove_and_destroy(void)
{
    struct single_linked_list *head;
    bool pass;

    single_linked_list_node_remove(NULL);

    pass = true;
    head = unit_test_single_linked_list_sample(0x31e2, 0x28ed);

    single_linked_list_node_remove_and_destroy(&head);
    single_linked_list_destroy(&head);

    head = single_linked_list_create();
    single_linked_list_node_remove_and_destroy(&head);
    RESULT_CHECK_pointer(NULL, head, &pass);

    unit_test_result_print(SYM_2_STR(single_linked_list_node_remove_and_destroy), pass);
}

static void
unit_test_single_linked_list_iterate(void)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;
    bool pass;

    pass = true;
    head = unit_test_single_linked_list_sample(0x1E2, 0x282);

    single_linked_list_iterate(head, &linked_list_iterate_handler);
    single_linked_list_iterate(NULL, &linked_list_iterate_handler);

    tmp = head;
    do {
        RESULT_CHECK_uint32(0xdeadu, single_linked_list_node_sid(tmp), &pass);
        tmp = single_linked_list_node_next(tmp);
    } while (tmp != head);

    single_linked_list_iterate(head, &linked_list_iterate_handler);

    single_linked_list_destroy(&head);
    unit_test_result_print(SYM_2_STR(single_linked_list_iterate), pass);
}

static void
unit_test_single_linked_list_merge(void)
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

    RESULT_CHECK_pointer(NULL, single_linked_list_merge(NULL, NULL), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_merge(head, NULL), &pass);
    RESULT_CHECK_pointer(head, single_linked_list_merge(NULL, head), &pass);

    head = single_linked_list_merge(head, head_n);
    RESULT_CHECK_uint32(0x6u, single_linked_list_length(head), &pass);

    head = single_linked_list_merge(head, head_n);

    single_linked_list_destroy(&head);
    single_linked_list_destroy(&head_n);
    unit_test_result_print(SYM_2_STR(single_linked_list_merge), pass);
}

