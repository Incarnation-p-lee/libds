static void
unit_test_open_addressing_hash_struct_field(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    tmp = 0x3u;
    pass = true;

    hash = open_addressing_hash_create(tmp);
    RESULT_CHECK_uint32(tmp, open_addressing_hash_size(hash), &pass);

    tmp = 100u;
    open_addressing_hash_load_factor_set(hash, tmp);
    RESULT_CHECK_uint32(tmp, open_addressing_hash_load_factor(hash), &pass);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_struct_field), pass);
}

static void
unit_test_open_addressing_hash_create(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    tmp = 0;
    pass = true;

    hash = open_addressing_hash_create(tmp);
    tmp = DEFAULT_CHAIN_HASH_SIZE;
    RESULT_CHECK_uint32(tmp, open_addressing_hash_size(hash), &pass);
    tmp = OPEN_ADDRESSING_HASH_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, open_addressing_hash_load_factor(hash), &pass);
    open_addressing_hash_destroy(&hash);

    tmp = 11u;
    hash = open_addressing_hash_create(tmp);
    open_addressing_hash_destroy(&hash);

    hash = open_addressing_hash_create(tmp);
    RESULT_CHECK_uint32(tmp, open_addressing_hash_size(hash), &pass);
    tmp = OPEN_ADDRESSING_HASH_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, open_addressing_hash_load_factor(hash), &pass);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_create), pass);
}

static void
unit_test_open_addressing_hash_destroy(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    pass = true;
    hash = NULL;
    open_addressing_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    tmp = 0xfu;
    hash = open_addressing_hash_create(tmp);
    open_addressing_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    tmp = 0xafu;
    hash = test_open_addressing_hash_sample(tmp);
    open_addressing_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    unit_test_result_print(SYM_2_STR(open_addressing_hash_destroy), pass);
}

static void
unit_test_open_addressing_hash_load_factor_calculate(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    tmp = 0xbedu;
    pass = true;

    hash = NULL;
    RESULT_CHECK_NOT_LESS_uint32(0x0u,
        open_addressing_hash_load_factor_calculate(hash), &pass);

    hash = test_open_addressing_hash_sample(tmp);
    tmp = OPEN_ADDRESSING_HASH_LOAD_FACTOR;
    RESULT_CHECK_NOT_LESS_uint32(tmp,
        open_addressing_hash_load_factor_calculate(hash), &pass);
    open_addressing_hash_destroy(&hash);

    tmp = 0x0u;
    hash = test_open_addressing_hash_sample(tmp);
    open_addressing_hash_load_factor_calculate(hash);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_load_factor_calculate), pass);
}

static void
unit_test_open_addressing_hash_insert(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    tmp = 0x29u;
    pass = true;

    hash = NULL;
    open_addressing_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    hash = test_open_addressing_hash_sample(0x7);
    open_addressing_hash_destroy(&hash);

    RESULT_CHECK_pointer(NULL, open_addressing_hash_find(hash, &pass), &pass);
    hash = test_open_addressing_hash_sample(tmp);
    open_addressing_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, open_addressing_hash_find(hash, &pass), &pass);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_insert), pass);
}

static void
unit_test_open_addressing_hash_remove(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    tmp = 0x0u;
    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, open_addressing_hash_remove(hash, NULL), &pass);

    hash = open_addressing_hash_create(tmp);
    open_addressing_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, open_addressing_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(&pass, open_addressing_hash_remove(hash, &pass), &pass);
    open_addressing_hash_destroy(&hash);

    hash = test_open_addressing_hash_sample(0x7);
    open_addressing_hash_insert(&hash, &pass);
    open_addressing_hash_destroy(&hash);

    tmp = 0x32u;
    hash = test_open_addressing_hash_sample(tmp);
    open_addressing_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, open_addressing_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, open_addressing_hash_remove(hash, NULL), &pass);

    RESULT_CHECK_pointer(&pass, open_addressing_hash_remove(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, open_addressing_hash_find(hash, &pass), &pass);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_remove), pass);
}

static void
unit_test_open_addressing_hash_find(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;

    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, open_addressing_hash_find(hash, &pass), &pass);

    tmp = 0x0u;
    hash = open_addressing_hash_create(tmp);
    RESULT_CHECK_pointer(NULL, open_addressing_hash_find(hash, &pass), &pass);
    open_addressing_hash_destroy(&hash);

    tmp = 0xebu;
    hash = test_open_addressing_hash_sample(tmp);
    RESULT_CHECK_pointer(NULL, open_addressing_hash_find(hash, &pass), &pass);
    open_addressing_hash_insert(&hash, &pass);

    RESULT_CHECK_pointer(&pass, open_addressing_hash_find(hash, &pass), &pass);

    open_addressing_hash_destroy(&hash);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_find), pass);
}

static void
unit_test_open_addressing_hash_rehashing(void)
{
    bool pass;
    uint32 tmp;
    struct open_addressing_hash *hash;
    struct open_addressing_hash *new;

    tmp = 0x0u;
    pass = true;

    hash = NULL;
    RESULT_CHECK_pointer(NULL, open_addressing_hash_rehashing(&hash), &pass);

    hash = test_open_addressing_hash_sample(tmp);
    tmp = open_addressing_hash_size(hash);
    new = open_addressing_hash_rehashing(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);
    RESULT_CHECK_uint32(prime_numeral_next(tmp),
        open_addressing_hash_size(new), &pass);

    hash = open_addressing_hash_rehashing(&new);
    RESULT_CHECK_pointer(NULL, new, &pass);
    new = open_addressing_hash_rehashing(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    open_addressing_hash_destroy(&new);
    unit_test_result_print(SYM_2_STR(open_addressing_hash_rehashing), pass);
}

