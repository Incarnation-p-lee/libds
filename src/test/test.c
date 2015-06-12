#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include "types.h"
#include "defines.h"
#include "util.h"
#include "data_structure_types.h"
#include "data_structure_defines.h"

#include "test.h"
#include "test_result_check.h"
#include "test_performance.h"
#include "test_performance_set.h"
#include "ds.h"

#include "impl/test_utilize.c"
#include "impl/test_wrapper.c"
#include "impl/test_result_check.c"
#include "impl/test_time_stamp.c"
#include "impl/test_performance.c"
#include "unit_test/unit_test.c"

void
test_perform(struct option_set *opts)
{
    if (!opts) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (opts->list) {
        unit_test_list(opts->content);
    } else {
        unit_test_perform(opts->content);
    }

    return;
}
