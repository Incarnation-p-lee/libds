#ifndef HAVE_HASH_H
#define HAVE_HASH_H

extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val);
extern s_doubly_linked_list_t * doubly_linked_list_remove(s_doubly_linked_list_t **list);
extern void doubly_linked_list_initial(s_doubly_linked_list_t *list);
extern bool doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list);

#endif
