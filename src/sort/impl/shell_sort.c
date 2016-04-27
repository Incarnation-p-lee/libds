void
shell_sort(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    uint32 i;
    uint32 j;
    uint32 k;
    void *tmp;
    uint32 inc;

    if (sort_parameters_legal_p(base, size, csize, compare)) {
        tmp = memory_cache_allocate(csize);
        k = shell_sort_exponet_get(size);

        while (k > 0) {
            inc = shell_sort_hibbard_increment_seq(k);
            i = inc;

            while (i < size) {
                sort_cell_copy(tmp, base + i * csize, csize);
                j = i;

                while (j >= inc && compare(base + (j - inc) * csize, tmp) > 0) {
                    sort_cell_copy(base + j * csize, base + (j - inc) * csize, csize);
                    j -= inc;
                }

                sort_cell_copy(base + j * csize, tmp, csize);
                i++;
            }

            k--;
        }

        memory_cache_free(tmp);
        assert(sort_data_sorted_p(base, size, csize, compare));
    }
}

/*
 * Here shell sort use Hibbard increment sequence.
 * H[k] = 2^k - 1.
 * with worst time O(N^(3/2))
 */
static inline uint32
shell_sort_exponet_get(uint32 size)
{
    uint32 retval;

    assert(size > 1);

    retval = 0;
    while (size) {
        retval += 1;
        size = size >> 1;
    }

    return retval - 1;
}

/*
 * For shell sort H[k] = 2^k - 1.
 */
static const uint32 hibbard_sequence[] = {
    0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191,
    16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151,
    4194303, 8388607, 16777215, 33554431, 67108863, 134217727,
    268435455, 536870911, 1073741823, 2147483647, 4294967295,
};

static inline uint32
shell_sort_hibbard_increment_seq(uint32 k)
{
    assert(!complain_zero_size_p(k));
    assert(k < array_sizeof(hibbard_sequence));

    return hibbard_sequence[k];
}

