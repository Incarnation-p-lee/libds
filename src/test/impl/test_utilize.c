void
memory_trace_print(void)
{
    printf("  >> Memory Usage Summary <<\n");
    printf("    . Malloc  %10"U64_MDF_U"\n", malloc_cnt);
    printf("    . Realloc %10"U64_MDF_U"\n", realloc_cnt);
    printf("    . Free    %10"U64_MDF_U"\n", free_cnt);
    printf("  >> Memory End <<\n\n");

    if (free_cnt != malloc_cnt) {
        printf("Memory leak at malloc %10"U64_MDF_U" <=> free %10"U64_MDF_U"\n",
            malloc_cnt, free_cnt);
        exit(1);
    }
}

void
end_of_report_print(void)
{
    printf("  >> End of Data Structure Library <<\n\n");
}

static void
linked_list_iterate_handler(void *node)
{
    uint32 *tmp;

    if (node) {
        tmp = node;
        *tmp += 1;
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

