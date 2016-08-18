#define QUEUE                  stacked_queue

#define QUEUE_create           stacked_queue_create
#define QUEUE_destroy          stacked_queue_destroy
#define QUEUE_resize           stacked_queue_resize
#define QUEUE_full_p           stacked_queue_full_p
#define QUEUE_empty_p          stacked_queue_empty_p
#define QUEUE_capacity         stacked_queue_capacity
#define QUEUE_rest             stacked_queue_rest
#define QUEUE_enter            stacked_queue_enter
#define QUEUE_front            stacked_queue_front
#define QUEUE_rear             stacked_queue_rear
#define QUEUE_leave            stacked_queue_leave
#define QUEUE_cleanup          stacked_queue_cleanup
#define QUEUE_iterate          stacked_queue_iterate

#include "../unit_test_queue.h"

UT_QUEUE_destroy(stacked)
UT_QUEUE_resize(stacked)
UT_QUEUE_full_p(stacked)
UT_QUEUE_empty_p(stacked)
UT_QUEUE_capacity(stacked)
UT_QUEUE_enter(stacked)
UT_QUEUE_front(stacked)
UT_QUEUE_rear(stacked)

#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_resize
#undef QUEUE_full_p
#undef QUEUE_empty_p
#undef QUEUE_capacity
#undef QUEUE_rest
#undef QUEUE_enter
#undef QUEUE_leave
#undef QUEUE_front
#undef QUEUE_rear
#undef QUEUE_cleanup
#undef QUEUE_iterate

static void
utest_stacked_queue_create(void)
{

    bool pass;
    uint32 capacity;
    s_stacked_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(stacked_queue_create);
    queue = stacked_queue_create();

    capacity = stacked_queue_capacity(queue);
    RESULT_CHECK_uint32(capacity, stacked_queue_capacity(queue), &pass);
    RESULT_CHECK_uint32(capacity * 2, stacked_queue_rest(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_create, pass);
}

static void
utest_stacked_queue_rest(void)
{
    bool pass;
    uint32 capacity;
    s_stacked_queue_t *queue;

    pass = true;
    queue = NULL;

    UNIT_TEST_BEGIN(stacked_queue_rest);
    RESULT_CHECK_uint32(QUEUE_REST_INVALID, stacked_queue_rest(queue), &pass);

    queue = stacked_queue_create();
    capacity = stacked_queue_capacity(queue);
    RESULT_CHECK_uint32(capacity * 2, stacked_queue_rest(queue), &pass);

    stacked_queue_enter(queue, &pass);
    RESULT_CHECK_uint32(capacity * 2 - 1, stacked_queue_rest(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_rest, pass);
}

static void
utest_stacked_queue_leave(void)
{
    bool pass;
    s_stacked_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(stacked_queue_leave);

    queue = stacked_queue_create();
    RESULT_CHECK_pointer(PTR_INVALID, stacked_queue_leave(NULL), &pass);
    stacked_queue_resize(queue, 0u);

    do {
        stacked_queue_enter(queue, queue);
    } while (!stacked_queue_full_p(queue));

    do {
        RESULT_CHECK_pointer(queue, stacked_queue_leave(queue), &pass);
    } while (!stacked_queue_empty_p(queue));
    RESULT_CHECK_pointer(PTR_INVALID, stacked_queue_leave(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_leave, pass);
}

static void
utest_stacked_queue_cleanup(void)
{
    bool pass;
    s_stacked_queue_t *queue;

    pass = true;
    UNIT_TEST_BEGIN(stacked_queue_cleanup);

    stacked_queue_cleanup(NULL);

    queue = stacked_queue_create();
    stacked_queue_enter(queue, queue);
    RESULT_CHECK_bool(false, stacked_queue_full_p(queue), &pass);
    RESULT_CHECK_bool(false, stacked_queue_empty_p(queue), &pass);

    stacked_queue_cleanup(queue);
    RESULT_CHECK_bool(true, stacked_queue_empty_p(queue), &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_cleanup, pass);
}

static void
utest_stacked_queue_iterate(void)
{
    bool pass;
    uint32 tmp;
    s_stacked_queue_t *queue;

    tmp = 0;
    pass = true;
    UNIT_TEST_BEGIN(stacked_queue_iterate);

    queue = stacked_queue_create();
    do {
        stacked_queue_enter(queue, &tmp);
    } while (!stacked_queue_full_p(queue));

    stacked_queue_iterate(queue, queue_iterate_handler);
    RESULT_CHECK_uint32(tmp, stacked_queue_capacity(queue) * 2, &pass);

    stacked_queue_destroy(&queue);
    UNIT_TEST_RESULT(stacked_queue_iterate, pass);
}

