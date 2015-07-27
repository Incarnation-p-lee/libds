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
        return skip_linked_list_node_find(list, key, SKIP_LIST_MAX_LVL_IDX);
    }
}

static inline struct skip_linked_list *
skip_linked_list_node_find(struct skip_linked_list *list,
    sint32 key, uint32 lvl)
{
    assert(NULL != list);
    assert(SKIP_LIST_MAX_LVL > lvl);

    while (true) {
        if (list->key == key) {
            return list;
        } else if (list->key > key) {
            /*
             * key sorted list.
             */
            return NULL;
        } else if (!list->layer[lvl] && SKIP_LIST_BOTTOM_IDX != lvl) {
            lvl--;
        } else if (!list->layer[lvl]) {
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

    do {
        tgt->layer[lvl] = list;
    } while (0 != lvl--);

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
    } else if (NULL != skip_linked_list_node_find(*list, tgt->key, lvl)) {
        pr_log_warn("Insert node alreay exist, nothing will be done.\n");
        return NULL;
    } else {
        head = list;
        iter = *head;

        if (tgt->key < iter->key) {
            *list = skip_linked_list_insert_before_head(iter, tgt);
        } else {
            while (true) {
                head = &iter->layer[lvl];

                if (!*head || (*head)->key > tgt->key) {
                    prev_list[lvl] = iter;
                    if (SKIP_LIST_BOTTOM_IDX == lvl) {
                        skip_linked_list_insert_update_with_lvl(tgt, prev_list,
                            random_uint32_with_limit(SKIP_LIST_MAX_LVL));
                        break;
                    } else {
                        lvl--;
                    }
                } else {
                    iter = iter->layer[lvl];
                }
            }
        }

        return tgt;
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

struct skip_linked_list *
skip_linked_list_node_remove(struct skip_linked_list *list,
    struct skip_linked_list *node)
{
    return NULL;
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

