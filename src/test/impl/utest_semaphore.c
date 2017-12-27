static inline void
utest_semaphore_create(void)
{
    bool pass;
    uint32 val;
    s_semaphore_t *semaphore;

    UNIT_TEST_BEGIN(semaphore_create);

    val = 4;
    pass = true;
    semaphore = semaphore_create(val);

    RESULT_CHECK_bool(true, semaphore_legal_p(semaphore), &pass);

    semaphore_destroy(&semaphore);

    UNIT_TEST_RESULT(semaphore_create, pass);
}

static inline void
utest_semaphore_destroy(void)
{
    bool pass;
    uint32 val;
    s_semaphore_t *semaphore;

    UNIT_TEST_BEGIN(semaphore_destroy);

    val = 4;
    pass = true;
    semaphore = semaphore_create(val);

    RESULT_CHECK_bool(true, semaphore_legal_p(semaphore), &pass);

    semaphore_destroy(&semaphore);
    RESULT_CHECK_pointer(NULL, semaphore, &pass);

    UNIT_TEST_RESULT(semaphore_destroy, pass);
}

static inline void *
utest_semaphore_thread(void *semaphore_sample)
{
    uint32 i;
    s_semaphore_sample_t *sample;

    assert_exit(!complain_null_pointer_p(semaphore_sample));

    i = 0;
    sample = semaphore_sample;

    semaphore_down(sample->semaphore);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = sample->idx;

        i++;
    }

    semaphore_up(sample->semaphore);

    return NULL;
}

static inline void
utest_semaphore_down(void)
{
    bool pass;
    uint32 val, i, count;
    s_semaphore_t *semaphore;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_semaphore_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(semaphore_down);

    val = 0x4;
    pass = true;
    count = sizeof(critical_section[0]) * LOCK_THREAD_MAX;
    dp_memset(critical_section, 0, count);
    semaphore = semaphore_create(val);

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread, &sample[i]);
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        dp_thread_join(ids[i], NULL);
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        RESULT_CHECK_uint32(i, critical_section[i], &pass);
        i++;
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_down, pass);
}

