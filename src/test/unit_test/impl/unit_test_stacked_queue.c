static void
unit_test_stacked_queue_struct_field(void)
{
    bool pass;
    uint32 sid;
    uint32 capacity;
    struct stacked_queue *queue;

    pass = true;
    sid = 0xfadeu;
    queue = stacked_queue_create();

    stacked_queue_sid_set(queue, sid);
    RESULT_CHECK_uint32(sid, stacked_queue_sid(queue), &pass);

    capacity = stacked_queue_capacity(queue);
    RESULT_CHECK_uint32(capacity, stacked_queue_dim(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_struct_field, pass);
}

static void
unit_test_stacked_queue_create(void)
{
    bool pass;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    stacked_queue_destroy(&queue);

    pass = true;
    queue = stacked_queue_create();
    RESULT_CHECK_uint32(0x0u, stacked_queue_sid(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_create, pass);
}

static void
unit_test_stacked_queue_destroy(void)
{
    bool pass;
    struct stacked_queue *queue;

    pass = true;
    queue = NULL;
    stacked_queue_destroy(&queue);

    queue = stacked_queue_create();
    stacked_queue_destroy(&queue);

    RESULT_CHECK_pointer(NULL, queue, &pass);
    UNIT_TEST_RESULT(stacked_queue_destroy, pass);
}

static void
unit_test_stacked_queue_resize(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;
    uint32 dim;

    pass = true;
    dim = 0x1023;
    stacked_queue_resize(NULL, dim);

    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);
    stacked_queue_resize(queue, dim);
    RESULT_CHECK_uint32(dim, stacked_queue_capacity(queue), &pass);

    dim = 0;
    capacity = stacked_queue_capacity(queue);
    stacked_queue_resize(queue, dim);
    capacity = capacity * 2 + EXPAND_QUEUE_SPACE_MIN;
    RESULT_CHECK_uint32(capacity, stacked_queue_capacity(queue), &pass);

    dim = 1;
    stacked_queue_resize(queue, dim);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_resize, pass);
}

static void
unit_test_stacked_queue_capacity(void)
{
    bool pass;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_uint32(0x0u, stacked_queue_capacity(NULL), &pass);
    RESULT_CHECK_uint32(stacked_queue_dim(queue),
        stacked_queue_capacity(queue), &pass);

    stacked_queue_resize(queue, 0);
    RESULT_CHECK_uint32(stacked_queue_dim(queue),
        stacked_queue_capacity(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_capacity, pass);
}

static void
unit_test_stacked_queue_space_rest(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;

    pass = true;
    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);

    RESULT_CHECK_uint32(0x0u, stacked_queue_space_rest(NULL), &pass);
    RESULT_CHECK_uint32(capacity * 2, stacked_queue_space_rest(queue), &pass);

    stacked_queue_enter(queue, queue);
    RESULT_CHECK_uint32(capacity * 2, stacked_queue_space_rest(queue) + 1, &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_space_rest, pass);
}

static void
unit_test_stacked_queue_full_p(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 cnt;
    uint32 capacity;

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
    RESULT_CHECK_bool(true, stacked_queue_full_p(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_full_p, pass);
}

static void
unit_test_stacked_queue_empty_p(void)
{
    bool pass;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_bool(false, stacked_queue_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, stacked_queue_empty_p(queue), &pass);

    stacked_queue_enter(queue, queue);
    RESULT_CHECK_bool(false, stacked_queue_empty_p(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_empty_p, pass);
}

static void
unit_test_stacked_queue_enter(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 capacity;

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
    capacity = capacity * 2;
    RESULT_CHECK_uint32(capacity, stacked_queue_capacity(queue), &pass);

    stacked_queue_resize(queue, capacity + 1);
    stacked_queue_enter(queue, queue);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_enter, pass);
}

static void
unit_test_stacked_queue_leave(void)
{
    bool pass;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    pass = true;

    RESULT_CHECK_pointer(NULL, stacked_queue_leave(NULL), &pass);
    stacked_queue_resize(queue, 0u);

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));

    do {
        RESULT_CHECK_pointer(queue, stacked_queue_leave(queue), &pass);
    } while (!stacked_queue_empty_p(queue));
    RESULT_CHECK_pointer(NULL, stacked_queue_leave(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_leave, pass);
}

static void
unit_test_stacked_queue_cleanup(void)
{
    bool pass;
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    pass = true;

    stacked_queue_cleanup(NULL);

    stacked_queue_enter(queue, queue);
    RESULT_CHECK_bool(false, stacked_queue_full_p(queue), &pass);
    RESULT_CHECK_bool(false, stacked_queue_empty_p(queue), &pass);

    stacked_queue_cleanup(queue);
    RESULT_CHECK_bool(true, stacked_queue_empty_p(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_cleanup, pass);
}

static void
unit_test_stacked_queue_iterate(void)
{
    bool pass;
    struct stacked_queue *queue;
    uint32 tmp;

    tmp = 0;
    pass = true;
    queue = stacked_queue_create();

    do {
        stacked_queue_enter(queue, &tmp);
    } while (!stacked_queue_full_p(queue));

    stacked_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(tmp, stacked_queue_capacity(queue) * 2, &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_iterate, pass);
}

