#ifndef HAVE_TREE_H
#define HAVE_TREE_H

#define TREE_NICE_PLUS_LMT    0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT   (-TREE_NICE_PLUS_LMT - 1)

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false

static sint32 direct = 0;

extern bool array_queue_empty_p(s_array_queue_t *queue);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void * array_queue_leave(s_array_queue_t *queue);
extern void array_queue_destroy(s_array_queue_t **queue);
extern void swap_pointer(void **ptr_a, void **ptr_b);
extern s_array_queue_t * array_queue_create(void);

#endif

