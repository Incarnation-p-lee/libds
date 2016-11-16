static inline void
utest_bitmap_create(void)
{
    bool pass;
    native_wide_t min;
    native_wide_t max;
    s_bitmap_t *bitmap;

    min = 1;
    max = 0x12f2;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_create);

    bitmap = bitmap_create(max, min);
    RESULT_CHECK_pointer(PTR_INVALID, bitmap, &pass);
    RESULT_CHECK_bool(true, bitmap_structure_illegal_p(bitmap), &pass);

    bitmap = bitmap_create(min, max);
    RESULT_CHECK_bool(true, bitmap_structure_legal_p(bitmap), &pass);
    RESULT_CHECK_native_wide(min, bitmap->min, &pass);
    RESULT_CHECK_native_wide(max, bitmap->max, &pass);

    bitmap_destroy(&bitmap);
    UNIT_TEST_RESULT(bitmap_create, pass);
}

static inline void
utest_bitmap_destroy(void)
{
    bool pass;
    native_wide_t min;
    native_wide_t max;
    s_bitmap_t *bitmap;

    min = 1;
    max = 0x12f2;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_destroy);

    bitmap = NULL;
    bitmap_destroy(&bitmap);
    RESULT_CHECK_pointer(NULL, bitmap, &pass);

    bitmap = bitmap_create(min, max);
    bitmap_destroy(&bitmap);
    RESULT_CHECK_pointer(NULL, bitmap, &pass);

    UNIT_TEST_RESULT(bitmap_destroy, pass);
}

static inline void
utest_bitmap_bit_get(void)
{
    bool pass;
    s_bitmap_t *bitmap;
    native_wide_t min, max, val;

    min = 0x32d;
    max = 0x83d1;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_bit_get);

    RESULT_CHECK_native_wide(BITMAP_INVALID, bitmap_bit_get(NULL, min), &pass);
    RESULT_CHECK_native_wide(BITMAP_INVALID, bitmap_bit_get(NULL, min - 1), &pass);
    RESULT_CHECK_native_wide(BITMAP_INVALID, bitmap_bit_get(NULL, min + 1), &pass);

    bitmap = bitmap_create(min, max);

    val = min + 1;
    RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);
    val = max - 1;
    RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);

    val = max;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);

    val = min;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);

    bitmap_destroy(&bitmap);
    UNIT_TEST_RESULT(bitmap_bit_get, pass);
}

static inline void
utest_bitmap_bit_set(void)
{
    bool pass;
    s_bitmap_t *bitmap;
    native_wide_t min, max, val;

    min = 0x132d;
    max = 0xa3d1;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_bit_set);

    bitmap_bit_set(NULL, min);
    bitmap_bit_set(NULL, min - 1);

    bitmap = bitmap_create(min, max);

    val = min;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);

    val = max;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);

    val = max + min;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);

    bitmap_destroy(&bitmap);
    UNIT_TEST_RESULT(bitmap_bit_set, pass);
}

static inline void
utest_bitmap_bit_clear(void)
{
    bool pass;
    s_bitmap_t *bitmap;
    native_wide_t min, max, val;

    min = 0x132d;
    max = 0xa3d1;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_bit_clear);

    bitmap_bit_set(NULL, min);
    bitmap_bit_set(NULL, min - 1);

    bitmap = bitmap_create(min, max);

    val = min;
    bitmap_bit_clear(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);

    val = max;
    bitmap_bit_clear(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);

    val = (min + max) / 2;
    bitmap_bit_set(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_SET, bitmap_bit_get(bitmap, val), &pass);
    bitmap_bit_clear(bitmap, val);
    RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);

    bitmap_destroy(&bitmap);
    UNIT_TEST_RESULT(bitmap_bit_clear, pass);
}

static inline void
utest_bitmap_map_cleanup(void)
{
    bool pass;
    s_bitmap_t *bitmap;
    native_wide_t min, max, val;

    min = 0x732d;
    max = 0xf3d1;
    pass = true;
    UNIT_TEST_BEGIN(bitmap_map_cleanup);

    bitmap_map_cleanup(NULL);

    bitmap = bitmap_create(min, max);

    bitmap_bit_set(bitmap, min);
    bitmap_bit_set(bitmap, max);
    bitmap_bit_set(bitmap, (min + max) / 2);

    bitmap_map_cleanup(bitmap);

    val = bitmap->min;
    while (val <= bitmap->max) {
        RESULT_CHECK_native_wide(BITMAP_CLR, bitmap_bit_get(bitmap, val), &pass);
        val++;
    }

    bitmap_destroy(&bitmap);
    UNIT_TEST_RESULT(bitmap_map_cleanup, pass);
}

