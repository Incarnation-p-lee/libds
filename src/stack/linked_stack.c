/*
 * _RETURN_ one instance of linked_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct linked_stack *
linked_stack_create(void)
{
    struct linked_stack *ptr;

    ptr = (struct linked_stack *)malloc_ds(sizeof(*ptr));
    if (!ptr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->index = 0;
        dlinked_list_initial(ptr->link);
    }

    ptr->stack = array_stack_create();

    return ptr;
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
