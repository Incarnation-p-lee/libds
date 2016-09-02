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

#define PT_QUEUE_rest(name)                     \
static void                                     \
ptest_##name##_queue_rest(uint32 count)         \
{                                               \
    QUEUE *queue;                               \
                                                \
    PERFORMANCE_TEST_BEGIN(name##_queue_rest);  \
    queue = QUEUE_create();                     \
                                                \
    PERFORMANCE_TEST_CHECKPOINT;                \
                                                \
    while (count--) {                           \
        QUEUE_rest(queue);                      \
    }                                           \
                                                \
    PERFORMANCE_TEST_ENDPOINT;                  \
                                                \
    QUEUE_destroy(&queue);                      \
    PERFORMANCE_TEST_RESULT(name##_queue_rest); \
}

#define PT_QUEUE_full_p(name)                     \
static void                                       \
ptest_##name##_queue_full_p(uint32 count)         \
{                                                 \
    QUEUE *queue;                                 \
                                                  \
    PERFORMANCE_TEST_BEGIN(name##_queue_full_p);  \
    queue = QUEUE_create();                       \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        QUEUE_full_p(queue);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    QUEUE_destroy(&queue);                        \
    PERFORMANCE_TEST_RESULT(name##_queue_full_p); \
}

#define PT_QUEUE_capacity(name)                     \
static void                                         \
ptest_##name##_queue_capacity(uint32 count)         \
{                                                   \
    QUEUE *queue;                                   \
                                                    \
    PERFORMANCE_TEST_BEGIN(name##_queue_capacity);  \
    queue = QUEUE_create();                         \
                                                    \
    PERFORMANCE_TEST_CHECKPOINT;                    \
                                                    \
    while (count--) {                               \
        QUEUE_capacity(queue);                      \
    }                                               \
                                                    \
    PERFORMANCE_TEST_ENDPOINT;                      \
                                                    \
    QUEUE_destroy(&queue);                          \
    PERFORMANCE_TEST_RESULT(name##_queue_capacity); \
}

#define PT_QUEUE_enter(name)                     \
static void                                      \
ptest_##name##_queue_enter(uint32 count)         \
{                                                \
    QUEUE *queue;                                \
                                                 \
    PERFORMANCE_TEST_BEGIN(name##_queue_enter);  \
    queue = QUEUE_create();                      \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        QUEUE_enter(queue, queue);               \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    QUEUE_destroy(&queue);                       \
    PERFORMANCE_TEST_RESULT(name##_queue_enter); \
}

#define PT_QUEUE_leave(name)                     \
static void                                      \
ptest_##name##_queue_leave(uint32 count)         \
{                                                \
    QUEUE *queue;                                \
                                                 \
    PERFORMANCE_TEST_BEGIN(name##_queue_leave);  \
    queue = QUEUE_create();                      \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        QUEUE_enter(queue, queue);               \
        QUEUE_leave(queue);                      \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    QUEUE_destroy(&queue);                       \
    PERFORMANCE_TEST_RESULT(name##_queue_leave); \
}

#endif

