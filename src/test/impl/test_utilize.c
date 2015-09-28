void
memory_trace_print(void)
{
    printf("  >> Memory Usage Summary <<\n");
    printf("    . Malloc  %10lu\n", malloc_cnt);
    printf("    . Realloc %10lu\n", realloc_cnt);
    printf("    . Free    %10lu\n", free_cnt);
    printf("  >> Memory End <<\n");
}

void
end_of_report_print(void)
{
    printf("\n  >> End of Data Structure Library <<\n\n");
}

static void
linked_list_iterate_handler(void *node)
{
    if (node) {
        *(uint32 *)node = 0xDEADu;
    }
}

static void
stack_iterate_handler(void *ptr)
{
    if (ptr) {
        *(sint32 *)ptr += 1;
    }
}

static void
queue_iterate_handler(void *ptr)
{
    if (ptr) {
        *(uint32 *)ptr += 1;
    }
}

static void
tree_iterate_handler(void *ptr)
{
    uint32 *tmp;

    if (ptr) {
        tmp = ptr;
        *tmp += 1;
    }
}

