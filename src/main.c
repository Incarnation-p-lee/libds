#include <stdlib.h>
#include "types.h"
#include "util.h"

int
main(int argc, char **argv)
{
    memory_maps_obtain();
    unit_test_perform(argv[1]);

    MEMORY_STAT;
    end_of_report_print();
    return 0;
}
