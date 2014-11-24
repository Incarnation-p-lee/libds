/*
 * _RETURN_ one instance of array_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct array_stack *
array_stack_create(void)
{
    struct array_stack *ptr;

    ptr = malloc_ds(sizeof(*ptr));
    if (!ptr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->sid = 0u;
    }

    ptr->space.bp = malloc_ds(sizeof(void *) * DEFAULT_STACK_SPACE_SIZE);
    if (!ptr->space.bp) {
        free_ds(ptr);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->space.sp = ptr->space.bp;
        ptr->space.dim = DEFAULT_STACK_SPACE_SIZE;
    }

    return ptr;
}

/*
 * Destroy the instance of array stack.
 *   If NULL _ARGV_, nothing will be done.
 */
void
array_stack_destroy(struct array_stack **stack)
{
    if (stack && *stack) {
        free_ds((*stack)->space.bp);
        free_ds(*stack);
        *stack = NULL;
    }

    return;
}

/*
 * Expand the stack space if need.
 *   If NULL stack, nothing will be done.
 *   If extra is zero, expand to 2x + min.
 */
void
array_stack_expand_space(struct array_stack *stack, uint32 extra)
{
    uint32 new_size;
    void **new_addr;

    new_size = 0;
    new_addr = NULL;
    if (stack && extra) {
        new_size = stack->space.dim + extra;
    } else if (stack && !extra) {
        new_size = stack->space.dim * 2 + EXPAND_STACK_SPACE_MIN;
    }

    if (new_size) {
        new_addr = realloc_ds(stack->space.bp, sizeof(void *) * new_size);
        if (!new_addr) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            stack->space.bp = new_addr;
            stack->space.dim = new_size;
        }
    }

    return;
}

/*
 * _RETURN_ true if no space left in stack, or _RETURN_ false;
 *   If NULL _ARGV_, _RETURN_ false.
 */
bool
array_stack_is_full(struct array_stack *stack)
{
    return 0u == array_stack_rest_space(stack) ? true : false;
}

/*
 * _RETURN_ total space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_capacity(struct array_stack *stack)
{
    return stack ? stack->space.dim : 0u;
}

/*
 * _RETURN_ rest space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_rest_space(struct array_stack *stack)
{
    void **limit;
    void **tmp;
    uint32 rest;

    rest = 0;
    if (stack) {
        tmp = stack->space.sp;
        limit = stack->space.bp + stack->space.dim;
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
array_stack_push(struct array_stack *stack, void *member)
{
    if (stack) {
        if (array_stack_is_full(stack)) {
            array_stack_expand_space(stack, EXPAND_STACK_SPACE_MIN);
        }
        *stack->space.sp++ = member;
    }

    return;
}

/*
 * _RETURN_ one void pointer from stack
 *  If NULL _ARGV_, _RETURN_ NULL.
 */
void *
array_stack_pop(struct array_stack *stack)
{
    void *data;

    data = NULL;
    if (stack && !array_stack_is_empty(stack)) {
        data = *(--stack->space.sp);
    }

    return data;
}

/*
 * _RETURN_ true if empty stack, or _RETURN_ false.
 *  If NULL _ARGV_, _RETURN_ false.
 */
bool
array_stack_is_empty(struct array_stack *stack)
{
    bool is_empty;

    is_empty = false;
    if (stack) {
        if ((sint32)(stack->space.sp - stack->space.bp) < 0) {
            pr_log_err("Array stack overflow.");
        } else {
            is_empty = stack->space.bp == stack->space.sp ? true : false;
        }
    }

    return is_empty;
}

/*
 * Clean up stack space. Discard all data in stack.
 *   If NULL _ARGV_, nothing will be done.  
 */
void
array_stack_cleanup(struct array_stack *stack)
{
    if (stack) {
        memset(stack->space.bp, 0, sizeof(void *) * stack->space.dim);
        stack->space.sp = stack->space.bp;
    }

    return;
}

/*
 * Iterate each element of stack.
 *   If NULL stack, nothing will be done.
 */
void
array_stack_iterate(struct array_stack *stack, void (*handler)(void *))
{
    register void **iter;

    if (stack && handler) {
        /* iterate from sp to bp */
        iter = stack->space.sp;
        while(iter != stack->space.bp) {
            handler(*(--iter));
        }
    }

    return;
}
