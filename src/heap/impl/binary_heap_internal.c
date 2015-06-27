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
    register struct collision_chain **iter;

    assert(NULL != heap);

    iter = heap_iterate_start(heap);

    while (iter < heap_iterate_limit(heap)) {
        assert(NULL != *iter);
        doubly_linked_list_destroy(&(*iter)->link);
        assert(NULL == (*iter)->link);

        free_ds(*iter);
        *iter = NULL;
        iter++;
    }

    heap->size = 0;
}

static inline struct doubly_linked_list *
binary_heap_node_root(struct binary_heap *heap)
{
    assert(NULL != heap);

    return heap->base[1]->link;
}

static inline struct doubly_linked_list *
binary_heap_node_find(struct binary_heap *heap, sint64 nice)
{
    register struct collision_chain **iter;

    assert(NULL != heap);

    iter = heap_iterate_start(heap);
    while (iter < heap_iterate_limit(heap)) {
        if ((*iter)->nice == nice) {
            break;
        }
        iter++;
    }

    if (iter == heap_iterate_limit(heap)) {
        return NULL;
    } else {
        return (*iter)->link;
    }
}

static inline void
binary_heap_capacity_extend(struct binary_heap *heap)
{
    struct collision_chain **new;

    assert(NULL != heap);
    assert(NULL != heap->base);

    new = malloc_ds(sizeof(*heap->base[0]) * u_offset(heap->capacity * 2, 1));
    memcpy(new, heap->base, u_offset(heap->capacity, 1));

    heap->capacity = heap->capacity * 2;
    free_ds(heap->base);
    heap->base = new;
}

static inline void
binary_heap_percolate_up(struct binary_heap *heap, void *val, sint64 nice)
{
    uint32 index;

    assert(NULL != heap);
    assert(NULL == binary_heap_node_find(heap, nice));

    if (binary_heap_full_p(heap)) {
        pr_log_warn("Binary heap is full, will rebuild for percolate up.\n");
        binary_heap_capacity_extend(heap);
    }

    index = ++heap->size;
    while (1 != index && HEAP_PARENT_NICE(heap, index) > nice) {
        heap->base[index] = heap->base[INDEX_PARENT(index)];
        index = INDEX_PARENT(index);
    }

    heap->base[index] = malloc_ds(sizeof(*heap->base[0]));
    heap->base[index]->nice = nice;
    heap->base[index]->link = doubly_linked_list_node_create(val, 0);
}

