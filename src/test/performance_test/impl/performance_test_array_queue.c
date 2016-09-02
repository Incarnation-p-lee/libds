#define QUEUE                  s_array_queue_t

#define QUEUE_create           array_queue_create
#define QUEUE_destroy          array_queue_destroy
#define QUEUE_rest             array_queue_rest
#define QUEUE_resize           array_queue_resize
#define QUEUE_full_p           array_queue_full_p
#define QUEUE_capacity         array_queue_capacity
#define QUEUE_enter            array_queue_enter
#define QUEUE_leave            array_queue_leave

#include "../performance_test_queue.h"

PT_QUEUE_create(array)
PT_QUEUE_destroy(array)
PT_QUEUE_resize(array)
PT_QUEUE_rest(array)
PT_QUEUE_full_p(array)
PT_QUEUE_capacity(array)
PT_QUEUE_enter(array)
PT_QUEUE_leave(array)

#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_rest
#undef QUEUE_resize
#undef QUEUE_full_p
#undef QUEUE_capacity
#undef QUEUE_enter
#undef QUEUE_leave


static void
performance_test_array_queue_empty_p(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_empty_p(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(array_queue_empty_p);
}

static void
performance_test_array_queue_cleanup(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_cleanup(queue);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(array_queue_cleanup);
}

static void
performance_test_array_queue_iterate(uint32 count)
{
    struct array_queue *queue;

    queue = array_queue_create();
    while (!array_queue_full_p(queue)) {
        array_queue_enter(queue, queue);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_queue_iterate(queue, &queue_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_queue_destroy(&queue);
    PERFORMANCE_TEST_RESULT(array_queue_iterate);
}

