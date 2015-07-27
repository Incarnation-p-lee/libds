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

#endif
