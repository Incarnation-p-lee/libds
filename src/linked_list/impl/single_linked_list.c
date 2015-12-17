struct single_linked_list *
single_linked_list_create(void)
{
    return single_linked_list_node_create(NULL, 0u);
}

struct single_linked_list *
single_linked_list_node_create(void *val, uint32 sid)
{
    struct single_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    if (!complain_no_memory_p(list)) {
        single_linked_list_node_initial(list, val, sid);
    }

    return list;
}

void
single_linked_list_initial(struct single_linked_list *list)
{
    single_linked_list_node_initial(list, NULL, 0u);
}

void
single_linked_list_node_initial(struct single_linked_list *list,
    void *val, uint32 sid)
{
    if (!complain_null_pointer_p(list)) {
        list->sid = sid;
        list->val = val;
        list->next = list;
    }
}

static inline void
single_linked_list_insert_after_internal(struct single_linked_list *list,
    void *val, uint32 sid)
{
    struct single_linked_list *node;

    assert(!complain_null_pointer_p(list));

    node = single_linked_list_node_create(val, sid);
    node->next = list->next;
    list->next = node;
}

void
single_linked_list_insert_after(struct single_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        single_linked_list_insert_after_internal(list, val, 0u);
    }
}

void
single_linked_list_insert_before(struct single_linked_list *list, void *val)
{
    struct single_linked_list *prev;
    struct single_linked_list *tmp;

    if (!complain_null_pointer_p(list)) {
        prev = single_linked_list_previous_internal(list);
        tmp = single_linked_list_node_create(val, 0u);

        tmp->next = list;
        prev->next = tmp;
    }
}

struct single_linked_list *
single_linked_list_node_copy(struct single_linked_list *node)
{
    struct single_linked_list *copy;

    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        copy = single_linked_list_node_create(node->val, node->sid);
        copy->next = node->next;

        return copy;
    }
}

void
single_linked_list_destroy(struct single_linked_list **list)
{
    register struct single_linked_list *node;
    register struct single_linked_list **next;

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(*list)) {
        node = *list;
        /*
         * We do not use the way like douby linked list used, because
         * lazy remove need to get previous node. This will result in
         * go through all node in list, which has heavy performance
         * drop in performance test.
         */
        do {
            next = &node->next;
            memory_cache_free(node);
            node = *next;
        } while (*list != node);

        *list = NULL;
    }
}

static inline uint32
single_linked_list_length_internal(struct single_linked_list *list)
{
    uint32 len;
    register struct single_linked_list *node;

    assert(NULL != list);

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
    if (complain_null_pointer_p(list)) {
        return 0u;
    } else {
        return single_linked_list_length_internal(list);
    }
}

struct single_linked_list *
single_linked_list_node_by_index(struct single_linked_list *list, uint32 index)
{
    register struct single_linked_list *node;
    uint32 len;

    if (complain_null_pointer_p(list)) {
        return NULL;
    } else {
        len = single_linked_list_length_internal(list);
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
single_linked_list_contains_p_internal(struct single_linked_list *list,
    struct single_linked_list *node)
{
    register struct single_linked_list *iter;

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
single_linked_list_contains_p(struct single_linked_list *list,
    struct single_linked_list *node)
{
    if (complain_null_pointer_p(list) || complain_null_pointer_p(node)) {
        return false;
    } else {
        return single_linked_list_contains_p_internal(list, node);
    }
}

void
single_linked_list_serialize(struct single_linked_list *list)
{
    struct single_linked_list *node;
    uint32 index;

    if (!complain_null_pointer_p(list)) {
        index = 0;
        node = list;
        do {
            node->sid = index++;
            node = node->next;
        } while (node != list);
    }
}

static inline struct single_linked_list *
single_linked_list_previous_internal(struct single_linked_list *node)
{
    register struct single_linked_list *prev;

    assert(NULL != node);
    assert(NULL != node->next);

    prev = node;

    do {
        prev = prev->next;
    } while (prev->next != node);

    return prev;
}

struct single_linked_list *
single_linked_list_previous(struct single_linked_list *node)
{
    if (complain_null_pointer_p(node) || complain_null_pointer_p(node->next)) {
        return NULL;
    } else {
        return single_linked_list_previous_internal(node);
    }
}

static inline struct single_linked_list *
single_linked_list_node_remove_internal_default(struct single_linked_list **node)
{
    struct single_linked_list *removed;
    struct single_linked_list *prev;

    assert(NULL != node);
    assert(NULL != *node);

    removed = *node;

    if (*node == removed->next) {
        *node = NULL;
        return removed;
    } else {
        prev = single_linked_list_previous_internal(removed);
        prev->next = removed->next;
        *node = removed->next;
        removed->next = removed;

        return removed;
    }
}

struct single_linked_list *
single_linked_list_node_remove(struct single_linked_list **node)
{
    if (complain_null_pointer_p(node) || complain_null_pointer_p(*node)) {
        return NULL;
    } else {
        return single_linked_list_node_remove_internal(node);
    }
}

void
single_linked_list_node_remove_and_destroy(struct single_linked_list **node)
{
    struct single_linked_list *removed;

    if (!complain_null_pointer_p(node) && !complain_null_pointer_p(*node)) {
        removed = single_linked_list_node_remove_internal(node);
        memory_cache_free(removed);
    }
}


void
single_linked_list_iterate(struct single_linked_list *list,
    void (*handler)(void *))
{
    register struct single_linked_list *node;

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(handler)) {
        node = list;

        do {
            (*handler)(single_linked_list_node_val(node));
            node = node->next;
        } while (node != list);
    }
}

struct single_linked_list *
single_linked_list_merge(struct single_linked_list *m,
    struct single_linked_list *n)
{
    register struct single_linked_list *iter;

    if (complain_null_pointer_p(m) || complain_null_pointer_p(n)) {
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        do {
            assert(!single_linked_list_contains_p_internal(m, iter));
            single_linked_list_insert_after_internal(m, iter->val, iter->sid);

            iter = iter->next;
        } while (iter != n);

        return m;
    }
}

