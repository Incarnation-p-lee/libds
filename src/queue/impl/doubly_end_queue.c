struct doubly_end_queue *
doubly_end_queue_create(void)
{
    struct doubly_end_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        doubly_end_queue_sid_set(queue, 0x0u);
        queue->head = NULL;
        queue->tail = NULL;
    }

    return queue;
}

void
doubly_end_queue_destroy(struct doubly_end_queue **queue)
{
    if (!queue || !*queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (doubly_end_queue_empty_p(queue)) {
            pr_log_info("Empty doubly end queue.\n");
        } else {
            tmp = queue->head;
            do {
                tmp = doubly_end_queue_list_next(tmp);
                retval++;
            } while (tmp != queue->head);
        }
    }
    return retval;
}

static inline struct doubly_end_queue_list *
doubly_end_queue_list_offset_reflect(struct doubly_linked_list *link)
{
    assert(NULL != link);

    return (void *)((void *)link
        - (void *)(&((struct doubly_end_queue_list *)0)->link));
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

/*
 * NULL _ARGV_ will be treated as full, _RETURN_ false.
 */
bool
doubly_end_queue_empty_p(struct doubly_end_queue *queue)
{
    bool is_empty;

    is_empty = false;
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (NULL == queue->head && NULL == queue->tail) {
            is_empty = true;
        }
    }

    return is_empty;
}

void
doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (!queue || !member) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = malloc_ds(sizeof(*tmp));
        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;
            if (doubly_end_queue_empty_p(queue)) {
                queue->head = tmp;
                queue->tail = tmp;
                doubly_linked_list_initial(&queue->head->link);
            } else {
                doubly_linked_list_node_insert_before(&queue->head->link, &tmp->link);
                queue->head = tmp;
            }
        }
    }
    return;
}

void
doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member)
{
    struct doubly_end_queue_list *tmp;

    if (!queue || !member) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = malloc_ds(sizeof(*tmp));
        if (!tmp) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            tmp->val = member;
            if (doubly_end_queue_empty_p(queue)) {
                queue->head = tmp;
                queue->tail = tmp;
                doubly_linked_list_initial(&queue->head->link);
            } else {
                doubly_linked_list_node_insert_after(&queue->tail->link, &tmp->link);
                queue->tail = tmp;
            }
        }
    }

    return;
}

void *
doubly_end_queue_head_leave(struct doubly_end_queue *queue)
{
    struct doubly_end_queue_list *next;
    void *retval;

    retval = NULL;
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (doubly_end_queue_empty_p(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        } else {
            retval = queue->head->val;
            next = doubly_end_queue_list_next(queue->head);

            if (next == queue->head) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                // FixMe doubly_linked_list_node_lazy_remove(&queue->head->link);
                free_ds(queue->head);
                queue->head = next;
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
    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (doubly_end_queue_empty_p(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        } else {
            retval = queue->tail->val;
            previous = doubly_end_queue_list_previous(queue->tail);

            if (previous == queue->tail) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                // FixMe doubly_linked_list_node_lazy_remove(&queue->tail->link);
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
    assert(queue->head == queue->tail);

    free_ds(queue->head);
    queue->head = NULL;
    queue->tail = NULL;

    return;
}

void
doubly_end_queue_cleanup(struct doubly_end_queue *queue)
{
    register struct doubly_end_queue_list *tmp;
    register struct doubly_end_queue_list *next;

    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = queue->head;
        if (!tmp) {
            pr_log_info("Cleaned queue, nothing will be done.\n");
        } else {
            while (tmp != queue->tail) {
                next = doubly_end_queue_list_next(tmp);
                // Fixme doubly_linked_list_node_lazy_remove(&tmp->link);
                free_ds(tmp);
                tmp = next;
            }
            queue->head = tmp;
            doubly_end_queue_last_node_clean(queue);
        }
    }

    return;
}

void
doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *))
{
    register struct doubly_end_queue_list *tmp;

    if (!queue) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = queue->head;
        if (!tmp) {
            pr_log_info("Iterate on _EMPTY_ queue, nothing will be done.\n");
        } else {
            do {
                (*handle)(tmp->val);
                tmp = doubly_end_queue_list_next(tmp);
            } while (tmp != queue->head);
        }
    }
    return;
}
