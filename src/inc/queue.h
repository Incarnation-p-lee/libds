#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

#define DEFAULT_QUEUE_SPACE_SIZE   128
#define EXPAND_QUEUE_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
#endif


extern void libds_log_print(enum log_level lvl, const char *msg);

extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void array_stack_cleanup(struct array_stack *stack);
extern bool array_stack_full_p(struct array_stack *stack);
extern bool array_stack_empty_p(struct array_stack *stack);
extern struct array_stack * array_stack_create(void);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_space_expand(struct array_stack *stack, uint32 extra);
extern uint32 array_stack_space_rest(struct array_stack *stack);
extern void array_stack_push(struct array_stack *stack, void *member);
extern void * array_stack_pop(struct array_stack *stack);

extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_node_insert_before(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node);


/* ARRAY STACK */
struct array_queue * array_queue_create(void);
void array_queue_destroy(struct array_queue **queue);
void array_queue_space_expand(struct array_queue *queue, uint32 extra);
uint32 array_queue_capacity(struct array_queue *queue);
uint32 array_queue_space_rest(struct array_queue *queue);
bool array_queue_full_p(struct array_queue *queue);
bool array_queue_empty_p(struct array_queue *queue);
void array_queue_enter(struct array_queue *queue, void *member);
void * array_queue_leave(struct array_queue *queue);
void array_queue_cleanup(struct array_queue *queue);
void array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
/* END OF ARRAY STACK */

/* STACKED QUEUE */
struct stacked_queue * stacked_queue_create(void);
void stacked_queue_destroy(struct stacked_queue **queue);
void stacked_queue_space_expand(struct stacked_queue *queue, uint32 extra);
uint32 stacked_queue_capacity(struct stacked_queue *queue);
uint32 stacked_queue_space_rest(struct stacked_queue *queue);
bool stacked_queue_full_p(struct stacked_queue *queue);
bool stacked_queue_empty_p(struct stacked_queue *queue);
void stacked_queue_enter(struct stacked_queue *queue, void *member);
void * stacked_queue_leave(struct stacked_queue *queue);
void stacked_queue_cleanup(struct stacked_queue *queue);
void stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));

static inline void stacked_queue_stack_dump(struct array_stack *from, struct array_stack *to);
/* END OF STACKED QUEUE */


/* DOUBLY END QUEUE */
struct doubly_end_queue * doubly_end_queue_create(void);
void doubly_end_queue_destroy(struct doubly_end_queue **queue);
uint32 doubly_end_queue_length(struct doubly_end_queue *queue);
bool doubly_end_queue_empty_p(struct doubly_end_queue *queue);
void doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
void doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
void * doubly_end_queue_head_leave(struct doubly_end_queue *queue);
void * doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
void doubly_end_queue_cleanup(struct doubly_end_queue *queue);
void doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));

static inline void doubly_end_queue_last_node_clean(struct doubly_end_queue *queue);
static inline struct doubly_end_queue_list * doubly_end_queue_list_next(struct doubly_end_queue_list *node);
static inline struct doubly_end_queue_list * doubly_end_queue_list_previous(struct doubly_end_queue_list *node);
static inline struct doubly_end_queue_list * doubly_end_queue_list_offset_reflect(struct doubly_linked_list *link);
/* END OF DOUBLY END QUEUE */
#endif
