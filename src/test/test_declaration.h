#ifndef TEST_DECLARATION_H
#define TEST_DECLARATION_H


static inline bool test_result_check_bool_p(bool get, bool expect, bool *pass);
static inline bool test_result_check_double_p(double get, double expect, bool *pass);
static inline bool test_result_check_float_p(float get, float expect, bool *pass);
static inline bool test_result_check_less_uint32_p(uint32 get, uint32 limit, bool *pass);
static inline bool test_result_check_not_less_uint32_p(uint32 get, uint32 limit, bool *pass);
static inline bool test_result_check_pointer_p(void *get, void *expect, bool *pass);
static inline bool test_result_check_sint32_p(sint32 get, sint32 expect, bool *pass);
static inline bool test_result_check_sint64_p(sint64 get, sint64 expect, bool *pass);
static inline bool test_result_check_uint32_p(uint32 get, uint32 expect, bool *pass);
static inline bool test_result_check_uint64_p(uint64 get, uint64 expect, bool *pass);
static inline sint64 test_time_stamp_period(void);
static inline sint64 test_time_stamp_timeval_unpack(struct timeval *tv);
static inline struct test_performance * test_reference_entry_find(char *name);
static inline void test_performance_result_writeback(const char *fname, struct test_performance *cate);
static inline void test_reference_prepare(const char *fname, struct test_performance *cate);
static inline void test_reference_update(char *raw, struct test_performance *ref);
static inline void test_result_and_performance_print(double variance, bool passed, char *name);
static inline void test_time_stamp_begin(void);
static inline void test_time_stamp_end(void);
static uint32 test_utilize_iteration(void);
static void linked_list_iterate_handler(void *node);
static void queue_iterate_handler(void *ptr);
static void stack_iterate_handler(void *ptr);
static void test_result_print(char *name, bool passed);
static void tree_iterate_handler(void *ptr);
void * malloc_wrap(size_t size);
void * realloc_wrap(void *ptr, size_t size);
void end_of_report_print(void);
void free_wrap(void *ptr);
void memory_trace_print(void);

#endif
