#ifndef HAVE_TREE_H
#define HAVE_TREE_H

#define TREE_NICE_PLUS_LMT       0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT      (-TREE_NICE_PLUS_LMT - 1)

#define TREE_PATH_LEFT_MASK      0x0u /* indicate the node take left in given path */
#define TREE_PATH_RIGHT_MASK     0x1u
#define PATH_MASK                TREE_PATH_RIGHT_MASK

#define TREE_PATH_L_ENCODE(node) (void *)((ptr_t)node | TREE_PATH_LEFT_MASK)
#define TREE_PATH_R_ENCODE(node) (void *)((ptr_t)node | TREE_PATH_RIGHT_MASK)
#define TREE_PATH_MASK(node)     (uint32)((ptr_t)node & PATH_MASK)
#define TREE_PATH_DECODE(node)   (void *)((ptr_t)node & (((ptr_t)-1) - 1))

enum tree_path_type {
    PATH_LEFT           = 0x0,
    PATH_RIGHT          = 0x1,
    PATH_LEFT_TO_LEFT   = 0x0,
    PATH_LEFT_TO_RIGHT  = 0x1,
    PATH_RIGHT_TO_LEFT  = 0x2,
    PATH_RIGHT_TO_RIGHT = 0x3,
};

extern void swap_pointer(void **ptr_a, void **ptr_b);

extern s_array_queue_t * array_queue_create(void);
extern bool array_queue_structure_legal_p(s_array_queue_t *queue);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void array_queue_destroy(s_array_queue_t **queue);
extern s_array_iterator_t * array_queue_iterator_obtain(s_array_queue_t *queue);
extern bool array_queue_empty_p(s_array_queue_t *queue);
extern void * array_queue_leave(s_array_queue_t *queue);

extern s_array_stack_t * array_stack_create(void);
extern void array_stack_destroy(s_array_stack_t **stack);
extern void array_stack_push(s_array_stack_t *stack, void *member);
extern void * array_stack_pop(s_array_stack_t *stack);
extern bool array_stack_empty_p(s_array_stack_t *stack);
extern bool array_stack_structure_legal_p(s_array_stack_t *queue);
extern uint32 array_stack_size(s_array_stack_t *stack);

#endif

