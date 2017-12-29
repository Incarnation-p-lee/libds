#ifndef HAVE_DEFINED_test_H
#define HAVE_DEFINED_test_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

#if defined DEBUG


#endif

static inline FILE * memory_maps_proc_read(void);
static inline bool test_case_filter_match_p(const struct test_layer_table *category, char *name);
static inline bool test_result_check_bool_p(bool expect, bool get, bool *pass);
static inline bool test_result_check_less_uint32_p(uint32 expect, uint32 limit, bool *pass);
static inline bool test_result_check_native_wide_p(native_wide_t expect, native_wide_t get, bool *pass);
static inline bool test_result_check_not_equal_pointer_p(void *expect, void *get, bool *pass);
static inline bool test_result_check_not_less_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_not_less_uint32_p(uint32 expect, uint32 limit, bool *pass);
static inline bool test_result_check_pointer_p(void *expect, void *get, bool *pass);
static inline bool test_result_check_sint32_p(sint32 expect, sint32 get, bool *pass);
static inline bool test_result_check_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_uint32_p(uint32 expect, uint32 get, bool *pass);
static inline bool utest_directed_graph_path_exist_p(s_array_queue_t *queue);
static inline bool utest_maximal_heap_ordered_p(struct maximal_heap *heap);
static inline bool utest_minimal_heap_ordered_p(struct minimal_heap *heap);
static inline char * memory_maps_one_line_map_name(char *line);
static inline double performance_test_reference_variance_calculate(char *name, sint64 period);
static inline s_binary_search_tree_t * test_binary_search_tree_sample(uint64 range, uint32 count);
static inline s_doubly_end_queue_t * test_doubly_end_queue_sample(uint32 count);
static inline s_doubly_linked_list_t * test_doubly_linked_list_sample(uint32 node_count);
static inline s_graph_t * test_directed_graph_sample(uint64 range, uint32 size);
static inline s_graph_t * test_indirected_graph_sample(uint64 range, uint32 size);
static inline s_single_linked_list_t * test_single_linked_list_sample(uint32 node_count);
static inline s_skip_linked_list_t * test_skip_linked_list_sample(uint32 node_count);
static inline s_splay_tree_t * utest_splay_random_node(s_splay_tree_t *tree);
static inline sint32 test_sort_compare_ptr(const void *a, const void *b);
static inline sint32 test_sort_compare_struct(const void *a, const void *b);
static inline sint32 test_sort_compare_u32(const void *a, const void *b);
static inline sint64 * test_sint64_data_array(uint32 size);
static inline sint64 performance_test_time_stamp_period(void);
static inline sint64 performance_test_time_stamp_timeval_unpack(struct timeval *tv);
static inline sint64 test_sint64_data_sum(sint64 *data, uint32 m, uint32 n);
static inline struct avl_tree * test_avl_tree_sample(uint64 range, uint32 count);
static inline struct leftist_heap * test_leftist_heap_sample(uint64 range, uint32 size);
static inline struct maximal_heap * test_maximal_heap_sample(uint64 range, uint32 size);
static inline struct min_max_heap * test_min_max_heap_sample(uint64 range, uint32 size);
static inline struct minimal_heap * test_minimal_heap_sample(uint64 range, uint32 size);
static inline struct open_addressing_hash * test_open_addressing_hash_sample(uint32 count);
static inline struct performance_test_reference * performance_test_reference_entry_find_by_name(char *name);
static inline struct separate_chain_hash * test_separate_chain_hash_sample(uint32 count);
static inline struct splay_tree * test_splay_tree_sample(uint64 range, uint32 node_count);
static inline struct test_case_filter * test_case_filter_initial(void);
static inline struct test_sort_data * test_sort_data_array(uint32 size);
static inline struct test_sort_data ** test_sort_data_ptr_array(uint32 size);
static inline uint32 * test_uint32_data_array(uint32 size);
static inline uint32 memory_maps_one_line_map_authority(char *line);
static inline void * utest_semaphore_thread_0(void *semaphore_sample);
static inline void * utest_semaphore_thread_1(void *semaphore_sample);
static inline void * utest_spin_lock_thread(void *spin_lock_sample);
static inline void memory_maps_filter_process(FILE *maps);
static inline void memory_maps_one_line_map_boundary(char *line, struct memory_maps *map);
static inline void memory_maps_one_line_process(char *line);
static inline void performance_test_begin_print(char *name);
static inline void performance_test_execution_category(const struct test_layer_table *category, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_implement(const struct test_layer_table *implement, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_interface(const struct test_layer_table *interface, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_start(struct test_extra_info *info, char *content);
static inline void performance_test_leftist_heap_create(uint32 count);
static inline void performance_test_leftist_heap_destroy(uint32 count);
static inline void performance_test_leftist_heap_get_min(uint32 count);
static inline void performance_test_leftist_heap_insert(uint32 count);
static inline void performance_test_leftist_heap_merge(uint32 count);
static inline void performance_test_leftist_heap_node_create(uint32 count);
static inline void performance_test_leftist_heap_remove_min(uint32 count);
static inline void performance_test_leftist_heap_remove_min_and_destroy(uint32 count);
static inline void performance_test_leftist_heap_struct_field(uint32 count);
static inline void performance_test_reference_golden_prepare(const char *fname);
static inline void performance_test_reference_new_writeback(const char *fname);
static inline void performance_test_reference_update(char *raw, struct performance_test_reference *ref);
static inline void performance_test_result_print(char *name, sint64 period);
static inline void performance_test_time_stamp_begin(void);
static inline void performance_test_time_stamp_end(void);
static inline void ptest_avl_tree_contains_p(uint32 count);
static inline void ptest_avl_tree_create(uint32 count);
static inline void ptest_avl_tree_destroy(uint32 count);
static inline void ptest_avl_tree_find(uint32 count);
static inline void ptest_avl_tree_find_max(uint32 count);
static inline void ptest_avl_tree_find_min(uint32 count);
static inline void ptest_avl_tree_height(uint32 count);
static inline void ptest_avl_tree_initial(uint32 count);
static inline void ptest_avl_tree_insert(uint32 count);
static inline void ptest_avl_tree_iterate(uint32 count);
static inline void ptest_avl_tree_remove(uint32 count);
static inline void ptest_binary_search_tree_contains_p(uint32 count);
static inline void ptest_binary_search_tree_create(uint32 count);
static inline void ptest_binary_search_tree_destroy(uint32 count);
static inline void ptest_binary_search_tree_find(uint32 count);
static inline void ptest_binary_search_tree_find_max(uint32 count);
static inline void ptest_binary_search_tree_find_min(uint32 count);
static inline void ptest_binary_search_tree_height(uint32 count);
static inline void ptest_binary_search_tree_initial(uint32 count);
static inline void ptest_binary_search_tree_insert(uint32 count);
static inline void ptest_binary_search_tree_iterate(uint32 count);
static inline void ptest_binary_search_tree_remove(uint32 count);
static inline void ptest_bitmap_bit_clear(uint32 count);
static inline void ptest_bitmap_bit_clear_p(uint32 count);
static inline void ptest_bitmap_bit_get(uint32 count);
static inline void ptest_bitmap_bit_set(uint32 count);
static inline void ptest_bitmap_bit_set_p(uint32 count);
static inline void ptest_bitmap_create(uint32 count);
static inline void ptest_bitmap_destroy(uint32 count);
static inline void ptest_bitmap_map_cleanup(uint32 count);
static inline void ptest_disjoint_set_create(uint32 count);
static inline void ptest_disjoint_set_destroy(uint32 count);
static inline void ptest_disjoint_set_equivalent_p(uint32 count);
static inline void ptest_disjoint_set_find(uint32 count);
static inline void ptest_disjoint_set_union(uint32 count);
static inline void ptest_semaphore_available_p(uint32 count);
static inline void ptest_semaphore_create(uint32 count);
static inline void ptest_semaphore_destroy(uint32 count);
static inline void ptest_semaphore_down(uint32 count);
static inline void ptest_semaphore_up(uint32 count);
static inline void ptest_spin_lock_create(uint32 count);
static inline void ptest_spin_lock_destroy(uint32 count);
static inline void ptest_spin_lock_release(uint32 count);
static inline void ptest_spin_lock_try(uint32 count);
static inline void ptest_splay_tree_contains_p(uint32 count);
static inline void ptest_splay_tree_create(uint32 count);
static inline void ptest_splay_tree_destroy(uint32 count);
static inline void ptest_splay_tree_height(uint32 count);
static inline void ptest_splay_tree_initial(uint32 count);
static inline void ptest_splay_tree_insert(uint32 count);
static inline void ptest_splay_tree_iterate(uint32 count);
static inline void ptest_trie_tree_create(uint32 count);
static inline void ptest_trie_tree_destroy(uint32 count);
static inline void ptest_trie_tree_sequence_insert(uint32 count);
static inline void ptest_trie_tree_sequence_matched_p(uint32 count);
static inline void ptest_trie_tree_sequence_remove(uint32 count);
static inline void ptest_trie_tree_string_insert(uint32 count);
static inline void ptest_trie_tree_string_matched_p(uint32 count);
static inline void ptest_trie_tree_string_remove(uint32 count);
static inline void test_binary_heap_data_randomization(struct heap_data **hd_array, uint32 last);
static inline void test_case_filter_obtain_internal(char *dest, char *arg, uint32 len);
static inline void test_case_list(struct test_extra_info *info, char *content);
static inline void test_case_list_category(const struct test_layer_table *category, struct test_case_filter *filter);
static inline void test_case_list_implement(const struct test_layer_table *implement, struct test_case_filter *filter, char *category);
static inline void test_case_list_interface(const struct test_layer_table *interface, struct test_case_filter *filter, char *category, char *implement);
static inline void test_lock_critical_section_init(void);
static inline void test_parameter_default_entry_set(struct test_suite *suite);
static inline void test_parameter_parser_internal(struct test_suite *suite, char *arg);
static inline void test_sort_data_ptr_array_destroy(struct test_sort_data **data, uint32 size);
static inline void unit_test_begin_print(char *name);
static inline void unit_test_execution_category(const struct test_layer_table *category, struct test_case_filter *filter);
static inline void unit_test_execution_implement(const struct test_layer_table *implement, struct test_case_filter *filter);
static inline void unit_test_execution_interface(const struct test_layer_table *interface, struct test_case_filter *filter);
static inline void unit_test_execution_start(struct test_extra_info *info, char *content);
static inline void unit_test_result_print(char *name, bool passed);
static inline void utest_avl_tree_contains_p(void);
static inline void utest_avl_tree_create(void);
static inline void utest_avl_tree_destroy(void);
static inline void utest_avl_tree_find(void);
static inline void utest_avl_tree_find_max(void);
static inline void utest_avl_tree_find_min(void);
static inline void utest_avl_tree_height(void);
static inline void utest_avl_tree_initial(void);
static inline void utest_avl_tree_insert(void);
static inline void utest_avl_tree_iterate(void);
static inline void utest_avl_tree_iterate_handler(void *val);
static inline void utest_avl_tree_remove(void);
static inline void utest_binary_indexed_tree_add(void);
static inline void utest_binary_indexed_tree_create(void);
static inline void utest_binary_indexed_tree_destroy(void);
static inline void utest_binary_indexed_tree_range_sum(void);
static inline void utest_binary_indexed_tree_sub(void);
static inline void utest_binary_indexed_tree_sum(void);
static inline void utest_binary_search_tree_contains_p(void);
static inline void utest_binary_search_tree_create(void);
static inline void utest_binary_search_tree_destroy(void);
static inline void utest_binary_search_tree_find(void);
static inline void utest_binary_search_tree_find_max(void);
static inline void utest_binary_search_tree_find_min(void);
static inline void utest_binary_search_tree_height(void);
static inline void utest_binary_search_tree_initial(void);
static inline void utest_binary_search_tree_insert(void);
static inline void utest_binary_search_tree_iterate(void);
static inline void utest_binary_search_tree_iterate_handler(void *val);
static inline void utest_binary_search_tree_remove(void);
static inline void utest_bitmap_bit_clear(void);
static inline void utest_bitmap_bit_clear_p(void);
static inline void utest_bitmap_bit_get(void);
static inline void utest_bitmap_bit_set(void);
static inline void utest_bitmap_bit_set_p(void);
static inline void utest_bitmap_create(void);
static inline void utest_bitmap_destroy(void);
static inline void utest_bitmap_map_cleanup(void);
static inline void utest_directed_graph_create(void);
static inline void utest_directed_graph_destroy(void);
static inline void utest_directed_graph_edge_remove(void);
static inline void utest_directed_graph_link(void);
static inline void utest_directed_graph_path_find(void);
static inline void utest_directed_graph_topo_sort(void);
static inline void utest_directed_graph_vertex_remove(void);
static inline void utest_disjoint_set_create(void);
static inline void utest_disjoint_set_destroy(void);
static inline void utest_disjoint_set_equivalent_p(void);
static inline void utest_disjoint_set_find(void);
static inline void utest_disjoint_set_union(void);
static inline void utest_doubly_end_queue_create(void);
static inline void utest_indirected_graph_create(void);
static inline void utest_indirected_graph_destroy(void);
static inline void utest_indirected_graph_edge_remove(void);
static inline void utest_indirected_graph_link(void);
static inline void utest_indirected_graph_vertex_remove(void);
static inline void utest_linked_stack_capacity(void);
static inline void utest_linked_stack_cleanup(void);
static inline void utest_linked_stack_create(void);
static inline void utest_linked_stack_destroy(void);
static inline void utest_linked_stack_empty_p(void);
static inline void utest_linked_stack_full_p(void);
static inline void utest_linked_stack_iterate(void);
static inline void utest_linked_stack_pop(void);
static inline void utest_linked_stack_push(void);
static inline void utest_linked_stack_resize(void);
static inline void utest_linked_stack_rest(void);
static inline void utest_linked_stack_top(void);
static inline void utest_maximal_heap_decrease_nice(void);
static inline void utest_maximal_heap_increase_nice(void);
static inline void utest_min_max_heap_decrease_nice(void);
static inline void utest_min_max_heap_depth(void);
static inline void utest_min_max_heap_increase_nice(void);
static inline void utest_minimal_heap_decrease_nice(void);
static inline void utest_minimal_heap_increase_nice(void);
static inline void utest_semaphore_available_p(void);
static inline void utest_semaphore_create(void);
static inline void utest_semaphore_destroy(void);
static inline void utest_semaphore_down(void);
static inline void utest_semaphore_up(void);
static inline void utest_spin_lock_create(void);
static inline void utest_spin_lock_destroy(void);
static inline void utest_spin_lock_release(void);
static inline void utest_spin_lock_try(void);
static inline void utest_splay_tree_create(void);
static inline void utest_splay_tree_destroy(void);
static inline void utest_splay_tree_height(void);
static inline void utest_splay_tree_initial(void);
static inline void utest_splay_tree_insert(void);
static inline void utest_splay_tree_iterate(void);
static inline void utest_splay_tree_iterate_handler(void *val);
static inline void utest_trie_tree_create(void);
static inline void utest_trie_tree_destroy(void);
static inline void utest_trie_tree_sequence_insert(void);
static inline void utest_trie_tree_sequence_matched_p(void);
static inline void utest_trie_tree_sequence_remove(void);
static inline void utest_trie_tree_string_insert(void);
static inline void utest_trie_tree_string_matched_p(void);
static inline void utest_trie_tree_string_remove(void);
static struct test_case_filter * test_case_filter_obtain(char *arg);
static uint32 test_iterate_reference(void);
static void linked_list_iterate_handler(void *ptr);
static void ptest_avl_tree_balanced_p(uint32 count);
static void ptest_binary_indexed_tree_add(uint32 count);
static void ptest_binary_indexed_tree_create(uint32 count);
static void ptest_binary_indexed_tree_destroy(uint32 count);
static void ptest_binary_indexed_tree_range_sum(uint32 count);
static void ptest_binary_indexed_tree_sub(uint32 count);
static void ptest_binary_indexed_tree_sum(uint32 count);
static void ptest_doubly_end_queue_front_enter(uint32 count);
static void ptest_doubly_end_queue_front_leave(uint32 count);
static void ptest_doubly_end_queue_length(uint32 count);
static void ptest_doubly_end_queue_rear_enter(uint32 count);
static void ptest_doubly_end_queue_rear_leave(uint32 count);
static void ptest_skip_linked_list_contains_p(uint32 count);
static void ptest_skip_linked_list_create_with_key(uint32 count);
static void ptest_skip_linked_list_find_key(uint32 count);
static void ptest_skip_linked_list_insert(uint32 count);
static void ptest_skip_linked_list_remove(uint32 count);
static void ptest_splay_tree_find(uint32 count);
static void ptest_splay_tree_find_max(uint32 count);
static void ptest_splay_tree_find_min(uint32 count);
static void ptest_splay_tree_remove(uint32 count);
static void queue_iterate_handler(void *ptr);
static void stack_iterate_handler(void *ptr);
static void test_case_filter_destroy(struct test_case_filter **filter);
static void test_case_filter_parser(struct test_case_filter *filter, char *arg);
static void test_iterate_reference_clean(void);
static void tree_iterate_handler(void *ptr);
static void unit_test_leftist_heap_create(void);
static void unit_test_leftist_heap_destroy(void);
static void unit_test_leftist_heap_get_min(void);
static void unit_test_leftist_heap_insert(void);
static void unit_test_leftist_heap_merge(void);
static void unit_test_leftist_heap_node_create(void);
static void unit_test_leftist_heap_remove_min(void);
static void unit_test_leftist_heap_remove_min_and_destroy(void);
static void unit_test_leftist_heap_struct_field(void);
static void utest_avl_tree_balanced_p(void);
static void utest_doubly_end_queue_cleanup(void);
static void utest_doubly_end_queue_empty_p(void);
static void utest_doubly_end_queue_front_enter(void);
static void utest_doubly_end_queue_front_leave(void);
static void utest_doubly_end_queue_iterate(void);
static void utest_doubly_end_queue_length(void);
static void utest_doubly_end_queue_rear_enter(void);
static void utest_doubly_end_queue_rear_leave(void);
static void utest_skip_linked_list_contains_p(void);
static void utest_skip_linked_list_create_with_key(void);
static void utest_skip_linked_list_find_key(void);
static void utest_skip_linked_list_insert(void);
static void utest_skip_linked_list_merge(void);
static void utest_skip_linked_list_remove(void);
static void utest_splay_tree_contains_p(void);
static void utest_splay_tree_find(void);
static void utest_splay_tree_find_max(void);
static void utest_splay_tree_find_min(void);
static void utest_splay_tree_remove(void);
static void utest_stacked_queue_cleanup(void);
static void utest_stacked_queue_create(void);
static void utest_stacked_queue_iterate(void);
static void utest_stacked_queue_leave(void);
static void utest_stacked_queue_rest(void);
struct memory_maps * memory_maps_entry_find(char *name);
void memory_maps_obtain(void);
void test_execution_start(void);
void test_parameter_parser(uint32 argc, char **argv);

#endif

