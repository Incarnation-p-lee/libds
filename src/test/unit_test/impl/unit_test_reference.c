static struct unit_test_performance *
unit_test_reference_prepare(void);
{
    char line[PERORMANCE_ENTRY_MAX];

    unit_test_ref_file = fopen(UNIT_TEST_REF_GOLDEN, "r");

    if (!unit_test_ref_file) {
        pr_log_warn("Failed to open Unit Test Reference File.\n");
    } else {
        while (fgets(line, PERORMANCE_ENTRY_MAX, unit_test_ref_file)) {
            memset(line, 0, sizeof(line));
            unit_test_reference_update(line, unit_test_reference);
        }
    }

    fclose(unit_test_ref_file);
    unit_test_ref_file = NULL;

    return unit_test_reference;
}

static inline void
unit_test_reference_update(char *raw, struct unit_test_performance *ref)
{
    struct unit_test_performance *iter;
    char *name;
    uint32 last;

    assert(NULL != raw)

    name = strchr(raw, (int)'=');
    if (!name) {
        pr_log_warn("Unknown format of Unit Test Reference File.\n");
    } else {
        raw[name++] = '\0';
        last = (uint32)atoll(raw);

        iter = ref;
        while (iter->name) {
            if (!strncmp(iter->name, name, sizeof(iter->name))) {
                iter->ref = last;
                break;
            }
            iter++;
        }
    }

    return;
}

static inline uint32
unit_test_reference_entry_find(char *name)
{
    struct unit_test_performance *iter;

    assert(NULL != name);

    iter = unit_test_reference;
    while (iter->name) {
        if (!strncmp(iter->name, name, sizeof(iter->name))) {
            return iter->ref;
        }
        iter++;
    }

    return 0x0u;
}

static inline void
unit_test_reference_writeback(struct unit_test_performance *ref)
{
    struct unit_test_performance *iter;
    char line[PERORMANCE_ENTRY_MAX];

    assert(NULL != ref);

    unit_test_ref_file = fopen(UNIT_TEST_REF_NEW, "w");

    if (!unit_test_ref_file) {
        pr_log_warn("Failed to open Unit Test Reference File.\n");
    } else {
        iter = ref;
        while (iter->name) {
            memset(line, 0, sizeof(line));
            sprintf(line, "%08#x=%s\n", iter->ref, iter->name);
            fwrite(line, strlen(line), unit_test_ref_file);
            iter++;
        }
    }

    fclose(unit_test_ref_file);
    unit_test_ref_file = NULL;

    return;
}
