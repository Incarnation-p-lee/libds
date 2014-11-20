extern void
linked_list_unit_test(void);
extern void
stack_unit_test(void);
extern void
memory_trace_print(void);

static void (*run_test[])(void) = {
    &linked_list_unit_test,
    &stack_unit_test,
};

int
main(int argc, char **argv)
{
    register void (**iter)(void) = run_test;

    while (iter < run_test + sizeof(run_test) / sizeof(run_test[0])) {
        (*iter++)();
    }
    memory_trace_print();

    return 0;
}
