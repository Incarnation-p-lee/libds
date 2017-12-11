s_spin_lock_t *
spin_lock_create(void)
{
    s_spin_lock_t *spin_lock;

    spin_lock = memory_cache_allocate(sizeof(*spin_lock));
    spin_lock->lock = SPIN_LOCK_UNLOCKED;

    return spin_lock;
}

static inline bool
spin_lock_legal_p(s_spin_lock_t *spin_lock)
{
    if (complain_null_pointer_p(spin_lock)) {
        return false;
    } else if (spin_lock->lock > SPIN_LOCK_VAL_MAX) {
        return false;
    } else {
        return true;
    }
}

static inline bool
spin_lock_illegal_p(s_spin_lock_t *spin_lock)
{
    return spin_lock_legal_p(spin_lock);
}


static inline void
spin_lock_destroy(s_spin_lock_t *spin_lock)
{
    assert_exit(spin_lock_legal_p(spin_lock));

    memory_cache_free(spin_lock);
}

void
spin_lock_destroy(s_spin_lock_t **lock)
{
    if (complain_null_pointer_p(lock) || spin_lock_illegal_p(*lock)) {
        return;
    } else {
        spin_lock_destroy_i(*lock);
        *lock = NULL;
    }
}

static inline void
spin_lock_release_i(s_spin_lock_t *spin_lock)
{
    assert_exit(spin_lock_legal_p(spin_lock));

    spin_lock->lock = SPIN_LOCK_UNLOCKED;
}

void
spin_lock_release(s_spin_lock_t *spin_lock)
{
    if (spin_lock_illegal_p(spin_lock)) {
        return;
    } else {
        spin_lock_release_i(spin_lock);
    }
}

static inline void
spin_lock_try_i(s_spin_lock_t *spin_lock)
{
    assert_exit(spin_lock_legal_p(spin_lock));

    SPIN_LOCK_TRY(spin_lock)
}

void
spin_lock_try(s_spin_lock_t *spin_lock)
{
    if (spin_lock_illegal_p(spin_lock)) {
        return;
    } else {
        spin_lock_try_i(spin_lock);
    }
}

