/*
 * Init single linked list data structure.
 * _RETURN_ single linked list node: (0, NULL).
 *   If no memory available, it never return, export an error and exit.
 */
struct single_linked_list *
slinked_list_create(void)
{
    struct single_linked_list *head;

    head = malloc_ds(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        slinked_list_initial(head);
    }

    return head;
}

/*
 * Init single node linked list.
 *   If NULL _ARGV_, nothing will be done.
 */
void
slinked_list_initial(struct single_linked_list *head)
{
    if (head) {
        head->index = 0u;
        head->next = head;
    }

    return;
}

/*
 * Generate one new single linked list data structure from int array.
 * _RETURN_ the head node of single linked list node.
 * _ARGV_ the int array, if invaild array, _RETURN_ NULL.
 */
struct single_linked_list *
slinked_list_generate(sint32 *val, uint32 size)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    register sint32 *iterator;

    head = NULL;
    if (val && size > 0) {
        iterator = val;
        node = slinked_list_create();
        node->index = (uint32)(*iterator++);
        head = node;

        while (iterator < val + size) {
            slinked_list_append_node(node, *iterator++);
            node = node->next;
        }
    }

    return head;
}

/*
 * Append one single linked list node to the node your specified.
 * _ARGV_ node, if NULL, nothing will be done.
 *        value, the value for the append node. 
 */
void
slinked_list_append_node(struct single_linked_list *node, uint32 value)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
        if (!node->next) {
            pr_log_warn("Uninitialized or destroyed single linked list node.\n");
        } else {
            next = slinked_list_create();
            next->index = value;
            slinked_list_insert_after(node, next);
            node->next = next;
        }
    }

    return;
}

/*
 * _RETURN_ the next node of linked list.
 *   If NULL _ARGV_, _RETURN_ NULL.
 *   If uninitialized or destroyed _ARGV_, _RETURN_ NULL.
 */
struct single_linked_list *
slinked_list_next_node(struct single_linked_list *node)
{
    struct single_linked_list *next;

    next = NULL;
    if (node && node->next) {
        next = node->next;
    } else if (!node->next) {
        pr_log_warn("Uninitialized or destroyed single linked list node.\n");
    }

    return next;
}

/*
 * _RETURN_ the previous node of linked list.
 *   If NULL _ARGV_, _RETURN_ NULL.
 *   If uninitialized or destroyed _ARGV_, _RETURN_ NULL.
 */
struct single_linked_list *
slinked_list_previous_node(struct single_linked_list *node)
{
    register struct single_linked_list *previous;

    previous = NULL;
    if (node && node->next) {
        previous = node;
        do {
            previous = previous->next;
        } while (previous->next != node);
    } else if (!node->next) {
        pr_log_warn("Uninitialized or destroyed single linked list node.\n");
    }

    return previous;
}

/*
 * Insert one existed node after another given node.
 * _ARGV_, cur current given node.
 *         node inserted node.
 *         If either of _ARGV_ is NULL, nothing will be done.
 */
void
slinked_list_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    if (cur && node)
    {
        node->next = cur->next;
        cur->next = node;
    }

    return;
}

/*
 * Insert one existed node before another given node.
 * _ARGV_, cur current given node.
 *         node inserted node.
 *         If either of _ARGV_ is NULL, nothing will be done.
 */
void
slinked_list_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (cur && node)
    {
        previous = slinked_list_previous_node(cur);
        if (previous) {
            slinked_list_insert_after(previous, node);
        }
    }

    return;
}

/*
 * Destroy the whole linked list, set head to NULL.
 *   If NULL _ARGV_, nothing will be done.
 */
void
slinked_list_destroy(struct single_linked_list **head)
{
    register struct single_linked_list *node;
    register struct single_linked_list *next;

    if (head && *head) {
        /*
         * We do not use the way like douby linked list used, because
         * lazy remove need to get previous node. This will result in
         * go through all node in list, which has heavy performance
         * drop in unit test.
         */
        next = (*head)->next;
        while (*head != (node = next)) {
            next = node->next;
            free_ds(node);
        }

        free_ds(node);
        *head = NULL;
    }

    return;
}

/*
 * _RETURN_ Length of given linked list.
 *   If NULL linked list, _RETURN_ 0.
 */
uint32
slinked_list_length(struct single_linked_list *head)
{
    uint32 length;
    register struct single_linked_list *node;

    length = 0;
    if (head) {
        node = head;
        do {
            length++;
            node = node->next;
        } while (node != head);
    }

    return length;
}

/*
 * _RETURN_ the node of index by given head node.
 *   If invalid _ARGV_, nothing will done, _RETURN_ NULL.
 */
struct single_linked_list *
slinked_list_get_node_by_index(struct single_linked_list *head, uint32 index)
{
    register struct single_linked_list *node;

    node = NULL;
    if (head) {
        if (index <= slinked_list_length(head)) {
            node = head;
            while (index > 0) {
                node = node->next;
                index--;
            }
        }
    }

    return node;
}

/*
 * Print single linked list
 *   If invalid head, nothing will be done.
 */
void
slinked_list_print(FILE *fd, char *msg, struct single_linked_list *head)
{
    register struct single_linked_list *iterator;
    char *default_msg = "Default single linked list";

    if (head) {
        fprintf(fd, "[%s]:\n", msg);
        if (!msg) {
            msg = default_msg;
        }

        iterator = head;
        do {
            fprintf(fd, "%d ->\n", iterator->index);
            iterator = iterator->next;
        } while (iterator != head);
    }
    fprintf(fd, "NULL\n");

    return;
}

/*
 * Exchange two node of linked list.
 *   If either _ARGV_ is NULL, nothing will be done.
 *   If the same node, nothing will be done.
 */
void
slinked_list_exchange_node(struct single_linked_list *fir,
    struct single_linked_list *sec)
{
    struct single_linked_list *prev_fir;
    struct single_linked_list *prev_sec;

    if (fir && sec) {
        if (slinked_list_is_contains(fir, sec) && (fir != sec)) {
            prev_fir = slinked_list_previous_node(fir);
            prev_sec = slinked_list_previous_node(sec);

            if (prev_fir && prev_sec) {
                slinked_list_lazy_remove_node(fir);
                slinked_list_lazy_remove_node(sec);
                slinked_list_insert_after(prev_fir, sec);
                slinked_list_insert_after(prev_sec, fir);
            }
        }
    }

    return;
}

/*
 * _RETURN_ true if _ARGV_ node in the list of _ARGV_ tar, else false.
 *   If either of _ARGV_ is NULL, return false.
 */
bool
slinked_list_is_contains(struct single_linked_list *tar,
    struct single_linked_list *node)
{
    register struct single_linked_list *iter;
    bool contains;

    contains = false;
    if (tar && node) {
        iter = tar;
        do {
            if (iter == node) {
                contains = true;
                break;
            }
            iter = iter->next;
        } while (iter != tar);
    }

    return contains;
}

/*
 * Serialize the given linked list.
 *   If NULL, nothing will be done.
 */
void
slinked_list_serialize(struct single_linked_list *head)
{
    struct single_linked_list *node;
    uint32 index;

    if (head) {
        index = 0;
        node = head;
        do {
            node->index = index++;
            node = node->next;
        } while (node != head);
    }

    return;
}

/*
 * Remove the given node.
 * _RETURN_ the next node.
 *   If only one node of linked list, _RETURN_ NULL.
 *   If NULL _ARGV_, _RETURN_ NULL
 */
struct single_linked_list *
slinked_list_remove_node(struct single_linked_list *node)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
         slinked_list_lazy_remove_node(node);
        if (node->next != node) {
            next = node->next;
        }
        free_ds(node);
    }

    return next;
}

/*
 * Remove the given node without free the memory.
 *   If only one node of linked list, nothing will be done.
 */
void
slinked_list_lazy_remove_node(struct single_linked_list *node)
{
    struct single_linked_list *previous;

    if (node) {
        previous = slinked_list_previous_node(node);
        if (previous) {
            previous->next = node->next;
        }
    }

    return;
}

/*
 * Iterate each node by given function handler.
 *   If NULL _ARGV_, nothing will be done.
 */
void
slinked_list_iterate(struct single_linked_list *head,
    void (*handler)(struct single_linked_list *))
{
    register struct single_linked_list *node;

    if (head && handler) {
        node = head;
        do {
            (*handler)(node);
            node = node->next;
        } while (node != head);
    }

    return;
}
