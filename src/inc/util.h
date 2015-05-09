#ifndef HAVE_UTIL_H
#define HAVE_UTIL_H

#define NAME_LEN      128
#define MAP_ENTRY_MAX 128

#define M_UKNW      0x1u << 0
#define M_READ      0x1u << 1
#define M_WRITE     0x1u << 2
#define M_EXECUTE   0x1u << 3
#define M_SHARED    0x1u << 4
#define M_PRIVATE   0x1u << 5

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
    #define MEMORY_STAT memory_trace_print()
#else
    #define MEMORY_STAT
#endif

/* GLOBAL EXPORTED INTERFACE */
extern void libds_log_print(enum log_level lvl, const char *msg);
extern uint32 prime_numeral_next(uint32 prime);
extern struct memory_maps * memory_maps_entry_find(char *name);
extern void unit_test_perform(char *arg);
extern void end_of_report_print(void);
extern void memory_maps_obtain(void);

/* END OF GLOBAL EXPORTED INTERFACE */


#endif
