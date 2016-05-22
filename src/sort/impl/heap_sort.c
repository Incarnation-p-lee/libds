void
heap_sort(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    uint32 index;

    if (sort_parameters_legal_p(base, size, csize, compare)) {
        heap_sort_build_heap(base, size, csize, compare);

        // Put the max one from heap top to tail of array
        index = size - 1;
        while (index > 0) {
            sort_cell_swap(base, base + index * csize, csize);
            heap_sort_percolate_down(base, index, csize, 0, compare);
            index--;
        }

        dp_assert(sort_data_sorted_p(base, size, csize, compare));
    }
}

static inline void
heap_sort_build_heap(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    sint32 index;

    dp_assert(sort_parameters_legal_p(base, size, csize, compare));

    index = (sint32)(size >> 1);

    while (index >= 0) {
        heap_sort_percolate_down(base, size, csize, index, compare);
        index--;
    }
}

#define HEAP_LEFT(idx)         ((idx) * 2 + 1)

static inline void
heap_sort_percolate_down(void *base, uint32 size, uint32 csize, uint32 index,
    sint32 (*compare)(const void *, const void *))
{
    uint32 i;
    void *tmp;
    uint32 child;

    dp_assert(sort_parameters_legal_p(base, size, csize, compare));
    dp_assert(index < size);

    tmp = memory_cache_allocate(csize);
    sort_cell_copy(tmp, base + index * csize, csize);

    i = index;
    while (HEAP_LEFT(i) < size) {
        child = HEAP_LEFT(i);
        if (child != size - 1
            && compare(base + child * csize, base + (child + 1) * csize) < 0) {
            child++;
        }

        if (compare(tmp, base + child * csize) < 0) {
            sort_cell_copy(base + i * csize, base + child * csize, csize);
        } else {
            break;
        }
        i = child;
    }

    sort_cell_copy(base + i * csize, tmp, csize);
    memory_cache_dp_free(tmp);
}

#undef HEAP_LEFT

