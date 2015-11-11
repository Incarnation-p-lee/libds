#ifndef HEAP_DECLARATION_H
#define HEAP_DECLARATION_H


bool maximal_heap_empty_p(struct maximal_heap *heap);
bool maximal_heap_full_p(struct maximal_heap *heap);
bool min_max_heap_empty_p(struct min_max_heap *heap);
bool min_max_heap_full_p(struct min_max_heap *heap);
bool minimal_heap_empty_p(struct minimal_heap *heap);
bool minimal_heap_full_p(struct minimal_heap *heap);
static inline bool binary_heap_empty_p(struct binary_heap *heap);
static inline bool binary_heap_full_p(struct binary_heap *heap);
static inline bool binary_heap_index_legal_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_maximal_ordered_p(struct binary_heap *heap, uint32 index, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_min_max_nice_ordered_p(struct binary_heap *heap, sint64 nice, uint32 up_index, uint32 down_index, uint32 grandson, uint32 depth);
static inline bool binary_heap_min_max_no_child_ordered_p(struct binary_heap *heap, uint32 index, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_min_max_ordered_p(struct binary_heap *heap, uint32 index, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_min_max_root_ordered_p(struct binary_heap *heap, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_min_max_root_parent_ordered_p(struct binary_heap *heap, uint32 index, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_minimal_ordered_p(struct binary_heap *heap, uint32 index, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_nice_legal_p(sint64 nice);
static inline bool binary_heap_nice_repeated_p(struct binary_heap *heap, uint32 parent, uint32 small_child, sint64 nice);
static inline bool binary_heap_node_child_exist_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_node_contains_p(struct binary_heap *heap, sint64 nice, uint32 *tgt);
static inline bool binary_heap_node_contains_with_null_p(struct binary_heap *heap, sint64 nice);
static inline bool binary_heap_node_depth_even_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_node_depth_odd_p(struct binary_heap *heap, uint32 index);
static inline bool binary_heap_ordered_p(struct binary_heap *heap, void *heap_order);
static inline bool binary_heap_range_ordered_p(struct binary_heap *heap, uint32 up_idx, uint32 down_idx, sint64 nice, uint32 *tgt_index);
static inline bool binary_heap_structure_legal_p(struct binary_heap *heap);
static inline bool binary_heap_valid_ordered_func_ptr_p(void *func_ptr);
static inline struct binary_heap * binary_heap_create(uint32 capacity);
static inline struct collision_chain * binary_heap_collision_chain_create(sint64 nice, void *val);
static inline struct doubly_linked_list * binary_heap_node_find(struct binary_heap *heap, sint64 nice);
static inline struct doubly_linked_list * binary_heap_node_remove_root(struct binary_heap *heap, void *order);
static inline struct doubly_linked_list * binary_heap_node_root(struct binary_heap *heap);
static inline struct doubly_linked_list * maximal_heap_node_remove_internal(struct binary_heap *heap, uint32 index);
static inline struct doubly_linked_list * min_max_heap_node_remove_internal(struct min_max_heap *heap, uint32 index);
static inline struct doubly_linked_list * min_max_heap_node_remove_max_internal(struct min_max_heap *heap);
static inline struct doubly_linked_list * minimal_heap_node_remove_internal(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_child_big_nice_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_child_small_nice_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_grandchild_big_nice_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_grandchild_small_nice_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_min_max_ordered_target_index(struct binary_heap *heap, uint32 grandparent, sint64 nice, uint32 grandson);
static inline uint32 binary_heap_node_depth(uint32 index);
static inline uint32 binary_heap_node_reorder(struct binary_heap *heap, uint32 index, sint64 nice, void *heap_order);
static inline uint32 binary_heap_serial_node_big_nice_index(struct binary_heap *heap, uint32 index, uint32 count);
static inline uint32 binary_heap_serial_node_small_nice_index(struct binary_heap *heap, uint32 index, uint32 count);
static inline void binary_heap_capacity_extend(struct binary_heap *heap);
static inline void binary_heap_cleanup(struct binary_heap *heap);
static inline void binary_heap_destroy(struct binary_heap **heap);
static inline void binary_heap_initial(struct binary_heap *heap, uint32 capacity);
static inline void binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_idx, uint32 s_idx);
static inline void binary_heap_node_create_by_index(struct binary_heap *heap, uint32 index, sint64 nice, void *val);
static inline void binary_heap_node_insert(struct binary_heap *heap, void *val, sint64 nice, void *ordering);
static inline void binary_heap_node_remove_root_and_destroy(struct binary_heap *heap, void *ordering);
static inline void maximal_heap_build_internal(struct binary_heap *heap);
static inline void maximal_heap_node_nice_alter(struct binary_heap *heap, uint32 index, sint64 new_nice);
static inline void maximal_heap_node_remove_and_destroy_internal(struct binary_heap *heap, uint32 index);
static inline void min_max_heap_node_nice_alter(struct min_max_heap *heap, uint32 index, sint64 new_nice);
static inline void min_max_heap_node_remove_and_destroy_internal(struct min_max_heap *heap, uint32 index);
static inline void min_max_heap_node_remove_max_and_destroy_internal(struct min_max_heap *heap);
static inline void minimal_heap_build_internal(struct binary_heap *heap);
static inline void minimal_heap_node_nice_alter(struct binary_heap *heap, uint32 index, sint64 new_nice);
static inline void minimal_heap_node_remove_and_destroy_internal(struct binary_heap *heap, uint32 index);
struct doubly_linked_list * maximal_heap_node_find(struct maximal_heap *heap, sint64 nice);
struct doubly_linked_list * maximal_heap_node_find_max(struct maximal_heap *heap);
struct doubly_linked_list * maximal_heap_node_remove(struct maximal_heap *heap, sint64 nice);
struct doubly_linked_list * maximal_heap_node_remove_max(struct maximal_heap *heap);
struct doubly_linked_list * min_max_heap_node_find(struct min_max_heap *heap, sint64 nice);
struct doubly_linked_list * min_max_heap_node_find_max(struct min_max_heap *heap);
struct doubly_linked_list * min_max_heap_node_find_min(struct min_max_heap *heap);
struct doubly_linked_list * min_max_heap_node_remove(struct min_max_heap *heap, sint64 nice);
struct doubly_linked_list * min_max_heap_node_remove_max(struct min_max_heap *heap);
struct doubly_linked_list * min_max_heap_node_remove_min(struct min_max_heap *heap);
struct doubly_linked_list * minimal_heap_node_find(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_find_min(struct minimal_heap *heap);
struct doubly_linked_list * minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_remove_min(struct minimal_heap *heap);
struct maximal_heap * maximal_heap_build(struct collision_chain **chain_array, uint32 size);
struct maximal_heap * maximal_heap_create(uint32 capacity);
struct min_max_heap * min_max_heap_create(uint32 capacity);
struct minimal_heap * minimal_heap_build(struct collision_chain **chain_array, uint32 size);
struct minimal_heap * minimal_heap_create(uint32 capacity);
uint32 min_max_heap_node_depth(struct min_max_heap *heap, uint32 index);
void maximal_heap_cleanup(struct maximal_heap *heap);
void maximal_heap_destroy(struct maximal_heap **heap);
void maximal_heap_node_decrease_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
void maximal_heap_node_increase_nice(struct maximal_heap *heap, sint64 nice, uint32 offset);
void maximal_heap_node_insert(struct maximal_heap *heap, void *val, sint64 nice);
void maximal_heap_node_remove_and_destroy(struct maximal_heap *heap, sint64 nice);
void maximal_heap_node_remove_max_and_destroy(struct maximal_heap *heap);
void min_max_heap_cleanup(struct min_max_heap *heap);
void min_max_heap_destroy(struct min_max_heap **heap);
void min_max_heap_node_decrease_nice(struct min_max_heap *heap, sint64 nice, uint32 offset);
void min_max_heap_node_increase_nice(struct min_max_heap *heap, sint64 nice, uint32 offset);
void min_max_heap_node_insert(struct min_max_heap *heap, void *val, sint64 nice);
void min_max_heap_node_remove_and_destroy(struct min_max_heap *heap, sint64 nice);
void min_max_heap_node_remove_max_and_destroy(struct min_max_heap *heap);
void min_max_heap_node_remove_min_and_destroy(struct min_max_heap *heap);
void minimal_heap_cleanup(struct minimal_heap *heap);
void minimal_heap_destroy(struct minimal_heap **heap);
void minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset);
void minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice);
void minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice);
void minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap);

#endif
