#define QUEUE                  s_doubly_end_queue_t
#define QUEUE_create           doubly_end_queue_create
#define QUEUE_destroy          doubly_end_queue_destroy


#include "../performance_test_queue.h"

PT_QUEUE_create(doubly_end)
PT_QUEUE_destroy(doubly_end)


#undef QUEUE
#undef QUEUE_create
#undef QUEUE_destroy


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
    PERFORMANCE_TEST_RESULT(doubly_end_queue_length);
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
    PERFORMANCE_TEST_RESULT(doubly_end_queue_empty_p);
}

static void
performance_test_doubly_end_queue_front_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    count = count >> 4;
    count = count == 0 ? 1000 : count;
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
performance_test_doubly_end_queue_front_leave(uint32 count)
{
    struct doubly_end_queue *queue;

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
performance_test_doubly_end_queue_rear_enter(uint32 count)
{
    struct doubly_end_queue *queue;

    count = count >> 4;
    count = count == 0 ? 1000 : count;
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
performance_test_doubly_end_queue_rear_leave(uint32 count)
{
    struct doubly_end_queue *queue;

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
    PERFORMANCE_TEST_RESULT(doubly_end_queue_cleanup);
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
    PERFORMANCE_TEST_RESULT(doubly_end_queue_iterate);
}

