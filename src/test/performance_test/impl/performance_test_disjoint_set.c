static inline void
ptest_disjoint_set_create(uint32 count)
{
    s_disjoint_set_t *disjoint_set;

    PERFORMANCE_TEST_BEGIN(disjoint_set_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        disjoint_set = disjoint_set_create(0x134);
        disjoint_set_destroy(&disjoint_set);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(disjoint_set_create);
}

static inline void
ptest_disjoint_set_destroy(uint32 count)
{
    s_disjoint_set_t *disjoint_set;

    PERFORMANCE_TEST_BEGIN(disjoint_set_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        disjoint_set = disjoint_set_create(0x234);
        disjoint_set_destroy(&disjoint_set);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(disjoint_set_destroy);
}

static inline void
ptest_disjoint_set_find(uint32 count)
{
    uint32 element;
    s_disjoint_set_t *disjoint_set;

    PERFORMANCE_TEST_BEGIN(disjoint_set_find);

    element = 0x230;
    disjoint_set = disjoint_set_create(0x234);

    disjoint_set_union(disjoint_set, 0, 1);
    disjoint_set_union(disjoint_set, 0, 2);
    disjoint_set_union(disjoint_set, 0, 3);
    disjoint_set_union(disjoint_set, 0, 4);
    disjoint_set_union(disjoint_set, 0, element);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        disjoint_set_find(disjoint_set, element);
    }

    PERFORMANCE_TEST_ENDPOINT;

    disjoint_set_destroy(&disjoint_set);

    PERFORMANCE_TEST_RESULT(disjoint_set_find);
}

static inline void
ptest_disjoint_set_union(uint32 count)
{
    uint32 element;
    s_disjoint_set_t *disjoint_set;

    PERFORMANCE_TEST_BEGIN(disjoint_set_union);

    element = 0x230;
    disjoint_set = disjoint_set_create(0x234);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        element = count % element + 1;
        disjoint_set_union(disjoint_set, 0, element);
    }

    PERFORMANCE_TEST_ENDPOINT;

    disjoint_set_destroy(&disjoint_set);

    PERFORMANCE_TEST_RESULT(disjoint_set_union);
}

static inline void
ptest_disjoint_set_equivalent_p(uint32 count)
{
    uint32 element;
    s_disjoint_set_t *disjoint_set;

    PERFORMANCE_TEST_BEGIN(disjoint_set_equivalent_p);

    element = 0x230;
    disjoint_set = disjoint_set_create(0x234);

    disjoint_set_union(disjoint_set, 0, 1);
    disjoint_set_union(disjoint_set, 0, 2);
    disjoint_set_union(disjoint_set, 0, 3);
    disjoint_set_union(disjoint_set, 9, element);
    disjoint_set_union(disjoint_set, 0, 9);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        disjoint_set_equivalent_p(disjoint_set, 0, element);
    }

    PERFORMANCE_TEST_ENDPOINT;

    disjoint_set_destroy(&disjoint_set);

    PERFORMANCE_TEST_RESULT(disjoint_set_equivalent_p);
}

