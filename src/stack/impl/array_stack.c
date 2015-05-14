/*
 * _RETURN_ one instance of array_stack.  *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct array_stack *
array_stack_create(void)
{
    struct array_stack *ptr;

    ptr = malloc_ds(sizeof(*ptr));
    if (!ptr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        array_stack_sid_set(ptr, 0x0u);
    }

    ptr->space.bp = malloc_ds(sizeof(void *) * DEFAULT_STACK_SPACE_SIZE);
    if (!ptr->space.bp) {
        free_ds(ptr);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->space.sp = ptr->space.bp;
        array_stack_space_dim_set(ptr, DEFAULT_STACK_SPACE_SIZE);
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
    if (!stack || !*stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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
array_stack_space_expand(struct array_stack *stack, uint32 extra)
{
    uint32 new_size;
    ptrdiff_t offset;
    void **new_addr;

    new_size = 0;
    new_addr = NULL;
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return;
    } else if (!extra) {
        new_size = stack->space.dim * 2 + EXPAND_STACK_SPACE_MIN;
        pr_log_info("Expanding size not specified, use default.\n");
    } else {
        new_size = stack->space.dim + extra;
    }

    if (!new_size) {
        pr_log_warn("Expanding size overflow, nothing will be done.\n");
    } else {
        offset = (ptrdiff_t)(stack->space.sp - stack->space.bp);
        new_addr = realloc_ds(stack->space.bp, sizeof(void *) * new_size);
        if (!new_addr) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            stack->space.bp = new_addr;
            stack->space.sp = stack->space.bp + offset;
            array_stack_space_dim_set(stack, new_size);
        }
    }

    return;
}

/*
 * _RETURN_ true if no space left in stack, or _RETURN_ false;
 *   If NULL _ARGV_, _RETURN_ true.
 */
bool
array_stack_full_p(struct array_stack *stack)
{
    return 0u == array_stack_space_rest(stack) ? true : false;
}

/*
 * _RETURN_ total space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_capacity(struct array_stack *stack)
{
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0u;
    } else {
        return array_stack_space_dim(stack);
    }
}

/*
 * _RETURN_ rest space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_space_rest(struct array_stack *stack)
{
    void **limit;
    void **tmp;
    uint32 rest;

    rest = 0;
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = stack->space.sp;
        limit = stack->space.bp + stack->space.dim;
        if ((sint32)(tmp - limit) > 0) {
            pr_log_err("Array stack overflow.\n");
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
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (array_stack_full_p(stack)) {
            pr_log_info("Stack is full, expand stack with default size.\n");
            array_stack_space_expand(stack, EXPAND_STACK_SPACE_MIN);
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
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (array_stack_empty_p(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
    } else {
        data = *(--stack->space.sp);
    }

    return data;
}

/*
 * _RETURN_ true if empty stack, or _RETURN_ false.
 *  If NULL _ARGV_, _RETURN_ false.
 */
bool
array_stack_empty_p(struct array_stack *stack)
{
    bool is_empty;

    is_empty = false;
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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
    if (!stack) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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

    if (!stack || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        /* iterate from sp to bp */
        iter = stack->space.sp;
        while(iter != stack->space.bp) {
            handler(*(--iter));
        }
    }

    return;
}
