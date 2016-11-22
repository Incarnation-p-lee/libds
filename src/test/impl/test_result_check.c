static inline bool
test_result_check_pointer_p(void *expect, void *get, bool *pass)
{
    bool tmp;

    assert_exit(NULL != pass);

    tmp = (expect == get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %p\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %p\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_not_equal_pointer_p(void *expect, void *get, bool *pass)
{
    bool tmp;

    assert_exit(NULL != pass);

    tmp = (expect != get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %p\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %p\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_bool_p(bool expect, bool get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %s\n", expect ? "true" : "false");
        dp_fprintf(stdout, "[31mcomputed[0m: %s\n", get ? "true" : "false");
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_uint32_p(uint32 expect, uint32 get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %#x\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_less_uint32_p(uint32 expect, uint32 limit, bool *pass)
{
    bool tmp;

    tmp = (expect < limit);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        dp_fprintf(stdout, "[31mlimited [0m: %#x\n", limit);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_not_less_uint32_p(uint32 expect, uint32 limit, bool *pass)
{
    bool tmp;

    tmp = (expect >= limit);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        dp_fprintf(stdout, "[31mlimited [0m: %#x\n", limit);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_sint32_p(sint32 expect, sint32 get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %#x\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

// Not enabled yet.
// static inline bool
// test_result_check_uint64_p(uint64 expect, uint64 get, bool *pass)
// {
//     bool tmp;
// 
//     tmp = (expect == get);
// 
//     if (!tmp) {
//         dp_fprintf(stdout, "[32mexpected[0m: %#"U64_MDF_X"\n", expect);
//         dp_fprintf(stdout, "[31mcomputed[0m: %#"U64_MDF_X"\n", get);
//     }
// 
//     *pass = *pass && tmp;
// 
//     return tmp;
// }

static inline bool
test_result_check_sint64_p(sint64 expect, sint64 get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        dp_fprintf(stdout, "[32mexpected[0m: %#"S64_MDF_X"\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %#"S64_MDF_X"\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_not_less_sint64_p(sint64 expect, sint64 get, bool *pass)
{
    bool tmp;

    tmp = (expect >= get);

    if (!tmp) {
        dp_fprintf(stdout, "[expect >= computed]\n");
        dp_fprintf(stdout, "[32mexpected[0m: %#"S64_MDF_X"\n", expect);
        dp_fprintf(stdout, "[31mcomputed[0m: %#"S64_MDF_X"\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

// Not enabled yet.
// static inline bool
// test_result_check_less_sint64_p(sint64 expect, sint64 get, bool *pass)
// {
//     bool tmp;
// 
//     tmp = (expect < get);
// 
//     if (!tmp) {
//         dp_fprintf(stdout, "[expect < computed]\n");
//         dp_fprintf(stdout, "[32mexpected[0m: %"S64_MDF_D"\n", expect);
//         dp_fprintf(stdout, "[31mcomputed[0m: %"S64_MDF_D"\n", get);
//     }
// 
//     *pass = *pass && tmp;
// 
//     return tmp;
// }

// Not enabled yet.
// static inline bool
// test_result_check_more_sint64_p(sint64 expect, sint64 get, bool *pass)
// {
//     bool tmp;
// 
//     tmp = (expect > get);
// 
//     if (!tmp) {
//         dp_fprintf(stdout, "[expect > computed]\n");
//         dp_fprintf(stdout, "[32mexpected[0m: %"S64_MDF_D"\n", expect);
//         dp_fprintf(stdout, "[31mcomputed[0m: %"S64_MDF_D"\n", get);
//     }
// 
//     *pass = *pass && tmp;
// 
//     return tmp;
// }

// Not enabled yet
// static inline bool
// test_result_check_float_p(float expect, float get, bool *pass)
// {
//     bool tmp;
// 
//     tmp = !(expect > get || expect < get);
//     *pass = *pass && tmp;
// 
//     return tmp;
// }

// Not enabled yet
// static inline bool
// test_result_check_double_p(double expect, double get, bool *pass)
// {
//     bool tmp;
// 
//     tmp = !(expect > get || expect < get);
//     *pass = *pass && tmp;
// 
//     return tmp;
// }

static inline bool
test_result_check_native_wide_p(native_wide_t expect, native_wide_t get, bool *pass)
{
    bool tmp;

    tmp = expect == get;
    *pass = *pass && tmp;

    return tmp;
}

