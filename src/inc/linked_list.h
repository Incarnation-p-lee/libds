#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);

/* doubly linked list, Circular. */
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
void
dlinked_list_iterate(struct doubly_linked_list *head,
    void (*handler)(struct doubly_linked_list *));


/* single linked list, Circular. */
struct single_linked_list *
slinked_list_initial(void);
struct single_linked_list *
slinked_list_generate(int *val, int size);
void
slinked_list_append_node(struct single_linked_list *node, int value);
struct single_linked_list *
slinked_list_next_node(struct single_linked_list *node);
struct single_linked_list *
slinked_list_previous_node(struct single_linked_list *node);
void
slinked_list_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node);
void
slinked_list_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node);
void
slinked_list_destroy(struct single_linked_list **head);
int
slinked_list_length(struct single_linked_list *head);
struct single_linked_list *
slinked_list_get_node_by_index(struct single_linked_list *head, int index);
void
slinked_list_print(FILE *fd, char *msg, struct single_linked_list *head);
void
slinked_list_exchange_node(struct single_linked_list *fir,
    struct single_linked_list *sec);
bool
slinked_list_is_contains(struct single_linked_list *tar,
    struct single_linked_list *node);
void
slinked_list_serialize(struct single_linked_list *head);
struct single_linked_list *
slinked_list_remove_node(struct single_linked_list *node);
void
slinked_list_lazy_remove_node(struct single_linked_list *node);
void
slinked_list_iterate(struct single_linked_list *head,
    void (*handler)(struct single_linked_list *));

#endif
