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

    RESULT_CHECK_bool(true, spin_lock_legal_p(spin_lock), &pass);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    spin_lock_destroy(&spin_lock);
    RESULT_CHECK_pointer(NULL, spin_lock, &pass);

    UNIT_TEST_RESULT(spin_lock_destroy, pass);
}

static inline void *
utest_spin_lock_thread(void *spin_lock_sample)
{
    s_spin_lock_sample_t *sample;

    assert_exit(!complain_null_pointer_p(spin_lock_sample));

    sample = spin_lock_sample;

    spin_lock_try(sample->spin_lock);

    critical_section[sample->idx] = 'A' + sample->idx;

    spin_lock_release(sample->spin_lock);

    return NULL;
}

static inline void
utest_spin_lock_try(void)
{
    uint32 i;
    bool pass;
    s_spin_lock_t *spin_lock;
    s_spin_lock_sample_t sample[LOCK_THREAD_MAX];
    pthread_t threads[LOCK_THREAD_MAX];

    UNIT_TEST_BEGIN(spin_lock_try);

    pass = true;
    spin_lock = spin_lock_create();

    RESULT_CHECK_bool(true, spin_lock_legal_p(spin_lock), &pass);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    i = 0;

    while (i < LOCK_THREAD_MAX) {
        sample[i].idx = i;
        sample[i].spin_lock = spin_lock;

        i++;
    }

    i = 0;

    while (i < LOCK_THREAD_MAX) {
        pthread_create(&threads[i], NULL, utest_spin_lock_thread, &sample[i]);

        i++;
    }

    i = 0;

    while (i < LOCK_THREAD_MAX) {
        pthread_join(threads[i], NULL);

        i++;
    }

    // printf("%s\n", critical_section);

    spin_lock_destroy(&spin_lock);
    UNIT_TEST_RESULT(spin_lock_try, pass);
}

