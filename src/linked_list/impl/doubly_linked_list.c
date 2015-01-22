struct doubly_linked_list *
dlinked_list_create(void)
{
    return dlinked_list_node_create(NULL, 0u);
}

struct doubly_linked_list *
dlinked_list_node_create(void *val, uint32 id)
{
    struct doubly_linked_list *head;

    head = malloc_ds(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        dlinked_list_node_initial(head, val, id);
    }

    return head;
}

void
dlinked_list_node_initial(struct doubly_linked_list *head, void *val, uint32 id)
{
    if (head) {
        head->id = id;
        head->next = head;
        head->previous = head;
        head->val = val;
    }

    return;
}

void
dlinked_list_initial(struct doubly_linked_list *head)
{
    dlinked_list_node_initial(head, NULL, 0u);
    return;
}

struct doubly_linked_list *
dlinked_list_generate(uint32 *id, uint32 size)
{
    struct doubly_linked_list *head;
    register struct doubly_linked_list *node;
    register uint32 *iterator;

    head = NULL;
    if (id && size > 0) {
        iterator = id;
        node = dlinked_list_node_create(NULL, *iterator++);
        head = node;

        while (iterator < id + size) {
            dlinked_list_node_append(node, *iterator++);
            node = node->next;
        }
    }

    return head;
}

void
dlinked_list_node_set_val(struct doubly_linked_list *node, void *val)
{
    if (node) {
        node->val = val;
    }
    return;
}

void *
dlinked_list_node_get_val(struct doubly_linked_list *node)
{
    return node ? node->val : NULL;
}

void
dlinked_list_node_append(struct doubly_linked_list *node, uint32 id)
{
    struct doubly_linked_list *next;

    if (node) {
        if (!node->next || !node->previous) {
            pr_log_warn("Uninitialized or destroyed doubly linked list node.\n");
        } else {
            next = dlinked_list_node_create(NULL, id);
            dlinked_list_node_insert_after(node, next);
        }
    }

    return;
}

struct doubly_linked_list *
dlinked_list_node_next(struct doubly_linked_list *node)
{
    struct doubly_linked_list *next;

    next = NULL;
    if (!node->next || !node->previous) {
        pr_log_warn("Uninitialized or destroyed doubly linked list node.\n");
    } else if (node && node->next && node->previous) {
        next = node->next;
    }

    return next;
}

struct doubly_linked_list *
dlinked_list_node_previous(struct doubly_linked_list *node)
{
    struct doubly_linked_list *previous;

    previous = NULL;
    if (node && node->next && node->previous) {
        previous = node->previous;
    } else if (!node->next || !node->previous) {
        pr_log_warn("Uninitialized or destroyed doubly linked list node.\n");
    }

    return previous;
}

void
dlinked_list_node_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (cur && node)
    {
        cur->next->previous = node;
        node->next = cur->next;
        cur->next = node;
        node->previous = cur;
    }

    return;
}

void
dlinked_list_node_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *prev;

    if (cur && node)
    {
        prev = cur->previous;
        dlinked_list_node_insert_after(prev, node);
    }

    return;
}

void
dlinked_list_destroy(struct doubly_linked_list **head)
{
    register struct doubly_linked_list *node;
    register struct doubly_linked_list *next;

    if (head && *head) {
        /*
         * Do not call dlinked_list_remove_node for
         * the consider of performance drop.
         */
        next = (*head)->next;
        while (*head != (node = next)) {
            next = node->next;
            free_ds(node);
        }

        free_ds(node);
        *head = NULL;
    }

    return;
}

uint32
dlinked_list_length(struct doubly_linked_list *head)
{
    uint32 length;
    register struct doubly_linked_list *node;

    length = 0;
    if (head) {
        node = head;
        do {
            length++;
            node = node->next;
        } while (node != head);
    }

    return length;
}

struct doubly_linked_list *
dlinked_list_node_get_by_index(struct doubly_linked_list *head, uint32 index)
{
    register struct doubly_linked_list *node;

    node = NULL;
    if (head) {
        if (index <= dlinked_list_length(head)) {
            node = head;
            while (index > 0) {
                node = node->next;
                index--;
            }
        }
    }

    return node;
}

void
dlinked_list_print(FILE *fd, char *msg, struct doubly_linked_list *head)
{
    register struct doubly_linked_list *iterator;
    char *default_msg = "Default doubly linked list";

    if (head) {
        fprintf(fd, "[%s]:\n", msg);
        if (!msg) {
            msg = default_msg;
        }

        iterator = head;
        do {
            fprintf(fd, "%d ->\n", iterator->id);
            iterator = iterator->next;
        } while (iterator != head);
    }
    fprintf(fd, "NULL\n");

    return;
}

void
dlinked_list_node_exchange(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec)
{
    struct doubly_linked_list *prev_fir;
    struct doubly_linked_list *prev_sec;

    if (fir && sec) {
        if (dlinked_list_contains_p(fir, sec) && (fir != sec)) {
            prev_fir = fir->previous;
            prev_sec = sec->previous;

            dlinked_list_node_lazy_remove(fir);
            dlinked_list_node_lazy_remove(sec);
            dlinked_list_node_insert_after(prev_fir, sec);
            dlinked_list_node_insert_after(prev_sec, fir);
        }
    }

    return;
}

bool
dlinked_list_contains_p(struct doubly_linked_list *tar,
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
            iter = iter->next;
        } while (iter != tar);
    }

    return contains;
}

void
dlinked_list_serialize(struct doubly_linked_list *head)
{
    struct doubly_linked_list *node;
    uint32 index;

    if (head) {
        index = 0;
        node = head;
        do {
            node->id = index++;
            node = node->next;
        } while (node != head);
    }

    return;
}

struct doubly_linked_list *
dlinked_list_node_remove(struct doubly_linked_list *node)
{
    struct doubly_linked_list *next;

    next = NULL;
    if (node) {
        dlinked_list_node_lazy_remove(node);
        if (node->next != node) {
            next = node->next;
        }
        free_ds(node);
    }

    return next;
}

void
dlinked_list_node_lazy_remove(struct doubly_linked_list *node)
{
    if (node) {
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }

    return;
}

void
dlinked_list_iterate(struct doubly_linked_list *head,
    void (*handler)(struct doubly_linked_list *))
{
    register struct doubly_linked_list *node;

    if (head && handler) {
        node = head;
        do {
            (*handler)(node);
            node = node->next;
        } while (node != head);
    }

    return;
}

struct doubly_linked_list *
dlinked_list_join(struct doubly_linked_list *m, struct doubly_linked_list *n)
{
    register struct doubly_linked_list *iter;
    register struct doubly_linked_list *new;

    if (m && n) {
        iter = n;
        do {
            new = dlinked_list_node_create(iter->val, iter->id);
            dlinked_list_node_insert_before(m, new);
            iter = iter->next;
        } while (iter != n);
    }

    return m ? m : n;
}

void
dlinked_list_node_redundant_remove(struct doubly_linked_list *head)
{


}
