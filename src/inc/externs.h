#ifndef HAVE_EXTERNS_H
#define HAVE_EXTERNS_H

/* Unit Test List */
extern void linked_list_unit_test(void);
extern void stack_unit_test(void);
extern void queue_unit_test(void);
extern void tree_unit_test(void);
/* End of Unit Test List */

extern void end_of_report_print(void);
extern void memory_maps_obtain(void);

#ifdef DEBUG
    extern void memory_trace_print(void);
    #define MEMORY_STAT memory_trace_print()
#else
    #define MEMORY_STAT
#endif

static void (*test_suite[])(void) = {
#if 1
    &linked_list_unit_test,
    &stack_unit_test,
    &queue_unit_test,
    &tree_unit_test,
#else
    &tree_unit_test,
#endif
};

#endif
