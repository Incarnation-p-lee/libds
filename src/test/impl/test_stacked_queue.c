static void
test_stacked_queue_create(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    if (queue->enter->space.dim != queue->leave->space.dim) {
        is_passed = false;
    }

    if (queue->enter->space.dim != queue->dim &&
        0u == queue->sid) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_create), is_passed);
    return;
}

static void
test_stacked_queue_destroy(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    stacked_queue_destroy(&queue);
    if (NULL != queue) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(stacked_queue_destroy), is_passed);
    return;
}

static void
test_stacked_queue_space_expand(void)
{
    bool is_passed;
    struct stacked_queue *queue;
    uint32 capacity;
    uint32 extra;

    queue = stacked_queue_create();
    is_passed = true;
    capacity = stacked_queue_capacity(queue);
    extra = 1023;

    stacked_queue_space_expand(queue, extra);
    if (capacity + extra != stacked_queue_capacity(queue)) {
        is_passed = false;
    }

    if (capacity + extra != queue->enter->space.dim
        || capacity + extra != queue->leave->space.dim) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_space_expand), is_passed);
    return;
}

static void
test_stacked_queue_capacity(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    if (0 != stacked_queue_capacity(NULL)) {
        is_passed = false;
    }

    if (queue->dim != stacked_queue_capacity(queue)) {
        is_passed = false;
    }

    stacked_queue_space_expand(queue, 0);
    if (queue->dim != stacked_queue_capacity(queue)) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_capacity), is_passed);
    return;
}

static void
test_stacked_queue_space_rest(void)
{
    bool is_passed;
    struct stacked_queue *queue;
    uint32 capacity;

    queue = stacked_queue_create();
    is_passed = true;
    capacity = stacked_queue_capacity(queue);

    if (0 != stacked_queue_space_rest(NULL)) {
        is_passed = false;
    }

    if (capacity * 2 != stacked_queue_space_rest(queue)) {
        is_passed = false;
    }

    stacked_queue_enter(queue, queue);
    if (capacity * 2 != stacked_queue_space_rest(queue) + 1) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_space_rest), is_passed);
    return;
}

static void
test_stacked_queue_full_p(void)
{
    bool is_passed;
    struct stacked_queue *queue;
    uint32 cnt;
    uint32 capacity;

    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);
    is_passed = true;
    cnt = 0;

    if (!stacked_queue_full_p(NULL)) {
        is_passed = false;
    }

    if (stacked_queue_full_p(queue)) {
        is_passed = false;
    }

    while (!stacked_queue_full_p(queue)) {
        cnt++;
        stacked_queue_enter(queue, queue);
    }

    if (cnt != capacity * 2) {
        is_passed = false;
        printf("cnt %d, capacity %d\n", cnt, capacity);
    }

    if (!stacked_queue_full_p(queue)) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_full_p), is_passed);
    return;
}

static void
test_stacked_queue_empty_p(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    if (!stacked_queue_empty_p(queue)) {
        is_passed = false;
    }

    if (stacked_queue_empty_p(NULL)) {
        is_passed = false;
    }

    stacked_queue_enter(queue, queue);
    if (stacked_queue_empty_p(NULL)) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_empty_p), is_passed);
    return;
}

static void
test_stacked_queue_enter(void)
{
    bool is_passed;
    struct stacked_queue *queue;
    uint32 capacity;

    queue = stacked_queue_create();
    is_passed = true;

    stacked_queue_enter(queue, queue);
    if (queue != stacked_queue_leave(queue)) {
        is_passed = false;
    }

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));
    if (!stacked_queue_full_p(queue)) {
        is_passed = false;
    }

    capacity = stacked_queue_capacity(queue);
    stacked_queue_enter(queue, queue);
    if (stacked_queue_capacity(queue) != capacity * 2 + EXPAND_STACK_SPACE_MIN) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_enter), is_passed);
    return;
}

static void
test_stacked_queue_leave(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));

    do {
        if (queue != stacked_queue_leave(queue)) {
            is_passed = false;
        }
    } while (!stacked_queue_empty_p(queue));

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_leave), is_passed);
    return;
}

static void
test_stacked_queue_cleanup(void)
{
    bool is_passed;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    is_passed = true;

    stacked_queue_enter(queue, queue);
    if (stacked_queue_full_p(queue)) {
        is_passed = false;
    }

    if (stacked_queue_empty_p(queue)) {
        is_passed = false;
    }

    stacked_queue_cleanup(queue);
    if (!stacked_queue_empty_p(queue)) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_cleanup), is_passed);
    return;
}

static void
test_stacked_queue_iterate(void)
{
    bool is_passed;
    struct stacked_queue *queue;
    uint32 tmp;

    queue = stacked_queue_create();
    is_passed = true;
    tmp = 0;

    do {
        stacked_queue_enter(queue, &tmp);
    } while (!stacked_queue_full_p(queue));

    stacked_queue_iterate(queue, queue_iterate_handler);
    if (tmp != stacked_queue_capacity(queue) * 2) {
        is_passed = false;
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_iterate), is_passed);
    return;
}

