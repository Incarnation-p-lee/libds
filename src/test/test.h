#ifndef HAVE_TEST_H
#define HAVE_TEST_H

#define TEST_PERFORMANCE_CHECKPOINT test_time_stamp_begin()
#define VARIANCE_LIMIT              3.0f

static uint64 malloc_cnt = 0;
static uint64 free_cnt = 0;
static uint64 realloc_cnt = 0;
static uint32 reference = 0;
static uint32 iteration = 0;

static struct timeval chk_pnt_bgn;
static struct timeval chk_pnt_end;

static FILE *test_performance_file;

#endif
