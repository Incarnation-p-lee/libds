s_skip_linked_list_t *
skip_linked_list_next(s_skip_linked_list_t *list)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return PTR_INVALID;
    } else {
        return list->next;
    }
}

void
skip_linked_list_next_set(s_skip_linked_list_t *list,
    s_skip_linked_list_t *next)
{
    if (skip_linked_list_structure_legal_p(list)
        && skip_linked_list_structure_legal_p(next)) {
        list->next = next;
    }
}

sint32
skip_linked_list_key(s_skip_linked_list_t *list)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return SKIP_KEY_INVALID;
    } else {
        return list->key;
    }
}

void
skip_linked_list_key_set(s_skip_linked_list_t *list, sint32 key)
{
    if (skip_linked_list_structure_legal_p(list)) {
        list->key = key;
    }
}

bool
skip_linked_list_structure_legal_p(s_skip_linked_list_t *list)
{
    return skip_linked_list_structure_legal_ip(list);
}

static inline bool
skip_linked_list_structure_legal_ip(s_skip_linked_list_t *list)
{
    if (NULL_PTR_P(list)) {
        return false;
    } else if (list->next == list) {
        return false;
    } else if (list->key == SKIP_KEY_INVALID) {
        return false;
    } else {
        return true;
    }
}

s_skip_linked_list_t *
skip_linked_list_create(void)
{
    s_skip_linked_list_t *list;

    list = memory_cache_allocate(sizeof(*list));
    memset(list, 0, sizeof(*list));
    skip_linked_list_initial_i(list, 0);

    return list;
}

s_skip_linked_list_t *
skip_linked_list_create_with_key(sint32 key)
{
    s_skip_linked_list_t *list;

    list = memory_cache_allocate(sizeof(*list));
    memset(list, 0, sizeof(*list));
    skip_linked_list_initial_i(list, key);

    return list;
}

void
skip_linked_list_initial(s_skip_linked_list_t *list)
{
    if (!NULL_PTR_P(list)) {
        skip_linked_list_initial_i(list, 0);
    }
}

static inline void
skip_linked_list_initial_i(s_skip_linked_list_t *list, sint32 key)
{
    assert_exit(!NULL_PTR_P(list));

    list->key = key;
    list->next = NULL;
}

void
skip_linked_list_destroy(s_skip_linked_list_t **list)
{
    s_skip_linked_list_t *next;
    s_skip_linked_list_t *node;

    if (!NULL_PTR_P(list)
        && skip_linked_list_structure_legal_p(*list)) {
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
skip_linked_list_length_i(s_skip_linked_list_t *list)
{
    uint32 retval;
    s_skip_linked_list_t *node;

    assert_exit(skip_linked_list_structure_legal_p(list));

    retval = 0u;
    node = list;

    while (node) {
        retval++;
        node = node->next;
    }

    return retval;
}

uint32
skip_linked_list_length(s_skip_linked_list_t *list)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return LIST_SIZE_INVALID;
    } else {
        return skip_linked_list_length_i(list);
    }
}

s_skip_linked_list_t *
skip_linked_list_find_key(s_skip_linked_list_t *list, sint32 key)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_find_key_i(list, key, SKIP_LIST_MAX_LVL_IDX);
    }
}

static inline s_skip_linked_list_t *
skip_linked_list_find_key_i(s_skip_linked_list_t *list, sint32 key, uint32 lv)
{
    s_skip_linked_list_t **head;

    assert_exit(skip_linked_list_structure_legal_p(list));
    assert_exit(SKIP_LIST_MAX_LVL > lv);

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
skip_linked_list_contains_ip(s_skip_linked_list_t *list,
    s_skip_linked_list_t *node)
{
    s_skip_linked_list_t *skip;

    assert_exit(skip_linked_list_structure_legal_p(list));
    assert_exit(skip_linked_list_structure_legal_p(node));

    skip = list;
    while (NULL != skip) {
        if (node == skip) {
            return true;
        }
        skip = skip->next;
    }

    return false;
}

bool
skip_linked_list_contains_p(s_skip_linked_list_t *list,
    s_skip_linked_list_t *node)
{
    if (!skip_linked_list_structure_legal_p(list)) {
        return false;
    } else if (!skip_linked_list_structure_legal_p(node)) {
        return false;
    } else {
        return skip_linked_list_contains_ip(list, node);
    }
}

static inline s_skip_linked_list_t *
skip_linked_list_insert_before_head(s_skip_linked_list_t *list,
    s_skip_linked_list_t *tgt)
{
    uint32 lv;

    assert_exit(skip_linked_list_structure_legal_p(list));
    assert_exit(skip_linked_list_structure_legal_p(tgt));
    assert_exit(tgt->key < list->key);

    lv = SKIP_LIST_MAX_LVL_IDX;

    while (SKIP_LIST_BOTTOM_IDX != lv) {
        tgt->layer[lv] = list->layer[lv];
        list->layer[lv] = NULL;
        lv--;
    }

    tgt->layer[SKIP_LIST_BOTTOM_IDX] = list;

    return tgt;
}

static inline s_skip_linked_list_t *
skip_linked_list_insert_i(s_skip_linked_list_t **list,
    s_skip_linked_list_t *tgt)
{
    uint32 lv;
    uint32 lmt;
    s_skip_linked_list_t *skip;
    s_skip_linked_list_t **head;
    s_skip_linked_list_t *prev_list[SKIP_LIST_MAX_LVL];

    assert_exit(!NULL_PTR_P(list));
    assert_exit(skip_linked_list_ordering_p(*list));
    assert_exit(skip_linked_list_structure_legal_p(tgt));
    assert_exit(skip_linked_list_structure_legal_p(*list));

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
                if (SKIP_LIST_BOTTOM_IDX != lv) {
                    lv--;
                } else {
                    lmt = random_uint32_with_limit(SKIP_LIST_MAX_LVL);
                    skip_linked_list_insert_update_with_lv(tgt, prev_list, lmt);
                    break;
                }
            } else {
                skip = skip->layer[lv];
            }
        }
    }

    assert_exit(skip_linked_list_ordering_p(*list));
    return tgt;
}

s_skip_linked_list_t *
skip_linked_list_insert(s_skip_linked_list_t **list,
    s_skip_linked_list_t *tgt)
{
    if (NULL_PTR_P(list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(*list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(tgt)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_insert_i(list, tgt);
    }
}

static inline void
skip_linked_list_insert_update_with_lv(s_skip_linked_list_t *tgt,
    s_skip_linked_list_t **prev_list, uint32 lv)
{
    assert_exit(!NULL_PTR_P(prev_list));
    assert_exit(skip_linked_list_structure_legal_p(tgt));
    assert_exit(SKIP_LIST_MAX_LVL > lv);

    do {
        tgt->layer[lv] = prev_list[lv]->layer[lv];
        prev_list[lv]->layer[lv] = tgt;
    } while (0 != lv--);
}

s_skip_linked_list_t *
skip_linked_list_node_by_index(s_skip_linked_list_t *list, uint32 index)
{
    uint32 len;
    s_skip_linked_list_t *skip;

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
skip_linked_list_node_clean(s_skip_linked_list_t *list)
{
    uint32 lv;

    assert_exit(skip_linked_list_structure_legal_p(list));

    lv = SKIP_LIST_BOTTOM_IDX;

    while (NULL != list->layer[lv] && lv < SKIP_LIST_MAX_LVL) {
        list->layer[lv++] = NULL;
    }
}

static inline void
skip_linked_list_remove_head(s_skip_linked_list_t *list)
{
    uint32 lv;
    s_skip_linked_list_t *next;

    assert_exit(skip_linked_list_structure_legal_p(list));

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

static inline void
skip_linked_list_remove_on_level(s_skip_linked_list_t *list,
    s_skip_linked_list_t *removed, uint32 level)
{
    s_skip_linked_list_t *skip;

    assert_exit(SKIP_LIST_MAX_LVL > level);
    assert_exit(skip_linked_list_structure_legal_p(list));
    assert_exit(skip_linked_list_structure_legal_p(removed));

    do {
        skip = list;
        assert_exit(skip_linked_list_exist_on_level(list, removed, level));

        while (skip->layer[level] != removed) {
            skip = skip->layer[level];
        }

        skip->layer[level] = removed->layer[level];
        level--;
    } while (SKIP_LIST_MAX_LVL > level);

    skip_linked_list_node_clean(removed);
}

static inline s_skip_linked_list_t *
skip_linked_list_remove_i(s_skip_linked_list_t **list,
    s_skip_linked_list_t *tgt)
{
    uint32 lv;
    s_skip_linked_list_t *node;
    s_skip_linked_list_t *head;
    s_skip_linked_list_t *removed;

    assert_exit(!NULL_PTR_P(list));
    assert_exit(skip_linked_list_ordering_p(*list));
    assert_exit(skip_linked_list_structure_legal_p(tgt));
    assert_exit(skip_linked_list_structure_legal_p(*list));

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

        assert_exit(skip_linked_list_ordering_p(head));
    }

    return removed;
}

s_skip_linked_list_t *
skip_linked_list_remove(s_skip_linked_list_t **list,
    s_skip_linked_list_t *tgt)
{
    if (NULL_PTR_P(list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(*list)) {
        return PTR_INVALID;
    } else if (!skip_linked_list_structure_legal_p(tgt)) {
        return PTR_INVALID;
    } else {
        return skip_linked_list_remove_i(list, tgt);
    }
}

void
skip_linked_list_iterate(s_skip_linked_list_t *list,
    void (*handler)(void *))
{
    s_skip_linked_list_t *skip;

    if (!NULL_PTR_P(handler)
        && skip_linked_list_structure_legal_p(list)) {
        skip = list;
        while(skip) {
            (*handler)(skip);
            skip = skip->next;
        }
    }
}

s_skip_linked_list_t *
skip_linked_list_merge(s_skip_linked_list_t *m, s_skip_linked_list_t *n)
{
    s_skip_linked_list_t *skip;
    s_skip_linked_list_t *inserted;

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
            inserted = skip_linked_list_create_with_key(skip->key);
            skip_linked_list_insert_i(&m, inserted);
            skip = skip->next;
        }

        return m;
    }
}

