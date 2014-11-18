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
    register struct linked_stack_space *node;

    if (stack && *stack) {
        node = (*stack)->base;
        while (node) {
            node = linked_stack_space_remove_node(node);
        }

        free_ds(*stack);
        *stack = NULL;
    }

    return;
}

/*
 * _RETURN_ next node of linked stack space.
 *   If NULL _ARGV_, _RETURN_ NULL
 */
static inline struct linked_stack_space *
linked_stack_space_next_node(struct linked_stack_space *node)
{
    struct linked_stack_space *next;
    struct doubly_linked_list *tmp;

    next = NULL;
    if (node) {
        tmp = dlinked_list_next_node(&node->link);
        if (tmp) {
            next = UNOFFSET_OF(tmp, struct linked_stack_space, link);
        }
    }

    return next;
}

/*
 * _RETURN_ previous node of linked stack space.
 *   If NULL _ARGV_, _RETURN_ NULL
 */
static inline struct linked_stack_space *
linked_stack_space_previous_node(struct linked_stack_space *node)
{
    struct linked_stack_space *previous;
    struct doubly_linked_list *tmp;

    previous = NULL;
    if (node) {
        tmp = dlinked_list_previous_node(&node->link);
        if (tmp) {
            previous = UNOFFSET_OF(tmp, struct linked_stack_space, link);
        }
    }

    return previous;
}

/*
 * _RETURN_ the next node of linked stack space
 *   If NULL _ARGV_, or last node, _RETURN_ NULL.
 */
static inline struct linked_stack_space *
linked_stack_space_remove_node(struct linked_stack_space *node)
{
    struct linked_stack_space *next;

    next = NULL;
    if (node) {
        dlinked_list_lazy_remove_node(&node->link);
        next = linked_stack_space_next_node(node);

        /* If only one node */
        if (next == node) {
            next = NULL;
        }

        free_ds(node->space.bp);
        free_ds(node);
    }

    return next;
}

void
linked_stack_expand_space(struct linked_stack *stack, unsigned dim)
{
    struct linked_stack_space *node;
    struct linked_stack_space *last;

    if (stack) {
        last = linked_stack_space_previous_node(stack->base);
        if (last) {
            node = malloc_ds(
        }
    }

    return;
}
