static inline void
performance_test_reference_golden_prepare(const char *fname)
{
    FILE *golden;
    char line[PERORMANCE_ENTRY_MAX_SIZE];

    assert(NULL != fname);

    memset(line, 0, sizeof(line));
    golden = fopen(fname, "r");

    if (!golden) {
        pr_log_warn("Failed to open Test Reference File.\n");
        return;
    } else {
        while (fgets(line, PERORMANCE_ENTRY_MAX_SIZE, golden)) {
            performance_test_reference_update(line, performance_reference);
            memset(line, 0, sizeof(line));
        }
    }

    fclose(golden);
}

static inline void
performance_test_reference_update(char *raw, struct performance_test_reference *ref)
{
    struct performance_test_reference *iter;
    char *name;
    uint32 last;

    assert(NULL != raw);

    raw[strlen(raw) - 1] = '\0';
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

static inline struct performance_test_reference *
performance_test_reference_entry_find_by_name(char *name)
{
    struct performance_test_reference *iter;

    assert(NULL != name);

    iter = performance_reference;
    while (iter->name) {
        if (!strncmp(iter->name, name, strlen(iter->name) + 1)) {
            return iter;
        }
        iter++;
    }

    return NULL;
}

static inline double
performance_test_reference_variance_calculate(char *name, sint64 period)
{
    struct performance_test_reference *entry;

    assert(NULL != name);
    assert(0 != period);

    entry = performance_test_reference_entry_find_by_name(name);
    assert(NULL != entry);

    entry->now = period;
    /*
     * tmp code, should delete this after all performance data available.
     */
    if (0u == entry->ref) {
        entry->ref = period;
    }

    return (double)(entry->ref - period) / entry->ref;
}


static inline void
performance_test_reference_new_writeback(const char *fname)
{
    FILE *golden;
    struct performance_test_reference *iter;
    char line[PERORMANCE_ENTRY_MAX_SIZE];

    assert(NULL != fname);

    golden = fopen(fname, "w");

    if (!golden) {
        pr_log_warn("Failed to open Test New File.\n");
        return;
    } else {
        iter = performance_reference;
        while (iter->name) {
            memset(line, 0, sizeof(line));
            sprintf(line, "%016"U64_MDF_U"=%s\n", iter->now, iter->name);
            fwrite(line, strlen(line), 1, golden);
            iter++;
        }
    }

    fclose(golden);
}

