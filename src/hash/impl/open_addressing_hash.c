uint32
open_addressing_hash_size(s_open_addressing_hash_t *hash)
{
    if (!open_addressing_hash_structure_legal_p(hash)) {
        return HASH_SIZE_INVALID;
    } else {
        return hash->table->size;
    }
}

uint32
open_addressing_hash_load_factor(s_open_addressing_hash_t *hash)
{
    if (!open_addressing_hash_structure_legal_p(hash)) {
        return HASH_LD_FTR_INVALID;
    } else {
        return hash->table->load_factor;
    }
}

static inline s_open_addressing_hash_t *
open_addressing_hash_create_i(uint32 size)
{
    s_open_addressing_hash_t *hash;

    hash = memory_cache_allocate(sizeof(*hash));
    if (complain_zero_size_p(size)) {
        size = SPT_CHN_HASH_SIZE_DFT;
        pr_log_warn("Hash table size not specified, use default size.\n");
    }

    /* open addressing requires prime table size. */
    hash->table = hashing_table_create(prime_numeral_next(size));
    hash->table->load_factor = OPN_ADDR_HASH_LOAD_FTR;
    hash->table->func = &hashing_function_open_addressing;

    return hash;
}


s_open_addressing_hash_t *
open_addressing_hash_create(uint32 size)
{
    return open_addressing_hash_create_i(size);
}

static inline bool
open_addressing_hash_structure_legal_p(s_open_addressing_hash_t *hash)
{
    if (NULL_PTR_P(hash)) {
        return false;
    } else {
        return hashing_table_structure_legal_p(hash->table);
    }
}

static inline void
open_addressing_hash_destroy_i(s_open_addressing_hash_t *hash)
{
    assert_exit(open_addressing_hash_structure_legal_p(hash));

    hashing_table_destroy(&hash->table);
    memory_cache_free(hash);
}

void
open_addressing_hash_destroy(s_open_addressing_hash_t **hash)
{
    if (NULL_PTR_P(hash)) {
        return;
    } else if (open_addressing_hash_structure_legal_p(*hash)) {
        open_addressing_hash_destroy_i(*hash);
        *hash = NULL;
    }
}

uint32
open_addressing_hash_load_factor_calculate(s_open_addressing_hash_t *hash)
{
    if (!open_addressing_hash_structure_legal_p(hash)) {
        return 0u;
    } else {
        return hashing_table_load_factor_calculate(hash->table);
    }
}

static inline uint32
open_addressing_hash_index_calculate(s_open_addressing_hash_t *hash,
    void *key, uint32 counter)
{
    uint32 index;
    assert_exit(open_addressing_hash_structure_legal_p(hash));
    assert_exit(counter < open_addressing_hash_limit(hash));

    index = hash->table->open_addressing(key, hash->table->size, counter);

    assert_exit(index < hash->table->size);
    return index;
}

void *
open_addressing_hash_insert_i(s_open_addressing_hash_t *hash, void *key)
{
    uint32 i;
    uint32 index;
    uint32 factor;

    assert_exit(!NULL_PTR_P(key));
    assert_exit(open_addressing_hash_structure_legal_p(hash));

    factor = open_addressing_hash_load_factor_calculate(hash);
    if (factor >= hash->table->load_factor) {
        pr_log_info("Reach the load factor limit, will rehashing.\n");
        open_addressing_hash_rehashing_i(hash);
    }

    i = 0;
    do {
        index = open_addressing_hash_index_calculate(hash, key, i++);
    } while (hash->table->space[index]);

    hash->table->space[index] = key;
    return key;
}

void *
open_addressing_hash_insert(s_open_addressing_hash_t *hash, void *key)
{
    if (!open_addressing_hash_structure_legal_p(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
        return PTR_INVALID;
    } else {
        return open_addressing_hash_insert_i(hash, key);
    }
}

void *
open_addressing_hash_remove(s_open_addressing_hash_t *hash, void *key)
{
    uint32 index;

    if (!open_addressing_hash_structure_legal_p(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
        return PTR_INVALID;
    } else {
        index = open_addressing_hash_find_index(hash, key);
        if (HASH_IDX_INVALID == index) {
            return NULL;
        } else {
            hash->table->space[index] = NULL;
            return key;
        }
    }
}

static inline uint32
open_addressing_hash_find_index(s_open_addressing_hash_t *hash, void *key)
{
    uint32 i;
    uint32 index;

    assert_exit(!NULL_PTR_P(key));
    assert_exit(open_addressing_hash_structure_legal_p(hash));

    i = 0;
    do {
        index = open_addressing_hash_index_calculate(hash, key, i++);
        if (key == hash->table->space[index]) {
            return index;
        }
    } while (hash->table->space[index]);

    pr_log_info("Not such a key in given hash.\n");
    return HASH_IDX_INVALID;
}

void *
open_addressing_hash_find(s_open_addressing_hash_t *hash, void *key)
{
    if (!open_addressing_hash_structure_legal_p(hash)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(key)) {
        return PTR_INVALID;
    } else if (HASH_IDX_INVALID == open_addressing_hash_find_index(hash, key)) {
        return NULL;
    } else {
        return key;
    }
}

static inline void
open_addressing_hash_rehashing_i(s_open_addressing_hash_t *hash)
{
    void **i;
    uint32 new_size;
    s_open_addressing_hash_t *new_hash;

    assert_exit(open_addressing_hash_structure_legal_p(hash));

    new_size = prime_numeral_next(hash->table->size + 1);
    new_hash = open_addressing_hash_create_i(new_size);

    i = hash->table->space;
    while (i < hash->table->space + hash->table->size) {
        if (*i) {
            open_addressing_hash_insert_i(new_hash, *i);
        }
        i++;
    }

    /* swap space of hash and new */
    i = hash->table->space;
    hash->table->space = new_hash->table->space;
    new_hash->table->space = i;

    /* swap size of hash and new */
    new_hash->table->size = hash->table->size;
    hash->table->size = new_size;

    open_addressing_hash_destroy_i(new_hash);
}

void
open_addressing_hash_rehashing(s_open_addressing_hash_t *hash)
{
    if (open_addressing_hash_structure_legal_p(hash)) {
        open_addressing_hash_rehashing_i(hash);
    }
}

