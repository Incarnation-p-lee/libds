#include <stdlib.h>
#include "defines.h"
#include "types.h"
#include "util.h"

int
main(int argc, char **argv)
{
    LIBDS_LOGFILE_CREATE;

    memory_maps_obtain();
    test_parameter_parser((uint32)argc, argv);
    test_execution_start();
    memory_cache_cleanup();

    MEMORY_STAT;
    LIBDS_LOGFILE_CLOSE;

    end_of_report_print();
    return 0;
}

