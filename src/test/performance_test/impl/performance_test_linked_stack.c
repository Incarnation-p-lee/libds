static void
performance_test_linked_stack_struct_field(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_sid_set(stack, 0x32);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_struct_field);
}

static void
performance_test_linked_stack_create(uint32 count)
{
    struct linked_stack *stack;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stack = linked_stack_create();
        linked_stack_destroy(&stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(linked_stack_create);
}

static void
performance_test_linked_stack_destroy(uint32 count)
{
    struct linked_stack *stack;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stack = linked_stack_create();
        linked_stack_destroy(&stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(linked_stack_destroy);
}

static void
performance_test_linked_stack_space_expand(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_space_expand(stack, 1u);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_space_expand);
}

static void
performance_test_linked_stack_full_p(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_full_p(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_full_p);
}

static void
performance_test_linked_stack_space_rest(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_space_rest(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_space_rest);
}

static void
performance_test_linked_stack_capacity(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_capacity(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_capacity);
}

static void
performance_test_linked_stack_push(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_push(stack, stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_push);
}

static void
performance_test_linked_stack_pop(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_push(stack, stack);
        linked_stack_pop(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_pop);
}

static void
performance_test_linked_stack_empty_p(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_empty_p(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_empty_p);
}

static void
performance_test_linked_stack_cleanup(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_cleanup(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_cleanup);
}

static void
performance_test_linked_stack_iterate(uint32 count)
{
    struct linked_stack *stack;

    stack = linked_stack_create();
    while (linked_stack_full_p(stack)) {
        linked_stack_push(stack, stack);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        linked_stack_iterate(stack, &stack_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    linked_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(linked_stack_iterate);
}

