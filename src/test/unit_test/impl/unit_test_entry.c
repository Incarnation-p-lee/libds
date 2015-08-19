void
unit_test_perform(char *arg)
{
    struct unit_test_filter *filter;

    filter = unit_test_filter_obtain(arg);
    test_reference_prepare(UNIT_TEST_REF_GOLDEN, unit_test_performance);

    unit_test_layer_table_category_perform(unit_test_category, filter);

    unit_test_filter_destroy(&filter);
    test_performance_result_writeback(UNIT_TEST_REF_NEW, unit_test_performance);
}

void
unit_test_list(char *arg)
{
    struct unit_test_filter *filter;

    filter = unit_test_filter_obtain(arg);
    unit_test_layer_table_category_list(unit_test_category, filter);
    unit_test_filter_destroy(&filter);
}

void
unit_test_iterater_cnt_set(uint32 count)
{
    if (!count) {
        pr_log_info("Invalid iteration count, use default.\n");
        iteration = DEFAULT_ITERATION_CNT;
    } else {
        iteration = count;
    }
}

static inline void
unit_test_layer_table_category_perform(const struct test_layer_table *category,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (unit_test_layer_table_match_p(category, tmp)) {
            fprintf(stdout, "\n  == Unit Test [ %s ] ==\n", category->name);
            unit_test_layer_table_implement_perform(category->junior, filter);
            fprintf(stdout, "  << Test Finished.\n");
        }
        category++;
    }
}

static inline void
unit_test_layer_table_category_list(const struct test_layer_table *category,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (unit_test_layer_table_match_p(category, tmp)) {
            fprintf(stdout, "\n  == Unit Test List [ %s ] ==\n", category->name);
            unit_test_layer_table_implement_list(category->junior, filter, category->name);
            fprintf(stdout, "  << Test Cases List Finished.\n");
        }
        category++;
    }
}

static inline void
unit_test_layer_table_implement_perform(const struct test_layer_table *implement,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (unit_test_layer_table_match_p(implement, tmp)) {
            unit_test_layer_table_interface_perform(implement->junior, filter);
        }
        implement++;
    }
}

static inline void
unit_test_layer_table_implement_list(const struct test_layer_table *implement,
    struct unit_test_filter *filter, char *category)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (unit_test_layer_table_match_p(implement, tmp)) {
            unit_test_layer_table_interface_list(implement->junior, filter, category, implement->name);
        }
        implement++;
    }
}


static inline void
unit_test_layer_table_interface_perform(const struct test_layer_table *interface,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->interface;

    while (interface->name) {
        if (unit_test_layer_table_match_p(interface, tmp)) {
            interface->func();
        }
        interface++;
    }
}

static inline void
unit_test_layer_table_interface_list(const struct test_layer_table *interface,
    struct unit_test_filter *filter, char *category, char *implement)
{
    char *tmp;

    assert(NULL != filter);
    assert(NULL != category);
    assert(NULL != implement);

    tmp = filter->interface;

    while (interface->name) {
        if (unit_test_layer_table_match_p(interface, tmp)) {
            fprintf(stdout, "    . [36m%s.%s.%s[0m\n", category, implement, interface->name);
        }
        interface++;
    }
}

static inline bool
unit_test_layer_table_match_p(const struct test_layer_table *category, char *name)
{
    if (!strncmp("*", name, 1)) {
        return true;
    } else if (!strncmp(category->name, name, strlen(category->name) + 1)) { /* compare the last \0 */
        return true;
    } else {
        return false;
    }
}

