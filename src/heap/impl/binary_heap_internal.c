static inline s_binary_heap_t *
binary_heap_create(uint32 capacity)
{
    s_binary_heap_t *heap;
    struct heap_data **iterator;

    if (complain_zero_size_p(capacity)) {
        capacity = DEFAULT_BINARY_HEAP_SIZE;
    }

    heap = memory_cache_allocate(sizeof(*heap));
    heap->base = memory_cache_allocate(sizeof(*iterator) * (capacity + 1));

    heap->capacity = capacity;
    heap->size = 0;

    iterator = heap->base;
    while (iterator < heap->base + u_offset(capacity, 1)) {
        *iterator++ = NULL;
    }

    return heap;
}

static inline void
binary_heap_destroy(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    binary_heap_cleanup(heap);
    memory_cache_free(ALIAS_BASE(heap));
    memory_cache_free(heap);
}

static inline bool
binary_heap_empty_p(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return heap->size == 0 ? true : false;
}

static inline uint32
binary_heap_size(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return heap->size;
}

static inline bool
binary_heap_full_p(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return heap->size == heap->capacity ? true : false;
}

static inline void
binary_heap_cleanup(s_binary_heap_t *heap)
{
    register uint32 index;

    assert_exit(binary_heap_legal_p(heap));

    index = INDEX_FIRST;

    while (index <= INDEX_LAST(heap)) {
        memory_cache_free(HEAP_DATA(heap, index));
        HEAP_DATA(heap, index) = NULL;
        index++;
    }

    heap->size = 0;
}

static inline void *
binary_heap_root(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return HEAP_VAL(heap, INDEX_ROOT);
}

static inline void
binary_heap_capacity_extend(s_binary_heap_t *heap)
{
    struct heap_data **new;
    uint32 size;

    assert_exit(binary_heap_legal_p(heap));

    size = sizeof(heap->base[0]) * u_offset(heap->capacity * 2, 1);
    new = memory_cache_allocate(size);
    memset(new, 0, size);

    size = sizeof(heap->base[0]) * u_offset(heap->capacity, 1);
    dp_memcpy(new, heap->base, size);

    heap->capacity = heap->capacity * 2;
    memory_cache_free(heap->base);
    heap->base = new;

    assert_exit(binary_heap_legal_p(heap));
}

static inline void
binary_heap_node_create_by_index(s_binary_heap_t *heap, uint32 index,
    sint64 nice, void *val)
{
    assert_exit(NULL_PTR_P(heap->base[index]));
    assert_exit(binary_heap_nice_legal_p(nice));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_legal_p(heap));

    HEAP_DATA(heap, index) = binary_heap_node_create(nice, val);
}

static inline struct heap_data *
binary_heap_node_create(sint64 nice, void *val)
{
    struct heap_data *retval;

    assert_exit(binary_heap_nice_legal_p(nice));

    retval = memory_cache_allocate(sizeof(*retval));
    retval->nice = nice;
    retval->val = val;

    return retval;
}

/*
 * index      - specific the empty hole index of heap.
 * nice       - nice value of percolate up.
 * heap_order - function pointer of heap order, should be one of function
 *              in file binary_heap_order.c.
 * RETURN the re-ordered index of heap with that nice.
 */
static inline uint32
binary_heap_reorder(s_binary_heap_t *heap, uint32 index, sint64 nice,
    void *heap_order)
{
    uint32 index_next;
    bool (*order)(s_binary_heap_t *, uint32, sint64, uint32 *);

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_nice_legal_p(nice));

    order = heap_order;

    while (!(*order)(heap, index, nice, &index_next)) {
        HEAP_DATA(heap, index) = HEAP_DATA(heap, index_next);
        index = index_next;
    }

    HEAP_DATA(heap, index) = NULL;
    return index;
}

static inline bool
binary_heap_child_exist_p(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    return INDEX_L_CHILD(index) <= INDEX_LAST(heap) ? true : false;
}

static inline uint32
binary_heap_child_min_nice_index(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    if (!binary_heap_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_R_CHILD(index) > INDEX_LAST(heap)) {
        return INDEX_L_CHILD(index);
    } else if (HEAP_L_CHILD_NICE(heap, index) > HEAP_R_CHILD_NICE(heap, index)) {
        return INDEX_R_CHILD(index);
    } else {
        return INDEX_L_CHILD(index);
    }
}

static inline uint32
binary_heap_child_max_nice_index(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    if (!binary_heap_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_R_CHILD(index) > INDEX_LAST(heap)) {
        return INDEX_L_CHILD(index);
    } else if (HEAP_L_CHILD_NICE(heap, index) < HEAP_R_CHILD_NICE(heap, index)) {
        return INDEX_R_CHILD(index);
    } else {
        return INDEX_L_CHILD(index);
    }
}

static inline uint32
binary_heap_gdp_randchild_min_nice_index(s_binary_heap_t *heap, uint32 index)
{
    uint32 begin;
    uint32 ret_index;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_depth_even_p(heap, index));

    if (!binary_heap_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_LL_CHILD(index) > INDEX_LAST(heap)) {
        return binary_heap_child_min_nice_index(heap, index);
    } else {
        begin = INDEX_LL_CHILD(index);
        ret_index = binary_heap_serial_small_nice_index(heap, begin, 4);

        if (HEAP_NICE(heap, INDEX_R_CHILD(index))
            < HEAP_NICE(heap, ret_index)) {
            return INDEX_R_CHILD(index);
        } else {
            return ret_index;
        }
    }
}

static inline uint32
binary_heap_gdp_randchild_max_nice_index(s_binary_heap_t *heap, uint32 index)
{
    uint32 begin;
    uint32 ret_index;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_depth_odd_p(heap, index));

    if (!binary_heap_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_LL_CHILD(index) > INDEX_LAST(heap)) {
        return binary_heap_child_max_nice_index(heap, index);
    } else {
        begin = INDEX_LL_CHILD(index);
        ret_index = binary_heap_serial_big_nice_index(heap, begin, 4);

        if (HEAP_NICE(heap, INDEX_R_CHILD(index))
            > HEAP_NICE(heap, ret_index)) {
            return INDEX_R_CHILD(index);
        } else {
            return ret_index;
        }
    }
}

static inline uint32
binary_heap_serial_small_nice_index(s_binary_heap_t *heap,
    uint32 index, uint32 count)
{
    uint32 small_index;
    uint32 rest;

    assert_exit(!complain_zero_size_p(count));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    small_index = index;
    rest = INDEX_LAST(heap) - index + 1;
    count = count > rest ? rest : count;

    while (count--) {
        if (HEAP_NICE(heap, index) < HEAP_NICE(heap, small_index)) {
            small_index = index;
        }
        index++;
    }

    return small_index;
}

static inline uint32
binary_heap_serial_big_nice_index(s_binary_heap_t *heap,
    uint32 index, uint32 count)
{
    uint32 big_index;
    uint32 rest;

    assert_exit(!complain_zero_size_p(count));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    big_index = index;
    rest = INDEX_LAST(heap) - index + 1;
    count = count > rest ? rest : count;

    while (count--) {
        if (HEAP_NICE(heap, index) > HEAP_NICE(heap, big_index)) {
            big_index = index;
        }
        index++;
    }

    return big_index;
}

static inline void
binary_heap_insert(s_binary_heap_t *heap, void *val, sint64 nice,
    void *ordering)
{
    uint32 index;

    assert_exit(binary_heap_nice_legal_p(nice));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(ordering));

    if (binary_heap_full_p(heap)) {
        pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
        binary_heap_capacity_extend(heap);
    }

    heap->size++;
    HEAP_DATA(heap, heap->size) = NULL;

    index = binary_heap_reorder(heap, heap->size, nice, ordering);
    binary_heap_node_create_by_index(heap, index, nice, val);

    assert_exit(binary_heap_ordered_p(heap, ordering));
}

static inline void
binary_heap_data_destroy(struct heap_data *data)
{
    assert_exit(NON_NULL_PTR_P(data));

    memory_cache_free(data);
}

static inline void *
binary_heap_remove_root(s_binary_heap_t *heap, void *order)
{
    sint64 nice;
    uint32 index;
    uint32 index_last;
    struct heap_data *last;
    void *retval;

    assert_exit(!binary_heap_empty_p(heap));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(order));

    index_last = INDEX_LAST(heap);
    retval = DATA_VAL(HEAP_DATA(heap, INDEX_ROOT));
    binary_heap_data_destroy(HEAP_DATA(heap, INDEX_ROOT));
    heap->size--;

    if (INDEX_ROOT != index_last) {
        nice = HEAP_NICE(heap, index_last);
        last = HEAP_DATA(heap, index_last);

        HEAP_DATA(heap, index_last) = NULL;

        index = binary_heap_reorder(heap, INDEX_ROOT, nice, order);
        assert_exit(NULL == HEAP_DATA(heap, index));

        HEAP_DATA(heap, index) = last;
    }

    assert_exit(binary_heap_ordered_p(heap, order));
    return retval;
}

static inline uint32
binary_heap_depth(uint32 index)
{
    uint32 depth;

    assert_exit(INDEX_INVALID != index);

    depth = 0;

    while (index >= (1u << (depth + 1))) {
        depth++;
    }

    return depth;
}

static inline bool
binary_heap_nice_legal_p(sint64 nice)
{
    if (nice > HEAP_NICE_LOWER_LMT && nice < HEAP_NICE_UPPER_LMT) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_nice_illegal_p(sint64 nice)
{
    return !binary_heap_nice_legal_p(nice);
}

static inline bool
binary_heap_index_legal_p(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));

    if (INDEX_INVALID == index || index > INDEX_LAST(heap)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_heap_index_illegal_p(s_binary_heap_t *heap, uint32 index)
{
    return !binary_heap_index_legal_p(heap, index);
}

static inline bool
binary_heap_legal_p(s_binary_heap_t *heap)
{
    if (NULL_PTR_P(heap)) {
        return false;
    } else if (NULL_PTR_P(heap->base)) {
        return false;
    } else if (complain_zero_size_p(heap->capacity)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_heap_illegal_p(s_binary_heap_t *heap)
{
    return !binary_heap_legal_p(heap);
}

static inline uint32
binary_heap_index_limit(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return INDEX_LAST(heap) + 1;
}

static inline uint32
binary_heap_index_last(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return heap->size;
}

static inline uint32
binary_heap_find_index(s_binary_heap_t *heap, void *val)
{
    uint32 i, limit;

    assert_exit(binary_heap_legal_p(heap));

    i = INDEX_ROOT;
    limit = binary_heap_index_limit(heap);

    while (i < limit) {
        if (val == HEAP_VAL(heap, i)) {
            return i;
        }

        i++;
    }

    return INDEX_INVALID;
}

