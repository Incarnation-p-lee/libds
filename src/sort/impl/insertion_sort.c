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
        memcpy(to, from, size);
    }
}

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
sort_insertion(void *base, uint32 size, uint32 csize,
    sint32 (*compare)(const void *, const void *))
{
    uint32 i;
    uint32 j;
    void *tmp;

    if (complain_null_pointer_p(base)) {
        return;
    } else if (complain_null_pointer_p(compare)) {
        return;
    } else if (complain_zero_size_p(size)) {
        return;
    } else if (complain_zero_size_p(csize)) {
        return;
    } else {
        i = 1;
        tmp = memory_cache_allocate(size);

        while (i < size) {
            sort_cell_copy(tmp, base + i * size, csize);
            j = i;

            while (j > 0 && compare(base + (j - 1) * csize, tmp) > 0) {
                sort_cell_copy(base + j * csize, base + (j - 1) * csize, csize);
                j--;
            }

            sort_cell_copy(base + i * csize, tmp, size);
            i++;
        }

        memory_cache_free(tmp);
    }
}

