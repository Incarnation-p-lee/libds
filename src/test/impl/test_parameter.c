void
test_parameter_parser(uint32 argc, char **argv)
{
    uint32 iter;
    struct test_suite *task;

    iter = 1;
    task = &suite;
    if (!*argv || !argv) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        while (iter < argc) {
            test_parameter_parser_internal(task, argv[iter++]);
        }

        /*
         * if content of suite has not been set
         */
        if ('\0' == task->content[0]) {
            strcpy(task->content, "*.*.*");
        }

        test_parameter_default_entry_set(task);
    }
}

static inline void
test_parameter_default_entry_set(struct test_suite *suite)
{
    struct test_entry_list *list;

    assert_exit(NULL != suite);
    assert_exit(NULL != suite->list);

    list = suite->list;

    while (list->name) {
        if (list->enabled) {
            return;
        }
        list++;
    }

    suite->list[UNIT_TEST].enabled = true;
}

static inline void
test_parameter_parser_internal(struct test_suite *suite, char *arg)
{
    char *tmp;
    uint32 len;
    struct test_entry_list *list;

    assert_exit(NULL != arg);
    assert_exit(NULL != suite);
    assert_exit(NULL != suite->list);

    list = suite->list;

    if ('-' == arg[0]) {
        if (!strcmp("-l", arg) || !strcmp("-list", arg)
            || !strcmp("--list", arg)) {
            list[TEST_CASE_LIST].enabled = true;
        } else if (!dp_strncmp("-p", arg, strlen("-p"))
            || !dp_strncmp("-perf", arg, strlen("-perf"))
            || !dp_strncmp("-perf", arg, strlen("--perf"))) {
            list[PERFORMANCE_TEST].enabled = true;
            tmp = dp_strchr(arg, '=');

            if (!tmp) {
                list[PERFORMANCE_TEST].info->count = DEFAULT_ITERATION_CNT;
            } else {
                tmp++;
                list[PERFORMANCE_TEST].info->count = atoi(tmp);
            }
        } else if (!dp_strncmp("-u", arg, strlen("-u"))
            || !dp_strncmp("-unit", arg, strlen("-uint"))
            || !dp_strncmp("-unit", arg, strlen("--unit"))) {
            list[UNIT_TEST].enabled = true;
        } else {
            list[UNIT_TEST].enabled = true;
            pr_log_warn("Invalid arguments specified, executing unit test.\n");
        }
    } else {
        len = strlen(arg);
        assert_exit(len < CONTENT_LEN);

        strncpy(suite->content, arg, len);
        suite->content[len] = '\0';
    }
}

