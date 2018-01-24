static inline bool
maximal_heap_legal_ip(s_maximal_heap_t *heap)
{
    if (NULL_PTR_P(heap)) {
        return false;
    } else if (binary_heap_illegal_p(HEAP_ALIAS(heap))) {
        return false;
    } else {
        return true;
    }
}

static inline bool
maximal_heap_illegal_ip(s_maximal_heap_t *heap)
{
    return !maximal_heap_legal_ip(heap);
}

bool
maximal_heap_legal_p(s_maximal_heap_t *heap)
{
    return maximal_heap_legal_ip(heap);
}

bool
maximal_heap_illegal_p(s_maximal_heap_t *heap)
{
    return maximal_heap_illegal_ip(heap);
}

uint32
maximal_heap_index_limit(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return HEAP_INDEX_INVALID;
    } else {
        return binary_heap_index_limit(HEAP_ALIAS(heap));
    }
}

uint32
maximal_heap_size(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return SIZE_INVALID;
    } else {
        return ALIAS_SIZE(HEAP_ALIAS(heap));
    }
}

sint64
maximal_heap_nice(s_maximal_heap_t *heap, uint32 index)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return HEAP_NICE_INVALID;
    } else if (index == HEAP_INDEX_INVALID) {
        return HEAP_NICE_INVALID;
    } else if (index >= binary_heap_index_limit(HEAP_ALIAS(heap))) {
        return HEAP_NICE_INVALID;
    } else {
        return ALIAS_NICE(HEAP_ALIAS(heap), index);
    }
}

void *
maximal_heap_val(s_maximal_heap_t *heap, uint32 index)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (index == HEAP_INDEX_INVALID) {
        return PTR_INVALID;
    } else if (index >= binary_heap_index_limit(HEAP_ALIAS(heap))) {
        return PTR_INVALID;
    } else {
        return ALIAS_VAL(HEAP_ALIAS(heap), index);
    }
}

static inline bool
maximal_heap_ordered_ip(s_maximal_heap_t *heap)
{
    s_binary_heap_t *alias;

    assert_exit(maximal_heap_legal_ip(heap));

    alias = HEAP_ALIAS(heap);

    return binary_heap_ordered_p(alias, &binary_heap_maximal_ordered_p);
}

bool
maximal_heap_ordered_p(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return false;
    } else {
        return maximal_heap_ordered_ip(heap);
    }
}

s_maximal_heap_t *
maximal_heap_create(uint32 capacity)
{
    s_maximal_heap_t *heap;

    heap = memory_cache_allocate(sizeof(*heap));
    HEAP_ALIAS(heap) = binary_heap_create(capacity);

    return heap;
}

void
maximal_heap_destroy(s_maximal_heap_t **heap)
{
    if (NULL_PTR_P(heap)) {
        return;
    } else if (MAXIMAL_HEAP_ILLEGAL_P(*heap)) {
        return;
    } else {
        binary_heap_destroy(HEAP_ALIAS(*heap));
        memory_cache_free(*heap);

        *heap = NULL;
    }
}

bool
maximal_heap_empty_p(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return false;
    } else {
        return binary_heap_empty_p(HEAP_ALIAS(heap));
    }
}

bool
maximal_heap_full_p(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return true;
    } else {
        return binary_heap_full_p(HEAP_ALIAS(heap));
    }
}

uint32
maximal_heap_index_last(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return HEAP_INDEX_INVALID;
    } else {
        return INDEX_LAST(HEAP_ALIAS(heap));
    }
}

void
maximal_heap_cleanup(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return;
    } else {
        binary_heap_cleanup(HEAP_ALIAS(heap));
    }
}

void *
maximal_heap_get_max(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return binary_heap_root(HEAP_ALIAS(heap));
    }
}

void
maximal_heap_insert(s_maximal_heap_t *heap, void *val, sint64 nice)
{
    s_binary_heap_t *alias;

    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return;
    } if (binary_heap_nice_illegal_p(nice)) {
        return;
    } else {
        alias = HEAP_ALIAS(heap);
        binary_heap_insert(alias, val, nice, &binary_heap_maximal_ordered_p);
    }
}

static inline void *
maximal_heap_remove_i(s_maximal_heap_t *heap, uint32 idx)
{
    sint64 nice;
    s_binary_heap_t *alias;
    s_heap_data_t *data_tmp;

    assert_exit(idx != HEAP_INDEX_ROOT);
    assert_exit(maximal_heap_legal_ip(heap));
    assert_exit(!binary_heap_empty_p(HEAP_ALIAS(heap)));
    assert_exit(binary_heap_index_legal_p(HEAP_ALIAS(heap), idx));

    alias = HEAP_ALIAS(heap);
    data_tmp = ALIAS_DATA(alias, idx);
    ALIAS_DATA(alias, idx) = NULL;

    /* Percolate current index node to root, then remove the root. */
    nice = ALIAS_NICE(alias, HEAP_INDEX_ROOT) + 1;
    idx = binary_heap_reorder(alias, idx, nice, &binary_heap_maximal_ordered_p);

    assert_exit(idx == HEAP_INDEX_ROOT);
    assert_exit(NULL_PTR_P(ALIAS_DATA(alias, HEAP_INDEX_ROOT)));

    ALIAS_DATA(alias, HEAP_INDEX_ROOT) = data_tmp;

    return binary_heap_remove_root(alias, &binary_heap_maximal_ordered_p);
}

void *
maximal_heap_remove(s_maximal_heap_t *heap, uint32 index)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return PTR_INVALID;
    } else if (index == HEAP_INDEX_ROOT) {
        return binary_heap_remove_root(HEAP_ALIAS(heap),
            &binary_heap_maximal_ordered_p);
    } else {
        return maximal_heap_remove_i(heap, index);
    }
}

void *
maximal_heap_remove_max(s_maximal_heap_t *heap)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (binary_heap_empty_p(HEAP_ALIAS(heap))) {
        return PTR_INVALID;
    } else {
        return binary_heap_remove_root(HEAP_ALIAS(heap),
            &binary_heap_maximal_ordered_p);
    }
}

static inline void
maximal_heap_nice_alter(s_maximal_heap_t *heap, uint32 idx, sint64 new)
{
    s_binary_heap_t *alias;
    s_heap_data_t *data_tmp;

    assert_exit(maximal_heap_legal_ip(heap));
    assert_exit(binary_heap_index_legal_p(HEAP_ALIAS(heap), idx));

    alias = HEAP_ALIAS(heap);
    data_tmp = ALIAS_DATA(alias, idx);
    ALIAS_DATA(alias, idx) = NULL;

    idx = binary_heap_reorder(alias, idx, new, &binary_heap_maximal_ordered_p);
    assert_exit(NULL == ALIAS_DATA(alias, idx));

    ALIAS_DATA(alias, idx) = data_tmp;
    ALIAS_NICE(alias, idx) = new;

    assert_exit(maximal_heap_ordered_p(heap));
}

void
maximal_heap_decrease_nice(s_maximal_heap_t *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return;
    } else {
        nice = ALIAS_NICE(HEAP_ALIAS(heap), index) - offset;
        maximal_heap_nice_alter(heap, index, nice);
    }
}

void
maximal_heap_increase_nice(s_maximal_heap_t *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return;
    } else {
        nice = ALIAS_NICE(HEAP_ALIAS(heap), index) + offset;
        maximal_heap_nice_alter(heap, index, nice);
    }
}

static inline void
maximal_heap_build_i(s_maximal_heap_t *heap)
{
    sint64 nice;
    uint32 i, index;
    s_binary_heap_t *alias;
    s_heap_data_t *data_tmp;

    assert_exit(maximal_heap_legal_ip(heap));
    assert_exit(binary_heap_full_p(HEAP_ALIAS(heap)));
    assert_exit(binary_heap_legal_p(HEAP_ALIAS(heap)));

    alias = HEAP_ALIAS(heap);

    for (i = ALIAS_SIZE(alias) / 2; i != HEAP_INDEX_INVALID; i--) {
        nice = ALIAS_NICE(alias, i);
        data_tmp = ALIAS_DATA(alias, i);
        ALIAS_DATA(alias, i) = NULL;

        index = binary_heap_reorder(alias, i, nice,
            &binary_heap_maximal_percolate_down);

        assert_exit(ALIAS_DATA(alias, index) == NULL);
        ALIAS_DATA(alias, index) = data_tmp;
    }
}

s_maximal_heap_t *
maximal_heap_build(s_heap_data_t **hd_array, uint32 size)
{
    s_maximal_heap_t *heap;

    if (NULL_PTR_P(hd_array)) {
        return PTR_INVALID;
    } else if (complain_zero_size_p(size)) {
        return PTR_INVALID;
    } else {
        heap = memory_cache_allocate(sizeof(*heap));
        HEAP_ALIAS(heap) = memory_cache_allocate(sizeof(*HEAP_ALIAS(heap)));

        ALIAS_BASE(HEAP_ALIAS(heap)) = hd_array;
        ALIAS_CAPACITY(HEAP_ALIAS(heap)) = size - 1;
        ALIAS_SIZE(HEAP_ALIAS(heap)) = size - 1;
        ALIAS_DATA(HEAP_ALIAS(heap), 0) = NULL;

        maximal_heap_build_i(heap);

        return heap;
    }
}

uint32
maximal_heap_find_index(s_maximal_heap_t *heap, void *val)
{
    if (MAXIMAL_HEAP_ILLEGAL_P(heap)) {
        return HEAP_INDEX_INVALID;
    } else {
        return binary_heap_find_index(HEAP_ALIAS(heap), val);
    }
}

