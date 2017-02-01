static inline void
utest_disjoint_set_create(void)
{
    bool pass;
    uint32 size;
    s_disjoint_set_t *disjoint_set;

    UNIT_TEST_BEGIN(disjoint_set_create);

    pass = true;
    size = 0x1234;

    disjoint_set = disjoint_set_create(size);

    RESULT_CHECK_NOT_EQUAL_pointer(NULL, disjoint_set->set, &pass);
    RESULT_CHECK_uint32(size, disjoint_set_size(disjoint_set), &pass);

    disjoint_set_destroy(&disjoint_set);

    UNIT_TEST_RESULT(disjoint_set_create, pass);
}

static inline void
utest_disjoint_set_destroy(void)
{
    bool pass;
    uint32 size;
    s_disjoint_set_t *disjoint_set;

    UNIT_TEST_BEGIN(disjoint_set_destroy);

    pass = true;
    size = 0x1234;

    disjoint_set = disjoint_set_create(size);
    RESULT_CHECK_NOT_EQUAL_pointer(NULL, disjoint_set, &pass);

    disjoint_set_destroy(&disjoint_set);
    RESULT_CHECK_pointer(NULL, disjoint_set, &pass);

    UNIT_TEST_RESULT(disjoint_set_destroy, pass);
}

static inline void
utest_disjoint_set_find(void)
{
    bool pass;
    uint32 size;
    uint32 value;
    s_disjoint_set_t *disjoint_set;

    UNIT_TEST_BEGIN(disjoint_set_find);

    pass = true;
    size = 0x1234;

    disjoint_set = disjoint_set_create(size);

    disjoint_set_union(disjoint_set, 0, 1);
    disjoint_set_union(disjoint_set, 0, 2);
    disjoint_set_union(disjoint_set, 0, 3);
    disjoint_set_union(disjoint_set, 0, 4);
    disjoint_set_union(disjoint_set, 0, 0x1233);
    disjoint_set_union(disjoint_set, 0, 0x1200);

    value = disjoint_set_find(disjoint_set, 0);

    RESULT_CHECK_sint32(value, disjoint_set_find(disjoint_set, 1), &pass);
    RESULT_CHECK_sint32(value, disjoint_set_find(disjoint_set, 2), &pass);
    RESULT_CHECK_sint32(value, disjoint_set_find(disjoint_set, 0x1233), &pass);
    RESULT_CHECK_sint32(value, disjoint_set_find(disjoint_set, 0x1200), &pass);

    RESULT_CHECK_sint32(DISJOINT_ELE_INVALID, disjoint_set_find(disjoint_set, 0x1243), &pass);
    RESULT_CHECK_sint32(DISJOINT_ELE_INVALID, disjoint_set_find(NULL, 0x1243), &pass);

    disjoint_set_destroy(&disjoint_set);
    UNIT_TEST_RESULT(disjoint_set_find, pass);
}

static inline void
utest_disjoint_set_union(void)
{
    bool pass;
    uint32 size;
    s_disjoint_set_t *disjoint_set;

    UNIT_TEST_BEGIN(disjoint_set_union);

    pass = true;
    size = 0x1234;

    disjoint_set = disjoint_set_create(size);

    disjoint_set_union(NULL, 0, 1);
    disjoint_set_union(disjoint_set, 0x1300, 0);
    disjoint_set_union(disjoint_set, 0, 0x1400);
    disjoint_set_union(disjoint_set, 0, 0);

    disjoint_set_union(disjoint_set, 0, 1);
    disjoint_set_union(disjoint_set, 0, 2);
    disjoint_set_union(disjoint_set, 0, 3);
    disjoint_set_union(disjoint_set, 4, 5);
    disjoint_set_union(disjoint_set, 4, 0x1000);
    disjoint_set_union(disjoint_set, 4, 0x1001);
    disjoint_set_union(disjoint_set, 0, 4);

    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 0, 0), &pass);
    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 0, 4), &pass);
    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 0, 5), &pass);

    disjoint_set_destroy(&disjoint_set);
    UNIT_TEST_RESULT(disjoint_set_union, pass);
}

static inline void
utest_disjoint_set_equivalent_p(void)
{
    bool pass;
    uint32 size;
    s_disjoint_set_t *disjoint_set;

    UNIT_TEST_BEGIN(disjoint_set_equivalent_p);

    pass = true;
    size = 0x1234;

    disjoint_set = disjoint_set_create(size);

    disjoint_set_union(disjoint_set, 0, 1);
    disjoint_set_union(disjoint_set, 0, 2);
    disjoint_set_union(disjoint_set, 0, 3);
    disjoint_set_union(disjoint_set, 4, 5);
    disjoint_set_union(disjoint_set, 4, 0x1233);
    disjoint_set_union(disjoint_set, 4, 0x1200);

    RESULT_CHECK_bool(false, disjoint_set_equivalent_p(disjoint_set, 0x2000, 1), &pass);
    RESULT_CHECK_bool(false, disjoint_set_equivalent_p(disjoint_set, 1, 0x1342), &pass);
    RESULT_CHECK_bool(false, disjoint_set_equivalent_p(disjoint_set, 4, 0), &pass);
    RESULT_CHECK_bool(false, disjoint_set_equivalent_p(NULL, 0, 1), &pass);

    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 0, 1), &pass);
    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 0, 3), &pass);
    RESULT_CHECK_bool(true, disjoint_set_equivalent_p(disjoint_set, 4, 5), &pass);

    disjoint_set_destroy(&disjoint_set);
    UNIT_TEST_RESULT(disjoint_set_equivalent_p, pass);
}

