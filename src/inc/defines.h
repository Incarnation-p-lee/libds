#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H


#define true        1
#define false       0

#define SYM_2_STR(symbol)   (#symbol)
#define UNOFFSET_OF(ptr, type, mem) \
    (void *)((void *)ptr - (void *)(&((type *)0)->mem))

#ifdef DEBUG
    #define pr_log_info(msg)    libds_log_print(INFO, msg);
    #define pr_log_warn(msg)    libds_log_print(WARN, msg);
    #define pr_log_debug(msg)   libds_log_print(DBUG, msg);
#else
    #define pr_log_info(msg)
    #define pr_log_warn(msg)
    #define pr_log_debug(msg)
#endif

#ifdef DEBUG
    #define malloc_ds      malloc_wrap
    #define realloc_ds     realloc_wrap
    #define free_ds        free_wrap
#else
    #define malloc_ds      malloc
    #define realloc_ds     realloc
    #define free_ds        free
#endif

#define pr_log_err(msg)     \
    do {                             \
        libds_log_print(ERRR, msg); \
        exit(1);                     \
    } while (0);


#endif
