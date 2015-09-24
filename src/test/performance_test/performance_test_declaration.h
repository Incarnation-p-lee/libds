#ifndef PERFORMANCE_TEST_DECLARATION_H
#define PERFORMANCE_TEST_DECLARATION_H


static inline double performance_test_reference_variance_calculate(char *name, sint64 period);
static inline sint64 performance_test_time_stamp_period(void);
static inline sint64 performance_test_time_stamp_timeval_unpack(struct timeval *tv);
static inline struct performance_test_reference * performance_test_reference_entry_find_by_name(char *name);
static inline void performance_test_execution_category(const struct test_layer_table *category, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_implement(const struct test_layer_table *implement, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_interface(const struct test_layer_table *interface, struct test_case_filter *filter, struct test_extra_info *info);
static inline void performance_test_execution_start(struct test_extra_info *info, char *content);
static inline void performance_test_reference_golden_prepare(const char *fname);
static inline void performance_test_reference_new_writeback(const char *fname);
static inline void performance_test_reference_update(char *raw, struct performance_test_reference *ref);
static inline void performance_test_result_print(char *name, sint64 period);
static inline void performance_test_time_stamp_begin(void);
static inline void performance_test_time_stamp_end(void);
static void performance_test_single_linked_list_struct_field(uint32 count);

#endif
