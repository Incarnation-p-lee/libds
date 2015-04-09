#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

static uint32 malloc_cnt = 0;
static uint32 free_cnt = 0;
static uint32 realloc_cnt = 0;
static uint32 reference = 0;

#define FILTER_LEN 32

struct unit_test_filter {
    char category[FILTER_LEN];
    char implement[FILTER_LEN];
    char interface[FILTER_LEN];
};


void unit_test_perform(char *arg);

void * malloc_wrap(size_t size);
void * realloc_wrap(void *ptr, size_t size);
void free_wrap(void *ptr);
void memory_trace_print(void);
void end_of_report_print(void);


static inline void unit_test_layer_table_category(const struct test_layer_table *category, struct unit_test_filter *filter);
static inline void unit_test_layer_table_implement(const struct test_layer_table *implement, struct unit_test_filter *filter);
static inline void unit_test_layer_table_interface(const struct test_layer_table *interface, struct unit_test_filter *filter);

static inline bool unit_test_layer_table_match_p(const struct test_layer_table *category, char *name);

static void test_result_print(char *name, bool passed);
static sint32 * int_array_generate(sint32 size);
static void linked_list_iterate_handler(void *node);
static void stack_iterate_handler(void *ptr);
static void queue_iterate_handler(void *ptr);
static void tree_iterate_handler(void *ptr);
static inline struct binary_search_tree * test_binary_search_tree_sample(uint64 range, uint32 node_count);
static inline struct single_linked_list * test_single_linked_list_sample(uint32 range, uint32 node_count);
static inline struct doubly_linked_list * test_doubly_linked_list_sample(uint32 range, uint32 node_count);
static inline struct avl_tree * test_avl_tree_sample(uint64 range, uint32 node_count);
static struct unit_test_filter * unit_test_filter_obtain(char *arg);
static void unit_test_filter_parser(struct unit_test_filter *filter, char *arg);
static inline void unit_test_filter_obtain_internal(char *dest, char *arg, uint32 len);
static inline struct unit_test_filter * unit_test_filter_initial(void);
static void unit_test_filter_destroy(struct unit_test_filter **filter);

#endif
