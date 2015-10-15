struct doubly_linked_list *
doubly_linked_list_create(void)
{
    return doubly_linked_list_node_create(NULL, 0u);
}

struct doubly_linked_list *
doubly_linked_list_node_create(void *val, uint32 sid)
{
    struct doubly_linked_list *list;

    list = malloc_ds(sizeof(*list));

    if (!list) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        doubly_linked_list_node_initial(list, val, sid);
        return list;
    }
}

void
doubly_linked_list_node_initial(struct doubly_linked_list *list,
    void *val, uint32 sid)
{
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        list->sid = sid;
        list->next = list;
        list->previous = list;
        list->val = val;
    }
}

void
doubly_linked_list_initial(struct doubly_linked_list *list)
{
    doubly_linked_list_node_initial(list, NULL, 0u);
}

void
doubly_linked_list_node_append(struct doubly_linked_list *node, void *val)
{
    struct doubly_linked_list *next;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (NULL == node->next || NULL == node->previous) {
        pr_log_warn("Destroyed data structure.\n");
    } else {
        next = doubly_linked_list_node_create(val, 0u);
        doubly_linked_list_node_insert_after_internal(node, next);
    }
}

static inline void
doubly_linked_list_node_insert_after_internal(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    assert(NULL != cur);
    assert(NULL != node);
    assert(!doubly_linked_list_contains_p_internal(cur, node));

    cur->next->previous = node;
    node->next = cur->next;
    cur->next = node;
    node->previous = cur;
}

void
doubly_linked_list_node_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (doubly_linked_list_contains_p_internal(cur, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_node_insert_after_internal(cur, node);
    }
}

static inline void
doubly_linked_list_node_insert_before_internal(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *prev;

    assert(NULL != cur);
    assert(NULL != node);
    assert(!doubly_linked_list_contains_p_internal(cur, node));

    prev = doubly_linked_list_node_previous(cur);
    assert(NULL != prev);

    doubly_linked_list_node_insert_after_internal(prev, node);
}

void
doubly_linked_list_node_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (doubly_linked_list_contains_p_internal(cur, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_node_insert_before_internal(cur, node);
    }
}

void
doubly_linked_list_node_insert_before_risky(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        doubly_linked_list_node_insert_before_internal(cur, node);
    }
}

void
doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur,
    struct doubly_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        doubly_linked_list_node_insert_after_internal(cur, node);
    }
}

struct doubly_linked_list *
doubly_linked_list_node_copy(struct doubly_linked_list *node)
{
    struct doubly_linked_list *copy;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        copy = doubly_linked_list_node_create(node->val, node->sid);
        copy->next = node->next;
        copy->previous = node->previous;

        return copy;
    }
}

void
doubly_linked_list_destroy(struct doubly_linked_list **list)
{
    register struct doubly_linked_list *node;
    register struct doubly_linked_list **next;

    if (!list || !*list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node = *list;
        /*
         * Do not call doubly_linked_list_remove_node for
         * the consider of performance drop.
         */
        do {
            next = &node->next;
            free_ds(node);
            node = *next;
        } while(*list != node);

        *list = NULL;
    }
}

static inline uint32
doubly_linked_list_length_internal(struct doubly_linked_list *list)
{
    uint32 len;
    register struct doubly_linked_list *node;

    assert(NULL != list);

    len = 0;
    node = list;

    do {
        len++;
        node = node->next;
    } while (node != list);

    return len;
}

uint32
doubly_linked_list_length(struct doubly_linked_list *list)
{
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0u;
    } else {
        return doubly_linked_list_length_internal(list);
    }
}

struct doubly_linked_list *
doubly_linked_list_node_by_index(struct doubly_linked_list *list,
    uint32 index)
{
    register struct doubly_linked_list *node;
    uint32 len;

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        len = doubly_linked_list_length_internal(list);

        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        node = list;
        while (index > 0) {
            node = node->next;
            index--;
        }

        return node;
    }
}

static inline bool
doubly_linked_list_contains_p_internal(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    register struct doubly_linked_list *iter;

    assert(NULL != list);
    assert(NULL != node);

    iter = list;

    do {
        if (iter == node) {
            return true;
        }
        iter = iter->next;
    } while (iter != list);

    return false;
}

bool
doubly_linked_list_contains_p(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (!list || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return doubly_linked_list_contains_p_internal(list, node);
    }
}

void
doubly_linked_list_serialize(struct doubly_linked_list *list)
{
    struct doubly_linked_list *node;
    uint32 index;

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        index = 0;
        node = list;

        do {
            node->sid = index++;
            node = node->next;
        } while (node != list);
    }
}

static inline struct doubly_linked_list *
doubly_linked_list_node_remove_internal(struct doubly_linked_list **node)
{
    struct doubly_linked_list *removed;

    assert(NULL != node);
    assert(NULL != *node);

    removed = *node;

    if (*node == removed->next) {
        *node = NULL;
        return removed;
    } else {
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        *node = removed->next;
        removed->next = removed;
        removed->previous = removed;

        return removed;
    }
}

struct doubly_linked_list *
doubly_linked_list_node_remove(struct doubly_linked_list **node)
{
    if (!node || !*node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return doubly_linked_list_node_remove_internal(node);
    }
}

void
doubly_linked_list_node_remove_and_destroy(struct doubly_linked_list **node)
{
    struct doubly_linked_list *removed;

    if (!node || !*node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = doubly_linked_list_node_remove_internal(node);
        free_ds(removed);
    }
}


void
doubly_linked_list_iterate(struct doubly_linked_list *list, void (*handler)(void *))
{
    register struct doubly_linked_list *node;

    if (!list || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node = list;

        do {
            (*handler)(doubly_linked_list_node_val(node));
            node = node->next;
        } while (node != list);
    }
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
            if (!doubly_linked_list_contains_p_internal(m, iter)) {
                new = doubly_linked_list_node_create(iter->val, iter->sid);
                doubly_linked_list_node_insert_before_internal(m, new);
            }

            iter = iter->next;
        } while (iter != n);

        return m;
    }
}

