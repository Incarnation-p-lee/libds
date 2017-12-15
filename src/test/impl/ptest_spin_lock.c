static inline void
ptest_spin_lock_create(uint32 count)
{
    s_spin_lock_t *spin_lock;

    PERFORMANCE_TEST_BEGIN(spin_lock_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock = spin_lock_create();
        spin_lock_destroy(&spin_lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(spin_lock_create);
}

static inline void
ptest_spin_lock_destroy(uint32 count)
{
    s_spin_lock_t *spin_lock;

    PERFORMANCE_TEST_BEGIN(spin_lock_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock = spin_lock_create();
        spin_lock_destroy(&spin_lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(spin_lock_destroy);
}

static inline void
ptest_spin_lock_try(uint32 count)
{
    s_spin_lock_t *spin_lock;

    spin_lock = spin_lock_create();

    PERFORMANCE_TEST_BEGIN(spin_lock_try);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock_try(spin_lock);
        spin_lock_release(spin_lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&spin_lock);

    PERFORMANCE_TEST_RESULT(spin_lock_try);
}

static inline void
ptest_spin_lock_release(uint32 count)
{
    s_spin_lock_t *spin_lock;

    spin_lock = spin_lock_create();

    PERFORMANCE_TEST_BEGIN(spin_lock_release);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock_try(spin_lock);
        spin_lock_release(spin_lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&spin_lock);

    PERFORMANCE_TEST_RESULT(spin_lock_release);
}

