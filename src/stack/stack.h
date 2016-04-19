#ifndef HAVE_STACK_H
#define HAVE_STACK_H

#define DEFAULT_STACK_SPACE_SIZE   1024
#define EXPAND_STACK_SPACE_MIN     32

extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_insert_ptr_after(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_remove(struct doubly_linked_list **node);

#endif

