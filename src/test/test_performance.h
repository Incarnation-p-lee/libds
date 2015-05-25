#ifndef HAVE_TEST_PERFORMANCE_H
#define HAVE_TEST_PERFORMANCE_H

#define PERORMANCE_ENTRY_MAX_SIZE 128

struct test_performance {
    char   *name;
    /* Ref and Now count in microseconds */
    sint64 ref;
    sint64 now;
};

static inline sint64 test_time_stamp_period(void);
static inline sint64 test_time_stamp_timeval_unpack(struct timeval *tv);
static inline void test_time_stamp_end(void);
static inline void test_time_stamp_begin(void);

static inline void test_reference_prepare(const char *fname, struct test_performance *cate);
static inline void test_reference_update(char *raw, struct test_performance *ref);
static inline struct test_performance * test_reference_entry_find(char *name);
static inline void test_performance_result_writeback(const char *fname, struct test_performance *cate);


#endif
