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
        stack->sid = 0u;
    }

    /* struct linked_space */
    stack->base = malloc_ds(sizeof(*stack->base));
    if (!stack->base) {
        free_ds(stack);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        dlinked_list_initial(&stack->base->link);
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
        stack->base->space.sp = stack->base->space.bp;
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
linked_stack_expand_space(struct linked_stack *stack, uint32 dim)
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
                node->space.sp = node->space.bp;
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
    return 0u == linked_stack_rest_space(stack) ? true : false;
}

/*
 * _RETURN_ total space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
linked_stack_rest_space(struct linked_stack *stack)
{
    uint32 rest;
    struct linked_stack_space *st;

    rest = 0u;
    if (stack) {
        rest = linked_stack_space_node_rest_space(stack->top);
        st = linked_stack_space_next_node(stack->top);
        while (stack->base != st) {
            rest += st->space.dim;
            st = linked_stack_space_next_node(st);
        }
    }

    return rest;
}

/*
 * _RETURN_ capacity of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
linked_stack_capacity(struct linked_stack *stack)
{
    uint32 total;
    struct linked_stack_space *st;

    total = 0;
    if (stack) {
        st = stack->base;
        do {
            total += linked_stack_space_node_capacity(st);
            st = linked_stack_space_next_node(st);
        } while (st != stack->base);
    }

    return total;
}

/*
 * _RETURN_ rest space of specific node.
 *   If NULL _ARGV_, return 0.
 */
static inline uint32
linked_stack_space_node_capacity(struct linked_stack_space *node)
{
    return node ? node->space.dim : 0u;
}

/*
 * _RETURN_ rest space of specific node.
 *   If NULL _ARGV_, return 0.
 */
static inline uint32
linked_stack_space_node_rest_space(struct linked_stack_space *node)
{
    uint32 rest;
    void **limit;
    void **tmp;

    rest = 0;
    if (node) {
        tmp = node->space.sp;
        limit = (void **)node->space.bp + node->space.dim;
        if ((sint32)(tmp - limit) > 0) {
            pr_log_err("Array stack overflow.");
        } else {
            rest = (uint32)(limit - tmp);
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

        if (0 == linked_stack_space_node_rest_space(stack->top)) {
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
        if (0u == linked_stack_space_node_rest_space(stack->top)) {
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
linked_stack_is_empty(struct linked_stack *stack)
{
    bool is_empty;

    is_empty = false;
    if (stack) {
        if (stack->base != stack->top) {
            is_empty = false;
        } else if (stack->top->space.dim
            == linked_stack_space_node_rest_space(stack->top)) {
            is_empty = true;
        }
    }

    return is_empty;
}

/*
 * Clean up stack space. Discard all data in stack.
 *   If NULL _ARGV_, nothing will be done.  
 */
void
linked_stack_cleanup(struct linked_stack *stack)
{
    register struct linked_stack_space *iter;

    if (stack) {
        stack->top = stack->base;
        iter = stack->base;
        do {
            memset(iter->space.bp, 0, sizeof(void *) * iter->space.dim);
            iter->space.sp = (void **)iter->space.bp;
            iter = linked_stack_space_next_node(iter);
        } while (iter != stack->base);
    }

    return;
}

/*
 * Iterate each element of stack.
 *   If NULL stack, nothing will be done.
 */
void
linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *))
{
    register struct linked_stack_space *node;
    struct linked_stack_space *limit;

    if (stack && handler) {
        node = stack->top;
        limit = linked_stack_space_previous_node(stack->base);
        do {
            linked_stack_space_iterate_node(node, handler);
            node = linked_stack_space_next_node(node);
        } while (node != limit);

    }

    return;
}

/*
 * Iterate each element of specific node of linked stack space
 *   If NULL stack, nothing will be done.
 */
static inline void
linked_stack_space_iterate_node(struct linked_stack_space *node,
    void (*handler)(void *))
{
    register void **iter;

    if (node && handler) {
        /* iterate from sp to bp */
        iter = node->space.sp;
        while(iter != (void **)node->space.bp) {
            handler(*(--iter));
        }
    }

    return;
}
