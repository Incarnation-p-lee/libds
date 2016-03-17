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

/*
 * binary indexed tree
 *     One kind of data structure provding efficient method
 * for prefix sum of an array values. It provides:
 *     sum(index);
 *     add(index, val);
 *     sub(index, val);
 *     read(index)
 *     scaling();
 *     find(value);
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
    struct heap_data **base;
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
    sint32              npl; /* null path length, NULL node is -1 */
    struct heap_data    data;
    struct leftist_heap *left;
    struct leftist_heap *right;
};

#endif

