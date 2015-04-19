struct doubly_linked_list *
doubly_linked_list_create(void)
{
    return doubly_linked_list_node_create(NULL, 0u);
}

struct doubly_linked_list *
doubly_linked_list_node_create(void *val, uint32 id)
{
    struct doubly_linked_list *head;

    head = malloc_ds(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        doubly_linked_list_node_initial(head, val, id);
    }

    return head;
}

void
doubly_linked_list_node_initial(struct doubly_linked_list *head,
    void *val, uint32 id)
{
    if (head) {
        doubly_linked_list_node_id_set(head, id);
        doubly_linked_list_node_next_set(head, head);
        doubly_linked_list_node_previous_set(head, head);
        doubly_linked_list_node_val_set(head, val);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
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
doubly_linked_list_generate(uint32 *id, uint32 size)
{
    struct doubly_linked_list *head;
    register struct doubly_linked_list *node;
    register uint32 *iterator;

    head = NULL;
    if (id) {
        iterator = id;
        node = doubly_linked_list_node_create(NULL, *iterator++);
        head = node;

        while (iterator < id + size) {
            doubly_linked_list_node_append(node, *iterator++);
            node = doubly_linked_list_node_next_get(node);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return head;
}

void
doubly_linked_list_node_append(struct doubly_linked_list *node, uint32 id)
{
    struct doubly_linked_list *next;

    if (node) {
        if (NULL == doubly_linked_list_node_next_get(node)
            || NULL == doubly_linked_list_node_previous_get(node)) {
            pr_log_warn("Destroyed data structure.\n");
        }

        next = doubly_linked_list_node_create(NULL, id);
        doubly_linked_list_node_insert_after(node, next);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
doubly_linked_list_node_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (cur && node) {
        doubly_linked_list_node_previous_set(cur->next, node);
        doubly_linked_list_node_next_set(node, cur->next);
        doubly_linked_list_node_next_set(cur, node);
        doubly_linked_list_node_previous_set(node, cur);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
doubly_linked_list_node_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *prev;

    if (cur && node) {
        prev = doubly_linked_list_node_previous_get(cur);
        doubly_linked_list_node_insert_after(prev, node);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
doubly_linked_list_destroy(struct doubly_linked_list **head)
{
    register struct doubly_linked_list *node;
    register struct doubly_linked_list *next;

    if (head && *head) {
        /*
         * Do not call doubly_linked_list_remove_node for
         * the consider of performance drop.
         */
        next = doubly_linked_list_node_next_get(*head);
        while (*head != (node = next)) {
            next = doubly_linked_list_node_next_get(node);
            free_ds(node);
        }

        free_ds(node);
        *head = NULL;
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

uint32
doubly_linked_list_length(struct doubly_linked_list *head)
{
    uint32 length;
    register struct doubly_linked_list *node;

    length = 0;
    if (head) {
        node = head;
        do {
            length++;
            node = doubly_linked_list_node_next_get(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return length;
}

struct doubly_linked_list *
doubly_linked_list_node_get_by_index(struct doubly_linked_list *head,
    uint32 index)
{
    register struct doubly_linked_list *node;
    uint32 len;

    node = NULL;
    if (head) {
        len = doubly_linked_list_length(head);
        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        node = head;
        while (index > 0) {
            node = doubly_linked_list_node_next_get(node);
            index--;
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return node;
}


void
doubly_linked_list_node_exchange(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec)
{
    struct doubly_linked_list *prev_fir;
    struct doubly_linked_list *prev_sec;

    if (fir && sec) {
        if (doubly_linked_list_contains_p(fir, sec) && (fir != sec)) {
            prev_fir = doubly_linked_list_node_previous_get(fir);
            prev_sec = doubly_linked_list_node_previous_get(sec);

            doubly_linked_list_node_lazy_remove(fir);
            doubly_linked_list_node_lazy_remove(sec);
            doubly_linked_list_node_insert_after(prev_fir, sec);
            doubly_linked_list_node_insert_after(prev_sec, fir);
        } else {
            pr_log_warn("Exchange itself or exchange in different list.\n");
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

bool
doubly_linked_list_contains_p(struct doubly_linked_list *tar,
    struct doubly_linked_list *node)
{
    register struct doubly_linked_list *iter;
    bool contains;

    contains = false;
    if (tar && node) {
        iter = tar;
        do {
            if (iter == node) {
                contains = true;
                break;
            }
            iter = doubly_linked_list_node_next_get(iter);
        } while (iter != tar);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return contains;
}

void
doubly_linked_list_serialize(struct doubly_linked_list *head)
{
    struct doubly_linked_list *node;
    uint32 index;

    if (head) {
        index = 0;
        node = head;
        do {
            doubly_linked_list_node_id_set(node, index++);
            node = doubly_linked_list_node_next_get(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct doubly_linked_list *
doubly_linked_list_node_remove(struct doubly_linked_list *node)
{
    struct doubly_linked_list *next;

    next = NULL;
    if (node) {
        doubly_linked_list_node_lazy_remove(node);
        if (doubly_linked_list_node_next_get(node) != node) {
            next = doubly_linked_list_node_next_get(node);
        }
        free_ds(node);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return next;
}

void
doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node)
{
    if (node) {
        doubly_linked_list_node_next_set(node->previous,
            doubly_linked_list_node_next_get(node));
        doubly_linked_list_node_previous_set(node->next,
            doubly_linked_list_node_previous_get(node));
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *))
{
    register struct doubly_linked_list *node;

    if (head && handler) {
        node = head;
        do {
            (*handler)(doubly_linked_list_node_val_get(node));
            node = doubly_linked_list_node_next_get(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct doubly_linked_list *
doubly_linked_list_join(struct doubly_linked_list *m, struct doubly_linked_list *n)
{
    register struct doubly_linked_list *iter;
    register struct doubly_linked_list *new;

    if (m && n) {
        iter = n;
        do {
            if (!doubly_linked_list_contains_p(m, iter)) {
                new = doubly_linked_list_node_create(
                    doubly_linked_list_node_val_get(iter),
                    doubly_linked_list_node_id_get(iter));

                doubly_linked_list_node_insert_before(m, new);
            }
            iter = doubly_linked_list_node_next_get(iter);
        } while (iter != n);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return m ? m : n;
}
