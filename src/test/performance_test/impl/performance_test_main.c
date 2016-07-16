static inline void
performance_test_execution_start(struct test_extra_info *info, char *content)
{
    struct test_case_filter *filter;

    assert_exit(NULL != content);

    performance_test_reference_golden_prepare(PERFORMANCE_TEST_GOLDEN);
    filter = test_case_filter_obtain(content);

    dp_fprintf(stdout, "  >> PERFORMANCE TEST << \n");
    performance_test_execution_category(test_category, filter, info);

    test_case_filter_destroy(&filter);
    performance_test_reference_new_writeback(PERFORMANCE_TEST_NEW);
}

static inline void
performance_test_execution_category(const struct test_layer_table *category,
    struct test_case_filter *filter, struct test_extra_info *info)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (test_case_filter_match_p(category, tmp)) {
            performance_test_execution_implement(category->junior, filter, info);
        }
        category++;
    }
}

static inline void
performance_test_execution_implement(const struct test_layer_table *implement,
    struct test_case_filter *filter, struct test_extra_info *info)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (test_case_filter_match_p(implement, tmp)) {
            performance_test_execution_interface(implement->junior, filter, info);
        }
        implement++;
    }

    dp_fprintf(stdout, "\n");
}

static inline void
performance_test_execution_interface(const struct test_layer_table *interface,
    struct test_case_filter *filter, struct test_extra_info *info)
{
    char *tmp;

    tmp = filter->interface;

    while (interface->name) {
        if (test_case_filter_match_p(interface, tmp)) {
            if (interface->entity.performance) {
                interface->entity.performance(info->count);
            }
        }
        interface++;
    }

    dp_fprintf(stdout, "\n");
}

static inline void
performance_test_begin_print(char *name)
{
    if (!name) {
        pr_log_warn("Unknow Test Function Name, nothing will be done.\n");
    } else {
        dp_fprintf(stdout, "    . Holding   .. 0xxxxxxxxxxx micro-seconds .. %s\r", name);
        dp_fflush(stdout);
    }
}

static inline void
performance_test_result_print(char *name, sint64 period)
{
    double variance;

    if (!name) {
        pr_log_warn("Unknow Test Function Name, nothing will be done.\n");
        return;
    }

    variance = performance_test_reference_variance_calculate(name, period);

    variance = variance * 100.0;

    if (-VARIANCE_LIMIT < variance && variance < VARIANCE_LIMIT) {
        dp_fprintf(stdout, "    . %08.3f%% .. %#012"S64_MDF_X" micro-seconds .. %s\n", variance, period, name);
    } else if (-VARIANCE_LIMIT > variance) {
        dp_fprintf(stdout, "    . [35m%08.3f%%[0m .. %#012"S64_MDF_X" micro-seconds .. %s\n", -variance, period, name);
    } else {
        dp_fprintf(stdout, "    . [36m%08.3f%%[0m .. %#012"S64_MDF_X" micro-seconds .. %s\n", variance, period, name);
    }
}

