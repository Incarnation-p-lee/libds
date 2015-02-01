struct single_linked_list *
single_linked_list_create(void)
{
    return single_linked_list_node_create(NULL, 0u);
}

struct single_linked_list *
single_linked_list_node_create(void *val, uint32 id)
{
    struct single_linked_list *head;

    head = malloc_ds(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        single_linked_list_node_initial(head, val, id);
    }

    return head;
}

void
single_linked_list_initial(struct single_linked_list *head)
{
    single_linked_list_node_initial(head, NULL, 0u);
    return;
}

void
single_linked_list_node_initial(struct single_linked_list *head, void *val, uint32 id)
{
    if (head) {
        head->id = id;
        head->val = val;
        head->next = head;
    }

    return;
}

struct single_linked_list *
single_linked_list_generate(uint32 *id, uint32 size)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    register uint32 *iterator;

    head = NULL;
    if (id && size > 0) {
        iterator = id;
        node = single_linked_list_create();
        node->id = *iterator++;
        head = node;

        while (iterator < id + size) {
            single_linked_list_node_append(node, *iterator++);
            node = node->next;
        }
    }

    return head;
}

void
single_linked_list_node_set_val(struct single_linked_list *node, void *val)
{
    if (node) {
        node->val = val;
    }
    return;
}

void *
single_linked_list_node_get_val(struct single_linked_list *node)
{
    return node ? node->val : node;
}

void
single_linked_list_node_append(struct single_linked_list *node, uint32 value)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
        if (!node->next) {
            pr_log_warn("Uninitialized or destroyed single linked list node.\n");
        } else {
            next = single_linked_list_create();
            next->id = value;
            single_linked_list_node_insert_after(node, next);
        }
    }

    return;
}

struct single_linked_list *
single_linked_list_node_next(struct single_linked_list *node)
{
    struct single_linked_list *next;

    next = NULL;
    if (node && node->next) {
        next = node->next;
    } else if (!node->next) {
        pr_log_warn("Uninitialized or destroyed single linked list node.\n");
    }

    return next;
}

struct single_linked_list *
single_linked_list_node_previous(struct single_linked_list *node)
{
    register struct single_linked_list *previous;

    previous = NULL;
    if (node && node->next) {
        previous = node;
        do {
            previous = previous->next;
        } while (previous->next != node);
    } else if (!node->next) {
        pr_log_warn("Uninitialized or destroyed single linked list node.\n");
    }

    return previous;
}

void
single_linked_list_node_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    if (cur && node)
    {
        node->next = cur->next;
        cur->next = node;
    }

    return;
}

void
single_linked_list_node_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (cur && node)
    {
        previous = single_linked_list_node_previous(cur);
        if (previous) {
            single_linked_list_node_insert_after(previous, node);
        }
    }

    return;
}

void
single_linked_list_destroy(struct single_linked_list **head)
{
    register struct single_linked_list *node;
    register struct single_linked_list *next;

    if (head && *head) {
        /*
         * We do not use the way like douby linked list used, because
         * lazy remove need to get previous node. This will result in
         * go through all node in list, which has heavy performance
         * drop in unit test.
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
single_linked_list_length(struct single_linked_list *head)
{
    uint32 length;
    register struct single_linked_list *node;

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

struct single_linked_list *
single_linked_list_node_get_by_index(struct single_linked_list *head, uint32 index)
{
    register struct single_linked_list *node;

    node = NULL;
    if (head) {
        if (index <= single_linked_list_length(head)) {
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
single_linked_list_node_exchange(struct single_linked_list *fir,
    struct single_linked_list *sec)
{
    struct single_linked_list *prev_fir;
    struct single_linked_list *prev_sec;

    if (fir && sec) {
        if (single_linked_list_contains_p(fir, sec) && (fir != sec)) {
            prev_fir = single_linked_list_node_previous(fir);
            prev_sec = single_linked_list_node_previous(sec);

            if (prev_fir && prev_sec) {
                single_linked_list_node_lazy_remove(fir);
                single_linked_list_node_lazy_remove(sec);
                single_linked_list_node_insert_after(prev_fir, sec);
                single_linked_list_node_insert_after(prev_sec, fir);
            }
        }
    }

    return;
}

bool
single_linked_list_contains_p(struct single_linked_list *tar,
    struct single_linked_list *node)
{
    register struct single_linked_list *iter;
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
single_linked_list_serialize(struct single_linked_list *head)
{
    struct single_linked_list *node;
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

struct single_linked_list *
single_linked_list_node_remove(struct single_linked_list *node)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
         single_linked_list_node_lazy_remove(node);
        if (node->next != node) {
            next = node->next;
        }
        free_ds(node);
    }

    return next;
}

void
single_linked_list_node_lazy_remove(struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (node) {
        previous = single_linked_list_node_previous(node);
        if (previous) {
            previous->next = node->next;
        }
    }

    return;
}

void
single_linked_list_iterate(struct single_linked_list *head,
    void (*handler)(struct single_linked_list *))
{
    register struct single_linked_list *node;

    if (head && handler) {
        node = head;
        do {
            (*handler)(node);
            node = node->next;
        } while (node != head);
    }

    return;
}

struct single_linked_list *
single_linked_list_join(struct single_linked_list *m, struct single_linked_list *n)
{
    register struct single_linked_list *iter;
    register struct single_linked_list *new;

    if (m && n) {
        iter = n;
        do {
            new = single_linked_list_node_create(iter->val, iter->id);
            single_linked_list_node_insert_before(m, new);
            iter = iter->next;
        } while (iter != n);
    }

    return m ? m : n;
}
