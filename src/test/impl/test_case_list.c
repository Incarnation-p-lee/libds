static inline void
test_case_list(struct test_extra_info *info, char *content)
{
    struct test_case_filter *filter;

    assert(NULL != content);

    filter = test_case_filter_obtain(content);
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
}

static inline void
test_case_list_interface(const struct test_layer_table *interface,
    struct test_case_filter *filter, char *category, char *implement)
{
    char *tmp;

    assert(NULL != filter);
    assert(NULL != category);
    assert(NULL != implement);

    tmp = filter->interface;

    while (interface->name) {
        if (test_case_filter_match_p(interface, tmp)) {
            fprintf(stdout, "    . [36m%s.%s.%s[0m\n", category, implement, interface->name);
        }
        interface++;
    }
}

static inline bool
test_case_filter_match_p(const struct test_layer_table *category, char *name)
{
    if (!strncmp("*", name, 1)) {
        return true;
    } else if (!strncmp(category->name, name, strlen(category->name) + 1)) { /* compare the last \0 */
        return true;
    } else {
        return false;
    }
}

