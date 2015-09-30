static inline bool
test_result_check_pointer_p(void *get, void *expect, bool *pass)
{
    bool tmp;

    assert(NULL != pass);

    tmp = (expect == get);

    if (!tmp) {
        fprintf(stdout, "[32mexpected[0m: %p\n", get);
        fprintf(stdout, "[31mcomputed[0m: %p\n", expect);
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
        fprintf(stdout, "[32mexpected[0m: %s\n", expect ? "true" : "false");
        fprintf(stdout, "[31mcomputed[0m: %s\n", get ? "true" : "false");
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
        fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        fprintf(stdout, "[31mcomputed[0m: %#x\n", get);
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
        fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        fprintf(stdout, "[31mlimited [0m: %#x\n", limit);
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
        fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        fprintf(stdout, "[31mlimited [0m: %#x\n", limit);
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
        fprintf(stdout, "[32mexpected[0m: %#x\n", expect);
        fprintf(stdout, "[31mcomputed[0m: %#x\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_uint64_p(uint64 expect, uint64 get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        fprintf(stdout, "[32mexpected[0m: %#lx\n", expect);
        fprintf(stdout, "[31mcomputed[0m: %#lx\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_sint64_p(sint64 expect, sint64 get, bool *pass)
{
    bool tmp;

    tmp = (expect == get);

    if (!tmp) {
        fprintf(stdout, "[32mexpected[0m: %#lx\n", expect);
        fprintf(stdout, "[31mcomputed[0m: %#lx\n", get);
    }

    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_float_p(float expect, float get, bool *pass)
{
    bool tmp;

    tmp = !(expect > get || expect < get);
    *pass = *pass && tmp;

    return tmp;
}

static inline bool
test_result_check_double_p(double expect, double get, bool *pass)
{
    bool tmp;

    tmp = !(expect > get || expect < get);
    *pass = *pass && tmp;

    return tmp;
}

