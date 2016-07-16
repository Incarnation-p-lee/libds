uint32
array_queue_dim(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return QUEUE_SIZE_INVALID;
    } else {
        return queue->space.dim;
    }
}

struct array_queue *
array_queue_create(void)
{
    uint32 size;
    struct array_queue *queue;

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
    assert_exit(array_queue_structure_legal_p(queue));

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

    assert_exit(!complain_null_pointer_p(addr));
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_p(queue));
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
array_queue_resize_narrow(struct array_queue *queue, uint32 size,
    void **addr)
{
    uint32 counted;
    uint32 part_size;
    uint32 chunk_size;

    assert_exit(!complain_null_pointer_p(addr));
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_p(queue));
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
array_queue_resize_internal(struct array_queue *queue, uint32 size)
{
    void **addr;

    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_p(queue));
    assert_exit(size != queue->space.dim);

    addr = memory_cache_allocate(sizeof(void *) * size);

    if (size > queue->space.dim) {
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
        size = queue->space.dim * 2 + QUEUE_EXPD_SIZE_MIN;
        pr_log_info("Expanding size not specified, use default.\n");
    }

    array_queue_resize_internal(queue, size);
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->space.dim;
    }
}

/*
 * NULL array queue will _RETURN_ 0.
 */
uint32
array_queue_rest(struct array_queue *queue)
{
    if (!array_queue_structure_legal_p(queue)) {
        return QUEUE_REST_INVALID;
    } else {
        return queue->space.rest;
    }
}

static inline bool
array_queue_full_p_internal(struct array_queue *queue)
{
    assert_exit(NULL != queue);

    return 0u == queue->space.rest ? true : false;
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

    assert_exit(NULL != queue);

    capacity = queue->space.dim;
    rest = queue->space.rest;

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
            array_queue_resize_internal(queue, queue->space.dim * 2);
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
array_queue_cleanup(struct array_queue *queue)
{
    uint32 dim;

    if (array_queue_structure_legal_p(queue)) {
        dim = queue->space.dim;
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

