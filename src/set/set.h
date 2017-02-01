#ifndef HAVE_DEFINED_SET_H
#define HAVE_DEFINED_SET_H

extern s_array_stack_t * array_stack_create(void);
extern void array_stack_push(s_array_stack_t *stack, void *member);
extern void * array_stack_pop(s_array_stack_t *stack);
extern bool array_stack_empty_p(s_array_stack_t *stack);
extern void array_stack_destroy(s_array_stack_t **stack);
extern bool array_stack_structure_legal_p(s_array_stack_t *stack);

#endif

