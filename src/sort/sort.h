#ifndef HAVE_DEFINED_SORT_H
#define HAVE_DEFINED_SORT_H

extern bool complain_null_pointer_p(void *ptr);
extern bool complain_zero_size_p(uint32 size);
extern void * memory_cache_allocate(uint32 size);
extern void memory_cache_free(void *addr);

#endif

