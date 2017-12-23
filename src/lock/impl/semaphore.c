static inline s_spin_lock_t *
semaphore_spin_lock(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    return semaphore->spin_lock;
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

s_semaphore_t *
semaphore_create(uint32 val)
{
    s_semaphore_t *semaphore;

    semaphore = memory_cache_allocate(sizeof(*semaphore));

    semaphore->val = val;
    semaphore->spin_lock = spin_lock_create();
    semaphore->sleep_queue = array_queue_create();

    return semaphore;
}

static inline bool
semaphore_legal_ip(s_semaphore_t *semaphore)
{
    if (complain_null_pointer_p(semaphore)) {
        return false;
    } else if (spin_lock_illegal_p(semaphore->spin_lock)) {
        return false;
    } else if (array_queue_structure_illegal_p(semaphore->sleep_queue)) {
        return false;
    } else {
        return false;
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
    return !semaphore_legal_ip(semaphore);
}

bool
semaphore_illegal_p(s_semaphore_t *semaphore)
{
    return !semaphore_illegal_ip(semaphore);
}

static inline void
semaphore_destroy_i(s_semaphore_t *semaphore)
{
    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock_destroy(&semaphore->spin_lock);
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
    dp_thread_id_t id;

    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock_try(semaphore_spin_lock(semaphore));

    SEMAPHORE_DOWN(semaphore);

    if (semaphore_val(semaphore) >= 0) {
        spin_lock_release(semaphore_spin_lock(semaphore));
        return;
    }

    id = dp_thread_id();
    array_queue_enter(semaphore_sleep_queue(semaphore), (void *)id);

    spin_lock_release(semaphore_spin_lock(semaphore));
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

static inline void
semaphore_up_i(s_semaphore_t *semaphore)
{
    dp_thread_id_t id;

    assert_exit(semaphore_legal_ip(semaphore));

    spin_lock_try(semaphore_spin_lock(semaphore));

    SEMAPHORE_UP(semaphore);

    if (semaphore_val(semaphore) > 0) {
        spin_lock_release(semaphore_spin_lock(semaphore));
        return;
    }

    id = (dp_thread_id_t)array_queue_leave(semaphore_sleep_queue(semaphore));

    spin_lock_release(semaphore_spin_lock(semaphore));
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

