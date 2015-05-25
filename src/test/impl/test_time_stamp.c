static inline void
test_time_stamp_begin(void)
{
    gettimeofday(&chk_pnt_bgn);
}

static inline void
test_time_stamp_end(void)
{
    gettimeofday(&chk_pnt_end);
}

static inline uint32
test_time_stamp_timeval_unpack(struct timeval *tv)
{
    assert(NULL != tv);

    return (uint32)(tv->tv_sec * 60 + tv->tv_usec)
}

static inline uint32
test_time_stamp_period(void)
{
    return test_time_stamp_timeval_unpack(&chk_pnt_end) -
        test_time_stamp_timeval_unpack(&chk_pnt_bgn);
}
