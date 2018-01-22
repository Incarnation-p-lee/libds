#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

/*
 * HEAP NICE LIMITS not reach the limitation of sint64
 */
#define HEAP_NICE_UPPER_LMT             0x7ffffffffffffff
#define HEAP_NICE_LOWER_LMT             -HEAP_NICE_UPPER_LMT

#define DEFAULT_BINARY_HEAP_SIZE        4097
#define DEPTH_INVALID                   0xffffffffu

#define INDEX_INVALID                   0u
#define INDEX_ROOT                      0x1u
#define INDEX_L_CHILD(index)            (index) * 2
#define INDEX_R_CHILD(index)            ((index) * 2 + 1)
#define INDEX_PARENT(index)             ((index) / 2)
#define INDEX_GD_PARENT(index)          ((index) / 4)
#define INDEX_LAST(heap)                ((heap)->size)
#define INDEX_FIRST                     INDEX_ROOT
#define INDEX_LL_CHILD(index)           ((index) * 4)
#define INDEX_LR_CHILD(index)           ((index) * 4 + 1)
#define INDEX_RL_CHILD(index)           ((index) * 4 + 2)
#define INDEX_RR_CHILD(index)           ((index) * 2 + 3)

#define HEAP_PARENT_NICE(heap, index)   (heap)->base[INDEX_PARENT(index)]->nice
#define HEAP_L_CHILD_NICE(heap, index)  (heap)->base[INDEX_L_CHILD(index)]->nice
#define HEAP_R_CHILD_NICE(heap, index)  (heap)->base[INDEX_R_CHILD(index)]->nice
#define HEAP_NICE(heap, index)          (heap)->base[index]->nice
#define HEAP_SIZE(heap)                 (heap)->size
#define HEAP_VAL(heap, index)           (heap)->base[index]->val
#define HEAP_DATA(heap, index)          (heap)->base[index]

#define HEAP_ALIAS(heap)                (heap)->alias
#define DATA_NICE(data)                 (data)->nice
#define DATA_VAL(data)                  (data)->val
#define ALIAS_CAPACITY(a)               (a)->capacity
#define ALIAS_SIZE(a)                   (a)->size
#define ALIAS_BASE(a)                   (a)->base
#define ALIAS_PARENT_NICE(a, index)     (a)->base[INDEX_PARENT(index)]->nice
#define ALIAS_L_CHILD_NICE(a, index)    (a)->base[INDEX_L_CHILD(index)]->nice
#define ALIAS_R_CHILD_NICE(a, index)    (a)->base[INDEX_R_CHILD(index)]->nice
#define ALIAS_NICE(a, index)            (a)->base[index]->nice
#define ALIAS_VAL(a, index)             (a)->base[index]->val
#define ALIAS_DATA(a, index)            (a)->base[index]

#define NPL_NULL                       -1
#define u_offset(n, offset)            (n + offset)

#if defined DEBUG
    #define MINIMAL_HEAP_LEGAL_P(h)     minimal_heap_legal_ip(h)
    #define MINIMAL_HEAP_ILLEGAL_P(h)   minimal_heap_illegal_ip(h)
    #define MAXIMAL_HEAP_LEGAL_P(h)     maximal_heap_legal_ip(h)
    #define MAXIMAL_HEAP_ILLEGAL_P(h)   maximal_heap_illegal_ip(h)
    #define MIN_MAX_HEAP_LEGAL_P(h)     min_max_heap_legal_ip(h)
    #define MIN_MAX_HEAP_ILLEGAL_P(h)   min_max_heap_illegal_ip(h)
#else
    #define MINIMAL_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MINIMAL_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
    #define MAXIMAL_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MAXIMAL_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
    #define MIN_MAX_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MIN_MAX_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
#endif

/* EXTERNAL FUNCTIONS */
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern void doubly_linked_list_destroy(struct doubly_linked_list **list);
extern void doubly_linked_list_initial(struct doubly_linked_list *list);
extern struct binary_search_tree * binary_search_tree_node_find(struct binary_search_tree *tree, sint64 nice);
/* END OF EXTERNAL FUNCTIONS */

/* BINARY HEAP DEBUG */
#if defined DEBUG

static void *heap_order_func[] = {
    &binary_heap_minimal_ordered_p,
    &binary_heap_maximal_ordered_p,
    &binary_heap_min_max_up_ordered_p,
    &binary_heap_min_max_down_ordered_p,
};

#endif
/* END OF BINARY HEAP DEBUG */

#endif
