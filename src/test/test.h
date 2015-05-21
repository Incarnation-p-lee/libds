#ifndef HAVE_TEST_H
#define HAVE_TEST_H


static uint32 malloc_cnt = 0;
static uint32 free_cnt = 0;
static uint32 realloc_cnt = 0;
static uint32 reference = 0;

void * malloc_wrap(size_t size);
void * realloc_wrap(void *ptr, size_t size);
void free_wrap(void *ptr);
void memory_trace_print(void);
void end_of_report_print(void);
void test_perform(struct option_set *opts);

static void test_result_print(char *name, bool passed);
static sint32 * int_array_generate(sint32 size);
static void linked_list_iterate_handler(void *node);
static void stack_iterate_handler(void *ptr);
static void queue_iterate_handler(void *ptr);
static void tree_iterate_handler(void *ptr);
static inline struct binary_search_tree * unit_test_binary_search_tree_sample(uint64 range, uint32 node_count);
static inline struct single_linked_list * unit_test_single_linked_list_sample(uint32 range, uint32 node_count);
static inline struct doubly_linked_list * unit_test_doubly_linked_list_sample(uint32 range, uint32 node_count);
static inline struct avl_tree * unit_test_avl_tree_sample(uint64 range, uint32 node_count);

#endif
