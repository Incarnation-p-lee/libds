static inline bool
mutex_legal_ip(s_mutex_t *mutex)
{
    if (NULL_PTR_P(mutex)) {
        return false;
    } else if (semaphore_illegal_ip(MUTEX_SEMAPHORE(mutex))) {
        return false;
    } else {
        return true;
    }
}

static inline bool
mutex_illegal_ip(s_mutex_t *mutex)
{
    return !mutex_legal_ip(mutex);
}

bool
mutex_legal_p(s_mutex_t *mutex)
{
    return mutex_legal_ip(mutex);
}

bool
mutex_illegal_p(s_mutex_t *mutex)
{
    return mutex_illegal_ip(mutex);
}

s_mutex_t *
mutex_create(void)
{
    s_mutex_t *mutex;

    mutex = memory_cache_allocate(sizeof(*mutex));

    MUTEX_SEMAPHORE(mutex) = semaphore_create_i(1);

    return mutex;
}

void
mutex_destroy(s_mutex_t **mutex)
{
    if (NULL_PTR_P(mutex) || MUTEX_ILLEGAL_P(*mutex)) {
        return;
    } else {
        semaphore_destroy_i(MUTEX_SEMAPHORE(*mutex));
        memory_cache_free(*mutex);

        *mutex = NULL;
    }
}

static inline void
mutex_lock_i(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    semaphore_down_i(MUTEX_SEMAPHORE(mutex));
}

void
mutex_lock(s_mutex_t *mutex)
{
    if (MUTEX_ILLEGAL_P(mutex)) {
        return;
    } else {
        mutex_lock_i(mutex);
    }
}

static inline bool
mutex_lock_try_i(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    return semaphore_down_try_i(MUTEX_SEMAPHORE(mutex));
}

bool
mutex_lock_try(s_mutex_t *mutex)
{
    if (MUTEX_ILLEGAL_P(mutex)) {
        return false;
    } else {
        return mutex_lock_try_i(mutex);
    }
}

static inline void
mutex_unlock_i(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    semaphore_up_i(MUTEX_SEMAPHORE(mutex));
}

void
mutex_unlock(s_mutex_t *mutex)
{
    if (MUTEX_ILLEGAL_P(mutex)) {
        return;
    } else {
        mutex_unlock_i(mutex);
    }
}

static inline bool
mutex_locked_ip(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    return semaphore_unavailable_p(MUTEX_SEMAPHORE(mutex));
}

bool
mutex_locked_p(s_mutex_t *mutex)
{
    if (MUTEX_ILLEGAL_P(mutex)) {
        return true;
    } else {
        return mutex_locked_ip(mutex);
    }
}

static inline bool
mutex_unlocked_ip(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    return semaphore_available_p(MUTEX_SEMAPHORE(mutex));
}

bool
mutex_unlocked_p(s_mutex_t *mutex)
{
    if (MUTEX_ILLEGAL_P(mutex)) {
        return false;
    } else {
        return mutex_unlocked_ip(mutex);
    }
}

