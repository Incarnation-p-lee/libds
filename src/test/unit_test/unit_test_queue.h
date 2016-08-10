#ifndef HAVE_DEFINED_UNIT_TEST_QUEUE_H
#define HAVE_DEFINED_UNIT_TEST_QUEUE_H

#define UT_QUEUE_create(name)                                    \
static void                                                      \
utest_##name##_queue_create(void)                                \
{                                                                \
    bool pass;                                                   \
    uint32 capacity;                                             \
    struct QUEUE *queue;                                         \
                                                                 \
    pass = true;                                                 \
    UNIT_TEST_BEGIN(name##_queue_create);                        \
    queue = QUEUE_create();                                      \
                                                                 \
    capacity = QUEUE_capacity(queue);                            \
    RESULT_CHECK_uint32(capacity, QUEUE_capacity(queue), &pass); \
    RESULT_CHECK_uint32(capacity, QUEUE_rest(queue), &pass);     \
                                                                 \
    QUEUE_destroy(&queue);                                       \
    UNIT_TEST_RESULT(name##_queue_create, pass);                 \
}

#define UT_QUEUE_destroy(name)                    \
static void                                       \
utest_##name##_queue_destroy(void)                \
{                                                 \
    bool pass;                                    \
    struct QUEUE *queue;                          \
                                                  \
    pass = true;                                  \
    queue = NULL;                                 \
    UNIT_TEST_BEGIN(name##_queue_destroy);        \
                                                  \
    QUEUE_destroy(&queue);                        \
    RESULT_CHECK_pointer(NULL, queue, &pass);     \
                                                  \
    queue = QUEUE_create();                       \
    QUEUE_destroy(&queue);                        \
    RESULT_CHECK_pointer(NULL, queue, &pass);     \
                                                  \
    UNIT_TEST_RESULT(name##_queue_destroy, pass); \
}

#define UT_QUEUE_resize(name)                                \
static void                                                  \
utest_##name##_queue_resize(void)                            \
{                                                            \
    bool pass;                                               \
    uint32 size;                                             \
    struct QUEUE *queue;                                     \
                                                             \
    pass = true;                                             \
    queue = NULL;                                            \
                                                             \
    QUEUE_resize(queue, 0);                                  \
    queue = QUEUE_create();                                  \
    size = QUEUE_capacity(queue);                            \
    QUEUE_resize(queue, size);                               \
                                                             \
    size = QUEUE_capacity(queue) * 2 + QUEUE_EXPD_SIZE_MIN;  \
    QUEUE_resize(queue, 0);                                  \
    RESULT_CHECK_uint32(size, QUEUE_capacity(queue), &pass); \
                                                             \
    QUEUE_resize(queue, size);                               \
    RESULT_CHECK_uint32(size, QUEUE_capacity(queue), &pass); \
                                                             \
    size = size * 2 + 100;                                   \
    QUEUE_resize(queue, size);                               \
    RESULT_CHECK_uint32(size, QUEUE_capacity(queue), &pass); \
                                                             \
    while (!QUEUE_full_p(queue)) {                           \
        QUEUE_enter(queue, &pass);                           \
    }                                                        \
    QUEUE_leave(queue);                                      \
    QUEUE_leave(queue);                                      \
    QUEUE_enter(queue, &pass);                               \
                                                             \
    size = size + 1000;                                      \
    QUEUE_resize(queue, size);                               \
    RESULT_CHECK_uint32(size, QUEUE_capacity(queue), &pass); \
                                                             \
    while (!QUEUE_full_p(queue)) {                           \
        QUEUE_enter(queue, &pass);                           \
    }                                                        \
    QUEUE_leave(queue);                                      \
    QUEUE_leave(queue);                                      \
    QUEUE_enter(queue, &pass);                               \
                                                             \
    size = size - 10;                                        \
    QUEUE_resize(queue, size);                               \
    RESULT_CHECK_uint32(size, QUEUE_capacity(queue), &pass); \
                                                             \
    QUEUE_destroy(&queue);                                   \
    UNIT_TEST_RESULT(name##_queue_resize, pass);             \
}

#define UT_QUEUE_capacity(name)                                               \
static void                                                                   \
utest_##name##_queue_capacity(void)                                           \
{                                                                             \
    bool pass;                                                                \
    struct QUEUE *queue;                                                      \
                                                                              \
    pass = true;                                                              \
    queue = NULL;                                                             \
                                                                              \
    RESULT_CHECK_uint32(QUEUE_CPCT_INVALID, QUEUE_capacity(queue), &pass);    \
                                                                              \
    queue = QUEUE_create();                                                   \
    RESULT_CHECK_uint32(QUEUE_capacity(queue), QUEUE_capacity(queue), &pass); \
                                                                              \
    QUEUE_destroy(&queue);                                                    \
    UNIT_TEST_RESULT(name##_queue_capacity, pass);                            \
}

#define UT_QUEUE_rest(name)                                                   \
static void                                                                   \
utest_##name##_queue_rest(void)                                               \
{                                                                             \
    bool pass;                                                                \
    struct QUEUE *queue;                                                      \
                                                                              \
    pass = true;                                                              \
    queue = NULL;                                                             \
                                                                              \
    RESULT_CHECK_uint32(QUEUE_REST_INVALID, QUEUE_rest(queue), &pass);        \
                                                                              \
    queue = QUEUE_create();                                                   \
    RESULT_CHECK_uint32(QUEUE_capacity(queue), QUEUE_rest(queue), &pass);     \
                                                                              \
    QUEUE_enter(queue, &pass);                                                \
    RESULT_CHECK_uint32(QUEUE_capacity(queue) - 1, QUEUE_rest(queue), &pass); \
                                                                              \
    QUEUE_destroy(&queue);                                                    \
    UNIT_TEST_RESULT(name##_queue_rest, pass);                                \
}

#define UT_QUEUE_full_p(name)                             \
static void                                               \
utest_##name##_queue_full_p(void)                         \
{                                                         \
    bool pass;                                            \
    struct QUEUE *queue;                                  \
                                                          \
    pass = true;                                          \
    queue = NULL;                                         \
                                                          \
    RESULT_CHECK_bool(true, QUEUE_full_p(queue), &pass);  \
                                                          \
    queue = QUEUE_create();                               \
    RESULT_CHECK_bool(false, QUEUE_full_p(queue), &pass); \
                                                          \
    while (!QUEUE_full_p(queue)) {                        \
        QUEUE_enter(queue, &pass);                        \
    }                                                     \
    RESULT_CHECK_bool(true, QUEUE_full_p(queue), &pass);  \
                                                          \
    QUEUE_destroy(&queue);                                \
    UNIT_TEST_RESULT(name##_queue_full_p, pass);          \
}

#define UT_QUEUE_empty_p(name)                             \
static void                                                \
utest_##name##_queue_empty_p(void)                         \
{                                                          \
    bool pass;                                             \
    struct QUEUE *queue;                                   \
                                                           \
    pass = true;                                           \
    queue = NULL;                                          \
                                                           \
    RESULT_CHECK_bool(false, QUEUE_empty_p(queue), &pass); \
                                                           \
    queue = QUEUE_create();                                \
    RESULT_CHECK_bool(true, QUEUE_empty_p(queue), &pass);  \
                                                           \
    while (!QUEUE_full_p(queue)) {                         \
        QUEUE_enter(queue, &pass);                         \
    }                                                      \
    RESULT_CHECK_bool(false, QUEUE_empty_p(queue), &pass); \
                                                           \
    QUEUE_destroy(&queue);                                 \
    UNIT_TEST_RESULT(name##_queue_empty_p, pass);          \
}

#define UT_QUEUE_enter(name)                                 \
static void                                                  \
utest_##name##_queue_enter(void)                             \
{                                                            \
    bool pass;                                               \
    uint32 rest;                                             \
    struct QUEUE *queue;                                     \
                                                             \
    pass = true;                                             \
    queue = NULL;                                            \
                                                             \
    QUEUE_enter(queue, NULL);                                \
    queue = QUEUE_create();                                  \
    rest = QUEUE_rest(queue);                                \
                                                             \
    QUEUE_enter(queue, &pass);                               \
    RESULT_CHECK_uint32(rest - 1, QUEUE_rest(queue), &pass); \
                                                             \
    while (!QUEUE_full_p(queue)) {                           \
        QUEUE_enter(queue, &pass);                           \
    }                                                        \
                                                             \
    rest = QUEUE_capacity(queue);                            \
    QUEUE_enter(queue, &pass);                               \
    RESULT_CHECK_uint32(rest - 1, QUEUE_rest(queue), &pass); \
                                                             \
    QUEUE_destroy(&queue);                                   \
    UNIT_TEST_RESULT(name##_queue_enter, pass);              \
}

#define UT_QUEUE_front(name)                                      \
static void                                                       \
utest_##name##_queue_front(void)                                  \
{                                                                 \
    bool pass;                                                    \
    void *tmp;                                                    \
    struct QUEUE *queue;                                          \
                                                                  \
    pass = true;                                                  \
    queue = NULL;                                                 \
                                                                  \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_front(queue), &pass); \
    queue = QUEUE_create();                                       \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_front(queue), &pass); \
                                                                  \
    QUEUE_enter(queue, &pass);                                    \
    RESULT_CHECK_pointer(&pass, QUEUE_front(queue), &pass);       \
                                                                  \
    tmp = QUEUE_front(queue);                                     \
    RESULT_CHECK_pointer(tmp, QUEUE_leave(queue), &pass);         \
                                                                  \
    while (1 != QUEUE_rest(queue)) {                              \
        QUEUE_enter(queue, &pass);                                \
    }                                                             \
    QUEUE_enter(queue, queue);                                    \
    RESULT_CHECK_pointer(queue, QUEUE_rear(queue), &pass);        \
                                                                  \
    QUEUE_destroy(&queue);                                        \
    UNIT_TEST_RESULT(name##_queue_front, pass);                   \
}

#define UT_QUEUE_rear(name)                                      \
static void                                                      \
utest_##name##_queue_rear(void)                                  \
{                                                                \
    bool pass;                                                   \
    void *tmp;                                                   \
    struct QUEUE *queue;                                         \
                                                                 \
    pass = true;                                                 \
    queue = NULL;                                                \
                                                                 \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_rear(queue), &pass); \
    queue = QUEUE_create();                                      \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_rear(queue), &pass); \
                                                                 \
    QUEUE_enter(queue, &pass);                                   \
    RESULT_CHECK_pointer(&pass, QUEUE_rear(queue), &pass);       \
                                                                 \
    tmp = QUEUE_rear(queue);                                     \
    RESULT_CHECK_pointer(tmp, QUEUE_leave(queue), &pass);        \
                                                                 \
    QUEUE_destroy(&queue);                                       \
    UNIT_TEST_RESULT(name##_queue_rear, pass);                   \
}

#define UT_QUEUE_leave(name)                                      \
static void                                                       \
utest_##name##_queue_leave(void)                                  \
{                                                                 \
    bool pass;                                                    \
    uint32 rest;                                                  \
    struct QUEUE *queue;                                          \
                                                                  \
    pass = true;                                                  \
    queue = NULL;                                                 \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_leave(queue), &pass); \
                                                                  \
    QUEUE_leave(queue);                                           \
    queue = QUEUE_create();                                       \
    RESULT_CHECK_pointer(PTR_INVALID, QUEUE_leave(queue), &pass); \
                                                                  \
    while (!QUEUE_full_p(queue)) {                                \
        QUEUE_enter(queue, &pass);                                \
    }                                                             \
                                                                  \
    rest = QUEUE_rest(queue);                                     \
    RESULT_CHECK_pointer(&pass, QUEUE_leave(queue), &pass);       \
    RESULT_CHECK_uint32(rest + 1, QUEUE_rest(queue), &pass);      \
                                                                  \
    QUEUE_destroy(&queue);                                        \
    UNIT_TEST_RESULT(name##_queue_leave, pass);                   \
}

#define UT_QUEUE_cleanup(name)                                            \
static void                                                               \
utest_##name##_queue_cleanup(void)                                        \
{                                                                         \
    bool pass;                                                            \
    struct QUEUE *queue;                                                  \
                                                                          \
    pass = true;                                                          \
    queue = NULL;                                                         \
                                                                          \
    QUEUE_cleanup(queue);                                                 \
    queue = QUEUE_create();                                               \
                                                                          \
    while (!QUEUE_full_p(queue)) {                                        \
        QUEUE_enter(queue, &pass);                                        \
    }                                                                     \
    QUEUE_cleanup(queue);                                                 \
    RESULT_CHECK_uint32(QUEUE_capacity(queue), QUEUE_rest(queue), &pass); \
                                                                          \
    QUEUE_destroy(&queue);                                                \
    UNIT_TEST_RESULT(name##_queue_cleanup, pass);                         \
}

#define UT_QUEUE_iterate(name)                    \
static void                                       \
utest_##name##_queue_iterate(void)                \
{                                                 \
    bool pass;                                    \
    struct QUEUE *queue;                          \
    uint32 capacity;                              \
    uint32 tmp;                                   \
                                                  \
    queue = QUEUE_create();                       \
    capacity = QUEUE_capacity(queue);             \
    pass = true;                                  \
    tmp = 0;                                      \
                                                  \
    QUEUE_iterate(NULL, queue_iterate_handler);   \
                                                  \
    while (!QUEUE_full_p(queue)) {                \
        QUEUE_enter(queue, &tmp);                 \
    }                                             \
                                                  \
    tmp = 0;                                      \
    QUEUE_iterate(queue, queue_iterate_handler);  \
    RESULT_CHECK_uint32(capacity, tmp, &pass);    \
                                                  \
    QUEUE_cleanup(queue);                         \
    QUEUE_iterate(queue, queue_iterate_handler);  \
                                                  \
    QUEUE_destroy(&queue);                        \
    UNIT_TEST_RESULT(name##_queue_iterate, pass); \
}

#endif

