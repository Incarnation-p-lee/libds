#include <stdlib.h>
#include "defines.h"
#include "types.h"
#include "util.h"

int
main(int argc, char **argv)
{
    memory_maps_obtain();
    test_parameter_parser((uint32)argc, argv);
    test_execution_start();

    MEMORY_STAT;
    end_of_report_print();

    return 0;
}
