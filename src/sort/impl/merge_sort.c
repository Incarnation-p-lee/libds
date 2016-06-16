void
merge_sort(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    void *tmp;

    if (sort_parameters_legal_p(base, size, csize, compare)) {
        tmp = memory_cache_allocate(size * csize);

        merge_sort_recursive(base, tmp, 0, size - 1, csize, compare);

        memory_cache_free(tmp);
        dp_assert(sort_data_sorted_p(base, size, csize, compare));
    }
}

static inline void
merge_sort_recursive(void *base, void *tmp, uint32 left, uint32 right,
    uint32 csize, sint32 (*compare)(const void *, const void *))
{
    uint32 med;

    dp_assert(!complain_null_pointer_p(base));
    dp_assert(!complain_null_pointer_p(tmp));
    dp_assert(!complain_null_pointer_p(compare));
    dp_assert(!complain_zero_size_p(csize));

    if (left < right) {
        med = (left + right) / 2;
        merge_sort_recursive(base, tmp, left, med, csize, compare);
        merge_sort_recursive(base, tmp, med + 1, right, csize, compare);
        merge_sort_divide_merge(base, tmp, left, med, right, csize, compare);
    }
}

static inline void
merge_sort_divide_merge(void *base, void *tmp, uint32 left, uint32 med, uint32 right,
    uint32 csize, sint32 (*compare)(const void *, const void *))
{
    void *start;
    void *limit;
    void *p1, *p1_lmt;
    void *p2, *p2_lmt;

    dp_assert(!complain_null_pointer_p(base));
    dp_assert(!complain_null_pointer_p(compare));
    dp_assert(!complain_null_pointer_p(tmp));
    dp_assert(!complain_zero_size_p(csize));
    dp_assert(left <= med && med <= right);

    p1 = base + left * csize;
    p1_lmt = base + med * csize;
    p2 = p1_lmt + csize;
    p2_lmt = base + right * csize;

    start = tmp + left * csize;
    while (p1 <= p1_lmt && p2 <= p2_lmt) {
        if (compare(p1, p2) < 0) {
            sort_cell_copy(start, p1, csize);
            p1 += csize;
        } else {
            sort_cell_copy(start, p2, csize);
            p2 += csize;
        }
        start += csize;
    }

    while (p1 <= p1_lmt) {
        sort_cell_copy(start, p1, csize);
        p1 += csize;
        start += csize;
    }

    while (p2 <= p2_lmt) {
        sort_cell_copy(start, p2, csize);
        p2 += csize;
        start += csize;
    }

    limit = tmp + right * csize;
    dp_assert(start == limit + csize);
    start = tmp + left * csize;
    p1 = base + left * csize;

    while (start <= limit) {
        sort_cell_copy(p1, start, csize);
        p1 += csize;
        start += csize;
    }
}

