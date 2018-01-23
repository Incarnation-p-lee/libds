#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

/*
 * HEAP NICE LIMITS not reach the limitation of sint64
 */
#define HEAP_NICE_UPPER_LMT             0x7ffffffffffffff
#define HEAP_NICE_LOWER_LMT             -HEAP_NICE_UPPER_LMT

#define DEFAULT_BINARY_HEAP_SIZE        4097
#define DEPTH_INVALID                   0xffffffffu
#define NPL_NULL                       -1
#define NPL_INVALID                     0x7fffffff

#define INDEX_INVALID                   0u
#define INDEX_ROOT                      0x1u
#define INDEX_FIRST                     INDEX_ROOT
#define INDEX_LEFT(index)               (index) * 2
#define INDEX_RIGHT(index)              ((index) * 2 + 1)
#define INDEX_PARENT(index)             ((index) / 2)
#define INDEX_GD_PARENT(index)          ((index) / 4)
#define INDEX_LAST(heap)                ((heap)->size)
#define INDEX_L_LEFT(index)             ((index) * 4)
#define INDEX_L_RIGHT(index)            ((index) * 4 + 1)
#define INDEX_R_LEFT(index)             ((index) * 4 + 2)
#define INDEX_R_RIGHT(index)            ((index) * 2 + 3)

#define HEAP_ALIAS(heap)                (heap)->alias
#define DATA_NICE(data)                 (data)->nice
#define DATA_VAL(data)                  (data)->val
#define ALIAS_CAPACITY(a)               (a)->capacity
#define ALIAS_SIZE(a)                   (a)->size
#define ALIAS_BASE(a)                   (a)->base
#define ALIAS_PARENT_NICE(a, index)     (a)->base[INDEX_PARENT(index)]->nice
#define ALIAS_LEFT_NICE(a, index)       (a)->base[INDEX_LEFT(index)]->nice
#define ALIAS_RIGHT_NICE(a, index)      (a)->base[INDEX_RIGHT(index)]->nice
#define ALIAS_NICE(a, index)            (a)->base[index]->nice
#define ALIAS_VAL(a, index)             (a)->base[index]->val
#define ALIAS_DATA(a, index)            (a)->base[index]

#define LEFTIST_NPL(l)                  (l)->npl
#define LEFTIST_DATA(l)                 (&(l)->data)
#define LEFTIST_LEFT(l)                 (l)->left
#define LEFTIST_RIGHT(l)                (l)->right

#define u_offset(n, offset)            (n + offset)

#if defined DEBUG
    #define MINIMAL_HEAP_LEGAL_P(h)     minimal_heap_legal_ip(h)
    #define MINIMAL_HEAP_ILLEGAL_P(h)   minimal_heap_illegal_ip(h)
    #define MAXIMAL_HEAP_LEGAL_P(h)     maximal_heap_legal_ip(h)
    #define MAXIMAL_HEAP_ILLEGAL_P(h)   maximal_heap_illegal_ip(h)
    #define MIN_MAX_HEAP_LEGAL_P(h)     min_max_heap_legal_ip(h)
    #define MIN_MAX_HEAP_ILLEGAL_P(h)   min_max_heap_illegal_ip(h)
    #define LEFTIST_HEAP_LEGAL_P(h)     leftist_heap_legal_ip(h)
    #define LEFTIST_HEAP_ILLEGAL_P(h)   leftist_heap_illegal_ip(h)
#else
    #define MINIMAL_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MINIMAL_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
    #define MAXIMAL_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MAXIMAL_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
    #define MIN_MAX_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define MIN_MAX_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
    #define LEFTIST_HEAP_LEGAL_P(h)     NON_NULL_PTR_P(h)
    #define LEFTIST_HEAP_ILLEGAL_P(h)   NULL_PTR_P(h)
#endif

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

extern s_array_queue_t * array_queue_create(void);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void * array_queue_leave(s_array_queue_t *queue);
extern void array_queue_destroy(s_array_queue_t **queue);
extern bool array_queue_empty_p(s_array_queue_t *queue);

#endif

