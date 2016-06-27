struct doubly_linked_list *
doubly_linked_list_next(struct doubly_linked_list *list)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
doubly_linked_list_next_set(struct doubly_linked_list *list,
    struct doubly_linked_list *next)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        list->next = next;
    }
}

bool
doubly_linked_list_structure_legal_p(struct doubly_linked_list *list)
{
    return doubly_linked_list_structure_legal_ip(list);
}

static inline bool
doubly_linked_list_structure_legal_ip(struct doubly_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return false;
    } else if (PTR_INVALID == list->next) {
        return false;
    } else {
        return true;
    }
}

struct doubly_linked_list *
doubly_linked_list_previous(struct doubly_linked_list *list)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return PTR_INVALID;
    } else {
        return list->previous;
    }
}

void
doubly_linked_list_previous_set(struct doubly_linked_list *list,
    struct doubly_linked_list *previous)
{
    if (doubly_linked_list_structure_legal_ip(list)
        && doubly_linked_list_structure_legal_ip(previous)) {
        list->previous = previous;
    }
}

struct doubly_linked_list *
doubly_linked_list_create(void)
{
    return doubly_linked_list_create_i(NULL);
}

static inline void
doubly_linked_list_initial_i(struct doubly_linked_list *list)
{
    dp_assert(doubly_linked_list_structure_legal_ip(list));

    list->next = list;
    list->previous = list;
}

void
doubly_linked_list_initial(struct doubly_linked_list *list)
{
    if (doubly_linked_list_structure_legal_ip(list)) {
        doubly_linked_list_initial_i(list);
    }
}

static inline struct doubly_linked_list *
doubly_linked_list_create_i()
{
    struct doubly_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    doubly_linked_list_initial_i(list);

    return list;
}

static inline void
doubly_linked_list_insert_after_i(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    dp_assert(doubly_linked_list_structure_legal_ip(list));
    dp_assert(doubly_linked_list_structure_legal_ip(node));
    dp_assert(!doubly_linked_list_contains_ip(list, node));

    list->next->previous = node;
    node->next = list->next;
    list->next = node;
    node->previous = list;
}

void
doubly_linked_list_insert_after(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)
        || !doubly_linked_list_structure_legal_ip(node)) {
        return;
    } else if (doubly_linked_list_contains_ip(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_insert_after_i(list, node);
    }
}

static inline void
doubly_linked_list_insert_before_i(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    dp_assert(doubly_linked_list_structure_legal_ip(list));
    dp_assert(doubly_linked_list_structure_legal_ip(node));
    dp_assert(!doubly_linked_list_contains_ip(list, node));

    doubly_linked_list_insert_after_i(list->previous, node);
}

void
doubly_linked_list_insert_before(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)
        || !doubly_linked_list_structure_legal_ip(node)) {
        return;
    } else if (doubly_linked_list_contains_ip(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_insert_before_i(list, node);
    }
}

struct doubly_linked_list *
doubly_linked_list_node_copy(struct doubly_linked_list *node)
{
    struct doubly_linked_list *copy;

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
doubly_linked_list_destroy(struct doubly_linked_list **list)
{
    struct doubly_linked_list *node;
    struct doubly_linked_list *next;

    if (!complain_null_pointer_p(list)
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
doubly_linked_list_length_i(struct doubly_linked_list *list)
{
    uint32 len;
    register struct doubly_linked_list *node;

    dp_assert(doubly_linked_list_structure_legal_ip(list));

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
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return doubly_linked_list_length_i(list);
    }
}

struct doubly_linked_list *
doubly_linked_list_node_by_index(struct doubly_linked_list *list,
    uint32 index)
{
    uint32 len;
    struct doubly_linked_list *node;

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
doubly_linked_list_contains_ip(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *doubly;

    dp_assert(doubly_linked_list_structure_legal_ip(list));
    dp_assert(doubly_linked_list_structure_legal_ip(node));

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
doubly_linked_list_contains_p(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (!doubly_linked_list_structure_legal_ip(list)) {
        return false;
    } else if (!doubly_linked_list_structure_legal_ip(node)) {
        return false;
    } else {
        return doubly_linked_list_contains_ip(list, node);
    }
}

static inline struct doubly_linked_list *
doubly_linked_list_remove_i(struct doubly_linked_list **list)
{
    struct doubly_linked_list *removed;

    dp_assert(!complain_null_pointer_p(list));
    dp_assert(doubly_linked_list_structure_legal_ip(*list));

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

struct doubly_linked_list *
doubly_linked_list_remove(struct doubly_linked_list **list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else if (!doubly_linked_list_structure_legal_ip(*list)) {
        return PTR_INVALID;
    } else {
        return doubly_linked_list_remove_i(list);
    }
}

void
doubly_linked_list_iterate(struct doubly_linked_list *list, void (*handler)(void *))
{
    struct doubly_linked_list *node;

    if (!complain_null_pointer_p(handler)
        && doubly_linked_list_structure_legal_ip(list)) {
        node = list;

        do {
            (*handler)(node);
            node = node->next;
        } while (node != list);
    }
}

struct doubly_linked_list *
doubly_linked_list_merge(struct doubly_linked_list *m,
    struct doubly_linked_list *n)
{
    struct doubly_linked_list *list;

    // Fix-Me
    if (!doubly_linked_list_structure_legal_ip(m)
        && !doubly_linked_list_structure_legal_ip(n)) {
        return PTR_INVALID;
    } else if (!doubly_linked_list_structure_legal_ip(m)) {
        return n;
    } else if (!doubly_linked_list_structure_legal_ip(n)) {
        return m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        list = n;

        do {
            doubly_linked_list_insert_after_i(m, list->val);
            list = list->next;
        } while (list != n);

        return m;
    }
}

