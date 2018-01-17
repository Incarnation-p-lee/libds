uint32
min_max_heap_index_limit(struct min_max_heap *heap)
{
    if (NULL_PTR_P(heap)) {
        return INDEX_INVALID;
    } else {
        return heap->alias->capacity + 1;
    }
}

uint32
min_max_heap_index_last(struct min_max_heap *heap)
{
    return heap->alias->size;
}

uint32
min_max_heap_size(struct min_max_heap *heap)
{
    if (NULL_PTR_P(heap)) {
        return SIZE_INVALID;
    } else {
        return heap->alias->size;
    }
}

sint64
min_max_heap_nice(struct min_max_heap *heap, uint32 index)
{
    if (NULL_PTR_P(heap)) {
        return HEAP_NICE_INVALID;
    } else if (index == HEAP_IDX_INVALID || index >= min_max_heap_index_limit(heap)) {
        return HEAP_NICE_INVALID;
    } else {
        return heap->alias->base[index]->nice;
    }
}

void *
min_max_heap_val(struct min_max_heap *heap, uint32 index)
{
    if (NULL_PTR_P(heap)) {
        return PTR_INVALID;
    } else if (index == HEAP_IDX_INVALID || index >= min_max_heap_index_limit(heap)) {
        return PTR_INVALID;
    } else {
        return heap->alias->base[index]->val;
    }
}

struct min_max_heap *
min_max_heap_create(uint32 capacity)
{
    struct min_max_heap *heap;

    heap = memory_cache_allocate(sizeof(*heap));
    heap->alias = binary_heap_create(capacity);

    return heap;
}

void
min_max_heap_destroy(struct min_max_heap **heap)
{
    if (!NULL_PTR_P(heap) && min_max_heap_structure_legal_p(*heap)) {
        binary_heap_destroy(HEAP_ALIAS(*heap));
        memory_cache_free(*heap);

        *heap = NULL;
    }
}

bool
min_max_heap_empty_p_internal(struct min_max_heap *heap)
{
    assert_exit(min_max_heap_structure_legal_p(heap));

    return binary_heap_empty_p(heap->alias);
}

bool
min_max_heap_empty_p(struct min_max_heap *heap)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return false;
    } else {
        return min_max_heap_empty_p_internal(heap);
    }
}

bool
min_max_heap_full_p(struct min_max_heap *heap)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return true;
    } else {
        return binary_heap_full_p(heap->alias);
    }
}

void
min_max_heap_cleanup(struct min_max_heap *heap)
{
    if (min_max_heap_structure_legal_p(heap)) {
        binary_heap_cleanup(heap->alias);
    }
}

/*
 * minimal node is root node
 * foreach node in heap, if
 *     even, > gdp_randfater > ... > depth 2 node > root
 *     odd,  > father > gdp_randfater > ... > depth 2 node > root
 */
void *
min_max_heap_get_min(struct min_max_heap *heap)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return NULL;
    } else {
        return binary_heap_root(heap->alias);
    }
}

/*
 * minimal node is either left or right child of root
 * foreach node in heap, if
 *     even, < fater < gdp_randfater < ... < depth 1 node > root
 *     odd,  < gdp_randfather < ... < depth 1 node > root
 */
void *
min_max_heap_get_max(struct min_max_heap *heap)
{
    uint32 index;

    if (!min_max_heap_structure_legal_p(heap)) {
        return NULL;
    } else if (INDEX_ROOT == INDEX_LAST(heap->alias)) {
        return HEAP_VAL(heap->alias, INDEX_ROOT);
    } else {
        index = binary_heap_child_max_nice_index(heap->alias, INDEX_ROOT);

        assert_exit(INDEX_INVALID != index);
        return HEAP_VAL(heap->alias, index);
    }
}

static inline bool
min_max_heap_structure_legal_p(struct min_max_heap *heap)
{
    if (NULL_PTR_P(heap)) {
        return false;
    } else {
        return binary_heap_legal_p(heap->alias);
    }
}

static inline bool
min_max_heap_index_legal_p(struct min_max_heap *heap, uint32 index)
{
    assert_exit(min_max_heap_structure_legal_p(heap));

    return binary_heap_index_legal_p(heap->alias, index);
}

void
min_max_heap_insert(struct min_max_heap *heap, void *val, sint64 nice)
{
    struct binary_heap *alias;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    if (!min_max_heap_structure_legal_p(heap)) {
        return;
    } else {
        alias = heap->alias;
        order = &binary_heap_min_max_up_ordered_p;

        binary_heap_insert(alias, val, nice, order);
        assert_exit(min_max_heap_ordered_p(heap));
    }
}

uint32
min_max_heap_depth(struct min_max_heap *heap, uint32 index)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return DEPTH_INVALID;
    } else if (!min_max_heap_index_legal_p(heap, index)) {
        return DEPTH_INVALID;
    } else {
        return binary_heap_depth(index);
    }
}

void *
min_max_heap_remove_min(struct min_max_heap *heap)
{
    void *retval;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    if (!min_max_heap_structure_legal_p(heap)) {
        return NULL;
    } else if (min_max_heap_empty_p_internal(heap)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        order = &binary_heap_min_max_down_ordered_p;
        retval = binary_heap_remove_root(heap->alias, order);

        assert_exit(min_max_heap_ordered_p(heap));
        return retval;
    }
}

static inline struct heap_data *
min_max_heap_remove_isolate(struct min_max_heap *heap, uint32 index)
{
    sint64 nice;
    uint32 index_aim;
    struct heap_data *tmp;
    struct heap_data *retval;
    struct binary_heap *alias;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert_exit(min_max_heap_structure_legal_p(heap));
    assert_exit(!min_max_heap_empty_p_internal(heap));
    assert_exit(min_max_heap_index_legal_p(heap, index));

    alias = heap->alias;
    index_aim = INDEX_LAST(alias);
    retval = HEAP_DATA(alias, index);
    alias->size--;

    /*
     * percolate down at index with last node.
     */
    tmp = HEAP_DATA(alias, index_aim);
    nice = HEAP_NICE(alias, index_aim);
    order = &binary_heap_min_max_down_ordered_p;

    index_aim = binary_heap_reorder(alias, index, nice, order);
    HEAP_DATA(alias, index_aim) = tmp;

    /*
     * percolate up at index_aim with aim node.
     */
    tmp = HEAP_DATA(alias, index_aim);
    nice = HEAP_NICE(alias, index_aim);
    order = &binary_heap_min_max_up_ordered_p;

    index = binary_heap_reorder(alias, index_aim, nice, order);
    HEAP_DATA(alias, index) = tmp;

    assert_exit(min_max_heap_ordered_p(heap));
    return retval;
}

static inline void *
min_max_heap_remove_internal(struct min_max_heap *heap, uint32 index)
{
    void *retval;
    struct heap_data *tmp;

    assert_exit(min_max_heap_structure_legal_p(heap));
    assert_exit(!min_max_heap_empty_p_internal(heap));
    assert_exit(min_max_heap_index_legal_p(heap, index));

    tmp = min_max_heap_remove_isolate(heap, index);
    retval = binary_heap_data_destroy(tmp);

    return retval;
}

struct doubly_linked_list *
min_max_heap_remove(struct min_max_heap *heap, uint32 index)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return NULL;
    } else if (!min_max_heap_index_legal_p(heap, index)) {
        return NULL;
    } else {
        return min_max_heap_remove_internal(heap, index);
    }
}

static inline void *
min_max_heap_remove_max_internal(struct min_max_heap *heap)
{
    void *retval;
    uint32 max_index;
    struct binary_heap *alias;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert_exit(min_max_heap_structure_legal_p(heap));

    alias = heap->alias;
    max_index = binary_heap_child_max_nice_index(alias, INDEX_ROOT);

    if (INDEX_INVALID == max_index) {
        order = &binary_heap_min_max_down_ordered_p;
        retval = binary_heap_remove_root(alias, order);
    } else {
        retval = min_max_heap_remove_internal(heap, max_index);
    }

    assert_exit(min_max_heap_ordered_p(heap));
    return retval;
}

void *
min_max_heap_remove_max(struct min_max_heap *heap)
{
    if (!min_max_heap_structure_legal_p(heap)) {
        return NULL;
    } else if (min_max_heap_empty_p_internal(heap)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        return min_max_heap_remove_max_internal(heap);
    }
}

static inline void
min_max_heap_nice_alter(struct min_max_heap *heap, uint32 index,
    sint64 new_nice)
{
    uint32 index_next;
    struct heap_data *tmp;
    struct binary_heap *alias;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert_exit(min_max_heap_structure_legal_p(heap));
    assert_exit(min_max_heap_index_legal_p(heap, index));

    alias = heap->alias;
    tmp = min_max_heap_remove_isolate(heap, index);

    alias->size++;
    tmp->nice = new_nice;

    order = &binary_heap_min_max_up_ordered_p;
    index_next = binary_heap_reorder(alias, alias->size, new_nice, order);

    HEAP_DATA(alias, index_next) = tmp;
    assert_exit(min_max_heap_ordered_p(heap));
}

void
min_max_heap_decrease_nice(struct min_max_heap *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (!min_max_heap_structure_legal_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!min_max_heap_index_legal_p(heap, index)) {
        return;
    } else {
        nice = HEAP_NICE(heap->alias, index) - offset;
        min_max_heap_nice_alter(heap, index, nice);
    }
}

void
min_max_heap_increase_nice(struct min_max_heap *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (!min_max_heap_structure_legal_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!min_max_heap_index_legal_p(heap, index)) {
        return;
    } else {
        nice = HEAP_NICE(heap->alias, index) + offset;
        min_max_heap_nice_alter(heap, index, nice);
    }
}

