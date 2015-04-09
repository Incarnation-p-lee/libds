#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "defines.h"
#include "ds.h"
#include "test_layer.h"
#include "test.h"

#include "test_linked_list.c"
#include "test_stack.c"
#include "test_queue.c"
#include "test_tree.c"

#include "impl/utilize.c"
#include "impl/wrapper.c"
#include "impl/test_layer.c"
#include "impl/test_filter.c"

void
unit_test_perform(char *arg)
{
    struct unit_test_filter *filter;

    filter = unit_test_filter_obtain(arg);
    unit_test_layer_table_category(unit_test_category, filter);
    unit_test_filter_destroy(&filter);

    return;
}

static inline void
unit_test_layer_table_category(const struct test_layer_table *category,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->category;

    while (category->name) {
        if (unit_test_layer_table_match_p(category, tmp)) {
            fprintf(stdout, "  == Unit Test >> %s << ==\n", category->name);
            unit_test_layer_table_implement(category->junior, filter);
            fprintf(stdout, "  << Test Finished.\n\n");
        }
        category++;
    }

    return;
}

static inline void
unit_test_layer_table_implement(const struct test_layer_table *implement,
    struct unit_test_filter *filter)
{
    char *tmp;

    tmp = filter->implement;

    while (implement->name) {
        if (unit_test_layer_table_match_p(implement, tmp)) {
            unit_test_layer_table_interface(implement->junior, filter);
        }
        implement++;
    }

    return;
}

static inline void
unit_test_layer_table_interface(const struct test_layer_table *interface,
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

    return;
}

static inline bool
unit_test_layer_table_match_p(const struct test_layer_table *category, char *name)
{
    if (!strncmp("*", name, 1)) {
        return true;
    } else if (!strncmp(category->name, name, strlen(category->name))) {
        return true;
    } else {
        return false;
    }
}

