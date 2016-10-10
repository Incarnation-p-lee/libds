#ifndef HAVE_DEFINED_tree_H
#define HAVE_DEFINED_tree_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

bool avl_tree_balanced_p(s_avl_tree_t *tree);
bool avl_tree_contains_p(s_avl_tree_t *tree, s_avl_tree_t *node);
bool binary_search_tree_contains_p(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
bool splay_tree_contains_p(struct splay_tree *tree, struct splay_tree *node);
s_avl_tree_t * avl_tree_create(void);
s_avl_tree_t * avl_tree_find(s_avl_tree_t *tree, sint64 nice);
s_avl_tree_t * avl_tree_find_max(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_find_min(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_insert(s_avl_tree_t **tree, s_avl_tree_t *node);
s_avl_tree_t * avl_tree_left(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_remove(s_avl_tree_t **tree, s_avl_tree_t *node);
s_avl_tree_t * avl_tree_right(s_avl_tree_t *tree);
s_binary_search_tree_t  * binary_search_tree_find_min(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_create(void);
s_binary_search_tree_t * binary_search_tree_find(s_binary_search_tree_t *tree, sint64 nice);
s_binary_search_tree_t * binary_search_tree_find_max(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_insert(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
s_binary_search_tree_t * binary_search_tree_left(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_remove(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
s_binary_search_tree_t * binary_search_tree_right(s_binary_search_tree_t *tree);
sint32 avl_tree_height(s_avl_tree_t *tree);
sint32 binary_search_tree_height(s_binary_search_tree_t *tree);
sint32 splay_tree_height(struct splay_tree *tree);
sint64 avl_tree_nice(s_avl_tree_t *tree);
sint64 binary_indexed_tree_range_sum(struct binary_indexed_tree *tree, uint32 nmbr_s, uint32 nmbr_e);
sint64 binary_indexed_tree_sum(struct binary_indexed_tree *tree, uint32 number);
sint64 binary_indexed_tree_value(struct binary_indexed_tree *tree, uint32 number);
sint64 binary_search_tree_nice(s_binary_search_tree_t *tree);
sint64 splay_tree_nice(struct splay_tree *tree);
static inline bool avl_tree_balanced_ip(s_avl_tree_t *tree);
static inline bool avl_tree_balanced_optimize_validity_p(struct avl_tree *tree, bool expected);
static inline bool avl_tree_contains_ip(s_avl_tree_t *tree, s_avl_tree_t *node);
static inline bool avl_tree_doubly_child_p(s_avl_tree_t *tree);
static inline bool avl_tree_doubly_rotate_left_precondition_p(struct avl_tree *node);
static inline bool avl_tree_doubly_rotate_right_precondition_p(struct avl_tree *node);
static inline bool avl_tree_height_balanced_p(struct avl_tree *tree);
static inline bool avl_tree_height_opt_validity_p(struct avl_tree *tree, sint32 expected);
static inline bool avl_tree_height_sync_with_calculated_p(struct avl_tree *tree, sint32 left, sint32 right);
static inline bool avl_tree_left_optimize_validity_p(struct avl_tree *node, void *expected);
static inline bool avl_tree_node_balanced_p(s_avl_tree_t *node);
static inline bool avl_tree_ordered_p(struct avl_tree *tree);
static inline bool avl_tree_right_optimize_validity_p(struct avl_tree *node, void *expected);
static inline bool avl_tree_single_rotate_left_precondition_p(struct avl_tree *node);
static inline bool avl_tree_single_rotate_right_precondition_p(struct avl_tree *node);
static inline bool avl_tree_structure_legal_p(s_avl_tree_t *tree);
static inline bool binary_indexed_tree_number_legal_p(struct binary_indexed_tree *tree, uint32 number);
static inline bool binary_indexed_tree_structure_legal_p(struct binary_indexed_tree *tree);
static inline bool binary_search_tree_contains_p_i(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
static inline bool binary_search_tree_doubly_child_p(s_binary_search_tree_t *node);
static inline bool binary_search_tree_ordered_p(struct binary_search_tree *tree);
static inline bool binary_search_tree_structure_legal_p(s_binary_search_tree_t *tree);
static inline bool splay_tree_contains_p_internal(struct splay_tree *tree, struct splay_tree *node);
static inline bool splay_tree_doubly_child_p(struct splay_tree *node);
static inline bool splay_tree_ordered_p(struct splay_tree *tree);
static inline bool splay_tree_structure_legal_p(struct splay_tree *tree);
static inline s_avl_tree_t * avl_tree_doubly_rotate_left(s_avl_tree_t *node);
static inline s_avl_tree_t * avl_tree_doubly_rotate_right(s_avl_tree_t *node);
static inline s_avl_tree_t * avl_tree_find_i(s_avl_tree_t *tree, sint64 nice);
static inline s_avl_tree_t * avl_tree_find_max_i(s_avl_tree_t *tree);
static inline s_avl_tree_t * avl_tree_find_min_i(s_avl_tree_t *tree);
static inline s_avl_tree_t * avl_tree_insert_i(s_avl_tree_t **tree, s_avl_tree_t *node);
static inline s_avl_tree_t * avl_tree_remove_i(s_avl_tree_t **tree, s_avl_tree_t *node);
static inline s_avl_tree_t * avl_tree_single_rotate_left(s_avl_tree_t *node);
static inline s_avl_tree_t * avl_tree_single_rotate_right(s_avl_tree_t *node);
static inline s_avl_tree_t ** avl_tree_find_ptr_to_max(s_avl_tree_t **tree);
static inline s_avl_tree_t ** avl_tree_find_ptr_to_min(s_avl_tree_t **tree);
static inline s_binary_search_tree_t * binary_search_tree_find_i(s_binary_search_tree_t *tree, sint64 nice);
static inline s_binary_search_tree_t * binary_search_tree_find_max_i(s_binary_search_tree_t *tree);
static inline s_binary_search_tree_t * binary_search_tree_find_min_i(s_binary_search_tree_t *tree);
static inline s_binary_search_tree_t * binary_search_tree_insert_i(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
static inline s_binary_search_tree_t * binary_search_tree_remove_i(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
static inline s_binary_search_tree_t ** binary_search_tree_find_ptr_to_max(s_binary_search_tree_t **tree);
static inline s_binary_search_tree_t ** binary_search_tree_find_ptr_to_min(s_binary_search_tree_t **tree);
static inline sint32 attr_always_inline avl_tree_height_balanced_opt_p(struct avl_tree *tree);
static inline sint32 attr_always_inline avl_tree_height_opt(struct avl_tree *tree);
static inline sint32 attr_always_inline avl_tree_height_opt(struct avl_tree *tree);
static inline sint32 avl_tree_height_calculate(struct avl_tree *tree);
static inline sint32 avl_tree_height_internal(struct avl_tree *tree);
static inline sint32 binary_search_tree_height_i(s_binary_search_tree_t *tree);
static inline sint32 splay_tree_height_internal(struct splay_tree *tree);
static inline sint64 binary_indexed_tree_sum_internal(struct binary_indexed_tree *tree, uint32 number);
static inline struct splay_tree * splay_tree_find_internal(struct splay_tree **tree, sint64 nice, struct splay_tree *root);
static inline struct splay_tree * splay_tree_find_max_internal(struct splay_tree **tree, struct splay_tree *root);
static inline struct splay_tree * splay_tree_find_min_internal(struct splay_tree **tree, struct splay_tree *root);
static inline struct splay_tree * splay_tree_insert_internal(struct splay_tree **tree, struct splay_tree *node, struct splay_tree *root);
static inline struct splay_tree * splay_tree_remove_internal(struct splay_tree **tree, struct splay_tree *node);
static inline struct splay_tree ** splay_tree_find_ptr_to_min(struct splay_tree **tree);
static inline void avl_tree_destroy_i(s_avl_tree_t *tree);
static inline void avl_tree_doubly_child_strip(s_avl_tree_t **node_pre);
static inline void avl_tree_doubly_child_strip_from_max(s_avl_tree_t **node_pre);
static inline void avl_tree_doubly_child_strip_from_min(s_avl_tree_t **node_pre);
static inline void avl_tree_height_update(s_avl_tree_t *tree);
static inline void avl_tree_initial_i(s_avl_tree_t *tree, sint64 nice);
static inline void avl_tree_iterate_i(s_avl_tree_t *tree, void (*handle)(void *), enum ITER_ORDER order);
static inline void avl_tree_lt_doubly_child_strip(s_avl_tree_t **pre, s_avl_tree_t *node);
static inline void avl_tree_rotate_left(s_avl_tree_t **tree);
static inline void avl_tree_rotate_right(s_avl_tree_t **tree);
static inline void avl_tree_swap_child(s_avl_tree_t *a, s_avl_tree_t *b);
static inline void binary_indexed_tree_add_internal(struct binary_indexed_tree *tree, uint32 number, sint64 val);
static inline void binary_search_tree_child_strip_from_max(s_binary_search_tree_t **node_pre);
static inline void binary_search_tree_child_strip_from_min(s_binary_search_tree_t **node_pre);
static inline void binary_search_tree_destroy_i(s_binary_search_tree_t *tree);
static inline void binary_search_tree_doubly_child_strip(s_binary_search_tree_t **node_pre);
static inline void binary_search_tree_initial_i(s_binary_search_tree_t *tree, sint64 nice);
static inline void binary_search_tree_iterate_i(s_binary_search_tree_t *tree, void (*handle)(void *), e_iter_order_t order);
static inline void binary_search_tree_lt_doubly_child_strip(s_binary_search_tree_t **pre, s_binary_search_tree_t *node);
static inline void binary_search_tree_swap_child(s_binary_search_tree_t *a, s_binary_search_tree_t *b);
static inline void splay_tree_balance_splaying_left(struct splay_tree **tree, struct splay_tree *root, struct splay_tree *target);
static inline void splay_tree_balance_splaying_right(struct splay_tree **tree, struct splay_tree *root, struct splay_tree *target);
static inline void splay_tree_destroy_internal(struct splay_tree *tree);
static inline void splay_tree_doubly_child_strip(struct splay_tree **pre);
static inline void splay_tree_initial_internal(struct splay_tree *tree, sint64 nice);
static inline void splay_tree_iterate_internal(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
static inline void splay_tree_lt_doubly_child_strip(struct splay_tree **pre, struct splay_tree *node);
static inline void splay_tree_node_destroy(struct splay_tree *node);
static inline void splay_tree_swap_child(struct splay_tree *a, struct splay_tree *b);
static void inline splay_tree_balance_doubly_splaying_left(struct splay_tree **tree);
static void inline splay_tree_balance_doubly_splaying_right(struct splay_tree **tree);
static void inline splay_tree_balance_root_splaying_left(struct splay_tree **tree);
static void inline splay_tree_balance_root_splaying_right(struct splay_tree **tree);
static void inline splay_tree_balance_single_splaying_left(struct splay_tree **tree);
static void inline splay_tree_balance_single_splaying_right(struct splay_tree **tree);
struct binary_indexed_tree * binary_indexed_tree_create(sint64 *data, uint32 size);
struct splay_tree * splay_tree_create(void);
struct splay_tree * splay_tree_find(struct splay_tree **tree, sint64 nice);
struct splay_tree * splay_tree_find_max(struct splay_tree **tree);
struct splay_tree * splay_tree_find_min(struct splay_tree **tree);
struct splay_tree * splay_tree_insert(struct splay_tree **tree, struct splay_tree *node);
struct splay_tree * splay_tree_left(struct splay_tree *tree);
struct splay_tree * splay_tree_remove(struct splay_tree **tree, struct splay_tree *node);
struct splay_tree * splay_tree_right(struct splay_tree *tree);
uint32 binary_indexed_tree_size(struct binary_indexed_tree *tree);
void avl_tree_destroy(s_avl_tree_t **tree);
void avl_tree_initial(s_avl_tree_t *tree, sint64 nice);
void avl_tree_iterate(s_avl_tree_t *tree, void (*handle)(void *), enum ITER_ORDER order);
void binary_indexed_tree_add(struct binary_indexed_tree *tree, uint32 number, sint64 val);
void binary_indexed_tree_destroy(struct binary_indexed_tree **tree);
void binary_indexed_tree_sub(struct binary_indexed_tree *tree, uint32 number, sint64 val);
void binary_search_tree_destroy(s_binary_search_tree_t **tree);
void binary_search_tree_initial(s_binary_search_tree_t *tree, sint64 nice);
void binary_search_tree_iterate(s_binary_search_tree_t *tree, void (*handle)(void *), e_iter_order_t order);
void binary_search_tree_nice_set(s_binary_search_tree_t *tree, sint64 nice);
void splay_tree_destroy(struct splay_tree **tree);
void splay_tree_initial(struct splay_tree *tree, sint64 nice);
void splay_tree_iterate(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
void splay_tree_nice_set(struct splay_tree *tree, sint64 nice);

#endif

