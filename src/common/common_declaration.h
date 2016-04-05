#ifndef COMMON_DECLARATION_H
#define COMMON_DECLARATION_H


bool complain_no_memory_p(void *ptr);
bool complain_null_pointer_p(void *ptr);
bool complain_zero_size_p(uint32 size);
sint64 random_sint64(void);
static inline FILE * memory_maps_proc_read(void);
static inline bool memory_cache_add_entry_p(void *addr, uint32 size);
static inline bool memory_cache_find_entry_greater_size_p(void **addr, uint32 size);
static inline bool memory_cache_find_entry_of_size_p(void **addr, uint32 size);
static inline char * memory_maps_one_line_map_name(char *line);
static inline uint32 memory_maps_one_line_map_authority(char *line);
static inline uint32 prime_numeral_calculate_next(uint32 prime);
static inline void memory_cache_remove_entry_by_index(uint32 index);
static inline void memory_maps_filter_process(FILE *maps);
static inline void memory_maps_one_line_map_boundary(char *line, struct memory_maps *map);
static inline void memory_maps_one_line_process(char *line, uint32 len);
struct memory_maps * memory_maps_entry_find(char *name);
uint32 prime_numeral_next(uint32 prime);
uint32 random_uint32_with_limit(uint32 lmt);
void * memory_cache_allocate(uint32 size);
void * memory_cache_re_allocate(void *addr, uint32 size);
void memory_cache_cleanup(void);
void memory_cache_free(void *addr);
void memory_maps_obtain(void);

#endif
