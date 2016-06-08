#ifndef HAVE_DEFINED_queue_H
#define HAVE_DEFINED_queue_H

bool array_queue_empty_p(struct array_queue *queue);
bool array_queue_full_p(struct array_queue *queue);
bool doubly_end_queue_empty_p(struct doubly_end_queue *queue);
bool stacked_queue_empty_p(struct stacked_queue *queue);
bool stacked_queue_full_p(struct stacked_queue *queue);
static inline bool array_queue_empty_p_internal(struct array_queue *queue);
static inline bool array_queue_full_p_internal(struct array_queue *queue);
static inline bool array_queue_resize_front_to_rear_p(struct array_queue *queue);
static inline bool array_queue_structure_legal_p(struct array_queue *queue);
static inline bool doubly_end_queue_empty_p_internal(struct doubly_end_queue *queue);
static inline bool stacked_queue_empty_p_internal(struct stacked_queue *queue);
static inline struct doubly_end_queue_list * doubly_end_queue_list_next(struct doubly_end_queue_list *node);
static inline struct doubly_end_queue_list * doubly_end_queue_list_offset_reflect(struct doubly_linked_list *link);
static inline struct doubly_end_queue_list * doubly_end_queue_list_previous(struct doubly_end_queue_list *node);
static inline uint32 stacked_queue_space_rest_internal(struct stacked_queue *queue);
static inline void array_queue_resize_expand(struct array_queue *queue, uint32 size, void **addr);
static inline void array_queue_resize_internal(struct array_queue *queue, uint32 size);
static inline void array_queue_resize_narrow(struct array_queue *queue, uint32 size, void **addr);
static inline void doubly_end_queue_cleanup_internal(struct doubly_end_queue *queue);
static inline void doubly_end_queue_last_node_clean(struct doubly_end_queue *queue);
static inline void stacked_queue_resize_internal(struct stacked_queue *queue, uint32 dim);
static inline void stacked_queue_stack_dump(struct array_stack *from, struct array_stack *to);
struct array_queue * array_queue_create(void);
struct doubly_end_queue * doubly_end_queue_create(void);
struct stacked_queue * stacked_queue_create(void);
uint32 array_queue_capacity(struct array_queue *queue);
uint32 array_queue_dim(struct array_queue *queue);
uint32 array_queue_rest(struct array_queue *queue);
uint32 doubly_end_queue_length(struct doubly_end_queue *queue);
uint32 stacked_queue_capacity(struct stacked_queue *queue);
uint32 stacked_queue_dim(struct stacked_queue *queue);
uint32 stacked_queue_space_rest(struct stacked_queue *queue);
void * array_queue_leave(struct array_queue *queue);
void * doubly_end_queue_head_leave(struct doubly_end_queue *queue);
void * doubly_end_queue_tail_leave(struct doubly_end_queue *queue);
void * stacked_queue_leave(struct stacked_queue *queue);
void array_queue_cleanup(struct array_queue *queue);
void array_queue_destroy(struct array_queue **queue);
void array_queue_enter(struct array_queue *queue, void *member);
void array_queue_iterate(struct array_queue *queue, void (*handler)(void *));
void array_queue_resize(struct array_queue *queue, uint32 size);
void doubly_end_queue_cleanup(struct doubly_end_queue *queue);
void doubly_end_queue_destroy(struct doubly_end_queue **queue);
void doubly_end_queue_head_enter(struct doubly_end_queue *queue, void *member);
void doubly_end_queue_iterate(struct doubly_end_queue *queue, void (*handle)(void *));
void doubly_end_queue_tail_enter(struct doubly_end_queue *queue, void *member);
void stacked_queue_cleanup(struct stacked_queue *queue);
void stacked_queue_destroy(struct stacked_queue **queue);
void stacked_queue_enter(struct stacked_queue *queue, void *member);
void stacked_queue_iterate(struct stacked_queue *queue, void (*handler)(void *));
void stacked_queue_resize(struct stacked_queue *queue, uint32 dim);

#endif

