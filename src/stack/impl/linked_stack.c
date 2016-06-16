static inline void
linked_stack_node_initial(struct linked_stack_space *node, uint32 dim)
{
    dp_assert(!complain_zero_size_p(dim));

    node->space.bp = memory_cache_allocate(sizeof(void *) * dim);
    node->space.sp = node->space.bp;
    node->space.dim = dim;
}

static inline struct linked_stack_space *
linked_stack_node_create(uint32 dim)
{
    struct linked_stack_space *node;

    dp_assert(!complain_zero_size_p(dim));

    node = memory_cache_allocate(sizeof(*node));
    doubly_linked_list_initial(&node->link);
    linked_stack_node_initial(node, dim);

    return node;
}

/*
 * _RETURN_ one instance of linked_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct linked_stack *
linked_stack_create(void)
{
    struct linked_stack *stack;

    stack = memory_cache_allocate(sizeof(*stack));
    stack->base = linked_stack_node_create(STACK_SIZE_DFT);
    stack->top = stack->base;

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

    if (!complain_null_pointer_p(stack) && !complain_null_pointer_p(*stack)) {
        node = (*stack)->base;

        while (node) {
            node = linked_stack_node_remove(node);
        }

        memory_cache_free(*stack);
        *stack = NULL;
    }
}

static inline struct linked_stack_space *
linked_stack_space_offset_reflect(struct doubly_linked_list *link)
{
    void *offset;

    dp_assert(NULL != link);

    offset = &((struct linked_stack_space *)0)->link;

    return (void *)((void *)link - offset);
}

/*
 * _RETURN_ next node of linked stack space.
 */
static inline struct linked_stack_space *
linked_stack_node_next(struct linked_stack_space *node)
{
    struct linked_stack_space *next;
    struct doubly_linked_list *tmp;

    dp_assert(NULL != node);
    dp_assert(NULL != (&node->link)->next);

    tmp = (&node->link)->next;
    next = linked_stack_space_offset_reflect(tmp);

    return next;
}

/*
 * _RETURN_ previous node of linked stack space.
 */
static inline struct linked_stack_space *
linked_stack_node_previous(struct linked_stack_space *node)
{
    struct linked_stack_space *previous;
    struct doubly_linked_list *tmp;

    tmp = (&node->link)->previous;

    dp_assert(NULL != node);
    dp_assert(NULL != tmp);

    previous = linked_stack_space_offset_reflect(tmp);

    return previous;
}

/*
 * _RETURN_ the next node of linked stack space
 *   If NULL _ARGV_, or last node, _RETURN_ NULL.
 */
static inline struct linked_stack_space *
linked_stack_node_remove(struct linked_stack_space *node)
{
    struct doubly_linked_list *link;

    dp_assert(NULL != node);

    link = &node->link;

    doubly_linked_list_remove(&link);
    memory_cache_free(node->space.bp);
    memory_cache_free(node);

    if (NULL == link) {
        /*
         * last node of linked stack
         */
        return NULL;
    } else {
        return linked_stack_space_offset_reflect(link);
    }
}

static inline void
linked_stack_resize_internal(struct linked_stack *stack, uint32 dim)
{
    uint32 capacity;
    uint32 node_capacity;
    struct linked_stack_space *node;
    struct linked_stack_space *last;

    dp_assert(0 != dim);
    dp_assert(NULL != stack);

    capacity = linked_stack_capacity(stack);
    last = linked_stack_node_previous(stack->base);

    if (capacity < dim) {
        dim = dim - capacity;
        node = linked_stack_node_create(dim);

        doubly_linked_list_insert_ptr_after(&last->link, &node->link);
    } else if (capacity > dim) {
        node_capacity = linked_stack_node_capacity(last);

        while (capacity - node_capacity >= dim) {
            capacity -= node_capacity;
            node = linked_stack_node_previous(last);
            node_capacity = linked_stack_node_capacity(node);

            linked_stack_node_remove(last);
            last = node;
        }

        dim = dim - (capacity - node_capacity);
        last->space.bp = memory_cache_re_allocate(last->space.bp,
            sizeof(void *) * dim);
        last->space.sp = last->space.bp;
        last->space.dim = dim;
    }
}

/*
 * Add one node with _ARGV_ dim at the end of linked stack space.
 *   If invalid _ARGV_, nothing will be done.
 */
void
linked_stack_resize(struct linked_stack *stack, uint32 dim)
{
    if (complain_null_pointer_p(stack)) {
        return;
    } else {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = linked_stack_capacity(stack) * 2 + STACK_EXPD_SIZE_MIN;
        }

        linked_stack_resize_internal(stack, dim);
    }
}

static inline bool
linked_stack_full_p_internal(struct linked_stack *stack)
{
    dp_assert(NULL != stack);

    return 0u == linked_stack_rest_internal(stack) ? true : false;
}

/*
 * _RETURN_ true if no space left in stack, or _RETURN_ false;
 *   If NULL _ARGV_, _RETURN_ false.
 */
bool
linked_stack_full_p(struct linked_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return true;
    } else {
        return linked_stack_full_p_internal(stack);
    }
}

static inline uint32
linked_stack_rest_internal(struct linked_stack *stack)
{
    uint32 rest;
    struct linked_stack_space *next;

    dp_assert(NULL != stack);

    rest = linked_stack_node_rest(stack->top);
    next = linked_stack_node_next(stack->top);

    while (stack->base != next) {
        rest += next->space.dim;
        next = linked_stack_node_next(next);
    }

    return rest;
}

/*
 * _RETURN_ total space of stack.
 *   If NULL _ARGV_, _RETURN_ 0.
 */
uint32
linked_stack_rest(struct linked_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return 0u;
    } else {
        return linked_stack_rest_internal(stack);
    }
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

    if (complain_null_pointer_p(stack)) {
        return 0u;
    } else {
        total = 0u;
        st = stack->base;

        do {
            total += linked_stack_node_capacity(st);
            st = linked_stack_node_next(st);
        } while (st != stack->base);

        return total;
    }
}

static inline bool
linked_stack_node_empty_p(struct linked_stack_space *node)
{
    dp_assert(NULL != node);

    return linked_stack_node_capacity(node)
        == linked_stack_node_rest(node) ? true : false;
}

static inline bool
linked_stack_node_full_p(struct linked_stack_space *node)
{
    dp_assert(NULL != node);

    return 0u == linked_stack_node_rest(node) ? true : false;
}

/*
 * _RETURN_ rest space of specific node.
 *   If NULL _ARGV_, return 0.
 */
static inline uint32
linked_stack_node_capacity(struct linked_stack_space *node)
{
    dp_assert(NULL != node);

    return node->space.dim;
}

/*
 * _RETURN_ rest space of specific node.
 *   If NULL _ARGV_, return 0.
 */
static inline uint32
linked_stack_node_rest(struct linked_stack_space *node)
{
    void **limit;
    void **tmp;

    dp_assert(NULL != node);

    tmp = node->space.sp;
    limit = node->space.bp + node->space.dim;
    if ((sint32)(tmp - limit) > 0) {
        pr_log_err("Array stack overflow.");
    }

    return (uint32)(limit - tmp);
}

/*
 * Push one void pointer to stack
 *   If NULL stack, nothing will be done.
 */
void
linked_stack_push(struct linked_stack *stack, void *member)
{
    uint32 dim;

    if (!complain_null_pointer_p(stack)) {
        if (linked_stack_full_p_internal(stack)) {
            pr_log_info("Stack is full, expand stack with default size.\n");
            dim = linked_stack_capacity(stack) * 2 + STACK_EXPD_SIZE_MIN;
            linked_stack_resize_internal(stack, dim);
        }

        if (linked_stack_node_full_p(stack->top)) {
            pr_log_info("Stack node is full, will move to next node.\n");
            stack->top = linked_stack_node_next(stack->top);
        }

        *stack->top->space.sp++ = member;
    }
}

/*
 * _RETURN_ one void pointer from stack
 *  If NULL _ARGV_, _RETURN_ NULL.
 */
void *
linked_stack_pop(struct linked_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return NULL;
    } else if (linked_stack_empty_p_internal(stack)) {
        pr_log_warn("Attempt to pop from _EMPTY_ stack.\n");
        return NULL;
    } else {
        if (linked_stack_node_empty_p(stack->top)) {
            pr_log_info("Stack node is empty, will move to previous node.\n");
            stack->top = linked_stack_node_previous(stack->top);
        }

        return *(--stack->top->space.sp);
    }
}

static inline bool
linked_stack_empty_p_internal(struct linked_stack *stack)
{
    dp_assert(NULL != stack);

    if (stack->base != stack->top) {
        return false;
    } else if (stack->top->space.dim == linked_stack_node_rest(stack->top)) {
        return true;
    } else {
        return false;
    }
}

/*
 * _RETURN_ true if empty stack, or _RETURN_ false.
 *  If NULL _ARGV_, _RETURN_ false.
 */
bool
linked_stack_empty_p(struct linked_stack *stack)
{
    if (complain_null_pointer_p(stack)) {
        return false;
    } else {
        return linked_stack_empty_p_internal(stack);
    }
}

/*
 * Clean up stack space. Discard all data in stack.
 *   If NULL _ARGV_, nothing will be done.  
 */
void
linked_stack_cleanup(struct linked_stack *stack)
{
    register struct linked_stack_space *iter;

    if (!complain_null_pointer_p(stack)) {
        stack->top = stack->base;
        iter = stack->base;

        do {
            memset(iter->space.bp, 0, sizeof(void *) * iter->space.dim);
            iter->space.sp = iter->space.bp;
            iter = linked_stack_node_next(iter);
        } while (iter != stack->base);
    }
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

    if (!complain_null_pointer_p(stack) && !complain_null_pointer_p(handler)) {
        node = stack->top;
        limit = linked_stack_node_previous(stack->base);

        do {
            linked_stack_node_iterate(node, handler);
            node = linked_stack_node_next(node);
        } while (node != limit);
    }
}

/*
 * Iterate each element of specific node of linked stack space
 *   If NULL stack, nothing will be done.
 */
static inline void
linked_stack_node_iterate(struct linked_stack_space *node,
    void (*handler)(void *))
{
    register void **iter;

    dp_assert(NULL != node);
    dp_assert(NULL != handler);

    iter = node->space.sp;
    /*
     * iterate from sp to bp
     */
    while(iter != node->space.bp) {
        handler(*(--iter));
    }
}

