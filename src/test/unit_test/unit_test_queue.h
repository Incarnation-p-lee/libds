#ifndef HAVE_DEFINED_UNIT_TEST_QUEUE_H
#define HAVE_DEFINED_UNIT_TEST_QUEUE_H

#define UT_QUEUE_create(name)                                \
static void                                                  \
utest_##name##_queue_create(void)                            \
{                                                            \
    bool pass;                                               \
    uint32 capacity;                                         \
    struct QUEUE *queue;                                     \
                                                             \
    pass = true;                                             \
    queue = QUEUE_create();                                  \
                                                             \
    capacity = QUEUE_capacity(queue);                        \
    RESULT_CHECK_uint32(capacity, QUEUE_dim(queue), &pass);  \
    RESULT_CHECK_uint32(capacity, QUEUE_rest(queue), &pass); \
                                                             \
    QUEUE_destroy(&queue);                                   \
    UNIT_TEST_RESULT(name##_queue_create, pass);             \
}

#endif

