#ifndef HAVE_HASHING_TABLE_INTERNAL_H
#define HAVE_HASHING_TABLE_INTERNAL_H

static inline struct hashing_table * hashing_table_create(uint32 size);
static inline void hashing_table_initial(struct hashing_table *hash);
static inline void hashing_table_hash_function_set(struct hashing_table *hash, void *func);
static inline void ** hashing_table_space(struct hashing_table *hash);
static inline void hashing_table_destroy(struct hashing_table **hash);
static inline uint32 hashing_table_load_factor_calculate(struct hashing_table *hash);

#endif
