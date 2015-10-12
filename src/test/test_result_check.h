#ifndef HAVE_TEST_RESULT_CHECK_H
#define HAVE_TEST_RESULT_CHECK_H

#ifdef DEBUG
    #define LOCATION_PRINT fprintf(stdout, "[33m                               .. @ %d: %s[0m\n", __LINE__, __FILE__)
#else
    #define LOCATION_PRINT
#endif

#define RESULT_CHECK_pointer(expect, get, pass)                   \
    do {                                                          \
        if (!test_result_check_pointer_p(expect, get, pass)) {    \
            LOCATION_PRINT;                                       \
            assert(false);                                        \
        }                                                         \
    } while (false)

#define RESULT_CHECK_bool(expect, get, pass)                \
    do {                                                    \
        if (!test_result_check_bool_p(expect, get, pass)) { \
            LOCATION_PRINT;                                 \
            assert(false);                                  \
        }                                                   \
    } while (false)

#define RESULT_CHECK_uint32(expect, get, pass)                \
    do {                                                      \
        if (!test_result_check_uint32_p(expect, get, pass)) { \
            LOCATION_PRINT;                                   \
            assert(false);                                    \
        }                                                     \
    } while (false)

#define RESULT_CHECK_LESS_uint32(get, limit, pass)                \
    do {                                                          \
        if (!test_result_check_less_uint32_p(get, limit, pass)) { \
            LOCATION_PRINT;                                       \
            assert(false);                                        \
        }                                                         \
    } while (false)

#define RESULT_CHECK_NOT_LESS_uint32(get, limit, pass)                \
    do {                                                              \
        if (!test_result_check_not_less_uint32_p(get, limit, pass)) { \
            LOCATION_PRINT;                                           \
            assert(false);                                            \
        }                                                             \
    } while (false)

#define RESULT_CHECK_sint32(expect, get, pass)                \
    do {                                                      \
        if (!test_result_check_sint32_p(expect, get, pass)) { \
            LOCATION_PRINT;                                   \
            assert(false);                                    \
        }                                                     \
    } while (false)

#define RESULT_CHECK_uint64(expect, get, pass)                \
    do {                                                      \
        if (!test_result_check_uint64_p(expect, get, pass)) { \
            LOCATION_PRINT;                                   \
            assert(false);                                    \
        }                                                     \
    } while (false)

#define RESULT_CHECK_LESS_sint64(expect, get, pass)                \
    do {                                                           \
        if (!test_result_check_less_sint64_p(expect, get, pass)) { \
            LOCATION_PRINT;                                        \
            assert(false);                                         \
        }                                                          \
    } while (false)

#define RESULT_CHECK_MORE_sint64(expect, get, pass)                \
    do {                                                           \
        if (!test_result_check_more_sint64_p(expect, get, pass)) { \
            LOCATION_PRINT;                                        \
            assert(false);                                         \
        }                                                          \
    } while (false)

#define RESULT_CHECK_sint64(expect, get, pass)                \
    do {                                                      \
        if (!test_result_check_sint64_p(expect, get, pass)) { \
            LOCATION_PRINT;                                   \
            assert(false);                                    \
        }                                                     \
    } while (false)

#define RESULT_CHECK_float(expect, get, pass)                \
    do {                                                     \
        if (!test_result_check_float_p(expect, get, pass)) { \
            LOCATION_PRINT;                                  \
            assert(false);                                   \
        }                                                    \
    } while (false)

#define RESULT_CHECK_double(expect, get, pass)                \
    do {                                                      \
        if (!test_result_check_double_p(expect, get, pass)) { \
            LOCATION_PRINT;                                   \
            assert(false);                                    \
        }                                                     \
    } while (false)

#endif
