/*
 * _RETURN_ one instance of linked_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct linked_stack *
linked_stack_create(void)
{
    struct linked_stack *stack;

    /* struct linked_stack */
    stack = malloc_ds(sizeof(*stack));
    if (!stack) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        stack->sid = 0;
    }

    /* struct linked_space */
    stack->base = malloc_ds(sizeof(*stack->base));
    if (!stack->base) {
        free_ds(stack);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        dlinked_list_initial(&stack->base.link);
        stack->top = stack->base;
    }

    /* struct array_stack_space */
    stack->base->space.bp = malloc_ds(sizeof(void *) *
        DEFAULT_STACK_SPACE_SIZE);
    if (!stack->base->space.bp) {
        free_ds(stack->base);
        free_ds(stack);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        stack->base->space.dim = DEFAULT_STACK_SPACE_SIZE;
        stack->base->space.sp = (void **)stack->base->space.bp;
    }

    return stack;
}

/*
 * Destroy the instance of array stack.
 *   If NULL _ARGV_, nothing will be done.
 */
void
linked_stack_destroy(struct linked_stack **stack)
{
    register struct linked_stack *node;
    register struct linked_stack *next;

    if (stack && *stack) {
        node = linked_stack_next_node(*stack);
        while (*stack != node) {
            next = linked_stack_next_node(node);
            array_stack_destroy(&next->stack);
            free_ds(node);
            node = next;
        }
        /* destroy head node */
        array_stack_destroy(&node->stack);
        free_ds(node);
        *stack = NULL;
    }

    return;
}

void
linked_stack_destroy_node(struct linked_stack *node)
{
    if (node) {
        
    }

}

/*
 * _RETURN_ next node of linked stack.
 *   If NULL _ARGV_, _RETURN_ NULL.
 */
struct linked_stack *
linked_stack_next_node(struct linked_stack *node)
{
    struct linked_stack *next;

    next = NULL;
    if (node) {
        next = UNOFFSET_OF(dlinked_list_next_node(&node->link),
             struct linked_stack, link);
    }

    return next;
}

/*
 * _RETURN_ previous node of linked stack.
 *   If NULL _ARGV_, _RETURN_ NULL.
 */
struct linked_stack *
linked_stack_previous_node(struct linked_stack *node)
{
    struct linked_stack *prev;

    prev = NULL;
    if (node) {
        prev = UNOFFSET_OF(dlinked_list_previous_node(&node->link),
             struct linked_stack, link);
    }

    return prev;
}

/*
 * Expand one new node at the end of linked list.
 *   If NULL stack, nothing will be done.
 */
void
linked_stack_append_node(struct array_stack *stack)
{
    struct linked_stack *node;

    if (stack) {
        node = linked_stack_create();
        dlinked_list_insert_before(st
    }

}
