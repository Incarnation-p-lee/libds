#include "types.h"
#include "externs.h"


sint32
main(sint32 argc, char **argv)
{
    register void (**iter)(void) = test_suite;

    while (iter < test_suite + sizeof(test_suite) / sizeof(test_suite[0])) {
        (*iter++)();
    }

    MEMORY_STAT;
    end_of_report_print();
    return 0;
}
