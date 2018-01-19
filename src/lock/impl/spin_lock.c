static inline bool
spin_lock_legal_ip(s_spin_lock_t *lock)
{
    if (NULL_PTR_P(lock)) {
        return false;
    } else if (SPIN_SHARED_LOCK(lock) > SPIN_LOCK_VAL_MAX) {
        return false;
    } else {
        return true;
    }
}

bool
spin_lock_legal_p(s_spin_lock_t *lock)
{
    return spin_lock_legal_ip(lock);
}

bool
spin_lock_illegal_p(s_spin_lock_t *lock)
{
    return spin_lock_illegal_ip(lock);
}

static inline bool
spin_lock_illegal_ip(s_spin_lock_t *lock)
{
    return !spin_lock_legal_ip(lock);
}

static inline void
spin_lock_shared_lock_clear(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    SPIN_SHARED_LOCK(lock) = SPIN_LOCK_UNLOCKED;
}

s_spin_lock_t *
spin_lock_create(void)
{
    s_spin_lock_t *lock;

    lock = memory_cache_allocate(sizeof(*lock));

    spin_lock_initial_i(lock);

    return lock;
}

static inline void
spin_lock_initial_i(s_spin_lock_t *lock)
{
    assert_exit(NON_NULL_PTR_P(lock));

    SPIN_SHARED_LOCK(lock) = SPIN_LOCK_UNLOCKED;
}

void
spin_lock_initial(s_spin_lock_t *lock)
{
    if (NULL_PTR_P(lock)) {
        return;
    } else {
        spin_lock_initial_i(lock);
    }
}

static inline bool
spin_locked_ip(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    if (SPIN_SHARED_LOCK(lock) == SPIN_LOCK_LOCKED) {
        return true;
    } else {
        return false;
    }
}

static inline bool
spin_unlocked_ip(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    return !spin_locked_ip(lock);
}

bool
spin_locked_p(s_spin_lock_t *lock)
{
    if (SPIN_LOCK_ILLEGAL_P(lock)) {
        return false;
    } else {
        return spin_locked_ip(lock);
    }
}

bool
spin_unlocked_p(s_spin_lock_t *lock)
{
    if (SPIN_LOCK_ILLEGAL_P(lock)) {
        return false;
    } else {
        return spin_unlocked_ip(lock);
    }
}

static inline void
spin_lock_destroy_i(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    memory_cache_free(lock);
}

void
spin_lock_destroy(s_spin_lock_t **lock)
{
    if (NULL_PTR_P(lock) || SPIN_LOCK_ILLEGAL_P(*lock)) {
        return;
    } else {
        spin_lock_destroy_i(*lock);
        *lock = NULL;
    }
}

static inline void
spin_unlock_i(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    if (spin_locked_ip(lock)) {
        spin_lock_shared_lock_clear(lock);
    }
}

void
spin_unlock(s_spin_lock_t *lock)
{
    if (SPIN_LOCK_ILLEGAL_P(lock)) {
        return;
    } else {
        spin_unlock_i(lock);
    }
}

static inline void
spin_lock_i(s_spin_lock_t *lock)
{
    assert_exit(spin_lock_legal_ip(lock));

    SPIN_LOCK(lock);
}

void
spin_lock(s_spin_lock_t *lock)
{
    if (SPIN_LOCK_ILLEGAL_P(lock)) {
        return;
    } else {
        spin_lock_i(lock);
    }
}

