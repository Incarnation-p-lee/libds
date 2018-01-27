static inline void
ptest_spin_lock_create(uint32 count)
{
    s_spin_lock_t *lock;

    PERFORMANCE_TEST_BEGIN(spin_lock_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        lock = spin_lock_create();
        spin_lock_destroy(&lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(spin_lock_create);
}

static inline void
ptest_spin_lock_destroy(uint32 count)
{
    s_spin_lock_t *lock;

    PERFORMANCE_TEST_BEGIN(spin_lock_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        lock = spin_lock_create();
        spin_lock_destroy(&lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(spin_lock_destroy);
}

static inline void
ptest_spin_lock(uint32 count)
{
    s_spin_lock_t *lock;

    lock = spin_lock_create();

    PERFORMANCE_TEST_BEGIN(spin_lock);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock(lock);
        spin_unlock(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&lock);

    PERFORMANCE_TEST_RESULT(spin_lock);
}

static inline void
ptest_spin_lock_try(uint32 count)
{
    s_spin_lock_t *lock;

    lock = spin_lock_create();

    PERFORMANCE_TEST_BEGIN(spin_lock_try);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
        spin_lock_try(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_unlock(lock);
    spin_lock_destroy(&lock);

    PERFORMANCE_TEST_RESULT(spin_lock_try);
}

static inline void
ptest_spin_unlock(uint32 count)
{
    s_spin_lock_t *lock;

    lock = spin_lock_create();

    PERFORMANCE_TEST_BEGIN(spin_unlock);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_lock(lock);
        spin_unlock(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&lock);

    PERFORMANCE_TEST_RESULT(spin_unlock);
}

static inline void
ptest_spin_unlocked_p(uint32 count)
{
    s_spin_lock_t *lock;

    PERFORMANCE_TEST_BEGIN(spin_unlocked_p);

    lock = spin_lock_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
        spin_unlocked_p(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&lock);
    PERFORMANCE_TEST_RESULT(spin_unlocked_p);
}

static inline void
ptest_spin_locked_p(uint32 count)
{
    s_spin_lock_t *lock;

    PERFORMANCE_TEST_BEGIN(spin_locked_p);

    lock = spin_lock_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
        spin_locked_p(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    spin_lock_destroy(&lock);
    PERFORMANCE_TEST_RESULT(spin_locked_p);
}

