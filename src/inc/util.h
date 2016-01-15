#ifndef HAVE_UTIL_H
#define HAVE_UTIL_H

struct memory_maps {
    char        name[NAME_LEN];
    uint32      authority;
    union {
        void    *begin;
        NUMERAL b_val;
    };
    union {
        void    *end;
        NUMERAL e_val;
    };
};

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
    extern void memory_trace_print(void);
    extern void libds_log_file_create(void);
    extern void libds_log_file_close(void);
#endif

/* GLOBAL EXPORTED INTERFACE */
extern void libds_log_print(enum log_level lvl, const char *msg);
extern uint32 prime_numeral_next(uint32 prime);
extern struct memory_maps * memory_maps_entry_find(char *name);
extern void end_of_report_print(void);
extern void memory_maps_obtain(void);
extern void test_parameter_parser(uint32 argc, char **argv);
extern void test_execution_start(void);
extern void memory_cache_cleanup(void);


/* END OF GLOBAL EXPORTED INTERFACE */

#endif
