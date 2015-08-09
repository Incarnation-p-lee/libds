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
    assert(NULL != heap->base);

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
    assert(NULL != heap->base);

    return HEAP_LINK(heap, HEAP_ROOT_INDEX);
}

static inline struct doubly_linked_list *
binary_heap_node_find(struct binary_heap *heap, sint64 nice)
{
    uint32 index;

    assert(NULL != heap);
    assert(NULL != heap->base);

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
    assert(NULL != heap->base);
    assert(NULL == heap->base[index]);

    HEAP_CHAIN(heap, index) = binary_heap_collision_chain_create(nice, val);
}

static inline struct collision_chain *
binary_heap_collision_chain_create(sint64 nice, void *val)
{
    struct collision_chain *retval;

    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);

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
    bool ignore;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);

    // optimization linear loop here.
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
 * index      - specific the empty hole index of heap.
 * nice       - nice value of percolate up.
 * heap_order - function pointer of heap order, should be one of function
 *              in file binary_heap_order.c.
 * RETURN the percolated index of heap.
 */
static inline uint32
binary_heap_percolate_up(struct binary_heap *heap, uint32 index, sint64 nice,
    void *ordering)
{
    bool (*order)(struct binary_heap *, uint32, sint64);

    assert(0 != index);
    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(NULL != ordering);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(HEAP_NICE_LOWER_LMT < nice);
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    order = ordering;

    if (binary_heap_full_p(heap)) {
        pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
        binary_heap_capacity_extend(heap);
    }

    assert(NULL == HEAP_CHAIN(heap, index));
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));
    assert(binary_heap_percolate_up_precondition_p(heap, index, nice, ordering));

    while (HEAP_ROOT_INDEX != index
        && (*order)(heap, INDEX_PARENT(index), nice)) {
        HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, INDEX_PARENT(index));
        index = INDEX_PARENT(index);
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

static inline void
binary_heap_node_remove_tail_fixup(struct binary_heap *heap, uint32 index,
    void *ordering)
{
    sint64 nice;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(0u != index);
    assert(!binary_heap_node_child_exist_p(heap, index));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    nice = HEAP_NICE(heap, INDEX_LAST(heap));
    tmp = HEAP_CHAIN(heap, INDEX_LAST(heap));
    HEAP_CHAIN(heap, INDEX_LAST(heap)) = NULL;
    heap->size--;

    index = binary_heap_percolate_up(heap, index, nice, ordering);
    HEAP_CHAIN(heap, index) = tmp;
}

static inline uint32
binary_heap_child_small_nice_index(struct binary_heap *heap, uint32 index)
{
    assert(NULL != heap);
    assert(0 != index);
    assert(NULL != heap->base);
    assert(INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap));

    if (HEAP_LEFT_CHILD_NICE(heap, index) > HEAP_RIGHT_CHILD_NICE(heap, index)) {
        return INDEX_RIGHT_CHILD(index);
    } else {
        return INDEX_LEFT_CHILD(index);
    }
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
binary_heap_percolate_down(struct binary_heap *heap, uint32 index, sint64 nice,
    void *ordering)
{
    uint32 small_child;
    bool (*order)(struct binary_heap *, uint32, sint64);

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(0 != index);
    assert(NULL == HEAP_CHAIN(heap, index));
    assert(!binary_heap_node_contains_with_hole_p(heap, nice));
    assert(binary_heap_percolate_down_precondition_p(heap, index, nice, ordering));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    order = ordering;

    if (binary_heap_empty_p(heap)) {
        pr_log_warn("Binary heap is empty, nothing will be done.\n");
        return 0;
    }

    while (index <= INDEX_LAST(heap)) {
        if (INDEX_RIGHT_CHILD(index) <= INDEX_LAST(heap)) {
            /*
             * index node has two child here.
             */
            small_child = binary_heap_child_small_nice_index(heap, index);
            if ((*order)(heap, small_child, nice)) {
                break;
            } else {
                HEAP_CHAIN(heap, index) = HEAP_CHAIN(heap, small_child);
                index = small_child;
            }
        } else if (INDEX_LEFT_CHILD(index) <= INDEX_LAST(heap)) {
            /*
             * index node has only one child here.
             */
            if ((*order)(heap, INDEX_LEFT_CHILD(index), nice)) {
                index = INDEX_LEFT_CHILD(index);
            }
            break;
        } else {
            /*
             * index node has no child here.
             */
            break;
        }
    }
    HEAP_CHAIN(heap, index) = NULL;

    return index;
}

/*
 * Merge s_idx indexed node to t_idx indexed node, then remove node s_idx.
 */
static inline void
binary_heap_node_collision_merge(struct binary_heap *heap, uint32 t_idx,
    uint32 s_idx)
{
    struct doubly_linked_list *head;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(0 != t_idx && t_idx <= INDEX_LAST(heap));
    assert(0 != s_idx && s_idx <= INDEX_LAST(heap));

    head = HEAP_LINK(heap, t_idx);
    doubly_linked_list_merge(head, HEAP_LINK(heap, s_idx));
}

static inline void
binary_heap_node_remove_and_destroy(struct binary_heap *heap, uint32 index,
    void *ordering)
{
    struct doubly_linked_list *link;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(0 != index && index <= INDEX_LAST(heap));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    link = binary_heap_node_remove(heap, index, ordering);
    doubly_linked_list_destroy(&link);
}

static inline void
binary_heap_node_insert(struct binary_heap *heap, void *val, sint64 nice,
    void *ordering)
{
    uint32 index;
    struct doubly_linked_list *head;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(HEAP_NICE_LOWER_LMT < nice);
    assert(HEAP_NICE_UPPER_LMT > nice);
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    head = binary_heap_node_find(heap, nice);

    if (!head) {
        index = binary_heap_percolate_up(heap, heap->size + 1, nice, ordering);
        binary_heap_node_create_by_index(heap, index, nice, val);
        heap->size++;
    } else {
        /*
         * conflict nice.
         */
        doubly_linked_list_node_insert_after(head,
            doubly_linked_list_node_create(val, nice));
    }
}

static inline void
binary_heap_percolate_down_to_tail(struct binary_heap *heap, uint32 index,
    void *ordering)
{
    sint64 limit;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(NULL == heap->base[index]);
    assert(0 != index && index <= INDEX_LAST(heap));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    limit = binary_heap_order_percolate_down_nice_limit(ordering);
    index = binary_heap_percolate_down(heap, index, limit, ordering);
    /*
     * binary heap _DO_ not allow NULL hole of array implement.
     * move the last node to percolated node, and percolate up.
     */
    binary_heap_node_remove_tail_fixup(heap, index, ordering);
}


static inline struct doubly_linked_list *
binary_heap_node_remove(struct binary_heap *heap, uint32 index, void *ordering)
{
    struct doubly_linked_list *link;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(NULL != heap->base[index]);
    assert(0 != index && index <= INDEX_LAST(heap));
    assert(binary_heap_order_function_pointer_valid_p(ordering));

    link = HEAP_LINK(heap, index);
    HEAP_LINK(heap, index) = NULL;

    free_ds(HEAP_CHAIN(heap, index));
    HEAP_CHAIN(heap, index) = NULL;

    binary_heap_percolate_down_to_tail(heap, index, ordering);

    return link;
}

/*
 * index - altered node index of binary heap
 */
static inline void
binary_heap_nice_alter_percolate_up(struct binary_heap *heap, uint32 index,
    sint64 new_nice, void *ordering)
{
    uint32 tgt_index;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(NULL != heap->base);
    assert(NULL != heap->base[index]);
    assert(0 != index && index <= INDEX_LAST(heap));
    assert(binary_heap_order_function_pointer_valid_p(ordering));
    assert(HEAP_NICE_LOWER_LMT < new_nice && HEAP_NICE_UPPER_LMT > new_nice);
    assert(binary_heap_percolate_direction_consistent_with_ordering_p(heap,
        index, new_nice, ordering));

    if (!binary_heap_node_contains_p(heap, new_nice, &tgt_index)) {
        tmp = HEAP_CHAIN(heap, index);
        HEAP_CHAIN(heap, index) = NULL;
        tmp->nice = new_nice;

        index = binary_heap_percolate_up(heap, index, tmp->nice, ordering);
        assert(NULL == HEAP_CHAIN(heap, index));

        HEAP_CHAIN(heap, index) = tmp;
    } else {
        /*
         * decreased nice already contained.
         * merge conflict and remove node.
         */
        binary_heap_node_collision_merge(heap, tgt_index, index);
        binary_heap_node_remove_and_destroy(heap, index, ordering);
    }
}

