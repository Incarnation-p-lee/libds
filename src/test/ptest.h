#ifndef HAVE_PERFORMANCE_TEST
#define HAVE_PERFORMANCE_TEST

#define PERFORMANCE_TEST_NEW            "./performance/performance.new.ref"
#define PERFORMANCE_TEST_GOLDEN         "./performance/performance.golden.ref"
#define PERFORMANCE_TEST_RESULT(symbol) performance_test_result_print( \
    SYM_2_STR(symbol), performance_test_time_stamp_period())
#define PERFORMANCE_TEST_BEGIN(symbol) performance_test_begin_print(SYM_2_STR(symbol))

struct performance_test_reference {
    char   *name;
    /* Ref and Now count in microseconds */
    sint64 ref;
    sint64 now;
};

#define VARIANCE_LIMIT              5.0f
#define PERORMANCE_ENTRY_MAX_SIZE   128

#define PERFORMANCE_TEST_CHECKPOINT performance_test_time_stamp_begin()
#define PERFORMANCE_TEST_ENDPOINT   performance_test_time_stamp_end()

static struct timeval chk_pnt_bgn;
static struct timeval chk_pnt_end;

#endif
