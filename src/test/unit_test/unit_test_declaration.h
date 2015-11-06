#ifndef UNIT_TEST_DECLARATION_H
#define UNIT_TEST_DECLARATION_H


static inline void unit_test_execution_category(const struct test_layer_table *category, struct test_case_filter *filter);
static inline void unit_test_execution_implement(const struct test_layer_table *implement, struct test_case_filter *filter);
static inline void unit_test_execution_interface(const struct test_layer_table *interface, struct test_case_filter *filter);
static inline void unit_test_execution_start(struct test_extra_info *entry, char *content);
static inline void unit_test_maximal_heap_build(void);
static inline void unit_test_maximal_heap_cleanup(void);
static inline void unit_test_maximal_heap_create(void);
static inline void unit_test_maximal_heap_destroy(void);
static inline void unit_test_maximal_heap_empty_p(void);
static inline void unit_test_maximal_heap_full_p(void);
static inline void unit_test_maximal_heap_node_decrease_nice(void);
static inline void unit_test_maximal_heap_node_find(void);
static inline void unit_test_maximal_heap_node_find_max(void);
static inline void unit_test_maximal_heap_node_increase_nice(void);
static inline void unit_test_maximal_heap_node_insert(void);
static inline void unit_test_maximal_heap_node_remove(void);
static inline void unit_test_maximal_heap_node_remove_and_destroy(void);
static inline void unit_test_maximal_heap_node_remove_max(void);
static inline void unit_test_maximal_heap_node_remove_max_and_destroy(void);
static inline void unit_test_maximal_heap_struct_field(void);
static inline void unit_test_min_max_heap_cleanup(void);
static inline void unit_test_min_max_heap_create(void);
static inline void unit_test_min_max_heap_destroy(void);
static inline void unit_test_min_max_heap_empty_p(void);
static inline void unit_test_min_max_heap_full_p(void);
static inline void unit_test_min_max_heap_node_depth(void);
static inline void unit_test_min_max_heap_node_find(void);
static inline void unit_test_min_max_heap_node_find_max(void);
static inline void unit_test_min_max_heap_node_find_min(void);
static inline void unit_test_min_max_heap_node_insert(void);
static inline void unit_test_min_max_heap_node_remove(void);
static inline void unit_test_min_max_heap_node_remove_and_destroy(void);
static inline void unit_test_min_max_heap_node_remove_min(void);
static inline void unit_test_min_max_heap_node_remove_min_and_destroy(void);
static inline void unit_test_min_max_heap_struct_field(void);
static inline void unit_test_minimal_heap_build(void);
static inline void unit_test_minimal_heap_cleanup(void);
static inline void unit_test_minimal_heap_create(void);
static inline void unit_test_minimal_heap_destroy(void);
static inline void unit_test_minimal_heap_empty_p(void);
static inline void unit_test_minimal_heap_full_p(void);
static inline void unit_test_minimal_heap_node_decrease_nice(void);
static inline void unit_test_minimal_heap_node_find(void);
static inline void unit_test_minimal_heap_node_find_min(void);
static inline void unit_test_minimal_heap_node_increase_nice(void);
static inline void unit_test_minimal_heap_node_insert(void);
static inline void unit_test_minimal_heap_node_remove(void);
static inline void unit_test_minimal_heap_node_remove_and_destroy(void);
static inline void unit_test_minimal_heap_node_remove_min(void);
static inline void unit_test_minimal_heap_node_remove_min_and_destroy(void);
static inline void unit_test_minimal_heap_struct_field(void);
static inline void unit_test_result_print(char *name, bool passed);
static void unit_test_array_queue_capacity(void);
static void unit_test_array_queue_cleanup(void);
static void unit_test_array_queue_create(void);
static void unit_test_array_queue_destroy(void);
static void unit_test_array_queue_empty_p(void);
static void unit_test_array_queue_enter(void);
static void unit_test_array_queue_full_p(void);
static void unit_test_array_queue_iterate(void);
static void unit_test_array_queue_leave(void);
static void unit_test_array_queue_space_expand(void);
static void unit_test_array_queue_space_rest(void);
static void unit_test_array_queue_struct_field(void);
static void unit_test_array_stack_capacity(void);
static void unit_test_array_stack_cleanup(void);
static void unit_test_array_stack_create(void);
static void unit_test_array_stack_destroy(void);
static void unit_test_array_stack_empty_p(void);
static void unit_test_array_stack_full_p(void);
static void unit_test_array_stack_iterate(void);
static void unit_test_array_stack_pop(void);
static void unit_test_array_stack_push(void);
static void unit_test_array_stack_space_expand(void);
static void unit_test_array_stack_space_rest(void);
static void unit_test_array_stack_struct_field(void);
static void unit_test_avl_tree_balanced_p(void);
static void unit_test_avl_tree_create(void);
static void unit_test_avl_tree_destroy(void);
static void unit_test_avl_tree_initial(void);
static void unit_test_avl_tree_iterate(void);
static void unit_test_avl_tree_node_contains_p(void);
static void unit_test_avl_tree_node_create(void);
static void unit_test_avl_tree_node_find(void);
static void unit_test_avl_tree_node_find_max(void);
static void unit_test_avl_tree_node_find_min(void);
static void unit_test_avl_tree_node_initial(void);
static void unit_test_avl_tree_node_insert(void);
static void unit_test_avl_tree_node_remove(void);
static void unit_test_avl_tree_node_remove_and_destroy(void);
static void unit_test_avl_tree_struct_field(void);
static void unit_test_binary_search_tree_create(void);
static void unit_test_binary_search_tree_destroy(void);
static void unit_test_binary_search_tree_height(void);
static void unit_test_binary_search_tree_initial(void);
static void unit_test_binary_search_tree_iterate(void);
static void unit_test_binary_search_tree_node_contains_p(void);
static void unit_test_binary_search_tree_node_create(void);
static void unit_test_binary_search_tree_node_find(void);
static void unit_test_binary_search_tree_node_find_max(void);
static void unit_test_binary_search_tree_node_find_min(void);
static void unit_test_binary_search_tree_node_initial(void);
static void unit_test_binary_search_tree_node_insert(void);
static void unit_test_binary_search_tree_node_remove(void);
static void unit_test_binary_search_tree_node_remove_and_destroy(void);
static void unit_test_binary_search_tree_struct_field(void);
static void unit_test_doubly_end_queue_cleanup(void);
static void unit_test_doubly_end_queue_create(void);
static void unit_test_doubly_end_queue_destroy(void);
static void unit_test_doubly_end_queue_empty_p(void);
static void unit_test_doubly_end_queue_head_enter(void);
static void unit_test_doubly_end_queue_head_leave(void);
static void unit_test_doubly_end_queue_iterate(void);
static void unit_test_doubly_end_queue_length(void);
static void unit_test_doubly_end_queue_struct_field(void);
static void unit_test_doubly_end_queue_tail_enter(void);
static void unit_test_doubly_end_queue_tail_leave(void);
static void unit_test_doubly_linked_list_contains_p(void);
static void unit_test_doubly_linked_list_create(void);
static void unit_test_doubly_linked_list_destroy(void);
static void unit_test_doubly_linked_list_initial(void);
static void unit_test_doubly_linked_list_iterate(void);
static void unit_test_doubly_linked_list_length(void);
static void unit_test_doubly_linked_list_merge(void);
static void unit_test_doubly_linked_list_node_append(void);
static void unit_test_doubly_linked_list_node_by_index(void);
static void unit_test_doubly_linked_list_node_copy(void);
static void unit_test_doubly_linked_list_node_create(void);
static void unit_test_doubly_linked_list_node_initial(void);
static void unit_test_doubly_linked_list_node_insert_after(void);
static void unit_test_doubly_linked_list_node_insert_after_risky(void);
static void unit_test_doubly_linked_list_node_insert_before(void);
static void unit_test_doubly_linked_list_node_insert_before_risky(void);
static void unit_test_doubly_linked_list_node_remove(void);
static void unit_test_doubly_linked_list_node_remove_and_destroy(void);
static void unit_test_doubly_linked_list_serialize(void);
static void unit_test_doubly_linked_list_struct_field(void);
static void unit_test_linked_stack_capacity(void);
static void unit_test_linked_stack_cleanup(void);
static void unit_test_linked_stack_create(void);
static void unit_test_linked_stack_destroy(void);
static void unit_test_linked_stack_empty_p(void);
static void unit_test_linked_stack_full_p(void);
static void unit_test_linked_stack_iterate(void);
static void unit_test_linked_stack_pop(void);
static void unit_test_linked_stack_push(void);
static void unit_test_linked_stack_space_expand(void);
static void unit_test_linked_stack_space_rest(void);
static void unit_test_linked_stack_struct_field(void);
static void unit_test_open_addressing_hash_create(void);
static void unit_test_open_addressing_hash_destroy(void);
static void unit_test_open_addressing_hash_find(void);
static void unit_test_open_addressing_hash_insert(void);
static void unit_test_open_addressing_hash_load_factor_calculate(void);
static void unit_test_open_addressing_hash_rehashing(void);
static void unit_test_open_addressing_hash_remove(void);
static void unit_test_open_addressing_hash_struct_field(void);
static void unit_test_separate_chain_hash_create(void);
static void unit_test_separate_chain_hash_destroy(void);
static void unit_test_separate_chain_hash_find(void);
static void unit_test_separate_chain_hash_insert(void);
static void unit_test_separate_chain_hash_load_factor_calculate(void);
static void unit_test_separate_chain_hash_rehashing(void);
static void unit_test_separate_chain_hash_remove(void);
static void unit_test_separate_chain_hash_struct_field(void);
static void unit_test_single_linked_list_contains_p(void);
static void unit_test_single_linked_list_create(void);
static void unit_test_single_linked_list_destroy(void);
static void unit_test_single_linked_list_initial(void);
static void unit_test_single_linked_list_iterate(void);
static void unit_test_single_linked_list_length(void);
static void unit_test_single_linked_list_merge(void);
static void unit_test_single_linked_list_node_append(void);
static void unit_test_single_linked_list_node_by_index(void);
static void unit_test_single_linked_list_node_copy(void);
static void unit_test_single_linked_list_node_create(void);
static void unit_test_single_linked_list_node_initial(void);
static void unit_test_single_linked_list_node_insert_after(void);
static void unit_test_single_linked_list_node_insert_after_risky(void);
static void unit_test_single_linked_list_node_insert_before(void);
static void unit_test_single_linked_list_node_insert_before_risky(void);
static void unit_test_single_linked_list_node_previous(void);
static void unit_test_single_linked_list_node_remove(void);
static void unit_test_single_linked_list_node_remove_and_destroy(void);
static void unit_test_single_linked_list_serialize(void);
static void unit_test_single_linked_list_struct_field(void);
static void unit_test_skip_linked_list_create(void);
static void unit_test_skip_linked_list_destroy(void);
static void unit_test_skip_linked_list_initial(void);
static void unit_test_skip_linked_list_iterate(void);
static void unit_test_skip_linked_list_key_contains_p(void);
static void unit_test_skip_linked_list_length(void);
static void unit_test_skip_linked_list_merge(void);
static void unit_test_skip_linked_list_node_by_index(void);
static void unit_test_skip_linked_list_node_create(void);
static void unit_test_skip_linked_list_node_find_key(void);
static void unit_test_skip_linked_list_node_initial(void);
static void unit_test_skip_linked_list_node_insert(void);
static void unit_test_skip_linked_list_node_remove(void);
static void unit_test_skip_linked_list_node_remove_and_destroy(void);
static void unit_test_skip_linked_list_struct_field(void);
static void unit_test_splay_tree_create(void);
static void unit_test_splay_tree_destroy(void);
static void unit_test_splay_tree_height(void);
static void unit_test_splay_tree_initial(void);
static void unit_test_splay_tree_iterate(void);
static void unit_test_splay_tree_node_contains_p(void);
static void unit_test_splay_tree_node_create(void);
static void unit_test_splay_tree_node_find(void);
static void unit_test_splay_tree_node_find_max(void);
static void unit_test_splay_tree_node_find_min(void);
static void unit_test_splay_tree_node_initial(void);
static void unit_test_splay_tree_node_insert(void);
static void unit_test_splay_tree_node_remove(void);
static void unit_test_splay_tree_node_remove_and_destroy(void);
static void unit_test_splay_tree_struct_field(void);
static void unit_test_stacked_queue_capacity(void);
static void unit_test_stacked_queue_cleanup(void);
static void unit_test_stacked_queue_create(void);
static void unit_test_stacked_queue_destroy(void);
static void unit_test_stacked_queue_empty_p(void);
static void unit_test_stacked_queue_enter(void);
static void unit_test_stacked_queue_full_p(void);
static void unit_test_stacked_queue_iterate(void);
static void unit_test_stacked_queue_leave(void);
static void unit_test_stacked_queue_space_expand(void);
static void unit_test_stacked_queue_space_rest(void);
static void unit_test_stacked_queue_struct_field(void);

#endif
