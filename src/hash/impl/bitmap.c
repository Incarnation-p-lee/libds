s_bitmap_t *
bitmap_create(native_wide_t min, native_wide_t max)
{
    s_bitmap_t *bitmap;
    uint32 bytes_count;

    if (min > max) {
        return PTR_INVALID;
    } else {
        bitmap = memory_cache_allocate(sizeof(*bitmap));
        bitmap->max = max;
        bitmap->min = min;

        bytes_count = (bitmap->max - bitmap->min + 1) / 8;
        bytes_count = bitmap_native_align(bytes_count);

        bitmap->map = memory_cache_allocate(bytes_count);
        dp_memset(bitmap->map, 0, bytes_count);

        return bitmap;
    }
}

bool
bitmap_structure_legal_p(s_bitmap_t *bitmap)
{
    return bitmap_structure_legal_ip(bitmap);
}

bool
bitmap_structure_illegal_p(s_bitmap_t *bitmap)
{
    return bitmap_structure_illegal_ip(bitmap);
}

static inline bool
bitmap_structure_illegal_ip(s_bitmap_t *bitmap)
{
    return !bitmap_structure_legal_ip(bitmap);
}

static inline bool
bitmap_structure_legal_ip(s_bitmap_t *bitmap)
{
    if (NULL_PTR_P(bitmap)) {
        return false;
    } else if (PTR_INVALID == bitmap) {
        return false;
    } else if (NULL_PTR_P(bitmap->map)) {
        return false;
    } else {
        return true;
    }
}

void
bitmap_destroy(s_bitmap_t **bitmap)
{
    if (NULL_PTR_P(bitmap)) {
        return;
    } else if (bitmap_structure_legal_ip(*bitmap)) {
        memory_cache_free((*bitmap)->map);
        memory_cache_free((*bitmap));

        *bitmap = NULL;
    }
}

static inline native_wide_t
bitmap_map_index(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t index;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->min && val <= bitmap->max);

    index = (val - bitmap->min) / BITMAP_NATIVE_BITS;

    return index;
}

static inline native_wide_t
bitmap_map_reminder(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->min && val <= bitmap->max);

    reminder = (val - bitmap->min) % BITMAP_NATIVE_BITS;

    return reminder;
}

static inline uint32
bitmap_native_align(uint32 bytes_count)
{
    uint32 bytes_padding;
    uint32 bytes_count_aligned;

    bytes_padding = BITMAP_NATIVE_BYTES - bytes_count % BITMAP_NATIVE_BYTES;
    bytes_count_aligned = bytes_count + bytes_padding;

    return bytes_count_aligned;
}

static inline uint32
bitmap_native_bytes_count(s_bitmap_t *bitmap)
{
    uint32 bytes_count;

    assert_exit(bitmap_structure_legal_ip(bitmap));

    bytes_count = (bitmap->max - bitmap->min + 1) / 8;
    bytes_count = bitmap_native_align(bytes_count);

    return bytes_count;
}

static inline void
bitmap_map_expand(s_bitmap_t *bitmap, native_wide_t val)
{
    uint32 bytes_count;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val > bitmap->max);

    bytes_count = (val - bitmap->min) / 8;
    bytes_count = bitmap_native_align(bytes_count);

    bitmap->max = val;
    bitmap->map = memory_cache_re_allocate(bitmap->map, bytes_count);
}

static inline void
bitmap_bit_clear_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->min);
    assert_exit(val <= bitmap->max);

    index = bitmap_map_index(bitmap, val);
    reminder = bitmap_map_reminder(bitmap, val);

    bitmap->map[index] &= (BITMAP_ALL ^ (BITMAP_SET << reminder));
}

static inline void
bitmap_bit_set_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->min);

    if (val > bitmap->max) {
        bitmap_map_expand(bitmap, val);
    }

    index = bitmap_map_index(bitmap, val);
    reminder = bitmap_map_reminder(bitmap, val);

    bitmap->map[index] |= (BITMAP_SET << reminder);
}

static inline native_wide_t
bitmap_bit_get_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t bit;
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->min);
    assert_exit(val <= bitmap->max);

    index = bitmap_map_index(bitmap, val);
    reminder = bitmap_map_reminder(bitmap, val);

    bit = (bitmap->map[index] >> reminder) & BITMAP_SET;

    return bit;
}

native_wide_t
bitmap_bit_get(s_bitmap_t *bitmap, native_wide_t val)
{
    if (bitmap_structure_illegal_ip(bitmap)) {
        return BITMAP_INVALID;
    } else if (val > bitmap->max) {
        return BITMAP_INVALID;
    } else if (val < bitmap->min) {
        return BITMAP_INVALID;
    } else {
        return bitmap_bit_get_i(bitmap, val);
    }
}

void
bitmap_bit_clear(s_bitmap_t *bitmap, native_wide_t val)
{
    if (bitmap_structure_illegal_ip(bitmap)) {
        return;
    } else if (val > bitmap->max) {
        return;
    } else if (val < bitmap->min) {
        return;
    } else {
        bitmap_bit_clear_i(bitmap, val);
    }
}

void
bitmap_bit_set(s_bitmap_t *bitmap, native_wide_t val)
{
    if (bitmap_structure_illegal_ip(bitmap)) {
        return;
    } else if (val < bitmap->min) {
        return;
    } else {
        bitmap_bit_set_i(bitmap, val);
    }
}

void
bitmap_map_cleanup(s_bitmap_t *bitmap)
{
    uint32 bytes_count;

    if (bitmap_structure_legal_ip(bitmap)) {
        bytes_count = bitmap_native_bytes_count(bitmap);
        dp_memset(bitmap->map, 0, bytes_count);
    }
}

