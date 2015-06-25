static inline struct minimal_heap *
unit_test_minimal_heap_sample(uint64 range, uint32 size)
{
    struct minimal_heap *heap;
    sint64 nice;
    uint32 i;

    assert(0 != size);

    heap = minimal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
        minimal_heap_node_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline void
unit_test_minimal_heap_struc_field(void)
{
    bool pass;
    uint32 loop;
    uint32 index;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0x1234567;
    index = 1;
    heap = unit_test_minimal_heap_sample(0x3DA2, 0x2F23);

    while (loop--) {
        RESULT_CHECK_uint32(heap->bin_heap->size, minimal_heap_size(heap), &pass);
        RESULT_CHECK_uint32(heap->bin_heap->capacity, minimal_heap_capacity(heap), &pass);
        RESULT_CHECK_sint64(heap->bin_heap->base[index]->nice,
            minimal_heap_nice(heap, index), &pass);
        RESULT_CHECK_pointer(heap->bin_heap->base[index]->link,
            minimal_heap_link(heap, index), &pass);
        tmp = minimal_heap_link(heap, index);
        RESULT_CHECK_pointer(NULL, minimal_heap_link_set(heap, index, NULL), &pass);
        RESULT_CHECK_pointer(tmp, minimal_heap_link_set(heap, index, tmp), &pass);
    }
    minimal_heap_destroy(&heap);

    test_result_print(SYM_2_STR(minimal_heap_struc_field), pass);
    return;
}

static inline void
unit_test_minimal_heap_create(void)
{
    bool pass;
    uint32 loop;
    uint32 capacity;
    struct minimal_heap *heap;
    struct collision_chain **iter;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    loop = 0xA234u;
    capacity = 0u;

    heap = minimal_heap_create(capacity++);
    minimal_heap_destroy(&heap);

    while (loop--) {
        heap = minimal_heap_create(capacity);
        RESULT_CHECK_uint32(capacity, minimal_heap_capacity(heap), &pass);
        RESULT_CHECK_uint32(0u, minimal_heap_size(heap), &pass);

        iter = heap->bin_heap->base;
        while (iter < heap->bin_heap->base + u_offset(heap->bin_heap->capacity, 1)) {
            RESULT_CHECK_pointer(NULL, *iter++, &pass);
        }

        minimal_heap_destroy(&heap);
        capacity++;
    }

    test_result_print(SYM_2_STR(minimal_heap_create), pass);
    return;
}
