// static inline void
// unit_test_min_max_heap_struc_field(void)
// {
//     bool pass;
//     uint32 index;
//     struct min_max_heap *heap;
//     struct doubly_linked_list *tmp;
// 
//     pass = true;
//     index = 1;
//     heap = test_min_max_heap_sample(0x3DA2, 0x2F23);
// 
//     RESULT_CHECK_uint32(heap->alias->size, minimal_heap_size(heap), &pass);
//     RESULT_CHECK_uint32(heap->alias->capacity, minimal_heap_capacity(heap), &pass);
//     RESULT_CHECK_sint64(heap->alias->base[index]->nice,
//         minimal_heap_nice(heap, index), &pass);
//     RESULT_CHECK_pointer(heap->alias->base[index]->link,
//         minimal_heap_link(heap, index), &pass);
//     tmp = minimal_heap_link(heap, index);
//     RESULT_CHECK_pointer(NULL, minimal_heap_link_set(heap, index, NULL), &pass);
//     RESULT_CHECK_pointer(tmp, minimal_heap_link_set(heap, index, tmp), &pass);
// 
//     minimal_heap_destroy(&heap);
//     unit_test_result_print(SYM_2_STR(minimal_heap_struc_field), pass);
// }

static inline void
unit_test_min_max_heap_create(void)
{
    bool pass;
    uint32 capacity;
    struct min_max_heap *heap;
    struct collision_chain **iter;

    pass = true;
    capacity = 0u;

    heap = min_max_heap_create(capacity++);
    min_max_heap_destroy(&heap);

    heap = min_max_heap_create(capacity);
    RESULT_CHECK_uint32(capacity, min_max_heap_capacity(heap), &pass);
    RESULT_CHECK_uint32(0u, min_max_heap_size(heap), &pass);

    iter = heap->alias->base;
    while (iter < heap->alias->base + u_offset(heap->alias->capacity, 1)) {
        RESULT_CHECK_pointer(NULL, *iter++, &pass);
    }

    min_max_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(min_max_heap_create), pass);
}

