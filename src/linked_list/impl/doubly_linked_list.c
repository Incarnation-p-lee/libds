struct doubly_linked_list *
doubly_linked_list_create(void)
{
    return doubly_linked_list_node_create(NULL, 0u);
}

struct doubly_linked_list *
doubly_linked_list_node_create(void *val, uint32 sid)
{
    struct doubly_linked_list *head;

    head = malloc_ds(sizeof(*head));

    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        doubly_linked_list_node_initial(head, val, sid);
        return head;
    }
}

void
doubly_linked_list_node_initial(struct doubly_linked_list *head,
    void *val, uint32 sid)
{
    if (!head) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        doubly_linked_list_node_sid_set(head, sid);
        doubly_linked_list_node_next_set(head, head);
        doubly_linked_list_node_previous_set(head, head);
        doubly_linked_list_node_val_set(head, val);
    }

    return;
}

void
doubly_linked_list_initial(struct doubly_linked_list *head)
{
    doubly_linked_list_node_initial(head, NULL, 0u);
    return;
}

struct doubly_linked_list *
doubly_linked_list_generate(uint32 *sid, uint32 size)
{
    struct doubly_linked_list *head;
    register struct doubly_linked_list *node;
    register uint32 *iter;

    if (!sid) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        iter= sid;
        node = doubly_linked_list_node_create(NULL, *iter++);
        head = node;

        while (iter< sid + size) {
            doubly_linked_list_node_append(node, *iter++);
            node = doubly_linked_list_node_next(node);
        }

        return head;
    }
}

void
doubly_linked_list_node_append(struct doubly_linked_list *node, uint32 sid)
{
    struct doubly_linked_list *next;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (NULL == doubly_linked_list_node_next(node)
            || NULL == doubly_linked_list_node_previous(node)) {
            pr_log_warn("Destroyed data structure.\n");
        } else {
            next = doubly_linked_list_node_create(NULL, sid);
            doubly_linked_list_node_insert_after(node, next);
        }
    }

    return;
}

void
doubly_linked_list_node_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        doubly_linked_list_node_previous_set(cur->next, node);
        doubly_linked_list_node_next_set(node, cur->next);
        doubly_linked_list_node_next_set(cur, node);
        doubly_linked_list_node_previous_set(node, cur);
    }

    return;
}

void
doubly_linked_list_node_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *prev;

    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        prev = doubly_linked_list_node_previous(cur);
        doubly_linked_list_node_insert_after(prev, node);
    }

    return;
}

struct doubly_linked_list *
doubly_linked_list_node_copy(struct doubly_linked_list *node)
{
    struct doubly_linked_list *copy;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        copy = doubly_linked_list_node_create(
            doubly_linked_list_node_val(node),
            doubly_linked_list_node_sid(node));

        doubly_linked_list_node_next_set(copy,
            doubly_linked_list_node_next(node));
        doubly_linked_list_node_previous_set(copy,
            doubly_linked_list_node_previous(node));

        return copy;
    }
}

void
doubly_linked_list_destroy(struct doubly_linked_list **head)
{
    register struct doubly_linked_list *node;
    register struct doubly_linked_list *next;

    if (!head || !*head) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        /*
         * Do not call doubly_linked_list_remove_node for
         * the consider of performance drop.
         */
        next = doubly_linked_list_node_next(*head);

        while (*head != (node = next)) {
            next = doubly_linked_list_node_next(node);
            free_ds(node);
        }

        free_ds(node);
        *head = NULL;
    }

    return;
}

uint32
doubly_linked_list_length(struct doubly_linked_list *head)
{
    uint32 length;
    register struct doubly_linked_list *node;

    if (!head) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0u;
    } else {
        node = head;
        length = 0;

        do {
            length++;
            node = doubly_linked_list_node_next(node);
        } while (node != head);

        return length;
    }
}

struct doubly_linked_list *
doubly_linked_list_node_by_index(struct doubly_linked_list *head,
    uint32 index)
{
    register struct doubly_linked_list *node;
    uint32 len;

    if (!head) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        node = head;
        len = doubly_linked_list_length(head);

        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        while (index > 0) {
            node = doubly_linked_list_node_next(node);
            index--;
        }

        return node;
    }

}


void
doubly_linked_list_node_exchange(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec)
{
    struct doubly_linked_list *prev_fir;
    struct doubly_linked_list *prev_sec;

    if (!fir || !sec) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        if (!doubly_linked_list_contains_p(fir, sec) || (fir == sec)) {
            pr_log_warn("Exchange itself or exchange in different list.\n");
        } else {
            prev_fir = doubly_linked_list_node_previous(fir);
            prev_sec = doubly_linked_list_node_previous(sec);

            doubly_linked_list_node_lazy_remove(fir);
            doubly_linked_list_node_lazy_remove(sec);
            doubly_linked_list_node_insert_after(prev_fir, sec);
            doubly_linked_list_node_insert_after(prev_sec, fir);
        }
    }

    return;
}

bool
doubly_linked_list_contains_p(struct doubly_linked_list *tar,
    struct doubly_linked_list *node)
{
    register struct doubly_linked_list *iter;

    if (!tar || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        iter = tar;

        do {
            if (iter == node) {
                return true;
            }
            iter = doubly_linked_list_node_next(iter);
        } while (iter != tar);

        return false;
    }
}

void
doubly_linked_list_serialize(struct doubly_linked_list *head)
{
    struct doubly_linked_list *node;
    uint32 index;

    if (!head) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        index = 0;
        node = head;

        do {
            doubly_linked_list_node_sid_set(node, index++);
            node = doubly_linked_list_node_next(node);
        } while (node != head);
    }

    return;
}

struct doubly_linked_list *
doubly_linked_list_node_remove(struct doubly_linked_list **node)
{
    struct doubly_linked_list *head;

    if (!node || !*node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        head = doubly_linked_list_node_lazy_remove(*node);
        free_ds(*node);
        *node = NULL;

        return head;
    }
}

struct doubly_linked_list *
doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node)
{
    struct doubly_linked_list *retval;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        if (node == doubly_linked_list_node_next(node)) {
            return NULL;
        } else {
            doubly_linked_list_node_next_set(node->previous,
                doubly_linked_list_node_next(node));
            doubly_linked_list_node_previous_set(node->next,
                doubly_linked_list_node_previous(node));

            retval = doubly_linked_list_node_next(node);
            doubly_linked_list_node_next_set(node, node);
            doubly_linked_list_node_previous_set(node, node);

            return retval;
        }
    }
}

void
doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *))
{
    register struct doubly_linked_list *node;

    if (!head || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node = head;

        do {
            (*handler)(doubly_linked_list_node_val(node));
            node = doubly_linked_list_node_next(node);
        } while (node != head);
    }

    return;
}

struct doubly_linked_list *
doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n)
{
    register struct doubly_linked_list *iter;
    register struct doubly_linked_list *new;

    if (!m || !n) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        do {
            if (!doubly_linked_list_contains_p(m, iter)) {
                new = doubly_linked_list_node_create(
                    doubly_linked_list_node_val(iter),
                    doubly_linked_list_node_sid(iter));

                doubly_linked_list_node_insert_before(m, new);
            }
            iter = doubly_linked_list_node_next(iter);
        } while (iter != n);

        return m;
    }
}

