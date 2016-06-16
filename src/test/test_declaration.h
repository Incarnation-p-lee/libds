#ifndef HAVE_DEFINED_test_H
#define HAVE_DEFINED_test_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

static inline FILE * memory_maps_proc_read(void);
static inline bool test_case_filter_match_p(const struct test_layer_table *category, char *name);
static inline bool test_result_check_bool_p(bool expect, bool get, bool *pass);
static inline bool test_result_check_double_p(double expect, double get, bool *pass);
static inline bool test_result_check_float_p(float expect, float get, bool *pass);
static inline bool test_result_check_less_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_less_uint32_p(uint32 expect, uint32 limit, bool *pass);
static inline bool test_result_check_more_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_not_equal_pointer_p(void *expect, void *get, bool *pass);
static inline bool test_result_check_not_less_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_not_less_uint32_p(uint32 expect, uint32 limit, bool *pass);
static inline bool test_result_check_pointer_p(void *expect, void *get, bool *pass);
static inline bool test_result_check_sint32_p(sint32 expect, sint32 get, bool *pass);
static inline bool test_result_check_sint64_p(sint64 expect, sint64 get, bool *pass);
static inline bool test_result_check_uint32_p(uint32 expect, uint32 get, bool *pass);
static inline bool test_result_check_uint64_p(uint64 expect, uint64 get, bool *pass);
static inline char * memory_maps_one_line_map_name(char *line);
static inline sint32 test_sort_compare_ptr(const void *a, const void *b);
static inline sint32 test_sort_compare_struct(const void *a, const void *b);
static inline sint32 test_sort_compare_u32(const void *a, const void *b);
static inline sint64 * test_sint64_data_array(uint32 size);
static inline sint64 test_sint64_data_sum(sint64 *data, int m, int n, int size);
static inline struct avl_tree * test_avl_tree_sample(uint64 range, uint32 count);
static inline struct binary_search_tree * test_binary_search_tree_sample(uint64 range, uint32 count);
static inline struct doubly_end_queue * test_doubly_end_queue_sample(uint32 count);
static inline struct doubly_linked_list * test_doubly_linked_list_sample(uint32 range, uint32 node_count);
static inline struct leftist_heap * test_leftist_heap_sample(uint64 range, uint32 size);
static inline struct maximal_heap * test_maximal_heap_sample(uint64 range, uint32 size);
static inline struct min_max_heap * test_min_max_heap_sample(uint64 range, uint32 size);
static inline struct minimal_heap * test_minimal_heap_sample(uint64 range, uint32 size);
static inline struct open_addressing_hash * test_open_addressing_hash_sample(uint32 count);
static inline struct separate_chain_hash * test_separate_chain_hash_sample(uint32 count);
static inline struct single_linked_list * test_single_linked_list_sample(uint32 range, uint32 node_count);
static inline struct skip_linked_list * test_skip_linked_list_sample(uint32 range, uint32 count);
static inline struct splay_tree * test_splay_tree_sample(uint64 range, uint32 node_count);
static inline struct test_case_filter * test_case_filter_initial(void);
static inline struct test_sort_data * test_sort_data_array(uint32 size);
static inline struct test_sort_data ** test_sort_data_ptr_array(uint32 size);
static inline uint32 * test_uint32_data_array(uint32 size);
static inline uint32 memory_maps_one_line_map_authority(char *line);
static inline void memory_maps_filter_process(FILE *maps);
static inline void memory_maps_one_line_map_boundary(char *line, struct memory_maps *map);
static inline void memory_maps_one_line_process(char *line, uint32 len);
static inline void test_binary_heap_data_randomization(struct heap_data **hd_array, uint32 last);
static inline void test_case_filter_obtain_internal(char *dest, char *arg, uint32 len);
static inline void test_case_list(struct test_extra_info *info, char *content);
static inline void test_case_list_category(const struct test_layer_table *category, struct test_case_filter *filter);
static inline void test_case_list_implement(const struct test_layer_table *implement, struct test_case_filter *filter, char *category);
static inline void test_case_list_interface(const struct test_layer_table *interface, struct test_case_filter *filter, char *category, char *implement);
static inline void test_parameter_default_entry_set(struct test_suite *suite);
static inline void test_parameter_parser_internal(struct test_suite *suite, char *arg);
static inline void test_sort_data_ptr_array_destroy(struct test_sort_data **data, uint32 size);
static struct test_case_filter * test_case_filter_obtain(char *arg);
static void linked_list_iterate_handler(void *node);
static void queue_iterate_handler(void *ptr);
static void stack_iterate_handler(void *ptr);
static void test_case_filter_destroy(struct test_case_filter **filter);
static void test_case_filter_parser(struct test_case_filter *filter, char *arg);
static void test_iterate_reference_clean(void);
static void tree_iterate_handler(void *ptr);
struct memory_maps * memory_maps_entry_find(char *name);
void * malloc_wrap(size_t size);
void * realloc_wrap(void *ptr, size_t size);
void free_wrap(void *ptr);
void libds_log_file_close(void);
void libds_log_file_create(void);
void libds_log_print(enum log_level lvl, const char *msg);
void memory_maps_obtain(void);
void memory_trace_print(void);
void test_execution_start(void);
void test_parameter_parser(uint32 argc, char **argv);

#endif

