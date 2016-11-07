#ifndef HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H
#define HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H

// Automaticaly generated by script/produce_data_structure_interface_h.pl.

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

enum log_level {
    INFO,
    WARN,
    DBUG,
    ERRR,
};


#define true                   1
#define false                  0
#define SIZE_INVALID           0xffffffffu
#define TRIE_INDEX_INVALID     SIZE_INVALID
#define LIST_SIZE_INVALID      SIZE_INVALID
#define SKIP_LVL_LMT           8          // skip linked list level limitation
#define SKIP_KEY_INVALID       (sint32)0x80000000
#define SPT_CHN_HASH_SIZE_DFT  11u        // separate chain hash default size
#define SPT_CHN_HASH_LOAD_FTR  72u        // separate chain hash load factor
#define OPN_ADDR_HASH_LOAD_FTR 50u        // open addressing hash load factor
#define HASH_SIZE_INVALID      SIZE_INVALID
#define HASH_IDX_INVALID       0xffffffffu
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
#define TRIE_TREE_ROOT         -1         // Root node val of trie tree
#define TRIE_TREE_SIZE_MIN     16         // Minimal sub tree size of trie tree
#define BIN_IDXED_NMBR_INVALID 0          // binary indexed tree invalid number
#define BIN_IDXED_SUM_INVALID  (sint64)(1ull << 63)
#define PTR_INVALID            (void *)-1 // invalid pointer
#define HEAP_IDX_CHILD_L(x)    ((x) * 2)
#define HEAP_IDX_CHILD_R(x)    ((x) * 2 + 1)
typedef struct single_linked_list    s_single_linked_list_t;
typedef struct doubly_linked_list    s_doubly_linked_list_t;
typedef struct skip_linked_list      s_skip_linked_list_t;
typedef struct separate_chain_hash   s_separate_chain_hash_t;
typedef struct open_addressing_hash  s_open_addressing_hash_t;
typedef struct hashing_table         s_hashing_table_t;
typedef struct separate_chain        s_separate_chain_t;
typedef struct open_addressing_hash  s_open_addressing_hash_t;
typedef struct array_stack           s_array_stack_t;
typedef struct array_stack_space     s_array_stack_space_t;
typedef struct linked_stack_space    s_linked_stack_space_t;
typedef struct linked_stack          s_linked_stack_t;
typedef struct array_queue_space     s_array_queue_space_t;
typedef struct array_queue           s_array_queue_t;
typedef struct stacked_queue         s_stacked_queue_t;
typedef struct doubly_end_queue      s_doubly_end_queue_t;
typedef struct doubly_end_queue_list s_doubly_end_queue_list_t;
typedef struct trie_tree             s_trie_tree_t;
typedef struct array_iterator        s_array_iterator_t;
typedef void   (*f_array_iterator_initial_t)(void *);
typedef bool   (*f_array_iterator_next_exist_t)(void *);
typedef void * (*f_array_iterator_next_obtain_t)(void *);

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

struct array_iterator {
    uint32                         index;
    f_array_iterator_initial_t     fp_index_initial;
    f_array_iterator_next_exist_t  fp_next_exist_p;
    f_array_iterator_next_obtain_t fp_next_obtain;
};

struct single_linked_list {
    struct single_linked_list *next;
};

struct doubly_linked_list {
    struct doubly_linked_list *next;
    struct doubly_linked_list *previous;
};

struct skip_linked_list {
    sint32 key;
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
    s_array_iterator_t       iterator;
};

struct stacked_queue {
    uint32             dim;
    struct array_stack *enter; /* enter stack */
    struct array_stack *leave; /* leave stack */
};

struct doubly_end_queue_list {
    void                      *val;
    struct doubly_linked_list link;
};

struct doubly_end_queue {
    struct doubly_end_queue_list *front;
    struct doubly_end_queue_list *rear;
};

struct collision_chain {
    struct doubly_linked_list *link;
    sint64                    nice;
};

struct binary_search_tree {
    sint64                    nice;
    struct binary_search_tree *left;
    struct binary_search_tree *right;
};

struct avl_tree {
    sint32          height;
    sint64          nice;
    struct avl_tree *left;
    struct avl_tree *right;
};

struct splay_tree {
    sint64            nice;
    struct splay_tree *left;
    struct splay_tree *right;
};

struct binary_indexed_tree {
    sint64 *data;
    uint32 size;
};

struct trie_tree {
    bool            is_deleted;
    bool            is_terminal;
    uint32          val;
    s_array_queue_t *sub_queue;
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

struct separate_chain {
    void                   *val;
    s_doubly_linked_list_t list;
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


extern bool array_iterator_structure_legal_p(s_array_iterator_t *iterator);
extern bool complain_no_memory_p(void *ptr);
extern bool complain_null_pointer_p(void *ptr);
extern bool complain_null_string_p(char *string);
extern bool complain_zero_size_p(uint32 size);
extern s_array_iterator_t * array_iterator_create(void);
extern sint64 random_sint64(void);
extern uint32 * convert_string_to_uint32_array(char *string, uint32 *len);
extern uint32 * random_sequence_uint32_limited_obtain(uint32 len, uint32 limit);
extern uint32 * random_sequence_uint32_obtain(uint32 len);
extern uint32 prime_numeral_next(uint32 prime);
extern uint32 random_uint32_with_limit(uint32 limit);
extern void * malloc_wrap(uint32 size);
extern void * memory_cache_allocate(uint32 size);
extern void * memory_cache_re_allocate(void *addr, uint32 size);
extern void * realloc_wrap(void *ptr, uint32 size);
extern void array_iterator_destroy(s_array_iterator_t *iterator);
extern void array_iterator_initial(s_array_iterator_t *iterator, f_array_iterator_initial_t fp_index_initial, f_array_iterator_next_exist_t fp_next_exist_p, f_array_iterator_next_obtain_t fp_next_obtain);
extern void complain_assert_caution(char *msg, const char *fname, const char *func, uint32 line);
extern void complain_assert_exit(char *msg, const char *fname, const char *func, uint32 line);
extern void free_wrap(void *ptr);
extern void libds_log_file_close(void);
extern void libds_log_file_create(void);
extern void libds_log_print(enum log_level lvl, const char *msg);
extern void memory_cache_cleanup(void);
extern void memory_cache_free(void *addr);
extern void random_sequence_drop(uint32 *sequence);

extern bool doubly_linked_list_contains_p(s_doubly_linked_list_t *list, s_doubly_linked_list_t *node);
extern bool doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list);
extern bool single_linked_list_contains_p(s_single_linked_list_t *list, s_single_linked_list_t *node);
extern bool single_linked_list_structure_legal_p(s_single_linked_list_t *list);
extern bool skip_linked_list_contains_p(s_skip_linked_list_t *list, s_skip_linked_list_t *node);
extern bool skip_linked_list_structure_legal_p(s_skip_linked_list_t *list);
extern s_doubly_linked_list_t * doubly_linked_list_create(void);
extern s_doubly_linked_list_t * doubly_linked_list_merge(s_doubly_linked_list_t *m, s_doubly_linked_list_t *n);
extern s_doubly_linked_list_t * doubly_linked_list_next(s_doubly_linked_list_t *list);
extern s_doubly_linked_list_t * doubly_linked_list_node_by_index(s_doubly_linked_list_t *list, uint32 index);
extern s_doubly_linked_list_t * doubly_linked_list_node_copy(s_doubly_linked_list_t *node);
extern s_doubly_linked_list_t * doubly_linked_list_previous(s_doubly_linked_list_t *list);
extern s_doubly_linked_list_t * doubly_linked_list_remove(s_doubly_linked_list_t **list);
extern s_single_linked_list_t * single_linked_list_create(void);
extern s_single_linked_list_t * single_linked_list_merge(s_single_linked_list_t *m, s_single_linked_list_t *n);
extern s_single_linked_list_t * single_linked_list_next(s_single_linked_list_t *list);
extern s_single_linked_list_t * single_linked_list_node_by_index(s_single_linked_list_t *list, uint32 index);
extern s_single_linked_list_t * single_linked_list_node_copy(s_single_linked_list_t *node);
extern s_single_linked_list_t * single_linked_list_previous(s_single_linked_list_t *list);
extern s_single_linked_list_t * single_linked_list_remove(s_single_linked_list_t **list);
extern s_skip_linked_list_t * skip_linked_list_create(void);
extern s_skip_linked_list_t * skip_linked_list_create_with_key(sint32 key);
extern s_skip_linked_list_t * skip_linked_list_find_key(s_skip_linked_list_t *list, sint32 key);
extern s_skip_linked_list_t * skip_linked_list_insert(s_skip_linked_list_t **list, s_skip_linked_list_t *tgt);
extern s_skip_linked_list_t * skip_linked_list_merge(s_skip_linked_list_t *m, s_skip_linked_list_t *n);
extern s_skip_linked_list_t * skip_linked_list_next(s_skip_linked_list_t *list);
extern s_skip_linked_list_t * skip_linked_list_node_by_index(s_skip_linked_list_t *list, uint32 index);
extern s_skip_linked_list_t * skip_linked_list_remove(s_skip_linked_list_t **list, s_skip_linked_list_t *tgt);
extern sint32 skip_linked_list_key(s_skip_linked_list_t *list);
extern uint32 doubly_linked_list_length(s_doubly_linked_list_t *list);
extern uint32 single_linked_list_length(s_single_linked_list_t *list);
extern uint32 skip_linked_list_length(s_skip_linked_list_t *list);
extern void doubly_linked_list_destroy(s_doubly_linked_list_t **list);
extern void doubly_linked_list_initial(s_doubly_linked_list_t *list);
extern void doubly_linked_list_insert_after(s_doubly_linked_list_t *list, s_doubly_linked_list_t *node);
extern void doubly_linked_list_insert_before(s_doubly_linked_list_t *list, s_doubly_linked_list_t *node);
extern void doubly_linked_list_iterate(s_doubly_linked_list_t *list, void (*handler)(void *));
extern void doubly_linked_list_next_set(s_doubly_linked_list_t *list, s_doubly_linked_list_t *next);
extern void doubly_linked_list_previous_set(s_doubly_linked_list_t *list, s_doubly_linked_list_t *previous);
extern void single_linked_list_destroy(s_single_linked_list_t **list);
extern void single_linked_list_initial(s_single_linked_list_t *list);
extern void single_linked_list_insert_after(s_single_linked_list_t *list, s_single_linked_list_t *node);
extern void single_linked_list_insert_before(s_single_linked_list_t *list, s_single_linked_list_t *node);
extern void single_linked_list_iterate(s_single_linked_list_t *list, void (*handler)(void *));
extern void single_linked_list_next_set(s_single_linked_list_t *list, s_single_linked_list_t *next);
extern void skip_linked_list_destroy(s_skip_linked_list_t **list);
extern void skip_linked_list_initial(s_skip_linked_list_t *list);
extern void skip_linked_list_iterate(s_skip_linked_list_t *list, void (*handler)(void *));
extern void skip_linked_list_key_set(s_skip_linked_list_t *list, sint32 key);
extern void skip_linked_list_next_set(s_skip_linked_list_t *list, s_skip_linked_list_t *next);

extern bool array_queue_empty_p(s_array_queue_t *queue);
extern bool array_queue_full_p(s_array_queue_t *queue);
extern bool array_queue_structure_legal_p(s_array_queue_t *queue);
extern bool doubly_end_queue_empty_p(s_doubly_end_queue_t *queue);
extern bool doubly_end_queue_structure_legal_p(s_doubly_end_queue_t *queue);
extern bool stacked_queue_empty_p(s_stacked_queue_t *queue);
extern bool stacked_queue_full_p(s_stacked_queue_t *queue);
extern s_array_iterator_t * array_queue_iterator_obtain(s_array_queue_t *queue);
extern s_array_queue_t * array_queue_create(void);
extern s_doubly_end_queue_t * doubly_end_queue_create(void);
extern s_stacked_queue_t * stacked_queue_create(void);
extern uint32 array_queue_capacity(s_array_queue_t *queue);
extern uint32 array_queue_rest(s_array_queue_t *queue);
extern uint32 doubly_end_queue_length(s_doubly_end_queue_t *queue);
extern uint32 stacked_queue_capacity(s_stacked_queue_t *queue);
extern uint32 stacked_queue_rest(s_stacked_queue_t *queue);
extern void * array_queue_front(s_array_queue_t *queue);
extern void * array_queue_leave(s_array_queue_t *queue);
extern void * array_queue_rear(s_array_queue_t *queue);
extern void * doubly_end_queue_front(s_doubly_end_queue_t *queue);
extern void * doubly_end_queue_front_leave(s_doubly_end_queue_t *queue);
extern void * doubly_end_queue_rear(s_doubly_end_queue_t *queue);
extern void * doubly_end_queue_rear_leave(s_doubly_end_queue_t *queue);
extern void * stacked_queue_front(s_stacked_queue_t *queue);
extern void * stacked_queue_leave(s_stacked_queue_t *queue);
extern void * stacked_queue_rear(s_stacked_queue_t *queue);
extern void array_queue_cleanup(s_array_queue_t *queue);
extern void array_queue_destroy(s_array_queue_t **queue);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void array_queue_iterate(s_array_queue_t *queue, void (*handler)(void *));
extern void array_queue_resize(s_array_queue_t *queue, uint32 size);
extern void doubly_end_queue_cleanup(s_doubly_end_queue_t *queue);
extern void doubly_end_queue_destroy(s_doubly_end_queue_t **queue);
extern void doubly_end_queue_front_enter(s_doubly_end_queue_t *queue, void *member);
extern void doubly_end_queue_iterate(s_doubly_end_queue_t *queue, void (*handle)(void *));
extern void doubly_end_queue_rear_enter(s_doubly_end_queue_t *queue, void *member);
extern void stacked_queue_cleanup(s_stacked_queue_t *queue);
extern void stacked_queue_destroy(s_stacked_queue_t **queue);
extern void stacked_queue_enter(s_stacked_queue_t *queue, void *member);
extern void stacked_queue_iterate(s_stacked_queue_t *queue, void (*handler)(void *));
extern void stacked_queue_resize(s_stacked_queue_t *queue, uint32 dim);

extern bool array_stack_empty_p(s_array_stack_t *stack);
extern bool array_stack_full_p(s_array_stack_t *stack);
extern bool array_stack_space_structure_legal_p(s_array_stack_space_t *space);
extern bool array_stack_structure_legal_p(s_array_stack_t *stack);
extern bool linked_stack_empty_p(s_linked_stack_t *stack);
extern bool linked_stack_full_p(s_linked_stack_t *stack);
extern bool linked_stack_structure_legal_p(s_linked_stack_t *stack);
extern s_array_stack_t * array_stack_create(void);
extern s_linked_stack_t * linked_stack_create(void);
extern uint32 array_stack_capacity(s_array_stack_t *stack);
extern uint32 array_stack_rest(s_array_stack_t *stack);
extern uint32 array_stack_size(s_array_stack_t *stack);
extern uint32 linked_stack_capacity(s_linked_stack_t *stack);
extern uint32 linked_stack_rest(s_linked_stack_t *stack);
extern void * array_stack_pop(s_array_stack_t *stack);
extern void * array_stack_top(s_array_stack_t *stack);
extern void * linked_stack_pop(s_linked_stack_t *stack);
extern void * linked_stack_top(s_linked_stack_t *stack);
extern void array_stack_cleanup(s_array_stack_t *stack);
extern void array_stack_destroy(s_array_stack_t **stack);
extern void array_stack_iterate(s_array_stack_t *stack, void (*handler)(void *));
extern void array_stack_push(s_array_stack_t *stack, void *member);
extern void array_stack_resize(s_array_stack_t *stack, uint32 dim);
extern void linked_stack_cleanup(s_linked_stack_t *stack);
extern void linked_stack_destroy(s_linked_stack_t **stack);
extern void linked_stack_iterate(s_linked_stack_t *stack, void (*handler)(void *));
extern void linked_stack_push(s_linked_stack_t *stack, void *member);
extern void linked_stack_resize(s_linked_stack_t *stack, uint32 dim);

extern bool avl_tree_balanced_p(struct avl_tree *tree);
extern bool avl_tree_contains_p(struct avl_tree *tree, struct avl_tree *node);
extern bool binary_search_tree_contains_p(struct binary_search_tree *tree, struct binary_search_tree *node);
extern bool splay_tree_contains_p(struct splay_tree *tree, struct splay_tree *node);
extern bool trie_tree_sequence_matched_p(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
extern bool trie_tree_string_matched_p(s_trie_tree_t *trie, char *string);
extern bool trie_tree_structure_legal_p(s_trie_tree_t *trie);
extern s_trie_tree_t * trie_tree_create(void);
extern sint32 avl_tree_height(struct avl_tree *tree);
extern sint32 binary_search_tree_height(struct binary_search_tree *tree);
extern sint32 splay_tree_height(struct splay_tree *tree);
extern sint64 avl_tree_nice(struct avl_tree *tree);
extern sint64 binary_indexed_tree_range_sum(struct binary_indexed_tree *tree, uint32 nmbr_s, uint32 nmbr_e);
extern sint64 binary_indexed_tree_sum(struct binary_indexed_tree *tree, uint32 number);
extern sint64 binary_indexed_tree_value(struct binary_indexed_tree *tree, uint32 number);
extern sint64 binary_search_tree_nice(struct binary_search_tree *tree);
extern sint64 splay_tree_nice(struct splay_tree *tree);
extern struct avl_tree * avl_tree_create(void);
extern struct avl_tree * avl_tree_find(struct avl_tree *tree, sint64 nice);
extern struct avl_tree * avl_tree_find_max(struct avl_tree *tree);
extern struct avl_tree * avl_tree_find_min(struct avl_tree *tree);
extern struct avl_tree * avl_tree_insert(struct avl_tree **tree, struct avl_tree *node);
extern struct avl_tree * avl_tree_left(struct avl_tree *tree);
extern struct avl_tree * avl_tree_remove(struct avl_tree **tree, struct avl_tree *node);
extern struct avl_tree * avl_tree_right(struct avl_tree *tree);
extern struct binary_indexed_tree * binary_indexed_tree_create(sint64 *data, uint32 size);
extern struct binary_search_tree  * binary_search_tree_find_min(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_create(void);
extern struct binary_search_tree * binary_search_tree_find(struct binary_search_tree *tree, sint64 nice);
extern struct binary_search_tree * binary_search_tree_find_max(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_insert(struct binary_search_tree **tree, struct binary_search_tree *node);
extern struct binary_search_tree * binary_search_tree_left(struct binary_search_tree *tree);
extern struct binary_search_tree * binary_search_tree_remove(struct binary_search_tree **tree, struct binary_search_tree *node);
extern struct binary_search_tree * binary_search_tree_right(struct binary_search_tree *tree);
extern struct splay_tree * splay_tree_create(void);
extern struct splay_tree * splay_tree_find(struct splay_tree **tree, sint64 nice);
extern struct splay_tree * splay_tree_find_max(struct splay_tree **tree);
extern struct splay_tree * splay_tree_find_min(struct splay_tree **tree);
extern struct splay_tree * splay_tree_insert(struct splay_tree **tree, struct splay_tree *node);
extern struct splay_tree * splay_tree_left(struct splay_tree *tree);
extern struct splay_tree * splay_tree_remove(struct splay_tree **tree, struct splay_tree *node);
extern struct splay_tree * splay_tree_right(struct splay_tree *tree);
extern uint32 binary_indexed_tree_size(struct binary_indexed_tree *tree);
extern void avl_tree_destroy(struct avl_tree **tree);
extern void avl_tree_height_set(struct avl_tree *tree, sint32 height);
extern void avl_tree_initial(struct avl_tree *tree, sint64 nice);
extern void avl_tree_iterate(struct avl_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void avl_tree_nice_set(struct avl_tree *tree, sint64 nice);
extern void binary_indexed_tree_add(struct binary_indexed_tree *tree, uint32 number, sint64 val);
extern void binary_indexed_tree_destroy(struct binary_indexed_tree **tree);
extern void binary_indexed_tree_sub(struct binary_indexed_tree *tree, uint32 number, sint64 val);
extern void binary_search_tree_destroy(struct binary_search_tree **tree);
extern void binary_search_tree_initial(struct binary_search_tree *tree, sint64 nice);
extern void binary_search_tree_iterate(struct binary_search_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void binary_search_tree_left_set(struct binary_search_tree *tree, struct binary_search_tree *left);
extern void binary_search_tree_node_nice_set(struct binary_search_tree *tree, sint64 nice);
extern void binary_search_tree_right_set(struct binary_search_tree *tree, struct binary_search_tree *right);
extern void splay_tree_destroy(struct splay_tree **tree);
extern void splay_tree_initial(struct splay_tree *tree, sint64 nice);
extern void splay_tree_iterate(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
extern void splay_tree_nice_set(struct splay_tree *tree, sint64 nice);
extern void trie_tree_destroy(s_trie_tree_t **trie);
extern void trie_tree_sequence_insert(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
extern void trie_tree_sequence_remove(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
extern void trie_tree_string_insert(s_trie_tree_t *trie, char *string);
extern void trie_tree_string_remove(s_trie_tree_t *trie, char *string);

extern s_open_addressing_hash_t * open_addressing_hash_create(uint32 size);
extern s_separate_chain_hash_t * separate_chain_hash_create(uint32 size);
extern uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 counter);
extern uint32 hashing_function_polynomial(void *key, uint32 size);
extern uint32 open_addressing_hash_load_factor(s_open_addressing_hash_t *hash);
extern uint32 open_addressing_hash_load_factor_calculate(s_open_addressing_hash_t *hash);
extern uint32 open_addressing_hash_size(s_open_addressing_hash_t *hash);
extern uint32 separate_chain_hash_load_factor(s_separate_chain_hash_t *hash);
extern uint32 separate_chain_hash_load_factor_calculate(s_separate_chain_hash_t *hash);
extern uint32 separate_chain_hash_size(s_separate_chain_hash_t *hash);
extern void * open_addressing_hash_find(s_open_addressing_hash_t *hash, void *key);
extern void * open_addressing_hash_insert(s_open_addressing_hash_t *hash, void *key);
extern void * open_addressing_hash_insert_i(s_open_addressing_hash_t *hash, void *key);
extern void * open_addressing_hash_remove(s_open_addressing_hash_t *hash, void *key);
extern void * separate_chain_hash_find(s_separate_chain_hash_t *hash, void *key);
extern void * separate_chain_hash_insert(s_separate_chain_hash_t *hash, void *key);
extern void * separate_chain_hash_remove(s_separate_chain_hash_t *hash, void *key);
extern void open_addressing_hash_destroy(s_open_addressing_hash_t **hash);
extern void open_addressing_hash_rehashing(s_open_addressing_hash_t *hash);
extern void separate_chain_hash_destroy(s_separate_chain_hash_t **hash);
extern void separate_chain_hash_rehashing(s_separate_chain_hash_t *hash);

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
