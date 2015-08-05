static void
test_result_print(char *name, bool passed)
{
    sint64 period;
    double variance;
    struct test_performance *entry;

    test_time_stamp_end();
    period = test_time_stamp_period();

    if (!name) {
        pr_log_warn("Unknow Test Function Name, nothing will be done.\n");
        return;
    }

    entry = test_reference_entry_find(name);
    assert(NULL != entry);

    entry->now = period;
    if (0u == entry->ref) {
        entry->ref = period;
    }

    variance = (double)(entry->ref - period) / entry->ref;
    test_result_and_performance_print(variance, passed, name);

    return;
}

static inline void
test_result_and_performance_print(double variance, bool passed, char *name)
{
    variance = variance * 100.0;

    if (passed && (-VARIANCE_LIMIT < variance && variance < VARIANCE_LIMIT)) {
        fprintf(stdout, "    . [32mPass[0m .. %06.2f%% .. %s\n", variance, name);
    } else if (passed && variance > VARIANCE_LIMIT) {
        fprintf(stdout, "    . [32mPass[0m .. [36m%06.2f%%[0m .. %s\n", variance, name);
    } else if (passed && variance < -VARIANCE_LIMIT) {
        fprintf(stdout, "    . [32mPass[0m .. [31m%06.2f%%[0m .. %s\n", -variance, name);
    } else {
        fprintf(stdout, "    . [31mFail[0m .. %s\n", name);
    }

    return;
}

void
memory_trace_print(void)
{
    printf("\n  >> Memory Usage Summary <<\n");
    printf("    . Malloc  %10lu\n", malloc_cnt);
    printf("    . Realloc %10lu\n", realloc_cnt);
    printf("    . Free    %10lu\n", free_cnt);
    printf("  >> Memory End.\n");

    return;
}

void
end_of_report_print(void)
{
    printf("\n  >> End of Data Structure Library.<<\n\n");
}

static void
linked_list_iterate_handler(void *node)
{
    if (node) {
        *(uint32 *)node = 0xDEADu;
    }

    return;
}

static void
stack_iterate_handler(void *ptr)
{
    if (ptr) {
        *(sint32 *)ptr += 1;
    }

    return;
}

static void
queue_iterate_handler(void *ptr)
{
    if (ptr) {
        *(uint32 *)ptr += 1;
    }

    return;
}

static void
tree_iterate_handler(void *ptr)
{
    uint32 *tmp;

    if (ptr) {
        tmp = ptr;
        *tmp += 1;
    }

    return;
}

