#ifndef HAVE_DEFINED_PERFORMANCE_TEST_QUEUE_H
#define HAVE_DEFINED_PERFORMANCE_TEST_QUEUE_H

#define PT_QUEUE_create(name)                     \
static void                                       \
ptest_##name##_queue_create(uint32 count)         \
{                                                 \
    QUEUE *queue;                                 \
                                                  \
    PERFORMANCE_TEST_BEGIN(name##_queue_create);  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        queue = QUEUE_create();                   \
        QUEUE_destroy(&queue);                    \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
    PERFORMANCE_TEST_RESULT(name##_queue_create); \
}

#define PT_QUEUE_destroy(name)                     \
static void                                        \
ptest_##name##_queue_destroy(uint32 count)         \
{                                                  \
    QUEUE *queue;                                  \
                                                   \
    PERFORMANCE_TEST_BEGIN(name##_queue_destroy);  \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        queue = QUEUE_create();                    \
        QUEUE_destroy(&queue);                     \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
    PERFORMANCE_TEST_RESULT(name##_queue_destroy); \
}

#define PT_QUEUE_resize(name)                       \
static void                                         \
ptest_##name##_queue_resize(uint32 count)           \
{                                                   \
    QUEUE *queue;                                   \
                                                    \
    PERFORMANCE_TEST_BEGIN(name##_queue_resize);    \
    queue = QUEUE_create();                         \
                                                    \
    PERFORMANCE_TEST_CHECKPOINT;                    \
                                                    \
    while (count--) {                               \
        QUEUE_resize(queue, QUEUE_rest(queue) + 1); \
    }                                               \
                                                    \
    PERFORMANCE_TEST_ENDPOINT;                      \
                                                    \
    QUEUE_destroy(&queue);                          \
    PERFORMANCE_TEST_RESULT(name##_queue_resize);   \
}

#endif

