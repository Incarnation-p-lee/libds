struct stacked_queue *
stacked_queue_create(void)
{
    struct stacked_queue *queue;
    uint32 capacity;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0u;
    }

    queue->enter = array_stack_create();
    queue->leave = array_stack_create();

    capacity = array_stack_capacity(queue->enter);
    queue->dim = capacity;

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
    }
    return;
}

void
stacked_queue_expand_space(struct stacked_queue *queue, uint32 extra)
{
    uint32 capacity;

    if (queue) {
        array_stack_expand_space(queue->enter, extra);
        array_stack_expand_space(queue->leave, extra);

        capacity = array_stack_capacity(queue->enter);
        queue->dim = capacity;
    }
    return;
}

/*
 * In face, stacked queue can hold 2 * queue->dim elements in critial case.
 *   So the capacity should be queue->dim at min
 *                             queue->dim * 2 at max
 * For the consideration of safy, We took queu->dim as capacity for interface.
 */
uint32
stacked_queue_capacity(struct stacked_queue *queue)
{
    return queue ? queue->dim : 0u;
}

/*
 * NULL stacked queue will _RETURN_ 0.
 */
uint32
stacked_queue_rest_space(struct stacked_queue *queue)
{
    return queue ? array_stack_rest_space(queue->enter) : 0u;
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ true.
 */
bool
stacked_queue_is_full(struct stacked_queue *queue)
{
    return 0u == stacked_queue_rest_space(queue) ? true : false;
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ false.
 */
bool
stacked_queue_is_empty(struct stacked_queue *queue)
{
    return queue ? array_stack_is_empty(queue->enter)
            && array_stack_is_empty(queue->leave) : false;
}

void
stacked_queue_enter(struct stacked_queue *queue, void *member)
{
    if (queue && member) {
        if (array_stack_is_full(queue->enter)
            && array_stack_is_empty(queue->leave)) {
            stacked_queue_dump_stack(queue->enter, queue->leave);
        } else if (array_stack_is_full(queue->enter)) {
            array_stack_expand_space(queue->enter, 0u);
            array_stack_expand_space(queue->leave, 0u);
        }
        array_stack_push(queue->enter, member);
    }
    return;
}

static inline void
stacked_queue_dump_stack(struct array_stack *from,
    struct array_stack *to)
{
    if (from && to) {
        if (array_stack_rest_space(from) > array_stack_rest_space(to)) {
            pr_log_info("Operation may result in array stack overflow.\n");
        } else {
            while (!array_stack_is_empty(from)) {
                array_stack_push(to, array_stack_pop(from));
            }
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
        if (!stacked_queue_is_empty(queue)) {
            if (array_stack_is_empty(queue->leave)) {
                stacked_queue_dump_stack(queue->enter, queue->leave);
            }
            retval = array_stack_pop(queue->leave);
        }
    }

    return retval;
}

void
stacked_queue_cleanup(struct stacked_queue *queue)
{
    if (queue) {
        array_stack_cleanup(queue->enter);
        array_stack_cleanup(queue->leave);
    }
    return;
}

void
stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *))
{
    if (queue && handler) {
        array_stack_iterate(queue->leave, handler);
        array_stack_iterate(queue->enter, handler);
    }
    return;
}
