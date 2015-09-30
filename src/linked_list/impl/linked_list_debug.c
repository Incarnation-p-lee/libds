#if defined DEBUG

static inline bool
skip_linked_list_ordering_p(struct skip_linked_list *list)
{
    assert(NULL != list);

    while (NULL != list->next) {
        if (list->key >= list->next->key) {
            return false;
        }
        list = list->next;
    }

    return true;
}

static inline bool
skip_linked_list_node_exist_on_level(struct skip_linked_list *list,
    struct skip_linked_list *node, uint32 level)
{
    struct skip_linked_list *iter;

    assert(NULL != node);
    assert(NULL != list);
    assert(SKIP_LIST_MAX_LVL > level);

    iter = list;
    while (NULL != iter) {
        if (iter == node) {
            return true;
        }
        iter = iter->layer[level];
    }

    return false;
}

#endif
