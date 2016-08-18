static void
performance_test_stacked_queue_create(uint32 count)
{
    struct stacked_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = stacked_queue_create();
        stacked_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(stacked_queue_create);
}

static void
performance_test_stacked_queue_destroy(uint32 count)
{
    struct stacked_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = stacked_queue_create();
        stacked_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(stacked_queue_destroy);
}

static void
performance_test_stacked_queue_space_expand(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_resize(queue, 1u);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_space_expand);
}

static void
performance_test_stacked_queue_rest(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_rest(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_rest);
}

static void
performance_test_stacked_queue_full_p(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_full_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_full_p);
}

static void
performance_test_stacked_queue_capacity(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_capacity(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_capacity);
}

static void
performance_test_stacked_queue_enter(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_enter);
}

static void
performance_test_stacked_queue_leave(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_enter(queue, queue);
        stacked_queue_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_leave);
}

static void
performance_test_stacked_queue_empty_p(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_empty_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_empty_p);
}

static void
performance_test_stacked_queue_cleanup(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_cleanup(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_cleanup);
}

static void
performance_test_stacked_queue_iterate(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    while (!stacked_queue_full_p(queue)) {
        stacked_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_iterate(queue, &queue_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_iterate);
}

