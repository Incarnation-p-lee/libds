#ifndef HAVE_DEFINED_tree_H
#define HAVE_DEFINED_tree_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

bool avl_tree_balanced_p(s_avl_tree_t *tree);
bool avl_tree_contains_p(s_avl_tree_t *tree, s_avl_tree_t *node);
bool binary_search_tree_contains_p(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
bool splay_tree_contains_p(s_splay_tree_t *tree, s_splay_tree_t *node);
bool trie_tree_sequence_matched_p(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
bool trie_tree_string_matched_p(s_trie_tree_t *trie, char *string);
bool trie_tree_structure_legal_p(s_trie_tree_t *trie);
s_avl_tree_t * avl_tree_create(void);
s_avl_tree_t * avl_tree_find(s_avl_tree_t *tree, sint64 nice);
s_avl_tree_t * avl_tree_find_max(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_find_min(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_insert(s_avl_tree_t **tree, s_avl_tree_t *node);
s_avl_tree_t * avl_tree_left(s_avl_tree_t *tree);
s_avl_tree_t * avl_tree_remove(s_avl_tree_t **tree, s_avl_tree_t *node);
s_avl_tree_t * avl_tree_right(s_avl_tree_t *tree);
s_binary_indexed_tree_t * binary_indexed_tree_create(sint64 *data, uint32 size);
s_binary_search_tree_t  * binary_search_tree_find_min(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_create(void);
s_binary_search_tree_t * binary_search_tree_find(s_binary_search_tree_t *tree, sint64 nice);
s_binary_search_tree_t * binary_search_tree_find_max(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_insert(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
s_binary_search_tree_t * binary_search_tree_left(s_binary_search_tree_t *tree);
s_binary_search_tree_t * binary_search_tree_remove(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
s_binary_search_tree_t * binary_search_tree_right(s_binary_search_tree_t *tree);
s_splay_tree_t * splay_tree_create(void);
s_splay_tree_t * splay_tree_find(s_splay_tree_t **tree, sint64 nice);
s_splay_tree_t * splay_tree_find_max(s_splay_tree_t **tree);
s_splay_tree_t * splay_tree_find_min(s_splay_tree_t **tree);
s_splay_tree_t * splay_tree_insert(s_splay_tree_t **tree, s_splay_tree_t *node);
s_splay_tree_t * splay_tree_left(s_splay_tree_t *tree);
s_splay_tree_t * splay_tree_remove(s_splay_tree_t **tree, s_splay_tree_t *node);
s_splay_tree_t * splay_tree_right(s_splay_tree_t *tree);
s_trie_tree_t * trie_tree_create(void);
sint32 avl_tree_height(s_avl_tree_t *tree);
sint32 binary_search_tree_height(s_binary_search_tree_t *tree);
sint32 splay_tree_height(s_splay_tree_t *tree);
sint64 avl_tree_nice(s_avl_tree_t *tree);
sint64 binary_indexed_tree_range_sum(s_binary_indexed_tree_t *tree, uint32 nmbr_s, uint32 nmbr_e);
sint64 binary_indexed_tree_sum(s_binary_indexed_tree_t *tree, uint32 number);
sint64 binary_search_tree_nice(s_binary_search_tree_t *tree);
sint64 splay_tree_nice(s_splay_tree_t *tree);
static inline bool avl_tree_balanced_ip(s_avl_tree_t *tree);
static inline bool avl_tree_balanced_optimize_validity_p(struct avl_tree *tree, bool expected);
static inline bool avl_tree_contains_ip(s_avl_tree_t *tree, s_avl_tree_t *node);
static inline bool avl_tree_doubly_child_p(s_avl_tree_t *tree);
static inline bool avl_tree_doubly_rotate_left_precondition_p(struct avl_tree *node);
static inline bool avl_tree_doubly_rotate_right_precondition_p(struct avl_tree *node);
static inline bool avl_tree_height_balanced_p(struct avl_tree *tree);
static inline bool avl_tree_height_opt_validity_p(struct avl_tree *tree, sint32 expected);
static inline bool avl_tree_height_sync_with_calculated_p(struct avl_tree *tree, sint32 left, sint32 right);
static inline bool avl_tree_node_balanced_p(s_avl_tree_t *node);
static inline bool avl_tree_ordered_p(struct avl_tree *tree);
static inline bool avl_tree_single_rotate_left_precondition_p(struct avl_tree *node);
static inline bool avl_tree_single_rotate_right_precondition_p(struct avl_tree *node);
static inline bool avl_tree_structure_legal_p(s_avl_tree_t *tree);
static inline bool binary_indexed_tree_number_legal_p(s_binary_indexed_tree_t *tree, uint32 number);
static inline bool binary_indexed_tree_structure_legal_p(s_binary_indexed_tree_t *tree);
static inline bool binary_search_tree_contains_p_i(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
static inline bool binary_search_tree_doubly_child_p(s_binary_search_tree_t *node);
static inline bool binary_search_tree_ordered_p(struct binary_search_tree *tree);
static inline bool binary_search_tree_structure_legal_p(s_binary_search_tree_t *tree);
static inline bool splay_tree_contains_ip(s_splay_tree_t *tree, s_splay_tree_t *node);
static inline bool splay_tree_doubly_child_p(s_splay_tree_t *node);
static inline bool splay_tree_ordered_p(struct splay_tree *tree);
static inline bool splay_tree_structure_legal_p(s_splay_tree_t *tree);
static inline bool trie_tree_root_node_p(s_trie_tree_t *trie);
static inline bool trie_tree_sequence_matched_ip(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
static inline bool trie_tree_structure_legal_ip(s_trie_tree_t *trie);
static inline bool trie_tree_sub_queue_empty_p(s_trie_tree_t *trie);
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
static inline s_binary_search_tree_t * binary_search_tree_insert_i(s_binary_search_tree_t *tree, s_binary_search_tree_t *node);
static inline s_binary_search_tree_t * binary_search_tree_remove_i(s_binary_search_tree_t **tree, s_binary_search_tree_t *node);
static inline s_binary_search_tree_t * binary_search_tree_repeated_remove(s_binary_search_tree_t **tree, s_binary_search_tree_t *node, sint32 direction);
static inline s_binary_search_tree_t ** binary_search_tree_find_ptr_to_max(s_binary_search_tree_t **tree);
static inline s_binary_search_tree_t ** binary_search_tree_find_ptr_to_min(s_binary_search_tree_t **tree);
static inline s_splay_tree_t * splay_tree_find_i(s_splay_tree_t **tree, sint64 nice);
static inline s_splay_tree_t * splay_tree_find_max_i(s_splay_tree_t **tree);
static inline s_splay_tree_t * splay_tree_find_min_i(s_splay_tree_t **tree);
static inline s_splay_tree_t * splay_tree_insert_i(s_splay_tree_t **tree, s_splay_tree_t *node);
static inline s_splay_tree_t * splay_tree_remove_i(s_splay_tree_t **tree, s_splay_tree_t *node);
static inline s_splay_tree_t * splay_tree_repeated_remove(s_splay_tree_t **tree, s_splay_tree_t *node, sint32 direction);
static inline s_splay_tree_t ** splay_tree_find_ptr_to_max(s_splay_tree_t **tree);
static inline s_splay_tree_t ** splay_tree_find_ptr_to_min(s_splay_tree_t **tree);
static inline s_trie_tree_t * trie_tree_node_create(uint32 val);
static inline s_trie_tree_t * trie_tree_scalar_insert(s_trie_tree_t *trie, uint32 val);
static inline s_trie_tree_t * trie_tree_sub_queue_find(s_trie_tree_t *trie, uint32 val);
static inline sint32 ALWAYS_INLINE avl_tree_height_balanced_opt_p(struct avl_tree *tree);
static inline sint32 ALWAYS_INLINE avl_tree_height_opt(struct avl_tree *tree);
static inline sint32 ALWAYS_INLINE avl_tree_height_opt(struct avl_tree *tree);
static inline sint32 avl_tree_height_calculate(struct avl_tree *tree);
static inline sint32 avl_tree_height_internal(struct avl_tree *tree);
static inline sint32 binary_search_tree_height_i(s_binary_search_tree_t *tree);
static inline sint32 splay_tree_height_i(s_splay_tree_t *tree);
static inline sint64 binary_indexed_tree_sum_i(s_binary_indexed_tree_t *tree, uint32 number);
static inline void avl_tree_destroy_i(s_avl_tree_t *tree);
static inline void avl_tree_doubly_child_strip(s_avl_tree_t **node_pre);
static inline void avl_tree_doubly_child_strip_from_max(s_avl_tree_t **node_pre);
static inline void avl_tree_doubly_child_strip_from_min(s_avl_tree_t **node_pre);
static inline void avl_tree_height_update(s_avl_tree_t *tree);
static inline void avl_tree_initial_i(s_avl_tree_t *tree, sint64 nice);
static inline void avl_tree_iterate_i(s_avl_tree_t *tree, void (*handler)(void *));
static inline void avl_tree_lt_doubly_child_strip(s_avl_tree_t **pre, s_avl_tree_t *node);
static inline void avl_tree_rotate_left(s_avl_tree_t **tree);
static inline void avl_tree_rotate_right(s_avl_tree_t **tree);
static inline void avl_tree_swap_child(s_avl_tree_t *a, s_avl_tree_t *b);
static inline void binary_indexed_tree_add_i(s_binary_indexed_tree_t *tree, uint32 number, sint64 val);
static inline void binary_search_tree_child_strip(s_binary_search_tree_t **binary_node, sint32 direction);
static inline void binary_search_tree_child_strip_from_max(s_binary_search_tree_t **binary_node);
static inline void binary_search_tree_child_strip_from_min(s_binary_search_tree_t **binary_node);
static inline void binary_search_tree_destroy_i(s_binary_search_tree_t *tree);
static inline void binary_search_tree_doubly_child_strip(s_binary_search_tree_t **binary_node, sint32 direction);
static inline void binary_search_tree_initial_i(s_binary_search_tree_t *tree, sint64 nice);
static inline void binary_search_tree_iterate_i(s_binary_search_tree_t *tree, void (*handler)(void *));
static inline void binary_search_tree_lt_doubly_child_strip(s_binary_search_tree_t **binary_node);
static inline void binary_search_tree_swap_child(s_binary_search_tree_t *a, s_binary_search_tree_t *b);
static inline void splay_tree_balance_splaying(s_array_stack_t *path_stack);
static inline void splay_tree_balance_splaying_i(s_splay_tree_t **tree, uint32 path_mask);
static inline void splay_tree_balance_splaying_left_to_left(s_splay_tree_t **tree);
static inline void splay_tree_balance_splaying_left_to_right(s_splay_tree_t **tree);
static inline void splay_tree_balance_splaying_right_to_left(s_splay_tree_t **tree);
static inline void splay_tree_balance_splaying_right_to_right(s_splay_tree_t **tree);
static inline void splay_tree_balance_splaying_root(s_splay_tree_t **tree, uint32 path_mask);
static inline void splay_tree_balance_splaying_root_left(s_splay_tree_t **tree);
static inline void splay_tree_balance_splaying_root_right(s_splay_tree_t **tree);
static inline void splay_tree_child_strip(s_splay_tree_t **splay_node, sint32 direction);
static inline void splay_tree_destroy_i(s_splay_tree_t *tree);
static inline void splay_tree_doubly_child_strip(s_splay_tree_t **splay_node, sint32 direction);
static inline void splay_tree_doubly_child_strip_from_max(s_splay_tree_t **splay_node);
static inline void splay_tree_doubly_child_strip_from_min(s_splay_tree_t **splay_node);
static inline void splay_tree_initial_i(s_splay_tree_t *tree, sint64 nice);
static inline void splay_tree_iterate_i(s_splay_tree_t *tree, void (*handler)(void *));
static inline void splay_tree_lt_doubly_child_strip(s_splay_tree_t **splay_node);
static inline void splay_tree_repeated_insert(s_splay_tree_t *splay, s_splay_tree_t *inserted, sint32 path_direction);
static inline void splay_tree_swap_child(s_splay_tree_t *a, s_splay_tree_t *b);
static inline void trie_tree_node_destroy(s_trie_tree_t *trie);
static inline void trie_tree_sequence_insert_i(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
static inline void trie_tree_sequence_remove_i(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
void avl_tree_destroy(s_avl_tree_t **tree);
void avl_tree_initial(s_avl_tree_t *tree, sint64 nice);
void avl_tree_iterate(s_avl_tree_t *tree, void (*handler)(void *));
void binary_indexed_tree_add(s_binary_indexed_tree_t *tree, uint32 number, sint64 val);
void binary_indexed_tree_destroy(s_binary_indexed_tree_t **tree);
void binary_indexed_tree_sub(s_binary_indexed_tree_t *tree, uint32 number, sint64 val);
void binary_search_tree_destroy(s_binary_search_tree_t **tree);
void binary_search_tree_initial(s_binary_search_tree_t *tree, sint64 nice);
void binary_search_tree_iterate(s_binary_search_tree_t *tree, void (*handler)(void *));
void binary_search_tree_nice_set(s_binary_search_tree_t *tree, sint64 nice);
void splay_tree_destroy(s_splay_tree_t **tree);
void splay_tree_initial(s_splay_tree_t *tree, sint64 nice);
void splay_tree_iterate(s_splay_tree_t *tree, void (*handler)(void *));
void trie_tree_destroy(s_trie_tree_t **trie);
void trie_tree_sequence_insert(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
void trie_tree_sequence_remove(s_trie_tree_t *trie, uint32 *sequence, uint32 len);
void trie_tree_string_insert(s_trie_tree_t *trie, char *string);
void trie_tree_string_remove(s_trie_tree_t *trie, char *string);

#endif

