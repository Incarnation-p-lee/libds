uint32
array_queue_capacity(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->space.dim;
    }
}

/*
 * Return the size of elements in given queue.
 */
uint32
array_queue_size(s_array_queue_t *queue)
{
    if (!array_queue_structure_legal_ip(queue)) {
        return QUEUE_CPCT_INVALID;
    } else {
        return queue->space.dim - queue->space.rest;
    }
}

s_array_iterator_t *
array_queue_iterator_obtain(s_array_queue_t *queue)
{
    if (array_queue_structure_legal_ip(queue)) {
        return &queue->iterator;
    } else {
        return PTR_INVALID;
    }
}

static inline void
array_queue_iterator_index_initial(void *queue)
{
    uint32 index;
    s_array_iterator_t *iterator;
    s_array_queue_t *array_queue;

    assert_exit(array_queue_structure_legal_ip(queue));

    array_queue = queue;
    iterator = &array_queue->iterator;

    index = (uint32)(array_queue->space.front - array_queue->space.base);
    iterator->index = index;
}

static inline bool
array_queue_iterator_next_exist_p(void *queue)
{
    void **location;
    s_array_iterator_t *iterator;
    s_array_queue_t *array_queue;

    assert_exit(array_queue_structure_legal_ip(queue));

    array_queue = queue;
    iterator = &array_queue->iterator;

    location = array_queue->space.base + iterator->index;
    if (location == array_queue->space.rear) {
        return false;
    } else {
        return true;
    }
}

static inline void *
array_queue_iterator_next_obtain(void *queue)
{
    void *next_node;
    s_array_iterator_t *iterator;
    s_array_queue_t *array_queue;

    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(array_queue_iterator_next_exist_p(queue));

    array_queue = queue;
    iterator = &array_queue->iterator;

    next_node = array_queue->space.base[iterator->index];
    iterator->index++;

    if (iterator->index == array_queue->space.dim) { // Index of array rotated
        iterator->index = 0;
    }

    return next_node;
}

s_array_queue_t *
array_queue_create(void)
{
    uint32 size;
    s_array_queue_t *queue;
    void *initial, *next_exist_p, *next_obtain;

    size = QUEUE_SIZE_DFT;
    queue = memory_cache_allocate(sizeof(*queue));

    queue->space.dim = size;
    queue->space.base = memory_cache_allocate(sizeof(void *) * size);
    queue->space.rest = size;
    queue->space.front = queue->space.base;
    queue->space.rear = queue->space.base;

    initial = &array_queue_iterator_index_initial;
    next_exist_p = &array_queue_iterator_next_exist_p;
    next_obtain = &array_queue_iterator_next_obtain;

    array_iterator_initial(&queue->iterator, initial, next_exist_p, next_obtain);

    return queue;
}

void
array_queue_destroy(s_array_queue_t **queue)
{
    if (!NULL_PTR_P(queue) && array_queue_structure_legal_ip(*queue)) {
        memory_cache_free((*queue)->space.base);
        memory_cache_free(*queue);

        *queue = NULL;
    }
}

static inline bool
array_queue_space_structure_legal_p(s_array_queue_space_t *space)
{
    if (NULL_PTR_P(space)) {
        return false;
    } else if (space->rest > space->dim) {
        return false;
    } else if (NULL_PTR_P(space->base)) {
        return false;
    } else if (NULL_PTR_P(space->front)) {
        return false;
    } else if (NULL_PTR_P(space->rear)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
array_queue_structure_legal_ip(s_array_queue_t *queue)
{
    if (NULL_PTR_P(queue)) {
        return false;
    } else if (!array_iterator_structure_legal_p(&queue->iterator)) {
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
array_queue_resize_rotated_p(s_array_queue_t *queue)
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
array_queue_resize_expand(s_array_queue_t *queue, uint32 size)
{
    void **addr;
    uint32 left_size, right_size;
    uint32 data_size, leading_size;

    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size > queue->space.dim);

    /* Additional 1 position for checking */
    addr = memory_cache_allocate(sizeof(void *) * (size + 1));
    assert_exit(array_queue_resize_restore_data_p(queue, size, addr));

    if (queue->space.front < queue->space.rear) {
        data_size = queue->space.rear - queue->space.front;
        dp_memcpy(addr, queue->space.front, sizeof(void *) * data_size);
    } else if (array_queue_resize_rotated_p(queue)) {
        /*
         *      r   f            f         r
         * +-+-+-+-+-+-+-+      +-+-+-+-+-+-+-+-+-+
         * |a|b| | |X|Y|Z|  ==> |X|Y|Z|a|b| | | | |
         * +-+-+-+-+-+-+-+      +-+-+-+-+-+-+-+-+-+
         * left|   |right
         * leading |
         */
        leading_size = queue->space.front - queue->space.base;
        left_size = queue->space.rear - queue->space.base;
        right_size = queue->space.dim - leading_size;

        dp_memcpy(addr, queue->space.front, sizeof(void *) * right_size);
        dp_memcpy(addr + right_size, queue->space.base, sizeof(void *) * left_size);

        data_size = left_size + right_size;
    } else { /* queue is empty */
        data_size = 0;
    }

    memory_cache_free(queue->space.base);
    queue->space.front = queue->space.base = addr;
    queue->space.rear = addr + data_size;
    queue->space.rest = size - data_size;
    queue->space.dim = size;

    assert_exit(array_queue_resize_data_consistant_p(queue));
}

static inline void
array_queue_resize_narrow(s_array_queue_t *queue, uint32 size)
{
    void **addr;
    uint32 left_size, right_size;
    uint32 data_size, leading_size, rest_size;

    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size < queue->space.dim);

    /* Additional 1 position for checking */
    addr = memory_cache_allocate(sizeof(void *) * (size + 1));
    assert_exit(array_queue_resize_restore_data_p(queue, size, addr));

    if (queue->space.front < queue->space.rear) {
        data_size = queue->space.rear - queue->space.front;
        data_size = MIN_U32(data_size, size); /* May be trancated from tail. */
        dp_memcpy(addr, queue->space.front, sizeof(void *) * data_size);
    } else if (array_queue_resize_rotated_p(queue)) {
        /*                             r
         *            r   f            f
         * +-+-+-+-+-+-+-+-+-+-+      +-+-+-+-+-+
         * |A|B|C|D|E| | |x|y|z|  ==> |x|y|z|A|B|
         * +-+-+-+-+-+-+-+-+-+-+      +-+-+-+-+-+
         *     left  |   |right
         *     leading   |
         */
        leading_size = queue->space.front - queue->space.base;
        left_size = queue->space.rear - queue->space.base;
        right_size = queue->space.dim - leading_size;

        data_size = MIN_U32(right_size, size); /* May be trancated from tail. */
        dp_memcpy(addr, queue->space.front, sizeof(void *) * data_size);

        if (right_size < size) {
            rest_size = size - right_size;
            rest_size = MIN_U32(rest_size, left_size); /* May be trancated from tail. */
            dp_memcpy(addr + data_size, queue->space.base, sizeof(void *) * rest_size);
            data_size += rest_size;
        }
    } else { /* queue is empty */
        data_size = 0;
    }

    memory_cache_free(queue->space.base);
    queue->space.front = queue->space.base = addr;
    queue->space.rear = size == data_size ? addr : addr + data_size;
    queue->space.rest = size - data_size;
    queue->space.dim = size;

    assert_exit(array_queue_resize_data_consistant_p(queue));
}

static inline void
array_queue_resize_i(s_array_queue_t *queue, uint32 size)
{
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(size != queue->space.dim);

    if (size > queue->space.dim) {
        array_queue_resize_expand(queue, size);
    } else {
        array_queue_resize_narrow(queue, size);
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
    } else if (NULL_PTR_P(handler)) {
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

