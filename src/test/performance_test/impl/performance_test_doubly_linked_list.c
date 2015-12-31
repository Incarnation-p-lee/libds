static void
performance_test_doubly_linked_list_create(uint32 count)
{
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_create();
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(doubly_linked_list_create);
}

static void
performance_test_doubly_linked_list_initial(uint32 count)
{
    struct doubly_linked_list *tmp;

    tmp = doubly_linked_list_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_initial(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(doubly_linked_list_initial);
}

static void
performance_test_doubly_linked_list_node_create(uint32 count)
{
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_node_create(&count);
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(doubly_linked_list_node_create);
}

static void
performance_test_doubly_linked_list_insert_before(uint32 count)
{
    struct doubly_linked_list *head;

    count = count >> 6;
    count = 0u == count ? 1000 : count;
    head = test_doubly_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_insert_before(head, &head);
        doubly_linked_list_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_insert_before);
}

static void
performance_test_doubly_linked_list_insert_after(uint32 count)
{
    struct doubly_linked_list *head;

    count = count >> 6;
    count = 0u == count ? 1000 : count;
    head = test_doubly_linked_list_sample(0x722, 0x342);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_insert_after(head, &head);
        doubly_linked_list_remove_and_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_insert_after);
}

static void
performance_test_doubly_linked_list_destroy(uint32 count)
{
    struct doubly_linked_list *head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_doubly_linked_list_sample(0x22, 0x9);
        doubly_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(doubly_linked_list_destroy);
}

static void
performance_test_doubly_linked_list_length(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xe3e, 0x9a7);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_length(head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_length);
}

static void
performance_test_doubly_linked_list_node_by_index(uint32 count)
{
    struct doubly_linked_list *head;
    uint32 length;

    head = test_doubly_linked_list_sample(0xfde, 0x4af);
    length = doubly_linked_list_length(head);
    length /= 2;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_node_by_index(head, length);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_node_by_index);
}

static void
performance_test_doubly_linked_list_contains_p(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = test_doubly_linked_list_sample(0xfde, 0x4af);
    tmp = head;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_contains_p(head, tmp);
        tmp = doubly_linked_list_next(tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_contains_p);
}

static void
performance_test_doubly_linked_list_node_copy(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    head = doubly_linked_list_node_create(&count);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = doubly_linked_list_node_copy(head);
        doubly_linked_list_next_set(tmp, tmp);
        doubly_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_node_copy);
}

static void
performance_test_doubly_linked_list_remove(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *removed;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        removed = doubly_linked_list_remove(&head);
        doubly_linked_list_insert_before(head, &head);
        doubly_linked_list_destroy(&removed);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_remove);
}

static void
performance_test_doubly_linked_list_remove_and_destroy(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_remove_and_destroy(&head);
        doubly_linked_list_insert_after(head, &head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_remove_and_destroy);
}

static void
performance_test_doubly_linked_list_iterate(uint32 count)
{
    struct doubly_linked_list *head;

    head = test_doubly_linked_list_sample(0xe0d, 0x493);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_linked_list_iterate(head, &linked_list_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_linked_list_destroy(&head);
    PERFORMANCE_TEST_RESULT(doubly_linked_list_iterate);
}

static void
performance_test_doubly_linked_list_merge(uint32 count)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        head = test_doubly_linked_list_sample(0xe0d, 0xd);
        tmp = test_doubly_linked_list_sample(0xfe0d, 0xf);
        doubly_linked_list_merge(head, tmp);
        doubly_linked_list_destroy(&tmp);
        doubly_linked_list_destroy(&head);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(doubly_linked_list_merge);
}

