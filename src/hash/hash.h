#ifndef HAVE_HASH_H
#define HAVE_HASH_H

#define DEFAULT_CHAIN_HASH_SIZE 11u
#define DEFAULT_LOAD_FACTOR     72u /* Means 0.72 or 72% */

#define OPEN_ADDRESSING_HASH_LOAD_FACTOR 50u

extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
extern struct doubly_linked_list * doubly_linked_list_node_remove(struct doubly_linked_list **node);

/* SEPARATE CHAIN HASH */
struct separate_chain_hash * separate_chain_hash_create(uint32 size);
void separate_chain_hash_destroy(struct separate_chain_hash **hash);
uint32 separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash);
void separate_chain_hash_insert(struct separate_chain_hash **hash, void *key);
void * separate_chain_hash_remove(struct separate_chain_hash *hash, void *key);
void * separate_chain_hash_find(struct separate_chain_hash *hash, void *key);
struct separate_chain_hash * separate_chain_hash_rehashing(struct separate_chain_hash **hash);

static inline void separate_chain_hash_chain_rehashing(struct doubly_linked_list *link, struct separate_chain_hash *hash);
static inline void separate_chain_hash_space_rehashing(struct separate_chain_hash *to, struct separate_chain_hash *from);
static inline struct doubly_linked_list ** separate_chain_hash_space(struct separate_chain_hash *hash);
static inline void separate_chain_hash_chain_destroy(struct separate_chain_hash *hash);
static inline struct doubly_linked_list * separate_chain_hash_chain_head(struct separate_chain_hash *hash, uint32 index);
static inline void separate_chain_hash_chain_head_set(struct separate_chain_hash *hash, uint32 index, struct doubly_linked_list *val);
static inline uint32 separate_chain_hash_index_calculate(struct separate_chain_hash *hash, void *key);
/* END OF SEPARATE CHAIN HASH */

#endif
