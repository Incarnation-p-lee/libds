static void
unit_test_linked_stack_struct_field(void)
{
    bool pass;
    uint32 sid;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x32345678u;
    pass = true;
    sid = 0xfadeu;
    stack = linked_stack_create();

    while (0 != loop--) {
        linked_stack_sid_set(stack, sid);
        RESULT_CHECK_uint32(sid, linked_stack_sid(stack), &pass);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_struct_field), pass);
}

static void
unit_test_linked_stack_create(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x2234567u;
    pass = true;

    stack = linked_stack_create();
    while (0 != loop--) {
        linked_stack_destroy(&stack);
        stack = linked_stack_create();
    }

    RESULT_CHECK_uint32(0x0u, stack->sid, &pass);
    RESULT_CHECK_pointer(stack->base, stack->top, &pass);
    RESULT_CHECK_pointer((void *)stack->base->space.sp, stack->base->space.bp, &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_create), pass);
}

static void
unit_test_linked_stack_destroy(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x2234567u;
    pass = true;
    stack = NULL;

    linked_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    while (0 != loop--) {
        stack = linked_stack_create();
        linked_stack_destroy(&stack);
    }

    RESULT_CHECK_pointer(NULL, stack, &pass);
    test_result_print(SYM_2_STR(linked_stack_destroy), pass);
}

static void
unit_test_linked_stack_space_expand(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 extra;
    uint32 capacity;
    uint32 loop;

    

    loop = 0x5234u;
    pass = true;
    extra = 1024u;
    stack = NULL;

    linked_stack_space_expand(stack, extra);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    stack = linked_stack_create();
    capacity = linked_stack_capacity(stack);

    extra = 1u;
    while (0 != loop--) {
        linked_stack_space_expand(stack, extra);
        RESULT_CHECK_uint32(capacity + extra, linked_stack_capacity(stack), &pass);
        capacity = linked_stack_capacity(stack);
    }

    linked_stack_space_expand(stack, 0x0u);
    RESULT_CHECK_uint32(capacity, linked_stack_capacity(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_space_expand), pass);
}

static void
unit_test_linked_stack_full_p(void)
{
    bool pass;
    struct linked_stack *stack;
    void *mem;
    uint32 tmp;
    uint32 loop;

    

    loop = 0xe234567u;
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

    while (0 != loop--) {
        RESULT_CHECK_bool(true, linked_stack_full_p(stack), &pass);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_full_p), pass);
}

static void
unit_test_linked_stack_space_rest(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 capacity;
    uint32 loop;

    

    RESULT_CHECK_uint32(0x0u, linked_stack_space_rest(NULL), &pass);

    loop = 0xe234567u;
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

    while (0 != loop--) {
        RESULT_CHECK_uint32(EXPAND_STACK_SPACE_MIN + 1,
            linked_stack_space_rest(stack), &pass);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_space_rest), pass);
}

static void
unit_test_linked_stack_capacity(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 stk_size;
    uint32 extra;
    uint32 loop;

    

    loop = 0xe234567u;
    pass = true;
    stack = linked_stack_create();
    stk_size = linked_stack_capacity(stack);

    RESULT_CHECK_uint32(0x0u, linked_stack_capacity(NULL), &pass);
    RESULT_CHECK_uint32(stk_size, linked_stack_capacity(stack), &pass);

    extra = 1024u;
    linked_stack_space_expand(stack, extra);
    while (0 != loop--) {
        RESULT_CHECK_uint32(stk_size + extra, linked_stack_capacity(stack), &pass);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_capacity), pass);
}

static void
unit_test_linked_stack_push(void)
{
    bool pass;
    struct linked_stack *stack;
    void *mem;
    uint32 tmp;
    uint32 loop;

    

    loop = 0x7234567u;
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

    linked_stack_space_expand(stack, loop);
    while (0 != loop--) {
        linked_stack_push(stack, mem);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_push), pass);
}

static void
unit_test_linked_stack_pop(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x7234567u;
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

    while (0 != loop--) {
        linked_stack_push(stack, stack);
        linked_stack_pop(stack);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_pop), pass);
}

static void
unit_test_linked_stack_empty_p(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x12345678u;
    stack = linked_stack_create();
    pass = true;

    RESULT_CHECK_bool(false, linked_stack_empty_p(NULL), &pass);
    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    while (!linked_stack_full_p(stack)) {
        linked_stack_push(stack, &pass);
    }

    while (0 != loop--) {
        RESULT_CHECK_bool(false, linked_stack_empty_p(stack), &pass);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_empty_p), pass);
}


static void
unit_test_linked_stack_cleanup(void)
{
    bool pass;
    struct linked_stack *stack;
    uint32 loop;

    

    loop = 0x4234567u;
    stack = linked_stack_create();
    pass = true;

    linked_stack_cleanup(NULL);

    while (0 != loop--) {
        linked_stack_push(stack, stack);
        linked_stack_cleanup(stack);
    }

    RESULT_CHECK_bool(true, linked_stack_empty_p(stack), &pass);

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_cleanup), pass);
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
    uint32 loop;

    

    loop = 0x12345678u;
    stack = linked_stack_create();
    pass = true;

    linked_stack_iterate(NULL, &stack_iterate_handler);

    d1 = data;
    while (d1 < data + array_sizeof(data)) {
        linked_stack_push(stack, d1++);
    }

    e1 = expect;
    linked_stack_iterate(stack, &stack_iterate_handler);
    while (e1 < expect + array_sizeof(expect)) {
        tmp = linked_stack_pop(stack);
        RESULT_CHECK_sint32(*e1, *tmp, &pass);
        e1++;
    }

    while (0 != loop--) {
        linked_stack_iterate(stack, &stack_iterate_handler);
    }

    linked_stack_destroy(&stack);
    test_result_print(SYM_2_STR(linked_stack_iterate), pass);
}

