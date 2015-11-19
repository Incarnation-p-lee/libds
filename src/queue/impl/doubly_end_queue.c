struct doubly_end_queue *
doubly_end_queue_create(void)
{
    struct doubly_end_queue *queue;

    queue = malloc_ds(sizeof(*queue));

    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0x0u;
        queue->head = NULL;
        queue->tail = NULL;

        return queue;
    }
}

void
doubly_end_queue_destroy(struct doubly_end_queue **queue)
{
    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(*queue)) {
        if (!doubly_end_queue_empty_p_internal(*queue)) {
            doubly_end_queue_cleanup_internal(*queue);
        }

        free_ds(*queue);
        *queue = NULL;
    }
}

uint32
doubly_end_queue_length(struct doubly_end_queue *queue)
{
    uint32 retval;
    struct doubly_end_queue_list *tmp;

    if (complain_null_pointer_p(queue)) {
        return 0u;
    } else {
        if (doubly_end_queue_empty_p_internal(queue)) {
            pr_log_info("Empty doubly end queue.\n");
            return 0u;
        } else {
            retval = 0u;
            tmp = queue->head;

            do {
                tmp = doubly_end_queue_list_next(tmp);
                retval++;
            } while (tmp != queue->head);

            return retval;
        }
    }
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_offset_reflect(struct doubly_linked_list *link)
{
    void *offset;

    assert(NULL != link);

    offset = &((struct doubly_end_queue_list *)0)->link;

    return (void *)((void *)link - offset);
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_next(struct doubly_end_queue_list *node)
{
    assert(NULL != node);

    return doubly_end_queue_list_offset_reflect(node->link.next);
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_previous(struct doubly_end_queue_list *node)
{
    assert(NULL != node);

    return doubly_end_queue_list_offset_reflect(node->link.previous);
}

static inline bool
doubly_end_queue_empty_p_internal(struct doubly_end_queue *queue)
{
    assert(NULL != queue);

    if (NULL == queue->head && NULL == queue->tail) {
        return true;
    } else {
        return false;
    }
}

/*
 * NULL _ARGV_ will be treated as full, _RETURN_ false.
 */
bool
doubly_end_queue_empty_p(struct doubly_end_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else {
        return doubly_end_queue_empty_p_internal(queue);
    }
}

void
doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(member)) {
        tmp = malloc_ds(sizeof(*tmp));

        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;

            if (doubly_end_queue_empty_p_internal(queue)) {
                queue->head = tmp;
                queue->tail = tmp;
                doubly_linked_list_initial(&queue->head->link);
            } else {
                doubly_linked_list_node_insert_before_risky(&queue->head->link, &tmp->link);
                queue->head = tmp;
            }
        }
    }
}

void
doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (!complain_null_pointer_p(queue) && !complain_null_pointer_p(member)) {
        tmp = malloc_ds(sizeof(*tmp));

        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;

            if (doubly_end_queue_empty_p_internal(queue)) {
                queue->head = tmp;
                queue->tail = tmp;
                doubly_linked_list_initial(&queue->head->link);
            } else {
                doubly_linked_list_node_insert_after_risky(&queue->tail->link, &tmp->link);
                queue->tail = tmp;
            }
        }
    }
}

void *
doubly_end_queue_head_leave(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *tmp;
    struct doubly_linked_list *link;
    void *retval;

    if (complain_null_pointer_p(queue)) {
        return NULL;
    } else {
        if (doubly_end_queue_empty_p_internal(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
            return NULL;
        } else {
            retval = queue->head->val;
            tmp = doubly_end_queue_list_next(queue->head);

            if (tmp == queue->head) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                link = &queue->head->link;
                doubly_linked_list_node_remove(&link);
                free_ds(queue->head);
                queue->head = tmp;
            }

            return retval;
        }
    }
}

void *
doubly_end_queue_tail_leave(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *tmp;
    struct doubly_linked_list *link;
    void *retval;

    if (complain_null_pointer_p(queue)) {
        return NULL;
    } else {
        if (doubly_end_queue_empty_p_internal(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
            return NULL;
        } else {
            retval = queue->tail->val;
            tmp = doubly_end_queue_list_previous(queue->tail);

            if (tmp == queue->tail) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                link = &queue->tail->link;
                doubly_linked_list_node_remove(&link);
                free_ds(queue->tail);
                queue->tail = tmp;
            }

            return retval;
        }
    }
}

static inline void
doubly_end_queue_last_node_clean(struct doubly_end_queue *queue)
{
    assert(queue);
    assert(queue->head == queue->tail);

    free_ds(queue->head);
    queue->head = NULL;
    queue->tail = NULL;
}

static inline void
doubly_end_queue_cleanup_internal(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *tmp;
    struct doubly_end_queue_list *next;
    struct doubly_linked_list *link;

    assert(NULL != queue);
    assert(NULL != queue->head);

    tmp = queue->head;

    while (tmp != queue->tail) {
        next = doubly_end_queue_list_next(tmp);
        link = &tmp->link;
        doubly_linked_list_node_remove(&link);
        free_ds(tmp);

        tmp = next;
    }

    queue->head = tmp;
    doubly_end_queue_last_node_clean(queue);
}

void
doubly_end_queue_cleanup(struct doubly_end_queue *queue)
{
    if (complain_null_pointer_p(queue)) {
        return;
    } else if (!queue->head) {
        pr_log_info("Cleaned queue, nothing will be done.\n");
    } else {
        doubly_end_queue_cleanup_internal(queue);
    }
}

void
doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *))
{
    register struct doubly_end_queue_list *tmp;

    if (complain_null_pointer_p(queue)) {
        return;
    } else if (!queue->head) {
        pr_log_info("Iterate on _EMPTY_ queue, nothing will be done.\n");
    } else {
        tmp = queue->head;

        do {
           (*handle)(tmp->val);
           tmp = doubly_end_queue_list_next(tmp);
        } while (tmp != queue->head);
    }
}

