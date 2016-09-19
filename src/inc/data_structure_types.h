#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

#define true                   1
#define false                  0
#define SIZE_INVALID           0xffffffffu
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
#define BIN_IDXED_NMBR_INVALID 0          // binary indexed tree invalid number
#define BIN_IDXED_SUM_INVALID  (sint64)(1ull << 63)
#define TREE_NICE_INVALID      (sint64)(-1)

#define PTR_INVALID            (void *)-1 // invalid pointer
// New-Line

#define HEAP_IDX_CHILD_L(x)    ((x) * 2)
#define HEAP_IDX_CHILD_R(x)    ((x) * 2 + 1)
// New-Line

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
typedef struct binary_search_tree    s_binary_search_tree_t;
typedef struct avl_tree              s_avl_tree_t;
typedef struct splay_tree            s_splay_tree_t;
typedef struct heap_data             s_heap_data_t;
typedef struct binary_heap           s_binary_heap_t;
typedef struct leftist_heap          s_leftist_heap_t;
typedef struct binary_indexed_tree   s_binary_indexed_tree_t;
typedef enum ITER_ORDER              e_iter_order_t;

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
    s_single_linked_list_t *next;
};

struct doubly_linked_list {
    s_doubly_linked_list_t *next;
    s_doubly_linked_list_t *previous;
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
struct skip_linked_list {
    sint32 key;
    union {
        s_skip_linked_list_t *next;
        s_skip_linked_list_t *layer[SKIP_LVL_LMT];
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
    s_array_stack_space_t space;
};

/*
 * linked stack space
 */
struct linked_stack_space {
    s_array_stack_space_t  space;
    s_doubly_linked_list_t link;
};

/*
 * linked stack
 */
struct linked_stack {
    s_linked_stack_space_t *base;
    s_linked_stack_space_t *top;
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
    s_array_queue_space_t space;
};

/*
 * stacked queue
 */
struct stacked_queue {
    uint32          dim;
    s_array_stack_t *enter; /* enter stack */
    s_array_stack_t *leave; /* leave stack */
};

/*
 * doubly_end_queue_list
 */
struct doubly_end_queue_list {
    void                   *val;
    s_doubly_linked_list_t link;
};

/*
 * doubly end queue
 */
struct doubly_end_queue {
    s_doubly_end_queue_list_t *front;
    s_doubly_end_queue_list_t *rear;
};

/*
 * binary search tree
 */
struct binary_search_tree {
    sint64                 nice;
    s_binary_search_tree_t *left;
    s_binary_search_tree_t *right;
};

/*
 * avl tree
 */
struct avl_tree {
    sint32       height;
    sint64       nice;
    s_avl_tree_t *left;
    s_avl_tree_t *right;
};

/*
 * splay tree
 */
struct splay_tree {
    sint64         nice;
    s_splay_tree_t *left;
    s_splay_tree_t *right;
};

/*
 * binary indexed tree
 *     One kind of data structure provding efficient method
 * for prefix sum of an array values. It provides:
 *     sum(index);
 *     range_sum(index);
 *     add(index, val);
 *     sub(index, val);
 *     create();
 *     destroy();
 * with log(N) time cost.
 *
 * For example:
 * A[1] -> C[1] = A[1]
 * A[2] -> C[2] = A[1] + A[2]
 * A[3] -> C[3] = A[3]
 * A[4] -> C[4] = A[1] + A[2] + A[3] + A[4]
 * A[5] -> C[5] = A[5]
 * A[6] -> C[6] = A[5] + A[6]
 * A[7] -> C[7] = A[7]
 * A[8] -> C[8] = A[1] + A[2] + A[3] + A[4] + A[5] + A[6] + A[7] + A[8]
 */
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

struct separate_chain {
    void                   *val;
    s_doubly_linked_list_t list;
};

/*
 * hashing table with separate chaining
 */
struct separate_chain_hash {
    s_hashing_table_t *table;
};

/*
 * hashing table with open addressing square
 */
struct open_addressing_hash {
    s_hashing_table_t *table;
};

/*
 * Hold all data heap stored
 */
struct heap_data {
    sint64 nice;
    void   *val;
};

/*
 * generate heap
 * allow different node with the same nice
 */
struct binary_heap {
    s_heap_data_t **base;
    uint32 capacity;
    uint32 size;
};

/*
 * min heap
 */
struct minimal_heap {
    s_binary_heap_t *alias;
};

/*
 * max heap
 */
struct maximal_heap {
    s_binary_heap_t *alias;
};

/*
 * min-max heap, root have 0 depth
 *     for even depth node, < fater, > gdp_randfater
 *     for odd  depth node, > fater, < gdp_randfater
 */
struct min_max_heap {
    s_binary_heap_t *alias;
};

/*
 * leftist heap
 *     <null path length>, the shortest length from one node to other node
 *     who hasn't two child.
 *     Foreach node in leftist heap, the <null path length> of left child >=
 *     the <null path length> of right child.
 *     This structure can finish heap merge in O(N).
 *     For example:
 *           4<1>
 *          /    \
 *         7<1>   9<0>
 *        /    \
 *       12<0>  18<0>
 *             /
 *            21<0>
 * Note: unlike binary search tree, leftist heap allow repeated nice.
 *       So there is not collision chain concept here, just reuse the
 *       structure binary search tree.
 */
struct leftist_heap {
    sint32           npl; /* null path length, NULL node is -1 */
    s_heap_data_t    data;
    s_leftist_heap_t *left;
    s_leftist_heap_t *right;
};

#endif

