#ifndef HAVE_UNIT_TEST_HASH_H
#define HAVE_UNIT_TEST_HASH_H

#define UT_HASH_create(name)                                      \
static void                                                       \
utest_##name##_hash_create(void)                                  \
{                                                                 \
    bool pass;                                                    \
    uint32 tmp;                                                   \
    struct HASH *hash;                                            \
                                                                  \
    pass = true;                                                  \
                                                                  \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_create(0), &pass);     \
                                                                  \
    tmp = SPT_CHN_HASH_SIZE_DFT;                                  \
    hash = HASH_create(tmp);                                      \
    RESULT_CHECK_uint32(tmp, HASH_size(hash), &pass);             \
    tmp = LOAD_FACTOR;                                            \
    RESULT_CHECK_uint32(tmp, HASH_load_factor_peak(hash), &pass); \
    HASH_destroy(&hash);                                          \
                                                                  \
    tmp = 11u;                                                    \
    hash = HASH_create(tmp);                                      \
    HASH_destroy(&hash);                                          \
                                                                  \
    hash = HASH_create(tmp);                                      \
    RESULT_CHECK_uint32(tmp, HASH_size(hash), &pass);             \
    tmp = LOAD_FACTOR;                                            \
    RESULT_CHECK_uint32(tmp, HASH_load_factor_peak(hash), &pass); \
                                                                  \
    HASH_destroy(&hash);                                          \
    UNIT_TEST_RESULT(name##_hash_create, pass);                   \
}

#define UT_HASH_destroy(name)                    \
static void                                      \
utest_##name##_hash_destroy(void)                \
{                                                \
    bool pass;                                   \
    uint32 tmp;                                  \
    struct HASH *hash;                           \
                                                 \
    pass = true;                                 \
    hash = NULL;                                 \
    HASH_destroy(&hash);                         \
    RESULT_CHECK_pointer(NULL, hash, &pass);     \
                                                 \
    tmp = 0xfu;                                  \
    hash = HASH_create(tmp);                     \
    HASH_destroy(&hash);                         \
    RESULT_CHECK_pointer(NULL, hash, &pass);     \
                                                 \
    tmp = 0xafu;                                 \
    hash = TEST_HASH_sample(tmp);                \
    HASH_destroy(&hash);                         \
                                                 \
    RESULT_CHECK_pointer(NULL, hash, &pass);     \
    UNIT_TEST_RESULT(name##_hash_destroy, pass); \
}

#define UT_HASH_load_factor(name)                                      \
static void                                                            \
utest_##name##_hash_load_factor(void)                                  \
{                                                                      \
    bool pass;                                                         \
    uint32 tmp;                                                        \
    struct HASH *hash;                                                 \
                                                                       \
    tmp = 0x2adeu;                                                     \
    pass = true;                                                       \
                                                                       \
    hash = NULL;                                                       \
    RESULT_CHECK_NOT_LESS_uint32(0x0u, HASH_load_factor(hash), &pass); \
                                                                       \
    hash = TEST_HASH_sample(tmp);                                      \
    tmp = LOAD_FACTOR;                                                 \
    RESULT_CHECK_NOT_LESS_uint32(tmp, HASH_load_factor(hash), &pass);  \
    HASH_destroy(&hash);                                               \
                                                                       \
    tmp = 0x0u;                                                        \
    hash = TEST_HASH_sample(tmp);                                      \
    HASH_load_factor(hash);                                            \
                                                                       \
    HASH_destroy(&hash);                                               \
    UNIT_TEST_RESULT(name##_hash_load_factor, pass);                   \
}

#define UT_HASH_insert(name)                                            \
static void                                                             \
utest_##name##_hash_insert(void)                                        \
{                                                                       \
    bool pass;                                                          \
    uint32 tmp;                                                         \
    struct HASH *hash;                                                  \
                                                                        \
    tmp = 0x2eadu;                                                      \
    pass = true;                                                        \
                                                                        \
    hash = NULL;                                                        \
    HASH_insert(hash, &pass);                                           \
    RESULT_CHECK_pointer(NULL, hash, &pass);                            \
                                                                        \
    hash = TEST_HASH_sample(0x7);                                       \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_insert(hash, NULL), &pass);  \
    HASH_destroy(&hash);                                                \
                                                                        \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_find(hash, &pass), &pass);   \
    hash = TEST_HASH_sample(tmp);                                       \
    HASH_insert(hash, &pass);                                           \
    RESULT_CHECK_pointer(&pass, HASH_find(hash, &pass), &pass);         \
                                                                        \
    HASH_destroy(&hash);                                                \
    UNIT_TEST_RESULT(name##_hash_insert, pass);                         \
}

#define UT_HASH_remove(name)                                           \
static void                                                            \
utest_##name##_hash_remove(void)                                       \
{                                                                      \
    bool pass;                                                         \
    uint32 tmp;                                                        \
    struct HASH *hash;                                                 \
                                                                       \
    tmp = 0x1u;                                                        \
    pass = true;                                                       \
    hash = NULL;                                                       \
                                                                       \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_remove(hash, NULL), &pass); \
                                                                       \
    hash = HASH_create(tmp);                                           \
    HASH_insert(hash, &pass);                                          \
    RESULT_CHECK_pointer(&pass, HASH_find(hash, &pass), &pass);        \
    RESULT_CHECK_pointer(&pass, HASH_remove(hash, &pass), &pass);      \
    HASH_destroy(&hash);                                               \
                                                                       \
    hash = TEST_HASH_sample(0x7);                                      \
    HASH_insert(hash, &pass);                                          \
    HASH_destroy(&hash);                                               \
                                                                       \
    tmp = 0xfu;                                                        \
    hash = TEST_HASH_sample(tmp);                                      \
    HASH_insert(hash, &pass);                                          \
    RESULT_CHECK_pointer(&pass, HASH_find(hash, &pass), &pass);        \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_remove(hash, NULL), &pass); \
                                                                       \
    RESULT_CHECK_pointer(&pass, HASH_remove(hash, &pass), &pass);      \
    RESULT_CHECK_pointer(NULL, HASH_find(hash, &pass), &pass);         \
                                                                       \
    HASH_destroy(&hash);                                               \
    UNIT_TEST_RESULT(name##_hash_remove, pass);                        \
}

#define UT_HASH_find(name)                                            \
static void                                                           \
utest_##name##_hash_find(void)                                        \
{                                                                     \
    bool pass;                                                        \
    uint32 tmp;                                                       \
    struct HASH *hash;                                                \
                                                                      \
    pass = true;                                                      \
    hash = NULL;                                                      \
                                                                      \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_find(hash, &pass), &pass); \
    RESULT_CHECK_pointer(PTR_INVALID, HASH_find(hash, NULL), &pass);  \
                                                                      \
    tmp = 0x1u;                                                       \
    hash = HASH_create(tmp);                                          \
    RESULT_CHECK_pointer(NULL, HASH_find(hash, &pass), &pass);        \
    HASH_destroy(&hash);                                              \
                                                                      \
    tmp = 0x1debu;                                                    \
    hash = TEST_HASH_sample(tmp);                                     \
    RESULT_CHECK_pointer(NULL, HASH_find(hash, &pass), &pass);        \
    HASH_insert(hash, &pass);                                         \
                                                                      \
    RESULT_CHECK_pointer(&pass, HASH_find(hash, &pass), &pass);       \
                                                                      \
    HASH_destroy(&hash);                                              \
    UNIT_TEST_RESULT(name##_hash_find, pass);                         \
}

#define UT_HASH_rehashing(name)                            \
static void                                                \
utest_##name##_hash_rehashing(void)                        \
{                                                          \
    bool pass;                                             \
    uint32 tmp;                                            \
    struct HASH *hash;                                     \
                                                           \
    tmp = 0x1u;                                            \
    pass = true;                                           \
                                                           \
    hash = TEST_HASH_sample(tmp);                          \
    tmp = HASH_size(hash);                                 \
    HASH_rehashing(hash);                                  \
    RESULT_CHECK_LESS_uint32(tmp, HASH_size(hash), &pass); \
                                                           \
    tmp = prime_numeral_next(tmp + 1);                     \
    RESULT_CHECK_uint32(tmp, HASH_size(hash), &pass);      \
                                                           \
    HASH_destroy(&hash);                                   \
    UNIT_TEST_RESULT(name##_hash_rehashing, pass);         \
}

#endif

