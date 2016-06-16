static inline struct single_linked_list *
single_linked_list_remove_internal_optimize(
    struct single_linked_list **node)
{
    struct single_linked_list *next;
    struct single_linked_list *removed;
    struct single_linked_list copy;

    dp_assert(NULL != node);
    dp_assert(NULL != *node);

    removed = *node;
    next = (*node)->next;

    if (*node == next) {
        *node = NULL;
        return removed;
    } else {
        /*
         * exchange removed node and its next node
         */
        copy.sid = removed->sid;
        copy.val = removed->val;

        removed->sid = next->sid;
        removed->val = next->val;

        next->sid = copy.sid;
        next->val = copy.val;

        removed->next = next->next;
        next->next = next;

        return next;
    }
}

