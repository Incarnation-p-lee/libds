#include "types.h"
#include "depends.h"
#include "defines.h"

extern void memory_maps_obtain(void);
extern void test_parameter_parser(uint32 argc, char **argv);
extern void test_execution_start(void);
extern void memory_cache_cleanup(void);
extern void libds_log_file_create(void);
extern void libds_log_file_close(void);
extern void memory_trace_print(void);

int
main(int argc, char **argv)
{
    libds_log_file_create();
    memory_maps_obtain();

    test_parameter_parser((uint32)argc, argv);
    test_execution_start();

    memory_cache_cleanup();
    memory_trace_print();
    libds_log_file_close();

    return 0;
}

