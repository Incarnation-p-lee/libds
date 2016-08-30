#define QUEUE                  s_doubly_end_queue_t

#define QUEUE_create           doubly_end_queue_create
#define QUEUE_destroy          doubly_end_queue_destroy
#define QUEUE_enter            doubly_end_queue_front_enter
#define QUEUE_leave            doubly_end_queue_rear_leave
#define QUEUE_front            doubly_end_queue_front
#define QUEUE_rear             doubly_end_queue_rear

#include "../unit_test_queue.h"

UT_QUEUE_destroy(doubly_end)
UT_QUEUE_front(doubly_end)
UT_QUEUE_rear(doubly_end)

#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_enter
#undef QUEUE_leave
#undef QUEUE_front
#undef QUEUE_rear

static inline void
utest_doubly_end_queue_create(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_create);

    queue = doubly_end_queue_create();
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_create, pass);
}

static void
utest_doubly_end_queue_length(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_length);

    queue = doubly_end_queue_create();
    RESULT_CHECK_uint32(QUEUE_SIZE_INVALID, doubly_end_queue_length(NULL), &pass);
    RESULT_CHECK_uint32(0x0u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_destroy(&queue);

    queue = doubly_end_queue_create();
    doubly_end_queue_front_enter(queue, queue);
    RESULT_CHECK_uint32(0x1u, doubly_end_queue_length(queue), &pass);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_length, pass);
}

static void
utest_doubly_end_queue_empty_p(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_empty_p);

    queue = doubly_end_queue_create();
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_destroy(&queue);

    queue = doubly_end_queue_create();
    doubly_end_queue_front_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_empty_p, pass);
}

static void
utest_doubly_end_queue_front_enter(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_front_enter);

    queue = doubly_end_queue_create();
    doubly_end_queue_front_enter(NULL, queue);

    doubly_end_queue_front_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_front_enter(queue, queue);
    RESULT_CHECK_uint32(0x2u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_front_leave(queue);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_front_enter, pass);
}

static void
utest_doubly_end_queue_rear_enter(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_rear_enter);

    queue = doubly_end_queue_create();
    doubly_end_queue_rear_enter(NULL, queue);

    doubly_end_queue_rear_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_rear_enter(queue, queue);
    RESULT_CHECK_uint32(0x2u, doubly_end_queue_length(queue), &pass);
    doubly_end_queue_rear_leave(queue);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_rear_enter, pass);
}

static void
utest_doubly_end_queue_front_leave(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_front_leave);

    queue = doubly_end_queue_create();
    RESULT_CHECK_pointer(PTR_INVALID, doubly_end_queue_front_leave(queue), &pass);

    doubly_end_queue_front_enter(queue, queue);
    doubly_end_queue_front_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);
    RESULT_CHECK_pointer(queue, doubly_end_queue_front_leave(queue), &pass);

    doubly_end_queue_front_leave(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_front_enter(queue, queue);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_front_leave, pass);
}

static void
utest_doubly_end_queue_rear_leave(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_rear_leave);

    queue = doubly_end_queue_create();
    RESULT_CHECK_pointer(PTR_INVALID, doubly_end_queue_rear_leave(queue), &pass);

    doubly_end_queue_rear_enter(queue, queue);
    doubly_end_queue_rear_enter(queue, queue);
    RESULT_CHECK_bool(false, doubly_end_queue_empty_p(queue), &pass);

    RESULT_CHECK_pointer(queue, doubly_end_queue_rear_leave(queue), &pass);

    doubly_end_queue_rear_leave(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);
    doubly_end_queue_rear_enter(queue, queue);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_rear_leave, pass);
}

static void
utest_doubly_end_queue_cleanup(void)
{
    bool pass;
    s_doubly_end_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_cleanup);

    queue = doubly_end_queue_create();
    doubly_end_queue_cleanup(NULL);

    doubly_end_queue_front_enter(queue, queue);
    doubly_end_queue_rear_enter(queue, queue);
    doubly_end_queue_cleanup(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_cleanup(queue);
    RESULT_CHECK_bool(true, doubly_end_queue_empty_p(queue), &pass);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_cleanup, pass);
}

static void
utest_doubly_end_queue_iterate(void)
{
    bool pass;
    uint32 tmp;
    uint32 cnt;
    s_doubly_end_queue_t *queue;

    tmp = 0;
    cnt = 1023;
    pass = true;
    UNIT_TEST_BEGIN(doubly_end_queue_iterate);

    queue = doubly_end_queue_create();
    doubly_end_queue_iterate(NULL, queue_iterate_handler);

    while (cnt) {
        doubly_end_queue_front_enter(queue, &tmp);
        cnt--;
    }

    tmp = 0;
    doubly_end_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(tmp, doubly_end_queue_length(queue), &pass);

    doubly_end_queue_destroy(&queue);
    UNIT_TEST_RESULT(doubly_end_queue_iterate, pass);
}

