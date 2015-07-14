static inline struct binary_heap *
binary_heap_create(uint32 capacity)
{
    struct binary_heap *heap;

    if (0 == capacity) {
        pr_log_warn("Cannot create zero binary heap, use default capacity\n");
        capacity = DEFAULT_BINARY_HEAP_SIZE;
    }

    heap = malloc_ds(sizeof(*heap));
    if (!heap) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        heap->base = malloc_ds(sizeof(*heap->base[0]) * u_offset(capacity, 1));
        if (!heap->base) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            binary_heap_initial(heap, capacity);
        }
    }

    return heap;
}

static inline void
binary_heap_initial(struct binary_heap *heap, uint32 capacity)
{
    register struct collision_chain **iter;

    assert(NULL != heap);
    assert(0 != capacity);

    heap->capacity = capacity;
    heap->size = 0;

    iter = heap->base;
    while (iter < heap->base + u_offset(heap->capacity, 1)) {
        *iter++ = NULL;
    }

    return;
}

static inline void
binary_heap_destroy(struct binary_heap **heap)
{
    assert(NULL != *heap);
    assert(NULL != heap);

    binary_heap_cleanup(*heap);
    free_ds((*heap)->base);
    free_ds(*heap);

    *heap = NULL;
}

static inline bool
binary_heap_empty_p(struct binary_heap *heap)
{
    assert(NULL != heap);

    return heap->size == 0 ? true : false;
}

static inline bool
binary_heap_full_p(struct binary_heap *heap)
{
    assert(NULL != heap);

    return heap->size == heap->capacity ? true : false;
}

static inline void
binary_heap_cleanup(struct binary_heap *heap)
{
    register uint32 index;

    assert(NULL != heap);

    index = INDEX_FIRST;

    while (index <= INDEX_LAST(heap)) {
        assert(NULL != HEAP_CHAIN(heap, index));
        doubly_linked_list_destroy(&HEAP_LINK(heap, index));
        assert(NULL == HEAP_LINK(heap, index));

        free_ds(HEAP_CHAIN(heap, index));
        HEAP_CHAIN(heap, index) = NULL;
        index++;
    }

    heap->size = 0;
}

static inline struct doubly_linked_list *
binary_heap_node_root(struct binary_heap *heap)
{
    assert(NULL != heap);

    return HEAP_LINK(heap, HEAP_ROOT_INDEX);
}

static inline struct doubly_linked_list *
binary_heap_node_find(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(NULL != heap);

    if (binary_heap_empty_p(heap)) {
        pr_log_info("Attempt to find node in empty heap.\n");
        return NULL;
    } else {
        if (!binary_heap_node_contains_p(heap, nice, &index)) {
            return NULL;
        } else {
            return HEAP_LINK(heap, index);
        }
    }
}

static inline void
binary_heap_capacity_extend(struct binary_heap *heap)
{
    struct collision_chain **new;
    uint32 size;

    assert(NULL != heap);
    assert(NULL != heap->base);

    size = sizeof(heap->base[0]) * u_offset(heap->capacity * 2, 1);
    new = malloc_ds(size);
    memset(new, 0, size);

    size = sizeof(heap->base[0]) * u_offset(heap->capacity, 1);
    memcpy(new, heap->base, size);

    heap->capacity = heap->capacity * 2;
    free_ds(heap->base);
    heap->base = new;
}

static inline void
binary_heap_node_create_by_index(struct binary_heap *heap, uint32 index,
    sint64 nice, void *val)
{
    assert(NULL != heap);
    assert(0 != index);
    assert(NULL == heap->base[index]);

    HEAP_CHAIN(heap, index) = binary_heap_collision_chain_create(nice, val);
}

static inline struct doubly_linked_list *
binary_heap_node_destroy_by_index(struct binary_heap *heap, uint32 index)
{
    struct doubly_linked_list *retval;

    assert(NULL != heap);
    assert(0 != index);
    assert(NULL != heap->base[index]);

    retval = HEAP_LINK(heap, index);
    HEAP_LINK(heap, index) = NULL;

    free_ds(HEAP_CHAIN(heap, index));
    HEAP_CHAIN(heap, index) = NULL;

    return retval;
}

static inline struct collision_chain *
binary_heap_collision_chain_create(sint64 nice, void *val)
{
    struct collision_chain *retval;

    retval = malloc_ds(sizeof(*retval));
    retval->nice = nice;
    retval->link = doubly_linked_list_node_create(val, 0);

    return retval;
}

static inline uint32
binary_heap_index_get_by_nice(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(NULL != heap);
    assert(NULL != heap->base);

    if (!binary_heap_node_contains_p(heap, nice, &index)) {
        pr_log_warn("Failed to find node of heap with given nice.\n");
        return 0u;
    } else {
        return index;
    }
}

/*
 * If contains the nice specificed, *tgt will be set to the index with nice.
 * If NOT contains, unchanged to *tgt.
 * If NULL == tgt, will ignore this parameter.
 */
static inline bool
binary_heap_node_contains_p(struct binary_heap *heap, sint64 nice, uint32 *tgt)
{
    register uint32 index;
    bool ignore;

    assert(NULL != heap);
    assert(NULL != heap->base);

    index = INDEX_FIRST;
    ignore = NULL == tgt ? true : false;

    while (index <= INDEX_LAST(heap)) {
        if (nice == HEAP_NICE(heap, index)) {
            if (!ignore) {
                *tgt = index;
            }
            return true;
        }
        index++;
    }

    return false;
}

/*
 * index -specific the empty hole index of heap.
 * nice  -nice value of percolate up.
 * Todo: should assert nice is not contained by heap
 */
static inline uint32
binary_heap_percolate_up(struct binary_heap *heap, uint32 index, sint64 nice)
{
    assert(0 != index);
    assert(NULL != heap);

    if (binary_heap_full_p(heap)) {
        pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
        binary_heap_capacity_extend(heap);
    }

    assert(NULL == HEAP_CHAIN(heap, index));

    while (HEAP_ROOT_INDEX != index && HEAP_PARENT_NICE(heap, index) > nice) {
        HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, INDEX_PARENT(index));
        index = INDEX_PARENT(index);
    }
    HEAP_CHAIN(heap, index) = NULL;

    return index;

}

static inline uint32
binary_heap_percolate_down(struct binary_heap *heap, uint32 index, sint64 nice)
{
    // uint32 small_child;

    // assert(NULL != heap);
    // assert(0 != index);
    // assert(NULL == HEAP_CHAIN(heap, index));

    // if (binary_heap_empty_p(heap)) {
    //     pr_log_warn("Binary heap is empty, nothing will be done.\n");
    //     return 0;
    // }

    // while (index != minimal_heap_size(heap)
    //     && HEAP_NICE(heap->bin_heap, index) < nice) {
    //     if (HEAP
    //     && HEAP_NICE(heap->bin_heap, index) 
    // }

    return index;
}

