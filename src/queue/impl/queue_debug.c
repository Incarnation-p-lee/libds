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

