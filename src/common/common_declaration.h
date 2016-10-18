#ifndef HAVE_DEFINED_common_H
#define HAVE_DEFINED_common_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

bool array_iterator_structure_legal_p(s_array_iterator_t *iterator);
bool complain_no_memory_p(void *ptr);
bool complain_null_pointer_p(void *ptr);
bool complain_zero_size_p(uint32 size);
s_array_iterator_t * array_iterator_create(void);
sint64 random_sint64(void);
static inline bool array_iterator_structure_legal_ip(s_array_iterator_t *iterator);
static inline bool memory_cache_add_entry_p(void *addr, uint32 size);
static inline bool memory_cache_find_entry_greater_size_p(void **addr, uint32 size);
static inline bool memory_cache_find_entry_of_size_p(void **addr, uint32 size);
static inline uint32 prime_numeral_calculate_next(uint32 prime);
static inline void libds_log_memory_stat_print(void);
static inline void memory_cache_remove_entry_by_index(uint32 index);
uint32 * convert_string_to_uint32_array(char *string, uint32 *len);
uint32 prime_numeral_next(uint32 prime);
uint32 random_uint32_with_limit(uint32 lmt);
void * malloc_wrap(uint32 size);
void * memory_cache_allocate(uint32 size);
void * memory_cache_re_allocate(void *addr, uint32 size);
void * realloc_wrap(void *ptr, uint32 size);
void array_iterator_destroy(s_array_iterator_t *iterator);
void array_iterator_initial(s_array_iterator_t *iterator, f_array_iterator_initial_t fp_index_initial, f_array_iterator_next_exist_t fp_next_exist_p, f_array_iterator_next_obtain_t fp_next_obtain);
void complain_assert_caution(char *msg, const char *fname, const char *func, uint32 line);
void complain_assert_exit(char *msg, const char *fname, const char *func, uint32 line);
void free_wrap(void *ptr);
void libds_log_file_close(void);
void libds_log_file_create(void);
void libds_log_print(enum log_level lvl, const char *msg);
void memory_cache_cleanup(void);
void memory_cache_free(void *addr);

#endif

