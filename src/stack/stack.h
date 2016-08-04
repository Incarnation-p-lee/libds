#ifndef HAVE_STACK_H
#define HAVE_STACK_H

extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_remove(struct doubly_linked_list **node);
extern bool doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list);

#endif

