void *
doubly_linked_list_val(struct doubly_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->val;
    }
}

void
doubly_linked_list_val_set(struct doubly_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        list->val = val;
    }
}

struct doubly_linked_list *
doubly_linked_list_next(struct doubly_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
doubly_linked_list_next_set(struct doubly_linked_list *list,
    struct doubly_linked_list *next)
{
    if (!complain_null_pointer_p(list)) {
        list->next = next;
    }
}

struct doubly_linked_list *
doubly_linked_list_previous(struct doubly_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->previous;
    }
}

void
doubly_linked_list_previous_set(struct doubly_linked_list *list,
    struct doubly_linked_list *previous)
{
    if (!complain_null_pointer_p(list)) {
        list->previous = previous;
    }
}

struct doubly_linked_list *
doubly_linked_list_create(void)
{
    return doubly_linked_list_node_create_internal(NULL);
}

static inline void
doubly_linked_list_initial_internal(struct doubly_linked_list *list, void *val)
{
    dp_assert(!complain_null_pointer_p(list));

    list->next = list;
    list->previous = list;
    list->val = val;
}

void
doubly_linked_list_initial(struct doubly_linked_list *list)
{
    if (!complain_null_pointer_p(list)) {
        doubly_linked_list_initial_internal(list, NULL);
    }
}

static inline struct doubly_linked_list *
doubly_linked_list_node_create_internal(void *val)
{
    struct doubly_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    doubly_linked_list_initial_internal(list, val);

    return list;
}

struct doubly_linked_list *
doubly_linked_list_node_create(void *val)
{
    return doubly_linked_list_node_create_internal(val);
}

static inline void
doubly_linked_list_insert_after_internal(struct doubly_linked_list *list,
    void *val)
{
    struct doubly_linked_list *node;

    dp_assert(!complain_null_pointer_p(list));

    node = doubly_linked_list_node_create_internal(val);

    list->next->previous = node;
    node->next = list->next;
    list->next = node;
    node->previous = list;
}

static inline void
doubly_linked_list_insert_ptr_after_internal(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    dp_assert(!complain_null_pointer_p(list));
    dp_assert(!complain_null_pointer_p(list));
    dp_assert(!doubly_linked_list_contains_p_internal(list, node));

    list->next->previous = node;
    node->next = list->next;
    list->next = node;
    node->previous = list;
}

void
doubly_linked_list_insert_ptr_after(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (complain_null_pointer_p(list) || complain_null_pointer_p(node)) {
        return;
    } else if (doubly_linked_list_contains_p_internal(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_insert_ptr_after_internal(list, node);
    }
}

static inline void
doubly_linked_list_insert_ptr_before_internal(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    struct doubly_linked_list *prev;

    dp_assert(!complain_null_pointer_p(list));
    dp_assert(!complain_null_pointer_p(node));
    dp_assert(!doubly_linked_list_contains_p_internal(list, node));

    prev = list->previous;
    dp_assert(NULL != prev);

    doubly_linked_list_insert_ptr_after_internal(prev, node);
}

void
doubly_linked_list_insert_ptr_before(struct doubly_linked_list *list,
    struct doubly_linked_list *node)
{
    if (complain_null_pointer_p(list) || complain_null_pointer_p(node)) {
        return;
    } else if (doubly_linked_list_contains_p_internal(list, node)) {
        pr_log_warn("Attempt to insert node contains already.\n");
    } else {
        doubly_linked_list_insert_ptr_before_internal(list, node);
    }
}

void
doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        doubly_linked_list_insert_after_internal(list, val);
    }
}

static inline void
doubly_linked_list_insert_before_internal(struct doubly_linked_list *list,
    void *val)
{
    struct doubly_linked_list *prev;

    dp_assert(!complain_null_pointer_p(list));

    prev = list->previous;
    dp_assert(NULL != prev);

    doubly_linked_list_insert_after_internal(prev, val);
}

void
doubly_linked_list_insert_before(struct doubly_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        doubly_linked_list_insert_before_internal(list, val);
    }
}

struct doubly_linked_list *
doubly_linked_list_node_copy(struct doubly_linked_list *node)
{
    struct doubly_linked_list *copy;

    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        copy = doubly_linked_list_node_create_internal(node->val);
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

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(*list)) {
        node = *list;
        /*
         * Do not call doubly_linked_list_remove_node for
         * the consider of performance drop.
         */
        do {
            next = node->next;
            memory_cache_dp_free(node);
            node = next;
        } while(*list != node);

        *list = NULL;
    }
}

static inline uint32
doubly_linked_list_length_internal(struct doubly_linked_list *list)
{
    uint32 len;
    register struct doubly_linked_list *node;

    dp_assert(NULL != list);

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
    if (complain_null_pointer_p(list)) {
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

    if (complain_null_pointer_p(list)) {
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

    dp_assert(NULL != list);
    dp_assert(NULL != node);

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
    if (complain_null_pointer_p(list) || complain_null_pointer_p(node)) {
        return false;
    } else {
        return doubly_linked_list_contains_p_internal(list, node);
    }
}

static inline struct doubly_linked_list *
doubly_linked_list_remove_internal(struct doubly_linked_list **node)
{
    struct doubly_linked_list *removed;

    dp_assert(NULL != node);
    dp_assert(NULL != *node);

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
doubly_linked_list_remove(struct doubly_linked_list **node)
{
    if (complain_null_pointer_p(node) || complain_null_pointer_p(*node)) {
        return NULL;
    } else {
        return doubly_linked_list_remove_internal(node);
    }
}

void
doubly_linked_list_remove_and_destroy(struct doubly_linked_list **node)
{
    struct doubly_linked_list *removed;

    if (!complain_null_pointer_p(node) && !complain_null_pointer_p(*node)) {
        removed = doubly_linked_list_remove_internal(node);
        memory_cache_dp_free(removed);
    }
}

void
doubly_linked_list_iterate(struct doubly_linked_list *list, void (*handler)(void *))
{
    register struct doubly_linked_list *node;

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(handler)) {
        node = list;

        do {
            (*handler)(node->val);
            node = node->next;
        } while (node != list);
    }
}

struct doubly_linked_list *
doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n)
{
    register struct doubly_linked_list *iter;

    if (complain_null_pointer_p(m) || complain_null_pointer_p(n)) {
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        do {
            doubly_linked_list_insert_after_internal(m, iter->val);
            iter = iter->next;
        } while (iter != n);

        return m;
    }
}

