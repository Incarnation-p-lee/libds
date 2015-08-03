struct skip_linked_list *
skip_linked_list_create(void)
{
    return skip_linked_list_node_create(NULL, 0);
}

struct skip_linked_list *
skip_linked_list_node_create(void *val, sint32 key)
{
    struct skip_linked_list *list;

    list = malloc_ds(sizeof(*list));
    if (!list) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        memset(list, 0, sizeof(*list));
        skip_linked_list_node_initial(list, val, key);
    }

    return list;
}

void
skip_linked_list_initial(struct skip_linked_list *list)
{
    skip_linked_list_node_initial(list, NULL, 0);
}

void
skip_linked_list_node_initial(struct skip_linked_list *list,
    void *val, sint32 key)
{
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        list->key = key;
        list->val = val;
        list->next = NULL;
    }
}

void
skip_linked_list_destroy(struct skip_linked_list **list)
{
    register struct skip_linked_list *next;
    register struct skip_linked_list *node;

    if (!*list || !list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        node = *list;

        while (node) {
            next = node->next;
            free_ds(node);
            node = next;
        }

        *list = NULL;
    }
}

uint32
skip_linked_list_length(struct skip_linked_list *list)
{
    uint32 retval;
    register struct skip_linked_list *node;

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return 0u;
    } else {
        retval = 0u;
        node = list;

        while (node) {
            retval++;
            node = node->next;
        }

        return retval;
    }
}

struct skip_linked_list *
skip_linked_list_node_find_key(struct skip_linked_list *list, sint32 key)
{
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return skip_linked_list_node_find_key_internal(list, key,
            SKIP_LIST_MAX_LVL_IDX);
    }
}

static inline struct skip_linked_list *
skip_linked_list_node_find_key_internal(struct skip_linked_list *list,
    sint32 key, uint32 lvl)
{
    struct skip_linked_list **head;

    assert(NULL != list);
    assert(SKIP_LIST_MAX_LVL > lvl);

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
skip_linked_list_contains_p_internal(struct skip_linked_list *list,
    struct skip_linked_list *tgt)
{
    struct skip_linked_list *tmp;

    assert(NULL != list);
    assert(NULL != tgt);

    tmp = skip_linked_list_node_find_key_internal(list, tgt->key,
        SKIP_LIST_MAX_LVL_IDX);

    if (tgt == tmp) {
        return true;
    } else {
        return false;
    }
}


bool
skip_linked_list_contains_p(struct skip_linked_list *list,
    struct skip_linked_list *tgt)
{
    if (!list || !tgt) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return skip_linked_list_contains_p_internal(list, tgt);
    }
}

static inline struct skip_linked_list *
skip_linked_list_insert_before_head(struct skip_linked_list *list,
    struct skip_linked_list *tgt)
{
    uint32 lvl;

    assert(NULL != tgt);
    assert(NULL != list);
    assert(tgt->key < list->key);

    lvl = SKIP_LIST_MAX_LVL_IDX;

    while (SKIP_LIST_BOTTOM_IDX != lvl) {
        tgt->layer[lvl] = list->layer[lvl];
        list->layer[lvl] = NULL;
        lvl--;
    }

    tgt->layer[SKIP_LIST_BOTTOM_IDX] = list;

    return tgt;
}

/*
 * RETURN the inserted node of linked list, or RETURN NULL.
 */
struct skip_linked_list *
skip_linked_list_node_insert(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    uint32 lvl;
    register struct skip_linked_list *iter;
    register struct skip_linked_list **head;
    struct skip_linked_list *prev_list[SKIP_LIST_MAX_LVL];

    lvl = SKIP_LIST_MAX_LVL_IDX;

    if (!list || !tgt) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        head = list;
        iter = *head;

        if (tgt->key < iter->key) {
            *list = skip_linked_list_insert_before_head(iter, tgt);
            return tgt;
        } else {
            while (true) {
                head = &iter->layer[lvl];

                if (iter == tgt) {
                    pr_log_warn("Insert node alreay exist, nothing will be done.\n");
                    return NULL;
                } else if (iter->key == tgt->key) {
                    pr_log_warn("The key of insert node already exist, nothing will be done.\n");
                    return NULL;
                } else if (!*head || (*head)->key > tgt->key) {
                    prev_list[lvl] = iter;

                    if (SKIP_LIST_BOTTOM_IDX == lvl) {
                        skip_linked_list_insert_update_with_lvl(tgt, prev_list,
                            random_uint32_with_limit(SKIP_LIST_MAX_LVL));

                        assert(skip_linked_list_ordering_p(*list));
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
}

static inline void
skip_linked_list_insert_update_with_lvl(struct skip_linked_list *tgt,
    struct skip_linked_list **prev_list, uint32 lvl)
{
    assert(NULL != prev_list);
    assert(NULL != tgt);
    assert(SKIP_LIST_MAX_LVL > lvl);

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

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

    assert(NULL != list);

    lvl = SKIP_LIST_BOTTOM_IDX;

    while (NULL != list->layer[lvl] && lvl < SKIP_LIST_MAX_LVL) {
        list->layer[lvl++] = NULL;
    }
}

static inline struct skip_linked_list *
skip_linked_list_node_remove_head(struct skip_linked_list *list)
{
    struct skip_linked_list *next;
    uint32 lvl;

    assert(NULL != list);

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
skip_linked_list_node_remove_with_previous_list(struct skip_linked_list *tgt,
    struct skip_linked_list **pre_list, uint32 lvl)
{
    assert(NULL != pre_list);
    assert(NULL != tgt);
    assert(lvl < SKIP_LIST_MAX_LVL);
    assert(lvl == skip_linked_list_node_level(tgt));

    do {
        pre_list[lvl]->layer[lvl] = tgt->layer[lvl];
    } while (0 != lvl--);

    skip_linked_list_node_clean(tgt);

    return tgt;
}

static inline uint32
skip_linked_list_node_level(struct skip_linked_list *list)
{
    uint32 level;

    assert(NULL != list);

    level = SKIP_LIST_MAX_LVL_IDX;

    while (NULL == list->layer[level] && SKIP_LIST_BOTTOM_IDX != level) {
        level--;
    }

    return level;
}

static inline struct skip_linked_list *
skip_linked_list_node_remove_internal(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *node;
    struct skip_linked_list *removed;
    struct skip_linked_list *prev_list[SKIP_LIST_MAX_LVL];
    uint32 lvl;
    uint32 lmt;

    assert(NULL != list);
    assert(NULL != *list);

    if ((*list)->key == key) {
        removed = *list;
        *list = removed->next;

        return skip_linked_list_node_remove_head(removed);
    } else {
        node = *list;
        lvl = SKIP_LIST_MAX_LVL_IDX;

        while (true) {
            list = &node->layer[lvl];

            if (!*list || (*list)->key > key) {
                prev_list[lvl] = node;

                if (SKIP_LIST_BOTTOM_IDX == lvl) {
                    return NULL;
                } else {
                    lvl--;
                }
            } else if ((*list)->key == key) {
                removed = *list;
                prev_list[lvl] = node;

                if (SKIP_LIST_BOTTOM_IDX == lvl) {
                    lmt = skip_linked_list_node_level(removed);
                    return skip_linked_list_node_remove_with_previous_list(removed,
                        prev_list, lmt);
                } else {
                    lvl--;
                }
            } else {
                node = node->layer[lvl];
            }
        }
    }
}

void
skip_linked_list_node_remove_and_destroy(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *removed;

    if (!list || !*list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        removed = skip_linked_list_node_remove_internal(list, key);

        if (!removed) {
            pr_log_warn("The node to be removed do not exist in given list.\n");
        } else {
            free_ds(removed);
        }
    }
}

struct skip_linked_list *
skip_linked_list_node_remove(struct skip_linked_list **list,
    sint32 key)
{
    struct skip_linked_list *removed;

    if (!list || !*list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        removed = skip_linked_list_node_remove_internal(list, key);

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

    if (!list || !handler) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
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

    if (!m || !n) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL == m ? n : m;
    } else if (m == n) {
        pr_log_info("Merge same linked list, nothing will be done.\n");
        return m;
    } else {
        iter = n;

        while (iter) {
            if (!skip_linked_list_contains_p_internal(m, iter)) {
                inserted = skip_linked_list_node_create(iter->val, iter->key);
                skip_linked_list_node_insert(&m, inserted);
            }

            iter = iter->next;
        }

        return m;
    }
}

