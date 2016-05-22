#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H

#define true                       1
#define false                      0

#define SYM_2_STR(symbol)          (#symbol)
#define array_sizeof(a)            (sizeof(a) / sizeof(a[0]))

/*
 * abs without if-else
 *     y = x >> 31, x eq 0xffffffff or 0x0
 *     z = y + x, x eq x - 1 or unchanged
 *     abs = z ^ x, x eq -x or unchanged.
 */
#define abs_in_width(x, n)         ((((x) >> ((n) - 1)) + (x)) ^ ((x) >> ((n) - 1)))
#define abs_sint32(x)              abs_in_width((sint32)x, 32)
#define abs_sint64(x)              abs_in_width((sint64)x, 64)

#define NAME_LEN                   256
#define CONTENT_LEN                NAME_LEN

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);

    #define malloc_ds              malloc_wrap
    #define realloc_ds             realloc_wrap
    #define free_ds                free_wrap
    #define pr_log_info(msg)       libds_log_print(INFO, msg)
    #define pr_log_warn(msg)       libds_log_print(WARN, msg)
    #define pr_log_debug(msg)      libds_log_print(DBUG, msg)
    #define assert_not_reached()   dp_assert(false)
    #define LIBDS_LOGFILE_CREATE   libds_log_file_create()
    #define LIBDS_LOGFILE_CLOSE    libds_log_file_close()
    #define MEMORY_STAT            memory_trace_print()
#else
    #define malloc_ds              dp_malloc
    #define realloc_ds             dp_realloc
    #define free_ds                dp_free
    #define pr_log_info(msg)
    #define pr_log_warn(msg)
    #define pr_log_debug(msg)
    #define assert_not_reached()  ((*(uint32 *)0) = 0xdeadu)
    #define LIBDS_LOGFILE_CREATE
    #define LIBDS_LOGFILE_CLOSE
    #define MEMORY_STAT
#endif

#define CONTAINER_OF(ptr, type, member) \
    (dp_assert(ptr), (type *)((void *)(ptr) - (void *)(&((type *)0)->member)))

#define pr_log_err(msg)                                         \
    do {                                                        \
        dp_printf("ERRR: %s\n  at function %s:%d in file %s\n", \
            msg, __FUNCTION__, __LINE__, __FILE__);             \
        dp_exit(1);                                             \
    } while (0);


#define MAX_U32(x, y)    ((uint32)(x) > (uint32)(y) ? (uint32)(x) : (uint32)(y))
#define MIN_U32(x, y)    ((uint32)(x) < (uint32)(y) ? (uint32)(x) : (uint32)(y))
#define MAX_S32(x, y)    ((sint32)(x) > (sint32)(y) ? (sint32)(x) : (sint32)(y))
#define MIN_S32(x, y)    ((sint32)(x) < (sint32)(y) ? (sint32)(x) : (sint32)(y))

#define UINT32_IDX_BIT(op, idx) ((op >> (idx)) & 1u)
#define SINT64_ABS(x)           (((sint64)(x) > 0) ? (x) : -(x))

#if defined X86_64
    #define PTR_TO_UNSIGNED(ptr) (uint64)(ptr)
    #define UNSIGNED_TO_PTR(usd) (void *)(usd)
    #define U64_MDF_X            "lx"
    #define U64_MDF_U            "lu"
    #define S64_MDF_D            "ld"
    #define S64_MDF_X            "lx"
#endif

#if defined X86_32
    #define PTR_TO_UNSIGNED(ptr) (uint32)(ptr)
    #define UNSIGNED_TO_PTR(usd) (void *)((uint32)usd)
    #define U64_MDF_X            "llx"
    #define U64_MDF_U            "llu"
    #define S64_MDF_D            "lld"
    #define S64_MDF_X            "llx"
#endif

#endif

