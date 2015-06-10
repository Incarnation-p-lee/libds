static void
unit_test_stacked_queue_struct_field(void)
{
    bool pass;
    uint32 sid;
    uint32 capacity;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    pass = true;
    sid = 0xfadeu;
    queue = stacked_queue_create();

    while (0 != loop--) {
        stacked_queue_sid_set(queue, sid);
        RESULT_CHECK_uint32(sid, stacked_queue_sid(queue), &pass);

        capacity = stacked_queue_capacity(queue);
        RESULT_CHECK_uint32(capacity, stacked_queue_dim(queue), &pass);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_struct_field), pass);
    return;
}

static void
unit_test_stacked_queue_create(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x1234567u;
    while (0 != loop--) {
        queue = stacked_queue_create();
        stacked_queue_destroy(&queue);
    }

    pass = true;
    queue = stacked_queue_create();
    RESULT_CHECK_uint32(0x0u, stacked_queue_sid(queue), &pass);
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_create), pass);
    return;
}

static void
unit_test_stacked_queue_destroy(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x1234567u;
    pass = true;
    queue = NULL;
    stacked_queue_destroy(&queue);

    while (0 != loop--) {
        queue = stacked_queue_create();
        stacked_queue_destroy(&queue);
    }
    RESULT_CHECK_pointer(NULL, queue, &pass);

    test_result_print(SYM_2_STR(stacked_queue_destroy), pass);
    return;
}

static void
unit_test_stacked_queue_space_expand(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;
    uint32 extra;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xa234567u;
    pass = true;
    extra = 1023;
    stacked_queue_space_expand(NULL, extra);

    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);
    stacked_queue_space_expand(queue, extra);
    RESULT_CHECK_uint32(capacity + extra, stacked_queue_capacity(queue), &pass);

    extra = 0;
    capacity = stacked_queue_capacity(queue);
    stacked_queue_space_expand(queue, extra);
    RESULT_CHECK_uint32(capacity * 2 + EXPAND_STACK_SPACE_MIN,
        stacked_queue_capacity(queue), &pass);

    extra = 1;
    while (0 != loop--) {
        stacked_queue_space_expand(queue, extra);
    }

    stacked_queue_destroy(&queue);
    test_result_print(SYM_2_STR(stacked_queue_space_expand), pass);

    return;
}

static void
unit_test_stacked_queue_capacity(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x32345678u;
    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_uint32(0x0u, stacked_queue_capacity(NULL), &pass);
    RESULT_CHECK_uint32(stacked_queue_dim(queue),
        stacked_queue_capacity(queue), &pass);

    stacked_queue_space_expand(queue, 0);
    while (0 != loop--) {
        RESULT_CHECK_uint32(stacked_queue_dim(queue),
            stacked_queue_capacity(queue), &pass);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_capacity), pass);
    return;
}

static void
unit_test_stacked_queue_space_rest(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x22345678u;
    pass = true;
    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);

    RESULT_CHECK_uint32(0x0u, stacked_queue_space_rest(NULL), &pass);
    RESULT_CHECK_uint32(capacity * 2, stacked_queue_space_rest(queue), &pass);

    stacked_queue_enter(queue, queue);
    while (0 != loop--) {
        RESULT_CHECK_uint32(capacity * 2, stacked_queue_space_rest(queue) + 1, &pass);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_space_rest), pass);
    return;
}

static void
unit_test_stacked_queue_full_p(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 cnt;
    uint32 capacity;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    cnt = 0;
    pass = true;
    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);

    RESULT_CHECK_bool(true, stacked_queue_full_p(NULL), &pass);
    RESULT_CHECK_bool(false, stacked_queue_full_p(queue), &pass);

    while (!stacked_queue_full_p(queue)) {
        cnt++;
        stacked_queue_enter(queue, queue);
    }
    RESULT_CHECK_uint32(cnt, capacity * 2, &pass);

    while (0 != loop--) {
        RESULT_CHECK_bool(true, stacked_queue_full_p(queue), &pass);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_full_p), pass);
    return;
}

static void
unit_test_stacked_queue_empty_p(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x32345678u;
    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_bool(false, stacked_queue_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, stacked_queue_empty_p(queue), &pass);

    stacked_queue_enter(queue, queue);
    while (0 != loop--) {
        RESULT_CHECK_bool(false, stacked_queue_empty_p(queue), &pass);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_empty_p), pass);
    return;
}

static void
unit_test_stacked_queue_enter(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x6234567u;
    queue = stacked_queue_create();
    pass = true;

    stacked_queue_enter(NULL, queue);

    stacked_queue_enter(queue, queue);
    RESULT_CHECK_pointer(queue, stacked_queue_leave(queue), &pass);

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));
    RESULT_CHECK_bool(true, stacked_queue_full_p(queue), &pass);

    capacity = stacked_queue_capacity(queue);
    stacked_queue_enter(queue, queue);
    RESULT_CHECK_uint32(capacity * 2 + EXPAND_STACK_SPACE_MIN,
        stacked_queue_capacity(queue), &pass);

    while (0 != loop--) {
        stacked_queue_space_expand(queue, 1);
        stacked_queue_enter(queue, queue);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_enter), pass);
    return;
}

static void
unit_test_stacked_queue_leave(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x1234567u;
    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_pointer(NULL, stacked_queue_leave(NULL), &pass);
    stacked_queue_space_expand(queue, loop);

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));

    do {
        RESULT_CHECK_pointer(queue, stacked_queue_leave(queue), &pass);
    } while (!stacked_queue_empty_p(queue));
    RESULT_CHECK_pointer(NULL, stacked_queue_leave(queue), &pass);
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_leave), pass);
    return;
}

static void
unit_test_stacked_queue_cleanup(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x7234567u;
    queue = stacked_queue_create();
    pass = true;

    stacked_queue_cleanup(NULL);

    stacked_queue_enter(queue, queue);
    RESULT_CHECK_bool(false, stacked_queue_full_p(queue), &pass);
    RESULT_CHECK_bool(false, stacked_queue_empty_p(queue), &pass);

    while (0 != loop--) {
        stacked_queue_cleanup(queue);
    }
    RESULT_CHECK_bool(true, stacked_queue_empty_p(queue), &pass);
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_cleanup), pass);
    return;
}

static void
unit_test_stacked_queue_iterate(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x523456;
    tmp = 0;
    pass = true;
    queue = stacked_queue_create();

    do {
        stacked_queue_enter(queue, &tmp);
    } while (!stacked_queue_full_p(queue));

    stacked_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(tmp, stacked_queue_capacity(queue) * 2, &pass);

    while (0 != loop--) {
        stacked_queue_iterate(queue, queue_iterate_handler);
    }
    stacked_queue_destroy(&queue);

    test_result_print(SYM_2_STR(stacked_queue_iterate), pass);
    return;
}

