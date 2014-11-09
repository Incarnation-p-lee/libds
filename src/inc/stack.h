#ifndef HAVE_STACK_H
#define HAVE_STACK_H

#define DEFAULT_STACK_SPACE_SIZE   128
#define EXPAND_STACK_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);

struct array_stack *
array_stack_create(void);
void
array_stack_destroy(struct array_stack **stack);
void
array_stack_expand_space(struct array_stack *stack, unsigned extra);
bool
array_stack_is_full(struct array_stack *stack);
unsigned
array_stack_rest_space(struct array_stack *stack);
void
array_stack_push(struct array_stack *stack, void *member);
void *
array_stack_pop(struct array_stack *stack);
bool
array_stack_is_empty(struct array_stack *stack);
void
array_stack_cleanup(struct array_stack *stack);
void
array_stack_iterate(struct array_stack *stack, void (*handler)(void *));


#endif
