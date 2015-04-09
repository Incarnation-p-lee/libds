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

/*
 * hashing table with separate chaining
 *     hashing function for .data and .text address
 */
struct linked_hashing {
    struct doubly_linked_list **base;
    uint64                    size;
    uint64                    (*func)(uint64);
};
#endif

