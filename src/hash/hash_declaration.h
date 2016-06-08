#ifndef HAVE_DEFINED_hash_H
#define HAVE_DEFINED_hash_H

static inline bool hashing_table_structure_legal_p(struct hashing_table *hash);
static inline bool open_addressing_hash_structure_legal_p(struct open_addressing_hash *hash);
static inline bool separate_chain_hash_structure_legal_p(struct separate_chain_hash *hash);
static inline struct doubly_linked_list * separate_chain_hash_chain_head(struct separate_chain_hash *hash, uint32 index);
static inline struct doubly_linked_list ** separate_chain_hash_space(struct separate_chain_hash *hash);
static inline struct hashing_table * hashing_table_create(uint32 size);
static inline uint32 hashing_function_square(uint32 iter);
static inline uint32 hashing_table_load_factor_calculate(struct hashing_table *hash);
static inline uint32 open_addressing_hash_index_calculate(struct open_addressing_hash *hash, void *key, uint32 iter);
static inline uint32 open_addressing_hash_limit(struct open_addressing_hash *hash);
static inline uint32 separate_chain_hash_index_calculate(struct separate_chain_hash *hash, void *key);
static inline void * open_addressing_hash_node(struct open_addressing_hash *hash, uint32 index);
static inline void ** hashing_table_space(struct hashing_table *hash);
static inline void ** open_addressing_hash_space(struct open_addressing_hash *hash);
static inline void hashing_table_destroy(struct hashing_table **hash);
static inline void hashing_table_hash_function_set(struct hashing_table *hash, void *func);
static inline void hashing_table_initial(struct hashing_table *hash);
static inline void open_addressing_hash_node_set(struct open_addressing_hash *hash, uint32 index, void *val);
static inline void open_addressing_hash_space_rehashing(struct open_addressing_hash *to, struct open_addressing_hash *from);
static inline void separate_chain_hash_chain_destroy(struct separate_chain_hash *hash);
static inline void separate_chain_hash_chain_head_set(struct separate_chain_hash *hash, uint32 index, struct doubly_linked_list *val);
static inline void separate_chain_hash_chain_rehashing(struct doubly_linked_list *link, struct separate_chain_hash *hash);
static inline void separate_chain_hash_space_rehashing(struct separate_chain_hash *to, struct separate_chain_hash *from);
struct open_addressing_hash * open_addressing_hash_create(uint32 size);
struct open_addressing_hash * open_addressing_hash_rehashing(struct open_addressing_hash **hash);
struct separate_chain_hash * separate_chain_hash_create(uint32 size);
struct separate_chain_hash * separate_chain_hash_rehashing(struct separate_chain_hash **hash);
uint32 hashing_function_open_addressing(void *key, uint32 size, uint32 iter);
uint32 hashing_function_polynomial(void *key, uint32 size);
uint32 open_addressing_hash_load_factor(struct open_addressing_hash *hash);
uint32 open_addressing_hash_load_factor_calculate(struct open_addressing_hash *hash);
uint32 open_addressing_hash_size(struct open_addressing_hash *hash);
uint32 separate_chain_hash_load_factor(struct separate_chain_hash *hash);
uint32 separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash);
uint32 separate_chain_hash_size(struct separate_chain_hash *hash);
void * open_addressing_hash_find(struct open_addressing_hash *hash, void *key);
void * open_addressing_hash_remove(struct open_addressing_hash *hash, void *key);
void * separate_chain_hash_find(struct separate_chain_hash *hash, void *key);
void * separate_chain_hash_remove(struct separate_chain_hash *hash, void *key);
void open_addressing_hash_destroy(struct open_addressing_hash **hash);
void open_addressing_hash_insert(struct open_addressing_hash **hash, void *key);
void separate_chain_hash_destroy(struct separate_chain_hash **hash);
void separate_chain_hash_insert(struct separate_chain_hash **hash, void *key);

#endif

