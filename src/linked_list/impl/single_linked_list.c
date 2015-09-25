struct single_linked_list *
single_linked_list_create(void)
{
    return single_linked_list_node_create(NULL, 0u);
}

struct single_linked_list *
single_linked_list_node_create(void *val, uint32 sid)
{
    struct single_linked_list *list;

    list = malloc_ds(sizeof(*list));
    if (!list) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        single_linked_list_node_initial(list, val, sid);
        return list;
    }
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
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        list->sid = sid;
        list->val = val;
        list->next = list;
    }
}

void
single_linked_list_node_append(struct single_linked_list *node, void *val)
{
    struct single_linked_list *next;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (!node->next) {
        pr_log_warn("Destroyed data structure.\n");
    } else {
        next = single_linked_list_node_create(val, 0u);
        single_linked_list_node_insert_after_internal(node, next);
    }
}

static inline void
single_linked_list_node_insert_after_internal(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    assert(NULL != cur);
    assert(NULL != node);

    node->next = cur->next;
    cur->next = node;
}

void
single_linked_list_node_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        single_linked_list_node_insert_after_internal(cur, node);
    }
}

void
single_linked_list_node_insert_before_internal(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    struct single_linked_list *prev;

    assert(NULL != cur);
    assert(NULL != node);

    //FixMe: add check for inserted node already exist
    prev = single_linked_list_node_previous_internal(cur);
    assert(NULL != prev);

    node->next = prev->next;
    prev->next = node;
}

void
single_linked_list_node_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    if (!cur || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        single_linked_list_node_insert_before_internal(cur, node);
    }
}

struct single_linked_list *
single_linked_list_node_copy(struct single_linked_list *node)
{
    struct single_linked_list *copy;

    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

    if (!list || !*list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node = *list;
        /*
         * We do not use the way like douby linked list used, because
         * lazy remove need to get previous node. This will result in
         * go through all node in list, which has heavy performance
         * drop in unit test.
         */
        do {
            next = &node->next;
            free_ds(node);
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
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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
    if (!list || !node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

static inline struct single_linked_list *
single_linked_list_node_previous_internal(struct single_linked_list *node)
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
single_linked_list_node_previous(struct single_linked_list *node)
{
    if (!node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (!node->next) {
        pr_log_warn("Destroyed data structure.\n");
        return NULL;
    } else {
        return single_linked_list_node_previous_internal(node);
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
        prev = single_linked_list_node_previous_internal(removed);
        prev->next = removed->next;
        *node = removed->next;
        removed->next = removed;

        return removed;
    }
}

struct single_linked_list *
single_linked_list_node_remove(struct single_linked_list **node)
{
    if (!node || !*node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return single_linked_list_node_remove_internal(node);
    }
}

void
single_linked_list_node_remove_and_destroy(struct single_linked_list **node)
{
    struct single_linked_list *removed;

    if (!node || !*node) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = single_linked_list_node_remove_internal(node);
        free_ds(removed);
    }
}


void
single_linked_list_iterate(struct single_linked_list *list,
    void (*handler)(void *))
{
    register struct single_linked_list *node;

    if (!list || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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
    register struct single_linked_list *new;

    if (!m || !n) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        do {
            if (!single_linked_list_contains_p_internal(m, iter)) {
                new = single_linked_list_node_create(iter->val, iter->sid);
                // optimization
                single_linked_list_node_insert_before_internal(m, new);
            }

            iter = iter->next;
        } while (iter != n);

        return m;
    }
}

