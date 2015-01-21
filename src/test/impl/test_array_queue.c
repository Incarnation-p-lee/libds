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
    if (NULL != queue) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(array_queue_destroy), is_passed);
    return;
}

static void
test_array_queue_space_expand(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;
    uint32 rest;
    uint32 extra;

    queue = array_queue_create();
    is_passed = true;
    capacity = array_queue_capacity(queue);
    rest = array_queue_space_rest(queue);
    extra = 1101u;

    array_queue_space_expand(queue, extra);
    if (capacity + extra != array_queue_capacity(queue)) {
        is_passed = false;
    }

    if (rest + extra != array_queue_space_rest(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_space_expand), is_passed);
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
test_array_queue_space_rest(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    is_passed = true;

    if (array_queue_space_rest(NULL)) {
        is_passed = false;
    }

    if (capacity != array_queue_space_rest(queue)) {
        is_passed = false;
    }

    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }
    if (0 != array_queue_space_rest(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_space_rest), is_passed);
    return;
}

static void
test_array_queue_full_p(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    is_passed = true;

    if (!array_queue_full_p(NULL)) {
        is_passed = false;
    }

    array_queue_enter(queue, &capacity);
    capacity--;
    if (array_queue_full_p(queue)) {
        is_passed = false;
    }

    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }

    if (!array_queue_full_p(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}

static void
test_array_queue_empty_p(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (array_queue_empty_p(NULL)) {
        is_passed = false;
    }

    if (!array_queue_empty_p(queue)) {
        is_passed = false;
    }

    array_queue_enter(queue, &is_passed);
    if (array_queue_empty_p(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_empty_p), is_passed);
    return;
}


static void
test_array_queue_enter(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    is_passed = true;
    capacity = array_queue_capacity(queue);

    array_queue_enter(queue, &capacity);
    if (capacity != array_queue_space_rest(queue) + 1) {
        is_passed = false;
    }
    if (&capacity != *queue->space.front) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_enter), is_passed);
    return;
}

static void
test_array_queue_leave(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (array_queue_leave(NULL)) {
        is_passed = false;
    }
    if (array_queue_leave(queue)) {
        is_passed = false;
    }

    array_queue_enter(queue, &is_passed);
    if (&is_passed != array_queue_leave(queue)) {
        is_passed = false;
    }

    if (array_queue_capacity(queue) != array_queue_space_rest(queue)) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_leave), is_passed);
    return;
}

static void
test_array_queue_cleanup(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    array_queue_enter(queue, &is_passed);
    array_queue_enter(queue, queue);
    array_queue_cleanup(queue);
    if (array_queue_capacity(queue) != array_queue_space_rest(queue)
        || queue->space.front != queue->space.base
        || queue->space.rear != queue->space.base) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_cleanup), is_passed);
    return;
}

static void
test_array_queue_iterate(void)
{
    bool is_passed;
    struct array_queue *queue;
    uint32 capacity;
    uint32 tmp;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    is_passed = true;
    tmp = 0;

    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, &tmp);
    }

    array_queue_iterate(queue, queue_iterate_handler);

    if (capacity != tmp) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_iterate), is_passed);
    return;
}
