static inline s_binary_heap_t *
binary_heap_create(uint32 capacity)
{
    s_heap_data_t **i;
    s_binary_heap_t *heap;

    if (complain_zero_size_p(capacity)) {
        capacity = DEFAULT_BINARY_HEAP_SIZE;
    }

    heap = memory_cache_allocate(sizeof(*heap));

    ALIAS_BASE(heap) = memory_cache_allocate(sizeof(*i) * (capacity + 1));
    ALIAS_CAPACITY(heap) = capacity;
    ALIAS_SIZE(heap) = 0;

    i = ALIAS_BASE(heap);

    while (i < heap->base + u_offset(capacity, 1)) {
        *i++ = NULL;
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

    if (ALIAS_SIZE(heap) == 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_full_p(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    if (ALIAS_SIZE(heap) == ALIAS_CAPACITY(heap)) {
        return true;
    } else {
        return false;
    }
}

static inline void
binary_heap_cleanup(s_binary_heap_t *heap)
{
    uint32 index;

    assert_exit(binary_heap_legal_p(heap));

    index = HEAP_INDEX_FIRST;

    while (index <= INDEX_LAST(heap)) {
        memory_cache_free(ALIAS_DATA(heap, index));
        ALIAS_DATA(heap, index) = NULL;

        index++;
    }

    ALIAS_SIZE(heap) = 0;
}

static inline void *
binary_heap_root(s_binary_heap_t *heap)
{
    assert_exit(binary_heap_legal_p(heap));

    return ALIAS_VAL(heap, HEAP_INDEX_ROOT);
}

static inline void
binary_heap_capacity_extend(s_binary_heap_t *heap)
{
    uint32 size;
    s_heap_data_t **new;

    assert_exit(binary_heap_legal_p(heap));

    size = sizeof(ALIAS_DATA(heap, 0)) * u_offset(ALIAS_CAPACITY(heap) * 2, 1);
    new = memory_cache_allocate(size);
    dp_memset(new, 0, size);

    size = sizeof(ALIAS_DATA(heap, 0)) * u_offset(ALIAS_CAPACITY(heap), 1);
    dp_memcpy(new, ALIAS_BASE(heap), size);
    memory_cache_free(ALIAS_BASE(heap));

    ALIAS_BASE(heap) = new;
    ALIAS_CAPACITY(heap) *= 2;

    assert_exit(binary_heap_legal_p(heap));
}

static inline void
binary_heap_node_create_by_index(s_binary_heap_t *heap, uint32 index,
    sint64 nice, void *val)
{
    assert_exit(NULL_PTR_P(ALIAS_DATA(heap, index)));
    assert_exit(binary_heap_nice_legal_p(nice));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_legal_p(heap));

    ALIAS_DATA(heap, index) = binary_heap_node_create(nice, val);
}

static inline s_heap_data_t *
binary_heap_node_create(sint64 nice, void *val)
{
    s_heap_data_t *data;

    assert_exit(binary_heap_nice_legal_p(nice));

    data = memory_cache_allocate(sizeof(*data));

    DATA_VAL(data) = val;
    DATA_NICE(data) = nice;

    return data;
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

    while ((*order)(heap, index, nice, &index_next) == false) {
        ALIAS_DATA(heap, index) = ALIAS_DATA(heap, index_next);

        index = index_next;
    }

    ALIAS_DATA(heap, index) = NULL;

    return index;
}

static inline bool
binary_heap_child_exist_p(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    if (INDEX_LEFT(index) <= INDEX_LAST(heap)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
binary_heap_child_not_exist_p(s_binary_heap_t *heap, uint32 index)
{
    return !binary_heap_child_exist_p(heap, index);
}

static inline uint32
binary_heap_child_min_nice_index(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    if (binary_heap_child_not_exist_p(heap, index)) {
        return HEAP_INDEX_INVALID;
    } else if (INDEX_RIGHT(index) > INDEX_LAST(heap)) {
        return INDEX_LEFT(index);
    } else if (ALIAS_LEFT_NICE(heap, index) > ALIAS_RIGHT_NICE(heap, index)) {
        return INDEX_RIGHT(index);
    } else {
        return INDEX_LEFT(index);
    }
}

static inline uint32
binary_heap_child_max_nice_index(s_binary_heap_t *heap, uint32 index)
{
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    if (binary_heap_child_not_exist_p(heap, index)) {
        return HEAP_INDEX_INVALID;
    } else if (INDEX_RIGHT(index) > INDEX_LAST(heap)) {
        return INDEX_LEFT(index);
    } else if (ALIAS_LEFT_NICE(heap, index) < ALIAS_RIGHT_NICE(heap, index)) {
        return INDEX_RIGHT(index);
    } else {
        return INDEX_LEFT(index);
    }
}

static inline uint32
binary_heap_gdp_randchild_min_nice_index(s_binary_heap_t *heap, uint32 index)
{
    uint32 begin;
    uint32 retval;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_depth_even_p(heap, index));

    if (binary_heap_child_not_exist_p(heap, index)) {
        return HEAP_INDEX_INVALID;
    } else if (INDEX_L_LEFT(index) > INDEX_LAST(heap)) {
        return binary_heap_child_min_nice_index(heap, index);
    } else {
        begin = INDEX_L_LEFT(index);
        retval = binary_heap_serial_small_nice_index(heap, begin, 4);

        if (ALIAS_NICE(heap, INDEX_RIGHT(index)) < ALIAS_NICE(heap, retval)) {
            return INDEX_RIGHT(index);
        } else {
            return retval;
        }
    }
}

static inline uint32
binary_heap_gdp_randchild_max_nice_index(s_binary_heap_t *heap, uint32 index)
{
    uint32 begin;
    uint32 retval;

    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));
    assert_exit(binary_heap_depth_odd_p(heap, index));

    if (!binary_heap_child_exist_p(heap, index)) {
        return HEAP_INDEX_INVALID;
    } else if (INDEX_L_LEFT(index) > INDEX_LAST(heap)) {
        return binary_heap_child_max_nice_index(heap, index);
    } else {
        begin = INDEX_L_LEFT(index);
        retval = binary_heap_serial_big_nice_index(heap, begin, 4);

        if (ALIAS_NICE(heap, INDEX_RIGHT(index)) > ALIAS_NICE(heap, retval)) {
            return INDEX_RIGHT(index);
        } else {
            return retval;
        }
    }
}

static inline uint32
binary_heap_serial_small_nice_index(s_binary_heap_t *heap, uint32 index,
    uint32 count)
{
    uint32 small_index, rest;

    assert_exit(!complain_zero_size_p(count));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    small_index = index;
    rest = INDEX_LAST(heap) - index + 1;
    count = count > rest ? rest : count;

    while (count--) {
        if (ALIAS_NICE(heap, index) < ALIAS_NICE(heap, small_index)) {
            small_index = index;
        }

        index++;
    }

    return small_index;
}

static inline uint32
binary_heap_serial_big_nice_index(s_binary_heap_t *heap, uint32 index,
    uint32 count)
{
    uint32 big_index, rest;

    assert_exit(!complain_zero_size_p(count));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(heap, index));

    big_index = index;
    rest = INDEX_LAST(heap) - index + 1;
    count = count > rest ? rest : count;

    while (count--) {
        if (ALIAS_NICE(heap, index) > ALIAS_NICE(heap, big_index)) {
            big_index = index;
        }

        index++;
    }

    return big_index;
}

static inline void
binary_heap_insert(s_binary_heap_t *heap, void *val, sint64 nice, void *order)
{
    uint32 index;

    assert_exit(binary_heap_nice_legal_p(nice));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(order));

    if (binary_heap_full_p(heap)) {
        binary_heap_capacity_extend(heap);
    }

    ALIAS_SIZE(heap) += 1;
    ALIAS_DATA(heap, ALIAS_SIZE(heap)) = NULL;

    index = binary_heap_reorder(heap, ALIAS_SIZE(heap), nice, order);
    binary_heap_node_create_by_index(heap, index, nice, val);

    assert_exit(binary_heap_ordered_p(heap, order));
}

static inline void
binary_heap_data_destroy(s_heap_data_t *data)
{
    assert_exit(NON_NULL_PTR_P(data));

    memory_cache_free(data);
}

static inline void *
binary_heap_remove_root(s_binary_heap_t *heap, void *order)
{
    sint64 nice;
    void *retval;
    s_heap_data_t *last;
    uint32 index, index_last;

    assert_exit(!binary_heap_empty_p(heap));
    assert_exit(binary_heap_legal_p(heap));
    assert_exit(binary_heap_valid_ordered_func_ptr_p(order));

    index_last = INDEX_LAST(heap);
    retval = DATA_VAL(ALIAS_DATA(heap, HEAP_INDEX_ROOT));
    binary_heap_data_destroy(ALIAS_DATA(heap, HEAP_INDEX_ROOT));
    ALIAS_SIZE(heap) -= 1;

    if (index_last != HEAP_INDEX_ROOT) {
        nice = ALIAS_NICE(heap, index_last);
        last = ALIAS_DATA(heap, index_last);

        ALIAS_DATA(heap, index_last) = NULL;

        index = binary_heap_reorder(heap, HEAP_INDEX_ROOT, nice, order);
        assert_exit(ALIAS_DATA(heap, index) == NULL);

        ALIAS_DATA(heap, index) = last;
    }

    assert_exit(binary_heap_ordered_p(heap, order));

    return retval;
}

static inline uint32
binary_heap_depth(uint32 index)
{
    uint32 depth;

    assert_exit(index != HEAP_INDEX_INVALID);

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

    if (index == HEAP_INDEX_INVALID  || index > INDEX_LAST(heap)) {
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
    } else if (NULL_PTR_P(ALIAS_BASE(heap))) {
        return false;
    } else if (complain_zero_size_p(ALIAS_CAPACITY(heap))) {
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
binary_heap_find_index(s_binary_heap_t *heap, void *val)
{
    uint32 i, limit;

    assert_exit(binary_heap_legal_p(heap));

    i = HEAP_INDEX_ROOT;
    limit = binary_heap_index_limit(heap);

    while (i < limit) {
        if (val == ALIAS_VAL(heap, i)) {
            return i;
        }

        i++;
    }

    return HEAP_INDEX_INVALID;
}

