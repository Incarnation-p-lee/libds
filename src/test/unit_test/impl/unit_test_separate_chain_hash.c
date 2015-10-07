static void
unit_test_separate_chain_hash_struct_field(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    tmp = 0x3u;
    pass = true;

    hash = separate_chain_hash_create(tmp);
    RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);

    tmp = 100u;
    separate_chain_hash_load_factor_set(hash, tmp);
    RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_struct_field), pass);
}

static void
unit_test_separate_chain_hash_create(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    tmp = 0;
    pass = true;

    hash = separate_chain_hash_create(tmp);
    tmp = DEFAULT_CHAIN_HASH_SIZE;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);
    tmp = DEFAULT_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 11u;
    hash = separate_chain_hash_create(tmp);
    separate_chain_hash_destroy(&hash);

    hash = separate_chain_hash_create(tmp);
    RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);
    tmp = DEFAULT_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_create), pass);
}

static void
unit_test_separate_chain_hash_destroy(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    pass = true;
    hash = NULL;
    separate_chain_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    tmp = 0xfu;
    hash = separate_chain_hash_create(tmp);
    separate_chain_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    tmp = 0xafu;
    hash = test_separate_chain_hash_sample(tmp);
    separate_chain_hash_destroy(&hash);

    RESULT_CHECK_pointer(NULL, hash, &pass);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_destroy), pass);
}

static void
unit_test_separate_chain_hash_load_factor_calculate(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    tmp = 0xfadeu;
    pass = true;

    hash = NULL;
    RESULT_CHECK_NOT_LESS_uint32(0x0u,
        separate_chain_hash_load_factor_calculate(hash), &pass);

    hash = test_separate_chain_hash_sample(tmp);
    tmp = DEFAULT_LOAD_FACTOR;
    RESULT_CHECK_NOT_LESS_uint32(tmp,
        separate_chain_hash_load_factor_calculate(hash), &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 0x0u;
    hash = test_separate_chain_hash_sample(tmp);
    separate_chain_hash_load_factor_calculate(hash);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_load_factor_calculate), pass);
}

static void
unit_test_separate_chain_hash_insert(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    tmp = 0xdeadu;
    pass = true;

    hash = NULL;
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    hash = test_separate_chain_hash_sample(0x7);
    separate_chain_hash_destroy(&hash);

    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    hash = test_separate_chain_hash_sample(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_insert), pass);
}

static void
unit_test_separate_chain_hash_remove(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    tmp = 0x0u;
    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, separate_chain_hash_remove(hash, NULL), &pass);

    hash = separate_chain_hash_create(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_remove(hash, &pass), &pass);
    separate_chain_hash_destroy(&hash);

    hash = test_separate_chain_hash_sample(0x7);
    separate_chain_hash_insert(&hash, &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 0xfu;
    hash = test_separate_chain_hash_sample(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_remove(hash, NULL), &pass);

    RESULT_CHECK_pointer(&pass, separate_chain_hash_remove(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_remove), pass);
}

static void
unit_test_separate_chain_hash_find(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;

    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);

    tmp = 0x0u;
    hash = separate_chain_hash_create(tmp);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 0xfadebu;
    hash = test_separate_chain_hash_sample(tmp);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    separate_chain_hash_insert(&hash, &pass);

    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);

    separate_chain_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_find), pass);
}

static void
unit_test_separate_chain_hash_rehashing(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    struct separate_chain_hash *new;

    tmp = 0x0u;
    pass = true;

    hash = NULL;
    RESULT_CHECK_pointer(NULL, separate_chain_hash_rehashing(&hash), &pass);

    hash = test_separate_chain_hash_sample(tmp);
    tmp = separate_chain_hash_size(hash);
    new = separate_chain_hash_rehashing(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);
    RESULT_CHECK_uint32(prime_numeral_next(tmp),
        separate_chain_hash_size(new), &pass);

    hash = separate_chain_hash_rehashing(&new);
    RESULT_CHECK_pointer(NULL, new, &pass);
    new = separate_chain_hash_rehashing(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    separate_chain_hash_destroy(&new);
    unit_test_result_print(SYM_2_STR(separate_chain_hash_rehashing), pass);
}

