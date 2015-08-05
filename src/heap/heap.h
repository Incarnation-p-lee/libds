#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

#define HEAP_NICE_UPPER_LMT      0x7fffffffffffffff
#define HEAP_NICE_LOWER_LMT      (-HEAP_NICE_UPPER_LMT - 1)

#define HEAP_ROOT_INDEX          0x1u
#define DEFAULT_BINARY_HEAP_SIZE 4097

#define INDEX_LEFT_CHILD(index)  (index) * 2
#define INDEX_RIGHT_CHILD(index) ((index) * 2 + 1)
#define INDEX_PARENT(index)      ((index) / 2)
#define INDEX_LAST(heap)         ((heap)->size)
#define INDEX_FIRST              HEAP_ROOT_INDEX

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
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
/* END OF EXTERNAL FUNCTIONS */


/* BINARY HEAP INTERNAL */
static inline void binary_heap_initial(struct binary_heap *heap, uint32 capacity);
static inline void binary_heap_node_remove_tail_fixup(struct binary_heap *heap, uint32 index);
static inline void binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_idx, uint32 s_idx);
static inline void binary_heap_node_remove_and_destroy(struct binary_heap *heap, uint32 index);
static inline void binary_heap_destroy(struct binary_heap **heap);
static inline void binary_heap_cleanup(struct binary_heap *heap);
static inline void binary_heap_capacity_extend(struct binary_heap *heap);
static inline void binary_heap_node_create_by_index(struct binary_heap *heap, uint32 index, sint64 nice, void *val);
static inline bool binary_heap_node_contains_p(struct binary_heap *heap, sint64 nice, uint32 *tgt);
static inline bool binary_heap_node_child_exist_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_empty_p(struct binary_heap *heap);
static inline bool binary_heap_full_p(struct binary_heap *heap);
static inline bool binary_heap_order_minimal(struct binary_heap *heap, uint32 index, sint64 nice);
static inline bool binary_heap_order_maximal(struct binary_heap *heap, uint32 index, sint64 nice);
static uint32 binary_heap_percolate_up(struct binary_heap *heap, uint32 index, sint64 nice, void *heap_order);
static inline uint32 binary_heap_percolate_down(struct binary_heap *heap, uint32 index, sint64 nice);
static inline struct doubly_linked_list * binary_heap_node_root(struct binary_heap *heap);
static inline struct doubly_linked_list * binary_heap_node_find(struct binary_heap *heap, sint64 nice);
static inline struct collision_chain * binary_heap_collision_chain_create(sint64 nice, void *val);
static inline struct doubly_linked_list * binary_heap_node_remove(struct binary_heap *heap, uint32 index);
static inline struct binary_heap * binary_heap_create(uint32 capacity);
/* END OF BINARY HEAP INTERNAL */

/* MINIMAL HEAP */
bool minimal_heap_empty_p(struct minimal_heap *heap);
bool minimal_heap_full_p(struct minimal_heap *heap);
void minimal_heap_destroy(struct minimal_heap **heap);
void minimal_heap_cleanup(struct minimal_heap *heap);
void minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice);
void minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap);
void minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice);
struct minimal_heap * minimal_heap_create(uint32 capacity);
struct doubly_linked_list * minimal_heap_node_find(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_find_min(struct minimal_heap *heap);
struct doubly_linked_list * minimal_heap_node_remove_min(struct minimal_heap *heap);
struct doubly_linked_list * minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice);
/* END OF MINIMAL HEAP */

/* MAXIMAL HEAP */
bool maximal_heap_empty_p(struct maximal_heap *heap);
bool maximal_heap_full_p(struct maximal_heap *heap);
void maximal_heap_destroy(struct maximal_heap **heap);
void maximal_heap_cleanup(struct maximal_heap *heap);
void maximal_heap_node_insert(struct maximal_heap *heap, void *val, sint64 nice);
struct maximal_heap * maximal_heap_create(uint32 capacity);
struct doubly_linked_list * maximal_heap_node_find(struct maximal_heap *heap, sint64 nice);
struct doubly_linked_list * maximal_heap_node_find_max(struct maximal_heap *heap);
/* END OF MAXIMAL HEAP */

/* BINARY HEAP DEBUG */
#if defined DEBUG
static void *order_func_list[] = {
    &binary_heap_order_minimal,
    &binary_heap_order_maximal,
};

static inline bool binary_heap_node_contains_with_hole_p(struct binary_heap *heap, sint64 nice);
static inline bool binary_heap_percolate_up_precondition_p(struct binary_heap *heap, uint32 index, sint64 nice);
static inline bool binary_heap_percolate_down_precondition_p(struct binary_heap *heap, uint32 index, sint64 nice);
static inline bool binary_heap_order_function_pointer_valid_p(void *func_ptr);
#endif
/* END OF BINARY HEAP DEBUG */

#endif
