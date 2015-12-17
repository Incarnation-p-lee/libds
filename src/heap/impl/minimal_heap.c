struct minimal_heap *
minimal_heap_create(uint32 capacity)
{
    struct minimal_heap *heap;

    heap = memory_cache_allocate(sizeof(*heap));
    if (!complain_no_memory_p(heap)) {
        heap->alias = binary_heap_create(capacity);
    }

    return heap;
}

void
minimal_heap_destroy(struct minimal_heap **heap)
{
    if (!complain_null_pointer_p(heap) && !complain_null_pointer_p(*heap)) {
        binary_heap_destroy(&(*heap)->alias);
        memory_cache_free(*heap);
        *heap = NULL;
    }
}

bool
minimal_heap_empty_p(struct minimal_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return false;
    } else {
        return binary_heap_empty_p(heap->alias);
    }
}

bool
minimal_heap_full_p(struct minimal_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return true;
    } else {
        return binary_heap_full_p(heap->alias);
    }
}

void
minimal_heap_cleanup(struct minimal_heap *heap)
{
    if (!complain_null_pointer_p(heap)) {
        binary_heap_cleanup(heap->alias);
    }
}

struct doubly_linked_list *
minimal_heap_node_find(struct minimal_heap *heap, sint64 nice)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (!binary_heap_nice_legal_p(nice)) {
        return NULL;
    } else {
        return binary_heap_node_find(heap->alias, nice);
    }
}

struct doubly_linked_list *
minimal_heap_node_find_min(struct minimal_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else {
        return binary_heap_node_root(heap->alias);
    }
}

void
minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice)
{
    if (complain_null_pointer_p(heap)) {
        return;
    } if (binary_heap_nice_legal_p(nice)) {
        binary_heap_node_insert(heap->alias, val, nice,
            &binary_heap_minimal_ordered_p);
    }
}

static inline struct doubly_linked_list *
minimal_heap_node_remove_internal(struct minimal_heap *heap, uint32 index)
{
    sint64 nice;
    struct binary_heap *alias;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));

    alias = heap->alias;

    tmp = HEAP_CHAIN(alias, index);
    HEAP_CHAIN(alias, index) = NULL;
    nice = HEAP_NICE(alias, INDEX_ROOT) - 1;

    /*
     * percolate current index node to root, then remove the root.
     */
    index = binary_heap_node_reorder(alias, index, nice,
        &binary_heap_minimal_ordered_p);
    assert(INDEX_ROOT == index);

    HEAP_CHAIN(alias, INDEX_ROOT) = tmp;
    return binary_heap_node_remove_root(alias, &binary_heap_minimal_ordered_p);
}

struct doubly_linked_list *
minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice)
{
    uint32 index;

    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (!binary_heap_nice_legal_p(nice)) {
        return NULL;
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        return NULL;
    } else {
        return minimal_heap_node_remove_internal(heap, index);
    }
}

static inline void
minimal_heap_node_remove_and_destroy_internal(struct minimal_heap *heap,
    uint32 index)
{
    struct doubly_linked_list *removed;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));

    removed = minimal_heap_node_remove_internal(heap, index);
    doubly_linked_list_destroy(&removed);
}

void
minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice)
{
    uint32 index;

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (!binary_heap_nice_legal_p(nice)) {
        return;
    } else if (binary_heap_node_contains_p(heap->alias, nice, &index)) {
        minimal_heap_node_remove_and_destroy_internal(heap, index);
    }
}

struct doubly_linked_list *
minimal_heap_node_remove_min(struct minimal_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return NULL;
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        return binary_heap_node_remove_root(heap->alias,
            &binary_heap_minimal_ordered_p);
    }
}

void
minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap)
{
    if (complain_null_pointer_p(heap)) {
        return;
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
    } else {
        binary_heap_node_remove_root_and_destroy(heap->alias,
            &binary_heap_minimal_ordered_p);
    }
}

static inline void
minimal_heap_node_nice_alter(struct minimal_heap *heap, uint32 index,
    sint64 new_nice)
{
    uint32 hit_idx;
    struct binary_heap *alias;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));
    assert(new_nice != HEAP_NICE(heap->alias, index));

    alias = heap->alias;

    if (!binary_heap_node_contains_p(alias, new_nice, &hit_idx)) {
        tmp = HEAP_CHAIN(alias, index);
        HEAP_CHAIN(alias, index) = NULL;

        index = binary_heap_node_reorder(alias, index, new_nice,
            &binary_heap_minimal_ordered_p);
        assert(NULL == HEAP_CHAIN(alias, index));

        tmp->nice = new_nice;
        HEAP_CHAIN(alias, index) = tmp;
    } else {
        binary_heap_node_collision_merge(alias, hit_idx, index);
        minimal_heap_node_remove_and_destroy_internal(heap, index);
    }
}

void
minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    sint64 new_nice;

    new_nice = nice - offset;

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!binary_heap_nice_legal_p(nice)
        || !binary_heap_nice_legal_p(new_nice)) {
        return;
    } else if (binary_heap_node_contains_p(heap->alias, nice, &index)) {
        minimal_heap_node_nice_alter(heap, index, new_nice);
    }
}

void
minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    sint64 new_nice;

    new_nice = nice + offset;

    if (complain_null_pointer_p(heap)) {
        return;
    } else if (complain_zero_size_p(offset)) {
        return;
    } else if (!binary_heap_nice_legal_p(nice)
        || !binary_heap_nice_legal_p(new_nice)) {
        return;
    } else if (binary_heap_node_contains_p(heap->alias, nice, &index)) {
        minimal_heap_node_nice_alter(heap, index, new_nice);
    }
}

static inline void
minimal_heap_build_internal(struct minimal_heap *heap)
{
    uint32 iter;
    uint32 index;
    sint64 nice;
    struct binary_heap *alias;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_full_p(heap->alias));

    alias = heap->alias;
    iter = HEAP_SIZE(alias) / 2;

    while (iter != INDEX_INVALID) {
        index = iter;
        tmp = HEAP_CHAIN(alias, index);
        nice = HEAP_NICE(alias, index);

        HEAP_CHAIN(alias, index) = NULL;
        index = binary_heap_node_reorder(alias, index, nice,
            &binary_heap_minimal_ordered_p);

        assert(NULL == HEAP_CHAIN(alias, index));
        HEAP_CHAIN(alias, index) = tmp;

        iter--;
    }
}

struct minimal_heap *
minimal_heap_build(struct collision_chain **chain_array, uint32 size)
{
    struct minimal_heap *heap;

    if (complain_null_pointer_p(chain_array)) {
        return NULL;
    } else if (complain_zero_size_p(size)) {
        return NULL;
    } else {
        heap = memory_cache_allocate(sizeof(*heap));

        if (!complain_no_memory_p(heap)) {
            heap->alias = memory_cache_allocate(sizeof(*heap->alias));

            if (!complain_no_memory_p(heap->alias)) {
                heap->alias->base = chain_array;
                heap->alias->capacity = size - 1;
                heap->alias->size = size - 1;

                chain_array[0] = NULL;
                minimal_heap_build_internal(heap);
            }
        }

        return heap;
    }
}

