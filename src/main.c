#include "types.h"
#include "externs.h"


int
main(int argc, char **argv)
{
    register void (**iter)(void) = test_suite;

    while (iter < test_suite + sizeof(test_suite) / sizeof(test_suite[0])) {
        (*iter++)();
    }

    MEMORY_STAT;
    end_of_report_print();
    return 0;
}
