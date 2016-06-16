/*
 *
 * 1,2,4,6,7,[5]
 * tmp = [5]
 * 1,2,4,6,7,7
 * 1,2,4,6,6,7
 * [5] = tmp
 * 1,2,4,5,6,7
 *
 */
void
insertion_sort(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    uint32 i;
    uint32 j;
    void *tmp;

    if (sort_parameters_legal_p(base, size, csize, compare)) {
        i = 1;
        tmp = memory_cache_allocate(csize);

        while (i < size) {
            sort_cell_copy(tmp, base + i * csize, csize);
            j = i;

            while (j > 0 && compare(base + (j - 1) * csize, tmp) > 0) {
                sort_cell_copy(base + j * csize, base + (j - 1) * csize, csize);
                j--;
            }

            sort_cell_copy(base + j * csize, tmp, csize);
            i++;
        }

        memory_cache_free(tmp);
        dp_assert(sort_data_sorted_p(base, size, csize, compare));
    }
}

