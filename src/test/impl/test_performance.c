static inline void
test_reference_prepare(const char *fname, struct test_performance *cate)
{
    char line[PERORMANCE_ENTRY_MAX_SIZE];

    assert(NULL != fname);
    assert(NULL != cate);

    memset(line, 0, sizeof(line));
    test_performance_file = fopen(fname, "r");

    if (!test_performance_file) {
        pr_log_warn("Failed to open Test Reference File.\n");
    } else {
        while (fgets(line, PERORMANCE_ENTRY_MAX_SIZE, test_performance_file)) {
            test_reference_update(line, cate);
            memset(line, 0, sizeof(line));
        }
    }

    if (test_performance_file) {
        fclose(test_performance_file);
        test_performance_file = NULL;
    }

    return;
}

static inline void
test_reference_update(char *raw, struct test_performance *ref)
{
    struct test_performance *iter;
    char *name;
    uint32 last;

    assert(NULL != raw);

    raw[strlen(raw) - 1] = '\0'; /* Rewrite the last from \n to \0 */
    name = strchr(raw, (int)'=');
    if (!name) {
        pr_log_warn("Unknown format of Test Reference File.\n");
    } else {
        *name++ = '\0';
        last = (uint32)atoll(raw);

        iter = ref;
        while (iter->name) {
            if (!strncmp(iter->name, name, strlen(iter->name) + 1)) {
                iter->ref = last;
                break;
            }
            iter++;
        }
    }

    return;
}

static inline struct test_performance *
test_reference_entry_find(char *name)
{
    struct test_performance *iter;

    assert(NULL != name);

    iter = unit_test_performance;
    while (iter->name) {
        if (!strncmp(iter->name, name, strlen(iter->name) + 1)) {
            return iter;
        }
        iter++;
    }

    return NULL;
}

static inline void
test_performance_result_writeback(const char *fname, struct test_performance *cate)
{
    struct test_performance *iter;
    char line[PERORMANCE_ENTRY_MAX_SIZE];

    assert(NULL != fname);
    assert(NULL != cate);

    test_performance_file = fopen(fname, "w");

    if (!test_performance_file) {
        pr_log_warn("Failed to open Test New File.\n");
    } else {
        iter = unit_test_performance;
        while (iter->name) {
            memset(line, 0, sizeof(line));
            sprintf(line, "%016ld=%s\n", iter->now, iter->name);
            fwrite(line, strlen(line), 1, test_performance_file);
            iter++;
        }
    }

    if (test_performance_file) {
        fclose(test_performance_file);
        test_performance_file = NULL;
    }

    return;
}
