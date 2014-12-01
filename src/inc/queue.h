#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

#define DEFAULT_QUEUE_SPACE_SIZE   128
#define EXPAND_QUEUE_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
#endif


extern void
libds_log_print(enum log_level lvl, const char *msg);

extern void
array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void
array_stack_cleanup(struct array_stack *stack);
extern bool
array_stack_is_full(struct array_stack *stack);
extern bool
array_stack_is_empty(struct array_stack *stack);
extern struct array_stack *
array_stack_create(void);
extern uint32
array_stack_capacity(struct array_stack *stack);
extern void
array_stack_destroy(struct array_stack **stack);
extern void
array_stack_expand_space(struct array_stack *stack, uint32 extra);
extern uint32
array_stack_rest_space(struct array_stack *stack);
extern void
array_stack_push(struct array_stack *stack, void *member);
extern void *
array_stack_pop(struct array_stack *stack);


/* ARRAY STACK */
struct array_queue *
array_queue_create(void);
void
array_queue_destroy(struct array_queue **queue);
void
array_queue_expand_space(struct array_queue *queue, uint32 extra);
uint32
array_queue_capacity(struct array_queue *queue);
uint32
array_queue_rest_space(struct array_queue *queue);
bool
array_queue_is_full(struct array_queue *queue);
bool
array_queue_is_empty(struct array_queue *queue);
void
array_queue_enter(struct array_queue *queue, void *member);
void *
array_queue_leave(struct array_queue *queue);
void
array_queue_cleanup(struct array_queue *queue);
void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
/* END OF ARRAY STACK */

/* STACKED STACK */
struct stacked_queue *
stacked_queue_create(void);
void
stacked_queue_destroy(struct stacked_queue **queue);
void
stacked_queue_expand_space(struct stacked_queue *queue, uint32 extra);
uint32
stacked_queue_capacity(struct stacked_queue *queue);
uint32
stacked_queue_rest_space(struct stacked_queue *queue);
bool
stacked_queue_is_full(struct stacked_queue *queue);
bool
stacked_queue_is_empty(struct stacked_queue *queue);
void
stacked_queue_enter(struct stacked_queue *queue, void *member);
void *
stacked_queue_leave(struct stacked_queue *queue);
void
stacked_queue_cleanup(struct stacked_queue *queue);
void
stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));

static inline void
stacked_queue_dump_stack(struct array_stack *from,
    struct array_stack *to);
/* END OF STACKED STACK */

#endif