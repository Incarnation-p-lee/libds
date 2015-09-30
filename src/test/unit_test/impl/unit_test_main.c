static inline void
unit_test_execution_start(struct test_extra_info *entry, char *content)
{
    struct test_case_filter *filter;

    assert(NULL != content);

    filter = test_case_filter_obtain(content);

    fprintf(stdout, "\n  >> UNIT LIST << \n");
    unit_test_execution_category(test_category, filter);

    test_case_filter_destroy(&filter);
}

static inline void
unit_test_execution_category(const struct test_layer_table *category,
    struct test_case_filter *filter)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (test_case_filter_match_p(category, tmp)) {
            unit_test_execution_implement(category->junior, filter);
        }
        category++;
    }
}

static inline void
unit_test_execution_implement(const struct test_layer_table *implement,
    struct test_case_filter *filter)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (test_case_filter_match_p(implement, tmp)) {
            unit_test_execution_interface(implement->junior, filter);
        }
        implement++;
    }

    fprintf(stdout, "\n");
}

static inline void
unit_test_execution_interface(const struct test_layer_table *interface,
    struct test_case_filter *filter)
{
    char *tmp;

    tmp = filter->interface;

    while (interface->name) {
        if (test_case_filter_match_p(interface, tmp)) {
            interface->entity.unit();
        }
        interface++;
    }

    fprintf(stdout, "\n");
}

static inline void
unit_test_result_print(char *name, bool passed)
{
    if (!name) {
        pr_log_warn("Unknow Test Function Name, nothing will be done.\n");
        return;
    }

    if (passed) {
        fprintf(stdout, "    . [32mPass[0m .. %s\n", name);
    } else {
        fprintf(stdout, "    . [31mFail[0m .. %s\n", name);
    }
}

