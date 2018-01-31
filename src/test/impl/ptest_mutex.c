static inline void
ptest_mutex_create(uint32 count)
{
    s_mutex_t *lock;

    PERFORMANCE_TEST_BEGIN(mutex_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        lock = mutex_create();
        mutex_destroy(&lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(mutex_create);
}

static inline void
ptest_mutex_destroy(uint32 count)
{
    s_mutex_t *lock;

    PERFORMANCE_TEST_BEGIN(mutex_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        lock = mutex_create();
        mutex_destroy(&lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(mutex_destroy);
}

static inline void
ptest_mutex_lock(uint32 count)
{
    s_mutex_t *lock;

    lock = mutex_create();

    PERFORMANCE_TEST_BEGIN(mutex_lock);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    mutex_destroy(&lock);

    PERFORMANCE_TEST_RESULT(mutex_lock);
}

static inline void
ptest_mutex_lock_try(uint32 count)
{
    s_mutex_t *lock;

    lock = mutex_create();

    PERFORMANCE_TEST_BEGIN(mutex_lock_try);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
        mutex_lock_try(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    mutex_unlock(lock);
    mutex_destroy(&lock);

    PERFORMANCE_TEST_RESULT(mutex_lock_try);
}

static inline void
ptest_mutex_unlock(uint32 count)
{
    s_mutex_t *lock;

    lock = mutex_create();

    PERFORMANCE_TEST_BEGIN(mutex_unlock);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
        mutex_lock(lock);
        mutex_unlock(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    mutex_destroy(&lock);

    PERFORMANCE_TEST_RESULT(mutex_unlock);
}

static inline void
ptest_mutex_unlocked_p(uint32 count)
{
    s_mutex_t *lock;

    PERFORMANCE_TEST_BEGIN(mutex_unlocked_p);

    lock = mutex_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
        mutex_unlocked_p(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    mutex_destroy(&lock);
    PERFORMANCE_TEST_RESULT(mutex_unlocked_p);
}

static inline void
ptest_mutex_locked_p(uint32 count)
{
    s_mutex_t *lock;

    PERFORMANCE_TEST_BEGIN(mutex_locked_p);

    lock = mutex_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
        mutex_locked_p(lock);
    }

    PERFORMANCE_TEST_ENDPOINT;

    mutex_destroy(&lock);
    PERFORMANCE_TEST_RESULT(mutex_locked_p);
}

