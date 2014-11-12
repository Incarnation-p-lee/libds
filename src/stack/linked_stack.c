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
        node = *stack;
        node = UNOFFSET_OF(dlinked_list_next_node(&node->link),
             struct linked_stack, link);
        while (*stack != node) {
            next = UNOFFSET_OF(dlinked_list_next_node(&node->link),
                struct linked_stack, link);
            array_stack_destroy(&next->stack);
            node = next;
        }


        *stack = NULL;
    }

    return;
}

static inline
linked_stack_next_node

