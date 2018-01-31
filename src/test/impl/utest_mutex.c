static inline void
utest_mutex_create(void)
{
    bool pass;
    s_mutex_t *mutex;
    s_semaphore_t *semaphore;

    UNIT_TEST_BEGIN(mutex_create);

    pass = true;
    mutex = mutex_create();
    RESULT_CHECK_NOT_EQUAL_pointer(PTR_INVALID, mutex, &pass);
    RESULT_CHECK_bool(true, mutex_legal_p(mutex), &pass);
    RESULT_CHECK_bool(false, mutex_illegal_p(mutex), &pass);

    semaphore = mutex->semaphore;
    mutex->semaphore = NULL;
    RESULT_CHECK_bool(true, semaphore_legal_p(semaphore), &pass);
    RESULT_CHECK_bool(false, mutex_legal_p(mutex), &pass);
    mutex->semaphore = semaphore;

    mutex_destroy(&mutex);

    UNIT_TEST_RESULT(mutex_create, pass);
}

static inline void
utest_mutex_destroy(void)
{
    bool pass;
    s_mutex_t *mutex;

    UNIT_TEST_BEGIN(mutex_destroy);

    pass = true;
    mutex = NULL;

    mutex_destroy(NULL);
    mutex_destroy(&mutex);
    RESULT_CHECK_pointer(NULL, mutex, &pass);

    mutex = mutex_create();
    RESULT_CHECK_bool(true, mutex_legal_p(mutex), &pass);

    mutex_destroy(&mutex);
    RESULT_CHECK_pointer(NULL, mutex, &pass);

    UNIT_TEST_RESULT(mutex_destroy, pass);
}

static inline void *
utest_mutex_thread_try(void *mutex_sample)
{
    uint32 i;
    bool is_success;
    s_mutex_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(mutex_sample));

    sample = mutex_sample;
    is_success = mutex_lock_try(sample->mutex);

    if (is_success == false) {
        return (void *)LOCK_MARK;
    }

    for (i = 0; i < LOOP_COUNT; i++) {
        critical_section[sample->idx] = sample->idx;
    }

    return NULL;
}

static inline void
utest_mutex_lock_try(void)
{
    uint32 i;
    bool pass;
    s_mutex_t *mutex;
    void *thread_retval;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_mutex_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(mutex_lock_try);

    pass = true;
    mutex = mutex_create();
    RESULT_CHECK_bool(false, mutex_lock_try(NULL), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].mutex = mutex;
    }

    test_lock_critical_section_init();

    dp_thread_create(&ids[0], NULL, utest_mutex_thread_try, &sample[0]);
    dp_thread_join(ids[0], &thread_retval);

    RESULT_CHECK_pointer(NULL, thread_retval, &pass);
    RESULT_CHECK_uint32(0, critical_section[0], &pass);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_try, &sample[i]);
    }

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], &thread_retval);
        RESULT_CHECK_pointer((void *)LOCK_MARK, thread_retval, &pass);
    }

    mutex_unlock(mutex);

    mutex_destroy(&mutex);
    UNIT_TEST_RESULT(mutex_lock_try, pass);
}

static inline void *
utest_mutex_thread_0(void *mutex_sample)
{
    uint32 i;
    s_mutex_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(mutex_sample));

    i = 0;
    sample = mutex_sample;

    mutex_lock(sample->mutex);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = sample->idx;

        i++;
    }

    mutex_unlock(sample->mutex);

    return NULL;
}

static inline void *
utest_mutex_thread_1(void *mutex_sample)
{
    uint32 i;
    s_mutex_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(mutex_sample));

    i = 0;
    sample = mutex_sample;

    mutex_lock(sample->mutex);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = 1;

        i++;
    }

    return NULL;
}

static inline void
utest_mutex_lock(void)
{
    uint32 i;
    bool pass;
    s_mutex_t *mutex;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_mutex_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(mutex_lock);

    pass = true;
    mutex_lock(NULL);
    mutex = mutex_create();
    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].mutex = mutex;
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_0, &sample[i]);
    }
    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(i, critical_section[i], &pass);
    }

    test_lock_critical_section_init();
    dp_thread_create(&ids[0], NULL, utest_mutex_thread_1, &sample[0]);
    dp_thread_join(ids[0], NULL);
    RESULT_CHECK_uint32(critical_section[0], 1, &pass);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_1, &sample[i]);
    }
    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        RESULT_CHECK_uint32(critical_section[i], 0, &pass);
    }

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        mutex_unlock(mutex);
    }
    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(1, critical_section[i], &pass);
    }

    mutex_destroy(&mutex);
    UNIT_TEST_RESULT(mutex_lock, pass);
}

static inline void
utest_mutex_unlock(void)
{
    uint32 i;
    bool pass;
    s_mutex_t *mutex;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_mutex_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(mutex_unlock);

    pass = true;
    mutex_unlock(NULL);
    mutex = mutex_create();
    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].mutex = mutex;
    }

    dp_thread_create(&ids[0], NULL, utest_mutex_thread_1, &sample[0]);
    dp_thread_join(ids[0], NULL);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_1, &sample[i]);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        mutex_unlock(mutex);
    }

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(1, critical_section[i], &pass);
    }

    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_0, &sample[i]);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
        RESULT_CHECK_uint32(i, critical_section[i], &pass);
    }

    mutex_destroy(&mutex);
    UNIT_TEST_RESULT(mutex_unlock, pass);
}

static inline void
utest_mutex_locked_p(void)
{
    uint32 i;
    bool pass;
    s_mutex_t *mutex;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_mutex_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(mutex_locked_p);

    pass = true;
    mutex = mutex_create();

    RESULT_CHECK_bool(true, mutex_locked_p(NULL), &pass);
    RESULT_CHECK_bool(false, mutex_locked_p(mutex), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].mutex = mutex;
    }

    dp_thread_create(&ids[0], NULL, utest_mutex_thread_1, &sample[0]);
    dp_thread_join(ids[0], NULL);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_1, &sample[i]);
    }

    RESULT_CHECK_bool(true, mutex_locked_p(mutex), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        mutex_unlock(mutex);
    }

    RESULT_CHECK_bool(false, mutex_locked_p(mutex), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    mutex_destroy(&mutex);
    UNIT_TEST_RESULT(mutex_locked_p, pass);
}

static inline void
utest_mutex_unlocked_p(void)
{
    uint32 i;
    bool pass;
    s_mutex_t *mutex;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_mutex_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(mutex_unlocked_p);

    pass = true;
    mutex = mutex_create();

    RESULT_CHECK_bool(false, mutex_unlocked_p(NULL), &pass);
    RESULT_CHECK_bool(true, mutex_unlocked_p(mutex), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].mutex = mutex;
    }

    dp_thread_create(&ids[0], NULL, utest_mutex_thread_1, &sample[0]);
    dp_thread_join(ids[0], NULL);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_mutex_thread_1, &sample[i]);
    }

    RESULT_CHECK_bool(false, mutex_unlocked_p(mutex), &pass);

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        mutex_unlock(mutex);
    }

    RESULT_CHECK_bool(true, mutex_unlocked_p(mutex), &pass);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    mutex_destroy(&mutex);
    UNIT_TEST_RESULT(mutex_unlocked_p, pass);
}

