#ifndef HEAP_DECLARATION_H
#define HEAP_DECLARATION_H


bool maximal_heap_empty_p(struct maximal_heap *heap);
bool maximal_heap_full_p(struct maximal_heap *heap);
bool minimal_heap_empty_p(struct minimal_heap *heap);
bool minimal_heap_full_p(struct minimal_heap *heap);
static inline bool binary_heap_empty_p(struct binary_heap *heap);
static inline bool binary_heap_full_p(struct binary_heap *heap);
static inline bool binary_heap_node_child_exist_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_node_contains_p(struct binary_heap *heap, sint64 nice, uint32 *tgt);
static inline bool binary_heap_node_contains_with_hole_p(struct binary_heap *heap, sint64 nice);
static inline bool binary_heap_order_function_pointer_valid_p(void *func_ptr);
static inline bool binary_heap_order_maximal(struct binary_heap *heap, uint32 index, sint64 nice);
static inline bool binary_heap_order_minimal(struct binary_heap *heap, uint32 index, sint64 nice);
static inline bool binary_heap_percolate_direction_consistent_with_ordering_p(struct binary_heap *heap, uint32 index, sint64 new_nice, void *ordering, void *percolate);
static inline bool binary_heap_percolate_down_precondition_p(struct binary_heap *heap, uint32 index, sint64 nice, void *ordering);
static inline bool binary_heap_percolate_function_pointer_valid_p(void *func_ptr);
static inline bool binary_heap_percolate_up_precondition_p(struct binary_heap *heap, uint32 index, sint64 nice, void *ordering);
static inline sint64 binary_heap_order_percolate_down_nice_limit(void *ordering);
static inline struct binary_heap * binary_heap_create(uint32 capacity);
static inline struct collision_chain * binary_heap_collision_chain_create(sint64 nice, void *val);
static inline struct doubly_linked_list * binary_heap_node_find(struct binary_heap *heap, sint64 nice);
static inline struct doubly_linked_list * binary_heap_node_remove(struct binary_heap *heap, uint32 index, void *ordering);
static inline struct doubly_linked_list * binary_heap_node_root(struct binary_heap *heap);
static inline uint32 binary_heap_child_small_nice_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_percolate_down(struct binary_heap *heap, uint32 index, sint64 nice, void *ordering);
static inline uint32 binary_heap_percolate_up(struct binary_heap *heap, uint32 index, sint64 nice, void *ordering);
static inline void binary_heap_capacity_extend(struct binary_heap *heap);
static inline void binary_heap_cleanup(struct binary_heap *heap);
static inline void binary_heap_destroy(struct binary_heap **heap);
static inline void binary_heap_initial(struct binary_heap *heap, uint32 capacity);
static inline void binary_heap_nice_alter_percolate(struct binary_heap *heap, uint32 index, sint64 new_nice, void *ordering, void *percolate);
static inline void binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_idx, uint32 s_idx);
static inline void binary_heap_node_create_by_index(struct binary_heap *heap, uint32 index, sint64 nice, void *val);
static inline void binary_heap_node_insert(struct binary_heap *heap, void *val, sint64 nice, void *ordering);
static inline void binary_heap_node_remove_and_destroy(struct binary_heap *heap, uint32 index, void *ordering);
static inline void binary_heap_node_remove_tail_fixup(struct binary_heap *heap, uint32 index, void *ordering);
static inline void binary_heap_percolate_down_to_tail(struct binary_heap *heap, uint32 index, void *ordering);
struct doubly_linked_list * maximal_heap_node_find(struct maximal_heap *heap, sint64 nice);
struct doubly_linked_list * maximal_heap_node_find_max(struct maximal_heap *heap);
struct doubly_linked_list * maximal_heap_node_remove(struct maximal_heap *heap, sint64 nice);
struct doubly_linked_list * maximal_heap_node_remove_max(struct maximal_heap *heap);
struct doubly_linked_list * minimal_heap_node_find(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_find_min(struct minimal_heap *heap);
struct doubly_linked_list * minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_remove_min(struct minimal_heap *heap);
struct maximal_heap * maximal_heap_create(uint32 capacity);
struct minimal_heap * minimal_heap_create(uint32 capacity);
void maximal_heap_cleanup(struct maximal_heap *heap);
void maximal_heap_destroy(struct maximal_heap **heap);
void maximal_heap_node_decrease_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
void maximal_heap_node_increase_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
void maximal_heap_node_insert(struct maximal_heap *heap, void *val, sint64 nice);
void maximal_heap_node_remove_and_destroy(struct maximal_heap *heap, sint64 nice);
void maximal_heap_node_remove_max_and_destroy(struct maximal_heap *heap);
void minimal_heap_cleanup(struct minimal_heap *heap);
void minimal_heap_destroy(struct minimal_heap **heap);
void minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice);
void minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice);
void minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap);

#endif
