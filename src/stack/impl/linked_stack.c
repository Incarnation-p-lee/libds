static inline void
linked_stack_space_initial(s_linked_stack_space_t *space, uint32 dim)
{
    assert_exit(!complain_null_pointer_p(space));
    assert_exit(!complain_zero_size_p(dim));

    space->space.bp = memory_cache_allocate(sizeof(void *) * dim);
    space->space.sp = space->space.bp;
    space->space.dim = dim;
}

static inline s_linked_stack_space_t *
linked_stack_space_create(uint32 dim)
{
    s_linked_stack_space_t *space;

    assert_exit(!complain_zero_size_p(dim));

    space = memory_cache_allocate(sizeof(*space));
    doubly_linked_list_initial(&space->link);
    linked_stack_space_initial(space, dim);

    return space;
}

static inline bool
linked_stack_space_structure_legal_p(s_linked_stack_space_t *space)
{
    if (complain_null_pointer_p(space)) {
        return false;
    } else if (!doubly_linked_list_structure_legal_p(&space->link)) {
        return false;
    } else if (!array_stack_space_structure_legal_p(&space->space)) {
        return false;
    } else {
        return true;
    }
}

bool
linked_stack_structure_legal_p(s_linked_stack_t *stack)
{
    return linked_stack_structure_legal_ip(stack);
}

static inline bool
linked_stack_structure_legal_ip(s_linked_stack_t *stack)
{
    if (complain_null_pointer_p(stack)) {
        return false;
    } else if (complain_null_pointer_p(stack->base)) {
        return false;
    } else if (complain_null_pointer_p(stack->top)) {
        return false;
    } else if (!linked_stack_space_structure_legal_p(stack->base)) {
        return false;
    } else if (!linked_stack_space_structure_legal_p(stack->top)) {
        return false;
    } else {
        return true;
    }
}

s_linked_stack_t *
linked_stack_create(void)
{
    s_linked_stack_t *stack;

    stack = memory_cache_allocate(sizeof(*stack));
    stack->base = linked_stack_space_create(STACK_SIZE_DFT);
    stack->top = stack->base;

    return stack;
}

void
linked_stack_destroy(s_linked_stack_t **stack)
{
    s_linked_stack_space_t *node;

    if (complain_null_pointer_p(stack)) {
        return;
    } else if (linked_stack_structure_legal_ip(*stack)) {
        node = (*stack)->base;
        while (node) {
            node = linked_stack_space_remove(node);
        }

        memory_cache_free(*stack);
        *stack = NULL;
    }
}

static inline s_linked_stack_space_t *
linked_stack_ptr_to_space(s_doubly_linked_list_t *link)
{
    assert_exit(doubly_linked_list_structure_legal_p(link));

    return CONTAINER_OF(link, s_linked_stack_space_t, link);
}

static inline s_linked_stack_space_t *
linked_stack_space_next(s_linked_stack_space_t *node)
{
    assert_exit(linked_stack_space_structure_legal_p(node));

    return linked_stack_ptr_to_space(node->link.next);
}

static inline s_linked_stack_space_t *
linked_stack_space_previous(s_linked_stack_space_t *node)
{
    assert_exit(linked_stack_space_structure_legal_p(node));

    return linked_stack_ptr_to_space(node->link.previous);
}

static inline s_linked_stack_space_t *
linked_stack_space_remove(s_linked_stack_space_t *node)
{
    s_doubly_linked_list_t *link;

    assert_exit(linked_stack_space_structure_legal_p(node));

    link = &node->link;

    doubly_linked_list_remove(&link);
    memory_cache_free(node->space.bp);
    memory_cache_free(node);

    if (NULL == link) {
        /* last node of linked stack */
        return NULL;
    } else {
        return linked_stack_ptr_to_space(link);
    }
}

static inline void
linked_stack_resize_i(s_linked_stack_t *stack, uint32 dim)
{
    uint32 capacity;
    uint32 node_capacity;
    s_linked_stack_space_t *node;
    s_linked_stack_space_t *last;

    assert_exit(!complain_zero_size_p(dim));
    assert_exit(linked_stack_structure_legal_ip(stack));

    capacity = linked_stack_capacity_i(stack);
    last = linked_stack_space_previous(stack->base);

    if (capacity < dim) {
        dim = dim - capacity;
        node = linked_stack_space_create(dim);
        doubly_linked_list_insert_after(&last->link, &node->link);
    } else if (capacity > dim) {
        node_capacity = last->space.dim;
        while (capacity - node_capacity >= dim) {
            capacity -= node_capacity;
            node = linked_stack_space_previous(last);
            node_capacity = node->space.dim;

            linked_stack_space_remove(last);
            last = node;
        }

        dim = dim - (capacity - node_capacity);
        last->space.bp = memory_cache_re_allocate(last->space.bp,
            sizeof(void *) * dim);
        last->space.sp = last->space.bp;
        last->space.dim = dim;
    }
}

void
linked_stack_resize(s_linked_stack_t *stack, uint32 dim)
{
    if (linked_stack_structure_legal_ip(stack)) {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = linked_stack_capacity_i(stack) * 2 + STACK_EXPD_SIZE_MIN;
        }

        linked_stack_resize_i(stack, dim);
    }
}

static inline bool
linked_stack_full_ip(s_linked_stack_t *stack)
{
    assert_exit(linked_stack_structure_legal_ip(stack));

    if (0 == linked_stack_rest_i(stack)) {
        return true;
    } else {
        return false;
    }
}

bool
linked_stack_full_p(s_linked_stack_t *stack)
{
    if (linked_stack_structure_legal_ip(stack)) {
        return true;
    } else {
        return linked_stack_full_ip(stack);
    }
}

static inline uint32
linked_stack_rest_i(s_linked_stack_t *stack)
{
    uint32 rest;
    struct linked_stack_space *next;

    assert_exit(linked_stack_structure_legal_ip(stack));

    rest = linked_stack_space_rest(stack->top);
    next = linked_stack_space_next(stack->top);

    while (stack->base != next) {
        rest += next->space.dim;
        next = linked_stack_space_next(next);
    }

    return rest;
}

uint32
linked_stack_rest(s_linked_stack_t *stack)
{
    if (!linked_stack_structure_legal_ip(stack)) {
        return 0u;
    } else {
        return linked_stack_rest_i(stack);
    }
}

static inline uint32
linked_stack_capacity_i(s_linked_stack_t *stack)
{
    uint32 capacity;
    s_linked_stack_space_t *space;

    assert_exit(linked_stack_structure_legal_ip(stack));

    capacity = 0u;
    space = stack->base;

    do {
        capacity += space->space.dim;
        space = linked_stack_space_next(space);
    } while (space != stack->base);

    return capacity;
}

uint32
linked_stack_capacity(s_linked_stack_t *stack)
{
    if (!linked_stack_structure_legal_ip(stack)) {
        return 0u;
    } else {
        return linked_stack_capacity_i(stack);
    }
}

static inline bool
linked_stack_space_empty_p(s_linked_stack_space_t *space)
{
    assert_exit(linked_stack_space_structure_legal_p(space));

    return space->space.dim == linked_stack_space_rest(space) ? true : false;
}

static inline bool
linked_stack_space_full_p(s_linked_stack_space_t *space)
{
    assert_exit(linked_stack_space_structure_legal_p(space));

    return 0u == linked_stack_space_rest(space) ? true : false;
}

static inline uint32
linked_stack_space_rest(s_linked_stack_space_t *space)
{
    void **tmp;
    void **limit;

    assert_exit(linked_stack_space_structure_legal_p(space));

    tmp = space->space.sp;
    limit = space->space.bp + space->space.dim;
    if ((ptr_t)tmp > (ptr_t)limit) {
        pr_log_err("Array stack overflow.");
    }

    return (uint32)(limit - tmp);
}

void
linked_stack_push(s_linked_stack_t *stack, void *member)
{
    uint32 dim;

    if (linked_stack_structure_legal_ip(stack)) {
        if (linked_stack_full_ip(stack)) {
            pr_log_info("Stack is full, expand stack with default size.\n");
            dim = linked_stack_capacity_i(stack) * 2 + STACK_EXPD_SIZE_MIN;
            linked_stack_resize_i(stack, dim);
        }

        if (linked_stack_space_full_p(stack->top)) {
            pr_log_info("Stack node is full, will move to next node.\n");
            stack->top = linked_stack_space_next(stack->top);
        }

        *stack->top->space.sp++ = member;
    }
}

void *
linked_stack_pop(s_linked_stack_t *stack)
{
    if (!linked_stack_structure_legal_ip(stack)) {
        return NULL;
    } else if (linked_stack_empty_ip(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return NULL;
    } else {
        if (linked_stack_space_empty_p(stack->top)) {
            pr_log_info("Stack node is empty, will move to previous node.\n");
            stack->top = linked_stack_space_previous(stack->top);
        }

        return *(--stack->top->space.sp);
    }
}

void *
linked_stack_top(s_linked_stack_t *stack)
{
    if (!linked_stack_structure_legal_ip(stack)) {
        return NULL;
    } else if (linked_stack_empty_ip(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return NULL;
    } else {
        if (linked_stack_space_empty_p(stack->top)) {
            pr_log_info("Stack node is empty, will move to previous node.\n");
            stack->top = linked_stack_space_previous(stack->top);
        }

        return *(stack->top->space.sp);
    }
}

static inline bool
linked_stack_empty_ip(s_linked_stack_t *stack)
{
    assert_exit(linked_stack_structure_legal_ip(stack));

    if (stack->base != stack->top) {
        return false;
    } else if (stack->top->space.dim == linked_stack_space_rest(stack->top)) {
        return true;
    } else {
        return false;
    }
}

bool
linked_stack_empty_p(s_linked_stack_t *stack)
{
    if (!linked_stack_structure_legal_ip(stack)) {
        return false;
    } else {
        return linked_stack_empty_ip(stack);
    }
}

void
linked_stack_cleanup(s_linked_stack_t *stack)
{
    s_linked_stack_space_t *space;

    if (linked_stack_structure_legal_ip(stack)) {
        stack->top = stack->base;
        space = stack->base;

        do {
            memset(space->space.bp, 0, sizeof(void *) * space->space.dim);
            space->space.sp = space->space.bp;
            space = linked_stack_space_next(space);
        } while (space != stack->base);
    }
}

void
linked_stack_iterate(s_linked_stack_t *stack, void (*handler)(void *))
{
    s_linked_stack_space_t *space;
    s_linked_stack_space_t *space_head;

    if (complain_null_pointer_p(handler)) {
        return;
    } else if (linked_stack_structure_legal_ip(stack)) {
        space = space_head = stack->top;

        do {
            linked_stack_space_iterate(space, handler);
            space = linked_stack_space_next(space);
        } while (space_head != space);
    }
}

static inline void
linked_stack_space_iterate(s_linked_stack_space_t *space,
    void (*handler)(void *))
{
    void **ptr;

    assert_exit(!complain_null_pointer_p(handler));
    assert_exit(linked_stack_space_structure_legal_p(space));

    ptr = space->space.sp;
    while(ptr != space->space.bp) {
        handler(*(--ptr));
    }
}

