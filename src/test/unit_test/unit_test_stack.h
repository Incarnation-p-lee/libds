#ifndef HAVE_DEFINED_UNIT_TEST_STACK_H
#define HAVE_DEFINED_UNIT_TEST_STACK_H

#define UT_STACK_create(name)                           \
static void                                             \
utest_##name##_stack_create(void)                       \
{                                                       \
    bool pass;                                          \
    struct STACK *stack;                                \
                                                        \
    pass = true;                                        \
    stack = STACK_create();                             \
                                                        \
    RESULT_CHECK_uint32(0x0u, STACK_sid(stack), &pass); \
                                                        \
    RESULT_CHECK_uint32(DEFAULT_STACK_SPACE_SIZE,       \
        STACK_space_dim(stack), &pass);                 \
                                                        \
    STACK_destroy(&stack);                              \
    UNIT_TEST_RESULT(name##_stack_create, pass);        \
}

#define UT_STACK_destroy(name)                    \
static void                                       \
utest_##name##_stack_destroy(void)                \
{                                                 \
    bool pass;                                    \
    struct STACK *stack;                          \
                                                  \
    pass = true;                                  \
    stack = NULL;                                 \
                                                  \
    STACK_destroy(&stack);                        \
    RESULT_CHECK_pointer(NULL, stack, &pass);     \
                                                  \
    stack = STACK_create();                       \
    STACK_destroy(&stack);                        \
                                                  \
    RESULT_CHECK_pointer(NULL, stack, &pass);     \
    UNIT_TEST_RESULT(name##_stack_destroy, pass); \
}

#define UT_STACK_space_expand(name)                                         \
static void                                                                 \
utest_##name##_stack_space_expand(void)                                     \
{                                                                           \
    bool pass;                                                              \
    struct STACK *stack;                                                    \
    uint32 stk_size;                                                        \
                                                                            \
    pass = true;                                                            \
    stack = STACK_create();                                                 \
    stk_size = STACK_space_dim(stack);                                      \
                                                                            \
    STACK_space_expand(NULL, 0);                                            \
    STACK_space_expand(stack, 0);                                           \
    RESULT_CHECK_uint32(stk_size * 2 + 32u, STACK_space_dim(stack), &pass); \
                                                                            \
    stk_size = STACK_space_dim(stack);                                      \
    STACK_space_expand(stack, 1u);                                          \
    RESULT_CHECK_uint32(++stk_size, STACK_space_dim(stack), &pass);         \
                                                                            \
    stk_size = STACK_space_dim(stack);                                      \
    STACK_space_expand(stack, 0xffffffffu - stk_size + 1);                  \
    RESULT_CHECK_uint32(stk_size, STACK_space_dim(stack), &pass);           \
                                                                            \
    STACK_destroy(&stack);                                                  \
    UNIT_TEST_RESULT(name##_stack_space_expand, pass);                      \
}

#define UT_STACK_full_p(name)                             \
static void                                               \
utest_##name##_stack_full_p(void)                         \
{                                                         \
    bool pass;                                            \
    struct STACK *stack;                                  \
    void *mem;                                            \
    uint32 tmp;                                           \
                                                          \
    RESULT_CHECK_bool(true, STACK_full_p(NULL), &pass);   \
                                                          \
    stack = STACK_create();                               \
    pass = true;                                          \
    tmp = STACK_space_dim(stack);                         \
    mem = &tmp;                                           \
                                                          \
    RESULT_CHECK_bool(false, STACK_full_p(stack), &pass); \
                                                          \
    while (tmp) {                                         \
        STACK_push(stack, mem);                           \
        tmp--;                                            \
    }                                                     \
                                                          \
    RESULT_CHECK_bool(true, STACK_full_p(stack), &pass);  \
                                                          \
    STACK_destroy(&stack);                                \
    UNIT_TEST_RESULT(name##_stack_full_p, pass);          \
}

#define UT_STACK_capacity(name)                                          \
static void                                                              \
utest_##name##_stack_capacity(void)                                      \
{                                                                        \
    bool pass;                                                           \
    struct STACK *stack;                                                 \
    uint32 stk_size;                                                     \
    uint32 extra;                                                        \
                                                                         \
    RESULT_CHECK_uint32(0x0u, STACK_capacity(NULL), &pass);              \
                                                                         \
    pass = true;                                                         \
    stack = STACK_create();                                              \
                                                                         \
    stk_size = STACK_space_dim(stack);                                   \
    RESULT_CHECK_uint32(stk_size, STACK_capacity(stack), &pass);         \
                                                                         \
    extra = 1024u;                                                       \
    STACK_space_expand(stack, extra);                                    \
    RESULT_CHECK_uint32(stk_size + extra, STACK_capacity(stack), &pass); \
                                                                         \
    STACK_destroy(&stack);                                               \
    UNIT_TEST_RESULT(name##_stack_capacity, pass);                       \
}

#define UT_STACK_space_rest(name)                                       \
static void                                                             \
utest_##name##_stack_space_rest(void)                                   \
{                                                                       \
    bool pass;                                                          \
    struct STACK *stack;                                                \
    uint32 stk_size;                                                    \
                                                                        \
    RESULT_CHECK_uint32(0x0u, STACK_capacity(NULL), &pass);             \
                                                                        \
    pass = true;                                                        \
    stack = STACK_create();                                             \
    stk_size = STACK_capacity(stack);                                   \
                                                                        \
    RESULT_CHECK_uint32(stk_size, STACK_capacity(stack), &pass);        \
                                                                        \
    STACK_push(stack, &stk_size);                                       \
    RESULT_CHECK_uint32(stk_size, STACK_space_rest(stack) + 1u, &pass); \
                                                                        \
    STACK_destroy(&stack);                                              \
    UNIT_TEST_RESULT(name##_stack_space_rest, pass);                    \
}

#define UT_STACK_push(name)                                        \
static void                                                        \
utest_##name##_stack_push(void)                                    \
{                                                                  \
    bool pass;                                                     \
    struct STACK *stack;                                           \
    void *mem;                                                     \
    uint32 tmp;                                                    \
                                                                   \
    mem = &tmp;                                                    \
    pass = true;                                                   \
                                                                   \
    stack = STACK_create();                                        \
    tmp = STACK_space_dim(stack);                                  \
    STACK_push(NULL, mem);                                         \
                                                                   \
    while (tmp) {                                                  \
        STACK_push(stack, mem);                                    \
        tmp--;                                                     \
    }                                                              \
                                                                   \
    RESULT_CHECK_bool(true, STACK_full_p(stack), &pass);           \
                                                                   \
    tmp = STACK_space_dim(stack);                                  \
    STACK_push(stack, mem);                                        \
    RESULT_CHECK_uint32(tmp + 32u, STACK_space_dim(stack), &pass); \
                                                                   \
    STACK_push(stack, mem);                                        \
    STACK_pop(stack);                                              \
                                                                   \
    STACK_destroy(&stack);                                         \
    UNIT_TEST_RESULT(name##_stack_push, pass);                     \
}

#define UT_STACK_pop(name)                                \
static void                                               \
utest_##name##_stack_pop(void)                            \
{                                                         \
    bool pass;                                            \
    struct STACK *stack;                                  \
                                                          \
    stack = STACK_create();                               \
    pass = true;                                          \
                                                          \
    RESULT_CHECK_pointer(NULL, STACK_pop(NULL), &pass);   \
    RESULT_CHECK_pointer(NULL, STACK_pop(stack), &pass);  \
                                                          \
    STACK_push(stack, stack);                             \
    RESULT_CHECK_pointer(stack, STACK_pop(stack), &pass); \
                                                          \
    STACK_push(stack, stack);                             \
    STACK_pop(stack);                                     \
                                                          \
    STACK_destroy(&stack);                                \
    UNIT_TEST_RESULT(name##_stack_pop, pass);             \
}

#define UT_STACK_empty_p(name)                             \
static void                                                \
utest_##name##_stack_empty_p(void)                         \
{                                                          \
    bool pass;                                             \
    struct STACK *stack;                                   \
                                                           \
    RESULT_CHECK_bool(false, STACK_empty_p(NULL), &pass);  \
                                                           \
    stack = STACK_create();                                \
    pass = true;                                           \
                                                           \
    RESULT_CHECK_bool(true, STACK_empty_p(stack), &pass);  \
                                                           \
    STACK_push(stack, stack);                              \
    RESULT_CHECK_bool(false, STACK_empty_p(stack), &pass); \
                                                           \
    STACK_destroy(&stack);                                 \
    UNIT_TEST_RESULT(name##_stack_empty_p, pass);          \
}

#define UT_STACK_cleanup(name)                            \
static void                                               \
utest_##name##_stack_cleanup(void)                        \
{                                                         \
    bool pass;                                            \
    struct STACK *stack;                                  \
                                                          \
    STACK_cleanup(NULL);                                  \
                                                          \
    pass = true;                                          \
    stack = STACK_create();                               \
                                                          \
    STACK_push(stack, stack);                             \
    STACK_cleanup(stack);                                 \
    RESULT_CHECK_bool(true, STACK_empty_p(stack), &pass); \
                                                          \
    STACK_destroy(&stack);                                \
    UNIT_TEST_RESULT(name##_stack_cleanup, pass);         \
}

#define UT_STACK_iterate(name)                     \
static void                                        \
utest_##name##_stack_iterate(void)                 \
{                                                  \
    bool pass;                                     \
    struct STACK *stack;                           \
    sint32 *tmp;                                   \
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };   \
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, }; \
    register sint32 *d1;                           \
    register sint32 *e1;                           \
                                                   \
    stack = STACK_create();                        \
    pass = true;                                   \
                                                   \
    d1 = data;                                     \
    while (d1 < data + array_sizeof(data)) {       \
        STACK_push(stack, d1++);                   \
    }                                              \
                                                   \
    STACK_iterate(NULL, &stack_iterate_handler);   \
    STACK_iterate(stack, &stack_iterate_handler);  \
                                                   \
    e1 = expect;                                   \
    while (e1 < expect + array_sizeof(expect)) {   \
        tmp = STACK_pop(stack);                    \
        RESULT_CHECK_sint32(*e1, *tmp, &pass);     \
        e1++;                                      \
    }                                              \
                                                   \
    STACK_destroy(&stack);                         \
    UNIT_TEST_RESULT(name##_stack_iterate, pass);  \
}

#endif

