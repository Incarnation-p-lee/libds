static void
test_array_queue_create(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (0u != queue->sid) {
        is_passed = false;
    }

    if (queue->space.rest != queue->space.dim) {
        is_passed = false;
    }

    if (queue->space.base != queue->space.front
        || queue->space.base != queue->space.rear) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}

static void
test_array_queue_destroy(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    array_queue_destroy(&queue);
    if (queue != NULL) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(array_queue_destroy), is_passed);
    return;
}

static void
test_array_queue_expand_space(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;
    uint32 rest;
    uint32 extra;

    queue = array_queue_create();
    is_passed = true;
    capacity = array_queue_capacity(queue);
    rest = array_queue_rest_space(queue);
    extra = 1101u;

    array_queue_expand_space(queue, extra);
    if (capacity + extra != array_queue_capacity(queue)) {
        is_passed = false;
    }

    if (rest + extra != array_queue_rest_space(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_expand_space), is_passed);
    return;
}

static void
test_array_queue_capacity(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (array_queue_capacity(NULL)) {
        is_passed = false;
    }

    if (queue->space.dim != array_queue_capacity(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_capacity), is_passed);
    return;
}

static void
test_array_queue_rest_space(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    is_passed = true;

    if (array_queue_rest_space(NULL)) {
        is_passed = false;
    }

    if (capacity != array_queue_rest_space(queue)) {
        is_passed = false;
    }

    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }
    if (0 != array_queue_rest_space(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_rest_space), is_passed);
    return;
}

static void
test_array_queue_is_full(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    is_passed = true;

    if (!array_queue_is_full(NULL)) {
        is_passed = false;
    }

    array_queue_enter(queue, &capacity);
    capacity--;
    if (array_queue_is_full(queue)) {
        is_passed = false;
    }

    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }

    if (!array_queue_is_full(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}

static void
test_array_queue_is_empty(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (array_queue_is_empty(NULL)) {
        is_passed = false;
    }

    if (!array_queue_is_empty(queue)) {
        is_passed = false;
    }

    array_queue_enter(queue, &is_passed);
    if (array_queue_is_empty(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_is_empty), is_passed);
    return;
}

/*
static void
test_array_queue_create(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}
*/
