#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

extern bool array_stack_full_p(struct array_stack *stack);
extern bool array_stack_empty_p(struct array_stack *stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_resize(struct array_stack *stack, uint32 dim);
extern void array_stack_push(struct array_stack *stack, void *member);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_insert_before(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern void * array_stack_pop(struct array_stack *stack);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_rest(struct array_stack *stack);
extern struct array_stack * array_stack_create(void);
extern struct doubly_linked_list * doubly_linked_list_remove(struct doubly_linked_list **node);
extern bool array_stack_structure_legal_p(s_array_stack_t *stack);
extern void * array_stack_top(s_array_stack_t *stack);
extern bool doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list);

#if defined DEBUG
    #define ARRAY_QUEUE_LEGAL_P(queue)   array_queue_structure_legal_ip(queue)
    #define ARRAY_QUEUE_ILLEGAL_P(queue) array_queue_structure_illegal_ip(queue)
#else
    #define ARRAY_QUEUE_LEGAL_P(queue)   (NON_NULL_PTR_P(queue))
    #define ARRAY_QUEUE_ILLEGAL_P(queue) (NULL_PTR_P(queue))
#endif

#endif

