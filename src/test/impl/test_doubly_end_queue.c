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

    if (NULL != queue->front || NULL != queue->tail) {
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
    doubly_end_queue_front_enter(queue, queue);
    doubly_end_queue_destroy(&queue);
    if (NULL != queue) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(doubly_end_queue_destroy), is_passed);
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
