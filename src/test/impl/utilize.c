static void
test_result_print(char *name, bool passed)
{
    char *msg = "Unknown Test Function";
    uint32 period;
    uint32 ref;
    float variance;

    if (name) {
        msg = name;
    }

    period = test_time_stamp_period();
    ref = unit_test_reference_entry_find(name);
    variance = (float)(ref - period) / ref;

    if (passed && variance > VARIANCE_LIMIT) {
        fprintf(stdout, "    . [32mPass[0m .. %f .. %s\n", variance, msg);
    if (passed && -variance > VARIANCE_LIMIT) {
        fprintf(stdout, "    . [32mPass[0m .. %f .. %s\n", -variance, msg);
    } else {
        fprintf(stdout, "    . [31mFail[0m .. %s\n", msg);
    }

    return;
}

void
memory_trace_print(void)
{
    printf("\n  >> Memory Usage Summary <<\n");
    printf("    . Malloc  %10u\n", malloc_cnt);
    printf("    . Realloc %10u\n", realloc_cnt);
    printf("    . Free    %10u\n", free_cnt);
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

static sint32 *
int_array_generate(sint32 size)
{
    sint32 *raw;
    register sint32 *iter;

    raw = NULL;
    if (size > 0) {
        raw = (sint32 *)malloc_ds(sizeof(*raw) * size);
        if (raw) {
            iter = raw;
            while (iter < raw + size) {
                *iter++ = rand();
            }
        }
    }

    return raw;
}
