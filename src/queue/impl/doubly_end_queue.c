struct doubly_end_queue *
doubly_end_queue_create(void)
{
    struct doubly_end_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0u;
    }

    queue->front = malloc_ds(sizeof(*queue->front));
    if (!queue->front) {
        free_ds(queue);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        dlinked_list_initial(&queue->front.link);
        queue->front->val = NULL;
        queue->tail = queue->front;
    }
    return queue;
}

void
doubly_end_queue_destroy(struct doubly_end_queue **queue)
{
    if (queue && *queue) {
        if ((*queue)->front) {
            free_ds((*queue)->front);
        }
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
        assert(queue->front == doubly_end_queue_list_next(queue->tail));
        tmp = queue->front;
        do {
            tmp = doubly_end_queue_list_next(tmp);
            retval++;
        } while (tmp != queue->front);
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
            dlinked_list_insert_before(&queue->front->link, &tmp->link);
            queue->front = tmp;
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
            dlinked_list_insert_after(&queue->tail->link, &tmp->link);
            queue->tail = tmp;
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
                /* If the last node, empty the deque instance. */
                free_ds(queue->front);
                queue->front = NULL;
                queue->tail = NULL;
            } else {
                free_ds(queue->front);
                queue->front = next;
            }
        }
    }
    return;
}
