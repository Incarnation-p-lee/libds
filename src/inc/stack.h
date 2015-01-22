#ifndef HAVE_STACK_H
#define HAVE_STACK_H

#define DEFAULT_STACK_SPACE_SIZE   128
#define EXPAND_STACK_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void libds_log_print(enum log_level lvl, const char *msg);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list * doubly_linked_list_node_next(struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_previous(struct doubly_linked_list *node);
extern void doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);


/* ARRAY STACK */
struct array_stack * array_stack_create(void);
void array_stack_destroy(struct array_stack **stack);
void array_stack_space_expand(struct array_stack *stack, uint32 extra);
bool array_stack_full_p(struct array_stack *stack);
uint32 array_stack_capacity(struct array_stack *stack);
uint32 array_stack_space_rest(struct array_stack *stack);
void array_stack_push(struct array_stack *stack, void *member);
void * array_stack_pop(struct array_stack *stack);
bool array_stack_empty_p(struct array_stack *stack);
void array_stack_cleanup(struct array_stack *stack);
void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
/* END OF ARRAY STACK */

/* LINKED STACK */
struct linked_stack * linked_stack_create(void);
void linked_stack_destroy(struct linked_stack **stack);
void linked_stack_space_expand(struct linked_stack *stack, uint32 dim);
bool linked_stack_full_p(struct linked_stack *stack);
uint32 linked_stack_space_rest(struct linked_stack *stack);
void linked_stack_push(struct linked_stack *stack, void *member);
void * linked_stack_pop(struct linked_stack *stack);
bool linked_stack_empty_p(struct linked_stack *stack);
void linked_stack_cleanup(struct linked_stack *stack);
void linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
uint32 linked_stack_capacity(struct linked_stack *stack);

static inline struct linked_stack_space * linked_stack_space_next_node(struct linked_stack_space *node);
static inline struct linked_stack_space * linked_stack_space_previous_node(struct linked_stack_space *node);
static inline struct linked_stack_space * linked_stack_space_remove_node(struct linked_stack_space *node);
static inline void linked_stack_space_iterate_node(struct linked_stack_space *node, void (*handler)(void *));
static inline uint32 linked_stack_space_node_capacity(struct linked_stack_space *node);
static inline uint32 linked_stack_space_node_space_rest(struct linked_stack_space *node);
/* END OF LINKED STACK */

#endif
