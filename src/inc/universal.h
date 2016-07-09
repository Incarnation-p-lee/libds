#ifndef HAVE_DEFINED_UNIVERSAL_H
#define HAVE_DEFINED_UNIVERSAL_H

// Automaticaly generated by script/produce_universal_h.pl.

extern bool complain_no_memory_p(void *ptr);
extern bool complain_null_pointer_p(void *ptr);
extern bool complain_zero_size_p(uint32 size);
extern sint64 random_sint64(void);
extern uint32 prime_numeral_next(uint32 prime);
extern uint32 random_uint32_with_limit(uint32 lmt);
extern void * memory_cache_allocate(uint32 size);
extern void * memory_cache_re_allocate(void *addr, uint32 size);
extern void complain_assert(char *msg, const char *fname, const char *func, uint32 line, bool cond);
extern void memory_cache_cleanup(void);
extern void memory_cache_free(void *addr);

#endif

