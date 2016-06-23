struct skip_linked_list *
skip_linked_list_next(struct skip_linked_list *list)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
skip_linked_list_next_set(struct skip_linked_list *list,
    struct linked_list *next)
{
    if (skip_linked_list_structure_legal_p(list)
        && skip_linked_list_structure_legal_p(next)) {
        list->next = next;
    }
}

sint32
skip_linked_list_key(struct skip_linked_list *list)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return SKIP_KEY_INVALID;
    } else {
        return list->key;
    }
}

void
skip_linked_list_key_set(struct skip_linked_list *list, sint32 key)
{
    if (skip_linked_list_structure_legal_p(list)) {
        list->key = key;
    }
}

static inline bool
skip_linked_list_structure_legal_p(struct skip_linked_list *list)
{
    if (complain_null_pointer_p(list)) {
        return false;
    } else if (list->next == list) {
        return false;
    } else if (list->key == SKIP_KEY_INVALID) {
        return false;
    } else {
        return true;
    }
}

struct skip_linked_list *
skip_linked_list_create(void)
{
    struct skip_linked_list *list;

    list = memory_cache_allocate(sizeof(*list));
    memset(list, 0, sizeof(*list));
    skip_linked_list_initial_i(list, key);

    return list;
}

void
skip_linked_list_initial(struct skip_linked_list *list)
{
    if (!complain_null_pointer_p(list)) {
        skip_linked_list_initial_i(list, 0);
    }
}

static inline void
skip_linked_list_initial_i(struct skip_linked_list *list, sint32 key)
{
    dp_assert(!complain_null_pointer_p(list));

    list->key = key;
    list->next = NULL;
}

void
skip_linked_list_destroy(struct skip_linked_list **list)
{
    struct skip_linked_list *next;
    struct skip_linked_list *node;

    if (!complain_null_pointer_p(list)
        && skip_linked_list_structure_legal_p(list)) {
        node = *list;

        while (node) {
            next = node->next;
            memory_cache_free(node);
            node = next;
        }

        *list = NULL;
    }
}

static inline uint32
skip_linked_list_length_i(struct skip_linked_list *list)
{
    uint32 retval;
    struct skip_linked_list *node;

    dp_assert(skip_linked_list_structure_legal_p(list));

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
    if (!skip_linked_list_structure_legal_p(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return skip_linked_list_length_i(list);
    }
}

struct skip_linked_list *
skip_linked_list_find_key(struct skip_linked_list *list, sint32 key)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_find_key_i(list, key, SKIP_LIST_MAX_LVL_IDX);
    }
}

static inline struct skip_linked_list *
skip_linked_list_find_key_i(struct skip_linked_list *list, sint32 key, uint32 lv)
{
    struct skip_linked_list **head;

    dp_assert(skip_linked_list_structure_legal_p(list));
    dp_assert(SKIP_LIST_MAX_LVL > lv);

    while (true) {
        head = &list->layer[lv];

        if (list->key == key) {
            return list;
        } else if ((!*head || (*head)->key > key)) {
            if (SKIP_LIST_BOTTOM_IDX != lv) {
                lv--;
            } else {
                return NULL;
            }
        } else {
            list = list->layer[lv];
        }
    }
}

static inline bool
skip_linked_list_key_contains_i_p(struct skip_linked_list *list, sint32 key)
{
    dp_assert(skip_linked_list_structure_legal_p(list));

    if (skip_linked_list_find_key_i(list, key, SKIP_LIST_MAX_LVL_IDX)) {
        return true;
    } else {
        return false;
    }
}

bool
skip_linked_list_key_contains_p(struct skip_linked_list *list, sint32 key)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return false;
    } else {
        return skip_linked_list_key_contains_i_p(list, key);
    }
}

static inline struct skip_linked_list *
skip_linked_list_insert_before_head(struct skip_linked_list *list,
    struct skip_linked_list *tgt)
{
    uint32 lv;

    dp_assert(skip_linked_list_structure_legal_p(list));
    dp_assert(skip_linked_list_structure_legal_p(tgt));
    dp_assert(tgt->key < list->key);

    lv = SKIP_LIST_MAX_LVL_IDX;

    while (SKIP_LIST_BOTTOM_IDX != lv) {
        tgt->layer[lv] = list->layer[lv];
        list->layer[lv] = NULL;
        lv--;
    }

    tgt->layer[SKIP_LIST_BOTTOM_IDX] = list;

    return tgt;
}

static inline struct skip_linked_list *
skip_linked_list_insert_i(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    uint32 lv;
    uint32 lmt;
    struct skip_linked_list *skip;
    struct skip_linked_list **head;
    struct skip_linked_list *prev_list[SKIP_LIST_MAX_LVL];

    dp_assert(!complain_null_pointer_p(list));
    dp_assert(skip_linked_list_ordering_p(*list));
    dp_assert(skip_linked_list_structure_legal_p(tgt));
    dp_assert(skip_linked_list_structure_legal_p(*list));

    lv = SKIP_LIST_MAX_LVL_IDX;
    head = list;
    skip = *head;

    if (tgt->key < skip->key) {
        *list = skip_linked_list_insert_before_head(skip, tgt);
    } else {
        while (true) {
            head = &skip->layer[lv];

            if (skip == tgt || *head == tgt) {
                pr_log_warn("Insert node already existed in linked list.\n");
                return NULL;
            } else if (!*head || (*head)->key >= tgt->key) {
                prev_list[lv] = skip;

                if (SKIP_LIST_BOTTOM_IDX == lv) {
                    lmt = random_uint32_with_limit(SKIP_LIST_MAX_LVL);
                    skip_linked_list_insert_update_with_lv(tgt, prev_list, lmt);
                    break;
                } else {
                    lv--;
                }
            } else {
                skip = skip->layer[lv];
            }
        }
    }

    dp_assert(skip_linked_list_ordering_p(*list));
    return tgt;
}

struct skip_linked_list *
skip_linked_list_insert(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else if (skip_linked_list_structure_legal_p(*list)) {
        return PTR_INVALID;
    } else if (skip_linked_list_structure_legal_p(tgt)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_insert_i(list, tgt);
    }
}

static inline void
skip_linked_list_insert_update_with_lv(struct skip_linked_list *tgt,
    struct skip_linked_list **prev_list, uint32 lv)
{
    dp_assert(!complain_null_pointer_p(prev_list));
    dp_assert(skip_linked_list_structure_legal_p(tgt));
    dp_assert(SKIP_LIST_MAX_LVL > lv);

    do {
        tgt->layer[lv] = prev_list[lv]->layer[lv];
        prev_list[lv]->layer[lv] = tgt;
    } while (0 != lv--);
}

struct skip_linked_list *
skip_linked_list_node_by_index(struct skip_linked_list *list, uint32 index)
{
    uint32 len;
    struct skip_linked_list *skip;

    if (!skip_linked_list_structure_legal_p(list)) {
        return PTR_INVALID;
    } else {
        skip = list;
        len = skip_linked_list_length(list);

        if (index >= len) {
            pr_log_warn("Index out of the lenght, rotated to front.\n");
            index = index % len;
        }

        while (index) {
            skip = skip->next;
            index--;
        }

        return skip;
    }
}

static inline void
skip_linked_list_node_clean(struct skip_linked_list *list)
{
    uint32 lv;

    dp_assert(skip_linked_list_structure_legal_p(list));

    lv = SKIP_LIST_BOTTOM_IDX;

    while (NULL != list->layer[lv] && lv < SKIP_LIST_MAX_LVL) {
        list->layer[lv++] = NULL;
    }
}

static inline void
skip_linked_list_remove_head(struct skip_linked_list *list)
{
    uint32 lv;
    struct skip_linked_list *next;

    dp_assert(skip_linked_list_structure_legal_p(list));

    next = list->next;

    if (next) {
        lv = SKIP_LIST_MAX_LVL_IDX;

        while (NULL == next->layer[lv] && lv > SKIP_LIST_BOTTOM_IDX) {
            next->layer[lv] = list->layer[lv];
            lv--;
        }
    }

    skip_linked_list_node_clean(list);
}

static inline struct skip_linked_list *
skip_linked_list_remove_with_previous_list(struct skip_linked_list *tgt,
    struct skip_linked_list **pre_list, uint32 lv)
{
    dp_assert(lv < SKIP_LIST_MAX_LVL);
    dp_assert(!complain_null_pointer_p(pre_list));
    dp_assert(skip_linked_list_structure_legal_p(tgt));

    do {
        pre_list[lv]->layer[lv] = tgt->layer[lv];
    } while (0 != lv--);

    skip_linked_list_node_clean(tgt);

    return tgt;
}

static inline void
skip_linked_list_remove_on_level(struct skip_linked_list *list,
    struct skip_linked_list *removed, uint32 level)
{
    struct skip_linked_list *skip;

    dp_assert(SKIP_LIST_MAX_LVL > level);
    dp_assert(skip_linked_list_structure_legal_p(list));
    dp_assert(skip_linked_list_structure_legal_p(removed));

    do {
        skip = list;
        dp_assert(skip_linked_list_exist_on_level(list, removed, level));

        while (skip->layer[level] != removed) {
            skip = skip->layer[level];
        }

        skip->layer[level] = removed->layer[level];
        level--;
    } while (SKIP_LIST_MAX_LVL > level);

    skip_linked_list_node_clean(removed);
}

static inline struct skip_linked_list *
skip_linked_list_remove_i(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    uint32 lv;
    struct skip_linked_list *node;
    struct skip_linked_list *head;
    struct skip_linked_list *removed;

    dp_assert(!complain_null_pointer_p(list));
    dp_assert(skip_linked_list_ordering_p(*list));
    dp_assert(skip_linked_list_structure_legal_p(tgt));
    dp_assert(skip_linked_list_structure_legal_p(*list));

    if ((*list)->key == tgt->key) {
        removed = *list;
        *list = removed->next;

        skip_linked_list_remove_head(removed);
    } else {
        node = *list;
        head = node;
        lv = SKIP_LIST_MAX_LVL_IDX;

        while (true) {
            list = &node->layer[lv];

            if (!*list || (*list)->key > tgt->key) {
                if (SKIP_LIST_BOTTOM_IDX == lv) {
                    removed = NULL;
                    pr_log_warn("The removing node do not exist in given list.\n");
                    break;
                } else {
                    lv--;
                }
            } else if ((*list) == tgt) {
                removed = tgt;
                skip_linked_list_remove_on_level(head, removed, lv);
                break;
            } else {
                node = node->layer[lv];
            }
        }
    }

    dp_assert(skip_linked_list_ordering_p(*list));
    return removed;
}

struct skip_linked_list *
skip_linked_list_remove(struct skip_linked_list **list,
    struct skip_linked_list *tgt)
{
    if (complain_null_pointer_p(list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(*list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(tgt)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_remove_i(list, key);
    }
}

void
skip_linked_list_iterate(struct skip_linked_list *list,
    void (*handler)(void *))
{
    struct skip_linked_list *skip;

    if (!complain_null_pointer_p(handler)
        && skip_linked_list_structure_legal_p(list)) {
        skip = list;
        while(skip) {
            (*handler)(skip->val);
            skip = skip->next;
        }
    }
}

struct skip_linked_list *
skip_linked_list_merge(struct skip_linked_list *m, struct skip_linked_list *n)
{
    struct skip_linked_list *skip;
    struct skip_linked_list *inserted;

    if (!skip_linked_list_structure_legal_p(m)
        && !skip_linked_list_structure_legal_p(n)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(m)) {
        return n;
    } else if (!skip_linked_list_structure_legal_p(n)) {
        return m;
    } else {
        skip = n;

        while (skip) {
            // Fix-Me for repeated key
            if (skip_linked_list_key_contains_p_internal(m, skip->key)) {
                pr_log_warn("Duplicated key appears in merge list.\n");
            } else {
                inserted = skip_linked_list_node_create(skip->val, skip->key);
                skip_linked_list_insert_internal(&m, inserted);
            }

            skip = skip->next;
        }

        return m;
    }
}

