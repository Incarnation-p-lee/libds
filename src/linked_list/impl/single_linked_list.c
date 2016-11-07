s_single_linked_list_t *
single_linked_list_next(s_single_linked_list_t *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
single_linked_list_next_set(s_single_linked_list_t *list,
    s_single_linked_list_t *next)
{
    if (single_linked_list_structure_legal_ip(list)
        && single_linked_list_structure_legal_ip(next)) {
        list->next = next;
    }
}

bool
single_linked_list_structure_legal_p(s_single_linked_list_t *list)
{
    return single_linked_list_structure_legal_ip(list);
}

static inline bool
single_linked_list_structure_legal_ip(s_single_linked_list_t *list)
{
    if (NULL_PTR_P(list)) {
        return false;
    } else if (PTR_INVALID == list->next) {
        return false;
    } else {
        return true;
    }
}

s_single_linked_list_t *
single_linked_list_create(void)
{
    return single_linked_list_create_i();
}

static inline void
single_linked_list_initial_i(s_single_linked_list_t *list)
{
    assert_exit(!NULL_PTR_P(list));

    list->next = list;
}

static inline s_single_linked_list_t *
single_linked_list_create_i(void)
{
    s_single_linked_list_t *list;

    list = memory_cache_allocate(sizeof(*list));
    single_linked_list_initial_i(list);

    return list;
}

void
single_linked_list_initial(s_single_linked_list_t *list)
{
    if (!NULL_PTR_P(list)) {
        single_linked_list_initial_i(list);
    }
}

static inline void
single_linked_list_insert_after_i(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
{
    assert_exit(single_linked_list_structure_legal_ip(list));
    assert_exit(single_linked_list_structure_legal_ip(node));
    assert_exit(!single_linked_list_contains_ip(list, node));

    node->next = list->next;
    list->next = node;
}

void
single_linked_list_insert_after(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
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
single_linked_list_insert_before_i(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
{
    s_single_linked_list_t *prev;

    assert_exit(single_linked_list_structure_legal_ip(list));
    assert_exit(single_linked_list_structure_legal_ip(node));
    assert_exit(!single_linked_list_contains_ip(list, node));

    prev = single_linked_list_previous_i(list);
    prev->next = node;
    node->next = list;
}

void
single_linked_list_insert_before(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
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

s_single_linked_list_t *
single_linked_list_node_copy(s_single_linked_list_t *node)
{
    s_single_linked_list_t *copy;

    if (!single_linked_list_structure_legal_ip(node)) {
        return PTR_INVALID;
    } else {
        copy = single_linked_list_create_i();
        copy->next = node->next;
        return copy;
    }
}

void
single_linked_list_destroy(s_single_linked_list_t **list)
{
    s_single_linked_list_t *node;
    s_single_linked_list_t *next;

    if (!NULL_PTR_P(list)
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
single_linked_list_length_i(s_single_linked_list_t *list)
{
    uint32 len;
    s_single_linked_list_t *node;

    assert_exit(single_linked_list_structure_legal_ip(list));

    len = 0u;
    node = list;

    do {
        len++;
        node = node->next;
    } while (node != list);

    return len;
}

uint32
single_linked_list_length(s_single_linked_list_t *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return single_linked_list_length_i(list);
    }
}

s_single_linked_list_t *
single_linked_list_node_by_index(s_single_linked_list_t *list, uint32 index)
{
    uint32 len;
    s_single_linked_list_t *node;

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
single_linked_list_contains_ip(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
{
    s_single_linked_list_t *single;

    assert_exit(single_linked_list_structure_legal_ip(list));
    assert_exit(single_linked_list_structure_legal_ip(node));

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
single_linked_list_contains_p(s_single_linked_list_t *list,
    s_single_linked_list_t *node)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return false;
    } else if (!single_linked_list_structure_legal_ip(node)) {
        return false;
    } else {
        return single_linked_list_contains_ip(list, node);
    }
}

static inline s_single_linked_list_t *
single_linked_list_previous_i(s_single_linked_list_t *list)
{
    register s_single_linked_list_t *prev;

    assert_exit(single_linked_list_structure_legal_ip(list));
    assert_exit(single_linked_list_structure_legal_ip(list->next));

    prev = list;

    do {
        prev = prev->next;
    } while (prev->next != list);

    return prev;
}

s_single_linked_list_t *
single_linked_list_previous(s_single_linked_list_t *list)
{
    if (!single_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return single_linked_list_previous_i(list);
    }
}

static inline s_single_linked_list_t *
single_linked_list_remove_i(s_single_linked_list_t **list)
{
    s_single_linked_list_t *prev;
    s_single_linked_list_t *removed;

    assert_exit(!NULL_PTR_P(list));
    assert_exit(single_linked_list_structure_legal_ip(*list));

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

s_single_linked_list_t *
single_linked_list_remove(s_single_linked_list_t **list)
{
    if (NULL_PTR_P(list)) {
        return PTR_INVALID;
    } else if (!single_linked_list_structure_legal_ip(*list)) {
        return PTR_INVALID;
    } else {
        return single_linked_list_remove_i(list);
    }
}

void
single_linked_list_iterate(s_single_linked_list_t *list,
    void (*handler)(void *))
{
    s_single_linked_list_t *node;

    if (!NULL_PTR_P(handler)
        && single_linked_list_structure_legal_ip(list)) {
        node = list;

        do {
            (*handler)(node);
            node = node->next;
        } while (node != list);
    }
}

static inline s_single_linked_list_t *
single_linked_list_merge_i(s_single_linked_list_t *m,
    s_single_linked_list_t *n)
{
    s_single_linked_list_t *m_prev;
    s_single_linked_list_t *n_prev;

    assert_exit(single_linked_list_structure_legal_p(m));
    assert_exit(single_linked_list_structure_legal_p(n));
    assert_exit(!single_linked_list_contains_ip(m, n));

    m_prev = single_linked_list_previous_i(m);
    n_prev = single_linked_list_previous_i(n);

    m_prev->next = n;
    n_prev->next = m;

    return m;
}

s_single_linked_list_t *
single_linked_list_merge(s_single_linked_list_t *m,
    s_single_linked_list_t *n)
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

