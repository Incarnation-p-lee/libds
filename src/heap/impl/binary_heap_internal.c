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

    return HEAP_LINK(heap, INDEX_ROOT);
}

static inline struct doubly_linked_list *
binary_heap_node_find(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_nice_legal_p(nice));

    if (binary_heap_empty_p(heap)) {
        pr_log_info("Attempt to find node in empty heap.\n");
        return NULL;
    } else {
        if (!binary_heap_node_contains_p(heap, nice, &index)) {
            return NULL;
        } else {
            assert(HEAP_LINK(heap, index));
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
    assert(binary_heap_nice_legal_p(nice));
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
 * RETURN the re-ordered index of heap with that nice.
 */
static inline uint32
binary_heap_node_reorder(struct binary_heap *heap, uint32 index, sint64 nice,
    void *heap_order)
{
    uint32 index_next;
    bool (*order)(struct binary_heap *, uint32, sint64, uint32 *);

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_nice_legal_p(nice));
    assert(!binary_heap_node_contains_with_null_p(heap, nice));

    order = heap_order;

    while (!(*order)(heap, index, nice, &index_next)) {
        HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, index_next);
        index = index_next;
    }

    HEAP_CHAIN(heap, index) = NULL;
    return index;
}

static inline bool
binary_heap_node_child_exist_p(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    return INDEX_L_CHILD(index) <= INDEX_LAST(heap) ? true : false;
}

static inline uint32
binary_heap_child_small_nice_index(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    if (!binary_heap_node_child_exist_p(heap, index)) {
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
binary_heap_child_big_nice_index(struct binary_heap *heap, uint32 index)
{
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

    if (!binary_heap_node_child_exist_p(heap, index)) {
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
binary_heap_grandchild_small_nice_index(struct binary_heap *heap, uint32 index)
{
    uint32 begin;
    uint32 ret_index;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_node_depth_even_p(heap, index));

    if (!binary_heap_node_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_LL_CHILD(index) > INDEX_LAST(heap)) {
        return binary_heap_child_small_nice_index(heap, index);
    } else {
        begin = INDEX_LL_CHILD(index);
        ret_index = binary_heap_serial_node_small_nice_index(heap, begin, 4);

        if (HEAP_NICE(heap, INDEX_R_CHILD(index))
            < HEAP_NICE(heap, ret_index)) {
            return INDEX_R_CHILD(index);
        } else {
            return ret_index;
        }
    }
}

static inline uint32
binary_heap_grandchild_big_nice_index(struct binary_heap *heap, uint32 index)
{
    uint32 begin;
    uint32 ret_index;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));
    assert(binary_heap_node_depth_odd_p(heap, index));

    if (!binary_heap_node_child_exist_p(heap, index)) {
        return INDEX_INVALID;
    } else if (INDEX_LL_CHILD(index) > INDEX_LAST(heap)) {
        return binary_heap_child_big_nice_index(heap, index);
    } else {
        begin = INDEX_LL_CHILD(index);
        ret_index = binary_heap_serial_node_big_nice_index(heap, begin, 4);

        if (HEAP_NICE(heap, INDEX_R_CHILD(index))
            > HEAP_NICE(heap, ret_index)) {
            return INDEX_R_CHILD(index);
        } else {
            return ret_index;
        }
    }
}

static inline uint32
binary_heap_serial_node_small_nice_index(struct binary_heap *heap,
    uint32 index, uint32 count)
{
    uint32 small_index;
    uint32 rest;

    assert(0 != count);
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

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
binary_heap_serial_node_big_nice_index(struct binary_heap *heap,
    uint32 index, uint32 count)
{
    uint32 big_index;
    uint32 rest;

    assert(0 != count);
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, index));

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

/*
 * Merge s_index indexed node to t_index indexed node, then remove node s_index.
 */
static inline void
binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_index,
    uint32 s_index)
{
    struct doubly_linked_list *head;

    assert(t_index != s_index);
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_index_legal_p(heap, t_index));
    assert(binary_heap_index_legal_p(heap, s_index));

    head = HEAP_LINK(heap, t_index);
    doubly_linked_list_merge(head, HEAP_LINK(heap, s_index));
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
    assert(binary_heap_valid_ordered_func_ptr_p(ordering));

    head = binary_heap_node_find(heap, nice);

    if (!head) {
        if (binary_heap_full_p(heap)) {
            pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
            binary_heap_capacity_extend(heap);
        }
        heap->size++;
        HEAP_CHAIN(heap, heap->size) = NULL;

        index = binary_heap_node_reorder(heap, heap->size, nice, ordering);
        binary_heap_node_create_by_index(heap, index, nice, val);
    } else {
        /*
         * nice collision occurs.
         */
        inserted = doubly_linked_list_node_create(val, nice);
        doubly_linked_list_node_insert_after_risky(head, inserted);
    }

    assert(binary_heap_ordered_p(heap, ordering));
}

static inline void
binary_heap_node_remove_root_and_destroy(struct binary_heap *heap,
    void *ordering)
{
    struct doubly_linked_list *removed;

    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_valid_ordered_func_ptr_p(ordering));

    removed = binary_heap_node_remove_root(heap, ordering);
    doubly_linked_list_destroy(&removed);
}

static inline struct doubly_linked_list *
binary_heap_node_remove_root(struct binary_heap *heap, void *order)
{
    struct doubly_linked_list *link;
    struct collision_chain *last;
    uint32 index;
    sint64 nice;

    assert(!binary_heap_empty_p(heap));
    assert(binary_heap_structure_legal_p(heap));
    assert(binary_heap_valid_ordered_func_ptr_p(order));

    link = HEAP_LINK(heap, INDEX_ROOT);
    HEAP_LINK(heap, INDEX_ROOT) = NULL;
    free_ds(HEAP_CHAIN(heap, INDEX_ROOT));

    if (INDEX_ROOT == INDEX_LAST(heap)) {
        heap->size--;
    } else {
        HEAP_CHAIN(heap, INDEX_ROOT) = NULL;
        nice = HEAP_NICE(heap, INDEX_LAST(heap));
        last = HEAP_CHAIN(heap, INDEX_LAST(heap));

        HEAP_CHAIN(heap, INDEX_LAST(heap)) = NULL;
        heap->size--;

        /*
         * percolate down last node from root.
         */
        index = binary_heap_node_reorder(heap, INDEX_ROOT, nice, order);
        assert(NULL == HEAP_CHAIN(heap, index));
        HEAP_CHAIN(heap, index) = last;
    }

    assert(binary_heap_ordered_p(heap, order));
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

