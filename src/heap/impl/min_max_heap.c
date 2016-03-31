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
    if (!complain_null_pointer_p(heap) && !complain_null_pointer_p(*heap)) {
        binary_heap_destroy(&(*heap)->alias);
        memory_cache_free(*heap);
        *heap = NULL;
    }
}

bool
min_max_heap_empty_p(struct min_max_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return false;
    } else {
        return binary_heap_empty_p(heap->alias);
    }
}

bool
min_max_heap_full_p(struct min_max_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return true;
    } else {
        return binary_heap_full_p(heap->alias);
    }
}

void
min_max_heap_cleanup(struct min_max_heap *heap)
{
    if (!complain_null_pointer_p(heap)) {
        binary_heap_cleanup(heap->alias);
    }
}

/*
 * minimal node is root node
 * foreach node in heap, if
 *     even, > grandfater > ... > depth 2 node > root
 *     odd,  > father > grandfater > ... > depth 2 node > root
 */
void *
min_max_heap_get_min(struct min_max_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        return binary_heap_root(heap->alias);
    }
}

/*
 * minimal node is either left or right child of root
 * foreach node in heap, if
 *     even, < fater < grandfater < ... < depth 1 node > root
 *     odd,  < grandfather < ... < depth 1 node > root
 */
void *
min_max_heap_get_max(struct min_max_heap *heap)
{
    uint32 index;

    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (INDEX_ROOT == INDEX_LAST(heap->alias)) {
        return HEAP_VAL(heap->alias, INDEX_ROOT);
    } else {
        index = binary_heap_child_max_nice_index(heap->alias, INDEX_ROOT);
        assert(INDEX_INVALID != index);

        return HEAP_VAL(heap->alias, index);
    }
}

void
min_max_heap_insert(struct min_max_heap *heap, void *val, sint64 nice)
{
    struct binary_heap *alias;

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (binary_heap_nice_legal_p(nice)) {
        alias = heap->alias;
        binary_heap_insert(alias, val, nice, &binary_heap_min_max_up_ordered_p);
        assert(min_max_heap_ordered_p(heap));
    }
}

uint32
min_max_heap_depth(struct min_max_heap *heap, uint32 index)
{
    if (complain_null_pointer_p(heap)) {
        return DEPTH_INVALID;
    } else if (!binary_heap_index_legal_p(heap->alias, index)) {
        return DEPTH_INVALID;
    } else {
        return binary_heap_depth(index);
    }
}

void *
min_max_heap_remove_min(struct min_max_heap *heap)
{
    void *retval;

    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        retval = binary_heap_remove_root(heap->alias,
            &binary_heap_min_max_down_ordered_p);
        assert(min_max_heap_ordered_p(heap));

        return retval;
    }
}

static inline void *
min_max_heap_remove_internal(struct min_max_heap *heap, uint32 index)
{
    sint64 nice;
    void *retval;
    uint32 index_final;
    uint32 index_last;
    struct heap_data *tmp;
    struct binary_heap *alias;

    assert(!complain_null_pointer_p(heap));
    assert(!binary_heap_empty_p(heap->alias));
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));

    alias = heap->alias;
    index_last = INDEX_LAST(alias);
    retval = binary_heap_destroy_node(alias, index);

    tmp = HEAP_DATA(alias, index_last);
    nice = HEAP_NICE(alias, index_last);
    index_final = binary_heap_reorder(alias, index, nice,
        &binary_heap_min_max_down_ordered_p);
    HEAP_DATA(alias, index_final) = tmp;

    tmp = HEAP_DATA(alias, index_final);
    nice = HEAP_NICE(alias, index_final);
    index = binary_heap_reorder(alias, index_final, nice,
        &binary_heap_min_max_up_ordered_p);
    HEAP_DATA(alias, index) = tmp;

    assert(min_max_heap_ordered_p(heap));
    return retval;
}

struct doubly_linked_list *
min_max_heap_remove(struct min_max_heap *heap, uint32 index)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (!binary_heap_index_legal_p(heap->alias, index)) {
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

    assert(!complain_null_pointer_p(heap));
    assert(binary_heap_structure_legal_p(heap->alias));

    alias = heap->alias;
    max_index = binary_heap_child_max_nice_index(alias, INDEX_ROOT);

    if (INDEX_INVALID == max_index) {
        retval = binary_heap_remove_root(alias, &binary_heap_min_max_ordered_p);
    } else {
        retval = min_max_heap_remove_internal(heap, max_index);
    }

    assert(min_max_heap_ordered_p(heap));
    return retval;
}

void *
min_max_heap_remove_max(struct min_max_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (binary_heap_empty_p(heap->alias)) {
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
    struct heap_data *tmp;
    struct binary_heap *alias;

    assert(!complain_null_pointer_p(heap));
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));

    alias = heap->alias;
    tmp = HEAP_DATA(alias, index);
    HEAP_DATA(alias, index) = NULL;

    index = binary_heap_reorder(alias, index, new_nice,
        &binary_heap_min_max_ordered_p);
    assert(NULL == HEAP_DATA(alias, index));

    tmp->nice = new_nice;
    HEAP_DATA(alias, index) = tmp;
}

void
min_max_heap_decrease_nice(struct min_max_heap *heap, uint32 index,
    uint32 offset)
{
    sint64 nice;

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!binary_heap_index_legal_p(heap->alias, index)) {
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

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!binary_heap_index_legal_p(heap->alias, index)) {
        return;
    } else {
        nice = HEAP_NICE(heap->alias, index) + offset;
        min_max_heap_nice_alter(heap, index, nice);
    }
}

