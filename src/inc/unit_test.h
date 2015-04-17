#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

#define FILTER_LEN 32

struct unit_test_filter {
    char category[FILTER_LEN];
    char implement[FILTER_LEN];
    char interface[FILTER_LEN];
};

void unit_test_perform(char *arg);

static inline void unit_test_layer_table_category(const struct test_layer_table *category, struct unit_test_filter *filter);
static inline void unit_test_layer_table_implement(const struct test_layer_table *implement, struct unit_test_filter *filter);
static inline void unit_test_layer_table_interface(const struct test_layer_table *interface, struct unit_test_filter *filter);
static inline bool unit_test_layer_table_match_p(const struct test_layer_table *category, char *name);
static inline void unit_test_filter_obtain_internal(char *dest, char *arg, uint32 len);
static inline struct unit_test_filter * unit_test_filter_initial(void);

static struct unit_test_filter * unit_test_filter_obtain(char *arg);
static void unit_test_filter_parser(struct unit_test_filter *filter, char *arg);
static void unit_test_filter_destroy(struct unit_test_filter **filter);

#endif
