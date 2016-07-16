#ifndef HAVE_DEFINED_common_H
#define HAVE_DEFINED_common_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

bool complain_no_memory_p(void *ptr);
bool complain_null_pointer_p(void *ptr);
bool complain_zero_size_p(uint32 size);
sint64 random_sint64(void);
static inline bool memory_cache_add_entry_p(void *addr, uint32 size);
static inline bool memory_cache_find_entry_greater_size_p(void **addr, uint32 size);
static inline bool memory_cache_find_entry_of_size_p(void **addr, uint32 size);
static inline uint32 prime_numeral_calculate_next(uint32 prime);
static inline void memory_cache_remove_entry_by_index(uint32 index);
uint32 prime_numeral_next(uint32 prime);
uint32 random_uint32_with_limit(uint32 lmt);
void * memory_cache_allocate(uint32 size);
void * memory_cache_re_allocate(void *addr, uint32 size);
void complain_assert_caution(char *msg, const char *fname, const char *func, uint32 line);
void complain_assert_exit(char *msg, const char *fname, const char *func, uint32 line);
void memory_cache_cleanup(void);
void memory_cache_free(void *addr);

#endif

