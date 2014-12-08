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
    struct doubly_end_queue_list *tmp;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_head_enter(queue, queue);
    tmp = queue->tail;
    if (doubly_end_queue_is_empty(queue) || tmp != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_head_enter(queue, queue);
    if (2u != doubly_end_queue_length(queue) || tmp != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_head_enter), is_passed);
    return;
}

static void
test_doubly_end_queue_tail_enter(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;
    struct doubly_end_queue_list *tmp;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_tail_enter(queue, queue);
    tmp = queue->head;
    if (doubly_end_queue_is_empty(queue) || tmp != queue->head) {
        is_passed = false;
    }

    doubly_end_queue_tail_enter(queue, queue);
    if (2u != doubly_end_queue_length(queue) || tmp != queue->head) {
        printf("BBB\n");
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_tail_enter), is_passed);
    return;
}

static void
test_doubly_end_queue_head_leave(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;
    struct doubly_end_queue_list *tmp;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_head_enter(queue, queue);
    tmp = queue->tail;
    if (doubly_end_queue_is_empty(queue)) {
        is_passed = false;
    }

    if (queue != doubly_end_queue_head_leave(queue)) {
        is_passed = false;
    }

    if (tmp != queue->head || tmp != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_head_leave), is_passed);
    return;
}

static void
test_doubly_end_queue_tail_leave(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;
    struct doubly_end_queue_list *tmp;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_tail_enter(queue, queue);
    doubly_end_queue_tail_enter(queue, queue);
    tmp = queue->head;
    if (doubly_end_queue_is_empty(queue)) {
        is_passed = false;
    }

    if (queue != doubly_end_queue_tail_leave(queue)) {
        is_passed = false;
    }

    if (tmp != queue->head || tmp != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_tail_leave), is_passed);
    return;
}


static void
test_doubly_end_queue_cleanup(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();
    is_passed = true;

    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_tail_enter(queue, queue);
    doubly_end_queue_cleanup(queue);
    if (NULL != queue->head || NULL != queue->tail) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_create), is_passed);
    return;
}

static void
test_doubly_end_queue_iterate(void)
{
    bool is_passed;
    struct doubly_end_queue *queue;
    uint32 tmp;
    uint32 cnt;

    queue = doubly_end_queue_create();
    is_passed = true;
    tmp = 0;
    cnt = 1023;

    while (cnt) {
        doubly_end_queue_head_enter(queue, &tmp);
        cnt--;
    }

    doubly_end_queue_iterate(queue, queue_iterate_handler);
    if (tmp != doubly_end_queue_length(queue)) {
        is_passed = false;
    }

    doubly_end_queue_destroy(&queue);

    test_result_print(SYM_2_STR(doubly_end_queue_iterate), is_passed);
    return;
}

