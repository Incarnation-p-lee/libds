#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

#define DEFAULT_QUEUE_SPACE_SIZE   1024
#define EXPAND_QUEUE_SPACE_MIN     32

extern bool complain_null_pointer_p(void *ptr);
extern bool array_stack_full_p(struct array_stack *stack);
extern bool array_stack_empty_p(struct array_stack *stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_space_expand(struct array_stack *stack, uint32 extra);
extern void array_stack_push(struct array_stack *stack, void *member);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_node_insert_before_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void * array_stack_pop(struct array_stack *stack);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_space_rest(struct array_stack *stack);
extern struct array_stack * array_stack_create(void);
extern struct doubly_linked_list * doubly_linked_list_node_remove(struct doubly_linked_list **node);

#endif
