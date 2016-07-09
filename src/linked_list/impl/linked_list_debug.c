static inline bool
skip_linked_list_ordering_p(s_skip_linked_list_t *list)
{
    assert(skip_linked_list_structure_legal_ip(list));

    while (NULL != list->next) {
        if (list->key > list->next->key) {
            return false;
        }
        list = list->next;
    }

    return true;
}

static inline bool
skip_linked_list_exist_on_level(s_skip_linked_list_t *list,
    s_skip_linked_list_t *node, uint32 level)
{
    s_skip_linked_list_t *iter;

    assert(SKIP_LIST_MAX_LVL > level);
    assert(skip_linked_list_structure_legal_ip(list));
    assert(skip_linked_list_structure_legal_ip(node));

    iter = list;
    while (NULL != iter) {
        if (iter == node) {
            return true;
        }
        iter = iter->layer[level];
    }

    return false;
}

