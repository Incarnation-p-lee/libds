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
    if(!queue || !*queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        free_ds((*queue)->space.base);
        free_ds(*queue);
        *queue = NULL;
    }
}

static inline void
array_queue_space_expand_chunk_fixup(struct array_queue *queue, uint32 increment)
{
    void **to;
    void **from;
    void **lmt;

    assert(NULL != queue);
    assert(0 != increment);
    assert(queue->space.dim > increment);

    lmt = queue->space.front;
    to = queue->space.base + queue->space.dim;
    from = queue->space.base + (queue->space.dim - increment);

    while ((sint32)(lmt - from) < 0) {
        *(--to) = *(--from);
    }
}

static inline void
array_queue_space_expand_attr_update(struct array_queue *queue, uint32 increment,
    void **new_addr)
{
    assert(NULL != queue);
    assert(NULL != new_addr);
    assert(0 != increment);

    if (new_addr != queue->space.base) {
        queue->space.front = new_addr + (queue->space.front - queue->space.base);
        queue->space.rear = new_addr + (queue->space.rear - queue->space.base);
    }

    queue->space.base = new_addr;
    queue->space.dim += increment;
    queue->space.rest += increment;
}

static inline void
array_queue_space_expand_internal(struct array_queue *queue, uint32 increment)
{
    uint32 new_size;
    void **new_addr;

    assert(NULL != queue);
    assert(0 != increment);

    new_size = array_queue_capacity_internal(queue) + increment;
    new_addr = realloc_ds(queue->space.base, sizeof(void *) * new_size);

    if (!new_addr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        /*
         * realloc may return a address different from queue->space.base 
         */
        array_queue_space_expand_attr_update(queue, increment, new_addr);
        /*
         * No need to do if (queue->space.front < queue->space.rear)
         */
        if ((queue->space.front == queue->space.rear && array_queue_full_p_internal(queue))
            || queue->space.front > queue->space.rear) {
            array_queue_space_expand_chunk_fixup(queue, increment);
        }
    }
}

void
array_queue_space_expand(struct array_queue *queue, uint32 extra)
{
    uint32 increment;

    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (!extra) {
            increment = array_queue_capacity_internal(queue) + EXPAND_QUEUE_SPACE_MIN;
            pr_log_info("Expanding size not specified, use default.\n");
        } else {
            increment = extra;
        }

        array_queue_space_expand_internal(queue, increment);
    }
}

static inline uint32
array_queue_capacity_internal(struct array_queue *queue)
{
    assert(NULL != queue);

    return queue->space.dim;
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0x0u;
    } else {
        return array_queue_capacity_internal(queue);
    }
}

static inline uint32
array_queue_space_rest_internal(struct array_queue *queue)
{
    assert(NULL != queue);

    return queue->space.rest;
}

/*
 * NULL array queue will _RETURN_ 0.
 */
uint32
array_queue_space_rest(struct array_queue *queue)
{
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0x0u;
    } else {
        return array_queue_space_rest_internal(queue);
    }
}

static inline bool
array_queue_full_p_internal(struct array_queue *queue)
{
    assert(NULL != queue);

    return 0u == array_queue_space_rest_internal(queue) ? true : false;
}

/*
 * NULL array queue will be treated as full, _RETURN_ true.
 */
bool
array_queue_full_p(struct array_queue *queue)
{
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return array_queue_full_p_internal(queue);
    }
}

static inline bool
array_queue_empty_p_internal(struct array_queue *queue)
{
    uint32 capacity;
    uint32 rest;

    assert(NULL != queue);

    capacity = array_queue_capacity_internal(queue);
    rest = array_queue_space_rest_internal(queue);

    return capacity == rest ? true : false;
}

/*
 * NULL array queue will be treated as full, _RETURN_ false.
 */
bool
array_queue_empty_p(struct array_queue *queue)
{
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return array_queue_empty_p_internal(queue);
    }
}

void
array_queue_enter(struct array_queue *queue, void *member)
{
    if (!queue || !member) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (array_queue_full_p_internal(queue)) {
            array_queue_space_expand(queue, 0u);
        }

        *queue->space.rear++ = member;

        if (queue->space.rear
            == queue->space.base + array_queue_capacity_internal(queue)) {
            pr_log_info("Reach the limitation of array, will rotate.\n");
            queue->space.rear = queue->space.base;
        }

        queue->space.rest--;
    }
}

void *
array_queue_leave(struct array_queue *queue)
{
    void *retval;

    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (array_queue_empty_p_internal(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return NULL;
    } else {
        retval = *queue->space.front++;

        if (queue->space.front
            == queue->space.base + array_queue_capacity_internal(queue)) {
            pr_log_info("Reach the limitation of array, will rotate.\n");
            queue->space.front = queue->space.base;
        }

        queue->space.rest++;

        return retval;
    }
}

void
array_queue_cleanup(struct array_queue *queue)
{
    uint32 capacity;

    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        capacity = array_queue_capacity_internal(queue);
        memset(queue->space.base, 0, sizeof(void *) * capacity);

        queue->space.rest = capacity;
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    }
}

void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *))
{
    register void **iter;
    void **lmt;

    if (!queue || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (array_queue_empty_p_internal(queue)) {
            pr_log_info("Iterate on _EMPTY_ queue, nothing will be done.\n");
        } else {
            lmt = queue->space.base + array_queue_capacity_internal(queue);
            iter = queue->space.front;

            do {
                (*handler)(*iter++);
                if (iter == lmt) {
                    iter = queue->space.base;
                }
            } while (iter != queue->space.rear);
        }
    }
}

