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
        queue->tail = queue->front;
    }
    return queue;
}

void
doubly_end_queue_destroy(struct doubly_end_queue **queue)
{
    if (queue && *queue) {
        free_ds((*queue)->front);
        free_ds(*queue);
        *queue = NULL;
    }
    return;
}

uint32
doubly_end_queue_capacity(struct doubly_end_queue *queue)
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
