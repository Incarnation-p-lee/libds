static void
performance_test_single_linked_list_struct_field(uint32 count)
{
    uint32 sid;
    struct single_linked_list *tmp;

    sid = 0xfade;
    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_sid_set(tmp, sid);
        single_linked_list_node_val_set(tmp, &sid);
        single_linked_list_node_next_set(tmp, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    PERFORMANCE_TEST_RESULT(single_linked_list_struct_field);
}

static void
performance_test_single_linked_list_create(uint32 count)
{
    struct single_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_create();
        single_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(single_linked_list_create);
}

static void
performance_test_single_linked_list_node_create(uint32 count)
{
    struct single_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_node_create(&count, count);
        single_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(single_linked_list_node_create);
}

static void
performance_test_single_linked_list_node_initial(uint32 count)
{
    struct single_linked_list *tmp;

    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_initial(tmp, tmp, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    PERFORMANCE_TEST_RESULT(single_linked_list_node_initial);
}

static void
performance_test_single_linked_list_initial(uint32 count)
{
    struct single_linked_list *tmp;

    tmp = single_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_initial(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&tmp);
    PERFORMANCE_TEST_RESULT(single_linked_list_initial);
}

static void
performance_test_single_linked_list_previous(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *prev;

    head = test_single_linked_list_sample(0x92A, 0x742);
    prev = head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        prev = single_linked_list_previous(prev);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_previous);
}

static void
performance_test_single_linked_list_insert_before(uint32 count)
{
    struct single_linked_list *head;

    count = count >> 6;
    count = 0u == count ? 1000 : count;
    head = test_single_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_insert_before(head, head);
        single_linked_list_node_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_insert_before);
}

static void
performance_test_single_linked_list_insert_after(uint32 count)
{
    struct single_linked_list *head;

    count = count >> 6;
    count = 0 == count ? 1000 : count;
    head = test_single_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_insert_after(head, head);
        single_linked_list_node_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_insert_after);
}

static void
performance_test_single_linked_list_destroy(uint32 count)
{
    struct single_linked_list *head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_single_linked_list_sample(0x22, 0x9);
        single_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(single_linked_list_destroy);
}

static void
performance_test_single_linked_list_length(uint32 count)
{
    struct single_linked_list *head;

    head = test_single_linked_list_sample(0xe3e, 0x9a7);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_length(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_length);
}

static void
performance_test_single_linked_list_node_by_index(uint32 count)
{
    struct single_linked_list *head;
    uint32 length;

    head = test_single_linked_list_sample(0xfde, 0x4af);
    length = single_linked_list_length(head);
    length /= 2;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_by_index(head, length);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_node_by_index);
}

static void
performance_test_single_linked_list_contains_p(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    head = test_single_linked_list_sample(0xfde, 0x4af);
    tmp = head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_contains_p(head, tmp);
        tmp = single_linked_list_node_next(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_contains_p);
}

static void
performance_test_single_linked_list_serialize(uint32 count)
{
    struct single_linked_list *head;

    head = test_single_linked_list_sample(0xf92, 0x434);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_serialize(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_serialize);
}

static void
performance_test_single_linked_list_node_copy(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    head = single_linked_list_node_create(&count, 0u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = single_linked_list_node_copy(head);
        single_linked_list_node_next_set(tmp, tmp);
        single_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_node_copy);
}

static void
performance_test_single_linked_list_node_remove(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *removed;

    head = test_single_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = single_linked_list_node_remove(&head);
        single_linked_list_insert_before(head, head);
        single_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_node_remove);
}

static void
performance_test_single_linked_list_node_remove_and_destroy(uint32 count)
{
    struct single_linked_list *head;

    head = test_single_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_node_remove_and_destroy(&head);
        single_linked_list_insert_after(head, head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_node_remove_and_destroy);
}

static void
performance_test_single_linked_list_iterate(uint32 count)
{
    struct single_linked_list *head;

    head = test_single_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        single_linked_list_iterate(head, &linked_list_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    single_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(single_linked_list_iterate);
}

static void
performance_test_single_linked_list_merge(uint32 count)
{
    struct single_linked_list *head;
    struct single_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_single_linked_list_sample(0xe0d, 0xd);
        tmp = test_single_linked_list_sample(0xfe0d, 0xf);
        single_linked_list_merge(head, tmp);
        single_linked_list_destroy(&tmp);
        single_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(single_linked_list_merge);
}

