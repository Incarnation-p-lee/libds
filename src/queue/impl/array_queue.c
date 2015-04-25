struct array_queue *
array_queue_create(void)
{
    struct array_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        array_queue_sid_set(queue, 0x0u);
    }

    queue->space.base = malloc_ds(sizeof(void *) * DEFAULT_QUEUE_SPACE_SIZE);
    if (!queue->space.base) {
        free_ds(queue);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->space.dim = DEFAULT_QUEUE_SPACE_SIZE;
        queue->space.rest = DEFAULT_QUEUE_SPACE_SIZE;
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    }

    return queue;
}

void
array_queue_destroy(struct array_queue **queue)
{
    if(queue && *queue) {
        free_ds((*queue)->space.base);
        free_ds(*queue);
        *queue = NULL;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

static inline void
array_queue_space_expand_chunk_fixup(struct array_queue *queue,
    uint32 old_size, uint32 new_size)
{
    void **to;
    void **from;
    void **lmt;

    assert(NULL != queue);

    lmt = queue->space.front;
    to = queue->space.base + new_size;
    from = queue->space.base + old_size;

    while ((sint32)(lmt - from) < 0) {
        *(--to) = *(--from);
    }
}

static inline void
array_queue_space_expand_attr_update(struct array_queue *queue, uint32 old_size,
    void **new_addr, uint32 new_size)
{
    assert(NULL != queue);
    assert(NULL != new_addr);
    assert(new_size >= old_size);

    if (new_addr != queue->space.base) {
        queue->space.front = new_addr + (queue->space.front - queue->space.base);
        queue->space.rear = new_addr + (queue->space.rear - queue->space.base);
    }

    queue->space.base = new_addr;
    queue->space.dim = new_size;
    queue->space.rest += new_size - old_size;
}

void
array_queue_space_expand(struct array_queue *queue, uint32 extra)
{
    uint32 old_size;
    uint32 new_size;
    void **new_addr;

    new_size = 0;
    if (queue) {
        old_size = array_queue_capacity(queue);
        if (extra) {
            new_size = old_size + extra;
        } else {
            new_size = old_size * 2 + EXPAND_QUEUE_SPACE_MIN;
            pr_log_info("Expanding size not specified, use default.\n");
        }

        new_addr = realloc_ds(queue->space.base, sizeof(void *) * new_size);
        if (!new_addr) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            /* realloc may return a address different from queue->space.base */
            array_queue_space_expand_attr_update(queue, old_size, new_addr, new_size);
        }

        /* No need to do if (queue->space.front < queue->space.rear) */
        if ((queue->space.front == queue->space.rear && array_queue_full_p(queue))
            || queue->space.front > queue->space.rear) {
            array_queue_space_expand_chunk_fixup(queue, old_size, new_size);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    if (queue) {
        return array_queue_dim(queue);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0x0u;
    }
}

/*
 * NULL array queue will _RETURN_ 0.
 */
uint32
array_queue_space_rest(struct array_queue *queue)
{
    if (queue) {
        return array_queue_rest(queue);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0x0u;
    }
}

/*
 * NULL array queue will be treated as full, _RETURN_ true.
 */
bool
array_queue_full_p(struct array_queue *queue)
{
    if (queue) {
        return 0u == array_queue_space_rest(queue);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    }
}

/*
 * NULL array queue will be treated as full, _RETURN_ false.
 */
bool
array_queue_empty_p(struct array_queue *queue)
{
    bool is_empty;

    is_empty = false;
    if (queue) {
        is_empty = array_queue_capacity(queue)
            == array_queue_space_rest(queue) ? true : false;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return is_empty;
}

void
array_queue_enter(struct array_queue *queue, void *member)
{
    if (queue && member) {
        if (array_queue_full_p(queue)) {
            array_queue_space_expand(queue, 0u);
        }

        *queue->space.rear++ = member;
        if (queue->space.rear == queue->space.base + array_queue_capacity(queue)) {
            queue->space.rear = queue->space.base;
            pr_log_info("Reach the limitation of array, will rotate.\n");
        }
        queue->space.rest--;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}

void *
array_queue_leave(struct array_queue *queue)
{
    void *retval;

    retval = NULL;
    if (queue) {
        if (!array_queue_empty_p(queue)) {
            retval = *queue->space.front++;
            if (queue->space.front == queue->space.base + array_queue_capacity(queue)) {
                queue->space.front = queue->space.base;
                pr_log_info("Reach the limitation of array, will rotate.\n");
            }
            queue->space.rest++;
        } else {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return retval;
}

void
array_queue_cleanup(struct array_queue *queue)
{
    uint32 capacity;

    if (queue) {
        capacity = array_queue_capacity(queue);
        memset(queue->space.base, 0, sizeof(void *) * capacity);
        queue->space.rest = capacity;
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *))
{
    register void **iter;
    void **lmt;

    if (queue && handler) {
        if (!array_queue_empty_p(queue)) {
            lmt = queue->space.base + array_queue_capacity(queue);
            iter = queue->space.front;
            do {
                (*handler)(*iter++);
                if (iter == lmt) {
                    iter = queue->space.base;
                }
            } while (iter != queue->space.rear);
        } else {
            pr_log_info("Iterate on _EMPTY_ queue, nothing will be done.\n");
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }
    return;
}
