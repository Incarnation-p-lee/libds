static inline void
ptest_semaphore_create(uint32 count)
{
    uint32 val;
    s_semaphore_t *semaphore;

    val = 0x13;

    PERFORMANCE_TEST_BEGIN(semaphore_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        semaphore = semaphore_create(val);
        semaphore_destroy(&semaphore);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(semaphore_create);
}

static inline void
ptest_semaphore_destroy(uint32 count)
{
    uint32 val;
    s_semaphore_t *semaphore;

    val = 0x3;

    PERFORMANCE_TEST_BEGIN(semaphore_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        semaphore = semaphore_create(val);
        semaphore_destroy(&semaphore);
        semaphore_destroy(&semaphore);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(semaphore_destroy);
}

static inline void
ptest_semaphore_down(uint32 count)
{
    uint32 val;
    s_semaphore_t *semaphore;

    val = 0x12;
    semaphore = semaphore_create(val);

    PERFORMANCE_TEST_BEGIN(semaphore_down);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        semaphore_down(semaphore);
        semaphore_down(semaphore);
        semaphore_down(semaphore);
        semaphore_up(semaphore);
        semaphore_up(semaphore);
        semaphore_up(semaphore);
    }

    PERFORMANCE_TEST_ENDPOINT;

    semaphore_destroy(&semaphore);
    PERFORMANCE_TEST_RESULT(semaphore_down);
}

static inline void
ptest_semaphore_up(uint32 count)
{
    uint32 val;
    s_semaphore_t *semaphore;

    val = 0x12;
    semaphore = semaphore_create(val);

    PERFORMANCE_TEST_BEGIN(semaphore_up);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        semaphore_up(semaphore);
        semaphore_up(semaphore);
        semaphore_up(semaphore);
        semaphore_up(semaphore);
    }

    PERFORMANCE_TEST_ENDPOINT;

    semaphore_destroy(&semaphore);
    PERFORMANCE_TEST_RESULT(semaphore_up);
}

static inline void
ptest_semaphore_available_p(uint32 count)
{
    uint32 val;
    s_semaphore_t *semaphore;

    val = 0x32;
    semaphore = semaphore_create(val);

    PERFORMANCE_TEST_BEGIN(semaphore_available_p);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
        semaphore_available_p(semaphore);
    }

    PERFORMANCE_TEST_ENDPOINT;

    semaphore_destroy(&semaphore);
    PERFORMANCE_TEST_RESULT(semaphore_available_p);
}

