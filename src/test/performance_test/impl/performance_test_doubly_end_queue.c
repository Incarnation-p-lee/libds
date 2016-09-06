#define QUEUE                  s_doubly_end_queue_t

#define QUEUE_create           doubly_end_queue_create
#define QUEUE_destroy          doubly_end_queue_destroy
#define QUEUE_empty_p          doubly_end_queue_empty_p
#define QUEUE_cleanup          doubly_end_queue_cleanup
#define QUEUE_iterate          doubly_end_queue_iterate
#define QUEUE_front            doubly_end_queue_front
#define QUEUE_rear             doubly_end_queue_rear


#include "../performance_test_queue.h"

PT_QUEUE_create(doubly_end)
PT_QUEUE_destroy(doubly_end)
PT_QUEUE_empty_p(doubly_end)
PT_QUEUE_cleanup(doubly_end)
PT_QUEUE_iterate(doubly_end)
PT_QUEUE_front(doubly_end)
PT_QUEUE_rear(doubly_end)


#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_empty_p
#undef QUEUE_cleanup
#undef QUEUE_iterate
#undef QUEUE_front


static void
ptest_doubly_end_queue_length(uint32 count)
{
    s_doubly_end_queue_t *queue;

    PERFORMANCE_TEST_BEGIN(doubly_end_queue_length);
    queue = test_doubly_end_queue_sample(224u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_length(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(doubly_end_queue_length);
}

static void
ptest_doubly_end_queue_front_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    count = count >> 4;
    count = count == 0 ? 1000 : count;
    PERFORMANCE_TEST_BEGIN(doubly_end_queue_front_enter);
    queue = doubly_end_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_front_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(doubly_end_queue_front_enter);
}

static void
ptest_doubly_end_queue_front_leave(uint32 count)
{
    struct doubly_end_queue *queue;

    PERFORMANCE_TEST_BEGIN(doubly_end_queue_front_leave);
    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_front_enter(queue, queue);
        doubly_end_queue_front_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(doubly_end_queue_front_leave);
}

static void
ptest_doubly_end_queue_rear_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    count = count >> 4;
    count = count == 0 ? 1000 : count;
    PERFORMANCE_TEST_BEGIN(doubly_end_queue_rear_enter);
    queue = doubly_end_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_rear_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(doubly_end_queue_rear_enter);
}

static void
ptest_doubly_end_queue_rear_leave(uint32 count)
{
    struct doubly_end_queue *queue;

    PERFORMANCE_TEST_BEGIN(doubly_end_queue_rear_leave);
    queue = test_doubly_end_queue_sample(1024u);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        doubly_end_queue_rear_enter(queue, queue);
        doubly_end_queue_rear_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    doubly_end_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(doubly_end_queue_rear_leave);
}

