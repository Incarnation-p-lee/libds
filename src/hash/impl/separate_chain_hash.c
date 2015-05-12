struct separate_chain_hash *
separate_chain_hash_create(uint32 size)
{
    struct separate_chain_hash *hash;

    hash = malloc_ds(sizeof(*hash));
    if (!hash) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        if (0 == size) {
            size = DEFAULT_CHAIN_HASH_SIZE;
            pr_log_warn("Hash table size not specified, use default size.\n");
        }

        hash->size = size;
        hash->load_factor = DEFAULT_LOAD_FACTOR;
        hash->func = hashing_function_polynomial;
        separate_chain_hash_chain_initial(hash);
    }

    return hash;
}

static inline void
separate_chain_hash_chain_initial(struct separate_chain_hash *hash)
{
    struct doubly_linked_list **iter;

    assert(NULL != hash);

    hash->space = malloc_ds(sizeof(**hash->space) * hash->size);
    if (!hash->space) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        iter = hash->space;
        while (iter < hash->space + hash->size) {
            *iter++ = NULL;
        }
    }

    return;
}

void
separate_chain_hash_destroy(struct separate_chain_hash **hash)
{
    struct doubly_linked_list **iter;

    if (!hash || !*hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = (*hash)->space;
        if (!iter) {
            pr_log_warn("Destroyed data structure.\n");
        } else {
            while (iter < (*hash)->space + (*hash)->size) {
                if (*iter) {
                   doubly_linked_list_destroy(iter);
                   assert(NULL == *iter);
                }
                iter++;
            }
            free_ds((*hash)->space);
        }
        free_ds((*hash));
        *hash = NULL;
    }

    return;
}

uint32
separate_chain_hash_load_factor_calculate(struct separate_chain_hash *hash)
{
    uint32 retval;
    struct doubly_linked_list **iter;

    retval = 0u;
    if (!hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = hash->space;
        if (!iter) {
            pr_log_warn("Destroyed data structure.\n");
        } else {
            retval = 0u;
            while (iter < hash->space + hash->size) {
                if (NULL != *iter) {
                    retval++;
                }
                iter++;
            }
        }

        retval = (retval * 100 / hash->size);
    }

    return retval;
}

void
separate_chain_hash_insert(struct separate_chain_hash **hash, void *key)
{
    uint32 factor;
    struct doubly_linked_list **head;
    struct doubly_linked_list *node;
    struct separate_chain_hash *tmp;

    if (!hash || !*hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        tmp = *hash;
        factor = separate_chain_hash_load_factor_calculate(tmp);
        if (factor > separate_chain_hash_load_factor(tmp)) {
            pr_log_info("Reach the load factor limit, will rehashing.\n");
            tmp = separate_chain_hash_rehashing(&tmp);
            *hash = tmp;
        }

        head = tmp->space + (ptrdiff_t)tmp->func(key, tmp->size);
        if (!*head) {
            /* Empty linked list */
            *head = doubly_linked_list_node_create(key, 0x0u);
        } else {
            node = doubly_linked_list_node_create(key, 0x0u);
            doubly_linked_list_node_insert_after(*head, node);
        }
    }

    return;
}

void *
separate_chain_hash_remove(struct separate_chain_hash *hash, void *key)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *iter;
    void *retval;

    if (!hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        retval = NULL;
        head = hash->space[hash->func(key, hash->size)];
        if (!head) {
            retval = NULL;
        } else {
            iter = head;
            do {
                if (key == doubly_linked_list_node_val(iter)) {
                    retval = key;
                    doubly_linked_list_node_remove(iter);
                    break;
                }
                iter = doubly_linked_list_node_next(iter);
            } while (iter != head);

            if (iter == head) {
                hash->space[hash->func(key, hash->size)] = NULL;
            }
        }

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }
        return retval;
    }
}

void *
separate_chain_hash_find(struct separate_chain_hash *hash, void *key)
{
    struct doubly_linked_list *head;
    struct doubly_linked_list *iter;
    void *retval;

    retval = NULL;
    if (!hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        head = hash->space[hash->func(key, hash->size)];
        if (!head) {
            retval = NULL;
        } else {
            iter = head;
            do {
                if (key == doubly_linked_list_node_val(iter)) {
                    retval = key;
                    break;
                }
                iter = doubly_linked_list_node_next(iter);
            } while (iter != head);
        }

        if (NULL == retval) {
            pr_log_info("Not such a key in given hash.\n");
        }
    }

    return retval;
}

static inline void
separate_chain_hash_chain_rehashing(struct doubly_linked_list *link,
    struct separate_chain_hash *hash)
{
    void *tmp;
    struct doubly_linked_list *iter;

    assert(NULL != link);
    assert(NULL != hash);

    iter = link;
    do {
        tmp = doubly_linked_list_node_val(iter);
        separate_chain_hash_insert(&hash, tmp);
        iter = doubly_linked_list_node_next(iter);
    } while (iter != link);

    return;
}

static inline void
separate_chain_hash_space_rehashing(struct separate_chain_hash *to,
    struct separate_chain_hash *from)
{
    struct doubly_linked_list **iter;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != from->space);

    iter = from->space;
    while (iter < from->space + from->size) {
        if (*iter) {
            separate_chain_hash_chain_rehashing(*iter, to);
        }
        iter++;
    }

    return;
}

struct separate_chain_hash *
separate_chain_hash_rehashing(struct separate_chain_hash **hash)
{
    struct separate_chain_hash *new;
    uint32 resize;

    new = NULL;
    if (!hash || !*hash) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        resize = prime_numeral_next(separate_chain_hash_size(*hash));
        new = separate_chain_hash_create(resize);
        separate_chain_hash_space_rehashing(new, *hash);
        separate_chain_hash_destroy(hash);
        *hash = NULL;
    }

    return new;
}

