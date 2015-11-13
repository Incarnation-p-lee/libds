struct minimal_heap *
minimal_heap_create(uint32 capacity)
{
    struct minimal_heap *heap;

    heap = malloc_ds(sizeof(*heap));
    if (!heap) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        heap->alias = binary_heap_create(capacity);
    }

    return heap;
}

void
minimal_heap_destroy(struct minimal_heap **heap)
{
    if (!*heap || !heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_destroy(&(*heap)->alias);
        free_ds(*heap);
        *heap = NULL;
    }
}

bool
minimal_heap_empty_p(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_heap_empty_p(heap->alias);
    }
}

bool
minimal_heap_full_p(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return binary_heap_full_p(heap->alias);
    }
}

void
minimal_heap_cleanup(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_cleanup(heap->alias);
    }
}

struct doubly_linked_list *
minimal_heap_node_find(struct minimal_heap *heap, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
        return NULL;
    } else {
        return binary_heap_node_find(heap->alias, nice);
    }
}

struct doubly_linked_list *
minimal_heap_node_find_min(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_root(heap->alias);
    }
}

void
minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else {
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
    assert(nice != HEAP_NICE_LOWER_LMT);

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

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
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

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        minimal_heap_node_remove_and_destroy_internal(heap, index);
    }
}

struct doubly_linked_list *
minimal_heap_node_remove_min(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
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

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (0 == offset) {
        pr_log_info("Zero offset of nice, nothing will be done.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice
        || HEAP_NICE_LOWER_LMT == new_nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        /*
         * index of nice has been set already.
         */
        minimal_heap_node_nice_alter(heap, index, new_nice);
    }
}

void
minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    sint64 new_nice;

    new_nice = nice + offset;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (0 == offset) {
        pr_log_info("Zero offset of nice, nothing will be done.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice
        || HEAP_NICE_UPPER_LMT == new_nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        /*
         * index of nice has been set already.
         */
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

    if (!chain_array) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (0 == size) {
        pr_log_warn("Zero size of chain array, nothing will be done.\n");
        return NULL;
    } else if (NULL != chain_array[0]) {
        pr_log_warn("First node of chain array should be NULL for heap-ordered.\n");
        return NULL;
    } else {
        heap = malloc_ds(sizeof(*heap));

        if (!heap) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            heap->alias = malloc_ds(sizeof(*heap->alias));

            if (!heap->alias) {
                pr_log_err("Fail to get memory from system.\n");
            } else {
                heap->alias->base = chain_array;
                heap->alias->capacity = size - 1;
                heap->alias->size = size - 1;

                minimal_heap_build_internal(heap);
                return heap;
            }
        }
    }
}

