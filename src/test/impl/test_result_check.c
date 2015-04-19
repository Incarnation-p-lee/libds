static inline bool
test_result_check_pointer_p(void *get, void *expect, bool *pass)
{
    bool tmp;

    tmp = (get == expect);
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

