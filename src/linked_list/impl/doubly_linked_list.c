s_doubly_linked_list_t *
doubly_linked_list_next(s_doubly_linked_list_t *list)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
doubly_linked_list_next_set(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *next)
{
    if (doubly_linked_list_structure_legal_ip(list)
        && doubly_linked_list_structure_legal_ip(next)) {
        list->next = next;
    }
}

bool
doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list)
{
    return doubly_linked_list_structure_legal_ip(list);
}

static inline bool
doubly_linked_list_structure_legal_ip(s_doubly_linked_list_t *list)
{
    if (NULL_PTR_P(list)) {
        return false;
    } else if (PTR_INVALID == list->next) {
        return false;
    } else {
        return true;
    }
}

s_doubly_linked_list_t *
doubly_linked_list_previous(s_doubly_linked_list_t *list)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->previous;
    }
}

void
doubly_linked_list_previous_set(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *previous)
{
    if (doubly_linked_list_structure_legal_ip(list)
        && doubly_linked_list_structure_legal_ip(previous)) {
        list->previous = previous;
    }
}

s_doubly_linked_list_t *
doubly_linked_list_create(void)
{
    return doubly_linked_list_create_i(NULL);
}

static inline void
doubly_linked_list_initial_i(s_doubly_linked_list_t *list)
{
    assert_exit(doubly_linked_list_structure_legal_ip(list));

    list->next = list;
    list->previous = list;
}

void
doubly_linked_list_initial(s_doubly_linked_list_t *list)
{
    if (doubly_linked_list_structure_legal_ip(list)) {
        doubly_linked_list_initial_i(list);
    }
}

static inline s_doubly_linked_list_t *
doubly_linked_list_create_i()
{
    s_doubly_linked_list_t *list;

    list = memory_cache_allocate(sizeof(*list));
    doubly_linked_list_initial_i(list);

    return list;
}

static inline void
doubly_linked_list_insert_after_i(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    assert_exit(doubly_linked_list_structure_legal_ip(list));
    assert_exit(doubly_linked_list_structure_legal_ip(node));
    assert_exit(!doubly_linked_list_contains_ip(list, node));

    list->next->previous = node;
    node->next = list->next;
    list->next = node;
    node->previous = list;
}

void
doubly_linked_list_insert_after(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)
        || !doubly_linked_list_structure_legal_ip(node)) {
        return;
    } else {
        assert_exit(!doubly_linked_list_contains_ip(list, node));
        doubly_linked_list_insert_after_i(list, node);
    }
}

static inline void
doubly_linked_list_insert_before_i(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    assert_exit(doubly_linked_list_structure_legal_ip(list));
    assert_exit(doubly_linked_list_structure_legal_ip(node));
    assert_exit(!doubly_linked_list_contains_ip(list, node));

    doubly_linked_list_insert_after_i(list->previous, node);
}

void
doubly_linked_list_insert_before(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)
        || !doubly_linked_list_structure_legal_ip(node)) {
        return;
    } else {
        assert_exit(!doubly_linked_list_contains_ip(list, node));
        doubly_linked_list_insert_before_i(list, node);
    }
}

s_doubly_linked_list_t *
doubly_linked_list_node_copy(s_doubly_linked_list_t *node)
{
    s_doubly_linked_list_t *copy;

    if (!doubly_linked_list_structure_legal_ip(node)) {
        return PTR_INVALID;
    } else {
        copy = doubly_linked_list_create_i();
        copy->next = node->next;
        copy->previous = node->previous;
        return copy;
    }
}

void
doubly_linked_list_destroy(s_doubly_linked_list_t **list)
{
    s_doubly_linked_list_t *node;
    s_doubly_linked_list_t *next;

    if (!NULL_PTR_P(list)
        && doubly_linked_list_structure_legal_ip(*list)) {
        node = *list;
        do {
            next = node->next;
            memory_cache_free(node);
            node = next;
        } while(*list != node);

        *list = NULL;
    }
}

static inline uint32
doubly_linked_list_length_i(s_doubly_linked_list_t *list)
{
    uint32 len;
    register s_doubly_linked_list_t *node;

    assert_exit(doubly_linked_list_structure_legal_ip(list));

    len = 0;
    node = list;

    do {
        len++;
        node = node->next;
    } while (node != list);

    return len;
}

uint32
doubly_linked_list_length(s_doubly_linked_list_t *list)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return doubly_linked_list_length_i(list);
    }
}

s_doubly_linked_list_t *
doubly_linked_list_node_by_index(s_doubly_linked_list_t *list,
    uint32 index)
{
    uint32 len;
    s_doubly_linked_list_t *node;

    if (!doubly_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        len = doubly_linked_list_length_i(list);

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
doubly_linked_list_contains_ip(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    s_doubly_linked_list_t *doubly;

    assert_exit(doubly_linked_list_structure_legal_ip(list));
    assert_exit(doubly_linked_list_structure_legal_ip(node));

    doubly = list;

    do {
        if (doubly == node) {
            return true;
        }

        doubly = doubly->next;
    } while (doubly != list);

    return false;
}

bool
doubly_linked_list_contains_p(s_doubly_linked_list_t *list,
    s_doubly_linked_list_t *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return false;
    } else if (!doubly_linked_list_structure_legal_ip(node)) {
        return false;
    } else {
        return doubly_linked_list_contains_ip(list, node);
    }
}

static inline s_doubly_linked_list_t *
doubly_linked_list_remove_i(s_doubly_linked_list_t **list)
{
    s_doubly_linked_list_t *removed;

    assert_exit(!NULL_PTR_P(list));
    assert_exit(doubly_linked_list_structure_legal_ip(*list));

    removed = *list;

    if (*list == removed->next) {
        *list = NULL;
        return removed;
    } else {
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;

        *list = removed->next;

        removed->next = removed;
        removed->previous = removed;

        return removed;
    }
}

s_doubly_linked_list_t *
doubly_linked_list_remove(s_doubly_linked_list_t **list)
{
    if (NULL_PTR_P(list)) {
        return PTR_INVALID;
    } else if (!doubly_linked_list_structure_legal_ip(*list)) {
        return PTR_INVALID;
    } else {
        return doubly_linked_list_remove_i(list);
    }
}

void
doubly_linked_list_iterate(s_doubly_linked_list_t *list, void (*handler)(void *))
{
    s_doubly_linked_list_t *node;

    if (!NULL_PTR_P(handler)
        && doubly_linked_list_structure_legal_ip(list)) {
        node = list;

        do {
            (*handler)(node);
            node = node->next;
        } while (node != list);
    }
}

static inline s_doubly_linked_list_t *
doubly_linked_list_merge_i(s_doubly_linked_list_t *m,
    s_doubly_linked_list_t *n)
{
    s_doubly_linked_list_t *n_prev;

    assert_exit(doubly_linked_list_structure_legal_p(m));
    assert_exit(doubly_linked_list_structure_legal_p(n));
    assert_exit(!doubly_linked_list_contains_ip(m, n));

    m->previous->next = n;
    n->previous->next = m;

    n_prev = n->previous;
    n->previous = m->previous;
    m->previous = n_prev;

    return m;
}

s_doubly_linked_list_t *
doubly_linked_list_merge(s_doubly_linked_list_t *m,
    s_doubly_linked_list_t *n)
{
    if (!doubly_linked_list_structure_legal_ip(m)
        && !doubly_linked_list_structure_legal_ip(n)) {
        return PTR_INVALID;
    } else if (!doubly_linked_list_structure_legal_ip(m)) {
        return n;
    } else if (!doubly_linked_list_structure_legal_ip(n)) {
        return m;
    } else if (doubly_linked_list_contains_ip(m, n)) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        return doubly_linked_list_merge_i(m, n);
    }
}

