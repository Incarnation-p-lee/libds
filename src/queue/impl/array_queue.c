uint32
array_queue_capacity(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->space.dim;
    }
}

s_array_queue_t *
array_queue_create(void)
{
    uint32 size;
    s_array_queue_t *queue;

    size = QUEUE_SIZE_DFT;
    queue = memory_cache_allocate(sizeof(*queue));

    queue->space.dim = size;
    queue->space.base = memory_cache_allocate(sizeof(void *) * size);
    queue->space.rest = size;
    queue->space.front = queue->space.base;
    queue->space.rear = queue->space.base;

    return queue;
}

void
array_queue_destroy(s_array_queue_t **queue)
{
    if (!complain_null_pointer_p(queue) && array_queue_structure_legal_ip(*queue)) {
        memory_cache_free((*queue)->space.base);
        memory_cache_free(*queue);
        *queue = NULL;
    }
}

static inline bool
array_queue_space_structure_legal_p(s_array_queue_space_t *space)
{
    if (complain_null_pointer_p(space)) {
        return false;
    } else if (space->rest > space->dim) {
        return false;
    } else if (complain_null_pointer_p(space->base)) {
        return false;
    } else if (complain_null_pointer_p(space->front)) {
        return false;
    } else if (complain_null_pointer_p(space->rear)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
array_queue_structure_legal_ip(s_array_queue_t *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else {
        return array_queue_space_structure_legal_p(&queue->space);
    }
}

bool
array_queue_structure_legal_p(s_array_queue_t *queue)
{
    return array_queue_structure_legal_ip(queue);
}

static inline bool
array_queue_resize_front_to_rear_p(s_array_queue_t *queue)
{
    assert_exit(array_queue_structure_legal_ip(queue));

    if (queue->space.front < queue->space.rear) {
        return false;
    } else if (array_queue_empty_ip(queue)) {
        return false;
    } else {
        return true;
    }
}

static inline void
array_queue_resize_expand(s_array_queue_t *queue, uint32 size, void **addr)
{
    uint32 counted;
    uint32 chunk_size;

    assert_exit(!complain_null_pointer_p(addr));
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size > queue->space.dim);

    if (queue->space.front < queue->space.rear) {
        counted = queue->space.rear - queue->space.front;
        dp_memcpy(addr, queue->space.front, sizeof(void *) * counted);
    } else if (array_queue_resize_front_to_rear_p(queue)) {
        chunk_size = queue->space.front - queue->space.base;
        counted = queue->space.dim - chunk_size;
        dp_memcpy(addr, queue->space.front, sizeof(void *) * counted);

        chunk_size = queue->space.rear - queue->space.base;
        dp_memcpy(addr + counted, queue->space.base, chunk_size);
        counted += chunk_size;
    } else {
        counted = 0;
    }

    memory_cache_free(queue->space.base);
    queue->space.base = addr;
    queue->space.front = addr;
    queue->space.rear = addr + counted;
    queue->space.rest = size - counted;
    queue->space.dim = size;
}

static inline void
array_queue_resize_narrow(s_array_queue_t *queue, uint32 size, void **addr)
{
    uint32 counted;
    uint32 part_size;
    uint32 chunk_size;

    assert_exit(!complain_null_pointer_p(addr));
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size < queue->space.dim);

    if (queue->space.front < queue->space.rear) {
        chunk_size = queue->space.rear - queue->space.front;
        if (chunk_size >= size) {
            pr_log_warn("Resize narrow will be trancated from tail.\n");
            counted = size;
        } else {
            counted = chunk_size;
        }

        dp_memcpy(addr, queue->space.front, sizeof(void *) * counted);
    } else if (array_queue_resize_front_to_rear_p(queue)) {
        part_size = queue->space.front - queue->space.base;
        chunk_size = queue->space.dim - part_size;

        counted = MIN_U32(part_size, chunk_size);
        dp_memcpy(addr, queue->space.front, sizeof(void *) * counted);

        if (chunk_size < size) {
            part_size = size - counted;
            chunk_size = queue->space.rear - queue->space.base;
            chunk_size = MIN_U32(part_size, chunk_size);

            dp_memcpy(addr + counted, queue->space.base, sizeof(void *) * chunk_size);
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
    queue->space.dim = size;
}

static inline void
array_queue_resize_i(s_array_queue_t *queue, uint32 size)
{
    void **addr;

    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size != queue->space.dim);

    addr = memory_cache_allocate(sizeof(void *) * size);

    if (size > queue->space.dim) {
        array_queue_resize_expand(queue, size, addr);
    } else {
        array_queue_resize_narrow(queue, size, addr);
    }
}

void
array_queue_resize(s_array_queue_t *queue, uint32 size)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return;
    } else if (size == queue->space.dim) {
        return;
    } else if (complain_zero_size_p(size)) {
        size = queue->space.dim * 2 + QUEUE_EXPD_SIZE_MIN;
        pr_log_info("Expanding size not specified, use default.\n");
    }

    array_queue_resize_i(queue, size);
}

uint32
array_queue_rest(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return QUEUE_REST_INVALID;
    } else {
        return queue->space.rest;
    }
}

static inline bool
array_queue_full_ip(s_array_queue_t *queue)
{
    assert_exit(array_queue_structure_legal_ip(queue));

    return 0u == queue->space.rest ? true : false;
}

bool
array_queue_full_p(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return true;
    } else {
        return array_queue_full_ip(queue);
    }
}

static inline bool
array_queue_empty_ip(s_array_queue_t *queue)
{
    assert_exit(array_queue_structure_legal_ip(queue));

    return queue->space.dim == queue->space.rest ? true : false;
}

bool
array_queue_empty_p(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return false;
    } else {
        return array_queue_empty_ip(queue);
    }
}

void *
array_queue_front(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return PTR_INVALID;
    } else if (array_queue_empty_ip(queue)) {
        return PTR_INVALID;
    } else {
        return *queue->space.front;
    }
}

void *
array_queue_rear(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return PTR_INVALID;
    } else if (array_queue_empty_ip(queue)) {
        return PTR_INVALID;
    } else {
        if (queue->space.rear == queue->space.base) {
             return *(queue->space.base + queue->space.dim - 1);
        } else {
             return *(queue->space.rear - 1);
        }
    }
}

void
array_queue_enter(s_array_queue_t *queue, void *member)
{
    uint32 dim;

    if (array_queue_structure_legal_ip(queue)) {
        if (array_queue_full_ip(queue)) {
            array_queue_resize_i(queue, queue->space.dim * 2);
        }

        *queue->space.rear++ = member;
        dim = queue->space.dim;

        if (queue->space.rear == queue->space.base + dim) {
            pr_log_info("Reach the limitation of array, will rotate.\n");
            queue->space.rear = queue->space.base;
        }

        queue->space.rest--;
    }
}

void *
array_queue_leave(s_array_queue_t *queue)
{
    uint32 dim;
    void *retval;

    if (!array_queue_structure_legal_ip(queue)) {
        return PTR_INVALID;
    } else if (array_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else {
        retval = *queue->space.front++;
        dim = queue->space.dim;

        if (queue->space.front == queue->space.base + dim) {
            pr_log_info("Reach the limitation of array, will rotate.\n");
            queue->space.front = queue->space.base;
        }

        queue->space.rest++;
        return retval;
    }
}

void
array_queue_cleanup(s_array_queue_t *queue)
{
    uint32 dim;

    if (array_queue_structure_legal_ip(queue)) {
        dim = queue->space.dim;
        dp_memset(queue->space.base, 0, sizeof(void *) * dim);

        queue->space.rest = dim;
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    }
}

void
array_queue_iterate(s_array_queue_t *queue, void (*handler)(void *))
{
    void **lmt;
    void **iter;

    if (!array_queue_structure_legal_ip(queue)) {
        return;
    } else if (complain_null_pointer_p(handler)) {
        return;
    } else if (array_queue_empty_ip(queue)) {
        pr_log_warn("Iterate on _EMPTY_ queue, nothing will be done.\n");
    } else {
        lmt = queue->space.base + queue->space.dim;
        iter = queue->space.front;

        do {
            (*handler)(*iter++);
            if (iter == lmt) {
                iter = queue->space.base;
            }
        } while (iter != queue->space.rear);
    }
}

