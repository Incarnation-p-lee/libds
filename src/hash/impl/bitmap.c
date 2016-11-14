s_bitmap_t *
bitmap_create(native_wide_t min, native_wide_t max)
{
    uint32 bytes_count;
    s_bitmap_t *bitmap;
    native_wide_t bit_size;

    if (min >= max) {
        return PTR_INVALID;
    } else {
        bitmap = dp_malloc(sizeof(*bitmap));
        bit_size = max - min + 1;
        bitmap->offset = min;

        bytes_count = bit_size / 8;
        bytes_count += sizeof(*bitmap->map) - bytes_count % sizeof(*bitmap->map);

        bitmap->bit_size = bytes_count * 8;
        bitmap->map = dp_malloc(bytes_count);
        dp_memset(bitmap->map, 0, bytes_count);

        return bitmap;
    }
}

static inline bool
bitmap_structure_legal_ip(s_bitmap_t *bitmap)
{
    if (NULL_PTR_P(bitmap)) {
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
        dp_free((*bitmap)->map);
        dp_free((*bitmap));
        *bitmap = NULL;
    }
}

static inline void
bitmap_map_expand(s_bitmap_t *bitmap, native_wide_t val)
{
    uint32 bytes_count;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->offset + bitmap->bit_size);

    bytes_count = (val - bitmap->offset) / 8;
    bytes_count += sizeof(*bitmap->map) - bytes_count % sizeof(*bitmap->map);

    bitmap->bit_size = bytes_count * 8;
    bitmap->map = dp_realloc(bitmap->map, bytes_count);
}

static inline void
bitmap_bit_clear_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->offset);
    assert_exit(val < bitmap->offset + bitmap->bit_size);

    index = (val - bitmap->offset) / (sizeof(*bitmap->map) * 8);
    reminder = (val - bitmap->offset) % (sizeof(*bitmap->map) * 8);

    bitmap->map[index] &= (BITMAP_ALL ^ (BITMAP_SET << reminder));
}

static inline void
bitmap_bit_set_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->offset);

    if (val >= bitmap->offset + bitmap->bit_size) {
        bitmap_map_expand(bitmap, val);
    }

    index = (val - bitmap->offset) / (sizeof(*bitmap->map) * 8);
    reminder = (val - bitmap->offset) % (sizeof(*bitmap->map) * 8);

    bitmap->map[index] |= (BITMAP_SET << reminder);
}


static inline native_wide_t
bitmap_bit_get_i(s_bitmap_t *bitmap, native_wide_t val)
{
    native_wide_t bit;
    native_wide_t index;
    native_wide_t reminder;

    assert_exit(bitmap_structure_legal_ip(bitmap));
    assert_exit(val >= bitmap->offset);
    assert_exit(val < bitmap->offset + bitmap->bit_size);

    index = (val - bitmap->offset) / (sizeof(*bitmap->map) * 8);
    reminder = (val - bitmap->offset) % (sizeof(*bitmap->map) * 8);

    bit = (bitmap->map[index] >> reminder) & BITMAP_SET;

    return bit;
}

native_wide_t
bitmap_bit_get(s_bitmap_t *bitmap, native_wide_t val)
{
    if (!bitmap_structure_legal_ip(bitmap)) {
        return BITMAP_INVALID;
    } else if (val < bitmap->offset) {
        return BITMAP_INVALID;
    } else if (val >= bitmap->offset + bitmap->bit_size) {
        return BITMAP_INVALID;
    } else {
        return bitmap_bit_get_i(bitmap, val);
    }
}

void
bitmap_bit_clear(s_bitmap_t *bitmap, native_wide_t val)
{
    if (!bitmap_structure_legal_ip(bitmap)) {
        return;
    } else if (val < bitmap->offset) {
        return;
    } else if (val >= bitmap->offset + bitmap->bit_size) {
        return;
    } else {
        bitmap_bit_clear_i(bitmap, val);
    }
}

void
bitmap_bit_set(s_bitmap_t *bitmap, native_wide_t val)
{
    if (!bitmap_structure_legal_ip(bitmap)) {
        return;
    } else if (val < bitmap->offset) {
        return;
    } else {
        bitmap_bit_set_i(bitmap, val);
    }
}

void
bitmap_map_cleanup(s_bitmap_t *bitmap)
{
    if (bitmap_structure_legal_ip(bitmap)) {
        dp_memset(bitmap->map, 0, bitmap->bit_size / 8);
    }
}

