#ifndef HAVE_PERFORMANCE_TEST
#define HAVE_PERFORMANCE_TEST

#define PERFORMANCE_TEST_GOLDEN "./performance/performance.golden.ref"
#define PERFORMANCE_TEST_NEW    "./performance/performance.new.ref"

struct performance_test_reference {
    char   *name;
    /* Ref and Now count in microseconds */
    sint64 ref;
    sint64 now;
};

#define PERORMANCE_ENTRY_MAX_SIZE   128
#define PERFORMANCE_TEST_CHECKPOINT performance_test_time_stamp_begin()
#define PERFORMANCE_TEST_ENDPOINT   performance_test_time_stamp_end()
#define VARIANCE_LIMIT              5.0f

static struct timeval chk_pnt_bgn;
static struct timeval chk_pnt_end;

#endif

