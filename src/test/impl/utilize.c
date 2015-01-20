static void
test_result_print(char *name, bool passed)
{
   char *msg = "Unknown Test Function";

   if (name) {
      msg = name;
   }

   if (passed) {
       fprintf(stdout, "  . [32mPass[0m ... %s\n", msg);
   } else {
       fprintf(stdout, "  . [31mFail[0m ... %s\n", msg);
   }

   return;
}

void
memory_trace_print(void)
{
    printf("\n  >> Memory Usage Summary <<\n");
    printf("  . Malloc  %10u\n", malloc_cnt);
    printf("  . Realloc %10u\n", realloc_cnt);
    printf("  . Free    %10u\n", free_cnt);
    printf("  >> Memory End.\n\n");
}

static void
dlinked_list_iterate_handler(struct doubly_linked_list *node)
{
    if (node) {
        node->id = 0xDEADu;
    }

    return;
}

static void
slinked_list_iterate_handler(struct single_linked_list *node)
{
    if (node) {
        node->id = 0xDAEDu;
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
