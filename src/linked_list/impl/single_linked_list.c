struct single_linked_list *
single_linked_list_next(struct single_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
single_linked_list_next_set(struct single_linked_list *list,
    struct single_linked_list *next)
{
    if (!complain_null_pointer_p(list)) {
        list->next = next;
    }
}

static inline bool
single_linked_list_structure_legal_p(struct single_linked_list *list)
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
    return single_linked_list_create_i(NULL);
}

static inline void
single_linked_list_initial_i(struct single_linked_list *list);
{
    dp_assert(single_linked_list_structure_legal_p(list));

    list->next = list;
}

static inline struct single_linked_list *
single_linked_list_create_i(void *val)
{
    struct single_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    single_linked_list_initial_i(list, val);

    return list;
}

void
single_linked_list_initial(struct single_linked_list *list)
{
    if (single_linked_list_structure_legal_p(list)) {
        single_linked_list_initial_i(list, NULL);
    }
}

static inline void
single_linked_list_insert_after_i(struct single_linked_list *list,
    struct single_linked_list *node)
{
    dp_assert(single_linked_list_structure_legal_p(list));
    dp_assert(single_linked_list_structure_legal_p(node));
    dp_assert(!single_linked_list_contains_i_p(list, node));

    node->next = list->next;
    list->next = node;
}

void
single_linked_list_insert_after(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (!single_linked_list_structure_legal_p(list)
        || !single_linked_list_structure_legal_p(node)) {
        return;
    } else if (single_linked_list_contains_i_p(list, node)) {
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

    dp_assert(single_linked_list_structure_legal_p(list));
    dp_assert(single_linked_list_structure_legal_p(node));
    dp_assert(!single_linked_list_contains_i_p(list, node));

    prev = single_linked_list_previous_i(list);
    prev->next = node;
    node->next = list;
}

void
single_linked_list_insert_ptr_before(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (!single_linked_list_structure_legal_p(list)
        || !single_linked_list_structure_legal_p(node)) {
        return;
    } else if (single_linked_list_contains_p_i(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        single_linked_list_insert_before_i(list, node);
    }
}


struct single_linked_list *
single_linked_list_node_copy(struct single_linked_list *node)
{
    struct single_linked_list *copy;

    if (!single_linked_list_structure_legal_p(node)) {
        return NULL;
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
        && single_linked_list_structure_legal_p(*list)) {
        node = *list;
        /*
         * We do not use the way like douby linked list used, because
         * lazy remove need to get previous node. This will result in
         * go through all node in list, which has heavy performance
         * drop in performance test.
         */
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

    dp_assert(single_linked_list_structure_legal_p(list));

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
    if (!single_linked_list_structure_legal_p(list)) {
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

    if (!single_linked_list_structure_legal_p(list)) {
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
single_linked_list_contains_p_i(struct single_linked_list *list,
    struct single_linked_list *node)
{
    struct single_linked_list *single;

    dp_assert(single_linked_list_structure_legal_p(list));
    dp_assert(single_linked_list_structure_legal_p(node));

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
    if (!single_linked_list_structure_legal_p(list)) {
        return false;
    } else if (!single_linked_list_structure_legal_p(node)) {
        return false;
    } else {
        return single_linked_list_contains_p_i(list, node);
    }
}

static inline struct single_linked_list *
single_linked_list_previous_i(struct single_linked_list *list)
{
    register struct single_linked_list *prev;

    dp_assert(single_linked_list_structure_legal_p(list));
    dp_assert(single_linked_list_structure_legal_p(list->next));

    prev = list;

    do {
        prev = prev->next;
    } while (prev->next != list);

    return prev;
}

struct single_linked_list *
single_linked_list_previous(struct single_linked_list *list)
{
    if (!single_linked_list_structure_legal_p(list)) {
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
    dp_assert(single_linked_list_structure_legal_p(*list));

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
    } else if (!single_linked_list_structure_legal_p(*list)) {
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
        && single_linked_list_structure_legal_p(list)) {
        node = list;

        do {
            (*handler)(node->val);
            node = node->next;
        } while (node != list);
    }
}

struct single_linked_list *
single_linked_list_merge(struct single_linked_list *m,
    struct single_linked_list *n)
{
    struct single_linked_list *list;

    if (!single_linked_list_structure_legal_p(m)
        && !single_linked_list_structure_legal_p(n)) {
        return PTR_INVALID;
    } else if (!single_linked_list_structure_legal_p(m)) {
        return n;
    } else if (!single_linked_list_structure_legal_p(n)) {
        return m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        list = n;

        do {
            single_linked_list_insert_after_i(m, list->val);
            list = list->next;
        } while (list != n);

        return m;
    }
}

