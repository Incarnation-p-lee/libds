#ifndef HAVE_DEFINED_PERFORMANCE_TEST_STACK_H
#define HAVE_DEFINED_PERFORMANCE_TEST_STACK_H

#define PT_STACK_create(name)                     \
static void                                       \
ptest_##name##_stack_create(uint32 count)         \
{                                                 \
    struct STACK *stack;                          \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        stack = STACK_create();                   \
        STACK_destroy(&stack);                    \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_stack_create); \
}

#define PT_STACK_destroy(name)                     \
static void                                        \
ptest_##name##_stack_destroy(uint32 count)         \
{                                                  \
    struct STACK *stack;                           \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        stack = STACK_create();                    \
        STACK_destroy(&stack);                     \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    PERFORMANCE_TEST_RESULT(name##_stack_destroy); \
}

#endif

