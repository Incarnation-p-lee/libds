void *
memory_cache_allocate(uint32 size)
{
    void *retval;

    if (complain_zero_size_p(size)) {
        return NULL;
    } else if (memory_cache_find_entry_of_size_p(&retval, size)) {
        memory_cache_remove_entry_by_index(mem_cc_set.index);
        return retval;
    } else if (memory_cache_find_entry_greater_size_p(&retval, size)) {
        memory_cache_remove_entry_by_index(mem_cc_set.index);
        return retval;
    } else {
        retval = malloc_ds(size + MEM_PRE_LEN);

        if (!complain_no_memory_p(retval)) {
            *(uint32 *)retval = size;
            return retval + MEM_PRE_LEN;
        } else {
            return NULL;
        }
    }
}

void *
memory_cache_re_allocate(void *addr, uint32 size)
{
    uint32 old_size;
    void *new_addr;

    if (complain_zero_size_p(size)) {
        return NULL;
    } else if (complain_null_pointer_p(addr)) {
        return memory_cache_allocate(size);
    } else {
        old_size = *(uint32 *)MEM_TO_REAL(addr);
        dp_assert(0 != old_size);

        if (size <= old_size) {
            return addr;
        } else {
            new_addr = realloc_ds(MEM_TO_REAL(addr), size + MEM_PRE_LEN);
            *(uint32 *)new_addr = size;
            return new_addr + MEM_PRE_LEN;
        }
    }
}

void
memory_cache_free(void *addr)
{
    uint32 size;

    if (!complain_null_pointer_p(addr)) {
        size = *(uint32 *)(MEM_TO_REAL(addr));
        dp_assert(0 != size);

        if (!memory_cache_add_entry_p(addr, size)) {
            free_ds(MEM_TO_REAL(addr));
        }
    }
}

static inline void
memory_cache_remove_entry_by_index(uint32 index)
{
    dp_assert(index < MEM_ENTRY_CNT);

    mem_cc_set.list[index].addr = NULL;
    mem_cc_set.list[index].size = MEM_ENTRY_NULL;
}

static inline bool
memory_cache_add_entry_p(void *addr, uint32 size)
{
    uint32 index_start;
    struct memory_cache_entry *cache;

    dp_assert(NULL != addr);
    dp_assert(!complain_zero_size_p(size));

    index_start = mem_cc_set.index;
    cache = mem_cc_set.list;

    do {
        if (MEM_ENTRY_NULL == cache[index_start].size) {
            cache[index_start].addr = addr;
            cache[index_start].size = size;
            return true;
        }

        index_start++;
        if (MEM_ENTRY_CNT == index_start) {
            index_start = 0;
        }
    } while (index_start != mem_cc_set.index);

    return false;
}

static inline bool
memory_cache_find_entry_of_size_p(void **addr, uint32 size)
{
    uint32 index_start;

    dp_assert(!complain_zero_size_p(size));

    index_start = mem_cc_set.index;

    while (index_start < MEM_ENTRY_CNT) {
        if (size == mem_cc_set.list[index_start].size) {
            *addr = mem_cc_set.list[index_start].addr;
            mem_cc_set.index = index_start;
            return true;
        }
        index_start++;
    }

    mem_cc_set.index = 0;

    return false;
}

static inline bool
memory_cache_find_entry_greater_size_p(void **addr, uint32 size)
{
    uint32 index_start;

    dp_assert(!complain_zero_size_p(size));

    index_start = mem_cc_set.index;

    while (index_start < MEM_ENTRY_CNT) {
        if (size <= mem_cc_set.list[index_start].size) {
            *addr = mem_cc_set.list[index_start].addr;
            mem_cc_set.index = index_start;
            return true;
        }
        index_start++;
    }

    mem_cc_set.index = 0;

    return false;
}

void
memory_cache_cleanup(void)
{
    uint32 index_start;

    index_start = 0;
    while (index_start < MEM_ENTRY_CNT) {
        if (MEM_ENTRY_NULL != mem_cc_set.list[index_start].size) {
            free_ds(MEM_TO_REAL(mem_cc_set.list[index_start].addr));
        }
        index_start++;
    }
}

