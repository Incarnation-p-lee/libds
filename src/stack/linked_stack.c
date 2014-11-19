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

/*
 * Add one node with _ARGV_ dim at the end of linked stack space.
 *   If invalid _ARGV_, nothing will be done.
 */
void
linked_stack_expand_space(struct linked_stack *stack, unsigned dim)
{
    struct linked_stack_space *node;
    struct linked_stack_space *last;

    if (stack && dim > 0) {
        last = linked_stack_space_previous_node(stack->base);
        if (last) {
            node = malloc_ds(sizeof(*node));
            if (!node) {
                pr_log_err("Fail to get memory from system.\n");
            } else {
                dlinked_list_initial(&node->link);
            }

            node->space.bp = malloc_ds(sizeof(void *) * dim);
            if (!node->space.bp) {
                free_ds(node);
                pr_log_err("Fail to get memory from system.\n");
            } else {
                node->space.dim = dim;
                node->space.sp = (void **)node->space.bp;
                dlinked_list_insert_after(&last->link, &node->link);
            }
        }
    }

    return;
}

/*
 * _RETURN_ true if no space left in stack, or _RETURN_ false;
 *   If NULL _ARGV_, _RETURN_ false.
 */
bool
linked_stack_is_full(struct linked_stack *stack)
{
    return 0 == linked_stack_rest_space(stack) ? true : false;
}

/*
 * _RETURN_ rest space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
unsigned
linked_stack_rest_space(struct linked_stack *stack)
{
    unsigned rest;
    struct linked_stack_sapce *st;

    rest = 0;
    if (stack) {
        rest = linked_stack_sapce_node_rest_space(stack->top);
        st = linked_stack_space_next_node(stack->top);
        while (stack->base != st) {
            rest += st->space.dim;
            st = linked_stack_space_next_node(st);
        }
    }

    return rest;
}

/*
 * _RETURN_ rest space of specific node.
 *   If NULL _ARGV_, return 0.
 */
static inline unsigned
linked_stack_sapce_node_rest_space(struct linked_stack_sapce *node)
{
    unsigned rest;
    void *limit;
    void *tmp;

    rest = 0;
    if (node) {
        tmp = (void *)stack->space.sp;
        limit = stack->space.bp + stack->space.dim;
        if ((signed)(tmp - limit) > 0) {
            pr_log_err("Array stack overflow.");
        } else {
            rest = (unsigned)(limit - tmp);
        }
    }

    return rest;
}

/*
 * Push one void pointer to stack
 *   If NULL stack, nothing will be done.
 */
void
linked_stack_push(struct linked_stack *stack, void *member)
{
    if (stack) {
        if (linked_stack_is_full(stack)) {
            linked_stack_expand_space(stack, EXPAND_STACK_SPACE_MIN);
        }

        if (!linked_stack_sapce_node_rest_space(stack->top)) {
            stack->top = linked_stack_space_next_node(stack->top);
        }

        *stack->top->space.sp++ = member;
    }

    return;
}

/*
 * _RETURN_ one void pointer from stack
 *  If NULL _ARGV_, _RETURN_ NULL.
 */
void *
linked_stack_pop(struct linked_stack *stack)
{
    void *data;

    data = NULL;
    if (stack && !linked_stack_is_empty(stack)) {
        if (!linked_stack_sapce_node_rest_space(stack->top)) {
            stack->top = linked_stack_space_previous_node(stack->top);
            data = *(--stack->top->space.sp);
        }
    }

    return data;
}

/*
 * _RETURN_ true if empty stack, or _RETURN_ false.
 *  If NULL _ARGV_, _RETURN_ false.
 */
bool
linked_stack_is_empty(struct array_stack *stack)
{
    void *tmp;
    bool is_empty;

    is_empty = false;
    if (stack) {
        if (stack->base != stack->top) {
            is_empty = false;
        } else if (stack->top->space.dim ==
                linked_stack_sapce_node_rest_space(stack->top)) {
                is_empty = true;
            }
        }
    }

    return is_empty;
}

