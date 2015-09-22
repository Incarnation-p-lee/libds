static void
unit_test_doubly_end_queue_struct_field(void)
{
    bool pass;
    uint32 sid;
    struct doubly_end_queue *queue;

    pass = true;
    sid = 0xfadeu;
    queue = doubly_end_queue_create();

    doubly_end_queue_sid_set(queue, sid);
    RESULT_CHECK_uint32(sid, doubly_end_queue_sid(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_struct_field), pass);
}

static void
unit_test_doubly_end_queue_create(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    RESULT_CHECK_uint32(0x0u, doubly_end_queue_sid(queue), &pass);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_create), pass);
}

static void
unit_test_doubly_end_queue_destroy(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = NULL;

    doubly_end_queue_destroy(&queue);
    queue = doubly_end_queue_create();
    doubly_end_queue_destroy(&queue);
    RESULT_CHECK_pointer(NULL, queue, &pass);

    queue = doubly_end_queue_create();
    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_destroy(&queue);
    RESULT_CHECK_pointer(NULL, queue, &pass);

    test_result_print(SYM_2_STR(doubly_end_queue_destroy), pass);
}

static void
unit_test_doubly_end_queue_length(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    RESULT_CHECK_uint32(0x0u, doubly_end_queue_length(NULL), &pass);
    RESULT_CHECK_uint32(0x0u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_destroy(&queue);

    queue = doubly_end_queue_create();
    doubly_end_queue_head_enter(queue, queue);
    RESULT_CHECK_uint32(0x1u, doubly_end_queue_length(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_length), pass);
}

static void
unit_test_doubly_end_queue_empty_p(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_destroy(&queue);

    queue = doubly_end_queue_create();
    doubly_end_queue_head_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_empty_p), pass);
}

static void
unit_test_doubly_end_queue_head_enter(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    doubly_end_queue_head_enter(NULL, queue);

    doubly_end_queue_head_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_head_enter(queue, queue);
    RESULT_CHECK_uint32(0x2u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_head_leave(queue);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_head_enter), pass);
}

static void
unit_test_doubly_end_queue_tail_enter(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    doubly_end_queue_tail_enter(NULL, queue);

    doubly_end_queue_tail_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_tail_enter(queue, queue);
    RESULT_CHECK_uint32(0x2u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_tail_leave(queue);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_tail_enter), pass);
}

static void
unit_test_doubly_end_queue_head_leave(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    RESULT_CHECK_pointer(NULL, doubly_end_queue_head_leave(queue), &pass);

    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_head_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);
    RESULT_CHECK_pointer(queue, doubly_end_queue_head_leave(queue), &pass);

    doubly_end_queue_head_leave(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_head_enter(queue, queue);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_head_leave), pass);
}

static void
unit_test_doubly_end_queue_tail_leave(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    RESULT_CHECK_pointer(NULL, doubly_end_queue_tail_leave(queue), &pass);

    doubly_end_queue_tail_enter(queue, queue);
    doubly_end_queue_tail_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    RESULT_CHECK_pointer(queue, doubly_end_queue_tail_leave(queue), &pass);

    doubly_end_queue_tail_leave(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_tail_enter(queue, queue);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_tail_leave), pass);
}


static void
unit_test_doubly_end_queue_cleanup(void)
{
    bool pass;
    struct doubly_end_queue *queue;

    pass = true;
    queue = doubly_end_queue_create();

    doubly_end_queue_cleanup(NULL);

    doubly_end_queue_head_enter(queue, queue);
    doubly_end_queue_tail_enter(queue, queue);
    doubly_end_queue_cleanup(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_cleanup(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_cleanup), pass);
}

static void
unit_test_doubly_end_queue_iterate(void)
{
    bool pass;
    struct doubly_end_queue *queue;
    uint32 tmp;
    uint32 cnt;

    tmp = 0;
    cnt = 1023;
    pass = true;
    queue = doubly_end_queue_create();

    doubly_end_queue_iterate(NULL, queue_iterate_handler);

    while (cnt) {
        doubly_end_queue_head_enter(queue, &tmp);
        cnt--;
    }

    tmp = 0;
    doubly_end_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(tmp, doubly_end_queue_length(queue), &pass);

    doubly_end_queue_destroy(&queue);
    test_result_print(SYM_2_STR(doubly_end_queue_iterate), pass);
}

