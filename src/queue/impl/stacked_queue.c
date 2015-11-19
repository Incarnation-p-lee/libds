struct stacked_queue *
stacked_queue_create(void)
{
    struct stacked_queue *queue;

    queue = malloc_ds(sizeof(*queue));

    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0x0u;
        queue->enter = array_stack_create();
        queue->leave = array_stack_create();
        queue->dim = array_stack_capacity(queue->enter);
    }

    return queue;
}

void
stacked_queue_destroy(struct stacked_queue **queue)
{
    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(*queue)) {
        array_stack_destroy(&(*queue)->enter);
        array_stack_destroy(&(*queue)->leave);

        free_ds(*queue);
        *queue = NULL;
    }
}

static inline void
stacked_queue_space_expand_internal(struct stacked_queue *queue, uint32 increment)
{
    assert(NULL != queue);
    assert(0 != increment);

    array_stack_space_expand(queue->enter, increment);
    array_stack_space_expand(queue->leave, increment);
    queue->dim = array_stack_capacity(queue->enter);
}

void
stacked_queue_space_expand(struct stacked_queue *queue, uint32 extra)
{
    uint32 increment;

    if (!complain_null_pointer_p(queue)) {
        if (!extra) {
            increment = queue->dim;
            pr_log_info("Expanding size not specified, use default.\n");
        } else {
            increment = extra;
        }

        stacked_queue_space_expand_internal(queue, increment);
    }
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
    if (complain_null_pointer_p(queue)) {
        return 0;
    } else {
        return stacked_queue_dim(queue);
    }
}

static inline uint32
stacked_queue_space_rest_internal(struct stacked_queue *queue)
{
    uint32 rest;

    assert(NULL != queue);

    rest = array_stack_space_rest(queue->enter);

    if (array_stack_empty_p(queue->leave)) {
        rest += array_stack_capacity(queue->leave);
    }

    return rest;
}

/*
 * NULL stacked queue will _RETURN_ 0.
 */
uint32
stacked_queue_space_rest(struct stacked_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return 0u;
    } else {
        return stacked_queue_space_rest_internal(queue);
    }
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ true.
 */
bool
stacked_queue_full_p(struct stacked_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return true;
    } else {
        return 0u == stacked_queue_space_rest_internal(queue) ? true : false;
    }
}


static inline bool
stacked_queue_empty_p_internal(struct stacked_queue *queue)
{
    assert(NULL != queue);

    return array_stack_empty_p(queue->enter) && array_stack_empty_p(queue->leave);
}

/*
 * NULL stacked queue will be treated as full, _RETURN_ false.
 */
bool
stacked_queue_empty_p(struct stacked_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else {
        return stacked_queue_empty_p_internal(queue);
    }
}

void
stacked_queue_enter(struct stacked_queue *queue, void *member)
{
    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(member)) {
        if (array_stack_full_p(queue->enter)
            && array_stack_empty_p(queue->leave)) {
            pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
            stacked_queue_stack_dump(queue->enter, queue->leave);
        } else if (array_stack_full_p(queue->enter)) {
            pr_log_info("Fail to dump enter stack, will expand enter space.\n");
            stacked_queue_space_expand_internal(queue, queue->dim);
        }

        array_stack_push(queue->enter, member);
    }
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
}

void *
stacked_queue_leave(struct stacked_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return NULL;
    } else {
        if (stacked_queue_empty_p_internal(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
            return NULL;
        } else {
            if (array_stack_empty_p(queue->leave)) {
                pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
                stacked_queue_stack_dump(queue->enter, queue->leave);
            }

            return array_stack_pop(queue->leave);
        }
    }
}

void
stacked_queue_cleanup(struct stacked_queue *queue)
{
    if (!complain_null_pointer_p(queue)) {
        array_stack_cleanup(queue->enter);
        array_stack_cleanup(queue->leave);
    }
}

void
stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *))
{
    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(handler)) {
        array_stack_iterate(queue->leave, handler);
        array_stack_iterate(queue->enter, handler);
    }
}

