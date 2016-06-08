#ifndef HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H
#define HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H

typedef signed char            sint8;
typedef unsigned char          uint8;
typedef unsigned int           bool;

#if defined X86_32
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long long   sint64;
    typedef unsigned long long uint64;
    typedef unsigned long      ulint32;
    typedef unsigned int       ptr_t;
#endif

#if defined X86_64
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long        sint64;
    typedef unsigned long      uint64;
    typedef unsigned long      ptr_t;
#endif

#define DATA_STRUCTURE_TYPES_H
#define SIZE_INVALID           0xffffffff
#define SKIP_LVL_LMT           8          // skip linked list level limitation
#define SKIP_KEY_INVALID       (sint32)0x80000000
#define SPT_CHN_HASH_SIZE_DFT  11u        // separate chain hash default size
#define SPT_CHN_HASH_LOAD_FTR  72u        // separate chain hash load factor
#define OPN_ADDR_HASH_LOAD_FTR 50u        // open addressing hash load factor
#define HASH_SIZE_INVALID      SIZE_INVALID
#define HASH_LD_FTR_INVALID    101u       // load factor max is 100u
#define HEAP_SIZE_INVALID      SIZE_INVALID
#define HEAP_CPCT_INVALID      SIZE_INVALID
#define HEAP_NICE_INVALID      (sint64)(1ull << 63)
#define HEAP_CPCT_DFT          4097u      // heap default capacity
#define HEAP_IDX_INVALID       0u         // heap invalid index
#define HEAP_IDX_ROOT          1u         // heap root index
#define HEAP_NPL_NULL          -1         // heap NPL value of NULL
#define HEAP_DEPTH_INVALID     SIZE_INVALID
#define QUEUE_SIZE_DFT         1024       // queue size default
#define QUEUE_EXPD_SIZE_MIN    128        // queue expand size minimal
#define QUEUE_REST_INVALID     SIZE_INVALID
#define QUEUE_CPCT_INVALID     SIZE_INVALID
#define QUEUE_SIZE_INVALID     SIZE_INVALID
#define STACK_SIZE_DFT         1024       // stack size default
#define STACK_EXPD_SIZE_MIN    128        // stack expand size minimal
#define STACK_SIZE_INVALID     SIZE_INVALID
#define BIN_IDXED_NMBR_INVALID 0          // binary indexed tree invalid number
#define BIN_IDXED_SUM_INVALID  (sint64)(1ull << 63)
#define PTR_INVALID            (void *)-1 // invalid pointer
#define HEAP_IDX_CHILD_L(x)    ((x) * 2)
#define HEAP_IDX_CHILD_R(x)    ((x) * 2 + 1)

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

struct single_linked_list {
    uint32                    sid;
    void                      *val;
    struct single_linked_list *next;
};

struct doubly_linked_list {
    void                      *val;
    struct doubly_linked_list *next;
    struct doubly_linked_list *previous;
};

struct skip_linked_list {
    sint32 key;
    void   *val;
    union {
        struct skip_linked_list *next;
        struct skip_linked_list *layer[SKIP_LVL_LMT];
    };
};

struct array_stack_space {
    uint32 dim;
    void   **sp;
    void   **bp;
};

struct array_stack {
    struct array_stack_space space;
};

struct linked_stack_space {
    struct array_stack_space  space;
    struct doubly_linked_list link;
};

struct linked_stack {
    struct linked_stack_space *base;
    struct linked_stack_space *top;
};

struct array_queue_space {
    /* We need this rest field to tell empty or full if front equals rear */
    uint32 rest;
    uint32 dim;
    void   **front;
    void   **rear;
    void   **base;
};

struct array_queue {
    struct array_queue_space space;
};

struct stacked_queue {
    uint32             sid;
    uint32             dim;
    struct array_stack *enter; /* enter stack */
    struct array_stack *leave; /* leave stack */
};

struct doubly_end_queue_list {
    void                      *val;
    struct doubly_linked_list link;
};

struct doubly_end_queue {
    uint32                       sid;
    struct doubly_end_queue_list *head;
    struct doubly_end_queue_list *tail;
};

struct collision_chain {
    struct doubly_linked_list *link;
    sint64                    nice;
};

struct binary_search_tree {
    struct collision_chain    chain;
    struct binary_search_tree *left;
    struct binary_search_tree *right;
};

struct avl_tree {
    sint32                    height;
    struct binary_search_tree alias;
};

struct splay_tree {
    struct binary_search_tree alias;
};

struct binary_indexed_tree {
    sint64 *data;
    uint32 size;
};

struct hashing_table {
    void       **space;
    uint32     size;
    uint32     load_factor;
    union {
        void   *func;
        uint32 (*separate_chain)(void *, uint32);
        uint32 (*open_addressing)(void *, uint32, uint32);
    };
};

struct separate_chain_hash {
    struct hashing_table *table;
};

struct open_addressing_hash {
    struct hashing_table *table;
};

struct heap_data {
    sint64 nice;
    void   *val;
};

struct binary_heap {
    struct heap_data **base;
    uint32 capacity;
    uint32 size;
};

struct minimal_heap {
    struct binary_heap *alias;
};

struct maximal_heap {
    struct binary_heap *alias;
};

struct min_max_heap {
    struct binary_heap *alias;
};

struct leftist_heap {
    sint32              npl; /* null path length, NULL node is -1 */
    struct heap_data    data;
    struct leftist_heap *left;
    struct leftist_heap *right;
};


extern bool doubly_linked_list_contains_p(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern bool single_linked_list_contains_p(struct single_linked_list *list, struct single_linked_list *node);
extern bool skip_linked_list_key_contains_p(struct skip_linked_list *list, sint32 key);
extern sint32 skip_linked_list_key(struct skip_linked_list *list);
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern struct doubly_linked_list * doubly_linked_list_next(struct doubly_linked_list *list);
extern struct doubly_linked_list * doubly_linked_list_node_by_index(struct doubly_linked_list *list, uint32 index);
extern struct doubly_linked_list * doubly_linked_list_node_copy(struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val);
extern struct doubly_linked_list * doubly_linked_list_previous(struct doubly_linked_list *list);
extern struct doubly_linked_list * doubly_linked_list_remove(struct doubly_linked_list **node);
extern struct single_linked_list * single_linked_list_create(void);
extern struct single_linked_list * single_linked_list_merge(struct single_linked_list *m, struct single_linked_list *n);
extern struct single_linked_list * single_linked_list_next(struct single_linked_list *list);
extern struct single_linked_list * single_linked_list_node_by_index(struct single_linked_list *list, uint32 index);
extern struct single_linked_list * single_linked_list_node_copy(struct single_linked_list *node);
extern struct single_linked_list * single_linked_list_node_create(void *val);
extern struct single_linked_list * single_linked_list_previous(struct single_linked_list *node);
extern struct single_linked_list * single_linked_list_remove(struct single_linked_list **node);
extern struct skip_linked_list * skip_linked_list_create(void);
extern struct skip_linked_list * skip_linked_list_find_key(struct skip_linked_list *list, sint32 key);
extern struct skip_linked_list * skip_linked_list_insert(struct skip_linked_list **list, struct skip_linked_list *tgt);
extern struct skip_linked_list * skip_linked_list_merge(struct skip_linked_list *m, struct skip_linked_list *n);
extern struct skip_linked_list * skip_linked_list_next(struct skip_linked_list *list);
extern struct skip_linked_list * skip_linked_list_node_by_index(struct skip_linked_list *list, uint32 index);
extern struct skip_linked_list * skip_linked_list_node_create(void *val, sint32 key);
extern struct skip_linked_list * skip_linked_list_remove(struct skip_linked_list **list, sint32 key);
extern uint32 doubly_linked_list_length(struct doubly_linked_list *list);
extern uint32 single_linked_list_length(struct single_linked_list *list);
extern uint32 skip_linked_list_length(struct skip_linked_list *list);
extern void * doubly_linked_list_val(struct doubly_linked_list *list);
extern void * single_linked_list_val(struct single_linked_list *list);
extern void * skip_linked_list_val(struct skip_linked_list *list);
extern void doubly_linked_list_destroy(struct doubly_linked_list **list);
extern void doubly_linked_list_initial(struct doubly_linked_list *list);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val);
extern void doubly_linked_list_insert_before(struct doubly_linked_list *list, void *val);
extern void doubly_linked_list_insert_ptr_after(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern void doubly_linked_list_insert_ptr_before(struct doubly_linked_list *list, struct doubly_linked_list *node);
extern void doubly_linked_list_iterate(struct doubly_linked_list *list, void (*handler)(void *));
extern void doubly_linked_list_next_set(struct doubly_linked_list *list, struct doubly_linked_list *next);
extern void doubly_linked_list_previous_set(struct doubly_linked_list *list, struct doubly_linked_list *previous);
extern void doubly_linked_list_remove_and_destroy(struct doubly_linked_list **node);
extern void doubly_linked_list_val_set(struct doubly_linked_list *list, void *val);
extern void single_linked_list_destroy(struct single_linked_list **list);
extern void single_linked_list_initial(struct single_linked_list *list);
extern void single_linked_list_insert_after(struct single_linked_list *list, void *val);
extern void single_linked_list_insert_before(struct single_linked_list *list, void *val);
extern void single_linked_list_insert_ptr_after(struct single_linked_list *list, struct single_linked_list *node);
extern void single_linked_list_insert_ptr_before(struct single_linked_list *list, struct single_linked_list *node);
extern void single_linked_list_iterate(struct single_linked_list *list, void (*handler)(void *));
extern void single_linked_list_next_set(struct single_linked_list *list, struct single_linked_list *next);
extern void single_linked_list_remove_and_destroy(struct single_linked_list **node);
extern void single_linked_list_val_set(struct single_linked_list *list, void *val);
extern void skip_linked_list_destroy(struct skip_linked_list **list);
extern void skip_linked_list_initial(struct skip_linked_list *list);
extern void skip_linked_list_iterate(struct skip_linked_list *list, void (*handler)(void *));
extern void skip_linked_list_key_set(struct skip_linked_list *list, sint32 key);
extern void skip_linked_list_next_set(struct skip_linked_list *list, void *val);
extern void skip_linked_list_remove_and_destroy(struct skip_linked_list **list, sint32 key);
extern void skip_linked_list_val_set(struct skip_linked_list *list, void *val);

extern bool array_queue_empty_p(struct array_queue *queue);
extern bool array_queue_full_p(struct array_queue *queue);
extern bool doubly_end_queue_empty_p(struct doubly_end_queue *queue);
extern bool stacked_queue_empty_p(struct stacked_queue *queue);
extern bool stacked_queue_full_p(struct stacked_queue *queue);
extern struct array_queue * array_queue_create(void);
extern struct doubly_end_queue * doubly_end_queue_create(void);
extern struct stacked_queue * stacked_queue_create(void);
extern uint32 array_queue_capacity(struct array_queue *queue);
extern uint32 array_queue_dim(struct array_queue *queue);
extern uint32 array_queue_rest(struct array_queue *queue);
extern uint32 doubly_end_queue_length(struct doubly_end_queue *queue);
extern uint32 stacked_queue_capacity(struct stacked_queue *queue);
extern uint32 stacked_queue_dim(struct stacked_queue *queue);
extern uint32 stacked_queue_space_rest(struct stacked_queue *queue);
extern void * array_queue_leave(struct array_queue *queue);
extern void * doubly_end_queue_head_leave(struct doubly_end_queue *queue);
extern void * doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
extern void * stacked_queue_leave(struct stacked_queue *queue);
extern void array_queue_cleanup(struct array_queue *queue);
extern void array_queue_destroy(struct array_queue **queue);
extern void array_queue_enter(struct array_queue *queue, void *member);
extern void array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
extern void array_queue_resize(struct array_queue *queue, uint32 size);
extern void doubly_end_queue_cleanup(struct doubly_end_queue *queue);
extern void doubly_end_queue_destroy(struct doubly_end_queue **queue);
extern void doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
extern void doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));
extern void doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
extern void stacked_queue_cleanup(struct stacked_queue *queue);
extern void stacked_queue_destroy(struct stacked_queue **queue);
extern void stacked_queue_enter(struct stacked_queue *queue, void *member);
extern void stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));
extern void stacked_queue_resize(struct stacked_queue *queue, uint32 dim);

extern bool array_stack_empty_p(struct array_stack *stack);
extern bool array_stack_full_p(struct array_stack *stack);
extern bool linked_stack_empty_p(struct linked_stack *stack);
extern bool linked_stack_full_p(struct linked_stack *stack);
extern struct array_stack * array_stack_create(void);
extern struct linked_stack * linked_stack_create(void);
extern uint32 array_stack_capacity(struct array_stack *stack);
extern uint32 array_stack_dim(struct array_stack *stack);
extern uint32 array_stack_rest(struct array_stack *stack);
extern uint32 linked_stack_capacity(struct linked_stack *stack);
extern uint32 linked_stack_rest(struct linked_stack *stack);
extern void * array_stack_pop(struct array_stack *stack);
extern void * linked_stack_pop(struct linked_stack *stack);
extern void array_stack_cleanup(struct array_stack *stack);
extern void array_stack_destroy(struct array_stack **stack);
extern void array_stack_iterate(struct array_stack *stack, void (*handler)(void *));
extern void array_stack_push(struct array_stack *stack, void *member);
extern void array_stack_resize(struct array_stack *stack, uint32 dim);
extern void linked_stack_cleanup(struct linked_stack *stack);
extern void linked_stack_destroy(struct linked_stack **stack);
extern void linked_stack_iterate(struct linked_stack *stack, void (*handler)(void *));
extern void linked_stack_push(struct linked_stack *stack, void *member);
extern void linked_stack_resize(struct linked_stack *stack, uint32 dim);

extern bool avl_tree_balanced_p(struct avl_tree *tree);
extern bool avl_tree_node_contains_p(struct avl_tree *tree, struct avl_tree *node);
extern bool binary_search_tree_node_contains_p(struct binary_search_tree *tree, struct binary_search_tree *node);
extern bool splay_tree_node_contains_p(struct splay_tree *tree, struct splay_tree *node);
extern sint32 avl_tree_height(struct avl_tree *tree);
extern sint32 binary_search_tree_height(struct binary_search_tree *tree);
extern sint32 splay_tree_height(struct splay_tree *tree);
extern sint64 avl_tree_node_nice(struct avl_tree *tree);
extern sint64 binary_indexed_tree_range_sum(struct binary_indexed_tree *tree, uint32 nmbr_s, uint32 nmbr_e);
extern sint64 binary_indexed_tree_sum(struct binary_indexed_tree *tree, uint32 number);
extern sint64 binary_indexed_tree_value(struct binary_indexed_tree *tree, uint32 number);
extern sint64 binary_search_tree_node_nice(struct binary_search_tree *tree);
extern sint64 splay_tree_node_nice(struct splay_tree *tree);
extern struct avl_tree * avl_tree_child_left(struct avl_tree *tree);
extern struct avl_tree * avl_tree_child_right(struct avl_tree *tree);
extern struct avl_tree * avl_tree_create(void);
extern struct avl_tree * avl_tree_node_create(void *val, sint64 nice);
extern struct avl_tree * avl_tree_node_find(struct avl_tree *tree, sint64 nice);
extern struct avl_tree * avl_tree_node_find_max(struct avl_tree *tree);
extern struct avl_tree * avl_tree_node_find_min(struct avl_tree *tree);
extern struct avl_tree * avl_tree_node_insert(struct avl_tree **tree, struct avl_tree *node);
extern struct avl_tree * avl_tree_node_remove(struct avl_tree **tree, sint64 nice);
extern struct avl_tree * avl_tree_ptr_binary_to_avl(struct binary_search_tree *node);
extern struct binary_indexed_tree * binary_indexed_tree_create(sint64 *data, uint32 size);
extern struct binary_search_tree  * binary_search_tree_node_find_min(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_child_left(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_child_right(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_create(void);
extern struct binary_search_tree * binary_search_tree_node_create(void *val, sint64 nice);
extern struct binary_search_tree * binary_search_tree_node_find(struct binary_search_tree *tree, sint64 nice);
extern struct binary_search_tree * binary_search_tree_node_find_max(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_node_insert(struct binary_search_tree *tree, struct binary_search_tree *node);
extern struct binary_search_tree * binary_search_tree_node_remove(struct binary_search_tree **tree, sint64 nice);
extern struct doubly_linked_list * avl_tree_node_link(struct avl_tree *tree);
extern struct doubly_linked_list * binary_search_tree_node_link(struct binary_search_tree *tree);
extern struct doubly_linked_list * splay_tree_node_link(struct splay_tree *tree);
extern struct splay_tree * splay_tree_child_left(struct splay_tree *tree);
extern struct splay_tree * splay_tree_child_right(struct splay_tree *tree);
extern struct splay_tree * splay_tree_create(void);
extern struct splay_tree * splay_tree_node_create(void *val, sint64 nice);
extern struct splay_tree * splay_tree_node_find(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_node_find_max(struct splay_tree **tree);
extern struct splay_tree * splay_tree_node_find_min(struct splay_tree **tree);
extern struct splay_tree * splay_tree_node_insert(struct splay_tree **tree, struct splay_tree *node);
extern struct splay_tree * splay_tree_node_remove(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_node_remove_internal(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_ptr_container_of(struct binary_search_tree *node);
extern uint32 binary_indexed_tree_size(struct binary_indexed_tree *tree);
extern void avl_tree_destroy(struct avl_tree **tree);
extern void avl_tree_height_set(struct avl_tree *tree, sint32 height);
extern void avl_tree_initial(struct avl_tree *tree);
extern void avl_tree_iterate(struct avl_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice);
extern void avl_tree_node_link_set(struct avl_tree *tree, struct doubly_linked_list *link);
extern void avl_tree_node_nice_set(struct avl_tree *tree, sint64 nice);
extern void avl_tree_node_remove_and_destroy(struct avl_tree **tree, sint64 nice);
extern void binary_indexed_tree_add(struct binary_indexed_tree *tree, uint32 number, sint64 val);
extern void binary_indexed_tree_destroy(struct binary_indexed_tree **tree);
extern void binary_indexed_tree_sub(struct binary_indexed_tree *tree, uint32 number, sint64 val);
extern void binary_search_tree_child_left_set(struct binary_search_tree *tree, struct binary_search_tree *left);
extern void binary_search_tree_child_right_set(struct binary_search_tree *tree, struct binary_search_tree *right);
extern void binary_search_tree_destroy(struct binary_search_tree **tree);
extern void binary_search_tree_initial(struct binary_search_tree *tree);
extern void binary_search_tree_iterate(struct binary_search_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void binary_search_tree_node_initial(struct binary_search_tree *node, void *val, sint64 nice);
extern void binary_search_tree_node_link_set(struct binary_search_tree *tree, struct doubly_linked_list *link);
extern void binary_search_tree_node_nice_set(struct binary_search_tree *tree, sint64 nice);
extern void binary_search_tree_node_remove_and_destroy(struct binary_search_tree **tree, sint64 nice);
extern void splay_tree_destroy(struct splay_tree **tree);
extern void splay_tree_initial(struct splay_tree *tree);
extern void splay_tree_iterate(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void splay_tree_node_initial(struct splay_tree *node, void *val, sint64 nice);
extern void splay_tree_node_nice_set(struct splay_tree *tree, sint64 nice);
extern void splay_tree_node_remove_and_destroy(struct splay_tree **tree, sint64 nice);

extern struct open_addressing_hash * open_addressing_hash_create(uint32 size);
extern struct open_addressing_hash * open_addressing_hash_rehashing(struct open_addressing_hash **hash);
extern struct separate_chain_hash * separate_chain_hash_create(uint32 size);
extern struct separate_chain_hash * separate_chain_hash_rehashing(struct separate_chain_hash **hash);
extern uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 iter);
extern uint32 hashing_function_polynomial(void *key, uint32 size);
extern uint32 open_addressing_hash_load_factor(struct open_addressing_hash *hash);
extern uint32 open_addressing_hash_load_factor_calculate(struct open_addressing_hash *hash);
extern uint32 open_addressing_hash_size(struct open_addressing_hash *hash);
extern uint32 separate_chain_hash_load_factor(struct separate_chain_hash *hash);
extern uint32 separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash);
extern uint32 separate_chain_hash_size(struct separate_chain_hash *hash);
extern void * open_addressing_hash_find(struct open_addressing_hash *hash, void *key);
extern void * open_addressing_hash_remove(struct open_addressing_hash *hash, void *key);
extern void * separate_chain_hash_find(struct separate_chain_hash *hash, void *key);
extern void * separate_chain_hash_remove(struct separate_chain_hash *hash, void *key);
extern void open_addressing_hash_destroy(struct open_addressing_hash **hash);
extern void open_addressing_hash_insert(struct open_addressing_hash **hash, void *key);
extern void separate_chain_hash_destroy(struct separate_chain_hash **hash);
extern void separate_chain_hash_insert(struct separate_chain_hash **hash, void *key);

extern bool maximal_heap_empty_p(struct maximal_heap *heap);
extern bool maximal_heap_full_p(struct maximal_heap *heap);
extern bool min_max_heap_empty_p(struct min_max_heap *heap);
extern bool min_max_heap_empty_p_internal(struct min_max_heap *heap);
extern bool min_max_heap_full_p(struct min_max_heap *heap);
extern bool minimal_heap_empty_p(struct minimal_heap *heap);
extern bool minimal_heap_full_p(struct minimal_heap *heap);
extern sint32 leftist_heap_npl(struct leftist_heap *heap);
extern sint64 leftist_heap_nice(struct leftist_heap *heap);
extern sint64 maximal_heap_nice(struct maximal_heap *heap, uint32 index);
extern sint64 min_max_heap_nice(struct min_max_heap *heap, uint32 index);
extern sint64 minimal_heap_nice(struct minimal_heap *heap, uint32 index);
extern struct doubly_linked_list * min_max_heap_remove(struct min_max_heap *heap, uint32 index);
extern struct leftist_heap * leftist_heap_create(void);
extern struct leftist_heap * leftist_heap_insert(struct leftist_heap *heap, void *val, sint64 nice);
extern struct leftist_heap * leftist_heap_left(struct leftist_heap *heap);
extern struct leftist_heap * leftist_heap_merge(struct leftist_heap *heap, struct leftist_heap *merge);
extern struct leftist_heap * leftist_heap_node_create(void *val, sint32 nlp, sint64 nice);
extern struct leftist_heap * leftist_heap_remove_min(struct leftist_heap **heap);
extern struct leftist_heap * leftist_heap_right(struct leftist_heap *heap);
extern struct maximal_heap * maximal_heap_build(struct heap_data **hd_array, uint32 size);
extern struct maximal_heap * maximal_heap_create(uint32 capacity);
extern struct min_max_heap * min_max_heap_create(uint32 capacity);
extern struct minimal_heap * minimal_heap_build(struct heap_data **hd_array, uint32 size);
extern struct minimal_heap * minimal_heap_create(uint32 capacity);
extern uint32 maximal_heap_index_last(struct maximal_heap *heap);
extern uint32 maximal_heap_index_limit(struct maximal_heap *heap);
extern uint32 maximal_heap_size(struct maximal_heap *heap);
extern uint32 min_max_heap_depth(struct min_max_heap *heap, uint32 index);
extern uint32 min_max_heap_index_last(struct min_max_heap *heap);
extern uint32 min_max_heap_index_limit(struct min_max_heap *heap);
extern uint32 min_max_heap_size(struct min_max_heap *heap);
extern uint32 minimal_heap_index_last(struct minimal_heap *heap);
extern uint32 minimal_heap_index_limit(struct minimal_heap *heap);
extern uint32 minimal_heap_size(struct minimal_heap *heap);
extern void * leftist_heap_get_min(struct leftist_heap *heap);
extern void * leftist_heap_val(struct leftist_heap *heap);
extern void * maximal_heap_get_max(struct maximal_heap *heap);
extern void * maximal_heap_remove(struct maximal_heap *heap, uint32 index);
extern void * maximal_heap_remove_max(struct maximal_heap *heap);
extern void * maximal_heap_val(struct maximal_heap *heap, uint32 index);
extern void * min_max_heap_get_max(struct min_max_heap *heap);
extern void * min_max_heap_get_min(struct min_max_heap *heap);
extern void * min_max_heap_remove_max(struct min_max_heap *heap);
extern void * min_max_heap_remove_min(struct min_max_heap *heap);
extern void * min_max_heap_val(struct min_max_heap *heap, uint32 index);
extern void * minimal_heap_get_min(struct minimal_heap *heap);
extern void * minimal_heap_remove(struct minimal_heap *heap, uint32 index);
extern void * minimal_heap_remove_min(struct minimal_heap *heap);
extern void * minimal_heap_val(struct minimal_heap *heap, uint32 index);
extern void leftist_heap_destroy(struct leftist_heap **heap);
extern void leftist_heap_nice_set(struct leftist_heap *heap, sint64 nice);
extern void leftist_heap_npl_set(struct leftist_heap *heap, sint32 npl);
extern void leftist_heap_remove_min_and_destroy(struct leftist_heap **heap);
extern void leftist_heap_val_set(struct leftist_heap *heap, void *val);
extern void maximal_heap_cleanup(struct maximal_heap *heap);
extern void maximal_heap_decrease_nice(struct maximal_heap *heap, uint32 index, uint32 offset);
extern void maximal_heap_destroy(struct maximal_heap **heap);
extern void maximal_heap_increase_nice(struct maximal_heap *heap, uint32 index, uint32 offset);
extern void maximal_heap_insert(struct maximal_heap *heap, void *val, sint64 nice);
extern void min_max_heap_cleanup(struct min_max_heap *heap);
extern void min_max_heap_decrease_nice(struct min_max_heap *heap, uint32 index, uint32 offset);
extern void min_max_heap_destroy(struct min_max_heap **heap);
extern void min_max_heap_increase_nice(struct min_max_heap *heap, uint32 index, uint32 offset);
extern void min_max_heap_insert(struct min_max_heap *heap, void *val, sint64 nice);
extern void minimal_heap_cleanup(struct minimal_heap *heap);
extern void minimal_heap_decrease_nice(struct minimal_heap *heap, uint32 index, uint32 offset);
extern void minimal_heap_destroy(struct minimal_heap **heap);
extern void minimal_heap_increase_nice(struct minimal_heap *heap, uint32 index, uint32 offset);
extern void minimal_heap_insert(struct minimal_heap *heap, void *val, sint64 nice);

extern bool sort_data_sorted_p(void *data, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
extern void heap_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
extern void insertion_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
extern void merge_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
extern void quick_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
extern void shell_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));


#endif

