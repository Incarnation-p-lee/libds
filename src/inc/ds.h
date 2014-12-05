#ifndef HAVE_DATA_STRUCTURE_INCLUDE_H
#define HAVE_DATA_STRUCTURE_INCLUDE_H

/* BEGIN of ./src/inc/types.h */
#ifndef HAVE_TYPES_H
#define HAVE_TYPES_H

enum log_level {
  INFO,
  WARN,
  DBUG,
  ERRR,
};

typedef signed char   sint8;
typedef unsigned char uint8;

#if defined X86
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long long   sint64;
    typedef unsigned long long uint64;
#endif

#if defined X86_64
    typedef signed short   sint16;
    typedef unsigned short uint16;
    typedef signed int     sint32;
    typedef unsigned int   uint32;
    typedef signed long    sint64;
    typedef unsigned long  uint64;
#endif

typedef unsigned int bool;

#endif
/* END of ./src/inc/types.h */

/* BEGIN of ./src/inc/data_structure_types.h */
#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H

/*
 *   Implement the unify single_linked_list interface
 * All other linked list will involved this structure
 * for linker, such as
 *   struct A {
 *     int;
 *     struct single_linked_list next;
 *   };
 *   Then, we can only care about this linked list opertion
 * for all other linked list.
 *   Both single_linked_list and doubly_linked_list are
 * _CIRCULAR_ linked list.
 */
struct single_linked_list {
    uint32                    index;
    void                      *val;
    struct single_linked_list *next;
};

struct doubly_linked_list {
    uint32                    index;
    void                      *val;
    struct doubly_linked_list *next;
    struct doubly_linked_list *previous;
};

/*
 * array stack space
 */
struct array_stack_space {
    uint32 dim;
    void   **sp;
    void   **bp;
};

/*
 * array stack
 */
struct array_stack {
    uint32                   sid;
    struct array_stack_space space;
};

/*
 * linked stack space
 */
struct linked_stack_space {
    struct array_stack_space  space;
    struct doubly_linked_list link;
};

/*
 * linked stack
 */
struct linked_stack {
    uint32                    sid;
    struct linked_stack_space *base;
    struct linked_stack_space *top;
};

/*
 * array queue space
 *    front -> first node
 *    rear  -> next address of read node
 */
struct array_queue_space {
    /* We need this rest field to tell empty or full if front equals rear */
    uint32 rest;
    uint32 dim;
    void   **front;
    void   **rear;
    void   **base;
};

/*
 * array queue
 */
struct array_queue {
    uint32                   sid;
    struct array_queue_space space;
};

/*
 * stacked queue
 */
struct stacked_queue {
    uint32             sid;
    uint32             dim;
    struct array_stack *enter; /* enter stack */
    struct array_stack *leave; /* leave stack */
};

/*
 * doubly_end_queue_list
 */
struct doubly_end_queue_list {
    void                      *val;
    struct doubly_linked_list link;
};

/*
 * doubly end queue
 */
struct doubly_end_queue {
    uint32                       sid;
    struct doubly_end_queue_list *head;
    struct doubly_end_queue_list *tail;
};

#endif
/* END of ./src/inc/data_structure_types.h */

/* BEGIN of ./src/inc/log.h */
#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

extern void
libds_log_print(enum log_level lvl, const char *msg);

#endif
/* END of ./src/inc/log.h */

/* BEGIN of ./src/inc/defines.h */
#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H


#define true        1
#define false       0

#define SYM_2_STR(symbol)   (#symbol)
#define UNOFFSET_OF(ptr, type, mem) \
    (void *)((void *)ptr - (void *)(&((type *)0)->mem))

#ifdef DEBUG
    #define pr_log_info(msg)    libds_log_print(INFO, msg);
    #define pr_log_warn(msg)    libds_log_print(WARN, msg);
    #define pr_log_debug(msg)   libds_log_print(DBUG, msg);
#else
    #define pr_log_info(msg)
    #define pr_log_warn(msg)
    #define pr_log_debug(msg)
#endif

#ifdef DEBUG
    #define malloc_ds      malloc_wrap
    #define realloc_ds     realloc_wrap
    #define free_ds        free_wrap
#else
    #define malloc_ds      malloc
    #define realloc_ds     realloc
    #define free_ds        free
#endif

#define pr_log_err(msg)     \
    do {                             \
        libds_log_print(ERRR, msg); \
        exit(1);                     \
    } while (0);


#endif
/* END of ./src/inc/defines.h */

/* BEGIN of ./src/inc/linked_list.h */
#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);

/* doubly linked list, Circular. */
extern struct doubly_linked_list *
dlinked_list_create(void);
extern void
dlinked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list *
dlinked_list_generate(sint32 *val, uint32 size);
extern void
dlinked_list_append_node(struct doubly_linked_list *node, uint32 value);
extern struct doubly_linked_list *
dlinked_list_next_node(struct doubly_linked_list *node);
extern struct doubly_linked_list *
dlinked_list_previous_node(struct doubly_linked_list *node);
extern void
dlinked_list_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_destroy(struct doubly_linked_list **head);
extern uint32
dlinked_list_length(struct doubly_linked_list *head);
extern struct doubly_linked_list *
dlinked_list_get_node_by_index(struct doubly_linked_list *head, uint32 index);
extern void
dlinked_list_print(FILE *fd, char *msg, struct doubly_linked_list *head);
extern void
dlinked_list_exchange_node(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec);
extern bool
dlinked_list_is_contains(struct doubly_linked_list *tar,
    struct doubly_linked_list *node);
extern void
dlinked_list_serialize(struct doubly_linked_list *head);
extern struct doubly_linked_list *
dlinked_list_remove_node(struct doubly_linked_list *node);
extern void
dlinked_list_lazy_remove_node(struct doubly_linked_list *node);
extern void
dlinked_list_iterate(struct doubly_linked_list *head,
    void (*handler)(struct doubly_linked_list *));


/* single linked list, Circular. */
extern struct single_linked_list *
slinked_list_create(void);
extern void
slinked_list_initial(struct single_linked_list *);
extern struct single_linked_list *
slinked_list_generate(sint32 *val, uint32 size);
extern void
slinked_list_append_node(struct single_linked_list *node, uint32 value);
extern struct single_linked_list *
slinked_list_next_node(struct single_linked_list *node);
extern struct single_linked_list *
slinked_list_previous_node(struct single_linked_list *node);
extern void
slinked_list_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node);
extern void
slinked_list_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node);
extern void
slinked_list_destroy(struct single_linked_list **head);
extern uint32
slinked_list_length(struct single_linked_list *head);
extern struct single_linked_list *
slinked_list_get_node_by_index(struct single_linked_list *head, uint32 index);
extern void
slinked_list_print(FILE *fd, char *msg, struct single_linked_list *head);
extern void
slinked_list_exchange_node(struct single_linked_list *fir,
    struct single_linked_list *sec);
extern bool
slinked_list_is_contains(struct single_linked_list *tar,
    struct single_linked_list *node);
extern void
slinked_list_serialize(struct single_linked_list *head);
extern struct single_linked_list *
slinked_list_remove_node(struct single_linked_list *node);
extern void
slinked_list_lazy_remove_node(struct single_linked_list *node);
extern void
slinked_list_iterate(struct single_linked_list *head,
    void (*handler)(struct single_linked_list *));

#endif
/* END of ./src/inc/linked_list.h */

/* BEGIN of ./src/inc/queue.h */
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

extern void
dlinked_list_initial(struct doubly_linked_list *);
extern void
dlinked_list_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_lazy_remove_node(struct doubly_linked_list *node);


/* ARRAY STACK */
extern struct array_queue *
array_queue_create(void);
extern void
array_queue_destroy(struct array_queue **queue);
extern void
array_queue_expand_space(struct array_queue *queue, uint32 extra);
extern uint32
array_queue_capacity(struct array_queue *queue);
extern uint32
array_queue_rest_space(struct array_queue *queue);
extern bool
array_queue_is_full(struct array_queue *queue);
extern bool
array_queue_is_empty(struct array_queue *queue);
extern void
array_queue_enter(struct array_queue *queue, void *member);
extern void *
array_queue_leave(struct array_queue *queue);
extern void
array_queue_cleanup(struct array_queue *queue);
extern void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
/* END OF ARRAY STACK */

/* STACKED QUEUE */
extern struct stacked_queue *
stacked_queue_create(void);
extern void
stacked_queue_destroy(struct stacked_queue **queue);
extern void
stacked_queue_expand_space(struct stacked_queue *queue, uint32 extra);
extern uint32
stacked_queue_capacity(struct stacked_queue *queue);
extern uint32
stacked_queue_rest_space(struct stacked_queue *queue);
extern bool
stacked_queue_is_full(struct stacked_queue *queue);
extern bool
stacked_queue_is_empty(struct stacked_queue *queue);
extern void
stacked_queue_enter(struct stacked_queue *queue, void *member);
extern void *
stacked_queue_leave(struct stacked_queue *queue);
extern void
stacked_queue_cleanup(struct stacked_queue *queue);
extern void
stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));

/* END OF STACKED QUEUE */


/* DOUBLY END QUEUE */
extern struct doubly_end_queue *
doubly_end_queue_create(void);
extern void
doubly_end_queue_destroy(struct doubly_end_queue **queue);
extern uint32
doubly_end_queue_length(struct doubly_end_queue *queue);
extern bool
doubly_end_queue_is_empty(struct doubly_end_queue *queue);
extern void
doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
extern void
doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
extern void *
doubly_end_queue_head_leave(struct doubly_end_queue *queue);
extern void *
doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
extern void
doubly_end_queue_cleanup(struct doubly_end_queue *queue);
extern void
doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));
/* END OF DOUBLY END QUEUE */

#endif
/* END of ./src/inc/queue.h */

/* BEGIN of ./src/inc/stack.h */
#ifndef HAVE_STACK_H
#define HAVE_STACK_H

#define DEFAULT_STACK_SPACE_SIZE   128
#define EXPAND_STACK_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);
extern void
dlinked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list *
dlinked_list_next_node(struct doubly_linked_list *node);
extern struct doubly_linked_list *
dlinked_list_previous_node(struct doubly_linked_list *node);
extern void
dlinked_list_lazy_remove_node(struct doubly_linked_list *node);
extern void
dlinked_list_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);


/* ARRAY STACK */
extern struct array_stack *
array_stack_create(void);
extern void
array_stack_destroy(struct array_stack **stack);
extern void
array_stack_expand_space(struct array_stack *stack, uint32 extra);
extern bool
array_stack_is_full(struct array_stack *stack);
extern uint32
array_stack_capacity(struct array_stack *stack);
extern uint32
array_stack_rest_space(struct array_stack *stack);
extern void
array_stack_push(struct array_stack *stack, void *member);
extern void *
array_stack_pop(struct array_stack *stack);
extern bool
array_stack_is_empty(struct array_stack *stack);
extern void
array_stack_cleanup(struct array_stack *stack);
extern void
array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
/* END OF ARRAY STACK */

/* LINKED STACK */
extern struct linked_stack *
linked_stack_create(void);
extern void
linked_stack_destroy(struct linked_stack **stack);
extern void
linked_stack_expand_space(struct linked_stack *stack, uint32 dim);
extern bool
linked_stack_is_full(struct linked_stack *stack);
extern uint32
linked_stack_rest_space(struct linked_stack *stack);
extern void
linked_stack_push(struct linked_stack *stack, void *member);
extern void *
linked_stack_pop(struct linked_stack *stack);
extern bool
linked_stack_is_empty(struct linked_stack *stack);
extern void
linked_stack_cleanup(struct linked_stack *stack);
extern void
linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
extern uint32
linked_stack_capacity(struct linked_stack *stack);

/* END OF LINKED STACK */

#endif
/* END of ./src/inc/stack.h */
#endif