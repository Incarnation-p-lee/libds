#ifndef HAVE_TEST_H
#define HAVE_TEST_H

#define TEST_PERFORMANCE_CHECKPOINT test_time_stamp_begin()
#define VARIANCE_LIMIT              3.0f

static uint64 malloc_cnt = 0;
static uint64 free_cnt = 0;
static uint64 realloc_cnt = 0;
static uint32 reference = 0;

static struct timeval chk_pnt_bgn;
static struct timeval chk_pnt_end;

static FILE *test_performance_file;

void * malloc_wrap(size_t size);
void * realloc_wrap(void *ptr, size_t size);
void free_wrap(void *ptr);
void memory_trace_print(void);
void end_of_report_print(void);
void test_perform(struct option_set *opts);

static void test_result_print(char *name, bool passed);
static void linked_list_iterate_handler(void *node);
static void stack_iterate_handler(void *ptr);
static void queue_iterate_handler(void *ptr);
static void tree_iterate_handler(void *ptr);
static inline void test_result_and_performance_print(double variance, bool passed, char *name);

#endif
