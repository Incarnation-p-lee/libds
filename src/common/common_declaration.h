#ifndef COMMON_DECLARATION_H
#define COMMON_DECLARATION_H


bool complain_no_memory_p(void *ptr);
bool complain_null_pointer_p(void *ptr);
bool complain_zero_size_p(uint32 size);
sint64 dp_random_sint64(void);
static inline bool memory_cache_add_entry_p(void *addr, uint32 size);
static inline bool memory_cache_find_entry_greater_size_p(void **addr, uint32 size);
static inline bool memory_cache_find_entry_of_size_p(void **addr, uint32 size);
static inline uint32 prime_numeral_calculate_next(uint32 prime);
static inline void memory_cache_remove_entry_by_index(uint32 index);
uint32 dp_random_uint32_with_limit(uint32 lmt);
uint32 prime_numeral_next(uint32 prime);
void * memory_cache_allocate(uint32 size);
void * memory_cache_re_allocate(void *addr, uint32 size);
void memory_cache_cleanup(void);
void memory_cache_dp_free(void *addr);

#endif
