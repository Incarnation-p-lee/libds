static inline void
utest_spin_lock_create(void)
{
    bool pass;
    s_spin_lock_t *lock;

    UNIT_TEST_BEGIN(spin_lock_create);

    pass = true;
    lock = spin_lock_create();
    lock->shared_lock = 2;

    RESULT_CHECK_bool(false, spin_lock_legal_p(lock), &pass);
    RESULT_CHECK_bool(false, spin_locked_p(NULL), &pass);

    spin_lock_initial(lock);

    RESULT_CHECK_bool(true, spin_lock_legal_p(lock), &pass);
    RESULT_CHECK_bool(false, spin_locked_p(lock), &pass);

    spin_lock_destroy(&lock);

    UNIT_TEST_RESULT(spin_lock_create, pass);
}

static inline void
utest_spin_lock_destroy(void)
{
    bool pass;
    s_spin_lock_t *lock;

    UNIT_TEST_BEGIN(spin_lock_destroy);

    pass = true;
    lock = spin_lock_create();

    spin_lock_destroy(&lock);
    RESULT_CHECK_pointer(NULL, lock, &pass);

    UNIT_TEST_RESULT(spin_lock_destroy, pass);
}

static inline void *
utest_spin_lock_thread(void *lock_sample)
{
    uint32 i;
    s_spin_lock_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(lock_sample));

    i = 0;
    sample = lock_sample;

    spin_lock(sample->lock);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = sample->idx;

        i++;
    }

    spin_unlock(sample->lock);

    return NULL;
}

static inline void
utest_spin_lock(void)
{
    uint32 i;
    bool pass;
    s_spin_lock_t *lock;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_spin_lock_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(spin_lock);

    pass = true;
    lock = spin_lock_create();

    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].lock = lock;
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_spin_lock_thread, &sample[i]);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        RESULT_CHECK_uint32(critical_section[i], i, &pass);
    }

    spin_lock_destroy(&lock);
    UNIT_TEST_RESULT(spin_lock, pass);
}

static inline void
utest_spin_unlock(void)
{
    bool pass;
    dp_thread_id_t id;
    s_spin_lock_t *lock;
    s_spin_lock_sample_t sample;

    UNIT_TEST_BEGIN(spin_unlock);

    pass = true;
    lock = spin_lock_create();

    spin_lock(lock);
    spin_unlock(lock);
    RESULT_CHECK_bool(false, spin_locked_p(lock), &pass);

    sample.idx = 0;
    sample.lock = lock;

    dp_thread_create(&id, NULL, utest_spin_lock_thread, &sample);

    spin_unlock(lock);
    RESULT_CHECK_bool(false, spin_locked_p(lock), &pass);

    dp_thread_join(id, NULL);

    spin_lock_destroy(&lock);
    UNIT_TEST_RESULT(spin_unlock, pass);
}

static inline void
utest_spin_unlocked_p(void)
{
    bool pass;
    s_spin_lock_t *lock;

    UNIT_TEST_BEGIN(spin_unlocked_p);

    pass = true;
    lock = spin_lock_create();

    RESULT_CHECK_bool(false, spin_unlocked_p(NULL), &pass);
    RESULT_CHECK_bool(true, spin_unlocked_p(lock), &pass);

    spin_lock(lock);

    RESULT_CHECK_bool(false, spin_unlocked_p(lock), &pass);

    spin_unlock(lock);

    RESULT_CHECK_bool(true, spin_unlocked_p(lock), &pass);

    spin_lock_destroy(&lock);
    UNIT_TEST_RESULT(spin_unlocked_p, pass);
}

static inline void
utest_spin_locked_p(void)
{
    bool pass;
    s_spin_lock_t *lock;

    UNIT_TEST_BEGIN(spin_locked_p);

    pass = true;
    lock = spin_lock_create();

    RESULT_CHECK_bool(false, spin_locked_p(NULL), &pass);
    RESULT_CHECK_bool(false, spin_locked_p(lock), &pass);

    spin_lock(lock);

    RESULT_CHECK_bool(true, spin_locked_p(lock), &pass);

    spin_unlock(lock);

    RESULT_CHECK_bool(false, spin_locked_p(lock), &pass);

    spin_lock_destroy(&lock);
    UNIT_TEST_RESULT(spin_locked_p, pass);
}

static inline void *
utest_spin_lock_try_thread(void *lock_sample)
{
    uint32 i;
    bool is_succ;
    s_spin_lock_sample_t *sample;

    assert_exit(NON_NULL_PTR_P(lock_sample));

    sample = lock_sample;

    is_succ = spin_lock_try(sample->lock);

    if (is_succ == false) {
        return NULL;
    }

    for (i = 0; i < 10000000; i++) {
        ;
    }

    critical_section[0] += 1;

    spin_unlock(sample->lock);

    return (void *)(ptr_t)i;
}

static inline void
utest_spin_lock_try(void)
{
    uint32 i;
    bool pass;
    s_spin_lock_t *lock;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_spin_lock_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(spin_lock);

    pass = true;
    lock = spin_lock_create();

    RESULT_CHECK_bool(false, spin_lock_try(NULL), &pass);

    test_lock_critical_section_init();

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        sample[i].idx = i;
        sample[i].lock = lock;
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_create(&ids[i], NULL, utest_spin_lock_try_thread, &sample[i]);
    }

    for (i = 0; i < LOCK_THREAD_MAX; i++) {
        dp_thread_join(ids[i], NULL);
    }

    RESULT_CHECK_uint32(critical_section[0], 1, &pass);

    for (i = 1; i < LOCK_THREAD_MAX; i++) {
        RESULT_CHECK_uint32(critical_section[i], 0, &pass);
    }

    spin_lock_destroy(&lock);
    UNIT_TEST_RESULT(spin_lock, pass);
}

