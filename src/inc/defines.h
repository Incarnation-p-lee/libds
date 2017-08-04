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

#define assert_not_reached(msg)    do {                                                             \
                                       complain_assert_exit(msg, __FILE__, __FUNCTION__, __LINE__); \
                                   } while (false)

#define assert_caution(exp)        do {                                                                     \
                                       if (!(exp)) {                                                        \
                                           complain_assert_caution(#exp, __FILE__, __FUNCTION__, __LINE__); \
                                       }                                                                    \
                                   } while (false)

#if defined DEBUG
    #define malloc_ds              malloc_wrap
    #define realloc_ds             realloc_wrap
    #define free_ds                free_wrap
    #define pr_log_info(msg)       libds_log_print(INFO, msg)
    #define pr_log_warn(msg)       libds_log_print(WARN, msg)
    #define pr_log_debug(msg)      libds_log_print(DBUG, msg)
    #define assert_exit(exp)       do {                                                                  \
                                       if (!(exp)) {                                                     \
                                           complain_assert_exit(#exp, __FILE__, __FUNCTION__, __LINE__); \
                                       }                                                                 \
                                   } while (false)
    #define NULL_PTR_P(ptr)        complain_null_pointer_p(ptr)
    #define NON_NULL_PTR_P(ptr)    (!complain_null_pointer_p(ptr))
    #define ALWAYS_INLINE
    #define inline
#else
    #define malloc_ds              dp_malloc
    #define realloc_ds             dp_realloc
    #define free_ds                dp_free
    #define pr_log_info(msg)
    #define pr_log_warn(msg)
    #define pr_log_debug(msg)
    #define assert_exit(exp)
    #define NULL_PTR_P(ptr)        (ptr == NULL ? true : false)
    #define NON_NULL_PTR_P(ptr)    (ptr != NULL ? true : false)
    #define ALWAYS_INLINE          __attribute__((always_inline))
    #define inline                 inline
#endif

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((void *)(ptr) - (void *)(&((type *)0)->member)))

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
#define TO_PTR(p)               ((void *)(ptr_t)(p))

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

#if defined X86_64
    #define SWAP(a, b)        \
        asm volatile (        \
            "xchg %0, %1\n\t" \
            :"+r"(a), "+r"(b) \
            :                 \
        )

#endif

#endif

