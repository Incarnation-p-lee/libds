struct stacked_queue *
stacked_queue_create(void)
{
    struct stacked_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        stacked_queue_sid_set(queue, 0x0u);
    }

    queue->enter = array_stack_create();
    queue->leave = array_stack_create();
    queue->dim = array_stack_capacity(queue->enter);

    return queue;
}

void
stacked_queue_destroy(struct stacked_queue **queue)
{
    if (queue && *queue) {
        array_stack_destroy(&(*queue)->enter);
        array_stack_destroy(&(*queue)->leave);
        free_ds(*queue);
        *queue = NULL;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}

void
stacked_queue_space_expand(struct stacked_queue *queue, uint32 extra)
{
    if (queue) {
        array_stack_space_expand(queue->enter, extra);
        array_stack_space_expand(queue->leave, extra);
        queue->dim = array_stack_capacity(queue->enter);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}

/*
 * In fact, stacked queue can hold 2 * queue->dim elements in critial case.
 *   So the capacity should be queue->dim at min
 *                             queue->dim * 2 at max
 * For the consideration of safy, We took queu->dim as capacity for interface.
 */
uint32
stacked_queue_capacity(struct stacked_queue *queue)
{
    if (queue) {
        return stacked_queue_dim(queue);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0;
    }
}

/*
 * NULL stacked queue will _RETURN_ 0.
 */
uint32
stacked_queue_space_rest(struct stacked_queue *queue)
{
    uint32 rest;

    rest = 0u;
    if (queue) {
        rest = array_stack_space_rest(queue->enter);
        if (array_stack_empty_p(queue->leave)) {
            rest += array_stack_capacity(queue->leave);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return rest;
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ true.
 */
bool
stacked_queue_full_p(struct stacked_queue *queue)
{
    if (queue) {
        return 0u == stacked_queue_space_rest(queue) ? true : false;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    }
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ false.
 */
bool
stacked_queue_empty_p(struct stacked_queue *queue)
{
    if (queue) {
        return array_stack_empty_p(queue->enter)
            && array_stack_empty_p(queue->leave);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    }
}

void
stacked_queue_enter(struct stacked_queue *queue, void *member)
{
    if (queue && member) {
        if (array_stack_full_p(queue->enter)
            && array_stack_empty_p(queue->leave)) {
            stacked_queue_stack_dump(queue->enter, queue->leave);
            pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
        } else if (array_stack_full_p(queue->enter)) {
            stacked_queue_space_expand(queue, 0u);
            pr_log_info("Fail to dump enter stack, will expand enter space.\n");
        }
        array_stack_push(queue->enter, member);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}

static inline void
stacked_queue_stack_dump(struct array_stack *from,
    struct array_stack *to)
{
    uint32 count;

    assert(NULL != from);
    assert(NULL != to);
    assert(array_stack_capacity(from) >= array_stack_space_rest(from));

    count = array_stack_capacity(from) - array_stack_space_rest(from);
    if (count > array_stack_space_rest(to)) {
        pr_log_err("Operation may result in array stack overflow.\n");
    } else {
        while (!array_stack_empty_p(from)) {
            array_stack_push(to, array_stack_pop(from));
        }
    }

    return;
}

void *
stacked_queue_leave(struct stacked_queue *queue)
{
    void *retval;

    retval = NULL;
    if (queue) {
        if (!stacked_queue_empty_p(queue)) {
            if (array_stack_empty_p(queue->leave)) {
                stacked_queue_stack_dump(queue->enter, queue->leave);
                pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
            }
            retval = array_stack_pop(queue->leave);
        } else {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return retval;
}

void
stacked_queue_cleanup(struct stacked_queue *queue)
{
    if (queue) {
        array_stack_cleanup(queue->enter);
        array_stack_cleanup(queue->leave);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}

void
stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *))
{
    if (queue && handler) {
        array_stack_iterate(queue->leave, handler);
        array_stack_iterate(queue->enter, handler);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}
