static void
performance_test_array_stack_struct_field(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_sid_set(stack, 0x32);
        array_stack_space_dim_set(stack, 0x43);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    performance_test_result_print(SYM_2_STR(array_stack_struct_field),
        performance_test_time_stamp_period());
}

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

    performance_test_result_print(SYM_2_STR(array_stack_create),
        performance_test_time_stamp_period());
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

    performance_test_result_print(SYM_2_STR(array_stack_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_array_stack_space_expand(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_space_expand(stack, 1u);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    performance_test_result_print(SYM_2_STR(array_stack_space_expand),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_full_p),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_capacity),
        performance_test_time_stamp_period());
}

static void
performance_test_array_stack_space_rest(uint32 count)
{
    struct array_stack *stack;

    stack = array_stack_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        array_stack_space_rest(stack);
    }

    PERFORMANCE_TEST_ENDPOINT;

    array_stack_destroy(&stack);
    performance_test_result_print(SYM_2_STR(array_stack_space_rest),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_push),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_pop),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_empty_p),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_cleanup),
        performance_test_time_stamp_period());
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
    performance_test_result_print(SYM_2_STR(array_stack_iterate),
        performance_test_time_stamp_period());
}

