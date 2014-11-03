#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

struct doubly_linked_list *
dlinked_list_initial(void);
struct doubly_linked_list *
dlinked_list_generate(int *val, int size);
void
dlinked_list_append_node(struct doubly_linked_list *node, int value);
struct doubly_linked_list *
dlinked_list_next_node(struct doubly_linked_list *node);
struct doubly_linked_list *
dlinked_list_previous_node(struct doubly_linked_list *node);
void
dlinked_list_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
void
dlinked_list_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
void
dlinked_list_destroy(struct doubly_linked_list **head);
int
dlinked_list_length(struct doubly_linked_list *head);
struct doubly_linked_list *
dlinked_list_get_node_by_index(struct doubly_linked_list *head, int index);
void
dlinked_list_print(FILE *fd, char *msg, struct doubly_linked_list *head);
void
dlinked_list_exchange_node(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec);
bool
dlinked_list_is_contains(struct doubly_linked_list *tar,
    struct doubly_linked_list *node);
void
dlinked_list_serialize(struct doubly_linked_list *head);
struct doubly_linked_list *
dlinked_list_remove_node(struct doubly_linked_list *node);
void
dlinked_list_lazy_remove_node(struct doubly_linked_list *node);

#endif
