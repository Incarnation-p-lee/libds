#ifndef HAVE_DEFINED_PERFORMANCE_TEST_HASH_H
#define HAVE_DEFINED_PERFORMANCE_TEST_HASH_H

#define PT_HASH_create(name)                     \
static inline void                               \
ptest_##name##_hash_create(uint32 count)         \
{                                                \
    struct HASH *hash;                           \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        hash = HASH_create(0x231);               \
        HASH_destroy(&hash);                     \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    PERFORMANCE_TEST_RESULT(name##_hash_create); \
}

#define PT_HASH_destroy(name)                     \
static inline void                                \
ptest_##name##_hash_destroy(uint32 count)         \
{                                                 \
    struct HASH *hash;                            \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        hash = HASH_create(0xd);                  \
        HASH_destroy(&hash);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_hash_destroy); \
}

#define PT_HASH_load_factor_calculate(name)                     \
static inline void                                              \
ptest_##name##_hash_load_factor_calculate(uint32 count)         \
{                                                               \
    struct HASH *hash;                                          \
                                                                \
    hash = TEST_HASH_sample(0x18f);                             \
                                                                \
    PERFORMANCE_TEST_CHECKPOINT;                                \
                                                                \
    while (count--) {                                           \
        HASH_load_factor_calculate(hash);                       \
    }                                                           \
                                                                \
    PERFORMANCE_TEST_ENDPOINT;                                  \
                                                                \
    HASH_destroy(&hash);                                        \
    PERFORMANCE_TEST_RESULT(name##_hash_load_factor_calculate); \
}

#define PT_HASH_insert(name)                     \
static inline void                               \
ptest_##name##_hash_insert(uint32 count)         \
{                                                \
    struct HASH *hash;                           \
                                                 \
    count = count >> 5;                          \
    count = 0 == count ? 1000 : count;           \
    hash = HASH_create(count * 3 + 1);           \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        HASH_insert(hash, &count + count);       \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    HASH_destroy(&hash);                         \
    PERFORMANCE_TEST_RESULT(name##_hash_insert); \
}

#define PT_HASH_remove(name)                     \
static inline void                               \
ptest_##name##_hash_remove(uint32 count)         \
{                                                \
    uint32 tmp;                                  \
    struct HASH *hash;                           \
                                                 \
    count = count >> 5;                          \
    count = 0 == count ? 1000 : count;           \
    tmp = count;                                 \
                                                 \
    hash = HASH_create(count * 3 + 1);           \
                                                 \
    while (count--) {                            \
        HASH_insert(hash, &count + count);       \
    }                                            \
                                                 \
    count = tmp;                                 \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        HASH_remove(hash, &count + count);       \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    HASH_destroy(&hash);                         \
    PERFORMANCE_TEST_RESULT(name##_hash_remove); \
}

#define PT_HASH_find(name)                     \
static inline void                             \
ptest_##name##_hash_find(uint32 count)         \
{                                              \
    uint32 tmp;                                \
    struct HASH *hash;                         \
                                               \
    count = count >> 5;                        \
    count = 0 == count ? 1000 : count;         \
    tmp = count;                               \
                                               \
    hash = HASH_create(count * 3 + 1);         \
                                               \
    while (count--) {                          \
        HASH_insert(hash, &count + count);     \
    }                                          \
                                               \
    count = tmp;                               \
                                               \
    PERFORMANCE_TEST_CHECKPOINT;               \
                                               \
    while (count--) {                          \
        HASH_find(hash, &count + count);       \
    }                                          \
                                               \
    PERFORMANCE_TEST_ENDPOINT;                 \
                                               \
    HASH_destroy(&hash);                       \
    PERFORMANCE_TEST_RESULT(name##_hash_find); \
}

#define PT_HASH_rehashing(name)                     \
static inline void                                  \
ptest_##name##_hash_rehashing(uint32 count)         \
{                                                   \
    struct HASH *hash;                              \
                                                    \
    count = count >> 13;                            \
    count = 0 == count ? 100 : count;               \
                                                    \
    hash = TEST_HASH_sample(0x1);                   \
                                                    \
    PERFORMANCE_TEST_CHECKPOINT;                    \
                                                    \
    while (count--) {                               \
        HASH_rehashing(hash);                       \
    }                                               \
                                                    \
    PERFORMANCE_TEST_ENDPOINT;                      \
                                                    \
    HASH_destroy(&hash);                            \
    PERFORMANCE_TEST_RESULT(name##_hash_rehashing); \
}

#endif

