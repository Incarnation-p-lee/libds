struct doubly_end_queue *
doubly_end_queue_create(void)
{
    struct doubly_end_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0u;
        queue->front = NULL;
        queue->tail = NULL;
    }
    return queue;
}

void
doubly_end_queue_destroy(struct doubly_end_queue **queue)
{
    if (queue && *queue) {
        doubly_end_queue_cleanup(*queue);
        free_ds(*queue);
        *queue = NULL;
    }
    return;
}

uint32
doubly_end_queue_length(struct doubly_end_queue *queue)
{
    uint32 retval;
    struct doubly_end_queue_list *tmp;

    retval = 0u;
    if (queue) {
        if (doubly_end_queue_is_empty(queue)) {
            tmp = queue->front;
            do {
                tmp = doubly_end_queue_list_next(tmp);
                retval++;
            } while (tmp != queue->front);
        }
    }
    return retval;
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_next(struct doubly_end_queue_list *node)
{
    struct doubly_end_queue_list *next;

    next = NULL;
    if (node) {
        next = UNOFFSET_OF(node->link.next, struct doubly_end_queue_list, link);
    }
    return next;
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_previous(struct doubly_end_queue_list *node)
{
    struct doubly_end_queue_list *previous;

    previous = NULL;
    if (node) {
        previous = UNOFFSET_OF(node->link.previous, struct doubly_end_queue_list, link);
    }
    return previous;
}

/*
 * NULL _ARGV_ will be treated as full, _RETURN_ false.
 */
bool
doubly_end_queue_is_empty(struct doubly_end_queue *queue)
{
    bool is_empty;

    is_empty = false;
    if (queue) {
        if (NULL == queue->front && NULL == queue->tail) {
            is_empty = true;
        }
    }
    return is_empty;
}

void
doubly_end_queue_front_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (queue && member) {
        tmp = malloc_ds(sizeof(*tmp));
        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;
            if (doubly_end_queue_is_empty(queue)) {
                queue->front = tmp;
                queue->tail = tmp;
                dlinked_list_initial(&queue->front->link);
            } else {
                dlinked_list_insert_before(&queue->front->link, &tmp->link);
                queue->front = tmp;
            }
        }
    }
    return;
}

void
doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (queue && member) {
        tmp = malloc_ds(sizeof(*tmp));
        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;
            if (doubly_end_queue_is_empty(queue)) {
                queue->front = tmp;
                queue->tail = tmp;
                dlinked_list_initial(&queue->front->link);
            } else {
                dlinked_list_insert_after(&queue->tail->link, &tmp->link);
                queue->tail = tmp;
            }
        }
    }
    return;
}

void *
doubly_end_queue_front_leave(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *next;
    void *retval;

    retval = NULL;
    if (queue) {
        if (!doubly_end_queue_is_empty(queue)) {
            retval = queue->front->val;
            next = doubly_end_queue_list_next(queue->front);

            if (next == queue->front) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                dlinked_list_lazy_remove_node(&queue->front->link);
                free_ds(queue->front);
                queue->front = next;
            }
        }
    }
    return retval;
}

void *
doubly_end_queue_tail_leave(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *previous;
    void *retval;

    retval = NULL;
    if (queue) {
        if (!doubly_end_queue_is_empty(queue)) {
            retval = queue->tail->val;
            previous = doubly_end_queue_list_previous(queue->front);

            if (previous == queue->tail) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                dlinked_list_lazy_remove_node(&queue->tail->link);
                free_ds(queue->tail);
                queue->tail = previous;
            }
        }
    }
    return retval;
}

static inline void
doubly_end_queue_last_node_clean(struct doubly_end_queue *queue)
{
    assert(queue);
    assert(queue->front == queue->tail);

    free_ds(queue->front);
    queue->front = NULL;
    queue->tail = NULL;
    return;
}

void
doubly_end_queue_cleanup(struct doubly_end_queue *queue)
{
    register struct doubly_end_queue_list *tmp;
    register struct doubly_end_queue_list *next;

    if (queue) {
        tmp = queue->front;
        if (tmp) {
            while (tmp != queue->tail) {
                next = doubly_end_queue_list_next(tmp);
                dlinked_list_lazy_remove_node(&tmp->link);
                free_ds(tmp);
                tmp = next;
            }
            doubly_end_queue_last_node_clean(queue);
        }
    }
    return;
}

void
doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *))
{
    register struct doubly_end_queue_list *tmp;

    if (queue) {
        tmp = queue->front;
        if (tmp) {
            do {
                (*handle)(tmp->val);
                tmp = doubly_end_queue_list_next(tmp);
            } while (tmp != queue->front);
        }
    }
    return;
}
