static inline void
test_case_list(struct test_extra_info *info, char *content)
{
    struct test_case_filter *filter;

    dp_assert(NULL != content);

    filter = test_case_filter_obtain(content);

    dp_fprintf(stdout, "  >> TEST CASE LIST << \n");
    test_case_list_category(test_category, filter);
    test_case_filter_destroy(&filter);
}

static inline void
test_case_list_category(const struct test_layer_table *category,
    struct test_case_filter *filter)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (test_case_filter_match_p(category, tmp)) {
            test_case_list_implement(category->junior, filter, category->name);
        }
        category++;
    }
}

static inline void
test_case_list_implement(const struct test_layer_table *implement,
    struct test_case_filter *filter, char *category)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (test_case_filter_match_p(implement, tmp)) {
            test_case_list_interface(implement->junior, filter, category, implement->name);
        }
        implement++;
    }

    dp_fprintf(stdout, "\n");
}

static inline void
test_case_list_interface(const struct test_layer_table *interface,
    struct test_case_filter *filter, char *category, char *implement)
{
    char *tmp;

    dp_assert(NULL != filter);
    dp_assert(NULL != category);
    dp_assert(NULL != implement);

    tmp = filter->interface;

    while (interface->name) {
        if (test_case_filter_match_p(interface, tmp)) {
            dp_fprintf(stdout, "    . [36m%s.%s.%s[0m\n", category, implement, interface->name);
        }
        interface++;
    }

    dp_fprintf(stdout, "\n");
}

static inline bool
test_case_filter_match_p(const struct test_layer_table *category, char *name)
{
    if (!dp_strncmp("*", name, 1)) {
        return true;
    } else if (!dp_strncmp(category->name, name, strlen(category->name) + 1)) { /* compare the last \0 */
        return true;
    } else {
        return false;
    }
}

