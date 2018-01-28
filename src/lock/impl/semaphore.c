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
    s_semaphore_t *s;

    assert_exit(val > 0);

    s = memory_cache_allocate(sizeof(*s));

    SEMAPHORE_VAL(s) = val;
    SEMAPHORE_SLEEP_QUEUE(s) = array_queue_create();
    SEMAPHORE_ACT_NEW(s)->sa_flags = SA_NODEFER;
    SEMAPHORE_ACT_NEW(s)->sa_handler = semaphore_sigcont_handler;

    spin_lock_initial(SEMAPHORE_LOCK(s));
    dp_sigaction(SIGCONT, SEMAPHORE_ACT_NEW(s), SEMAPHORE_ACT_OLD(s));

    return s;
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
semaphore_legal_ip(s_semaphore_t *s)
{
    if (complain_null_pointer_p(s)) {
        return false;
    } else if (spin_lock_illegal_p(SEMAPHORE_LOCK(s))) {
        return false;
    } else if (array_queue_structure_illegal_p(SEMAPHORE_SLEEP_QUEUE(s))) {
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
    return semaphore_illegal_ip(semaphore);
}

static inline void
semaphore_destroy_i(s_semaphore_t *s)
{
    assert_exit(semaphore_legal_ip(s));

    dp_sigaction(SIGCONT, SEMAPHORE_ACT_OLD(s), SEMAPHORE_ACT_NEW(s));
    array_queue_destroy(&SEMAPHORE_SLEEP_QUEUE(s));

    memory_cache_free(s);
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

    spin_lock(SEMAPHORE_LOCK(semaphore));

    SEMAPHORE_DOWN(semaphore);

    if (SEMAPHORE_VAL(semaphore) >= 0) {
        spin_unlock(SEMAPHORE_LOCK(semaphore));
        return;
    }

    array_queue_enter(SEMAPHORE_SLEEP_QUEUE(semaphore), (void *)dp_thread_id());

    spin_unlock(SEMAPHORE_LOCK(semaphore));

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

    spin_lock(SEMAPHORE_LOCK(semaphore));

    SEMAPHORE_DOWN(semaphore);

    if (SEMAPHORE_VAL(semaphore) < 0) {
        is_success = false;
        SEMAPHORE_UP(semaphore);
    } else {
        is_success = true;
    }

    spin_unlock(SEMAPHORE_LOCK(semaphore));

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

    spin_lock(SEMAPHORE_LOCK(semaphore));

    SEMAPHORE_UP(semaphore);

    if (SEMAPHORE_VAL(semaphore) > 0) {
        spin_unlock(SEMAPHORE_LOCK(semaphore));
        return;
    }

    id = (dp_thread_id_t)array_queue_leave(SEMAPHORE_SLEEP_QUEUE(semaphore));

    spin_unlock(SEMAPHORE_LOCK(semaphore));

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

    spin_lock(SEMAPHORE_LOCK(semaphore));

    if (SEMAPHORE_VAL(semaphore) > 0) {
        is_available = true;
    } else {
        is_available = false;
    }

    spin_unlock(SEMAPHORE_LOCK(semaphore));

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

