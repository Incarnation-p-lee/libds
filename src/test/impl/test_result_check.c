static inline bool
test_result_check_pointer_p(void *expect, void *get, bool *pass)
{
    bool tmp;

    assert(NULL != pass);

    tmp = (get == expect);

    if (!tmp) {
        fprintf(stdout, "[32mexpected[0m: %p\n", expect);
        fprintf(stdout, "[31mcomputed[0m: %p\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_bool_p(bool get, bool expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_uint32_p(uint32 get, uint32 expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_less_uint32_p(uint32 get, uint32 limit, bool *pass)
{
    bool tmp;

    tmp = (get < limit);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_not_less_uint32_p(uint32 get, uint32 limit, bool *pass)
{
    bool tmp;

    tmp = (get >= limit);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_sint32_p(sint32 get, sint32 expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_uint64_p(uint64 get, uint64 expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_sint64_p(sint64 get, sint64 expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_float_p(float get, float expect, bool *pass)
{
    bool tmp;

    tmp = !(get > expect || get < expect);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_double_p(double get, double expect, bool *pass)
{
    bool tmp;

    tmp = !(get > expect || get < expect);
    *pass = *pass && tmp;

    return tmp;
}

