#include <stdlib.h>
#include "defines.h"
#include "types.h"
#include "util.h"

int
main(int argc, char **argv)
{
    struct option_set *opts;

    memory_maps_obtain();
    opts = option_process((uint32)argc, argv);
    test_perform(opts);

    MEMORY_STAT;
    end_of_report_print();

    return 0;
}
