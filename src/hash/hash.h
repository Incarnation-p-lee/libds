#ifndef HAVE_HASH_H
#define HAVE_HASH_H

extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val);
extern void doubly_linked_list_remove(struct doubly_linked_list **node);

#endif
