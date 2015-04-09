#include "types.h"
#include "externs.h"

int
main(int argc, char **argv)
{
    unit_test_perform(argv[1]);

    MEMORY_STAT;
    end_of_report_print();
    return 0;
}
