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
test_linked_stack_expand_space(void)
{
    bool is_passed;
    struct linked_stack *stack;
    uint32 extra;
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;
    extra = 1024u;
    capacity = linked_stack_capacity(stack);

    linked_stack_expand_space(stack, extra);
    if (capacity + extra != linked_stack_capacity(stack)) {
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
    sint32 *data;
    register sint32 *iter;
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;
    capacity = linked_stack_capacity(stack);

    if (linked_stack_is_full(stack)) {
        is_passed = false;
    }

    data = malloc_ds(sizeof(sint32 *) * capacity);
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
    uint32 capacity;

    stack = linked_stack_create();
    is_passed = true;

    capacity = linked_stack_capacity(stack);
    if (capacity != linked_stack_rest_space(stack)) {
        is_passed = false;
    }

    linked_stack_push(stack, &is_passed);
    if (capacity != linked_stack_rest_space(stack) + 1u) {
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
