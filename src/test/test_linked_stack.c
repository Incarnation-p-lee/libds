static void
test_linked_stack_create(void)
{
    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    if (0 != stack->sid) {
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
test_linked_stack_expand_space(void)
{
    bool is_passed;
    struct linked_stack *stack;
    unsigned extra;
    unsigned capacity;

    stack = linked_stack_create();
    is_passed = true;
    extra = 1024;
    capacity = linked_stack_capacity(stack);

    linked_stack_expand_space(stack, extra);
    if (capacity + 1024 != linked_stack_capacity(stack)) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_expand_space), is_passed);
    return;
}

static void
test_linked_stack_is_full(void)
{
    bool is_passed;
    struct linked_stack *stack;
    int *data;
    register int *iter;
    unsigned capacity;

    stack = linked_stack_create();
    is_passed = true;
    capacity = linked_stack_capacity(stack);

    if (linked_stack_is_full(stack)) {
        is_passed = false;
    }

    data = malloc_ds(sizeof(int *) * capacity);
    iter = data;
    while (iter < data + capacity) {
        linked_stack_push(stack, iter++);
    }

    if (!linked_stack_is_full(stack)) {
        is_passed = false;
    }

    free_ds(data);
    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_is_full), is_passed);
    return;
}

static void
test_linked_stack_rest_space(void)
{
    bool is_passed;
    struct linked_stack *stack;
    unsigned capacity;

    stack = linked_stack_create();
    is_passed = true;

    capacity = linked_stack_capacity(stack);
    if (capacity != linked_stack_rest_space(stack)) {
        is_passed = false;
    }

    linked_stack_push(stack, &is_passed);
    if (capacity != linked_stack_rest_space(stack) + 1) {
        is_passed = false;
    }

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_rest_space), is_passed);
    return;
}

/*
 * Unit test pattern
static void
test_linked_stack_destroy(void)
{

    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    linked_stack_destroy(&stack);

    test_result_print(SYM_2_STR(linked_stack_create), is_passed);
    return;
}

*/
