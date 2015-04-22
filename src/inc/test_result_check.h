#ifndef HAVE_TEST_RESULT_CHECK_H
#define HAVE_TEST_RESULT_CHECK_H

#ifdef DEBUG
    #define LOCATION_PRINT fprintf(stderr, " ... at %d: %s\n", __LINE__, __FILE__)
#else
    #define LOCATION_PRINT
#endif

#define RESULT_check_pointer_p(get, expect) \
    (test_result_check_pointer_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_bool_p(get, expect) \
    (test_result_check_bool_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_uint32_p(get, expect) \
    (test_result_check_uint32_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_sint32_p(get, expect) \
    (test_result_check_sint32_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_uint64_p(get, expect) \
    (test_result_check_uint64_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_sint64_p(get, expect) \
    (test_result_check_sint64_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_float_p(get, expect) \
    (test_result_check_float_p(get, expect) ? \
        true : (LOCATION_PRINT, false))
#define RESULT_check_double_p(get, expect) \
    (test_result_check_double_p(get, expect) ? \
        true : (LOCATION_PRINT, false))

#endif
