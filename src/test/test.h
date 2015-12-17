#ifndef HAVE_TEST_H
#define HAVE_TEST_H

#define FILTER_LEN                     32
#define UNIT_TEST_RESULT(symbol, pass) unit_test_result_print( \
    SYM_2_STR(symbol), pass)

extern bool complain_no_memory_p(void *ptr);
extern void * memory_cache_allocate(uint32 size);
extern void memory_cache_free(void *addr);

struct test_case_filter {
    char category[FILTER_LEN];
    char implement[FILTER_LEN];
    char interface[FILTER_LEN];
};

struct test_layer_entity {
    void (*unit)(void);
    void (*performance)(uint32);
};

struct test_layer_table {
    char                     *name;
    const void               *junior;
    struct test_layer_entity entity;
};

enum tese_entry_name {
    TEST_CASE_LIST = 0,
    UNIT_TEST = 1,
    PERFORMANCE_TEST = 2,
};

struct test_extra_info {
    uint32 count;
};

struct test_entry_list {
    const char             *name;
    bool                   enabled;
    void                   *entrance;
    struct test_extra_info *info;
};

struct test_suite {
    struct test_entry_list *list;
    char                   content[CONTENT_LEN];
};

struct test_extra_info performance_attr = {
    DEFAULT_ITERATION_CNT,
};

static inline void test_case_list(struct test_extra_info *info, char *content);
static inline void unit_test_execution_start(struct test_extra_info *entry, char *content);
static inline void performance_test_execution_start(struct test_extra_info *entry, char *content);

static struct test_entry_list entry_list[] = {
    {"test_case_list",   false, &test_case_list,                   NULL},
    {"unit_test",        false, &unit_test_execution_start,        NULL},
    {"performance_test", false, &performance_test_execution_start, &performance_attr},
    {NULL,               false, NULL,                              NULL},
};

static struct test_suite suite = {
    entry_list,
};

static const struct test_layer_table test_category[];

static uint64 malloc_cnt = 0;
static uint64 free_cnt = 0;
static uint64 realloc_cnt = 0;
static uint32 reference = 0;

#endif

