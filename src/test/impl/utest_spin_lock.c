static inline void
utest_spin_lock_create(void)
{
    bool pass;
    s_spin_lock_t *spin_lock;

    UNIT_TEST_BEGIN(spin_lock_create);

    pass = true;
    spin_lock = spin_lock_create();

    RESULT_CHECK_bool(true, spin_lock_legal_p(spin_lock), &pass);
    RESULT_CHECK_bool(false, spin_lock_locked_p(spin_lock), &pass);

    spin_lock_destroy(&spin_lock);

    UNIT_TEST_RESULT(spin_lock_create, pass);
}

