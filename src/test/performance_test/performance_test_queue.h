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
        QUEUE_resize(queue, count);                 \
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

#define PT_QUEUE_front(name)                     \
static void                                      \
ptest_##name##_queue_front(uint32 count)         \
{                                                \
    QUEUE *queue;                                \
                                                 \
    PERFORMANCE_TEST_BEGIN(name##_queue_front);  \
    queue = QUEUE_create();                      \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        QUEUE_front(queue);                      \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    QUEUE_destroy(&queue);                       \
    PERFORMANCE_TEST_RESULT(name##_queue_front); \
}

#define PT_QUEUE_rear(name)                     \
static void                                     \
ptest_##name##_queue_rear(uint32 count)         \
{                                               \
    QUEUE *queue;                               \
                                                \
    PERFORMANCE_TEST_BEGIN(name##_queue_rear);  \
    queue = QUEUE_create();                     \
                                                \
    PERFORMANCE_TEST_CHECKPOINT;                \
                                                \
    while (count--) {                           \
        QUEUE_rear(queue);                      \
    }                                           \
                                                \
    PERFORMANCE_TEST_ENDPOINT;                  \
                                                \
    QUEUE_destroy(&queue);                      \
    PERFORMANCE_TEST_RESULT(name##_queue_rear); \
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

#define PT_QUEUE_empty_p(name)                     \
static void                                        \
ptest_##name##_queue_empty_p(uint32 count)         \
{                                                  \
    QUEUE *queue;                                  \
                                                   \
    PERFORMANCE_TEST_BEGIN(name##_queue_empty_p);  \
    queue = QUEUE_create();                        \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        QUEUE_empty_p(queue);                      \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    QUEUE_destroy(&queue);                         \
    PERFORMANCE_TEST_RESULT(name##_queue_empty_p); \
}

#define PT_QUEUE_cleanup(name)                     \
static void                                        \
ptest_##name##_queue_cleanup(uint32 count)         \
{                                                  \
    QUEUE *queue;                                  \
                                                   \
    PERFORMANCE_TEST_BEGIN(name##_queue_cleanup);  \
    queue = QUEUE_create();                        \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        QUEUE_cleanup(queue);                      \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    QUEUE_destroy(&queue);                         \
    PERFORMANCE_TEST_RESULT(name##_queue_cleanup); \
}

#define PT_QUEUE_iterate(name)                        \
static void                                           \
ptest_##name##_queue_iterate(uint32 count)            \
{                                                     \
    QUEUE *queue;                                     \
                                                      \
    PERFORMANCE_TEST_BEGIN(name##_queue_iterate);     \
    queue = QUEUE_create();                           \
                                                      \
    PERFORMANCE_TEST_CHECKPOINT;                      \
                                                      \
    while (count--) {                                 \
        QUEUE_iterate(queue, &queue_iterate_handler); \
    }                                                 \
                                                      \
    PERFORMANCE_TEST_ENDPOINT;                        \
                                                      \
    QUEUE_destroy(&queue);                            \
    PERFORMANCE_TEST_RESULT(name##_queue_iterate);    \
}

#define PT_QUEUE_copy(name)                     \
static void                                     \
ptest_##name##_queue_copy(uint32 count)         \
{                                               \
    ptr_t i;                                    \
    QUEUE *queue;                               \
    QUEUE *queue_copy;                          \
                                                \
    PERFORMANCE_TEST_BEGIN(name##_queue_copy);  \
    queue = QUEUE_create();                     \
    queue_copy = QUEUE_create();                \
                                                \
    i = 0;                                      \
    while (i < 0x132) {                         \
        QUEUE_enter(queue, (void *)i++);        \
    }                                           \
                                                \
    PERFORMANCE_TEST_CHECKPOINT;                \
                                                \
    while (count--) {                           \
        QUEUE_copy(queue_copy, queue);          \
    }                                           \
                                                \
    PERFORMANCE_TEST_ENDPOINT;                  \
                                                \
    QUEUE_destroy(&queue);                      \
    QUEUE_destroy(&queue_copy);                 \
    PERFORMANCE_TEST_RESULT(name##_queue_copy); \
}

#define PT_QUEUE_merge(name)                     \
static void                                      \
ptest_##name##_queue_merge(uint32 count)         \
{                                                \
    ptr_t i;                                     \
    QUEUE *queue;                                \
    QUEUE *queue_merge;                          \
                                                 \
    PERFORMANCE_TEST_BEGIN(name##_queue_merge);  \
    queue = QUEUE_create();                      \
    queue_merge = QUEUE_create();                \
                                                 \
    i = 0;                                       \
    while (i < 0x132) {                          \
        QUEUE_enter(queue, (void *)i++);         \
    }                                            \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        QUEUE_merge(queue_merge, queue);         \
        QUEUE_cleanup(queue_merge);              \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    QUEUE_destroy(&queue);                       \
    QUEUE_destroy(&queue_merge);                 \
    PERFORMANCE_TEST_RESULT(name##_queue_merge); \
}

#endif

