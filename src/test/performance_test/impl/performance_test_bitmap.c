static inline void
ptest_bitmap_create(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap = bitmap_create(min, max);
        bitmap_destroy(&bitmap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(bitmap_create);
}

static inline void
ptest_bitmap_destroy(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap = bitmap_create(min, max);
        bitmap_destroy(&bitmap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(bitmap_destroy);
}

static inline void
ptest_bitmap_bit_get(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_bit_get);

    bitmap = bitmap_create(min, max);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap_bit_get(bitmap, min);
        bitmap_bit_get(bitmap, max);
    }

    PERFORMANCE_TEST_ENDPOINT;

    bitmap_destroy(&bitmap);
    PERFORMANCE_TEST_RESULT(bitmap_bit_get);
}

static inline void
ptest_bitmap_bit_set(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_bit_set);

    bitmap = bitmap_create(min, max);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap_bit_set(bitmap, min);
        bitmap_bit_set(bitmap, max);
    }

    PERFORMANCE_TEST_ENDPOINT;

    bitmap_destroy(&bitmap);
    PERFORMANCE_TEST_RESULT(bitmap_bit_set);
}

static inline void
ptest_bitmap_bit_clear(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_bit_clear);

    bitmap = bitmap_create(min, max);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap_bit_clear(bitmap, min);
        bitmap_bit_clear(bitmap, max);
    }

    PERFORMANCE_TEST_ENDPOINT;

    bitmap_destroy(&bitmap);
    PERFORMANCE_TEST_RESULT(bitmap_bit_clear);
}

static inline void
ptest_bitmap_map_cleanup(uint32 count)
{
    s_bitmap_t *bitmap;
    native_wide_t min, max;

    min = 0xda1;
    max = 0xdeac;

    PERFORMANCE_TEST_BEGIN(bitmap_map_cleanup);

    bitmap = bitmap_create(min, max);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        bitmap_map_cleanup(bitmap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    bitmap_destroy(&bitmap);
    PERFORMANCE_TEST_RESULT(bitmap_map_cleanup);
}

