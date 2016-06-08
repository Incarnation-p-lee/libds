struct skip_linked_list *
skip_linked_list_next(struct skip_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
skip_linked_list_next_set(struct skip_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        list->next = val;
    }
}

void *
skip_linked_list_val(struct skip_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else {
        return list->val;
    }
}

void
skip_linked_list_val_set(struct skip_linked_list *list, void *val)
{
    if (!complain_null_pointer_p(list)) {
        list->val = val;
    }
}

sint32
skip_linked_list_key(struct skip_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return SKIP_KEY_INVALID;
    } else {
        return list->key;
    }
}

void
skip_linked_list_key_set(struct skip_linked_list *list, sint32 key)
{
    if (!complain_null_pointer_p(list)) {
        list->key = key;
    }
}

struct skip_linked_list *
skip_linked_list_create(void)
{
    return skip_linked_list_node_create(NULL, 0);
}

struct skip_linked_list *
skip_linked_list_node_create(void *val, sint32 key)
{
    struct skip_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    memset(list, 0, sizeof(*list));
    skip_linked_list_initial_internal(list, val, key);

    return list;
}

void
skip_linked_list_initial(struct skip_linked_list *list)
{
    if (!complain_null_pointer_p(list)) {
        skip_linked_list_initial_internal(list, NULL, 0);
    }
}

static inline void
skip_linked_list_initial_internal(struct skip_linked_list *list,
    void *val, sint32 key)
{
    dp_assert(!complain_null_pointer_p(list));

    list->key = key;
    list->val = val;
    list->next = NULL;
}

void
skip_linked_list_destroy(struct skip_linked_list **list)
{
    register struct skip_linked_list *next;
    register struct skip_linked_list *node;

    if (!complain_null_pointer_p(*list) && !complain_null_pointer_p(list)) {
        node = *list;

        while (node) {
            next = node->next;
            memory_cache_dp_free(node);
            node = next;
        }

        *list = NULL;
    }
}

static inline uint32
skip_linked_list_length_internal(struct skip_linked_list *list)
{
    uint32 retval;
    register struct skip_linked_list *node;

    dp_assert(NULL != list);

    retval = 0u;
    node = list;

    while (node) {
        retval++;
        node = node->next;
    }

    return retval;
}

uint32
skip_linked_list_length(struct skip_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return 0u;
    } else {
        return skip_linked_list_length_internal(list);
    }
}

struct skip_linked_list *
skip_linked_list_find_key(struct skip_linked_list *list, sint32 key)
{
    if (complain_null_pointer_p(list)) {
        return NULL;
    } else {
        return skip_linked_list_find_key_internal(list, key,
            SKIP_LIST_MAX_LVL_IDX);
    }
}

static inline struct skip_linked_list *
skip_linked_list_find_key_internal(struct skip_linked_list *list,
    sint32 key, uint32 lvl)
{
    struct skip_linked_list **head;

    dp_assert(NULL != list);
    dp_assert(SKIP_LIST_MAX_LVL > lvl);

    while (true) {
        head = &list->layer[lvl];

        if (list->key == key) {
            return list;
        } else if ((!*head || (*head)->key > key)) {
            /*
             * end condition of find key.
             */
            if (SKIP_LIST_BOTTOM_IDX != lvl) {
                lvl--;
            } else {
                return NULL;
            }
        } else {
            list = list->layer[lvl];
        }
    }
}

static inline bool
skip_linked_list_key_contains_p_internal(struct skip_linked_list *list, sint32 key)
{
    struct skip_linked_list *tmp;

    dp_assert(NULL != list);

    tmp = skip_linked_list_find_key_internal(list, key,
        SKIP_LIST_MAX_LVL_IDX);

    return NULL == tmp ? false : true;
}

bool
skip_linked_list_key_contains_p(struct skip_linked_list *list, sint32 key)
{
    if (complain_null_pointer_p(list)) {
        return false;
    } else {
        return skip_linked_list_key_contains_p_internal(list, key);
    }
}

static inline struct skip_linked_list *
skip_linked_list_insert_before_head(struct skip_linked_list *list,
    struct skip_linked_list *tgt)
{
    uint32 lvl;

    dp_assert(NULL != tgt);
    dp_assert(NULL != list);
    dp_assert(tgt->key < list->key);

    lvl = SKIP_LIST_MAX_LVL_IDX;

    while (SKIP_LIST_BOTTOM_IDX != lvl) {
        tgt->layer[lvl] = list->layer[lvl];
        list->layer[lvl] = NULL;
        lvl--;
    }

    tgt->layer[SKIP_LIST_BOTTOM_IDX] = list;

    return tgt;
}

static inline struct skip_linked_list *
skip_linked_list_insert_internal(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    uint32 lvl;
    register struct skip_linked_list *iter;
    register struct skip_linked_list **head;
    struct skip_linked_list *prev_list[SKIP_LIST_MAX_LVL];

    dp_assert(NULL != list);
    dp_assert(NULL != *list);
    dp_assert(NULL != tgt);

    lvl = SKIP_LIST_MAX_LVL_IDX;
    head = list;
    iter = *head;

    if (tgt->key < iter->key) {
        *list = skip_linked_list_insert_before_head(iter, tgt);
        return tgt;
    } else {
        while (true) {
            head = &iter->layer[lvl];

            if (iter == tgt || *head == tgt) {
                return NULL;
            } else if (!*head || (*head)->key >= tgt->key) {
                prev_list[lvl] = iter;

                if (SKIP_LIST_BOTTOM_IDX == lvl) {
                    skip_linked_list_insert_update_with_lvl(tgt, prev_list,
                        random_uint32_with_limit(SKIP_LIST_MAX_LVL));

                    dp_assert(skip_linked_list_ordering_p(*list));
                    return tgt;
                } else {
                    lvl--;
                }
            } else {
                iter = iter->layer[lvl];
            }
        }
    }
}

/*
 * RETURN the inserted node of linked list, or RETURN NULL.
 */
struct skip_linked_list *
skip_linked_list_insert(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    struct skip_linked_list *inserted;

    if (complain_null_pointer_p(list) || complain_null_pointer_p(tgt)) {
        return NULL;
    } else {
        inserted = skip_linked_list_insert_internal(list, tgt);

        if (!inserted) {
            pr_log_warn("Insert node already existed in linked list.\n");
        }

        return inserted;
    }
}

static inline void
skip_linked_list_insert_update_with_lvl(struct skip_linked_list *tgt,
    struct skip_linked_list **prev_list, uint32 lvl)
{
    dp_assert(NULL != prev_list);
    dp_assert(NULL != tgt);
    dp_assert(SKIP_LIST_MAX_LVL > lvl);

    do {
        tgt->layer[lvl] = prev_list[lvl]->layer[lvl];
        prev_list[lvl]->layer[lvl] = tgt;
    } while (0 != lvl--);
}

struct skip_linked_list *
skip_linked_list_node_by_index(struct skip_linked_list *list, uint32 index)
{
    uint32 len;
    register struct skip_linked_list *iter;

    if (complain_null_pointer_p(list)) {
        return NULL;
    } else {
        iter = list;
        len = skip_linked_list_length(list);

        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        while (index) {
            iter = iter->next;
            index--;
        }

        return iter;
    }
}

static inline void
skip_linked_list_node_clean(struct skip_linked_list *list)
{
    uint32 lvl;

    dp_assert(NULL != list);

    lvl = SKIP_LIST_BOTTOM_IDX;

    while (NULL != list->layer[lvl] && lvl < SKIP_LIST_MAX_LVL) {
        list->layer[lvl++] = NULL;
    }
}

static inline struct skip_linked_list *
skip_linked_list_remove_head(struct skip_linked_list *list)
{
    struct skip_linked_list *next;
    uint32 lvl;

    dp_assert(NULL != list);

    next = list->next;

    if (next) {
        lvl = SKIP_LIST_MAX_LVL_IDX;

        while (NULL == next->layer[lvl] && lvl > SKIP_LIST_BOTTOM_IDX) {
            next->layer[lvl] = list->layer[lvl];
            lvl--;
        }
    }

    skip_linked_list_node_clean(list);

    return list;
}

static inline struct skip_linked_list *
skip_linked_list_remove_with_previous_list(struct skip_linked_list *tgt,
    struct skip_linked_list **pre_list, uint32 lvl)
{
    dp_assert(NULL != pre_list);
    dp_assert(NULL != tgt);
    dp_assert(lvl < SKIP_LIST_MAX_LVL);

    do {
        pre_list[lvl]->layer[lvl] = tgt->layer[lvl];
    } while (0 != lvl--);

    skip_linked_list_node_clean(tgt);

    return tgt;
}

static inline void
skip_linked_list_remove_on_level(struct skip_linked_list *list,
    struct skip_linked_list *removed, uint32 level)
{
    struct skip_linked_list *iter;

    dp_assert(NULL != removed);
    dp_assert(NULL != list);
    dp_assert(SKIP_LIST_MAX_LVL > level);

    do {
        iter = list;
        dp_assert(skip_linked_list_exist_on_level(list, removed, level));

        while (iter->layer[level] != removed) {
            iter = iter->layer[level];
        }

        iter->layer[level] = removed->layer[level];
        level--;
    } while (SKIP_LIST_MAX_LVL > level);

    skip_linked_list_node_clean(removed);
}

static inline struct skip_linked_list *
skip_linked_list_remove_internal(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *node;
    struct skip_linked_list *head;
    struct skip_linked_list *removed;
    uint32 lvl;

    dp_assert(NULL != list);
    dp_assert(NULL != *list);

    if ((*list)->key == key) {
        removed = *list;
        *list = removed->next;

        return skip_linked_list_remove_head(removed);
    } else {
        node = *list;
        head = node;
        lvl = SKIP_LIST_MAX_LVL_IDX;

        while (true) {
            list = &node->layer[lvl];

            if (!*list || (*list)->key > key) {
                if (SKIP_LIST_BOTTOM_IDX == lvl) {
                    return NULL;
                } else {
                    lvl--;
                }
            } else if ((*list)->key == key) {
                removed = *list;
                skip_linked_list_remove_on_level(head, removed, lvl);
                return removed;
            } else {
                node = node->layer[lvl];
            }
        }
    }
}

void
skip_linked_list_remove_and_destroy(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *removed;

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(*list)) {
        removed = skip_linked_list_remove_internal(list, key);

        if (!removed) {
            pr_log_warn("The node to be removed do not exist in given list.\n");
        } else {
            memory_cache_dp_free(removed);
        }
    }
}

struct skip_linked_list *
skip_linked_list_remove(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *removed;

    if (complain_null_pointer_p(list) || complain_null_pointer_p(*list)) {
        return NULL;
    } else {
        removed = skip_linked_list_remove_internal(list, key);

        if (!removed) {
            pr_log_warn("The node to be removed do not exist in given list.\n");
        }

        return removed;
    }
}

void
skip_linked_list_iterate(struct skip_linked_list *list,
    void (*handler)(void *))
{
    register struct skip_linked_list *iter;

    if (!complain_null_pointer_p(list) && !complain_null_pointer_p(handler)) {
        iter = list;

        while(iter) {
            (*handler)(iter->val);
            iter = iter->next;
        }
    }
}

struct skip_linked_list *
skip_linked_list_merge(struct skip_linked_list *m, struct skip_linked_list *n)
{
    struct skip_linked_list *iter;
    struct skip_linked_list *inserted;

    if (complain_null_pointer_p(m) || complain_null_pointer_p(n)) {
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        while (iter) {
            if (skip_linked_list_key_contains_p_internal(m, iter->key)) {
                pr_log_warn("Duplicated key appears in merge list.\n");
            } else {
                inserted = skip_linked_list_node_create(iter->val, iter->key);
                skip_linked_list_insert_internal(&m, inserted);
            }

            iter = iter->next;
        }

        return m;
    }
}

