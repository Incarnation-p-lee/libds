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
    uint32                    id;
    void                      *val;
    struct single_linked_list *next;
};

struct doubly_linked_list {
    uint32                    id;
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

/*
 * collision chain of the same nice value
 */
struct collision_chain {
    struct doubly_linked_list *link;
    sint64                    nice;
};

/*
 * binary search tree
 */
struct binary_search_tree {
    struct collision_chain chain;
    uint32                 height;  /* reserved for avl */
    /* root node has height 0, NULL node has height -1 */
    union {
        struct binary_search_tree *left;
        struct avl_tree           *avl_left;  /* reserved for avl */
    };
    union {
        struct binary_search_tree *right;
        struct avl_tree           *avl_right; /* reserved for avl */
    };
};

/*
 * avl tree
 */
struct avl_tree {
    struct binary_search_tree b_node;
};
#endif
/* END of ./src/inc/data_structure_types.h */

/* BEGIN of ./src/inc/log.h */
#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

extern void libds_log_print(enum log_level lvl, const char *msg);

#endif
/* END of ./src/inc/log.h */

/* BEGIN of ./src/inc/tree.h */
#ifndef HAVE_TREE_H
#define HAVE_TREE_H

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif


/* BINARY SEARCH TREE */
extern struct binary_search_tree * binary_search_tree_create(void);
extern struct binary_search_tree * binary_search_tree_node_create(void *val, sint64 nice);
extern void binary_search_tree_initial(struct binary_search_tree *root);
extern void binary_search_tree_node_initial(struct binary_search_tree *node, void *val, sint64 nice);
extern void binary_search_tree_destroy(struct binary_search_tree **root);
extern struct binary_search_tree * binary_search_tree_node_find(struct binary_search_tree *root, sint64 nice);
extern struct binary_search_tree * binary_search_tree_node_insert(struct binary_search_tree *root, struct binary_search_tree **node);
extern struct binary_search_tree * binary_search_tree_node_find_min(struct binary_search_tree *root);
extern struct binary_search_tree * binary_search_tree_node_find_max(struct binary_search_tree *root);
extern bool binary_search_tree_node_contain_p(struct binary_search_tree *root, struct binary_search_tree *node);
extern void binary_search_tree_node_remove(struct binary_search_tree **root, sint64 nice);
extern sint32 binary_search_tree_height(struct binary_search_tree *root);
extern void binary_search_tree_iterate(struct binary_search_tree *root, void (*handle)(void *), enum ITER_ORDER order);

/* END OF BINARY SEARCH TREE */


/* AVL TREE */
extern struct avl_tree * avl_tree_create(void);
extern struct avl_tree * avl_tree_node_create(void *val, sint64 nice);
extern void avl_tree_initial(struct avl_tree *root);
extern void avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice);
extern void avl_tree_destroy(struct avl_tree **root);
extern struct avl_tree * avl_tree_node_find(struct avl_tree *root, sint64 nice);
extern struct avl_tree * avl_tree_node_find_min(struct avl_tree *root);
extern struct avl_tree * avl_tree_node_find_max(struct avl_tree *root);
extern bool avl_tree_balanced_p(struct avl_tree *root);
extern sint32 avl_tree_height(struct avl_tree *root);
extern bool avl_tree_node_contain_p(struct avl_tree *root, struct avl_tree *node);
extern void avl_tree_iterate(struct avl_tree *root, void (*handle)(void *), enum ITER_ORDER order);

/* END OF AVL TREE */

#endif
/* END of ./src/inc/tree.h */

/* BEGIN of ./src/inc/defines.h */
#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H


#define true        1
#define false       0

#define SYM_2_STR(symbol)   (#symbol)

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

#define MAX_U(x, y) ((uint32)(x) > (uint32)(y) ? (uint32)(x) : (uint32)(y))
#define MAX_S(x, y) ((sint32)(x) > (sint32)(y) ? (sint32)(x) : (sint32)(y))


#endif
/* END of ./src/inc/defines.h */

/* BEGIN of ./src/inc/linked_list.h */
#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif


/* doubly linked list, Circular. */
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 id);
extern void doubly_linked_list_node_initial(struct doubly_linked_list *head, void *val, uint32 id);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list * doubly_linked_list_generate(uint32 *id, uint32 size);
extern void doubly_linked_list_node_set_val(struct doubly_linked_list *node, void *val);
extern void * doubly_linked_list_node_get_val(struct doubly_linked_list *node);
extern void doubly_linked_list_node_append(struct doubly_linked_list *node, uint32 id);
extern struct doubly_linked_list * doubly_linked_list_node_next(struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_previous(struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_before(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern uint32 doubly_linked_list_length(struct doubly_linked_list *head);
extern struct doubly_linked_list * doubly_linked_list_node_get_by_index(struct doubly_linked_list *head, uint32 index);
extern void doubly_linked_list_node_exchange(struct doubly_linked_list *fir, struct doubly_linked_list *sec);
extern bool doubly_linked_list_contains_p(struct doubly_linked_list *tar, struct doubly_linked_list *node);
extern void doubly_linked_list_serialize(struct doubly_linked_list *head);
extern struct doubly_linked_list * doubly_linked_list_node_remove(struct doubly_linked_list *node);
extern void doubly_linked_list_node_lazy_remove(struct doubly_linked_list *node);
extern void doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *));
extern struct doubly_linked_list * doubly_linked_list_join(struct doubly_linked_list *m, struct doubly_linked_list *n);


/* single linked list, Circular. */
extern struct single_linked_list * single_linked_list_create(void);
extern struct single_linked_list * single_linked_list_node_create(void *val, uint32 id);
extern void single_linked_list_initial(struct single_linked_list *head);
extern void single_linked_list_node_initial(struct single_linked_list *head, void *val, uint32 id);
extern struct single_linked_list * single_linked_list_generate(uint32 *id, uint32 size);
extern void single_linked_list_node_set_val(struct single_linked_list *node, void *val);
extern void * single_linked_list_node_get_val(struct single_linked_list *node);
extern void single_linked_list_node_append(struct single_linked_list *node, uint32 value);
extern struct single_linked_list * single_linked_list_node_next(struct single_linked_list *node);
extern struct single_linked_list * single_linked_list_node_previous(struct single_linked_list *node);
extern void single_linked_list_node_insert_after(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_node_insert_before(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_destroy(struct single_linked_list **head);
extern uint32 single_linked_list_length(struct single_linked_list *head);
extern struct single_linked_list * single_linked_list_node_get_by_index(struct single_linked_list *head, uint32 index);
extern void single_linked_list_node_exchange(struct single_linked_list *fir, struct single_linked_list *sec);
extern bool single_linked_list_contains_p(struct single_linked_list *tar, struct single_linked_list *node);
extern void single_linked_list_serialize(struct single_linked_list *head);
extern struct single_linked_list * single_linked_list_node_remove(struct single_linked_list *node);
extern void single_linked_list_node_lazy_remove(struct single_linked_list *node);
extern void single_linked_list_iterate(struct single_linked_list *head, void (*handler)(void *));
extern struct single_linked_list * single_linked_list_join(struct single_linked_list *m, struct single_linked_list *n);

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






/* ARRAY STACK */
extern struct array_queue * array_queue_create(void);
extern void array_queue_destroy(struct array_queue **queue);
extern void array_queue_space_expand(struct array_queue *queue, uint32 extra);
extern uint32 array_queue_capacity(struct array_queue *queue);
extern uint32 array_queue_space_rest(struct array_queue *queue);
extern bool array_queue_full_p(struct array_queue *queue);
extern bool array_queue_empty_p(struct array_queue *queue);
extern void array_queue_enter(struct array_queue *queue, void *member);
extern void * array_queue_leave(struct array_queue *queue);
extern void array_queue_cleanup(struct array_queue *queue);
extern void array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
/* END OF ARRAY STACK */

/* STACKED QUEUE */
extern struct stacked_queue * stacked_queue_create(void);
extern void stacked_queue_destroy(struct stacked_queue **queue);
extern void stacked_queue_space_expand(struct stacked_queue *queue, uint32 extra);
extern uint32 stacked_queue_capacity(struct stacked_queue *queue);
extern uint32 stacked_queue_space_rest(struct stacked_queue *queue);
extern bool stacked_queue_full_p(struct stacked_queue *queue);
extern bool stacked_queue_empty_p(struct stacked_queue *queue);
extern void stacked_queue_enter(struct stacked_queue *queue, void *member);
extern void * stacked_queue_leave(struct stacked_queue *queue);
extern void stacked_queue_cleanup(struct stacked_queue *queue);
extern void stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));

/* END OF STACKED QUEUE */


/* DOUBLY END QUEUE */
extern struct doubly_end_queue * doubly_end_queue_create(void);
extern void doubly_end_queue_destroy(struct doubly_end_queue **queue);
extern uint32 doubly_end_queue_length(struct doubly_end_queue *queue);
extern bool doubly_end_queue_empty_p(struct doubly_end_queue *queue);
extern void doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
extern void doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
extern void * doubly_end_queue_head_leave(struct doubly_end_queue *queue);
extern void * doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
extern void doubly_end_queue_cleanup(struct doubly_end_queue *queue);
extern void doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));

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



/* ARRAY STACK */
extern struct array_stack * array_stack_create(void);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_space_expand(struct array_stack *stack, uint32 extra);
extern bool array_stack_full_p(struct array_stack *stack);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_space_rest(struct array_stack *stack);
extern void array_stack_push(struct array_stack *stack, void *member);
extern void * array_stack_pop(struct array_stack *stack);
extern bool array_stack_empty_p(struct array_stack *stack);
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
/* END OF ARRAY STACK */

/* LINKED STACK */
extern struct linked_stack * linked_stack_create(void);
extern void linked_stack_destroy(struct linked_stack **stack);
extern void linked_stack_space_expand(struct linked_stack *stack, uint32 dim);
extern bool linked_stack_full_p(struct linked_stack *stack);
extern uint32 linked_stack_space_rest(struct linked_stack *stack);
extern void linked_stack_push(struct linked_stack *stack, void *member);
extern void * linked_stack_pop(struct linked_stack *stack);
extern bool linked_stack_empty_p(struct linked_stack *stack);
extern void linked_stack_cleanup(struct linked_stack *stack);
extern void linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
extern uint32 linked_stack_capacity(struct linked_stack *stack);

/* END OF LINKED STACK */

#endif
/* END of ./src/inc/stack.h */
#endif /* END OF FILE */