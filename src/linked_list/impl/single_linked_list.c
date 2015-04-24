struct single_linked_list *
single_linked_list_create(void)
{
    return single_linked_list_node_create(NULL, 0u);
}

struct single_linked_list *
single_linked_list_node_create(void *val, uint32 sid)
{
    struct single_linked_list *head;

    head = malloc_ds(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        single_linked_list_node_initial(head, val, sid);
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
single_linked_list_node_initial(struct single_linked_list *head,
    void *val, uint32 sid)
{
    if (head) {
        single_linked_list_node_sid_set(head, sid);
        single_linked_list_node_val_set(head, val);
        single_linked_list_node_next_set(head, head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct single_linked_list *
single_linked_list_generate(uint32 *sid, uint32 size)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    register uint32 *iterator;

    head = NULL;
    if (sid && size > 0) {
        iterator = sid;
        node = single_linked_list_node_create(NULL, *iterator++);
        head = node;

        while (iterator < sid + size) {
            single_linked_list_node_append(node, *iterator++);
            node = single_linked_list_node_next(node);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return head;
}

void
single_linked_list_node_append(struct single_linked_list *node, uint32 sid)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
        if (NULL == single_linked_list_node_next(node)) {
            pr_log_warn("Destroyed data structure.\n");
        } else {
            next = single_linked_list_node_create(NULL, sid);
            single_linked_list_node_insert_after(node, next);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
single_linked_list_node_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    if (cur && node) {
        single_linked_list_node_next_set(node, cur->next);
        single_linked_list_node_next_set(cur, node);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
single_linked_list_node_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (cur && node) {
        previous = single_linked_list_node_previous(cur);
        if (previous) {
            single_linked_list_node_insert_after(previous, node);
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct single_linked_list *
single_linked_list_node_copy(struct single_linked_list *node)
{
    struct single_linked_list *copy;

    copy = NULL;
    if (node) {
        copy = single_linked_list_node_create(
            single_linked_list_node_val(node),
            single_linked_list_node_sid(node));

        single_linked_list_node_next_set(copy,
            single_linked_list_node_next(node));
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return copy;
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
        next = single_linked_list_node_next(*head);
        while (*head != (node = next)) {
            next = node->next;
            next = single_linked_list_node_next(node);
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
single_linked_list_length(struct single_linked_list *head)
{
    uint32 length;
    register struct single_linked_list *node;

    length = 0;
    if (head) {
        node = head;
        do {
            length++;
            node = single_linked_list_node_next(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return length;
}

struct single_linked_list *
single_linked_list_node_by_index(struct single_linked_list *head, uint32 index)
{
    register struct single_linked_list *node;
    uint32 len;

    node = NULL;
    if (head) {
        len = single_linked_list_length(head);
        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        node = head;
        while (index > 0) {
            node = single_linked_list_node_next(node);
            index--;
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

            single_linked_list_node_lazy_remove(fir);
            single_linked_list_node_lazy_remove(sec);
            single_linked_list_node_insert_after(prev_fir, sec);
            single_linked_list_node_insert_after(prev_sec, fir);
        } else {
            pr_log_warn("Exchange itself or exchange in different list.\n");
        }
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
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
            iter = single_linked_list_node_next(iter);
        } while (iter != tar);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
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
            single_linked_list_node_sid_set(node, index++);
            node = single_linked_list_node_next(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct single_linked_list *
single_linked_list_node_previous(struct single_linked_list *node)
{
    register struct single_linked_list *previous;

    previous = NULL;
    if (node && NULL != single_linked_list_node_next(node)) {
        previous = node;
        do {
            previous = single_linked_list_node_next(previous);
        } while (single_linked_list_node_next(previous) != node);
    } else if (node && NULL == single_linked_list_node_next(node)) {
        pr_log_warn("Destroyed data structure.\n");
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return previous;
}

struct single_linked_list *
single_linked_list_node_remove(struct single_linked_list *node)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
        single_linked_list_node_lazy_remove(node);
        if (single_linked_list_node_next(node) != node) {
            next = single_linked_list_node_next(node);
        }
        free_ds(node);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return next;
}

void
single_linked_list_node_lazy_remove(struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (node) {
        previous = single_linked_list_node_previous(node);
        single_linked_list_node_next_set(previous, node->next);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

void
single_linked_list_iterate(struct single_linked_list *head,
    void (*handler)(void *))
{
    register struct single_linked_list *node;

    if (head && handler) {
        node = head;
        do {
            (*handler)(single_linked_list_node_val(node));
            node = single_linked_list_node_next(node);
        } while (node != head);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return;
}

struct single_linked_list *
single_linked_list_join(struct single_linked_list *m,
    struct single_linked_list *n)
{
    register struct single_linked_list *iter;
    register struct single_linked_list *new;

    if (m && n) {
        iter = n;
        do {
            if (!single_linked_list_contains_p(m, iter)) {
                new = single_linked_list_node_create(
                    single_linked_list_node_val(iter),
                    single_linked_list_node_sid(iter));

                single_linked_list_node_insert_before(m, new);
            }
            iter = single_linked_list_node_next(iter);
        } while (iter != n);
    } else {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return m ? m : n;
}
