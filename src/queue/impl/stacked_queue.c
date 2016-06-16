uint32
stacked_queue_dim(struct stacked_queue *queue)
{
    if (!queue) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->dim;
    }
}

struct stacked_queue *
stacked_queue_create(void)
{
    struct stacked_queue *queue;

    queue = memory_cache_allocate(sizeof(*queue));

    if (!complain_no_memory_p(queue)) {
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

        memory_cache_free(*queue);
        *queue = NULL;
    }
}

static inline void
stacked_queue_resize_internal(struct stacked_queue *queue, uint32 dim)
{
    dp_assert(NULL != queue);
    dp_assert(0 != dim);

    array_stack_resize(queue->enter, dim);
    array_stack_resize(queue->leave, dim);
    queue->dim = array_stack_capacity(queue->enter);
}

void
stacked_queue_resize(struct stacked_queue *queue, uint32 dim)
{
    if (!complain_null_pointer_p(queue)) {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = queue->dim * 2 + QUEUE_EXPD_SIZE_MIN;
        }

        stacked_queue_resize_internal(queue, dim);
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
        return queue->dim;
    }
}

static inline uint32
stacked_queue_space_rest_internal(struct stacked_queue *queue)
{
    uint32 rest;

    dp_assert(NULL != queue);

    rest = array_stack_rest(queue->enter);

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
    dp_assert(NULL != queue);

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
            stacked_queue_resize_internal(queue, queue->dim * 2);
        }

        array_stack_push(queue->enter, member);
    }
}

static inline void
stacked_queue_stack_dump(struct array_stack *from,
    struct array_stack *to)
{
    uint32 count;

    dp_assert(NULL != from);
    dp_assert(NULL != to);
    dp_assert(array_stack_capacity(from) >= array_stack_rest(from));

    count = array_stack_capacity(from) - array_stack_rest(from);

    if (count > array_stack_rest(to)) {
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

