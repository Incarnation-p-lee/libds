void
quick_sort(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    if (sort_parameters_legal_p(base, size, csize, compare)) {
        quick_sort_recursive(base, 0, size - 1, csize, compare);
        assert(sort_data_sorted_p(base, size, csize, compare));
    }
}

static inline void
quick_sort_recursive(void *base, uint32 left, uint32 right,
    uint32 csize, sint32 (*compare)(const void *, const void *))
{
    void *ptr_l;
    void *ptr_r;
    void *ptr_m;
    uint32 median;

    assert(sort_parameters_legal_p(base, csize, csize, compare));

    ptr_l = base + left * csize;
    ptr_r = base + right * csize;

    if (left + 2 < right) {
        ptr_m = quick_sort_obtain_median(base, left, right, csize, compare);
        sort_cell_swap(ptr_m, ptr_r - csize, csize);

        ptr_m = ptr_r - csize;
        ptr_r = ptr_m;

        while (true) {
            do {
                ptr_l += csize;
            } while (compare(ptr_m, ptr_l) > 0);
            do {
                ptr_r -= csize;
            } while (compare(ptr_m, ptr_r) < 0);

            if (ptr_l < ptr_r) {
                sort_cell_swap(ptr_l, ptr_r, csize);
            } else {
                break;
            }
        }

        sort_cell_swap(ptr_l, ptr_m, csize);
        median = (ptr_l - base) / csize;

        quick_sort_recursive(base, left, median - 1, csize, compare);
        quick_sort_recursive(base, median + 1, right, csize, compare);
    } else if (left + 2 == right) {
        quick_sort_obtain_median(base, left, right, csize, compare);
    } else if (left + 1 == right && compare(ptr_l, ptr_r) > 0) {
        sort_cell_swap(ptr_l, ptr_r, csize);
    }
}

static inline void *
quick_sort_obtain_median(void *base, uint32 left, uint32 right, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    void *ptr_l;
    void *ptr_r;
    void *ptr_m;

    assert(sort_parameters_legal_p(base, csize, csize, compare));

    ptr_l = base + left * csize;
    ptr_r = base + right * csize;
    ptr_m = base + ((left + right) / 2) * csize;

    if (compare(ptr_l, ptr_m) > 0) {
        sort_cell_swap(ptr_l, ptr_m, csize);
    }

    if (compare(ptr_l, ptr_r) > 0) {
        sort_cell_swap(ptr_l, ptr_r, csize);
    }

    if (compare(ptr_m, ptr_r) > 0) {
        sort_cell_swap(ptr_m, ptr_r, csize);
    }

    return ptr_m;
}

