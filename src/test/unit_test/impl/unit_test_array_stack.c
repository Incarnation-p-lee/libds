static void
unit_test_array_stack_create(void)
{
    bool is_passed;
    struct array_stack *ins;

    ins = array_stack_create();
    is_passed = true;

    if ((void*)ins->space.sp != ins->space.bp) {
        is_passed = false;
    }
    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_create), is_passed);
    return;
}

static void
unit_test_array_stack_destroy(void)
{
    bool is_passed;
    struct array_stack *ins;

    ins = array_stack_create();
    is_passed = true;

    array_stack_destroy(&ins);

    if (NULL != ins) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(array_stack_destroy), is_passed);
    return;
}

static void
unit_test_array_stack_space_expand(void)
{
    bool is_passed;
    struct array_stack *ins;
    uint32 stk_size;

    ins = array_stack_create();
    is_passed = true;
    stk_size = ins->space.dim;

    array_stack_space_expand(ins, 0);
    if (ins->space.dim != stk_size * 2 + 32) {
        is_passed = false;
    }

    stk_size = ins->space.dim;
    array_stack_space_expand(ins, 1024);
    if (ins->space.dim != stk_size + 1024) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_space_expand), is_passed);
    return;
}

static void
unit_test_array_stack_full_p(void)
{
    bool is_passed;
    struct array_stack *ins;
    void *mem;
    uint32 tmp;

    ins = array_stack_create();
    is_passed = true;
    tmp = ins->space.dim;
    mem = &tmp;

    if (false != array_stack_full_p(ins)) {
        is_passed = false;
    }

    while (tmp) {
        array_stack_push(ins, mem);
        tmp--;
    }

    if (true != array_stack_full_p(ins)) {
        is_passed = false;
    }
    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_full_p), is_passed);
    return;
}


static void
unit_test_array_stack_capacity(void)
{
    bool is_passed;
    struct array_stack *ins;
    uint32 stk_size;
    uint32 extra;

    ins = array_stack_create();
    stk_size = ins->space.dim;
    is_passed = true;

    if (stk_size != array_stack_capacity(ins)) {
        is_passed = false;
    }

    if (0 != array_stack_capacity(NULL)) {
        is_passed = false;
    }

    extra = 1024u;
    array_stack_space_expand(ins, extra);
    if (stk_size + extra != array_stack_capacity(ins)) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_capacity), is_passed);
    return;
}

static void
unit_test_array_stack_space_rest(void)
{
    bool is_passed;
    struct array_stack *ins;
    uint32 stk_size;

    ins = array_stack_create();
    stk_size = array_stack_capacity(ins);
    is_passed = true;

    if (stk_size != array_stack_space_rest(ins)) {
        is_passed = false;
    }

    array_stack_push(ins, &stk_size);
    if (stk_size != array_stack_space_rest(ins) + 1u) {
        is_passed = false;
    }

    if (0u != array_stack_space_rest(NULL)) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_space_rest), is_passed);
    return;
}

static void
unit_test_array_stack_push(void)
{
    bool is_passed;
    struct array_stack *ins;
    void *mem;
    uint32 tmp;

    ins = array_stack_create();
    is_passed = true;
    tmp = ins->space.dim;
    mem = &tmp;

    while (tmp) {
        array_stack_push(ins, mem);
        tmp--;
    }

    if (!array_stack_full_p(ins)) {
        is_passed = false;
    }

    tmp = (uint32)ins->space.dim;
    array_stack_push(ins, mem);
    if (tmp + 32u != ins->space.dim) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_push), is_passed);
    return;
}

static void
unit_test_array_stack_pop(void)
{
    bool is_passed;
    struct array_stack *ins;

    ins = array_stack_create();
    is_passed = true;

    if (NULL != array_stack_pop(ins)) {
        is_passed = false;
    }

    array_stack_push(ins, ins);
    if (ins != array_stack_pop(ins)) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_pop), is_passed);
    return;
}

static void
unit_test_array_stack_empty_p(void)
{
    bool is_passed;
    struct array_stack *ins;

    ins = array_stack_create();
    is_passed = true;

    if (false != array_stack_empty_p(NULL)) {
        is_passed = false;
    }

    if (true != array_stack_empty_p(ins)) {
        is_passed = false;
    }

    array_stack_push(ins, ins);
    if (false != array_stack_empty_p(ins)) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_empty_p), is_passed);
    return;
}

static void
unit_test_array_stack_cleanup(void)
{
    bool is_passed;
    struct array_stack *ins;

    ins = array_stack_create();
    is_passed = true;

    array_stack_push(ins, ins);
    array_stack_cleanup(ins);

    if (true != array_stack_empty_p(ins)) {
        is_passed = false;
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_cleanup), is_passed);
    return;
}

static void
unit_test_array_stack_iterate(void)
{
    bool is_passed;
    struct array_stack *ins;
    sint32 *tmp;
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, };
    register sint32 *d1;
    register sint32 *e1;

    ins = array_stack_create();
    is_passed = true;

    d1 = data;
    while (d1 < data + sizeof(data) / sizeof(data[0])) {
        array_stack_push(ins, d1++);
    }

    array_stack_iterate(ins, &stack_iterate_handler);

    e1 = expect;
    while (e1 < expect + sizeof(expect) / sizeof(expect[0])) {
        tmp = array_stack_pop(ins);
        if (*e1++ != *tmp) {
            is_passed = false;
            break;
        }
    }

    array_stack_destroy(&ins);

    test_result_print(SYM_2_STR(array_stack_iterate), is_passed);
    return;
}
