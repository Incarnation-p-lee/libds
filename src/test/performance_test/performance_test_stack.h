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

#define PT_STACK_resize(name)                     \
static void                                       \
ptest_##name##_stack_resize(uint32 count)         \
{                                                 \
    struct STACK *stack;                          \
                                                  \
    stack = STACK_create();                       \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        STACK_resize(stack, count);               \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    STACK_destroy(&stack);                        \
    PERFORMANCE_TEST_RESULT(name##_stack_resize); \
}

#define PT_STACK_full_p(name)                     \
static void                                       \
ptest_##name##_stack_full_p(uint32 count)         \
{                                                 \
    struct STACK *stack;                          \
                                                  \
    stack = STACK_create();                       \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        STACK_full_p(stack);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    STACK_destroy(&stack);                        \
    PERFORMANCE_TEST_RESULT(name##_stack_full_p); \
}

#define PT_STACK_capacity(name)                     \
static void                                         \
ptest_##name##_stack_capacity(uint32 count)         \
{                                                   \
    struct STACK *stack;                            \
                                                    \
    stack = STACK_create();                         \
                                                    \
    PERFORMANCE_TEST_CHECKPOINT;                    \
                                                    \
    while (count--) {                               \
        STACK_capacity(stack);                      \
    }                                               \
                                                    \
    PERFORMANCE_TEST_ENDPOINT;                      \
                                                    \
    STACK_destroy(&stack);                          \
    PERFORMANCE_TEST_RESULT(name##_stack_capacity); \
}

#define PT_STACK_rest(name)                     \
static void                                     \
ptest_##name##_stack_rest(uint32 count)         \
{                                               \
    struct STACK *stack;                        \
                                                \
    stack = STACK_create();                     \
                                                \
    PERFORMANCE_TEST_CHECKPOINT;                \
                                                \
    while (count--) {                           \
        STACK_rest(stack);                      \
    }                                           \
                                                \
    PERFORMANCE_TEST_ENDPOINT;                  \
                                                \
    STACK_destroy(&stack);                      \
    PERFORMANCE_TEST_RESULT(name##_stack_rest); \
}

#define PT_STACK_push(name)                     \
static void                                     \
ptest_##name##_stack_push(uint32 count)         \
{                                               \
    struct STACK *stack;                        \
                                                \
    stack = STACK_create();                     \
                                                \
    PERFORMANCE_TEST_CHECKPOINT;                \
                                                \
    while (count--) {                           \
        STACK_push(stack, stack);               \
    }                                           \
                                                \
    PERFORMANCE_TEST_ENDPOINT;                  \
                                                \
    STACK_destroy(&stack);                      \
    PERFORMANCE_TEST_RESULT(name##_stack_push); \
}

#define PT_STACK_pop(name)                     \
static void                                    \
ptest_##name##_stack_pop(uint32 count)         \
{                                              \
    struct STACK *stack;                       \
                                               \
    stack = STACK_create();                    \
                                               \
    PERFORMANCE_TEST_CHECKPOINT;               \
                                               \
    while (count--) {                          \
        STACK_push(stack, stack);              \
        STACK_pop(stack);                      \
    }                                          \
                                               \
    PERFORMANCE_TEST_ENDPOINT;                 \
                                               \
    STACK_destroy(&stack);                     \
    PERFORMANCE_TEST_RESULT(name##_stack_pop); \
}

#define PT_STACK_empty_p(name)                     \
static void                                        \
ptest_##name##_stack_empty_p(uint32 count)         \
{                                                  \
    struct STACK *stack;                           \
                                                   \
    stack = STACK_create();                        \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        STACK_empty_p(stack);                      \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    STACK_destroy(&stack);                         \
    PERFORMANCE_TEST_RESULT(name##_stack_empty_p); \
}

#define PT_STACK_cleanup(name)                     \
static void                                        \
ptest_##name##_stack_cleanup(uint32 count)         \
{                                                  \
    struct STACK *stack;                           \
                                                   \
    stack = STACK_create();                        \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        STACK_push(stack, stack);                  \
        STACK_cleanup(stack);                      \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    STACK_destroy(&stack);                         \
    PERFORMANCE_TEST_RESULT(name##_stack_cleanup); \
}

#define PT_STACK_iterate(name)                        \
static void                                           \
ptest_##name##_stack_iterate(uint32 count)            \
{                                                     \
    struct STACK *stack;                              \
    sint32 reference;                                 \
                                                      \
    stack = STACK_create();                           \
    reference = 0u;                                   \
                                                      \
    while (!STACK_full_p(stack)) {                    \
        STACK_push(stack, &reference);                \
    }                                                 \
                                                      \
    PERFORMANCE_TEST_CHECKPOINT;                      \
                                                      \
    while (count--) {                                 \
        STACK_iterate(stack, &stack_iterate_handler); \
    }                                                 \
                                                      \
    PERFORMANCE_TEST_ENDPOINT;                        \
                                                      \
    STACK_destroy(&stack);                            \
    PERFORMANCE_TEST_RESULT(name##_stack_iterate);    \
}

#endif

