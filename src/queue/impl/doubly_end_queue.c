s_doubly_end_queue_t *
doubly_end_queue_create(void)
{
    s_doubly_end_queue_t *queue;

    queue = memory_cache_allocate(sizeof(*queue));

    return queue;
}

bool
doubly_end_queue_structure_legal_p(s_doubly_end_queue_t *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else if (complain_null_pointer_p(queue->head)) {
        return false;
    } else if (complain_null_pointer_p(queue->tail)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
doubly_end_queue_list_structure_legal_p(s_doubly_end_queue_list_t *list)
{
    if (complain_null_pointer_p(list)) {
        return false;
    } else {
        return doubly_linked_list_structure_legal_p(&list->link);
    }
}

void
doubly_end_queue_destroy(s_doubly_end_queue_t **queue)
{
    if (!complain_null_pointer_p(queue) && doubly_end_queue_structure_legal_p(*queue)) {
        if (!doubly_end_queue_empty_ip(*queue)) {
            doubly_end_queue_cleanup_i(*queue);
        }

        memory_cache_free(*queue);
        *queue = NULL;
    }
}

uint32
doubly_end_queue_length(s_doubly_end_queue_t *queue)
{
    uint32 retval;
    s_doubly_end_queue_list_t *link;

    if (!doubly_end_queue_structure_legal_p(queue)) {
        return QUEUE_SIZE_INVALID;
    } else {
        if (doubly_end_queue_empty_ip(queue)) {
            pr_log_info("Empty doubly end queue.\n");
            return 0u;
        } else {
            retval = 0u;
            link = queue->head;

            do {
                link = doubly_end_queue_list_next(link);
                retval++;
            } while (link != queue->head);

            return retval;
        }
    }
}

static inline s_doubly_end_queue_list_t *
doubly_end_queue_list_reflect(s_doubly_linked_list_t *list)
{
    ptr_t offset;

    assert_exit(doubly_linked_list_structure_legal_p(list));

    offset = (ptr_t)&((s_doubly_end_queue_list_t *)0)->link;

    return (void *)((ptr_t)list - offset);
}

static inline s_doubly_end_queue_list_t *
doubly_end_queue_list_next(s_doubly_end_queue_list_t *node)
{
    assert_exit(doubly_end_queue_list_structure_legal_p(node));

    return doubly_end_queue_list_reflect(node->link.next);
}

static inline s_doubly_end_queue_list_t *
doubly_end_queue_list_previous(s_doubly_end_queue_list_t *node)
{
    assert_exit(doubly_end_queue_list_structure_legal_p(node));

    return doubly_end_queue_list_reflect(node->link.previous);
}

static inline bool
doubly_end_queue_empty_ip(s_doubly_end_queue_t *queue)
{
    assert_exit(doubly_end_queue_structure_legal_p(queue));

    if (NULL == queue->head && NULL == queue->tail) {
        return true;
    } else {
        return false;
    }
}

bool
doubly_end_queue_empty_p(s_doubly_end_queue_t *queue)
{
    if (complain_null_pointer_p(queue)) {
        return false;
    } else {
        return doubly_end_queue_empty_ip(queue);
    }
}

void
doubly_end_queue_head_enter(s_doubly_end_queue_t *queue, void *member)
{
    s_doubly_end_queue_list_t *list;

    if (doubly_end_queue_structure_legal_p(queue)) {
        list = memory_cache_allocate(sizeof(*list));
        list->val = member;

        if (doubly_end_queue_empty_ip(queue)) {
            queue->head = list;
            queue->tail = list;
            doubly_linked_list_initial(&queue->head->link);
        } else {
            doubly_linked_list_insert_before(&queue->head->link, &list->link);
            queue->head = list;
        }
    }
}

void
doubly_end_queue_tail_enter(s_doubly_end_queue_t *queue, void *member)
{
    s_doubly_end_queue_list_t *list;

    if (doubly_end_queue_structure_legal_p(queue)) {
        list = memory_cache_allocate(sizeof(*list));
        list->val = member;

        if (doubly_end_queue_empty_ip(queue)) {
            queue->head = list;
            queue->tail = list;
            doubly_linked_list_initial(&queue->head->link);
        } else {
            doubly_linked_list_insert_after(&queue->tail->link, &list->link);
            queue->tail = list;
        }
    }
}

void *
doubly_end_queue_head(s_doubly_end_queue_t *queue)
{
    if (!doubly_end_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (doubly_end_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else {
        return queue->head->val;
    }
}

void *
doubly_end_queue_tail(s_doubly_end_queue_t *queue)
{
    if (!doubly_end_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (doubly_end_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else {
        return queue->tail->val;
    }
}

void *
doubly_end_queue_head_leave(s_doubly_end_queue_t *queue)
{
    void *retval;
    s_doubly_linked_list_t *link;
    s_doubly_end_queue_list_t *next;

    if (!doubly_end_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else if (doubly_end_queue_empty_ip(queue)) {
        pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
        return PTR_INVALID;
    } else {
        retval = queue->head->val;
        next = doubly_end_queue_list_next(queue->head);

        if (next == queue->head) {
            doubly_end_queue_last_node_clean(queue);
        } else {
            link = &queue->head->link;
            doubly_linked_list_remove(&link);
            memory_cache_free(queue->head);
            queue->head = next;
        }
        return retval;
    }
}

void *
doubly_end_queue_tail_leave(s_doubly_end_queue_t *queue)
{
    void *retval;
    s_doubly_linked_list_t *link;
    s_doubly_end_queue_list_t *list;

    if (!doubly_end_queue_structure_legal_p(queue)) {
        return PTR_INVALID;
    } else {
        if (doubly_end_queue_empty_ip(queue)) {
            pr_log_warn("Attempt to leave from _EMPTY_ queue.\n");
            return PTR_INVALID;
        } else {
            retval = queue->tail->val;
            list = doubly_end_queue_list_previous(queue->tail);

            if (list == queue->tail) {
                doubly_end_queue_last_node_clean(queue);
            } else {
                link = &queue->tail->link;
                doubly_linked_list_remove(&link);
                memory_cache_free(queue->tail);
                queue->tail = list;
            }
            return retval;
        }
    }
}

static inline void
doubly_end_queue_last_node_clean(s_doubly_end_queue_t *queue)
{
    assert_exit(doubly_end_queue_structure_legal_p(queue));
    assert_exit(queue->head == queue->tail);

    memory_cache_free(queue->head);
    queue->head = NULL;
    queue->tail = NULL;
}

static inline void
doubly_end_queue_cleanup_i(s_doubly_end_queue_t *queue)
{
    s_doubly_end_queue_list_t *list;
    s_doubly_end_queue_list_t *next;
    s_doubly_linked_list_t *link;

    assert_exit(doubly_end_queue_structure_legal_p(queue));

    list = queue->head;

    while (list != queue->tail) {
        next = doubly_end_queue_list_next(list);
        link = &list->link;
        doubly_linked_list_remove(&link);
        memory_cache_free(list);

        list = next;
    }

    queue->head = list;
    doubly_end_queue_last_node_clean(queue);
}

void
doubly_end_queue_cleanup(s_doubly_end_queue_t *queue)
{
    if (!doubly_end_queue_structure_legal_p(queue)) {
        return;
    } else {
        doubly_end_queue_cleanup_i(queue);
    }
}

void
doubly_end_queue_iterate(s_doubly_end_queue_t *queue, void (*handle)(void *))
{
    s_doubly_end_queue_list_t *list;

    if (!doubly_end_queue_structure_legal_p(queue)) {
        return;
    } else if (doubly_end_queue_empty_ip(queue)) {
        pr_log_info("Iterate on _EMPTY_ queue, nothing will be done.\n");
    } else {
        list = queue->head;

        do {
            (*handle)(list->val);
            list = doubly_end_queue_list_next(list);
        } while (list != queue->head);
    }
}

