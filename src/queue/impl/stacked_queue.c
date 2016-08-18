uint32
stacked_queue_capacity(s_stacked_queue_t *queue)
{
    if (!queue) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->dim;
    }
}

s_stacked_queue_t *
stacked_queue_create(void)
{
    s_stacked_queue_t *queue;

    queue = memory_cache_allocate(sizeof(*queue));

    queue->enter = array_stack_create();
    queue->leave = array_stack_create();
    queue->dim = array_stack_capacity(queue->enter);

    return queue;
}

static inline bool
stacked_queue_structure_legal_p(s_stacked_queue_t *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else if (complain_zero_size_p(queue->dim)) {
        return false;
    } else if (!array_stack_structure_legal_p(queue->enter)) {
        return false;
    } else if (!array_stack_structure_legal_p(queue->leave)) {
        return false;
    } else {
        return true;
    }
}

void
stacked_queue_destroy(s_stacked_queue_t **queue)
{
    if (!complain_null_pointer_p(queue) && stacked_queue_structure_legal_p(*queue)) {
        array_stack_destroy(&(*queue)->enter);
        array_stack_destroy(&(*queue)->leave);
        memory_cache_free(*queue);

        *queue = NULL;
    }
}

static inline void
stacked_queue_resize_i(s_stacked_queue_t *queue, uint32 dim)
{
    assert_exit(!complain_zero_size_p(dim));
    assert_exit(stacked_queue_structure_legal_p(queue));

    array_stack_resize(queue->enter, dim);
    array_stack_resize(queue->leave, dim);
    queue->dim = array_stack_capacity(queue->enter);
}

void
stacked_queue_resize(s_stacked_queue_t *queue, uint32 dim)
{
    if (stacked_queue_structure_legal_p(queue)) {
        if (0 == dim) {
            pr_log_info("Expanding size not specified, use default.\n");
            dim = queue->dim * 2 + QUEUE_EXPD_SIZE_MIN;
        }

        stacked_queue_resize_i(queue, dim);
    }
}

static inline uint32
stacked_queue_rest_i(s_stacked_queue_t *queue)
{
    uint32 rest;

    assert_exit(stacked_queue_structure_legal_p(queue));

    rest = array_stack_rest(queue->enter);
    if (array_stack_empty_p(queue->leave)) {
        rest += array_stack_capacity(queue->leave);
    }

    return rest;
}

uint32
stacked_queue_rest(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return QUEUE_SIZE_INVALID;
    } else {
        return stacked_queue_rest_i(queue);
    }
}

bool
stacked_queue_full_p(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return true;
    } else {
        return 0u == stacked_queue_rest_i(queue) ? true : false;
    }
}

static inline bool
stacked_queue_empty_ip(s_stacked_queue_t *queue)
{
    assert_exit(stacked_queue_structure_legal_p(queue));

    return array_stack_empty_p(queue->enter) && array_stack_empty_p(queue->leave);
}

bool
stacked_queue_empty_p(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return false;
    } else {
        return stacked_queue_empty_ip(queue);
    }
}

void *
stacked_queue_front(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (stacked_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to access _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else if (array_stack_empty_p(queue->leave)) {
        stacked_queue_stack_dump(queue->enter, queue->leave);
        return array_stack_top(queue->leave);
    } else {
        return array_stack_top(queue->leave);
    }
}

void
stacked_queue_enter(s_stacked_queue_t *queue, void *member)
{
    if (stacked_queue_structure_legal_p(queue) && !complain_null_pointer_p(member)) {
        if (array_stack_full_p(queue->enter) && array_stack_empty_p(queue->leave)) {
            pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
            stacked_queue_stack_dump(queue->enter, queue->leave);
        } else if (array_stack_full_p(queue->enter)) {
            pr_log_info("Fail to dump enter stack, will expand enter space.\n");
            stacked_queue_resize_i(queue, queue->dim * 2);
        }

        array_stack_push(queue->enter, member);
    }
}

static inline void
stacked_queue_stack_dump(s_array_stack_t *from, s_array_stack_t *to)
{
    assert_exit(array_stack_structure_legal_p(to));
    assert_exit(array_stack_structure_legal_p(from));
    assert_exit(array_stack_empty_p(to));
    assert_exit(array_stack_capacity(from) == array_stack_capacity(to));

    while (!array_stack_empty_p(from)) {
        array_stack_push(to, array_stack_pop(from));
    }
}

void *
stacked_queue_rear(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (stacked_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to access _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else if (array_stack_empty_p(queue->enter)) {
        stacked_queue_stack_dump(queue->leave, queue->enter);
        return array_stack_top(queue->enter);
    } else {
        return array_stack_top(queue->enter);
    }
}

void *
stacked_queue_leave(s_stacked_queue_t *queue)
{
    if (!stacked_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (stacked_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else {
        if (array_stack_empty_p(queue->leave)) {
            pr_log_info("Empty leave stack, will dump enter stack to leave.\n");
            stacked_queue_stack_dump(queue->enter, queue->leave);
        }
        return array_stack_pop(queue->leave);
    }
}

void
stacked_queue_cleanup(s_stacked_queue_t *queue)
{
    if (stacked_queue_structure_legal_p(queue)) {
        array_stack_cleanup(queue->enter);
        array_stack_cleanup(queue->leave);
    }
}

void
stacked_queue_iterate(s_stacked_queue_t *queue, void (*handler)(void *))
{
    if (stacked_queue_structure_legal_p(queue) && !complain_null_pointer_p(handler)) {
        array_stack_iterate(queue->leave, handler);
        array_stack_iterate(queue->enter, handler);
    }
}

