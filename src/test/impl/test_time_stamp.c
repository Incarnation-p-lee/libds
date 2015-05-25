static inline void
test_time_stamp_begin(void)
{
    gettimeofday(&chk_pnt_bgn, NULL);
}

static inline void
test_time_stamp_end(void)
{
    gettimeofday(&chk_pnt_end, NULL);
}

static inline sint64
test_time_stamp_timeval_unpack(struct timeval *tv)
{
    assert(NULL != tv);

    return (sint64)(tv->tv_sec * 1000000 + tv->tv_usec);
}

static inline sint64
test_time_stamp_period(void)
{
    return test_time_stamp_timeval_unpack(&chk_pnt_end) -
        test_time_stamp_timeval_unpack(&chk_pnt_bgn);
}
