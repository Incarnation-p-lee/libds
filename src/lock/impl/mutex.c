static inline bool
mutex_legal_ip(s_mutex_t *mutex)
{
    if (NULL_PTR_P(mutex)) {
        return false;
    } else if (semaphore_illegal_ip(mutex->semaphore)) {
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

static inline s_semaphore_t *
mutex_semaphore(s_mutex_t *mutex)
{
    assert_exit(mutex_legal_ip(mutex));

    return mutex->semaphore;
}

s_mutex_t *
mutex_create(void)
{
    s_mutex_t *mutex;

    mutex = memory_cache_allocate(sizeof(*mutex));

    mutex->semaphore = semaphore_create_i(1);

    return mutex;
}

void
mutex_destroy(s_mutex_t **mutex)
{
    if (NULL_PTR_P(mutex) || MUTEX_ILLEGAL_P(*mutex)) {
        return;
    } else {
        semaphore_destroy_i(mutex_semaphore(*mutex));
        memory_cache_free(*mutex);
        *mutex = NULL;
    }
}

static inline void
mutex_lock_i(s_mutex_t *mutex)
{
    s_semaphore_t *semaphore;

    assert_exit(mutex_legal_ip(mutex));

    semaphore = mutex_semaphore(mutex);

    semaphore_down_i(semaphore);
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

static inline void
mutex_unlock_i(s_mutex_t *mutex)
{
    s_semaphore_t *semaphore;

    assert_exit(mutex_legal_ip(mutex));

    semaphore = mutex_semaphore(mutex);

    semaphore_up_i(semaphore);
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

