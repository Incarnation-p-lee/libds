static inline void
utest_linked_stack_create(void)
{
    bool pass;
    s_linked_stack_t *stack;

    pass = true;
    UNIT_TEST_BEGIN(linked_stack_create);
    stack = linked_stack_create();

    RESULT_CHECK_bool(true, linked_stack_structure_legal_p(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_create, pass);
}

static inline void
utest_linked_stack_destroy(void)
{
    bool pass;
    s_linked_stack_t *stack;

    pass = true;
    stack = NULL;
    UNIT_TEST_BEGIN(linked_stack_destroy);

    linked_stack_destroy(NULL);
    linked_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    stack = linked_stack_create();
    linked_stack_destroy(&stack);

    RESULT_CHECK_pointer(NULL, stack, &pass);
    UNIT_TEST_RESULT(linked_stack_destroy, pass);
}

static inline void
utest_linked_stack_resize(void)
{
    bool pass;
    uint32 stk_size;
    s_linked_stack_t *stack;

    pass = true;
    UNIT_TEST_BEGIN(linked_stack_resize);
    stack = linked_stack_create();
    stk_size = linked_stack_capacity(stack);

    linked_stack_resize(NULL, 0);
    linked_stack_resize(stack, 0);

    stk_size = stk_size * 2 + STACK_EXPD_SIZE_MIN;
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    stk_size = linked_stack_capacity(stack);
    linked_stack_resize(stack, stk_size + 1);
    RESULT_CHECK_uint32(++stk_size, linked_stack_capacity(stack), &pass);

    stk_size = linked_stack_capacity(stack);
    linked_stack_resize(stack, stk_size);
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    stk_size = 1u;
    linked_stack_resize(stack, stk_size);
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_resize, pass);
}

static inline void
utest_linked_stack_full_p(void)
{
    bool pass;
    void *mem;
    uint32 tmp;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_full_p);
    RESULT_CHECK_bool(true, linked_stack_full_p(NULL), &pass);

    stack = linked_stack_create();
    pass = true;
    tmp = linked_stack_capacity(stack);
    mem = &tmp;

    RESULT_CHECK_bool(false, linked_stack_full_p(stack), &pass);

    while (tmp) {
        linked_stack_push(stack, mem);
        tmp--;
    }

    RESULT_CHECK_bool(true, linked_stack_full_p(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_full_p, pass);
}

static inline void
utest_linked_stack_capacity(void)
{
    bool pass;
    uint32 extra;
    uint32 stk_size;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_capacity);
    RESULT_CHECK_uint32(STACK_SIZE_INVALID, linked_stack_capacity(NULL), &pass);

    pass = true;
    stack = linked_stack_create();

    stk_size = linked_stack_capacity(stack);
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    extra = 1024u;
    linked_stack_resize(stack, extra + stk_size);
    RESULT_CHECK_uint32(stk_size + extra, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_capacity, pass);
}

static inline void
utest_linked_stack_rest(void)
{
    bool pass;
    uint32 rest;
    uint32 stk_size;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_rest);
    RESULT_CHECK_uint32(STACK_SIZE_INVALID, linked_stack_capacity(NULL), &pass);

    pass = true;
    stack = linked_stack_create();
    stk_size = linked_stack_capacity(stack);

    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    linked_stack_push(stack, &stk_size);
    RESULT_CHECK_uint32(stk_size, linked_stack_rest(stack) + 1u, &pass);

    rest = linked_stack_rest(stack);
    stk_size += rest * 4;
    linked_stack_resize(stack, stk_size);
    RESULT_CHECK_uint32(rest * 4 + rest, linked_stack_rest(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_rest, pass);
}

static inline void
utest_linked_stack_push(void)
{
    bool pass;
    void *mem;
    uint32 tmp;
    s_linked_stack_t *stack;

    mem = &tmp;
    pass = true;

    UNIT_TEST_BEGIN(linked_stack_push);
    stack = linked_stack_create();
    tmp = linked_stack_capacity(stack);
    linked_stack_push(NULL, mem);

    while (tmp) {
        linked_stack_push(stack, mem);
        tmp--;
    }

    RESULT_CHECK_bool(true, linked_stack_full_p(stack), &pass);

    tmp = linked_stack_capacity(stack);
    linked_stack_push(stack, mem);

    tmp = tmp * 2 + STACK_EXPD_SIZE_MIN;
    RESULT_CHECK_uint32(tmp, linked_stack_capacity(stack), &pass);

    linked_stack_push(stack, mem);
    linked_stack_pop(stack);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_push, pass);
}

static inline void
utest_linked_stack_pop(void)
{
    uint32 i;
    bool pass;
    uint32 count;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_pop);
    stack = linked_stack_create();
    pass = true;
    count = 0x1234;

    RESULT_CHECK_pointer(PTR_INVALID, linked_stack_pop(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, linked_stack_pop(stack), &pass);

    linked_stack_push(stack, stack);
    RESULT_CHECK_pointer(stack, linked_stack_pop(stack), &pass);

    i = 0;
    while (i++ < count) {
        linked_stack_push(stack, stack);
    }

    i = 0;
    while (i++ < count) {
        RESULT_CHECK_pointer(stack, linked_stack_pop(stack), &pass);
    }

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_pop, pass);
}

static inline void
utest_linked_stack_top(void)
{
    uint32 i;
    bool pass;
    void *tmp;
    uint32 count;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_top);
    stack = linked_stack_create();
    pass = true;
    count = 0x1c4e;

    RESULT_CHECK_pointer(PTR_INVALID, linked_stack_top(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, linked_stack_top(stack), &pass);

    tmp = linked_stack_top(stack);
    RESULT_CHECK_pointer(tmp, linked_stack_pop(stack), &pass);

    linked_stack_push(stack, stack);

    i = 0;
    while (i++ < count) {
        linked_stack_push(stack, stack);
    }

    i = 0;
    while (i++ < count) {
        tmp = linked_stack_top(stack);
        RESULT_CHECK_pointer(tmp, linked_stack_pop(stack), &pass);
    }

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_top, pass);
}

static inline void
utest_linked_stack_empty_p(void)
{
    bool pass;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_empty_p);
    RESULT_CHECK_bool(false, linked_stack_empty_p(NULL), &pass);

    stack = linked_stack_create();
    pass = true;

    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    linked_stack_push(stack, stack);
    RESULT_CHECK_bool(false, linked_stack_empty_p(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_empty_p, pass);
}

static inline void
utest_linked_stack_cleanup(void)
{
    bool pass;
    s_linked_stack_t *stack;

    UNIT_TEST_BEGIN(linked_stack_cleanup);
    linked_stack_cleanup(NULL);

    pass = true;
    stack = linked_stack_create();

    linked_stack_push(stack, stack);
    linked_stack_cleanup(stack);
    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_cleanup, pass);
}

static inline void
utest_linked_stack_iterate(void)
{
    bool pass;
    s_linked_stack_t *stack;
    sint32 *tmp;
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, };
    register sint32 *d1;
    register sint32 *e1;

    UNIT_TEST_BEGIN(linked_stack_iterate);
    stack = linked_stack_create();
    pass = true;

    d1 = data;
    while (d1 < data + array_sizeof(data)) {
        linked_stack_push(stack, d1++);
    }

    linked_stack_iterate(NULL, &stack_iterate_handler);
    linked_stack_iterate(stack, &stack_iterate_handler);

    e1 = expect;
    while (e1 < expect + array_sizeof(expect)) {
        tmp = linked_stack_pop(stack);
        RESULT_CHECK_sint32(*e1, *tmp, &pass);
        e1++;
    }

    linked_stack_destroy(&stack);
    UNIT_TEST_RESULT(linked_stack_iterate, pass);
}

