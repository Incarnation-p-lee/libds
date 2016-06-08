#ifndef HAVE_TREE_H
#define HAVE_TREE_H

#define TREE_NICE_PLUS_LMT    0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT   (-TREE_NICE_PLUS_LMT - 1)

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false

extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *));
extern void doubly_linked_list_next_set(struct doubly_linked_list *list, struct doubly_linked_list *next);
extern void doubly_linked_list_previous_set(struct doubly_linked_list *list, struct doubly_linked_list *previous);
extern void doubly_linked_list_val_set(struct doubly_linked_list *list, void *val);

#endif

