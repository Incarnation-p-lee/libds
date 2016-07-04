struct single_linked_list *
single_linked_list_next(struct single_linked_list *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
single_linked_list_next_set(struct single_linked_list *list,
    struct single_linked_list *next)
{
    if (single_linked_list_structure_legal_ip(list)
        && single_linked_list_structure_legal_ip(next)) {
        list->next = next;
    }
}

bool
single_linked_list_structure_legal_p(struct single_linked_list *list)
{
    return single_linked_list_structure_legal_ip(list);
}

static inline bool
single_linked_list_structure_legal_ip(struct single_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return false;
    } else if (PTR_INVALID == list->next) {
        return false;
    } else {
        return true;
    }
}

struct single_linked_list *
single_linked_list_create(void)
{
    return single_linked_list_create_i();
}

static inline void
single_linked_list_initial_i(struct single_linked_list *list)
{
    dp_assert(!complain_null_pointer_p(list));

    list->next = list;
}

static inline struct single_linked_list *
single_linked_list_create_i(void)
{
    struct single_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    single_linked_list_initial_i(list);

    return list;
}

void
single_linked_list_initial(struct single_linked_list *list)
{
    if (!complain_null_pointer_p(list)) {
        single_linked_list_initial_i(list);
    }
}

static inline void
single_linked_list_insert_after_i(struct single_linked_list *list,
    struct single_linked_list *node)
{
    dp_assert(single_linked_list_structure_legal_ip(list));
    dp_assert(single_linked_list_structure_legal_ip(node));
    dp_assert(!single_linked_list_contains_ip(list, node));

    node->next = list->next;
    list->next = node;
}

void
single_linked_list_insert_after(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (!single_linked_list_structure_legal_ip(list)
        || !single_linked_list_structure_legal_ip(node)) {
        return;
    } else if (single_linked_list_contains_ip(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        single_linked_list_insert_after_i(list, node);
    }
}

static inline void
single_linked_list_insert_before_i(struct single_linked_list *list,
    struct single_linked_list *node)
{
    struct single_linked_list *prev;

    dp_assert(single_linked_list_structure_legal_ip(list));
    dp_assert(single_linked_list_structure_legal_ip(node));
    dp_assert(!single_linked_list_contains_ip(list, node));

    prev = single_linked_list_previous_i(list);
    prev->next = node;
    node->next = list;
}

void
single_linked_list_insert_before(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (!single_linked_list_structure_legal_ip(list)
        || !single_linked_list_structure_legal_ip(node)) {
        return;
    } else if (single_linked_list_contains_ip(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        single_linked_list_insert_before_i(list, node);
    }
}

struct single_linked_list *
single_linked_list_node_copy(struct single_linked_list *node)
{
    struct single_linked_list *copy;

    if (!single_linked_list_structure_legal_ip(node)) {
        return PTR_INVALID;
    } else {
        copy = single_linked_list_create_i();
        copy->next = node->next;
        return copy;
    }
}

void
single_linked_list_destroy(struct single_linked_list **list)
{
    struct single_linked_list *node;
    struct single_linked_list *next;

    if (!complain_null_pointer_p(list)
        && single_linked_list_structure_legal_ip(*list)) {
        node = *list;
        do {
            next = node->next;
            memory_cache_free(node);
            node = next;
        } while (*list != node);

        *list = NULL;
    }
}

static inline uint32
single_linked_list_length_i(struct single_linked_list *list)
{
    uint32 len;
    struct single_linked_list *node;

    dp_assert(single_linked_list_structure_legal_ip(list));

    len = 0u;
    node = list;

    do {
        len++;
        node = node->next;
    } while (node != list);

    return len;
}

uint32
single_linked_list_length(struct single_linked_list *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return single_linked_list_length_i(list);
    }
}

struct single_linked_list *
single_linked_list_node_by_index(struct single_linked_list *list, uint32 index)
{
    uint32 len;
    struct single_linked_list *node;

    if (!single_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        len = single_linked_list_length_i(list);
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
single_linked_list_contains_ip(struct single_linked_list *list,
    struct single_linked_list *node)
{
    struct single_linked_list *single;

    dp_assert(single_linked_list_structure_legal_ip(list));
    dp_assert(single_linked_list_structure_legal_ip(node));

    single = list;

    do {
        if (single == node) {
            return true;
        }
        single = single ->next;
    } while (single != list);

    return false;
}

bool
single_linked_list_contains_p(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return false;
    } else if (!single_linked_list_structure_legal_ip(node)) {
        return false;
    } else {
        return single_linked_list_contains_ip(list, node);
    }
}

static inline struct single_linked_list *
single_linked_list_previous_i(struct single_linked_list *list)
{
    register struct single_linked_list *prev;

    dp_assert(single_linked_list_structure_legal_ip(list));
    dp_assert(single_linked_list_structure_legal_ip(list->next));

    prev = list;

    do {
        prev = prev->next;
    } while (prev->next != list);

    return prev;
}

struct single_linked_list *
single_linked_list_previous(struct single_linked_list *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return single_linked_list_previous_i(list);
    }
}

static inline struct single_linked_list *
single_linked_list_remove_i(struct single_linked_list **list)
{
    struct single_linked_list *prev;
    struct single_linked_list *removed;

    dp_assert(!complain_null_pointer_p(list));
    dp_assert(single_linked_list_structure_legal_ip(*list));

    removed = *list;

    if (*list == removed->next) {
        *list = NULL;
        return removed;
    } else {
        prev = single_linked_list_previous_i(removed);
        prev->next = removed->next;
        *list = removed->next;
        removed->next = removed;

        return removed;
    }
}

struct single_linked_list *
single_linked_list_remove(struct single_linked_list **list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else if (!single_linked_list_structure_legal_ip(*list)) {
        return PTR_INVALID;
    } else {
        return single_linked_list_remove_i(list);
    }
}

void
single_linked_list_iterate(struct single_linked_list *list,
    void (*handler)(void *))
{
    struct single_linked_list *node;

    if (!complain_null_pointer_p(handler)
        && single_linked_list_structure_legal_ip(list)) {
        node = list;

        do {
            (*handler)(node);
            node = node->next;
        } while (node != list);
    }
}

static inline struct single_linked_list *
single_linked_list_merge_i(struct single_linked_list *m,
    struct single_linked_list *n)
{
    struct single_linked_list *m_prev;
    struct single_linked_list *n_prev;

    dp_assert(single_linked_list_structure_legal_p(m));
    dp_assert(single_linked_list_structure_legal_p(n));
    dp_assert(!single_linked_list_contains_ip(m, n));

    m_prev = single_linked_list_previous_i(m);
    n_prev = single_linked_list_previous_i(n);

    m_prev->next = n;
    n_prev->next = m;

    return m;
}

struct single_linked_list *
single_linked_list_merge(struct single_linked_list *m,
    struct single_linked_list *n)
{
    if (!single_linked_list_structure_legal_ip(m)
        && !single_linked_list_structure_legal_ip(n)) {
        return PTR_INVALID;
    } else if (!single_linked_list_structure_legal_ip(m)) {
        return n;
    } else if (!single_linked_list_structure_legal_ip(n)) {
        return m;
    } else if (single_linked_list_contains_ip(m, n)) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        return single_linked_list_merge_i(m, n);
    }
}

