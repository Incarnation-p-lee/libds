static inline bool
array_queue_enter_optimize_legal_p(s_array_queue_t *queue, void *member)
{
    uint32 dim;
    uint32 rest;
    void **rear, **rear_backup;

    assert_exit(array_queue_structure_legal_ip(queue));

    dim = queue->space.dim;
    rest = queue->space.rest;

    rear_backup = queue->space.rear;
    rear = queue->space.rear + 1;

    if (rear == queue->space.base + dim) {
        rear = queue->space.base;
    }

    ARRAY_QUEUE_ENTER_I(queue, member);

    if (*rear_backup != member) {
        return false;
    } else if (rear != queue->space.rear) {
        return false;
    } else if (rest != queue->space.rest + 1) {
        return false;
    } else { // retrieve here
        queue->space.rest++;
        queue->space.rear = rear_backup;

        return true;
    }
}

static inline bool
array_queue_leave_optimize_legal_p(s_array_queue_t *queue)
{
    uint32 dim;
    uint32 rest;
    void *val, *val_backup;
    void **front, **front_backup;

    assert_exit(array_queue_structure_legal_ip(queue));

    dim = queue->space.dim;
    rest = queue->space.rest;

    val_backup = *queue->space.front;
    front_backup = queue->space.front;
    front = queue->space.front + 1;

    if (front == queue->space.base + dim) {
        front = queue->space.base;
    }

    ARRAY_QUEUE_LEAVE_I(queue, val);

    if (val != val_backup) {
        return false;
    } else if (rest + 1 != queue->space.rest) {
        return false;
    } else if (front != queue->space.front) {
        return false;
    } else { // retrieve here
        queue->space.rest--;
        queue->space.front = front_backup;

        return true;
    }
}

/*
 * *HACK*, use the last node of resize expand for store the element list of
 *         queue for sanity check.
 *         As the last element of expand space should not be touched, use it
 *         as the pointer to void * array, which hold all element in queue
 *         in order.
 *         then the other function will use the data for sanity check, and
 *         free them elegantly.
 */
static inline bool
array_queue_resize_restore_data_p(s_array_queue_t *queue, uint32 size,
    void **addr)
{
    void **restore_array;
    void **data_i, **data_limit;
    uint32 queue_element_size;

    assert_exit(!complain_null_pointer_p(addr));
    assert_exit(!complain_zero_size_p(size));
    assert_exit(array_queue_structure_legal_ip(queue));

    if (array_queue_empty_ip(queue)) {
        return true;
    } else {
        queue_element_size = array_queue_size(queue);
        addr[size] = dp_malloc(sizeof(void *) * (queue_element_size + 1));
        restore_array = addr[size];

        data_limit = queue->space.base + queue->space.dim;
        data_i = queue->space.front;

        do {
            *restore_array++ = *data_i++;
            if (data_limit == data_i) {
                data_i = queue->space.base;
            }
        } while (data_i != queue->space.rear);

        *restore_array = NULL;
        assert_exit(queue_element_size == restore_array - (void **)addr[size]);

        return true;
    }
}

static inline bool
array_queue_resize_data_consistant_p(s_array_queue_t *queue)
{
    uint32 i;
    void **restore_array;
    void **data_i, **data_limit;

    assert_exit(array_queue_structure_legal_ip(queue));
    assert_exit(queue->space.front == queue->space.base);

    if (array_queue_empty_ip(queue)) {
        return true;
    } else {
        data_i = queue->space.base;
        data_limit = queue->space.base + array_queue_size(queue);

        i = 0;
        restore_array = queue->space.base[queue->space.dim];

        do {
            if (restore_array[i] != *data_i) {
                dp_free(restore_array);
                return false;
            }
            i++;
            data_i++;
        } while (data_i != data_limit);

        dp_free(restore_array);
        return true;
    }
}

