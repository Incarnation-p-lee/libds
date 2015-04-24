static void
unit_test_linked_stack_struct_field(void)
{
    bool pass;
    uint32 sid;
    struct linked_stack *stack;

    pass = true;
    sid = 0xfadeu;
    stack = linked_stack_create();

    linked_stack_sid_set(stack, sid);
    RESULT_CHECK_uint32(sid, linked_stack_sid(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_struct_field), pass);

    return;
}

static void
unit_test_linked_stack_create(void)
{
    bool pass;
    struct linked_stack *stack;

    pass = true;
    stack = linked_stack_create();

    RESULT_CHECK_uint32(0x0u, stack->sid, &pass);
    RESULT_CHECK_pointer(stack->base, stack->top, &pass);
    RESULT_CHECK_pointer((void *)stack->base->space.sp, stack->base->space.bp, &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_create), pass);

    return;
}

static void
unit_test_linked_stack_destroy(void)
{
    bool pass;
    struct linked_stack *stack;

    pass = true;
    stack = NULL;

    linked_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    stack = linked_stack_create();
    linked_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    test_result_print(SYM_2_STR(linked_stack_destroy), pass);

    return;
}

static void
unit_test_linked_stack_space_expand(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 extra;
    uint32 capacity;

    pass = true;
    extra = 1024u;
    stack = NULL;

    linked_stack_space_expand(stack, extra);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    stack = linked_stack_create();
    capacity = linked_stack_capacity(stack);

    linked_stack_space_expand(stack, extra);
    RESULT_CHECK_uint32(capacity + extra, linked_stack_capacity(stack), &pass);

    linked_stack_space_expand(stack, 0x0u);
    RESULT_CHECK_uint32(capacity + extra, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_space_expand), pass);

    return;
}

static void
unit_test_linked_stack_full_p(void)
{
    bool pass;
    struct linked_stack *stack;
    void *mem;
    uint32 tmp;

    stack = linked_stack_create();
    pass = true;
    tmp = linked_stack_capacity(stack);
    mem = &tmp;

    RESULT_CHECK_bool(true, linked_stack_full_p(NULL), &pass);
    RESULT_CHECK_bool(false, linked_stack_full_p(stack), &pass);

    while (tmp) {
        linked_stack_push(stack, mem);
        tmp--;
    }
    RESULT_CHECK_bool(true, linked_stack_full_p(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_full_p), pass);

    return;
}

static void
unit_test_linked_stack_space_rest(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 capacity;

    RESULT_CHECK_uint32(0x0u, linked_stack_space_rest(NULL), &pass);

    stack = linked_stack_create();
    pass = true;

    capacity = linked_stack_capacity(stack);
    RESULT_CHECK_uint32(capacity, linked_stack_space_rest(stack), &pass);

    linked_stack_push(stack, &pass);
    RESULT_CHECK_uint32(capacity, linked_stack_space_rest(stack) + 1, &pass);

    while (!linked_stack_full_p(stack)) {
        linked_stack_push(stack, &pass);
    }

    linked_stack_push(stack, &pass);
    linked_stack_pop(stack);
    linked_stack_pop(stack);
    RESULT_CHECK_uint32(EXPAND_STACK_SPACE_MIN + 1,
        linked_stack_space_rest(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_space_rest), pass);

    return;
}

static void
unit_test_linked_stack_capacity(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 stk_size;
    uint32 extra;

    pass = true;
    stack = linked_stack_create();
    stk_size = linked_stack_capacity(stack);

    RESULT_CHECK_uint32(0x0u, linked_stack_capacity(NULL), &pass);
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    extra = 1024u;
    linked_stack_space_expand(stack, extra);
    RESULT_CHECK_uint32(stk_size + extra, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_capacity), pass);

    return;
}

static void
unit_test_linked_stack_push(void)
{
    bool pass;
    struct linked_stack *stack;
    void *mem;
    uint32 tmp;

    mem = &tmp;
    pass = true;
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
    RESULT_CHECK_uint32(tmp + 32u, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_push), pass);

    return;
}

static void
unit_test_linked_stack_pop(void)
{
    bool pass;
    struct linked_stack *stack;

    stack = linked_stack_create();
    pass = true;

    RESULT_CHECK_pointer(NULL, linked_stack_pop(NULL), &pass);
    RESULT_CHECK_pointer(NULL, linked_stack_pop(stack), &pass);

    linked_stack_push(stack, stack);
    RESULT_CHECK_pointer(stack, linked_stack_pop(stack), &pass);

    while (!linked_stack_full_p(stack)) {
        linked_stack_push(stack, stack);
    }
    linked_stack_push(stack, stack);
    RESULT_CHECK_pointer(stack, linked_stack_pop(stack), &pass);
    RESULT_CHECK_pointer(stack, linked_stack_pop(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_pop), pass);

    return;
}

static void
unit_test_linked_stack_empty_p(void)
{
    bool pass;
    struct linked_stack *stack;

    stack = linked_stack_create();
    pass = true;

    RESULT_CHECK_bool(false, linked_stack_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    while (!linked_stack_full_p(stack)) {
        linked_stack_push(stack, &pass);
    }
    RESULT_CHECK_bool(false, linked_stack_empty_p(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_empty_p), pass);

    return;
}


static void
unit_test_linked_stack_cleanup(void)
{
    bool pass;
    struct linked_stack *stack;

    stack = linked_stack_create();
    pass = true;

    linked_stack_cleanup(NULL);

    linked_stack_push(stack, stack);
    linked_stack_cleanup(stack);

    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_cleanup), pass);

    return;
}

static void
unit_test_linked_stack_iterate(void)
{
    bool pass;
    struct linked_stack *stack;
    sint32 *tmp;
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, };
    register sint32 *d1;
    register sint32 *e1;

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
    test_result_print(SYM_2_STR(linked_stack_iterate), pass);

    return;
}

