#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void libds_log_print(enum log_level lvl, const char *msg);


/* doubly linked list, Circular. */
struct doubly_linked_list * doubly_linked_list_create(void);
struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
void doubly_linked_list_node_initial(struct doubly_linked_list *head, void *val, uint32 sid);
void doubly_linked_list_initial(struct doubly_linked_list *);
struct doubly_linked_list * doubly_linked_list_generate(uint32 *sid, uint32 size);
struct doubly_linked_list * doubly_linked_list_node_copy(struct doubly_linked_list *node);
void doubly_linked_list_node_append(struct doubly_linked_list *node, uint32 sid);
void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
void doubly_linked_list_node_insert_before(struct doubly_linked_list *cur, struct doubly_linked_list *node);
void doubly_linked_list_destroy(struct doubly_linked_list **head);
uint32 doubly_linked_list_length(struct doubly_linked_list *head);
struct doubly_linked_list * doubly_linked_list_node_by_index(struct doubly_linked_list *head, uint32 index);
void doubly_linked_list_node_exchange(struct doubly_linked_list *fir, struct doubly_linked_list *sec);
bool doubly_linked_list_contains_p(struct doubly_linked_list *tar, struct doubly_linked_list *node);
void doubly_linked_list_serialize(struct doubly_linked_list *head);
struct doubly_linked_list * doubly_linked_list_node_remove(struct doubly_linked_list *node);
void doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node);
void doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *));
struct doubly_linked_list * doubly_linked_list_join(struct doubly_linked_list *m, struct doubly_linked_list *n);
/* END of doubly linked list, Circular. */


/* single linked list, Circular. */
struct single_linked_list * single_linked_list_create(void);
struct single_linked_list * single_linked_list_node_create(void *val, uint32 sid);
void single_linked_list_initial(struct single_linked_list *head);
void single_linked_list_node_initial(struct single_linked_list *head, void *val, uint32 sid);
struct single_linked_list * single_linked_list_generate(uint32 *sid, uint32 size);
void single_linked_list_node_append(struct single_linked_list *node, uint32 value);
struct single_linked_list * single_linked_list_node_copy(struct single_linked_list *node);
struct single_linked_list * single_linked_list_node_previous(struct single_linked_list *node);
void single_linked_list_node_insert_after(struct single_linked_list *cur, struct single_linked_list *node);
void single_linked_list_node_insert_before(struct single_linked_list *cur, struct single_linked_list *node);
void single_linked_list_destroy(struct single_linked_list **head);
uint32 single_linked_list_length(struct single_linked_list *head);
struct single_linked_list * single_linked_list_node_by_index(struct single_linked_list *head, uint32 index);
void single_linked_list_node_exchange(struct single_linked_list *fir, struct single_linked_list *sec);
bool single_linked_list_contains_p(struct single_linked_list *tar, struct single_linked_list *node);
void single_linked_list_serialize(struct single_linked_list *head);
struct single_linked_list * single_linked_list_node_remove(struct single_linked_list *node);
void single_linked_list_node_lazy_remove(struct single_linked_list *node);
void single_linked_list_iterate(struct single_linked_list *head, void (*handler)(void *));
struct single_linked_list * single_linked_list_join(struct single_linked_list *m, struct single_linked_list *n);

#endif
