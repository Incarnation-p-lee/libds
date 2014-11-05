extern void
linked_list_unit_test(void);
extern int
libds_log_initial(void);
extern void
libds_log_close(void);
extern void
memory_trace_print(void);

static void (*run_test[])(void) = {
    &linked_list_unit_test,
};

int
main(int argc, char **argv)
{
    register void (**iter)(void) = run_test;

    libds_log_initial();
    while (iter < run_test + sizeof(run_test) / sizeof(run_test[0])) {
        (*iter++)();
    }
    libds_log_close();
    memory_trace_print();

    return 0;
}
