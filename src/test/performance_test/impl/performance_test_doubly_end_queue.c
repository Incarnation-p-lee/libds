static void
performance_test_doubly_end_queue_struct_field(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_sid_set(queue, 0x32);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_struct_field),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_create(uint32 count)
{
    struct doubly_end_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = doubly_end_queue_create();
        doubly_end_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_end_queue_create),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_destroy(uint32 count)
{
    struct doubly_end_queue *queue;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        queue = test_doubly_end_queue_sample(3u);
        doubly_end_queue_destroy(&queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(doubly_end_queue_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_length(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(224u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_length(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_length),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_empty_p(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_empty_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_empty_p),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_head_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_head_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_head_enter),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_head_leave(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_head_enter(queue, queue);
        doubly_end_queue_head_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_head_leave),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_tail_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = doubly_end_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_tail_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_tail_enter),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_tail_leave(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_tail_enter(queue, queue);
        doubly_end_queue_tail_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_tail_leave),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_cleanup(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_cleanup(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_cleanup),
        performance_test_time_stamp_period());
}

static void
performance_test_doubly_end_queue_iterate(uint32 count)
{
    struct doubly_end_queue *queue;

    queue = test_doubly_end_queue_sample(823u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_iterate(queue, &queue_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    performance_test_result_print(SYM_2_STR(doubly_end_queue_iterate),
        performance_test_time_stamp_period());
}


