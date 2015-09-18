void
test_execution_start(void)
{
    struct test_entry_list *list;
    static void (*entrance)(struct test_extra_info *info, char *content);

    list = suite.list;

    fprintf(stdout, "\n  >> TEST EXECUTION OF LIBDS  << \n");
    while (NULL != list->name) {
        if (list->enabled) {
            entrance = list->entrance;
            (*entrance)(list->info, suite.content);
        }
        list++;
    }
}

