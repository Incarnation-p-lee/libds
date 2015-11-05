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

#if defined X86_32
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long long   sint64;
    typedef unsigned long long uint64;
    typedef unsigned long      ulint32;
    #define M32
    #define NUMERAL ulint32
#endif

#if defined X86_64
    typedef signed short   sint16;
    typedef unsigned short uint16;
    typedef signed int     sint32;
    typedef unsigned int   uint32;
    typedef signed long    sint64;
    typedef unsigned long  uint64;
    #define M64
    #define NUMERAL uint64
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
    uint32                    sid;
    void                      *val;
    struct single_linked_list *next;
};

struct doubly_linked_list {
    uint32                    sid;
    void                      *val;
    struct doubly_linked_list *next;
    struct doubly_linked_list *previous;
};

/*
 * Skip Linked List
 *     Skip linked list used extra pointer to forward node for quickly find.
 * the linked list should be sorted.
 *     Take 3 level skip list layout as below:
 * ------------------------------------------------------------
 * | Level 2 head  0 ----------------> 10 -------------> NULL |
 * | Level 1 head  0 ------> 7 ------> 10 -> 22 -------> NULL |
 * | Level 0 head  0 -> 3 -> 7 -> 9 -> 10 -> 22 -> 34 -> NULL |
 * ------------------------------------------------------------
 */
#define LEVEL_LIMIT 8

struct skip_linked_list {
    sint32 key;
    void   *val;
    union {
        struct skip_linked_list *next;
        struct skip_linked_list *layer[LEVEL_LIMIT];
    };
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
    struct collision_chain    chain;
    struct binary_search_tree *left;
    struct binary_search_tree *right;
};

/*
 * avl tree
 */
struct avl_tree {
    sint32                    height;
    struct binary_search_tree alias;
};

/*
 * splay tree
 */
struct splay_tree {
    struct binary_search_tree alias;
};

struct hashing_table {
    void       **space;
    uint32     size;
    uint32     load_factor; /* load_factor % */
    union {
        void   *func;
        uint32 (*separate_chain)(void *, uint32);
        uint32 (*open_addressing)(void *, uint32, uint32);
    };
};

/*
 * hashing table with separate chaining
 */
struct separate_chain_hash {
    struct hashing_table *table;
};

/*
 * hashing table with open addressing square
 */
struct open_addressing_hash {
    struct hashing_table *table;
};

/*
 * generate heap
 */
struct binary_heap {
    struct collision_chain **base;
    uint32 capacity;
    uint32 size;
};

/*
 * min heap
 */
struct minimal_heap {
    struct binary_heap *alias;
};

/*
 * max heap
 */
struct maximal_heap {
    struct binary_heap *alias;
};

/*
 * min-max heap, root have 0 depth
 *     for even depth node, < fater, > grandfater
 *     for odd  depth node, > fater, < grandfater
 */
struct min_max_heap {
    struct binary_heap *alias;
};

#endif

/* END of ./src/inc/data_structure_types.h */

/* BEGIN of ./src/inc/data_structure_defines.h */
#ifndef HAVE_DATA_STRUCTURE_DEFINES_H
#define HAVE_DATA_STRUCTURE_DEFINES_H

/* Macro of struct field set and get.
   We _DO_ NOT use function here for the balance of performance
   and interface clean.
   _Attention_, _DO_ _NOT_ use const parameters for following macro. */
/* DOUBLY LINKED LIST */
#define RESULT_CHECK_doubly_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->sid, (ex)->sid, (pass));            \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
        RESULT_CHECK_pointer((aim)->previous, (ex)->previous, (pass)); \
    } while (false)

#define doubly_linked_list_node_val(node) \
    (assert(node), (node)->val)
#define doubly_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define doubly_linked_list_node_sid(node) \
    (assert(node), (node)->sid)
#define doubly_linked_list_node_sid_set(node, v) \
    (assert(node), (node)->sid = (v))

#define doubly_linked_list_node_next(node) \
    (assert(node), (node)->next)
#define doubly_linked_list_node_next_set(node, v) \
    (assert(node), (node)->next = (v))

#define doubly_linked_list_node_previous(node) \
    (assert(node), (node)->previous)
#define doubly_linked_list_node_previous_set(node, v) \
    (assert(node), (node)->previous = (v))


/* SINGLE LINKED LIST */
#define RESULT_CHECK_single_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->sid, (ex)->sid, (pass));            \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
    } while (false)

#define single_linked_list_node_val(node) \
    (assert(node), (node)->val)
#define single_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define single_linked_list_node_sid(node) \
    (assert(node), (node)->sid)
#define single_linked_list_node_sid_set(node, v) \
    (assert(node), (node)->sid = (v))

#define single_linked_list_node_next(node) \
    (assert(node), (node)->next)
#define single_linked_list_node_next_set(node, v) \
    (assert(node), (node)->next = (v))


/* SKIP LINKED LIST */
#define skip_linked_list_node_key(node) \
    (assert(node), (node)->key)
#define skip_linked_list_node_key_set(node, k) \
    (assert(node), (node)->key = (k))

#define skip_linked_list_node_val(node) \
    (assert(node), (node)->val)
#define skip_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define skip_linked_list_node_next(node) \
    (assert(node), (node)->next)
#define skip_linked_list_node_next_set(node, n) \
    (assert(node), (node)->next = (n))

/* ARRAY STACK */
#define RESULT_CHECK_array_stack(aim, ex, pass)                        \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->sid, (ex)->sid, (pass))             \
        RESULT_CHECK_uint32((aim)->space.dim, (ex)->space.dim, (pass)) \
    } while (false)
    /* We do check sp, bp field here, they should not export to user */

#define array_stack_sid(stack) \
    (assert(stack), (stack)->sid)
#define array_stack_sid_set(stack, v) \
    (assert(stack), (stack)->sid = (v))

#define array_stack_space_dim(stack) \
    (assert(stack), (stack)->space.dim)
#define array_stack_space_dim_set(stack, v) \
    (assert(stack), (stack)->space.dim = (v))

/* LINKED STACK */
#define linked_stack_sid(stack) \
    (assert(stack), (stack)->sid)
#define linked_stack_sid_set(stack, v) \
    (assert(stack), (stack)->sid = (v))

/* ARRAY QUEUE */
#define array_queue_sid(queue) \
    (assert(queue), (queue)->sid)
#define array_queue_sid_set(queue, v) \
    (assert(queue), (queue)->sid = (v))

#define array_queue_rest(queue) \
    (assert(queue), (queue)->space.rest)

#define array_queue_dim(queue) \
    (assert(queue), (queue)->space.dim)

/* STACKED QUEUE */
#define stacked_queue_sid(queue) \
    (assert(queue), (queue)->sid)
#define stacked_queue_sid_set(queue, v) \
    (assert(queue), (queue)->sid = (v))

#define stacked_queue_dim(queue) \
    (assert(queue), (queue)->dim)

/* DOUBLY END QUEUE */
#define doubly_end_queue_sid(queue) \
    (assert(queue), (queue)->sid)
#define doubly_end_queue_sid_set(queue, v) \
    (assert(queue), (queue)->sid = (v))

/* BINARY SEARCH TREE */
#define binary_search_tree_node_nice(tree) \
    (assert(tree), (tree)->chain.nice)
#define binary_search_tree_node_nice_set(tree, v) \
    (assert(tree), (tree)->chain.nice = (v))

#define binary_search_tree_child_left(tree) \
    (assert(tree), (tree)->left)
#define binary_search_tree_child_left_set(tree, v) \
    (assert(tree), (tree)->left = (v))

#define binary_search_tree_child_right(tree) \
    (assert(tree), (tree)->right)
#define binary_search_tree_child_right_set(tree, v) \
    (assert(tree), (tree)->right = (v))

#define binary_search_tree_node_link(tree) \
    (assert(tree), ((tree)->chain).link)
#define binary_search_tree_child_link_set(tree, v) \
    (assert(tree), ((tree)->chain).link = (v))

/* AVL TREE */
#define avl_tree_node_nice(tree) \
    (assert(tree), (tree)->alias.chain.nice)
#define avl_tree_node_nice_set(tree, v) \
    (assert(tree), (tree)->alias.chain.nice = (v))

#define avl_tree_child_left(tree) \
    (assert(tree), avl_tree_ptr_container_of(tree->alias.left))

#define avl_tree_child_right(tree) \
    (assert(tree), avl_tree_ptr_container_of(tree->alias.right))

#define avl_tree_node_link(tree) \
    (assert(tree), (tree)->alias.chain.link)
#define avl_tree_node_link_set(tree, v) \
    (assert(tree), (tree)->alias.chain.link = (v))

#define avl_tree_height(tree) \
    (assert(tree), (tree)->height)
#define avl_tree_height_set(tree, v) \
    (assert(tree), (tree)->height = (v))

/* SPLAY TREE */
#define splay_tree_node_nice(tree) \
    (assert(tree), (tree)->alias.chain.nice)
#define splay_tree_node_nice_set(tree, v) \
    (assert(tree), (tree)->alias.chain.nice = (v))

#define splay_tree_child_left(tree) \
    (assert(tree), splay_tree_ptr_container_of(tree->alias.left))

#define splay_tree_child_right(tree) \
    (assert(tree), splay_tree_ptr_container_of(tree->alias.right))

#define splay_tree_node_link(tree) \
    (assert(tree), (tree)->alias.chain.link)

/* HASHING TABLE */
#define hashing_table_size(hash) \
    (assert(hash), (hash)->size)

#define hashing_table_load_factor(hash) \
    (assert(hash), (hash)->load_factor)
#define hashing_table_load_factor_set(hash, factor) \
    (assert(hash), (hash)->load_factor = (factor))

/* SEPARATE CHAIN HASHING */
#define separate_chain_hash_size(hash) \
    (assert(hash), hashing_table_size((hash)->table))

#define separate_chain_hash_load_factor(hash) \
    (assert(hash), hashing_table_load_factor((hash)->table))
#define separate_chain_hash_load_factor_set(hash, factor) \
    (assert(hash), hashing_table_load_factor_set((hash)->table, factor))

/* OPEN ADDRESSING HASHING */
#define open_addressing_hash_size(hash) \
    (assert(hash), hashing_table_size((hash)->table))

#define open_addressing_hash_load_factor(hash) \
    (assert(hash), hashing_table_load_factor((hash)->table))
#define open_addressing_hash_load_factor_set(hash, factor) \
    (assert(hash), hashing_table_load_factor_set((hash)->table, factor))

/* MINIMAL HEAP */
#define minimal_heap_size(heap) \
    (assert(heap), (heap)->alias->size)

#define minimal_heap_capacity(heap) \
    (assert(heap), (heap)->alias->capacity)

#define minimal_heap_nice(heap, index) \
    (assert(heap), HEAP_NICE(heap->alias, index))

#define minimal_heap_link(heap, index) \
    (assert(heap), HEAP_LINK(heap->alias, index))
#define minimal_heap_link_set(heap, index, link) \
    (assert(heap), HEAP_LINK(heap->alias, index) = (link))

/* MAXIMAL HEAP */
#define maximal_heap_size(heap) \
    (assert(heap), (heap)->alias->size)

#define maximal_heap_capacity(heap) \
    (assert(heap), (heap)->alias->capacity)

#define maximal_heap_nice(heap, index) \
    (assert(heap), HEAP_NICE(heap->alias, index))

#define maximal_heap_link(heap, index) \
    (assert(heap), HEAP_LINK(heap->alias, index))
#define maximal_heap_link_set(heap, index, link) \
    (assert(heap), HEAP_LINK(heap->alias, index) = (link))

/* MIN_MAX HEAP */
#define min_max_heap_size(heap) \
    (assert(heap), (heap)->alias->size)

#define min_max_heap_capacity(heap) \
    (assert(heap), (heap)->alias->capacity)

#define min_max_heap_nice(heap, index) \
    (assert(heap), HEAP_NICE(heap->alias, index))

#define min_max_heap_link(heap, index) \
    (assert(heap), HEAP_LINK(heap->alias, index))
#define min_max_heap_link_set(heap, index, link) \
    (assert(heap), HEAP_LINK(heap->alias, index) = (link))

#endif
/* END of ./src/inc/data_structure_defines.h */

/* BEGIN of ./src/inc/defines.h */
#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H

#define true                 1
#define false                0

#define SYM_2_STR(symbol)    (#symbol)
#define array_sizeof(a)      (sizeof(a) / sizeof(a[0]))

#define NAME_LEN             128
#define CONTENT_LEN          NAME_LEN


#define CONTAINER_OF(ptr, type, member) \
    (assert(ptr), (type *)((void *)(ptr) - (void *)(&((type *)0)->member)))

#define pr_log_err(msg)             \
    do {                            \
        libds_log_print(ERRR, msg); \
        exit(1);                    \
    } while (0);


#define MAX_U(x, y) ((uint32)(x) > (uint32)(y) ? (uint32)(x) : (uint32)(y))
#define MAX_S(x, y) ((sint32)(x) > (sint32)(y) ? (sint32)(x) : (sint32)(y))

#define UINT32_IDX_BIT(op, idx) ((op >> (idx)) & 1u)
#define SINT64_ABS(x)           (((sint64)(x) > 0) ? (x) : -(x))

#if defined X86_64
    #define PTR_TO_UNSIGNED(ptr) (uint64)(ptr)
    #define UNSIGNED_TO_PTR(usd) (void *)(usd)
    #define U64_MDF_X            "lx"
    #define U64_MDF_U            "lu"
    #define S64_MDF_D            "ld"
    #define S64_MDF_X            "lx"
#endif

#if defined X86_32
    #define PTR_TO_UNSIGNED(ptr) (uint32)(ptr)
    #define UNSIGNED_TO_PTR(usd) (void *)((uint32)usd)
    #define U64_MDF_X            "llx"
    #define U64_MDF_U            "llu"
    #define S64_MDF_D            "lld"
    #define S64_MDF_X            "llx"
#endif


#endif

/* END of ./src/inc/defines.h */

/* BEGIN of ./src/linked_list/linked_list.h */
#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#define SKIP_LIST_BOTTOM_IDX  0
#define SKIP_LIST_MAX_LVL     LEVEL_LIMIT
#define SKIP_LIST_MAX_LVL_IDX SKIP_LIST_MAX_LVL - 1


#endif
/* END of ./src/linked_list/linked_list.h */

/* BEGIN of ./src/linked_list/linked_list_declaration.h */
#ifndef LINKED_LIST_DECLARATION_H
#define LINKED_LIST_DECLARATION_H

extern bool doubly_linked_list_contains_p(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern bool single_linked_list_contains_p(struct single_linked_list *list, struct single_linked_list *node);
extern bool skip_linked_list_key_contains_p(struct skip_linked_list *list, sint32 key);
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern struct doubly_linked_list * doubly_linked_list_node_by_index(struct doubly_linked_list *list, uint32 index);
extern struct doubly_linked_list * doubly_linked_list_node_copy(struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern struct doubly_linked_list * doubly_linked_list_node_remove(struct doubly_linked_list **node);
extern struct single_linked_list * single_linked_list_create(void);
extern struct single_linked_list * single_linked_list_merge(struct single_linked_list *m, struct single_linked_list *n);
extern struct single_linked_list * single_linked_list_node_by_index(struct single_linked_list *list, uint32 index);
extern struct single_linked_list * single_linked_list_node_copy(struct single_linked_list *node);
extern struct single_linked_list * single_linked_list_node_create(void *val, uint32 sid);
extern struct single_linked_list * single_linked_list_node_previous(struct single_linked_list *node);
extern struct single_linked_list * single_linked_list_node_remove(struct single_linked_list **node);
extern struct skip_linked_list * skip_linked_list_create(void);
extern struct skip_linked_list * skip_linked_list_merge(struct skip_linked_list *m, struct skip_linked_list *n);
extern struct skip_linked_list * skip_linked_list_node_by_index(struct skip_linked_list *list, uint32 index);
extern struct skip_linked_list * skip_linked_list_node_create(void *val, sint32 key);
extern struct skip_linked_list * skip_linked_list_node_find_key(struct skip_linked_list *list, sint32 key);
extern struct skip_linked_list * skip_linked_list_node_insert(struct skip_linked_list **list, struct skip_linked_list *tgt);
extern struct skip_linked_list * skip_linked_list_node_remove(struct skip_linked_list **list, sint32 key);
extern uint32 doubly_linked_list_length(struct doubly_linked_list *list);
extern uint32 single_linked_list_length(struct single_linked_list *list);
extern uint32 skip_linked_list_length(struct skip_linked_list *list);
extern void doubly_linked_list_destroy(struct doubly_linked_list **list);
extern void doubly_linked_list_initial(struct doubly_linked_list *list);
extern void doubly_linked_list_iterate(struct doubly_linked_list *list, void (*handler)(void *));
extern void doubly_linked_list_node_append(struct doubly_linked_list *node, void *val);
extern void doubly_linked_list_node_initial(struct doubly_linked_list *list, void *val, uint32 sid);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_before(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_insert_before_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern void doubly_linked_list_node_remove_and_destroy(struct doubly_linked_list **node);
extern void doubly_linked_list_serialize(struct doubly_linked_list *list);
extern void single_linked_list_destroy(struct single_linked_list **list);
extern void single_linked_list_initial(struct single_linked_list *list);
extern void single_linked_list_iterate(struct single_linked_list *list, void (*handler)(void *));
extern void single_linked_list_node_append(struct single_linked_list *node, void *val);
extern void single_linked_list_node_initial(struct single_linked_list *list, void *val, uint32 sid);
extern void single_linked_list_node_insert_after(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_node_insert_after_risky(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_node_insert_before(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_node_insert_before_risky(struct single_linked_list *cur, struct single_linked_list *node);
extern void single_linked_list_node_remove_and_destroy(struct single_linked_list **node);
extern void single_linked_list_serialize(struct single_linked_list *list);
extern void skip_linked_list_destroy(struct skip_linked_list **list);
extern void skip_linked_list_initial(struct skip_linked_list *list);
extern void skip_linked_list_iterate(struct skip_linked_list *list, void (*handler)(void *));
extern void skip_linked_list_node_initial(struct skip_linked_list *list, void *val, sint32 key);
extern void skip_linked_list_node_remove_and_destroy(struct skip_linked_list **list, sint32 key);

#endif
/* END of ./src/linked_list/linked_list_declaration.h */

/* BEGIN of ./src/queue/queue.h */
#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

#define DEFAULT_QUEUE_SPACE_SIZE   1024
#define EXPAND_QUEUE_SPACE_MIN     32


#endif
/* END of ./src/queue/queue.h */

/* BEGIN of ./src/queue/queue_declaration.h */
#ifndef QUEUE_DECLARATION_H
#define QUEUE_DECLARATION_H


extern bool array_queue_empty_p(struct array_queue *queue);
extern bool array_queue_full_p(struct array_queue *queue);
extern bool doubly_end_queue_empty_p(struct doubly_end_queue *queue);
extern bool stacked_queue_empty_p(struct stacked_queue *queue);
extern bool stacked_queue_full_p(struct stacked_queue *queue);
extern struct array_queue * array_queue_create(void);
extern struct doubly_end_queue * doubly_end_queue_create(void);
extern struct stacked_queue * stacked_queue_create(void);
extern uint32 array_queue_capacity(struct array_queue *queue);
extern uint32 array_queue_space_rest(struct array_queue *queue);
extern uint32 doubly_end_queue_length(struct doubly_end_queue *queue);
extern uint32 stacked_queue_capacity(struct stacked_queue *queue);
extern uint32 stacked_queue_space_rest(struct stacked_queue *queue);
extern void * array_queue_leave(struct array_queue *queue);
extern void * doubly_end_queue_head_leave(struct doubly_end_queue *queue);
extern void * doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
extern void * stacked_queue_leave(struct stacked_queue *queue);
extern void array_queue_cleanup(struct array_queue *queue);
extern void array_queue_destroy(struct array_queue **queue);
extern void array_queue_enter(struct array_queue *queue, void *member);
extern void array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
extern void array_queue_space_expand(struct array_queue *queue, uint32 extra);
extern void doubly_end_queue_cleanup(struct doubly_end_queue *queue);
extern void doubly_end_queue_destroy(struct doubly_end_queue **queue);
extern void doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
extern void doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));
extern void doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
extern void stacked_queue_cleanup(struct stacked_queue *queue);
extern void stacked_queue_destroy(struct stacked_queue **queue);
extern void stacked_queue_enter(struct stacked_queue *queue, void *member);
extern void stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));
extern void stacked_queue_space_expand(struct stacked_queue *queue, uint32 extra);

#endif
/* END of ./src/queue/queue_declaration.h */

/* BEGIN of ./src/stack/stack.h */
#ifndef HAVE_STACK_H
#define HAVE_STACK_H

#define DEFAULT_STACK_SPACE_SIZE   1024
#define EXPAND_STACK_SPACE_MIN     32


/* ARRAY STACK */

extern bool array_stack_full_p(struct array_stack *stack);
extern bool array_stack_empty_p(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_space_expand(struct array_stack *stack, uint32 extra);
extern void array_stack_push(struct array_stack *stack, void *member);
extern void * array_stack_pop(struct array_stack *stack);
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_space_rest(struct array_stack *stack);
extern struct array_stack * array_stack_create(void);
/* END OF ARRAY STACK */

/* LINKED STACK */
extern bool linked_stack_full_p(struct linked_stack *stack);
extern bool linked_stack_empty_p(struct linked_stack *stack);
extern void linked_stack_destroy(struct linked_stack **stack);
extern void linked_stack_space_expand(struct linked_stack *stack, uint32 dim);
extern void linked_stack_push(struct linked_stack *stack, void *member);
extern void linked_stack_cleanup(struct linked_stack *stack);
extern void linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
extern void * linked_stack_pop(struct linked_stack *stack);
extern uint32 linked_stack_capacity(struct linked_stack *stack);
extern uint32 linked_stack_space_rest(struct linked_stack *stack);
extern struct linked_stack * linked_stack_create(void);

/* END OF LINKED STACK */

#endif
/* END of ./src/stack/stack.h */

/* BEGIN of ./src/stack/stack_declaration.h */
#ifndef STACK_DECLARATION_H
#define STACK_DECLARATION_H


extern bool array_stack_empty_p(struct array_stack *stack);
extern bool array_stack_full_p(struct array_stack *stack);
extern bool linked_stack_empty_p(struct linked_stack *stack);
extern bool linked_stack_full_p(struct linked_stack *stack);
extern struct array_stack * array_stack_create(void);
extern struct linked_stack * linked_stack_create(void);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_space_rest(struct array_stack *stack);
extern uint32 linked_stack_capacity(struct linked_stack *stack);
extern uint32 linked_stack_space_rest(struct linked_stack *stack);
extern void * array_stack_pop(struct array_stack *stack);
extern void * linked_stack_pop(struct linked_stack *stack);
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void array_stack_push(struct array_stack *stack, void *member);
extern void array_stack_space_expand(struct array_stack *stack, uint32 extra);
extern void linked_stack_cleanup(struct linked_stack *stack);
extern void linked_stack_destroy(struct linked_stack **stack);
extern void linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
extern void linked_stack_push(struct linked_stack *stack, void *member);
extern void linked_stack_space_expand(struct linked_stack *stack, uint32 dim);

#endif
/* END of ./src/stack/stack_declaration.h */

/* BEGIN of ./src/tree/tree.h */
#ifndef HAVE_TREE_H
#define HAVE_TREE_H

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

#define TREE_NICE_PLUS_LMT  0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT (-TREE_NICE_PLUS_LMT - 1)

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false


#endif
/* END of ./src/tree/tree.h */

/* BEGIN of ./src/tree/tree_declaration.h */
#ifndef TREE_DECLARATION_H
#define TREE_DECLARATION_H


extern bool avl_tree_balanced_p(struct avl_tree *tree);
extern bool avl_tree_node_contains_p(struct avl_tree *tree, struct avl_tree *node);
extern bool binary_search_tree_node_contains_p(struct binary_search_tree *tree, struct binary_search_tree *node);
extern bool splay_tree_node_contains_p(struct splay_tree *tree, struct splay_tree *node);
extern sint32 binary_search_tree_height(struct binary_search_tree *tree);
extern sint32 splay_tree_height(struct splay_tree *tree);
extern struct avl_tree * avl_tree_create(void);
extern struct avl_tree * avl_tree_node_create(void *val, sint64 nice);
extern struct avl_tree * avl_tree_node_find(struct avl_tree *tree, sint64 nice);
extern struct avl_tree * avl_tree_node_find_max(struct avl_tree *tree);
extern struct avl_tree * avl_tree_node_find_min(struct avl_tree *tree);
extern struct avl_tree * avl_tree_node_insert(struct avl_tree **tree, struct avl_tree *node);
extern struct avl_tree * avl_tree_node_remove(struct avl_tree **tree, sint64 nice);
extern struct avl_tree * avl_tree_ptr_container_of(struct binary_search_tree *node);
extern struct binary_search_tree  * binary_search_tree_node_find_min(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_create(void);
extern struct binary_search_tree * binary_search_tree_node_create(void *val, sint64 nice);
extern struct binary_search_tree * binary_search_tree_node_find(struct binary_search_tree *tree, sint64 nice);
extern struct binary_search_tree * binary_search_tree_node_find_max(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_node_insert(struct binary_search_tree *tree, struct binary_search_tree *node);
extern struct binary_search_tree * binary_search_tree_node_remove(struct binary_search_tree **tree, sint64 nice);
extern struct binary_search_tree * splay_tree_node_insert_internal(struct binary_search_tree **tree, struct binary_search_tree *node, struct binary_search_tree *root);
extern struct splay_tree * splay_tree_create(void);
extern struct splay_tree * splay_tree_node_create(void *val, sint64 nice);
extern struct splay_tree * splay_tree_node_find(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_node_find_max(struct splay_tree **tree);
extern struct splay_tree * splay_tree_node_find_min(struct splay_tree **tree);
extern struct splay_tree * splay_tree_node_insert(struct splay_tree **tree, struct splay_tree *node);
extern struct splay_tree * splay_tree_node_remove(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_node_remove_internal(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_ptr_container_of(struct binary_search_tree *node);
extern void avl_tree_destroy(struct avl_tree **tree);
extern void avl_tree_initial(struct avl_tree *tree);
extern void avl_tree_iterate(struct avl_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice);
extern void avl_tree_node_remove_and_destroy(struct avl_tree **tree, sint64 nice);
extern void binary_search_tree_destroy(struct binary_search_tree **tree);
extern void binary_search_tree_initial(struct binary_search_tree *tree);
extern void binary_search_tree_iterate(struct binary_search_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void binary_search_tree_node_initial(struct binary_search_tree *node, void *val, sint64 nice);
extern void binary_search_tree_node_remove_and_destroy(struct binary_search_tree **tree, sint64 nice);
extern void splay_tree_destroy(struct splay_tree **tree);
extern void splay_tree_initial(struct splay_tree *tree);
extern void splay_tree_iterate(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void splay_tree_node_initial(struct splay_tree *node, void *val, sint64 nice);
extern void splay_tree_node_remove_and_destroy(struct splay_tree **tree, sint64 nice);

#endif
/* END of ./src/tree/tree_declaration.h */

/* BEGIN of ./src/hash/hash.h */
#ifndef HAVE_HASH_H
#define HAVE_HASH_H

#define DEFAULT_CHAIN_HASH_SIZE 11u
#define DEFAULT_LOAD_FACTOR     72u /* Means 0.72 or 72% */

#define OPEN_ADDRESSING_HASH_LOAD_FACTOR 50u


#endif
/* END of ./src/hash/hash.h */

/* BEGIN of ./src/hash/hash_declaration.h */
#ifndef HASH_DECLARATION_H
#define HASH_DECLARATION_H


extern struct open_addressing_hash * open_addressing_hash_create(uint32 size);
extern struct open_addressing_hash * open_addressing_hash_rehashing(struct open_addressing_hash **hash);
extern struct separate_chain_hash * separate_chain_hash_create(uint32 size);
extern struct separate_chain_hash * separate_chain_hash_rehashing(struct separate_chain_hash **hash);
extern uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 iter);
extern uint32 hashing_function_polynomial(void *key, uint32 size);
extern uint32 open_addressing_hash_load_factor_calculate(struct open_addressing_hash *hash);
extern uint32 separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash);
extern void * open_addressing_hash_find(struct open_addressing_hash *hash, void *key);
extern void * open_addressing_hash_remove(struct open_addressing_hash *hash, void *key);
extern void * separate_chain_hash_find(struct separate_chain_hash *hash, void *key);
extern void * separate_chain_hash_remove(struct separate_chain_hash *hash, void *key);
extern void open_addressing_hash_destroy(struct open_addressing_hash **hash);
extern void open_addressing_hash_insert(struct open_addressing_hash **hash, void *key);
extern void separate_chain_hash_destroy(struct separate_chain_hash **hash);
extern void separate_chain_hash_insert(struct separate_chain_hash **hash, void *key);

#endif
/* END of ./src/hash/hash_declaration.h */

/* BEGIN of ./src/heap/heap.h */
#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

#define HEAP_NICE_UPPER_LMT      0x7fffffffffffffff
#define HEAP_NICE_LOWER_LMT      (-HEAP_NICE_UPPER_LMT - 1)

#define DEFAULT_BINARY_HEAP_SIZE 4097

#define INDEX_ROOT               0x1u
#define INDEX_L_CHILD(index)     (index) * 2
#define INDEX_R_CHILD(index)     ((index) * 2 + 1)
#define INDEX_PARENT(index)      ((index) / 2)
#define INDEX_GD_PARENT(index)   ((index) / 4)
#define INDEX_LAST(heap)         ((heap)->size)
#define INDEX_FIRST              INDEX_ROOT
#define INDEX_INVALID            0u
#define DEPTH_INVALID            0xffffffffu
#define INDEX_LL_CHILD(index)    (index) * 4
#define INDEX_RR_CHILD(index)    ((index) * 2 + 1) * 2

#define HEAP_PARENT_NICE(heap, index)      (heap)->base[INDEX_PARENT(index)]->nice
#define HEAP_LEFT_CHILD_NICE(heap, index)  (heap)->base[INDEX_L_CHILD(index)]->nice
#define HEAP_RIGHT_CHILD_NICE(heap, index) (heap)->base[INDEX_R_CHILD(index)]->nice
#define HEAP_NICE(heap, index)             (heap)->base[index]->nice
#define HEAP_LINK(heap, index)             (heap)->base[index]->link
#define HEAP_SIZE(heap)                    (heap)->size
#define HEAP_CHAIN(heap, index)            (heap)->base[index]

#define u_offset(n, offset) (n + offset)

/* EXTERNAL FUNCTIONS */
/* END OF EXTERNAL FUNCTIONS */

/* BINARY HEAP DEBUG */
/* END OF BINARY HEAP DEBUG */

#endif
/* END of ./src/heap/heap.h */

/* BEGIN of ./src/heap/heap_declaration.h */
#ifndef HEAP_DECLARATION_H
#define HEAP_DECLARATION_H


extern bool maximal_heap_empty_p(struct maximal_heap *heap);
extern bool maximal_heap_full_p(struct maximal_heap *heap);
extern bool min_max_heap_empty_p(struct min_max_heap *heap);
extern bool min_max_heap_full_p(struct min_max_heap *heap);
extern bool minimal_heap_empty_p(struct minimal_heap *heap);
extern bool minimal_heap_full_p(struct minimal_heap *heap);
extern struct doubly_linked_list * maximal_heap_node_find(struct maximal_heap *heap, sint64 nice);
extern struct doubly_linked_list * maximal_heap_node_find_max(struct maximal_heap *heap);
extern struct doubly_linked_list * maximal_heap_node_remove(struct maximal_heap *heap, sint64 nice);
extern struct doubly_linked_list * maximal_heap_node_remove_max(struct maximal_heap *heap);
extern struct doubly_linked_list * min_max_heap_node_find(struct min_max_heap *heap, sint64 nice);
extern struct doubly_linked_list * min_max_heap_node_find_max(struct min_max_heap *heap);
extern struct doubly_linked_list * min_max_heap_node_find_min(struct min_max_heap *heap);
extern struct doubly_linked_list * min_max_heap_node_remove(struct min_max_heap *heap, sint64 nice);
extern struct doubly_linked_list * min_max_heap_node_remove_min(struct min_max_heap *heap);
extern struct doubly_linked_list * minimal_heap_node_find(struct minimal_heap *heap, sint64 nice);
extern struct doubly_linked_list * minimal_heap_node_find_min(struct minimal_heap *heap);
extern struct doubly_linked_list * minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice);
extern struct doubly_linked_list * minimal_heap_node_remove_min(struct minimal_heap *heap);
extern struct maximal_heap * maximal_heap_build(struct collision_chain **chain_array, uint32 size);
extern struct maximal_heap * maximal_heap_create(uint32 capacity);
extern struct min_max_heap * min_max_heap_create(uint32 capacity);
extern struct minimal_heap * minimal_heap_build(struct collision_chain **chain_array, uint32 size);
extern struct minimal_heap * minimal_heap_create(uint32 capacity);
extern uint32 min_max_heap_node_depth(struct min_max_heap *heap, uint32 index);
extern void maximal_heap_cleanup(struct maximal_heap *heap);
extern void maximal_heap_destroy(struct maximal_heap **heap);
extern void maximal_heap_node_decrease_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
extern void maximal_heap_node_increase_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
extern void maximal_heap_node_insert(struct maximal_heap *heap, void *val, sint64 nice);
extern void maximal_heap_node_remove_and_destroy(struct maximal_heap *heap, sint64 nice);
extern void maximal_heap_node_remove_max_and_destroy(struct maximal_heap *heap);
extern void min_max_heap_cleanup(struct min_max_heap *heap);
extern void min_max_heap_destroy(struct min_max_heap **heap);
extern void min_max_heap_node_insert(struct min_max_heap *heap, void *val, sint64 nice);
extern void min_max_heap_node_remove_min_and_destroy(struct min_max_heap *heap);
extern void minimal_heap_cleanup(struct minimal_heap *heap);
extern void minimal_heap_destroy(struct minimal_heap **heap);
extern void minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
extern void minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
extern void minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice);
extern void minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice);
extern void minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap);

#endif
/* END of ./src/heap/heap_declaration.h */

/* BEGIN of ./src/log/log.h */
#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

#define LOG_FNAME "libds.log"

#endif
/* END of ./src/log/log.h */
#endif /* END OF FILE */