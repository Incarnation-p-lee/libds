static inline void
performance_test_time_stamp_begin(void)
{
    dp_gettimeofday(&chk_pnt_bgn, NULL);
}

static inline void
performance_test_time_stamp_end(void)
{
    dp_gettimeofday(&chk_pnt_end, NULL);
}

static inline sint64
performance_test_time_stamp_timeval_unpack(struct timeval *tv)
{
    dp_assert(NULL != tv);

    return (sint64)(tv->tv_sec * 1000000 + tv->tv_usec);
}

static inline sint64
performance_test_time_stamp_period(void)
{
    sint64 end;
    sint64 bgn;

    end = performance_test_time_stamp_timeval_unpack(&chk_pnt_end);
    bgn = performance_test_time_stamp_timeval_unpack(&chk_pnt_bgn);
    dp_assert(end > bgn);

    return end - bgn;
}

