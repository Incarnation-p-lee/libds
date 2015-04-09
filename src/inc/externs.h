#ifndef HAVE_EXTERNS_H
#define HAVE_EXTERNS_H

extern void unit_test_perform(char *arg);
extern void end_of_report_print(void);
extern void memory_maps_obtain(void);

#ifdef DEBUG
    extern void memory_trace_print(void);
    #define MEMORY_STAT memory_trace_print()
#else
    #define MEMORY_STAT
#endif

#endif
