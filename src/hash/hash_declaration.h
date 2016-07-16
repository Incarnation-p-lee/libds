#ifndef HAVE_DEFINED_hash_H
#define HAVE_DEFINED_hash_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

s_separate_chain_hash_t * separate_chain_hash_create(uint32 size);
s_separate_chain_hash_t * separate_chain_hash_rehashing(s_separate_chain_hash_t **hash);
static inline bool hashing_table_structure_legal_p(struct hashing_table *hash);
static inline bool open_addressing_hash_structure_legal_p(struct open_addressing_hash *hash);
static inline bool separate_chain_hash_structure_legal_p(s_separate_chain_hash_t *hash);
static inline bool separate_chain_structure_legal_p(s_separate_chain_t *chain);
static inline s_separate_chain_t * separate_chain_create(void *val);
static inline s_separate_chain_t * separate_chain_hash_head(s_separate_chain_hash_t *hash, uint32 index);
static inline s_separate_chain_t * separate_chain_next(s_separate_chain_t *chain);
static inline s_separate_chain_t * separate_chain_ptr_to_chain(s_doubly_linked_list_t *node);
static inline s_separate_chain_t ** separate_chain_hash_space(s_separate_chain_hash_t *hash);
static inline struct hashing_table * hashing_table_create(uint32 size);
static inline uint32 hashing_function_square(uint32 iter);
static inline uint32 hashing_table_load_factor_calculate(struct hashing_table *hash);
static inline uint32 open_addressing_hash_index_calculate(struct open_addressing_hash *hash, void *key, uint32 iter);
static inline uint32 open_addressing_hash_limit(struct open_addressing_hash *hash);
static inline uint32 separate_chain_hash_index_calculate(s_separate_chain_hash_t *hash, void *key);
static inline void * open_addressing_hash_node(struct open_addressing_hash *hash, uint32 index);
static inline void ** hashing_table_space(struct hashing_table *hash);
static inline void ** open_addressing_hash_space(struct open_addressing_hash *hash);
static inline void hashing_table_destroy(struct hashing_table **hash);
static inline void hashing_table_hash_function_set(struct hashing_table *hash, void *func);
static inline void hashing_table_initial(struct hashing_table *hash);
static inline void open_addressing_hash_node_set(struct open_addressing_hash *hash, uint32 index, void *val);
static inline void open_addressing_hash_space_rehashing(struct open_addressing_hash *to, struct open_addressing_hash *from);
static inline void separate_chain_destroy(s_separate_chain_t *chain);
static inline void separate_chain_hash_chain_destroy(s_separate_chain_hash_t *hash);
static inline void separate_chain_hash_head_set(s_separate_chain_hash_t *hash, uint32 index, s_separate_chain_t *val);
static inline void separate_chain_hash_space_rehashing(s_separate_chain_hash_t *to, s_separate_chain_hash_t *from);
struct open_addressing_hash * open_addressing_hash_create(uint32 size);
struct open_addressing_hash * open_addressing_hash_rehashing(struct open_addressing_hash **hash);
uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 iter);
uint32 hashing_function_polynomial(void *key, uint32 size);
uint32 open_addressing_hash_load_factor(struct open_addressing_hash *hash);
uint32 open_addressing_hash_load_factor_calculate(struct open_addressing_hash *hash);
uint32 open_addressing_hash_size(struct open_addressing_hash *hash);
uint32 separate_chain_hash_load_factor(s_separate_chain_hash_t *hash);
uint32 separate_chain_hash_load_factor_calculate(s_separate_chain_hash_t *hash);
uint32 separate_chain_hash_size(s_separate_chain_hash_t *hash);
void * open_addressing_hash_find(struct open_addressing_hash *hash, void *key);
void * open_addressing_hash_remove(struct open_addressing_hash *hash, void *key);
void * separate_chain_hash_find(s_separate_chain_hash_t *hash, void *key);
void * separate_chain_hash_insert(s_separate_chain_hash_t **hash, void *key);
void * separate_chain_hash_remove(s_separate_chain_hash_t *hash, void *key);
void open_addressing_hash_destroy(struct open_addressing_hash **hash);
void open_addressing_hash_insert(struct open_addressing_hash **hash, void *key);
void separate_chain_hash_destroy(s_separate_chain_hash_t **hash);

#endif

