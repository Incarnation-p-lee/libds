#ifndef HAVE_DEFINED_hash_H
#define HAVE_DEFINED_hash_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

#if defined DEBUG

static inline bool hashing_table_structure_legal_p(s_hashing_table_t *table);
static inline bool open_addressing_hash_structure_illegal_p(s_open_addressing_hash_t *hash);
static inline bool open_addressing_hash_structure_legal_p(s_open_addressing_hash_t *hash);
static inline bool separate_chain_hash_structure_illegal_p(s_separate_chain_hash_t *hash);
static inline bool separate_chain_hash_structure_legal_p(s_separate_chain_hash_t *hash);
static inline bool separate_chain_structure_legal_p(s_separate_chain_t *chain);
static inline uint32 hashing_table_load_factor_calculate(s_hashing_table_t *table);
static inline uint32 open_addressing_hash_limit(s_open_addressing_hash_t *hash);

#endif

bool bitmap_bit_clear_p(s_bitmap_t *bitmap, native_wide_t val);
bool bitmap_bit_set_p(s_bitmap_t *bitmap, native_wide_t val);
bool bitmap_structure_illegal_p(s_bitmap_t *bitmap);
bool bitmap_structure_legal_p(s_bitmap_t *bitmap);
native_wide_t bitmap_bit_get(s_bitmap_t *bitmap, native_wide_t val);
s_bitmap_t * bitmap_create(native_wide_t min, native_wide_t max);
s_open_addressing_hash_t * open_addressing_hash_create(uint32 size);
s_separate_chain_hash_t * separate_chain_hash_create(uint32 size);
static inline bool bitmap_structure_illegal_ip(s_bitmap_t *bitmap);
static inline bool bitmap_structure_legal_ip(s_bitmap_t *bitmap);
static inline native_wide_t bitmap_bit_get_i(s_bitmap_t *bitmap, native_wide_t val);
static inline native_wide_t bitmap_map_index(s_bitmap_t *bitmap, native_wide_t val);
static inline native_wide_t bitmap_map_reminder(s_bitmap_t *bitmap, native_wide_t val);
static inline s_hashing_table_t * hashing_table_create(uint32 size);
static inline s_open_addressing_hash_t * open_addressing_hash_create_i(uint32 size);
static inline s_separate_chain_hash_t * separate_chain_hash_create_i(uint32 size);
static inline s_separate_chain_t * separate_chain_create(void *val);
static inline s_separate_chain_t * separate_chain_next(s_separate_chain_t *chain);
static inline s_separate_chain_t * separate_chain_ptr_to_chain(s_doubly_linked_list_t *node);
static inline uint32 bitmap_native_align(uint32 bytes_count);
static inline uint32 bitmap_native_bytes_count(s_bitmap_t *bitmap);
static inline uint32 hashing_function_square(uint32 iter);
static inline uint32 hashing_table_load_factor(s_hashing_table_t *table);
static inline uint32 open_addressing_hash_find_index(s_open_addressing_hash_t *hash, void *key);
static inline uint32 open_addressing_hash_index_calculate(s_open_addressing_hash_t *hash, void *key, uint32 counter);
static inline uint32 separate_chain_hash_index_calculate(s_separate_chain_hash_t *hash, void *key);
static inline void * separate_chain_hash_insert_i(s_separate_chain_hash_t *hash, void *key);
static inline void * separate_chain_hash_remove_i(s_separate_chain_hash_t *hash, void *key);
static inline void bitmap_bit_clear_i(s_bitmap_t *bitmap, native_wide_t val);
static inline void bitmap_bit_set_i(s_bitmap_t *bitmap, native_wide_t val);
static inline void bitmap_map_expand(s_bitmap_t *bitmap, native_wide_t val);
static inline void hashing_table_destroy(s_hashing_table_t **table);
static inline void hashing_table_initial(s_hashing_table_t *table);
static inline void open_addressing_hash_destroy_i(s_open_addressing_hash_t *hash);
static inline void open_addressing_hash_rehashing_i(s_open_addressing_hash_t *hash);
static inline void separate_chain_destroy(s_separate_chain_t *chain);
static inline void separate_chain_hash_chain_destroy(s_separate_chain_hash_t *hash);
static inline void separate_chain_hash_destroy_i(s_separate_chain_hash_t *hash);
static inline void separate_chain_hash_rehashing_i(s_separate_chain_hash_t *hash);
uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 counter);
uint32 hashing_function_polynomial(void *key, uint32 size);
uint32 open_addressing_hash_load_factor(s_open_addressing_hash_t *hash);
uint32 open_addressing_hash_load_factor_peak(s_open_addressing_hash_t *hash);
uint32 open_addressing_hash_size(s_open_addressing_hash_t *hash);
uint32 separate_chain_hash_load_factor(s_separate_chain_hash_t *hash);
uint32 separate_chain_hash_load_factor_peak(s_separate_chain_hash_t *hash);
uint32 separate_chain_hash_size(s_separate_chain_hash_t *hash);
void * open_addressing_hash_find(s_open_addressing_hash_t *hash, void *key);
void * open_addressing_hash_insert(s_open_addressing_hash_t *hash, void *key);
void * open_addressing_hash_insert_i(s_open_addressing_hash_t *hash, void *key);
void * open_addressing_hash_remove(s_open_addressing_hash_t *hash, void *key);
void * separate_chain_hash_find(s_separate_chain_hash_t *hash, void *key);
void * separate_chain_hash_insert(s_separate_chain_hash_t *hash, void *key);
void * separate_chain_hash_remove(s_separate_chain_hash_t *hash, void *key);
void bitmap_bit_clear(s_bitmap_t *bitmap, native_wide_t val);
void bitmap_bit_set(s_bitmap_t *bitmap, native_wide_t val);
void bitmap_destroy(s_bitmap_t **bitmap);
void bitmap_map_cleanup(s_bitmap_t *bitmap);
void open_addressing_hash_destroy(s_open_addressing_hash_t **hash);
void open_addressing_hash_rehashing(s_open_addressing_hash_t *hash);
void separate_chain_hash_destroy(s_separate_chain_hash_t **hash);
void separate_chain_hash_rehashing(s_separate_chain_hash_t *hash);

#endif

