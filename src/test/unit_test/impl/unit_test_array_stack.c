static void
unit_test_array_stack_struct_field(void)
{
    bool pass;
    uint32 sid;
    uint32 dim;
    uint32 tmp;
    struct array_stack *stack;

    pass = true;
    sid = 0xfadeu;
    dim = 0xdeadu;
    stack = array_stack_create();

    array_stack_sid_set(stack, sid);
    RESULT_CHECK_uint32(sid, array_stack_sid(stack), &pass);

    tmp = array_stack_space_dim(stack);
    array_stack_space_dim_set(stack, dim);
    RESULT_CHECK_uint32(dim, array_stack_space_dim(stack), &pass);
    array_stack_space_dim_set(stack, tmp);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_struct_field), pass);
}

static void
unit_test_array_stack_create(void)
{
    bool pass;
    struct array_stack *stack;

    pass = true;
    stack = array_stack_create();

    RESULT_CHECK_uint32(0x0u, array_stack_sid(stack), &pass);
    RESULT_CHECK_uint32(DEFAULT_STACK_SPACE_SIZE,
        array_stack_space_dim(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_create), pass);
}

static void
unit_test_array_stack_destroy(void)
{
    bool pass;
    struct array_stack *stack;

    pass = true;
    stack = NULL;

    array_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    stack = array_stack_create();
    array_stack_destroy(&stack);
    RESULT_CHECK_pointer(NULL, stack, &pass);

    unit_test_result_print(SYM_2_STR(array_stack_destroy), pass);
}

static void
unit_test_array_stack_space_expand(void)
{
    bool pass;
    struct array_stack *stack;
    uint32 stk_size;

    stack = array_stack_create();
    pass = true;
    stk_size = array_stack_space_dim(stack);

    array_stack_space_expand(NULL, 0);

    array_stack_space_expand(stack, 0);
    RESULT_CHECK_uint32(stk_size * 2 + 32u, array_stack_space_dim(stack), &pass);

    stk_size = array_stack_space_dim(stack);
    array_stack_space_expand(stack, 1u);
    RESULT_CHECK_uint32(++stk_size, array_stack_space_dim(stack), &pass);

    stk_size = array_stack_space_dim(stack);
    array_stack_space_expand(stack, 0xffffffffu - stk_size + 1);
    RESULT_CHECK_uint32(stk_size, array_stack_space_dim(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_space_expand), pass);
}

static void
unit_test_array_stack_full_p(void)
{
    bool pass;
    struct array_stack *stack;
    void *mem;
    uint32 tmp;

    RESULT_CHECK_bool(true, array_stack_full_p(NULL), &pass);

    stack = array_stack_create();
    pass = true;
    tmp = array_stack_space_dim(stack);
    mem = &tmp;

    RESULT_CHECK_bool(false, array_stack_full_p(stack), &pass);

    while (tmp) {
        array_stack_push(stack, mem);
        tmp--;
    }
    RESULT_CHECK_bool(true, array_stack_full_p(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_full_p), pass);
}


static void
unit_test_array_stack_capacity(void)
{
    bool pass;
    struct array_stack *stack;
    uint32 stk_size;
    uint32 extra;

    RESULT_CHECK_uint32(0x0u, array_stack_capacity(NULL), &pass);

    pass = true;
    stack = array_stack_create();
    stk_size = array_stack_space_dim(stack);

    RESULT_CHECK_uint32(stk_size, array_stack_capacity(stack), &pass);

    extra = 1024u;
    array_stack_space_expand(stack, extra);
    RESULT_CHECK_uint32(stk_size + extra, array_stack_capacity(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_capacity), pass);
}

static void
unit_test_array_stack_space_rest(void)
{
    bool pass;
    struct array_stack *stack;
    uint32 stk_size;

    RESULT_CHECK_uint32(0x0u, array_stack_capacity(NULL), &pass);

    pass = true;
    stack = array_stack_create();
    stk_size = array_stack_capacity(stack);

    RESULT_CHECK_uint32(stk_size, array_stack_capacity(stack), &pass);

    array_stack_push(stack, &stk_size);
    RESULT_CHECK_uint32(stk_size, array_stack_space_rest(stack) + 1u, &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_space_rest), pass);
}

static void
unit_test_array_stack_push(void)
{
    bool pass;
    struct array_stack *stack;
    void *mem;
    uint32 tmp;

    mem = &tmp;
    pass = true;
    stack = array_stack_create();
    tmp = array_stack_space_dim(stack);

    array_stack_push(NULL, mem);
    while (tmp) {
        array_stack_push(stack, mem);
        tmp--;
    }

    RESULT_CHECK_bool(true, array_stack_full_p(stack), &pass);

    tmp = array_stack_space_dim(stack);
    array_stack_push(stack, mem);
    RESULT_CHECK_uint32(tmp + 32u, array_stack_space_dim(stack), &pass);

    array_stack_push(stack, mem);
    array_stack_pop(stack);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_push), pass);
}

static void
unit_test_array_stack_pop(void)
{
    bool pass;
    struct array_stack *stack;

    stack = array_stack_create();
    pass = true;

    RESULT_CHECK_pointer(NULL, array_stack_pop(NULL), &pass);
    RESULT_CHECK_pointer(NULL, array_stack_pop(stack), &pass);

    array_stack_push(stack, stack);
    RESULT_CHECK_pointer(stack, array_stack_pop(stack), &pass);

    array_stack_push(stack, stack);
    array_stack_pop(stack);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_pop), pass);
}

static void
unit_test_array_stack_empty_p(void)
{
    bool pass;
    struct array_stack *stack;

    RESULT_CHECK_bool(false, array_stack_empty_p(NULL), &pass);

    stack = array_stack_create();
    pass = true;

    RESULT_CHECK_bool(true, array_stack_empty_p(stack), &pass);

    array_stack_push(stack, stack);
    RESULT_CHECK_bool(false, array_stack_empty_p(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_empty_p), pass);
}

static void
unit_test_array_stack_cleanup(void)
{
    bool pass;
    struct array_stack *stack;

    array_stack_cleanup(NULL);

    pass = true;
    stack = array_stack_create();

    array_stack_push(stack, stack);
    array_stack_cleanup(stack);
    RESULT_CHECK_bool(true, array_stack_empty_p(stack), &pass);

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_cleanup), pass);
}

static void
unit_test_array_stack_iterate(void)
{
    bool pass;
    struct array_stack *stack;
    sint32 *tmp;
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, };
    register sint32 *d1;
    register sint32 *e1;

    stack = array_stack_create();
    pass = true;

    d1 = data;
    while (d1 < data + array_sizeof(data)) {
        array_stack_push(stack, d1++);
    }

    array_stack_iterate(NULL, &stack_iterate_handler);
    array_stack_iterate(stack, &stack_iterate_handler);

    e1 = expect;
    while (e1 < expect + array_sizeof(expect)) {
        tmp = array_stack_pop(stack);
        RESULT_CHECK_sint32(*e1, *tmp, &pass);
        e1++;
    }

    array_stack_destroy(&stack);
    unit_test_result_print(SYM_2_STR(array_stack_iterate), pass);
}

