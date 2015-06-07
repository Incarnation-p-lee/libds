static void
unit_test_separate_chain_hash_struct_field(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xa23456;
    tmp = 0x3u;
    pass = true;

    while (0 != loop--) {
        hash = separate_chain_hash_create(tmp);
        RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);

        tmp = 100u;
        separate_chain_hash_load_factor_set(hash, tmp);
        RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);
        separate_chain_hash_destroy(&hash);
    }

    test_result_print(SYM_2_STR(separate_chain_hash_struct_field), pass);
    return;
}

static inline struct separate_chain_hash *
unit_test_separate_chain_hash_sample(uint32 count)
{
    struct separate_chain_hash *hash;
    struct memory_maps *heap;
    uint64 iter;
    uint64 limit;

    hash = separate_chain_hash_create(0x11u);
    heap = memory_maps_entry_find("[heap]");

    assert(NULL != hash);
    assert(NULL != heap);

    iter = (uint64)heap->begin;
    limit = (uint64)heap->end;
    while (0 != count-- && iter < limit) {
        separate_chain_hash_insert(&hash, (void *)iter);
        iter += 4;
    }

    return hash;
}

static void
unit_test_separate_chain_hash_create(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x2234567;
    tmp = 0;
    pass = true;

    hash = separate_chain_hash_create(tmp);
    tmp = DEFAULT_CHAIN_HASH_SIZE;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);
    tmp = DEFAULT_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 11u;
    while (0 != loop--) {
        hash = separate_chain_hash_create(tmp);
        separate_chain_hash_destroy(&hash);
    }

    hash = separate_chain_hash_create(tmp);
    RESULT_CHECK_uint32(tmp, separate_chain_hash_size(hash), &pass);
    tmp = DEFAULT_LOAD_FACTOR;
    RESULT_CHECK_uint32(tmp, separate_chain_hash_load_factor(hash), &pass);
    separate_chain_hash_destroy(&hash);

    test_result_print(SYM_2_STR(separate_chain_hash_create), pass);
    return;
}

static void
unit_test_separate_chain_hash_destroy(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x2234567;
    pass = true;
    hash = NULL;
    separate_chain_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    while (0 != loop--) {
        tmp = 0xfu;
        hash = separate_chain_hash_create(tmp);
        separate_chain_hash_destroy(&hash);
        RESULT_CHECK_pointer(NULL, hash, &pass);
    }

    tmp = 0xafu;
    hash = unit_test_separate_chain_hash_sample(tmp);
    separate_chain_hash_destroy(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    test_result_print(SYM_2_STR(separate_chain_hash_destroy), pass);
    return;
}

static void
unit_test_separate_chain_hash_load_factor_calculate(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x2234567;
    tmp = 0xfadeu;
    pass = true;

    hash = NULL;
    RESULT_CHECK_NOT_LESS_uint32(0x0u,
        separate_chain_hash_load_factor_calculate(hash), &pass);

    hash = unit_test_separate_chain_hash_sample(tmp);
    tmp = DEFAULT_LOAD_FACTOR;
    while (0 != loop--) {
        RESULT_CHECK_NOT_LESS_uint32(tmp,
            separate_chain_hash_load_factor_calculate(hash), &pass);
    }
    separate_chain_hash_destroy(&hash);

    tmp = 0x0u;
    hash = unit_test_separate_chain_hash_sample(tmp);
    free_ds(hash->space);
    hash->space = NULL;
    separate_chain_hash_load_factor_calculate(hash);
    separate_chain_hash_destroy(&hash);

    test_result_print(SYM_2_STR(separate_chain_hash_load_factor_calculate), pass);

    return;
}

static void
unit_test_separate_chain_hash_insert(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x623456;
    tmp = 0xdeadu;
    pass = true;

    hash = NULL;
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(NULL, hash, &pass);

    while (0 != loop--) {
        hash = unit_test_separate_chain_hash_sample(0x7);
        separate_chain_hash_destroy(&hash);
    }

    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    hash = unit_test_separate_chain_hash_sample(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);

    separate_chain_hash_destroy(&hash);
    test_result_print(SYM_2_STR(separate_chain_hash_insert), pass);

    return;
}

static void
unit_test_separate_chain_hash_remove(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x623456;
    tmp = 0x0u;
    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, separate_chain_hash_remove(hash, NULL), &pass);

    hash = separate_chain_hash_create(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_remove(hash, &pass), &pass);
    separate_chain_hash_destroy(&hash);

    while (0 != loop--) {
        hash = unit_test_separate_chain_hash_sample(0x7);
        separate_chain_hash_insert(&hash, &pass);
        separate_chain_hash_destroy(&hash);
    }

    tmp = 0xfadeu;
    hash = unit_test_separate_chain_hash_sample(tmp);
    separate_chain_hash_insert(&hash, &pass);
    RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_remove(hash, NULL), &pass);

    RESULT_CHECK_pointer(&pass, separate_chain_hash_remove(hash, &pass), &pass);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);

    separate_chain_hash_destroy(&hash);
    test_result_print(SYM_2_STR(separate_chain_hash_remove), pass);

    return;
}

static void
unit_test_separate_chain_hash_find(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x7234567;
    pass = true;
    hash = NULL;

    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);

    tmp = 0x0u;
    hash = separate_chain_hash_create(tmp);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    separate_chain_hash_destroy(&hash);

    tmp = 0xfadebu;
    hash = unit_test_separate_chain_hash_sample(tmp);
    RESULT_CHECK_pointer(NULL, separate_chain_hash_find(hash, &pass), &pass);
    separate_chain_hash_insert(&hash, &pass);

    while (0 != loop--) {
        RESULT_CHECK_pointer(&pass, separate_chain_hash_find(hash, &pass), &pass);
    }

    separate_chain_hash_destroy(&hash);
    test_result_print(SYM_2_STR(separate_chain_hash_find), pass);

    return;
}

static void
unit_test_separate_chain_hash_rehashing(void)
{
    bool pass;
    uint32 tmp;
    struct separate_chain_hash *hash;
    struct separate_chain_hash *new;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x52;
    tmp = 0x0u;
    pass = true;

    hash = NULL;
    RESULT_CHECK_pointer(NULL, separate_chain_hash_rehashing(&hash), &pass);

    hash = unit_test_separate_chain_hash_sample(tmp);
    tmp = separate_chain_hash_size(hash);
    new = separate_chain_hash_rehashing(&hash);
    RESULT_CHECK_pointer(NULL, hash, &pass);
    RESULT_CHECK_uint32(prime_numeral_next(tmp),
        separate_chain_hash_size(new), &pass);

    while (0 != loop--) {
        hash = separate_chain_hash_rehashing(&new);
        RESULT_CHECK_pointer(NULL, new, &pass);
        new = separate_chain_hash_rehashing(&hash);
        RESULT_CHECK_pointer(NULL, hash, &pass);
    }
    separate_chain_hash_destroy(&new);

    test_result_print(SYM_2_STR(separate_chain_hash_rehashing), pass);
    return;
}
