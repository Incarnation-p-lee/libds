#include "types.h"

extern void
linked_list_unit_test(void);
extern void
stack_unit_test(void);
extern void
queue_unit_test(void);

extern void
memory_trace_print(void);

static void (*run_test[])(void) = {
#if 1
    &linked_list_unit_test,
    &stack_unit_test,
    &queue_unit_test,
#else
    &queue_unit_test,
#endif
};

sint32
main(sint32 argc, char **argv)
{
    register void (**iter)(void) = run_test;

    while (iter < run_test + sizeof(run_test) / sizeof(run_test[0])) {
        (*iter++)();
    }
    memory_trace_print();

    return 0;
}
