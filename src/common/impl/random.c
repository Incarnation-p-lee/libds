uint32
random_uint32_with_limit(uint32 limit)
{
    if (limit) {
        return random_uint32_limited(limit);
    } else {
        return 0;
    }
}

static inline uint32
random_uint32_limited(uint32 limit)
{
    assert_exit(!complain_zero_size_p(limit));

    return (uint32)dp_rand() % limit;
}

sint64
random_sint64(void)
{
    return (sint64)dp_rand() - (sint64)dp_rand();
}

uint32 *
random_sequence_uint32_limited_obtain(uint32 len, uint32 limit)
{
    uint32 i;
    uint32 *sequence;

    if (!len || !limit) {
        return PTR_INVALID;
    } else {
        sequence = dp_malloc(sizeof(*sequence) * len);

        i = 0;
        while (i < len) {
            sequence[i++] = random_uint32_limited(limit);
        }

        return sequence;
    }
}

uint32 *
random_sequence_uint32_obtain(uint32 len)
{
    uint32 i;
    uint32 *sequence;

    if (!len) {
        return PTR_INVALID;
    } else {
        sequence = dp_malloc(sizeof(*sequence) * len);

        i = 0;
        while (i < len) {
            sequence[i++] = dp_rand();
        }

        return sequence;
    }
}

void
random_sequence_drop(uint32 *sequence)
{
    if (!complain_null_pointer_p(sequence)) {
        dp_free(sequence);
    }
}

