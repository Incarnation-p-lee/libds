bool
sort_data_sorted_p(void *data, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    void *a;
    void *b;
    uint32 i;

    assert(!complain_null_pointer_p(data));
    assert(!complain_null_pointer_p(compare));
    assert(!complain_zero_size_p(size));
    assert(!complain_zero_size_p(csize));

    i = 1;
    while (i < size) {
        a = data + (i - 1) * csize;
        b = data + i * csize;

        if (compare(a, b) > 0) {
            return false;
        }
        i++;
    }

    return true;
}

static inline void
sort_cell_copy(void *to, void *from, uint32 size)
{
    assert(!complain_null_pointer_p(to));
    assert(!complain_null_pointer_p(from));
    assert(!complain_zero_size_p(size));

    if (sizeof(uint64) == size) {
        *(uint64 *)to = *(uint64 *)from;
    } else if (sizeof(uint32) == size) {
        *(uint32 *)to = *(uint32 *)from;
    } else if (sizeof(uint16) == size) {
        *(uint16 *)to = *(uint16 *)from;
    } else if (sizeof(uint8) == size) {
        *(uint8 *)to = *(uint8 *)from;
    } else {
        dp_memcpy(to, from, size);
    }
}

static inline void
sort_cell_swap(void *a, void *b, uint32 size)
{
    void *tmp;

    assert(!complain_null_pointer_p(a));
    assert(!complain_null_pointer_p(b));
    assert(!complain_zero_size_p(size));

    tmp = memory_cache_allocate(size);

    sort_cell_copy(tmp, a, size);
    sort_cell_copy(a, b, size);
    sort_cell_copy(b, tmp, size);

    memory_cache_free(tmp);
}

static inline bool
sort_parameters_legal_p(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    if (complain_null_pointer_p(base)) {
        return false;
    } else if (complain_null_pointer_p(compare)) {
        return false;
    } else if (complain_zero_size_p(size)) {
        return false;
    } else if (complain_zero_size_p(csize)) {
        return false;
    } else {
        return true;
    }
}

