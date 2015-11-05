#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

#define HEAP_NICE_UPPER_LMT      0x7fffffffffffffff
#define HEAP_NICE_LOWER_LMT      (-HEAP_NICE_UPPER_LMT - 1)

#define DEFAULT_BINARY_HEAP_SIZE 4097

#define INDEX_ROOT               0x1u
#define INDEX_LEFT_CHILD(index)  (index) * 2
#define INDEX_RIGHT_CHILD(index) ((index) * 2 + 1)
#define INDEX_PARENT(index)      ((index) / 2)
#define INDEX_GD_PARENT(index)   ((index) / 4)
#define INDEX_LAST(heap)         ((heap)->size)
#define INDEX_FIRST              INDEX_ROOT
#define INDEX_INVALID            0u
#define DEPTH_INVALID            0xffffffffu
#define INDEX_LL_CHILD(index)    (index) * 4
#define INDEX_RR_CHILD(index)    ((index) * 2 + 1) * 2

#define HEAP_PARENT_NICE(heap, index)      (heap)->base[INDEX_PARENT(index)]->nice
#define HEAP_LEFT_CHILD_NICE(heap, index)  (heap)->base[INDEX_LEFT_CHILD(index)]->nice
#define HEAP_RIGHT_CHILD_NICE(heap, index) (heap)->base[INDEX_RIGHT_CHILD(index)]->nice
#define HEAP_NICE(heap, index)             (heap)->base[index]->nice
#define HEAP_LINK(heap, index)             (heap)->base[index]->link
#define HEAP_SIZE(heap)                    (heap)->size
#define HEAP_CHAIN(heap, index)            (heap)->base[index]

#define u_offset(n, offset) (n + offset)

/* EXTERNAL FUNCTIONS */
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_node_insert_after_risky(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
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
