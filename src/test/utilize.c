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
    printf("  >> Memory Usage Summary <<\n\n");
    printf("  . Malloc %10d\n", malloc_cnt);
    printf("  . Free   %10d\n", free_cnt);
    printf("  >> Memory End.\n\n");
}

static void
dlinked_list_iterate_handler(struct doubly_linked_list *node)
{
    if (node) {
        node->index = 0xDEAD;
    }

    return;
}

static void
slinked_list_iterate_handler(struct single_linked_list *node)
{
    if (node) {
        node->index = 0xDAED;
    }

    return;
}
