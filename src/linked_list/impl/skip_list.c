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
        skip_linked_list_node_key_set(list, key);
        skip_linked_list_node_val_set(list, val);
        skip_linked_list_node_next_set(list, list);
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
            next = skip_linked_list_node_next(*list);
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
            node = skip_linked_list_node_next(node);
        }

        return retval;
    }
}

static inline struct skip_linked_list *
skip_linked_list_node_find(struct skip_linked_list *list,
    sint32 key, uint32 lvl)
{
    assert(NULL != list);

    while (true) {
        if (list->key == key) {
            return list;
        } else if (list->key > key) {
            /*
             * key sorted list.
             */
            return NULL;
        } else if (!skip_linked_list_node_next(list)
            && SKIP_LIST_BOTTOM_IDX != lvl) {
            list = list->layer[--lvl];
        } else if (!skip_linked_list_node_next(list)
            && SKIP_LIST_BOTTOM_IDX == lvl) {
            /*
             * key is great than all keys in skip linked list.
             */
            return NULL;
        } else {
            list = list->layer[lvl];
        }
    }
}

bool
skip_linked_list_contains_p(struct skip_linked_list *list, sint32 key)
{
    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return NULL != skip_linked_list_node_find(list, key,
            SKIP_LIST_MAX_LVL_IDX) ? true : false;
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

    while (lvl) {
        tgt->layer[lvl] = list->layer[lvl];
        lvl--;
    }

    return tgt;
}

void
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
    } else if (NULL != skip_linked_list_node_find(*list, tgt->key, lvl)) {
        pr_log_warn("Insert node alreay exist, nothing will be done.\n");
    } else {
        head = list;
        iter = *head;

        if (tgt->key < iter->key) {
            *list = skip_linked_list_insert_before_head(iter, tgt);
        } else {
            while (true) {
                head = &iter->layer[lvl];

                if (!*head || (*head)->key > tgt->key) {
                    prev_list[lvl] = iter->layer[lvl];
                    if (SKIP_LIST_BOTTOM_IDX == lvl) {
                        skip_linked_list_insert_update_with_lvl(tgt, prev_list,
                            random_uint32_with_limit(SKIP_LIST_MAX_LVL));
                    } else {
                        iter = iter->layer[--lvl];
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
        lvl--;
    } while (0 != lvl);
}

struct skip_linked_list *
skip_linked_list_node_by_index(struct skip_linked_list *list, uint32 index)
{
    register struct skip_linked_list *iter;

    if (!list) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        iter = list;

        while (index) {
            iter = skip_linked_list_node_next(iter);
            index--;
        }

        return iter;
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
            (*handler)(skip_linked_list_node_val(iter));
            iter = skip_linked_list_node_next(iter);
        }
    }
}

