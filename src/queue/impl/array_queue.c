struct array_queue *
array_queue_create(void)
{
    uint32 size;
    struct array_queue *queue;

    size = DEFAULT_QUEUE_SPACE_SIZE;
    queue = memory_cache_allocate(sizeof(*queue));

    array_queue_dim_set_m(queue, size);
    queue->space.base = memory_cache_allocate(sizeof(void *) * size);
    queue->space.rest = size;
    queue->space.front = queue->space.base;
    queue->space.rear = queue->space.base;

    return queue;
}

void
array_queue_destroy(struct array_queue **queue)
{
    if (!complain_null_pointer_p(queue) && array_queue_structure_legal_p(*queue)) {
        memory_cache_free((*queue)->space.base);
        memory_cache_free(*queue);
        *queue = NULL;
    }
}

static inline bool
array_queue_structure_legal_p(struct array_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else if (complain_null_pointer_p(queue->space.base)) {
        return false;
    } else if (complain_null_pointer_p(queue->space.front)) {
        return false;
    } else if (complain_null_pointer_p(queue->space.rear)) {
        return false;
    } else if (queue->space.rest > queue->space.dim) {
        return false;
    } else {
        return true;
    }
}

static inline bool
array_queue_resize_front_to_rear_p(struct array_queue *queue)
{
    assert(array_queue_structure_legal_p(queue));

    if (queue->space.front < queue->space.rear) {
        return false;
    } else if (array_queue_empty_p_internal(queue)) {
        return false;
    } else {
        return true;
    }
}

static inline void
array_queue_resize_expand(struct array_queue *queue, uint32 size,
    void **addr)
{
    uint32 counted;
    uint32 chunk_size;

    assert(!complain_null_pointer_p(addr));
    assert(!complain_zero_size_p(size));
    assert(array_queue_structure_legal_p(queue));
    assert(size > array_queue_dim_m(queue));

    if (queue->space.front < queue->space.rear) {
        counted = queue->space.rear - queue->space.front;
        memcpy(addr, queue->space.front, sizeof(void *) * counted);
    } else if (array_queue_resize_front_to_rear_p(queue)) {
        chunk_size = queue->space.front - queue->space.base;
        counted = array_queue_dim_m(queue) - chunk_size;
        memcpy(addr, queue->space.front, sizeof(void *) * counted);

        chunk_size = queue->space.rear - queue->space.base;
        memcpy(addr + counted, queue->space.base, chunk_size);
        counted += chunk_size;
    } else {
        counted = 0;
    }

    memory_cache_free(queue->space.base);
    queue->space.base = addr;
    queue->space.front = addr;
    queue->space.rear = addr + counted;
    queue->space.rest = size - counted;
    array_queue_dim_set_m(queue, size);
}

static inline void
array_queue_resize_narrow(struct array_queue *queue, uint32 size,
    void **addr)
{
    uint32 counted;
    uint32 part_size;
    uint32 chunk_size;

    assert(!complain_null_pointer_p(addr));
    assert(!complain_zero_size_p(size));
    assert(array_queue_structure_legal_p(queue));
    assert(size < array_queue_dim_m(queue));

    if (queue->space.front < queue->space.rear) {
        chunk_size = queue->space.rear - queue->space.front;
        if (chunk_size >= size) {
            pr_log_warn("Resize narrow will be trancated from tail.\n");
            counted = size;
        } else {
            counted = chunk_size;
        }

        memcpy(addr, queue->space.front, sizeof(void *) * counted);
    } else if (array_queue_resize_front_to_rear_p(queue)) {
        part_size = queue->space.front - queue->space.base;
        chunk_size = array_queue_dim_m(queue) - part_size;

        counted = MIN_U32(part_size, chunk_size);
        memcpy(addr, queue->space.front, sizeof(void *) * counted);

        if (chunk_size < size) {
            part_size = size - counted;
            chunk_size = queue->space.rear - queue->space.base;
            chunk_size = MIN_U32(part_size, chunk_size);

            memcpy(addr + counted, queue->space.base, sizeof(void *) * chunk_size);
            counted += chunk_size;
        }
    } else {
        counted = 0;
    }

    memory_cache_free(queue->space.base);
    queue->space.base = addr;
    queue->space.front = addr;
    queue->space.rest = size - counted;
    queue->space.rear = counted == size ? addr : addr + counted;
    array_queue_dim_set_m(queue, size);
}

static inline void
array_queue_resize_internal(struct array_queue *queue, uint32 size)
{
    void **addr;

    assert(!complain_zero_size_p(size));
    assert(array_queue_structure_legal_p(queue));
    assert(size != queue->space.dim);

    addr = memory_cache_allocate(sizeof(void *) * size);

    if (size > array_queue_dim_m(queue)) {
        array_queue_resize_expand(queue, size, addr);
    } else {
        array_queue_resize_narrow(queue, size, addr);
    }
}

void
array_queue_resize(struct array_queue *queue, uint32 size)
{
    if (!array_queue_structure_legal_p(queue)) {
        return;
    } else if (size == queue->space.dim) {
        return;
    } else if (complain_zero_size_p(size)) {
        size = queue->space.dim * 2 + EXPAND_QUEUE_SPACE_MIN;
        pr_log_info("Expanding size not specified, use default.\n");
    }

    array_queue_resize_internal(queue, size);
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return CAPACITY_INVALID;
    } else {
        return array_queue_dim_m(queue);
    }
}

/*
 * NULL array queue will _RETURN_ 0.
 */
uint32
array_queue_rest(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return REST_INVALID;
    } else {
        return array_queue_rest_m(queue);
    }
}

static inline bool
array_queue_full_p_internal(struct array_queue *queue)
{
    assert(NULL != queue);

    return 0u == array_queue_rest_m(queue) ? true : false;
}

/*
 * NULL array queue will be treated as full, _RETURN_ true.
 */
bool
array_queue_full_p(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
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

    capacity = array_queue_dim_m(queue);
    rest = array_queue_rest_m(queue);

    return capacity == rest ? true : false;
}

/*
 * NULL array queue will be treated as full, _RETURN_ false.
 */
bool
array_queue_empty_p(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return false;
    } else {
        return array_queue_empty_p_internal(queue);
    }
}

void
array_queue_enter(struct array_queue *queue, void *member)
{
    uint32 dim;

    if (array_queue_structure_legal_p(queue)) {
        if (array_queue_full_p_internal(queue)) {
            array_queue_resize_internal(queue, array_queue_dim_m(queue) * 2);
        }

        *queue->space.rear++ = member;
        dim = array_queue_dim_m(queue);

        if (queue->space.rear == queue->space.base + dim) {
            pr_log_info("Reach the limitation of array, will rotate.\n");
            queue->space.rear = queue->space.base;
        }

        queue->space.rest--;
    }
}

void *
array_queue_leave(struct array_queue *queue)
{
    uint32 dim;
    void *retval;

    if (!array_queue_structure_legal_p(queue)) {
        return NULL;
    } else if (array_queue_empty_p_internal(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return NULL;
    } else {
        retval = *queue->space.front++;
        dim = array_queue_dim_m(queue);

        if (queue->space.front == queue->space.base + dim) {
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
    uint32 dim;

    if (array_queue_structure_legal_p(queue)) {
        dim = array_queue_dim_m(queue);
        memset(queue->space.base, 0, sizeof(void *) * dim);

        queue->space.rest = dim;
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    }
}

void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *))
{
    void **lmt;
    void **iter;

    if (!array_queue_structure_legal_p(queue)) {
        return;
    } else if (complain_null_pointer_p(handler)) {
        return;
    } else if (array_queue_empty_p_internal(queue)) {
        pr_log_warn("Iterate on _EMPTY_ queue, nothing will be done.\n");
        return;
    } else {
        lmt = queue->space.base + array_queue_dim_m(queue);
        iter = queue->space.front;

        do {
            (*handler)(*iter++);
            if (iter == lmt) {
                iter = queue->space.base;
            }
        } while (iter != queue->space.rear);
    }
}

