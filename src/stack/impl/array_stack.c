/*
 * _RETURN_ one instance of array_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct array_stack *
array_stack_create(void)
{
    struct array_stack *stack;

    stack = memory_cache_allocate(sizeof(*stack));
    stack->space.bp = memory_cache_allocate(
        sizeof(void *) * DEFAULT_STACK_SPACE_SIZE);

    stack->space.sp = stack->space.bp;
    stack->space.dim = DEFAULT_STACK_SPACE_SIZE;

    return stack;
}

/*
 * Destroy the instance of array stack.
 *   If NULL _ARGV_, nothing will be done.
 */
void
array_stack_destroy(struct array_stack **stack)
{
    if (!complain_null_pointer_p(stack) && !complain_null_pointer_p(*stack)) {
        memory_cache_dp_free((*stack)->space.bp);
        memory_cache_dp_free(*stack);
        *stack = NULL;
    }
}

static inline void
array_stack_resize_internal(struct array_stack *stack, uint32 dim)
{
    uint32 offset;

    dp_assert(NULL != stack);
    dp_assert(0 != dim);

    offset = (uint32)((uint64)stack->space.sp - (uint64)stack->space.bp);
    if (offset > stack->space.dim) {
        pr_log_warn("Stack overflow, will truncate to the top of stack.\n");
        offset = stack->space.dim;
    }

    stack->space.bp = memory_cache_re_allocate(stack->space.bp,
        sizeof(void *) * dim);
    stack->space.sp = stack->space.bp + offset;
    stack->space.dim = dim;
}

/*
 * Expand the stack space if need.
 *   If NULL stack, nothing will be done.
 *   If extra is zero, expand to 2x + min.
 */
void
array_stack_resize(struct array_stack *stack, uint32 dim)
{
    if (!complain_null_pointer_p(stack)) {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = stack->space.dim * 2 + EXPAND_STACK_SPACE_MIN;
        }

        array_stack_resize_internal(stack, dim);
    }
}

static inline bool
array_stack_full_p_internal(struct array_stack *stack)
{
    dp_assert(NULL != stack);

    return 0u == array_stack_rest_internal(stack) ? true : false;
}

/*
 * _RETURN_ true if no space left in stack, or _RETURN_ false;
 *   If NULL _ARGV_, _RETURN_ true.
 */
bool
array_stack_full_p(struct array_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return true;
    } else {
        return array_stack_full_p_internal(stack);
    }
}

/*
 * _RETURN_ total space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_capacity(struct array_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return 0u;
    } else {
        return stack->space.dim;
    }
}

static inline uint32
array_stack_rest_internal(struct array_stack *stack)
{
    void **limit;
    void **tmp;

    dp_assert(NULL != stack);

    tmp = stack->space.sp;
    limit = stack->space.bp + stack->space.dim;

    if ((sint32)(tmp - limit) > 0) {
        pr_log_err("Array stack overflow.\n");
    } else {
        return (uint32)(limit - tmp);
    }
}

/*
 * _RETURN_ rest space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
array_stack_rest(struct array_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return 0;
    } else {
        return array_stack_rest_internal(stack);
    }
}

/*
 * Push one void pointer to stack
 *   If NULL stack, nothing will be done.
 */
void
array_stack_push(struct array_stack *stack, void *member)
{
    uint32 dim;

    if (!complain_null_pointer_p(stack)) {
        if (array_stack_full_p_internal(stack)) {
            pr_log_info("Stack is full, expand stack with default size.\n");

            dim = array_stack_space_dim(stack) * 2 + EXPAND_STACK_SPACE_MIN;
            array_stack_resize_internal(stack, dim);
        }

        *stack->space.sp++ = member;
    }
}

/*
 * _RETURN_ one void pointer from stack
 *  If NULL _ARGV_, _RETURN_ NULL.
 */
void *
array_stack_pop(struct array_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return NULL;
    } else if (array_stack_empty_p_internal(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return NULL;
    } else {
        return *(--stack->space.sp);
    }
}

static inline bool
array_stack_empty_p_internal(struct array_stack *stack)
{
    dp_assert(NULL != stack);
    dp_assert((sint32)(stack->space.sp - stack->space.bp) >= 0);

    return stack->space.bp == stack->space.sp ? true : false;
}

/*
 * _RETURN_ true if empty stack, or _RETURN_ false.
 *  If NULL _ARGV_, _RETURN_ false.
 */
bool
array_stack_empty_p(struct array_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return false;
    } else if ((sint32)(stack->space.sp - stack->space.bp) < 0) {
        pr_log_err("Array stack overflow.");
    } else {
        return array_stack_empty_p_internal(stack);
    }
}

/*
 * Clean up stack space. Discard all data in stack.
 *   If NULL _ARGV_, nothing will be done.  
 */
void
array_stack_cleanup(struct array_stack *stack)
{
    if (!complain_null_pointer_p(stack)) {
        memset(stack->space.bp, 0, sizeof(void *) * stack->space.dim);
        stack->space.sp = stack->space.bp;
    }
}

/*
 * Iterate each element of stack.
 *   If NULL stack, nothing will be done.
 */
void
array_stack_iterate(struct array_stack *stack, void (*handler)(void *))
{
    register void **iter;

    if (!complain_null_pointer_p(stack) && !complain_null_pointer_p(handler)) {
        /* 
         * iterate from sp to bp
         */
        iter = stack->space.sp;
        while(iter != stack->space.bp) {
            handler(*(--iter));
        }
    }
}

