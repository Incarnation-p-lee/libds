static inline void
utest_semaphore_create(void)
{
    bool pass;
    uint32 val;
    s_semaphore_t *semaphore;
    s_array_queue_t *queue_tmp;

    UNIT_TEST_BEGIN(semaphore_create);

    val = 4;
    pass = true;

    semaphore = semaphore_create(0);
    RESULT_CHECK_pointer(PTR_INVALID, semaphore, &pass);

    semaphore = semaphore_create(val);
    semaphore->lock.shared_lock = 2;
    RESULT_CHECK_bool(false, semaphore_legal_p(semaphore), &pass);
    semaphore->lock.shared_lock = 0;

    queue_tmp = semaphore->sleep_queue;
    semaphore->sleep_queue = NULL;
    RESULT_CHECK_bool(false, semaphore_legal_p(semaphore), &pass);
    semaphore->sleep_queue = queue_tmp;

    RESULT_CHECK_bool(true, semaphore_legal_p(semaphore), &pass);
    RESULT_CHECK_bool(false, semaphore_illegal_p(semaphore), &pass);

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
    semaphore = NULL;

    semaphore_destroy(NULL);
    semaphore_destroy(&semaphore);

    semaphore = semaphore_create(val);

    RESULT_CHECK_bool(true, semaphore_legal_p(semaphore), &pass);

    semaphore_destroy(&semaphore);
    RESULT_CHECK_pointer(NULL, semaphore, &pass);

    UNIT_TEST_RESULT(semaphore_destroy, pass);
}

static inline void *
utest_semaphore_thread_0(void *semaphore_sample)
{
    uint32 i;
    s_semaphore_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(semaphore_sample));

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

static inline void *
utest_semaphore_thread_1(void *semaphore_sample)
{
    uint32 i;
    s_semaphore_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(semaphore_sample));

    i = 0;
    sample = semaphore_sample;

    semaphore_down(sample->semaphore);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = 1;

        i++;
    }

    return NULL;
}

static inline void *
utest_semaphore_thread_try(void *semaphore_sample)
{
    uint32 i;
    bool is_success;
    s_semaphore_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(semaphore_sample));

    sample = semaphore_sample;
    is_success = semaphore_down_try(sample->semaphore);

    if (is_success == false) {
        return (void *)LOCK_MARK;
    }

    for (i = 0; i < LOOP_COUNT; i++) {
        critical_section[sample->idx] = sample->idx;
    }

    return NULL;
}

static inline void
utest_semaphore_down_try(void)
{
    bool pass;
    uint32 i, val;
    void *thread_retval;
    s_semaphore_t *semaphore;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_semaphore_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(semaphore_down_try);

    val = 12;
    pass = true;
    semaphore = semaphore_create(val);
    RESULT_CHECK_bool(false, semaphore_down_try(NULL), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
    }

    test_lock_critical_section_init();

    for (i = 0; i < val; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_try, &sample[i]);
    }

    for (i = 0; i < val; i++) {
        dp_thread_join(ids[i], &thread_retval);
        RESULT_CHECK_pointer(NULL, thread_retval, &pass);
        RESULT_CHECK_uint32(i, critical_section[i], &pass);
    }

    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_try, &sample[i]);
    }

    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], &thread_retval);
        RESULT_CHECK_pointer((void *)LOCK_MARK, thread_retval, &pass);
    }

    for (i = 0; i < val; i++) {
        semaphore_up(semaphore);
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_down_try, pass);
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

    val = 8;
    pass = true;
    semaphore_down(NULL);
    semaphore = semaphore_create(val);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
    }

    test_lock_critical_section_init();
    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_0, &sample[i]);
    }
    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(i, critical_section[i], &pass);
    }

    test_lock_critical_section_init();
    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        if (i < val) {
            dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
            dp_thread_join(ids[i], NULL);
        } else {
            dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
        }
    }
    for (i = count = 0; i < LOCK_THREAD_MAX; i++) {
        if (critical_section[i] == 1) {
            count++;
        }
    }
    RESULT_CHECK_uint32(count, val, &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        semaphore_up(semaphore);
    }
    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(1, critical_section[i], &pass);
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_down, pass);
}

static inline void
utest_semaphore_up(void)
{
    bool pass;
    uint32 val, i;
    s_semaphore_t *semaphore;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_semaphore_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(semaphore_up);

    val = 4;
    pass = true;
    semaphore_up(NULL);
    semaphore = semaphore_create(val);
    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        if (i < val) {
            dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
            dp_thread_join(ids[i], NULL);
        } else {
            dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
        }
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        semaphore_up(semaphore);
    }

    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(1, critical_section[i], &pass);
    }

    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        semaphore_up(semaphore);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(1, critical_section[i], &pass);
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_up, pass);
}

static inline void
utest_semaphore_available_p(void)
{
    bool pass;
    uint32 val, i;
    s_semaphore_t *semaphore;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_semaphore_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(semaphore_available_p);

    val = 3;
    pass = true;
    semaphore = semaphore_create(val);

    RESULT_CHECK_bool(false, semaphore_available_p(NULL), &pass);
    RESULT_CHECK_bool(true, semaphore_available_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
    }

    for (i = 0; i < val; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
        dp_thread_join(ids[i], NULL);
    }

    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
    }

    RESULT_CHECK_bool(false, semaphore_available_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        semaphore_up(semaphore);
    }

    RESULT_CHECK_bool(true, semaphore_available_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_available_p, pass);
}

static inline void
utest_semaphore_unavailable_p(void)
{
    bool pass;
    uint32 val, i;
    s_semaphore_t *semaphore;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_semaphore_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(semaphore_unavailable_p);

    val = 3;
    pass = true;
    semaphore = semaphore_create(val);

    RESULT_CHECK_bool(true, semaphore_unavailable_p(NULL), &pass);
    RESULT_CHECK_bool(false, semaphore_unavailable_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].semaphore = semaphore;
    }

    for (i = 0; i < val; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
        dp_thread_join(ids[i], NULL);
    }

    for (i = val; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_semaphore_thread_1, &sample[i]);
    }

    RESULT_CHECK_bool(true, semaphore_unavailable_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        semaphore_up(semaphore);
    }

    RESULT_CHECK_bool(false, semaphore_unavailable_p(semaphore), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    semaphore_destroy(&semaphore);
    UNIT_TEST_RESULT(semaphore_unavailable_p, pass);
}

