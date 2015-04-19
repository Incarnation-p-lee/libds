static void
test_linked_stack_create(void)
{
    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    if (0u != stack->sid) {
        is_passed = false;
    } else if (!stack->base || stack->base != stack->top) {
        is_passed = false;
    } else if (stack->base->link.next != &stack->base->link
        || stack->base->link.next != stack->base->link.previous) {
        is_passed = false;
    } else if ((void *)stack->base->space.sp != stack->base->space.bp) {
        is_passed = false;
    }
    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_create), is_passed);
    return;
}

static void
test_linked_stack_destroy(void)
{

    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    linked_stack_destroy(&stack);

    if (stack) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(linked_stack_destroy), is_passed);
    return;
}

static void
test_linked_stack_space_expand(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 extra;
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;
    extra = 1024u;
    capacity = linked_stack_capacity(stack);

    linked_stack_space_expand(stack, extra);
    if (capacity + extra != linked_stack_capacity(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_space_expand), is_passed);
    return;
}

static void
test_linked_stack_full_p(void)
{
    bool is_passed;
    struct linked_stack *stack;
    sint32 *data;
    register sint32 *iter;
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;
    capacity = linked_stack_capacity(stack);

    if (linked_stack_full_p(stack)) {
        is_passed = false;
    }

    data = malloc_ds(sizeof(sint32 *) * capacity);
    iter = data;
    while (iter < data + capacity) {
        linked_stack_push(stack, iter++);
    }

    if (!linked_stack_full_p(stack)) {
        is_passed = false;
    }

    free_ds(data);
    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_full_p), is_passed);
    return;
}

static void
test_linked_stack_space_rest(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;

    capacity = linked_stack_capacity(stack);
    if (capacity != linked_stack_space_rest(stack)) {
        is_passed = false;
    }

    linked_stack_push(stack, &is_passed);
    if (capacity != linked_stack_space_rest(stack) + 1u) {
        is_passed = false;
    }

    while (!linked_stack_full_p(stack)) {
        linked_stack_push(stack, &is_passed);
    }

    linked_stack_push(stack, &is_passed);
    linked_stack_pop(stack);
    linked_stack_pop(stack);
    if (EXPAND_STACK_SPACE_MIN + 1 != linked_stack_space_rest(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_space_rest), is_passed);
    return;
}

static void
test_linked_stack_capacity(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 capacity;
    uint32 extra;

    stack = linked_stack_create();
    is_passed = true;

    if (0 != linked_stack_capacity(NULL)) {
        is_passed = false;
    }

    extra = 1023u;
    capacity = linked_stack_capacity(stack);
    linked_stack_space_expand(stack, extra);
    if (capacity + extra != linked_stack_capacity(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_capacity), is_passed);
    return;
}

static void
test_linked_stack_push(void)
{
    bool is_passed;
    uint32 capacity;
    uint32 tmp;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;
    capacity = linked_stack_capacity(stack);
    tmp = capacity;

    while (tmp > 0) {
        linked_stack_push(stack, &is_passed);
        tmp--;
        if (tmp != linked_stack_space_rest(stack)) {
            is_passed = false;
        }
    }

    if (!linked_stack_full_p(stack)) {
        is_passed = false;
    }

    linked_stack_push(stack, &is_passed);
    if (capacity + EXPAND_STACK_SPACE_MIN != linked_stack_capacity(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_push), is_passed);
    return;
}

static void
test_linked_stack_pop(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 mark;

    stack = linked_stack_create();
    is_passed = true;
    mark = 0xAD;

    if (NULL != linked_stack_pop(stack)) {
        is_passed = false;
    }

    linked_stack_push(stack, &mark);
    if (&mark != linked_stack_pop(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_pop), is_passed);
    return;
}

static void
test_linked_stack_empty_p(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 tmp;

    stack = linked_stack_create();
    is_passed = true;

    if (!linked_stack_empty_p(stack)) {
        is_passed = false;
    }

    tmp = linked_stack_capacity(stack);
    while (tmp > 0) {
        linked_stack_push(stack, &is_passed);
        tmp--;
    }
    if (linked_stack_empty_p(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_empty_p), is_passed);
    return;
}


static void
test_linked_stack_cleanup(void)
{
    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    linked_stack_push(stack, &is_passed);
    if (linked_stack_empty_p(stack)) {
        is_passed = false;
    }

    linked_stack_cleanup(stack);
    if (!linked_stack_empty_p(stack)) {
        is_passed = false;
    }

    if (stack->base != stack->top) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_cleanup), is_passed);
    return;
}

static void
test_linked_stack_iterate(void)
{
    bool is_passed;
    struct linked_stack *stack;
    sint32 data[] = {0xA, 0xB, 0xC, 0xD, 0xE, };
    sint32 expect[] = {0xF, 0xE, 0xD, 0xC, 0xB, };
    register sint32 *d1;
    register sint32 *e1;
    sint32 *tmp;

    stack = linked_stack_create();
    is_passed = true;

    d1 = data;
    while (d1 < data + sizeof(data) / sizeof(data[0])) {
        linked_stack_push(stack, d1++);
    }

    linked_stack_iterate(stack, &stack_iterate_handler);

    e1 = expect;
    while (e1 < expect + sizeof(expect) / sizeof(expect[0])) {
        tmp = linked_stack_pop(stack);
        if (*e1++ != *tmp) {
            is_passed = false;
            break;
        }
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_iterate), is_passed);
    return;
}

