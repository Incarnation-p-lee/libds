static void
performance_test_array_queue_struct_field(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_sid_set(queue, 0x32);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_struct_field),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_create(uint32 count)
{
    struct array_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = array_queue_create();
        array_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(array_queue_create),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_destroy(uint32 count)
{
    struct array_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = array_queue_create();
        array_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(array_queue_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_space_expand(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_space_expand(queue, 1u);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_space_expand),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_capacity(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_capacity(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_capacity),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_space_rest(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_space_rest(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_space_rest),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_full_p(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_full_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_full_p),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_enter(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_enter),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_leave(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_enter(queue, queue);
        array_queue_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_leave),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_empty_p(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_empty_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_empty_p),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_cleanup(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_cleanup(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_cleanup),
        performance_test_time_stamp_period());
}

static void
performance_test_array_queue_iterate(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();
    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_iterate(queue, &queue_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(array_queue_iterate),
        performance_test_time_stamp_period());
}

