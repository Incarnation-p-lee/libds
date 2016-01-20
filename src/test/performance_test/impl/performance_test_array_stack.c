static void
performance_test_array_stack_create(uint32 count)
{
    struct array_stack *stack;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stack = array_stack_create();
        array_stack_destroy(&stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(array_stack_create);
}

static void
performance_test_array_stack_destroy(uint32 count)
{
    struct array_stack *stack;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        stack = array_stack_create();
        array_stack_destroy(&stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(array_stack_destroy);
}

static void
performance_test_array_stack_resize(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_resize(stack, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_resize);
}

static void
performance_test_array_stack_full_p(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_full_p(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_full_p);
}

static void
performance_test_array_stack_capacity(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_capacity(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_capacity);
}

static void
performance_test_array_stack_space_rest(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_rest(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_space_rest);
}

static void
performance_test_array_stack_push(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_push(stack, stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_push);
}

static void
performance_test_array_stack_pop(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_push(stack, stack);
        array_stack_pop(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_pop);
}

static void
performance_test_array_stack_empty_p(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_empty_p(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_empty_p);
}

static void
performance_test_array_stack_cleanup(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_push(stack, stack);
        array_stack_cleanup(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_cleanup);
}

static void
performance_test_array_stack_iterate(uint32 count)
{
    struct array_stack *stack;
    sint32 reference;

    stack = array_stack_create();
    reference = 0u;

    while (!array_stack_full_p(stack)) {
        array_stack_push(stack, &reference);
    }

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_iterate(stack, &stack_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    PERFORMANCE_TEST_RESULT(array_stack_iterate);
}

