extern void
linked_list_unit_test(void);

static void (*run_test[])(void) = {
    &linked_list_unit_test,
};

int
main(char **argv, int argc)
{
    register void (**iter)(void) = run_test;

    while (iter < run_test + sizeof(run_test) / sizeof(run_test[0])) {
        (*iter++)();
    }

    return 0;
}
