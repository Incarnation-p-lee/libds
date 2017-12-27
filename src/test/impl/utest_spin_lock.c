static inline void
utest_spin_lock_create(void)
{
    bool pass;
    s_spin_lock_t *spin_lock;

    UNIT_TEST_BEGIN(spin_lock_create);

    pass = true;
    spin_lock = spin_lock_create();

    RESULT_CHECK_bool(true, spin_lock_legal_p(spin_lock), &pass);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    spin_lock_destroy(&spin_lock);

    UNIT_TEST_RESULT(spin_lock_create, pass);
}

static inline void
utest_spin_lock_destroy(void)
{
    bool pass;
    s_spin_lock_t *spin_lock;

    UNIT_TEST_BEGIN(spin_lock_destroy);

    pass = true;
    spin_lock = spin_lock_create();

    spin_lock_destroy(&spin_lock);
    RESULT_CHECK_pointer(NULL, spin_lock, &pass);

    UNIT_TEST_RESULT(spin_lock_destroy, pass);
}

static inline void *
utest_spin_lock_thread(void *spin_lock_sample)
{
    uint32 i;
    s_spin_lock_sample_t *sample;

    assert_exit(!complain_null_pointer_p(spin_lock_sample));

    i = 0;
    sample = spin_lock_sample;

    spin_lock_try(sample->spin_lock);

    while (i < LOOP_COUNT) {
        critical_section[sample->idx] = sample->idx;

        i++;
    }

    spin_lock_release(sample->spin_lock);

    return NULL;
}

static inline void
utest_spin_lock_try(void)
{
    bool pass;
    uint32 i, count;
    s_spin_lock_t *spin_lock;
    dp_thread_id_t ids[LOCK_THREAD_MAX];
    s_spin_lock_sample_t sample[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(spin_lock_try);

    pass = true;
    spin_lock = spin_lock_create();

    count = sizeof(critical_section[0]) * LOCK_THREAD_MAX;
    dp_memset(critical_section, 0, count);

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        sample[i].idx = i;
        sample[i].spin_lock = spin_lock;
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        dp_thread_create(&ids[i], NULL, utest_spin_lock_thread, &sample[i]);
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        dp_thread_join(ids[i], NULL);
        i++;
    }

    i = 0;
    while (i < LOCK_THREAD_MAX) {
        RESULT_CHECK_uint32(critical_section[i], i, &pass);
        i++;
    }

    spin_lock_destroy(&spin_lock);
    UNIT_TEST_RESULT(spin_lock_try, pass);
}

static inline void
utest_spin_lock_release(void)
{
    bool pass;
    dp_thread_id_t id;
    s_spin_lock_t *spin_lock;
    s_spin_lock_sample_t sample;

    UNIT_TEST_BEGIN(spin_lock_release);

    pass = true;
    spin_lock = spin_lock_create();

    spin_lock_try(spin_lock);
    spin_lock_release(spin_lock);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    sample.idx = 0;
    sample.spin_lock = spin_lock;

    dp_thread_create(&id, NULL, utest_spin_lock_thread, &sample);

    spin_lock_release(spin_lock);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    dp_thread_join(id, NULL);

    spin_lock_destroy(&spin_lock);
    UNIT_TEST_RESULT(spin_lock_release, pass);
}

