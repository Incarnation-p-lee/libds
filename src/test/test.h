#ifndef HAVE_TEST_H
#define HAVE_TEST_H

#define FILTER_LEN             32
#define DEFAULT_ITERATION_CNT  1000000u
#define MAP_ENTRY_MAX          128

#define M_UKNW                 (0x1u << 0)
#define M_READ                 (0x1u << 1)
#define M_WRITE                (0x1u << 2)
#define M_EXECUTE              (0x1u << 3)
#define M_SHARED               (0x1u << 4)
#define M_PRIVATE              (0x1u << 5)


#define RESULT_CHECK_doubly_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
        RESULT_CHECK_pointer((aim)->previous, (ex)->previous, (pass)); \
    } while (false)

#define RESULT_CHECK_single_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
    } while (false)

#define UNIT_TEST_RESULT(symbol, pass) unit_test_result_print( \
    SYM_2_STR(symbol), pass)

#define UNIT_TEST_BEGIN(symbol) unit_test_begin_print(SYM_2_STR(symbol))

struct memory_maps {
    char        name[NAME_LEN];
    uint32      authority;
    union {
        void    *begin;
        NUMERAL b_val;
    };
    union {
        void    *end;
        NUMERAL e_val;
    };
};

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

struct test_sort_data {
    uint32 val;
    char   *n;
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

/*
 * section info of binary
 */
static struct memory_maps mmaps[MAP_ENTRY_MAX] = {
    {},
};

static uint32 reference = 0;

#endif

