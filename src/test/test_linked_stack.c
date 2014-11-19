static void
test_linked_stack_create(void)
{
    bool is_passed;
    struct linked_stack *stack;

    stack = linked_stack_create();
    is_passed = true;

    if (0 != stack->sid) {
        is_passed = false
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
