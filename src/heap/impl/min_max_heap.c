static inline bool
min_max_heap_legal_ip(s_min_max_heap_t *heap)
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
min_max_heap_illegal_ip(s_min_max_heap_t *heap)
{
    return !min_max_heap_legal_ip(heap);
}

bool
min_max_heap_legal_p(s_min_max_heap_t *heap)
{
    return min_max_heap_legal_ip(heap);
}

bool
min_max_heap_illegal_p(s_min_max_heap_t *heap)
{
    return min_max_heap_illegal_ip(heap);
}

uint32
min_max_heap_index_limit(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return INDEX_INVALID;
    } else {
        return binary_heap_index_limit(HEAP_ALIAS(heap));
    }
}

uint32
min_max_heap_size(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return SIZE_INVALID;
    } else {
        return binary_heap_size(HEAP_ALIAS(heap));
    }
}

sint64
min_max_heap_nice(s_min_max_heap_t *heap, uint32 index)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return HEAP_NICE_INVALID;
    } else if (index == HEAP_IDX_INVALID) {
        return HEAP_NICE_INVALID;
    } else if (index >= binary_heap_index_limit(HEAP_ALIAS(heap))) {
        return HEAP_NICE_INVALID;
    } else {
        return ALIAS_NICE(HEAP_ALIAS(heap), index);
    }
}

void *
min_max_heap_val(s_min_max_heap_t *heap, uint32 index)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (index == HEAP_IDX_INVALID) {
        return PTR_INVALID;
    } else if (index >= binary_heap_index_limit(HEAP_ALIAS(heap))) {
        return PTR_INVALID;
    } else {
        return ALIAS_VAL(HEAP_ALIAS(heap), index);
    }
}

s_min_max_heap_t *
min_max_heap_create(uint32 capacity)
{
    s_min_max_heap_t *heap;

    heap = memory_cache_allocate(sizeof(*heap));
    HEAP_ALIAS(heap) = binary_heap_create(capacity);

    return heap;
}

void
min_max_heap_destroy(s_min_max_heap_t **heap)
{
    if (NULL_PTR_P(heap)) {
        return;
    } else if (MIN_MAX_HEAP_ILLEGAL_P(*heap)) {
        return;
    } else {
        binary_heap_destroy(HEAP_ALIAS(*heap));
        memory_cache_free(*heap);

        *heap = NULL;
    }
}

bool
min_max_heap_empty_p(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return false;
    } else {
        return binary_heap_empty_p(HEAP_ALIAS(heap));
    }
}

bool
min_max_heap_full_p(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return true;
    } else {
        return binary_heap_full_p(HEAP_ALIAS(heap));
    }
}

uint32
min_max_heap_index_last(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return SIZE_INVALID;
    } else {
        return binary_heap_index_last(HEAP_ALIAS(heap));
    }
}

void
min_max_heap_cleanup(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return;
    } else {
        binary_heap_cleanup(HEAP_ALIAS(heap));
    }
}

/*
 * minimal node is root node
 * foreach node in heap, if
 *     even, > gdp_randfater > ... > depth 2 node > root
 *     odd,  > father > gdp_randfater > ... > depth 2 node > root
 */
void *
min_max_heap_get_min(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else {
        return binary_heap_root(HEAP_ALIAS(heap));
    }
}

/*
 * minimal node is either left or right child of root
 * foreach node in heap, if
 *     even, < fater < gdp_randfater < ... < depth 1 node > root
 *     odd,  < gdp_randfather < ... < depth 1 node > root
 */
void *
min_max_heap_get_max(s_min_max_heap_t *heap)
{
    uint32 index;

    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (INDEX_ROOT == INDEX_LAST(heap->alias)) {
        return ALIAS_VAL(HEAP_ALIAS(heap), INDEX_ROOT);
    } else {
        index = binary_heap_child_max_nice_index(HEAP_ALIAS(heap), INDEX_ROOT);
        assert_exit(index != INDEX_INVALID);

        return ALIAS_VAL(HEAP_ALIAS(heap), index);
    }
}

void
min_max_heap_insert(s_min_max_heap_t *heap, void *val, sint64 nice)
{
    s_binary_heap_t *alias;

    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return;
    } if (binary_heap_nice_illegal_p(nice)) {
        return;
    } else {
        alias = HEAP_ALIAS(heap);
        binary_heap_insert(alias, val, nice, &binary_heap_min_max_up_ordered_p);
    }
}

uint32
min_max_heap_depth(s_min_max_heap_t *heap, uint32 index)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return SIZE_INVALID;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return SIZE_INVALID;
    } else {
        return binary_heap_depth(index);
    }
}

void *
min_max_heap_remove_min(s_min_max_heap_t *heap)
{
    void *v;
    s_binary_heap_t *alias;

    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (binary_heap_empty_p(HEAP_ALIAS(heap))) {
        return PTR_INVALID;
    } else {
        alias = HEAP_ALIAS(heap);
        v = binary_heap_remove_root(alias, &binary_heap_min_max_down_ordered_p);

        return v;
    }
}

static inline s_heap_data_t *
min_max_heap_remove_isolate(s_min_max_heap_t *heap, uint32 index)
{
    sint64 nice;
    uint32 i, k;
    s_binary_heap_t *alias;
    s_heap_data_t *data_tmp,*retval;

    assert_exit(min_max_heap_legal_p(heap));
    assert_exit(!binary_heap_empty_p(HEAP_ALIAS(heap)));
    assert_exit(binary_heap_index_legal_p(HEAP_ALIAS(heap), index));

    i = index;
    alias = HEAP_ALIAS(heap);
    k = INDEX_LAST(alias);
    retval = ALIAS_DATA(alias, i);
    ALIAS_SIZE(alias) -= 1;

    /* percolate down at i with last node.  */
    data_tmp = ALIAS_DATA(alias, k);
    nice = ALIAS_NICE(alias, k);
    k = binary_heap_reorder(alias, i, nice, &binary_heap_min_max_down_ordered_p);
    ALIAS_DATA(alias, k) = data_tmp;

    /* percolate up at k with aim node.  */
    data_tmp = ALIAS_DATA(alias, k);
    nice = ALIAS_NICE(alias, k);
    i = binary_heap_reorder(alias, k, nice, &binary_heap_min_max_up_ordered_p);
    ALIAS_DATA(alias, i) = data_tmp;

    assert_exit(min_max_heap_ordered_p(heap));
    return retval;
}

static inline void *
min_max_heap_remove_i(s_min_max_heap_t *heap, uint32 index)
{
    void *val;
    s_heap_data_t *data_tmp;

    assert_exit(min_max_heap_legal_p(heap));
    assert_exit(!binary_heap_empty_p(HEAP_ALIAS(heap)));
    assert_exit(binary_heap_index_legal_p(HEAP_ALIAS(heap), index));

    data_tmp = min_max_heap_remove_isolate(heap, index);
    val = DATA_VAL(data_tmp);

    binary_heap_data_destroy(data_tmp);

    return val;
}

void *
min_max_heap_remove(s_min_max_heap_t *heap, uint32 index)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return PTR_INVALID;
    } else {
        return min_max_heap_remove_i(heap, index);
    }
}

static inline void *
min_max_heap_remove_max_i(s_min_max_heap_t *heap)
{
    void *v;
    uint32 max_index;
    s_binary_heap_t *alias;

    assert_exit(min_max_heap_legal_p(heap));

    alias = HEAP_ALIAS(heap);
    max_index = binary_heap_child_max_nice_index(alias, INDEX_ROOT);

    if (max_index == INDEX_INVALID) {
        v = binary_heap_remove_root(alias, &binary_heap_min_max_down_ordered_p);
    } else {
        v = min_max_heap_remove_i(heap, max_index);
    }

    return v;
}

void *
min_max_heap_remove_max(s_min_max_heap_t *heap)
{
    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return PTR_INVALID;
    } else if (binary_heap_empty_p(HEAP_ALIAS(heap))) {
        return PTR_INVALID;
    } else {
        return min_max_heap_remove_max_i(heap);
    }
}

static inline void
min_max_heap_nice_alter(s_min_max_heap_t *heap, uint32 index, sint64 new)
{
    uint32 k;
    s_binary_heap_t *alias;
    s_heap_data_t *data_tmp;

    assert_exit(min_max_heap_legal_p(heap));
    assert_exit(binary_heap_index_legal_p(HEAP_ALIAS(heap), index));

    alias = HEAP_ALIAS(heap);
    data_tmp = min_max_heap_remove_isolate(heap, index);

    ALIAS_SIZE(alias) += 1;
    DATA_NICE(data_tmp) = new;

    k = ALIAS_SIZE(alias);
    k = binary_heap_reorder(alias, k, new, &binary_heap_min_max_up_ordered_p);
    HEAP_DATA(alias, k) = data_tmp;

    assert_exit(min_max_heap_ordered_p(heap));
}

void
min_max_heap_decrease_nice(s_min_max_heap_t *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return;
    } else {
        nice = ALIAS_NICE(HEAP_ALIAS(heap), index) - offset;
        min_max_heap_nice_alter(heap, index, nice);
    }
}

void
min_max_heap_increase_nice(s_min_max_heap_t *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (MIN_MAX_HEAP_ILLEGAL_P(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (binary_heap_index_illegal_p(HEAP_ALIAS(heap), index)) {
        return;
    } else {
        nice = ALIAS_NICE(HEAP_ALIAS(heap), index) + offset;
        min_max_heap_nice_alter(heap, index, nice);
    }
}

