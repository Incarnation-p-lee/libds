#ifndef HAVE_TEST_RESULT_CHECK_H
#define HAVE_TEST_RESULT_CHECK_H

#ifdef DEBUG
    #define LOCATION_PRINT fprintf(stdout, "[33m                               .. @ %d: %s[0m\n", __LINE__, __FILE__)
#else
    #define LOCATION_PRINT
#endif

#define RESULT_CHECK_pointer(get, expect, pass)                \
    do {                                                       \
        if (!test_result_check_pointer_p(get, expect, pass)) { \
            LOCATION_PRINT;                                    \
        }                                                      \
    } while (false)

#define RESULT_CHECK_bool(get, expect, pass)                \
    do {                                                    \
        if (!test_result_check_bool_p(get, expect, pass)) { \
            LOCATION_PRINT;                                 \
        }                                                   \
    } while (false)

#define RESULT_CHECK_uint32(get, expect, pass)                \
    do {                                                      \
        if (!test_result_check_uint32_p(get, expect, pass)) { \
            LOCATION_PRINT;                                   \
        }                                                     \
    } while (false)

#define RESULT_CHECK_LESS_uint32(get, limit, pass)                \
    do {                                                          \
        if (!test_result_check_less_uint32_p(get, limit, pass)) { \
            LOCATION_PRINT;                                       \
        }                                                         \
    } while (false)

#define RESULT_CHECK_NOT_LESS_uint32(get, limit, pass)                \
    do {                                                              \
        if (!test_result_check_not_less_uint32_p(get, limit, pass)) { \
            LOCATION_PRINT;                                           \
        }                                                             \
    } while (false)

#define RESULT_CHECK_sint32(get, expect, pass)                \
    do {                                                      \
        if (!test_result_check_sint32_p(get, expect, pass)) { \
            LOCATION_PRINT;                                   \
        }                                                     \
    } while (false)

#define RESULT_CHECK_uint64(get, expect, pass)                \
    do {                                                      \
        if (!test_result_check_uint64_p(get, expect, pass)) { \
            LOCATION_PRINT;                                   \
        }                                                     \
    } while (false)

#define RESULT_CHECK_sint64(get, expect, pass)                \
    do {                                                      \
        if (!test_result_check_sint64_p(get, expect, pass)) { \
            LOCATION_PRINT;                                   \
        }                                                     \
    } while (false)

#define RESULT_CHECK_float(get, expect, pass)                \
    do {                                                     \
        if (!test_result_check_float_p(get, expect, pass)) { \
            LOCATION_PRINT;                                  \
        }                                                    \
    } while (false)

#define RESULT_CHECK_double(get, expect, pass)                \
    do {                                                      \
        if (!test_result_check_double_p(get, expect, pass)) { \
            LOCATION_PRINT;                                   \
        }                                                     \
    } while (false)

#endif
