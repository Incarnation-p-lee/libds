#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

/*
 * HEAP NICE LIMITS not reach the limitation of sint64
 */
#define HEAP_NICE_UPPER_LMT            0x7ffffffffffffff
#define HEAP_NICE_LOWER_LMT            -HEAP_NICE_UPPER_LMT

#define DEFAULT_BINARY_HEAP_SIZE       4097
#define DEPTH_INVALID                  0xffffffffu

#define INDEX_INVALID                  0u
#define INDEX_ROOT                     0x1u
#define INDEX_L_CHILD(index)           (index) * 2
#define INDEX_R_CHILD(index)           ((index) * 2 + 1)
#define INDEX_PARENT(index)            ((index) / 2)
#define INDEX_GD_PARENT(index)         ((index) / 4)
#define INDEX_LAST(heap)               ((heap)->size)
#define INDEX_FIRST                    INDEX_ROOT
#define INDEX_LL_CHILD(index)          ((index) * 4)
#define INDEX_LR_CHILD(index)          ((index) * 4 + 1)
#define INDEX_RL_CHILD(index)          ((index) * 4 + 2)
#define INDEX_RR_CHILD(index)          ((index) * 2 + 3)

#define HEAP_PARENT_NICE(heap, index)  (heap)->base[INDEX_PARENT(index)]->nice
#define HEAP_L_CHILD_NICE(heap, index) (heap)->base[INDEX_L_CHILD(index)]->nice
#define HEAP_R_CHILD_NICE(heap, index) (heap)->base[INDEX_R_CHILD(index)]->nice
#define HEAP_NICE(heap, index)         (heap)->base[index]->nice
#define HEAP_LINK(heap, index)         (heap)->base[index]->link
#define HEAP_SIZE(heap)                (heap)->size
#define HEAP_CHAIN(heap, index)        (heap)->base[index]

#define NPL_NULL                       -1

#define u_offset(n, offset)            (n + offset)

/* EXTERNAL FUNCTIONS */
extern bool complain_zero_size_p(uint32 size);
extern bool complain_no_memory_p(void *ptr);
extern bool complain_null_pointer_p(void *ptr);
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern void doubly_linked_list_destroy(struct doubly_linked_list **list);
extern void doubly_linked_list_initial(struct doubly_linked_list *list);
/* END OF EXTERNAL FUNCTIONS */

/* BINARY HEAP DEBUG */
#if defined DEBUG

static void *heap_order_func[] = {
    &binary_heap_minimal_ordered_p,
    &binary_heap_maximal_ordered_p,
    &binary_heap_min_max_ordered_p,
};

#endif
/* END OF BINARY HEAP DEBUG */

#endif
