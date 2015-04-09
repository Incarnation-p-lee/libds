#include <string.h>
#include <assert.h>

static struct unit_test_filter *
unit_test_filter_obtain(char *arg)
{
    char *tmp;
    struct unit_test_filter *filter;

    tmp = arg;
    filter = unit_test_filter_initial();
    if (!tmp) {
        unit_test_filter_obtain_internal(filter->category, "*", 1);
        unit_test_filter_obtain_internal(filter->implement, "*", 1);
        unit_test_filter_obtain_internal(filter->interface, "*", 1);
    } else {
        unit_test_filter_parser(filter, arg);
    }

    return filter;
}

static void
unit_test_filter_parser(struct unit_test_filter *filter, char *arg)
{
    char *tmp;
    uint32 dist;

    tmp = strchr(arg, '.');
    if (!tmp) {
        goto INVFMT;
    } else {
        dist = (uint32)(tmp - arg);
        unit_test_filter_obtain_internal(filter->category, arg, dist);

        arg = ++tmp;
        tmp = strchr(arg, '.');
        if (!tmp) {
            goto INVFMT;
        } else {
            dist = (uint32)(tmp - arg);
            unit_test_filter_obtain_internal(filter->implement, arg, dist);

            arg = ++tmp;
            dist = (uint32)strlen(arg);
            if (!dist) {
                goto INVFMT;
            } else {
                unit_test_filter_obtain_internal(filter->interface, arg, dist);
            }
        }
        return;
    }

INVFMT:
    pr_log_err("Invalid filter format detected, use *.*.* style filter.\n");
    return;
}

static inline void
unit_test_filter_obtain_internal(char *dest, char *arg, uint32 len)
{
    assert(NULL != arg);
    assert(NULL != dest);

    memcpy(dest, arg, len);
}

static inline struct unit_test_filter *
unit_test_filter_initial(void)
{
    struct unit_test_filter *filter;

    filter = malloc_ds(sizeof(*filter));
    if (!filter) {
        pr_log_err("Fail to get memory from system.\n");
    }

    memset(filter, '\0', sizeof(*filter));

    return filter;
}

static void
unit_test_filter_destroy(struct unit_test_filter **filter)
{
    assert(NULL != filter);

    free_ds(*filter);
    *filter = NULL;
}
