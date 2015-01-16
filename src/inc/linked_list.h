#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void libds_log_print(enum log_level lvl, const char *msg);

/* doubly linked list, Circular. */
struct doubly_linked_list * dlinked_list_create(void);
struct doubly_linked_list * dlinked_list_node_create(void *val, uint32 id);
void dlinked_list_node_initial(struct doubly_linked_list *head, void *val, uint32 id);
void dlinked_list_initial(struct doubly_linked_list *);
struct doubly_linked_list * dlinked_list_generate(uint32 *id, uint32 size);
void dlinked_list_node_set_val(struct doubly_linked_list *node, void *val);
void * dlinked_list_node_get_val(struct doubly_linked_list *node);
void dlinked_list_node_append(struct doubly_linked_list *node, uint32 id);
struct doubly_linked_list * dlinked_list_node_next(struct doubly_linked_list *node);
struct doubly_linked_list * dlinked_list_node_previous(struct doubly_linked_list *node);
void dlinked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
void dlinked_list_node_insert_before(struct doubly_linked_list *cur, struct doubly_linked_list *node);
void dlinked_list_destroy(struct doubly_linked_list **head);
uint32 dlinked_list_length(struct doubly_linked_list *head);
struct doubly_linked_list * dlinked_list_node_get_by_index(struct doubly_linked_list *head, uint32 index);
void dlinked_list_print(FILE *fd, char *msg, struct doubly_linked_list *head);
void dlinked_list_node_exchange(struct doubly_linked_list *fir, struct doubly_linked_list *sec);
bool dlinked_list_contains_p(struct doubly_linked_list *tar, struct doubly_linked_list *node);
void dlinked_list_serialize(struct doubly_linked_list *head);
struct doubly_linked_list * dlinked_list_node_remove(struct doubly_linked_list *node);
void dlinked_list_node_lazy_remove(struct doubly_linked_list *node);
void dlinked_list_iterate(struct doubly_linked_list *head, void (*handler)(struct doubly_linked_list *));


/* single linked list, Circular. */
struct single_linked_list *
slinked_list_create(void);
void
slinked_list_initial(struct single_linked_list *);
struct single_linked_list *
slinked_list_generate(sint32 *val, uint32 size);
void
slinked_list_append_node(struct single_linked_list *node, uint32 value);
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
uint32
slinked_list_length(struct single_linked_list *head);
struct single_linked_list *
slinked_list_get_node_by_index(struct single_linked_list *head, uint32 index);
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
