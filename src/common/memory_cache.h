#ifndef HAVE_MEMORY_CACHE_H
#define HAVE_MEMORY_CACHE_H

#define MEM_ENTRY_CNT  16
#define MEM_ENTRY_NULL 0
#define MEM_PRE_LEN    0x10
#define MEM_TO_REAL(a) (a - MEM_PRE_LEN)

struct memory_cache_entry {
    void   *addr;
    uint32 size;
};

struct memory_cache_set {
    struct memory_cache_entry *list;
    uint32                    cnt;
    uint32                    index;
};

static struct memory_cache_entry memory_cache_list[MEM_ENTRY_CNT];
static struct memory_cache_set mem_cc_set = {
    memory_cache_list, MEM_ENTRY_CNT, 0,
};

#endif

