static struct test_case_filter *
test_case_filter_obtain(char *arg)
{
    struct test_case_filter *filter;

    filter = test_case_filter_initial();
    if (!arg) {
        test_case_filter_obtain_internal(filter->category, "*", 1);
        test_case_filter_obtain_internal(filter->implement, "*", 1);
        test_case_filter_obtain_internal(filter->interface, "*", 1);
    } else {
        test_case_filter_parser(filter, arg);
    }

    return filter;
}

static void
test_case_filter_parser(struct test_case_filter *filter, char *arg)
{
    char *tmp;
    uint32 dist;

    tmp = strchr(arg, '.');
    if (!tmp) {
        goto INVFMT;
    } else {
        dist = (uint32)(tmp - arg);
        test_case_filter_obtain_internal(filter->category, arg, dist);

        arg = ++tmp;
        tmp = strchr(arg, '.');
        if (!tmp) {
            goto INVFMT;
        } else {
            dist = (uint32)(tmp - arg);
            test_case_filter_obtain_internal(filter->implement, arg, dist);

            arg = ++tmp;
            dist = (uint32)strlen(arg);
            if (!dist) {
                goto INVFMT;
            } else {
                test_case_filter_obtain_internal(filter->interface, arg, dist);
            }
        }
        return;
    }

INVFMT:
    pr_log_err("Invalid filter format detected, use *.*.* style filter.\n");
    return;
}

static inline void
test_case_filter_obtain_internal(char *dest, char *arg, uint32 len)
{
    assert(NULL != arg);
    assert(NULL != dest);

    memcpy(dest, arg, len);
}

static inline struct test_case_filter *
test_case_filter_initial(void)
{
    struct test_case_filter *filter;

    filter = memory_cache_allocate(sizeof(*filter));

    if (!complain_no_memory_p(filter)) {
        memset(filter, '\0', sizeof(*filter));
    }

    return filter;
}

static void
test_case_filter_destroy(struct test_case_filter **filter)
{
    assert(NULL != filter);

    memory_cache_free(*filter);
    *filter = NULL;
}

