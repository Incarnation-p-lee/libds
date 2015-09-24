static void
unit_test_array_queue_struct_field(void)
{
    bool pass;
    uint32 sid;
    uint32 capacity;
    struct array_queue *queue;

    pass = true;
    sid = 0xfadeu;
    queue = array_queue_create();

    array_queue_sid_set(queue, sid);
    RESULT_CHECK_uint32(sid, array_queue_sid(queue), &pass);

    capacity = array_queue_capacity(queue);
    RESULT_CHECK_uint32(capacity, array_queue_dim(queue), &pass);
    RESULT_CHECK_uint32(capacity, array_queue_rest(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_struct_field), pass);
}

static void
unit_test_array_queue_create(void)
{
    bool pass;
    struct array_queue *queue;

    queue = array_queue_create();
    pass = true;

    RESULT_CHECK_uint32(0x0u, array_queue_sid(queue), &pass);
    RESULT_CHECK_uint32(array_queue_rest(queue), array_queue_dim(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_create), pass);
}

static void
unit_test_array_queue_destroy(void)
{
    bool pass;
    struct array_queue *queue;

    pass = true;
    queue = NULL;
    array_queue_destroy(&queue);
    RESULT_CHECK_pointer(NULL, queue, &pass);

    queue = array_queue_create();
    array_queue_destroy(&queue);
    RESULT_CHECK_pointer(NULL, queue, &pass);
    unit_test_result_print(SYM_2_STR(array_queue_destroy), pass);
}

static void
unit_test_array_queue_space_expand(void)
{
    bool pass;
    struct array_queue *queue;
    uint32 capacity;
    uint32 rest;
    uint32 extra;

    queue = array_queue_create();
    pass = true;
    capacity = array_queue_capacity(queue);
    rest = array_queue_space_rest(queue);
    extra = 11u;

    array_queue_space_expand(NULL, extra);
    array_queue_space_expand(queue, extra);
    RESULT_CHECK_uint32(capacity + extra, array_queue_capacity(queue), &pass);
    RESULT_CHECK_uint32(rest + extra, array_queue_capacity(queue), &pass);

    capacity = array_queue_capacity(queue);
    array_queue_space_expand(queue, 0u);
    RESULT_CHECK_uint32(capacity * 2 + EXPAND_QUEUE_SPACE_MIN,
        array_queue_capacity(queue), &pass);

    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, &pass);
    }

    array_queue_leave(queue);
    array_queue_leave(queue);
    array_queue_leave(queue);
    array_queue_enter(queue, &pass);
    array_queue_enter(queue, &pass);

    extra = 0x1u;
    capacity = array_queue_capacity(queue);
    array_queue_space_expand(queue, extra);
    RESULT_CHECK_uint32(capacity + extra, array_queue_capacity(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_space_expand), pass);
}

static void
unit_test_array_queue_capacity(void)
{
    bool pass;
    uint32 extra;
    struct array_queue *queue;

    extra = 0x1;
    queue = array_queue_create();
    pass = true;

    RESULT_CHECK_uint32(0x0u, array_queue_capacity(NULL), &pass);

    array_queue_space_expand(queue, extra);
    RESULT_CHECK_uint32(array_queue_dim(queue),
        array_queue_capacity(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_capacity), pass);
}

static void
unit_test_array_queue_space_rest(void)
{
    bool pass;
    struct array_queue *queue;
    uint32 capacity;
    uint32 extra;

    pass = true;
    extra = 0x1;
    queue = array_queue_create();
    capacity = array_queue_capacity(queue);

    RESULT_CHECK_uint32(0x0u, array_queue_space_rest(NULL), &pass);
    RESULT_CHECK_uint32(capacity, array_queue_space_rest(queue), &pass);

    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }

    array_queue_space_expand(queue, 1);
    RESULT_CHECK_uint32(extra++, array_queue_space_rest(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_space_rest), pass);
}

static void
unit_test_array_queue_full_p(void)
{
    bool pass;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    pass = true;

    RESULT_CHECK_bool(true, array_queue_full_p(NULL), &pass);

    array_queue_enter(queue, &capacity);
    RESULT_CHECK_bool(false, array_queue_full_p(queue), &pass);

    capacity--;
    while (capacity > 0) {
        array_queue_enter(queue, &capacity);
        capacity--;
    }

    RESULT_CHECK_bool(true, array_queue_full_p(queue), &pass);
    array_queue_space_expand(queue, 0x1u);
    RESULT_CHECK_bool(false, array_queue_full_p(queue), &pass);
    array_queue_enter(queue, &capacity);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_full_p), pass);
}

static void
unit_test_array_queue_empty_p(void)
{
    bool pass;
    struct array_queue *queue;

    queue = array_queue_create();
    pass = true;

    RESULT_CHECK_bool(false, array_queue_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, array_queue_empty_p(queue), &pass);

    array_queue_enter(queue, &pass);
    RESULT_CHECK_bool(false, array_queue_empty_p(queue), &pass);
    array_queue_space_expand(queue, 1);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_empty_p), pass);
}


static void
unit_test_array_queue_enter(void)
{
    bool pass;
    struct array_queue *queue;
    uint32 capacity;

    queue = array_queue_create();
    pass = true;
    capacity = array_queue_capacity(queue);

    array_queue_enter(NULL, &capacity);
    array_queue_enter(queue, &capacity);
    RESULT_CHECK_uint32(capacity, array_queue_space_rest(queue) + 1, &pass);
    RESULT_CHECK_pointer(&capacity, array_queue_leave(queue), &pass);

    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, &pass);
    }

    array_queue_enter(queue, &pass);
    RESULT_CHECK_uint32(capacity * 2 + EXPAND_QUEUE_SPACE_MIN,
        array_queue_capacity(queue), &pass);

    array_queue_enter(queue, &pass);
    array_queue_space_expand(queue, 1);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_enter), pass);
}

static void
unit_test_array_queue_leave(void)
{
    bool pass;
    struct array_queue *queue;

    queue = array_queue_create();
    pass = true;

    RESULT_CHECK_pointer(NULL, array_queue_leave(NULL), &pass);
    RESULT_CHECK_pointer(NULL, array_queue_leave(queue), &pass);

    array_queue_enter(queue, &pass);
    RESULT_CHECK_pointer(&pass, array_queue_leave(queue), &pass);
    RESULT_CHECK_uint32(array_queue_capacity(queue),
        array_queue_space_rest(queue), &pass);

    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, &pass);
    }

    array_queue_leave(queue);
    array_queue_leave(queue);
    array_queue_enter(queue, &pass);
    array_queue_enter(queue, &pass);

    while (!array_queue_empty_p(queue)) {
        array_queue_leave(queue);
    }
    RESULT_CHECK_pointer(NULL, array_queue_leave(queue), &pass);

    array_queue_enter(queue, &pass);
    array_queue_leave(queue);
    array_queue_space_expand(queue, 1);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_leave), pass);
}

static void
unit_test_array_queue_cleanup(void)
{
    bool pass;
    struct array_queue *queue;

    queue = array_queue_create();
    pass = true;

    array_queue_cleanup(NULL);
    array_queue_enter(queue, &pass);
    array_queue_enter(queue, queue);

    array_queue_cleanup(queue);
    RESULT_CHECK_uint32(array_queue_capacity(queue),
        array_queue_space_rest(queue), &pass);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_cleanup), pass);
}

static void
unit_test_array_queue_iterate(void)
{
    bool pass;
    struct array_queue *queue;
    uint32 capacity;
    uint32 tmp;

    queue = array_queue_create();
    capacity = array_queue_capacity(queue);
    pass = true;
    tmp = 0;

    array_queue_iterate(NULL, queue_iterate_handler);

    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, &tmp);
    }

    tmp = 0;
    array_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(capacity, tmp, &pass);

    array_queue_cleanup(queue);
    array_queue_iterate(queue, queue_iterate_handler);

    array_queue_destroy(&queue);
    unit_test_result_print(SYM_2_STR(array_queue_iterate), pass);
}

