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

    assert(0 != capacity);
    assert(binary_heap_structure_legal_p(heap));

    heap->capacity = capacity;
    heap->size = 0;

    iter = heap->base;
    while (iter < heap->base + u_offset(heap->capacity, 1)) {
        *iter++ = NULL;
    }
}

static inline void
binary_heap_destroy(struct binary_heap **heap)
{
    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(*heap));

    binary_heap_cleanup(*heap);
    free_ds((*heap)->base);
    free_ds(*heap);

    *heap = NULL;
}

static inline bool
binary_heap_empty_p(struct binary_heap *heap)
{
    assert(binary_heap_structure_legal_p(heap));

    return heap->size == 0 ? true : false;
}

static inline bool
binary_heap_full_p(struct binary_heap *heap)
{
    assert(binary_heap_structure_legal_p(heap));

    return heap->size == heap->capacity ? true : false;
}

static inline void
binary_heap_cleanup(struct binary_heap *heap)
{
    register uint32 index;

    assert(binary_heap_structure_legal_p(heap));

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
    assert(binary_heap_structure_legal_p(heap));

    return HEAP_LINK(heap, HEAP_ROOT_INDEX);
}

static inline struct doubly_linked_list *
binary_heap_node_find(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(binary_heap_structure_legal_p(heap));

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

    assert(binary_heap_structure_legal_p(heap));

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
    assert(NULL == heap->base[index]);
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_structure_legal_p(heap));

    HEAP_CHAIN(heap, index) = binary_heap_collision_chain_create(nice, val);
}

static inline struct collision_chain *
binary_heap_collision_chain_create(sint64 nice, void *val)
{
    struct collision_chain *retval;

    assert(binary_heap_nice_legal_p(nice));

    retval = malloc_ds(sizeof(*retval));
    retval->nice = nice;
    retval->link = doubly_linked_list_node_create(val, 0);

    return retval;
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

    assert(binary_heap_nice_legal_p(nice));
    assert(binary_heap_structure_legal_p(heap));

    index = INDEX_FIRST;

    while (index <= INDEX_LAST(heap)) {
        if (nice == HEAP_NICE(heap, index)) {
            if (tgt) {
                *tgt = index;
            }

            return true;
        }

        index++;
    }

    return false;
}

/*
 * index      - specific the empty hole index of heap.
 * nice       - nice value of percolate up.
 * heap_order - function pointer of heap order, should be one of function
 *              in file binary_heap_order.c.
 * RETURN the percolated index of heap.
 */
static inline uint32
binary_heap_percolate_up(struct binary_heap *heap, uint32 up_index, sint64 nice,
    void *ordering)
{
    uint32 index;
    uint32 idx_next;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert(NULL != ordering);
    assert(binary_heap_up_ordered_p(ordering));
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, up_index));
    assert(!binary_heap_node_contains_with_null_p(heap, nice));

    order = ordering;
    index = up_index;

    assert(NULL == HEAP_CHAIN(heap, index));
    assert(binary_heap_percolate_up_precondition_p(heap, index, nice, ordering));

    while (HEAP_ROOT_INDEX != index) {
        if ((*order)(heap, index, nice, &idx_next)) {
            break;
        } else {
            HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, idx_next);
            index = idx_next;
        }
    }
    HEAP_CHAIN(heap, index) = NULL;

    return index;
}

/*
 * index - specific the empty hole index of heap.
 * nice  - nice value of percolate down.
 * RETURN  the percolated index of heap.
 *
 * HEAP_NICE_UPPER_LMT/HEAP_NICE_LOWER_LMT is allowed to nice
 * for remove one node from heap.
 */
static inline uint32
binary_heap_percolate_down(struct binary_heap *heap, uint32 down_index,
    sint64 nice, void *ordering)
{
    uint32 child_index;
    uint32 index;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert(binary_heap_structure_legal_p(heap));
    assert(NULL == HEAP_CHAIN(heap, down_index));
    assert(binary_heap_down_ordered_p(ordering));
    assert(binary_heap_nice_legal_p(nice));
    assert(!binary_heap_node_contains_with_null_p(heap, nice));
    assert(binary_heap_percolate_down_precondition_p(heap, down_index, nice, ordering));

    index = down_index;
    order = ordering;

    while (INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap)) {
        if ((*order)(heap, index, nice, &child_index)) {
            break;
        } else {
            HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, child_index);
            index = child_index;
        }
    }
    HEAP_CHAIN(heap, index) = NULL;

    return index;
}

static inline bool
binary_heap_node_child_exist_p(struct binary_heap *heap, uint32 index)
{
    assert(NULL != heap);
    assert(NULL != heap->base);

    return INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap) ? true : false;
}

static inline uint32
binary_heap_child_small_nice_index(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_node_child_exist_p(heap, index));

    if (INDEX_RIGHT_CHILD(index) > INDEX_LAST(heap)) {
        return INDEX_LEFT_CHILD(index);
    } else if (HEAP_LEFT_CHILD_NICE(heap, index) > HEAP_RIGHT_CHILD_NICE(heap, index)) {
        return INDEX_RIGHT_CHILD(index);
    } else {
        return INDEX_LEFT_CHILD(index);
    }
}

static inline uint32
binary_heap_child_big_nice_index(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_node_child_exist_p(heap, index));

    if (INDEX_RIGHT_CHILD(index) > INDEX_LAST(heap)) {
        return INDEX_LEFT_CHILD(index);
    } else if (HEAP_LEFT_CHILD_NICE(heap, index) < HEAP_RIGHT_CHILD_NICE(heap, index)) {
        return INDEX_RIGHT_CHILD(index);
    } else {
        return INDEX_LEFT_CHILD(index);
    }
}

/*
 * Merge s_idx indexed node to t_idx indexed node, then remove node s_idx.
 */
static inline void
binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_idx,
    uint32 s_idx)
{
    struct doubly_linked_list *head;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, t_idx));
    assert(binary_heap_index_legal_p(heap, s_idx));

    head = HEAP_LINK(heap, t_idx);
    doubly_linked_list_merge(head, HEAP_LINK(heap, s_idx));
}

static inline void
binary_heap_node_insert(struct binary_heap *heap, void *val, sint64 nice,
    void *ordering)
{
    uint32 index;
    struct doubly_linked_list *head;
    struct doubly_linked_list *inserted;

    assert(binary_heap_nice_legal_p(nice));
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_up_ordered_p(ordering));

    head = binary_heap_node_find(heap, nice);

    if (!head) {
        if (binary_heap_full_p(heap)) {
            pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
            binary_heap_capacity_extend(heap);
        }
        HEAP_CHAIN(heap, heap->size + 1) = NULL;

        index = binary_heap_percolate_up(heap, heap->size + 1, nice, ordering);
        binary_heap_node_create_by_index(heap, index, nice, val);
        heap->size++;
    } else {
        /*
         * nice collision occurs.
         */
        inserted = doubly_linked_list_node_create(val, nice);
        doubly_linked_list_node_insert_after_risky(head, inserted);
    }
}

static inline void
binary_heap_node_remove_root_and_destroy(struct binary_heap *heap,
    void *ordering)
{
    struct doubly_linked_list *removed;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_down_ordered_p(ordering));

    removed = binary_heap_node_remove_root(heap, ordering);
    doubly_linked_list_destroy(&removed);
}

static inline struct doubly_linked_list *
binary_heap_node_remove_root(struct binary_heap *heap, void *ordering)
{
    struct doubly_linked_list *link;
    struct collision_chain *last;
    uint32 index;
    sint64 nice;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_down_ordered_p(ordering));

    link = HEAP_LINK(heap, HEAP_ROOT_INDEX);
    HEAP_LINK(heap, HEAP_ROOT_INDEX) = NULL;
    free_ds(HEAP_CHAIN(heap, HEAP_ROOT_INDEX));
    HEAP_CHAIN(heap, HEAP_ROOT_INDEX) = NULL;

    nice = HEAP_NICE(heap, INDEX_LAST(heap));
    last = HEAP_CHAIN(heap, INDEX_LAST(heap));
    HEAP_CHAIN(heap, INDEX_LAST(heap)) = NULL;
    heap->size--;

    index = binary_heap_percolate_down(heap, HEAP_ROOT_INDEX, nice, ordering);
    HEAP_CHAIN(heap, index) = last;

    return link;
}

static inline uint32
binary_heap_node_depth(uint32 index)
{
    uint32 depth;

    assert(INDEX_INVALID != index);

    depth = 0;

    while (index >= (1 << (depth + 1))) {
        depth++;
    }

    return depth;
}
