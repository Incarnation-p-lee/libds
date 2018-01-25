static inline s_spin_lock_t *
semaphore_lock(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    return &semaphore->lock;
}

static inline s_array_queue_t *
semaphore_sleep_queue(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    return semaphore->sleep_queue;
}

static inline sint32
semaphore_val(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    return semaphore->val;
}

static void
semaphore_sigcont_handler(sint32 signum)
{
    if (signum != SIGCONT) {
        assert_not_reached("Other signal invoked SIGCONT handler");
    }
}

static inline s_semaphore_t *
semaphore_create_i(uint32 val)
{
    s_semaphore_t *semaphore;

    assert_exit(val > 0);

    semaphore = memory_cache_allocate(sizeof(*semaphore));

    semaphore->val = val;
    semaphore->sleep_queue = array_queue_create();
    semaphore->act_new.sa_flags = SA_NODEFER;
    semaphore->act_new.sa_handler = semaphore_sigcont_handler;

    spin_lock_initial(&semaphore->lock);
    dp_sigaction(SIGCONT, &semaphore->act_new, &semaphore->act_old);

    return semaphore;
}

s_semaphore_t *
semaphore_create(uint32 val)
{
    if (val == 0) {
        return PTR_INVALID;
    } else {
        return semaphore_create_i(val);
    }
}

static inline bool
semaphore_legal_ip(s_semaphore_t *semaphore)
{
    if (complain_null_pointer_p(semaphore)) {
        return false;
    } else if (spin_lock_illegal_p(&semaphore->lock)) {
        return false;
    } else if (array_queue_structure_illegal_p(semaphore->sleep_queue)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
semaphore_illegal_ip(s_semaphore_t *semaphore)
{
    return !semaphore_legal_ip(semaphore);
}

bool
semaphore_legal_p(s_semaphore_t *semaphore)
{
    return semaphore_legal_ip(semaphore);
}

bool
semaphore_illegal_p(s_semaphore_t *semaphore)
{
    return !semaphore_legal_ip(semaphore);
}

static inline void
semaphore_destroy_i(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    dp_sigaction(SIGCONT, &semaphore->act_old, &semaphore->act_new);
    array_queue_destroy(&semaphore->sleep_queue);
    memory_cache_free(semaphore);
}

void
semaphore_destroy(s_semaphore_t **semaphore)
{
    if (NULL_PTR_P(semaphore) || SEMAPHORE_ILLEGAL_P(*semaphore)) {
        return;
    } else {
        semaphore_destroy_i(*semaphore);
        *semaphore = NULL;
    }
}

static inline void
semaphore_down_i(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock(semaphore_lock(semaphore));

    SEMAPHORE_DOWN(semaphore);

    if (semaphore_val(semaphore) >= 0) {
        spin_unlock(semaphore_lock(semaphore));
        return;
    }

    array_queue_enter(semaphore_sleep_queue(semaphore), (void *)dp_thread_id());

    spin_unlock(semaphore_lock(semaphore));

    dp_sleep();
}

void
semaphore_down(s_semaphore_t *semaphore)
{
    if (SEMAPHORE_ILLEGAL_P(semaphore)) {
        return;
    } else {
        semaphore_down_i(semaphore);
    }
}

static inline bool
semaphore_down_try_i(s_semaphore_t *semaphore)
{
    bool is_success;

    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock(semaphore_lock(semaphore));

    SEMAPHORE_DOWN(semaphore);

    if (semaphore_val(semaphore) < 0) {
        is_success = false;
        SEMAPHORE_UP(semaphore);
    } else {
        is_success = true;
    }

    spin_unlock(semaphore_lock(semaphore));

    return is_success;
}

bool
semaphore_down_try(s_semaphore_t *semaphore)
{
    if (SEMAPHORE_ILLEGAL_P(semaphore)) {
        return false;
    } else {
        return semaphore_down_try_i(semaphore);
    }
}

static inline void
semaphore_up_i(s_semaphore_t *semaphore)
{
    dp_thread_id_t id;

    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock(semaphore_lock(semaphore));

    SEMAPHORE_UP(semaphore);

    if (semaphore_val(semaphore) > 0) {
        spin_unlock(semaphore_lock(semaphore));
        return;
    }

    id = (dp_thread_id_t)array_queue_leave(semaphore_sleep_queue(semaphore));

    spin_unlock(semaphore_lock(semaphore));

    dp_thread_signal(id, SIGCONT);
}

void
semaphore_up(s_semaphore_t *semaphore)
{
    if (SEMAPHORE_ILLEGAL_P(semaphore)) {
        return;
    } else {
        semaphore_up_i(semaphore);
    }
}

static inline bool
semaphore_available_ip(s_semaphore_t *semaphore)
{
    bool is_available;

    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock(semaphore_lock(semaphore));

    if (semaphore_val(semaphore) > 0) {
        is_available = true;
    } else {
        is_available = false;
    }

    spin_unlock(semaphore_lock(semaphore));

    return is_available;
}

bool
semaphore_available_p(s_semaphore_t *semaphore)
{
    if (SEMAPHORE_ILLEGAL_P(semaphore)) {
        return false;
    } else {
        return semaphore_available_ip(semaphore);
    }
}

bool
semaphore_unavailable_p(s_semaphore_t *semaphore)
{
    if (SEMAPHORE_ILLEGAL_P(semaphore)) {
        return false;
    } else {
        return !semaphore_available_ip(semaphore);
    }
}

