static void
test_doubly_end_queue_create(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;

    if (0u != queue->sid) {
        is_passed = false;
    }

    if (NULL != queue->head || NULL != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_create), is_passed);
    return;
}

static void
test_doubly_end_queue_destroy(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;
    doubly_end_queue_destroy(&queue);
    if (NULL != queue) {
        is_passed = false;
    }

    queue = doubly_end_queue_create();
    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_destroy(&queue);
    if (NULL != queue) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(doubly_end_queue_destroy), is_passed);
    return;
}

static void
test_doubly_end_queue_length(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;
    uint32 length;

    queue = doubly_end_queue_create();
    is_passed = true;

    length = doubly_end_queue_length(queue);
    if (0u != length) {
        is_passed = false;
    }

    doubly_end_queue_head_enter(queue, queue);
    length = doubly_end_queue_length(queue);
    if (1u != length) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_length), is_passed);
    return;
}

static void
test_doubly_end_queue_is_empty(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;

    if (doubly_end_queue_is_empty(NULL)) {
        is_passed = false;
    }

    if (!doubly_end_queue_is_empty(queue)) {
        is_passed = false;
    }

    doubly_end_queue_head_enter(queue, queue);
    if (doubly_end_queue_is_empty(queue)) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_is_empty), is_passed);
    return;
}

static void
test_doubly_end_queue_head_enter(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_head_enter(queue, queue);
    if (doubly_end_queue_is_empty(queue)) {
        is_passed = false;
    }

    doubly_end_queue_head_enter(queue, queue);
    if (2u != doubly_end_queue_length(queue)) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_head_enter), is_passed);
    return;
}
/*

static void
test_doubly_end_queue_create(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;


    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_create), is_passed);
    return;
}

*/
