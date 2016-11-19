#ifndef HAVE_DEFINED_performance_test_H
#define HAVE_DEFINED_performance_test_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

static inline double performance_test_reference_variance_calculate(char *name, sint64 period);
static inline sint64 performance_test_time_stamp_period(void);
static inline sint64 performance_test_time_stamp_timeval_unpack(struct timeval *tv);
static inline struct performance_test_reference * performance_test_reference_entry_find_by_name(char *name);
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
static inline void ptest_binary_search_tree_insert(uint32 count);
static inline void ptest_bitmap_bit_clear(uint32 count);
static inline void ptest_bitmap_bit_clear_p(uint32 count);
static inline void ptest_bitmap_bit_get(uint32 count);
static inline void ptest_bitmap_bit_set(uint32 count);
static inline void ptest_bitmap_bit_set_p(uint32 count);
static inline void ptest_bitmap_create(uint32 count);
static inline void ptest_bitmap_destroy(uint32 count);
static inline void ptest_bitmap_map_cleanup(uint32 count);
static inline void ptest_trie_tree_create(uint32 count);
static inline void ptest_trie_tree_destroy(uint32 count);
static inline void ptest_trie_tree_sequence_insert(uint32 count);
static inline void ptest_trie_tree_sequence_matched_p(uint32 count);
static inline void ptest_trie_tree_sequence_remove(uint32 count);
static inline void ptest_trie_tree_string_insert(uint32 count);
static inline void ptest_trie_tree_string_matched_p(uint32 count);
static inline void ptest_trie_tree_string_remove(uint32 count);
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

#endif

