void
memory_trace_print(void)
{
    dp_printf("  >> Memory Usage Summary <<\n");
    dp_printf("    . Malloc  %10"U64_MDF_U"\n", malloc_cnt);
    dp_printf("    . Realloc %10"U64_MDF_U"\n", realloc_cnt);
    dp_printf("    . Free    %10"U64_MDF_U"\n", free_cnt);
    dp_printf("  >> Memory End <<\n\n");

    if (free_cnt != malloc_cnt) {
        dp_printf("Memory leak at dp_malloc %10"U64_MDF_U" <=> dp_free %10"U64_MDF_U"\n",
            malloc_cnt, free_cnt);
        dp_exit(1);
    }
}

static uint32
test_iterate_reference(void)
{
    return reference;
}

static void
linked_list_iterate_handler(void *ptr)
{
    reference++;
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
    reference++;
}

static void
test_iterate_reference_clean(void)
{
    reference = 0;
}

