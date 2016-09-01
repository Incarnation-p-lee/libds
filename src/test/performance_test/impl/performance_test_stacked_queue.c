#define QUEUE                  s_stacked_queue_t

#define QUEUE_create           stacked_queue_create
#define QUEUE_destroy          stacked_queue_destroy
#define QUEUE_rest             stacked_queue_rest
#define QUEUE_resize           stacked_queue_resize


#include "../performance_test_queue.h"

PT_QUEUE_create(stacked)
PT_QUEUE_destroy(stacked)
PT_QUEUE_resize(stacked)


#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_rest
#undef QUEUE_resize


static void
performance_test_stacked_queue_rest(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_rest(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_rest);
}

static void
performance_test_stacked_queue_full_p(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_full_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_full_p);
}

static void
performance_test_stacked_queue_capacity(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_capacity(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_capacity);
}

static void
performance_test_stacked_queue_enter(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_enter);
}

static void
performance_test_stacked_queue_leave(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_enter(queue, queue);
        stacked_queue_leave(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_leave);
}

static void
performance_test_stacked_queue_empty_p(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_empty_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_empty_p);
}

static void
performance_test_stacked_queue_cleanup(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_cleanup(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_cleanup);
}

static void
performance_test_stacked_queue_iterate(uint32 count)
{
    struct stacked_queue *queue;

    queue = stacked_queue_create();
    while (!stacked_queue_full_p(queue)) {
        stacked_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stacked_queue_iterate(queue, &queue_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    stacked_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(stacked_queue_iterate);
}

