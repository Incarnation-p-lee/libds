uint32
array_stack_size(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return STACK_SIZE_INVALID;
    } else {
        return (uint32)(stack->space.sp - stack->space.bp);
    }
}

static inline uint32
array_stack_size_i(s_array_stack_t *stack)
{
    assert_exit(array_stack_structrue_legal_p(stack));

    return (uint32)(stack->space.sp - stack->space.bp);
}

static inline bool
array_stack_structrue_legal_p(s_array_stack_t *stack)
{
    if (complain_null_pointer_p(stack)) {
        return false;
    } else if (complain_null_pointer_p(stack->space.bp)) {
        return false;
    } else if (complain_null_pointer_p(stack->space.sp)) {
        return false;
    } else if (complain_zero_size_p(stack->space.dim)) {
        return false;
    } else if ((uint32)(stack->space.sp - stack->space.bp) > stack->space.dim) {
        return false;
    } else {
        return true;
    }
}

s_array_stack_t *
array_stack_create(void)
{
    s_array_stack_t *stack;

    stack = memory_cache_allocate(sizeof(*stack));
    stack->space.bp = memory_cache_allocate(sizeof(void *) * STACK_SIZE_DFT);
    stack->space.sp = stack->space.bp;
    stack->space.dim = STACK_SIZE_DFT;

    return stack;
}

void
array_stack_destroy(s_array_stack_t **stack)
{
    if (complain_null_pointer_p(stack)) {
        return;
    } else if (array_stack_structrue_legal_p(*stack)) {
        memory_cache_free((*stack)->space.bp);
        memory_cache_free(*stack);
        *stack = NULL;
    }
}

static inline void
array_stack_resize_i(s_array_stack_t *stack, uint32 dim)
{
    uint32 size;

    assert_exit(!complain_zero_size_p(dim));
    assert_exit(array_stack_structrue_legal_p(stack));

    size = array_stack_size_i(stack);
    if (size > dim) {
        pr_log_warn("Stack overflow, will truncate to the top of stack.\n");
        size = dim;
    }

    stack->space.bp = memory_cache_re_allocate(stack->space.bp,
        sizeof(void *) * dim);
    stack->space.sp = stack->space.bp + size;
    stack->space.dim = dim;
}

void
array_stack_resize(s_array_stack_t *stack, uint32 dim)
{
    if (array_stack_structrue_legal_p(stack)) {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = stack->space.dim * 2 + STACK_EXPD_SIZE_MIN;
        }
        array_stack_resize_i(stack, dim);
    }
}

static inline bool
array_stack_full_ip(s_array_stack_t *stack)
{
    assert_exit(array_stack_structrue_legal_p(stack));

    return stack->space.dim == array_stack_size_i(stack) ? true : false;
}

bool
array_stack_full_p(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return true;
    } else {
        return array_stack_full_ip(stack);
    }
}

uint32
array_stack_capacity(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return STACK_SIZE_INVALID;
    } else {
        return stack->space.dim;
    }
}

static inline uint32
array_stack_rest_i(s_array_stack_t *stack)
{
    assert_exit(array_stack_structrue_legal_p(stack));

    return stack->space.dim - array_stack_size_i(stack);
}

uint32
array_stack_rest(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return STACK_SIZE_INVALID;
    } else {
        return array_stack_rest_i(stack);
    }
}

void
array_stack_push(s_array_stack_t *stack, void *member)
{
    uint32 dim;

    if (array_stack_structrue_legal_p(stack)) {
        if (array_stack_full_ip(stack)) {
            pr_log_info("Stack is full, expand stack with default size.\n");
            dim = stack->space.dim * 2 + STACK_EXPD_SIZE_MIN;
            array_stack_resize_i(stack, dim);
        }

        *stack->space.sp++ = member;
    }
}

void *
array_stack_top(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return PTR_INVALID;
    } else if (array_stack_empty_ip(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return PTR_INVALID;
    } else {
        return *(stack->space.sp - 1);
    }
}

void *
array_stack_pop(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return PTR_INVALID;
    } else if (array_stack_empty_ip(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return PTR_INVALID;
    } else {
        return *(--stack->space.sp);
    }
}

static inline bool
array_stack_empty_ip(s_array_stack_t *stack)
{
    assert_exit(array_stack_structrue_legal_p(stack));

    return stack->space.bp == stack->space.sp ? true : false;
}

bool
array_stack_empty_p(s_array_stack_t *stack)
{
    if (!array_stack_structrue_legal_p(stack)) {
        return false;
    } else {
        return array_stack_empty_ip(stack);
    }
}

void
array_stack_cleanup(s_array_stack_t *stack)
{
    if (array_stack_structrue_legal_p(stack)) {
        dp_memset(stack->space.bp, 0, sizeof(void *) * stack->space.dim);
        stack->space.sp = stack->space.bp;
    }
}

void
array_stack_iterate(s_array_stack_t *stack, void (*handler)(void *))
{
    void **i;

    if (array_stack_structrue_legal_p(stack)
        && !complain_null_pointer_p(handler)) {
        /* iterate from sp to bp */
        i = stack->space.sp;
        while(i != stack->space.bp) {
            handler(*(--i));
        }
    }
}

