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
    uint32 index;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    index = 1;
    heap = unit_test_minimal_heap_sample(0x3DA2, 0x2F23);

    RESULT_CHECK_uint32(heap->alias->size, minimal_heap_size(heap), &pass);
    RESULT_CHECK_uint32(heap->alias->capacity, minimal_heap_capacity(heap), &pass);
    RESULT_CHECK_sint64(heap->alias->base[index]->nice,
        minimal_heap_nice(heap, index), &pass);
    RESULT_CHECK_pointer(heap->alias->base[index]->link,
        minimal_heap_link(heap, index), &pass);
    tmp = minimal_heap_link(heap, index);
    RESULT_CHECK_pointer(NULL, minimal_heap_link_set(heap, index, NULL), &pass);
    RESULT_CHECK_pointer(tmp, minimal_heap_link_set(heap, index, tmp), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_struc_field), pass);
}

static inline void
unit_test_minimal_heap_create(void)
{
    bool pass;
    uint32 capacity;
    struct minimal_heap *heap;
    struct collision_chain **iter;

    pass = true;
    capacity = 0u;

    heap = minimal_heap_create(capacity++);
    minimal_heap_destroy(&heap);

    heap = minimal_heap_create(capacity);
    RESULT_CHECK_uint32(capacity, minimal_heap_capacity(heap), &pass);
    RESULT_CHECK_uint32(0u, minimal_heap_size(heap), &pass);

    iter = heap->alias->base;
    while (iter < heap->alias->base + u_offset(heap->alias->capacity, 1)) {
        RESULT_CHECK_pointer(NULL, *iter++, &pass);
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_create), pass);
}

static inline void
unit_test_minimal_heap_destroy(void)
{
    bool pass;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    minimal_heap_destroy(&heap);

    heap = minimal_heap_create(0u);
    minimal_heap_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);
    unit_test_result_print(SYM_2_STR(minimal_heap_destroy), pass);
}

static inline void
unit_test_minimal_heap_empty_p(void)
{
    bool pass;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(false, minimal_heap_empty_p(heap), &pass);

    heap = unit_test_minimal_heap_sample(0x2234, 0x1234);
    RESULT_CHECK_bool(false, minimal_heap_empty_p(heap), &pass);
    minimal_heap_destroy(&heap);

    heap = minimal_heap_create(0u);
    RESULT_CHECK_bool(true, minimal_heap_empty_p(heap), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_empty_p), pass);
}

static inline void
unit_test_minimal_heap_full_p(void)
{
    bool pass;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(true, minimal_heap_full_p(heap), &pass);

    heap = unit_test_minimal_heap_sample(0x1, 0x1);
    RESULT_CHECK_bool(true, minimal_heap_full_p(heap), &pass);
    minimal_heap_destroy(&heap);

    heap = minimal_heap_create(0u);
    RESULT_CHECK_bool(false, minimal_heap_full_p(heap), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_full_p), pass);
}

static inline void
unit_test_minimal_heap_cleanup(void)
{
    bool pass;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    minimal_heap_cleanup(heap);

    heap = unit_test_minimal_heap_sample(0x3345, 0x204E);
    minimal_heap_cleanup(heap);

    RESULT_CHECK_bool(false, minimal_heap_full_p(heap), &pass);
    RESULT_CHECK_bool(true, minimal_heap_empty_p(heap), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_cleanup), pass);
}

static inline void
unit_test_minimal_heap_node_find(void)
{
    bool pass;
    uint32 index;
    struct minimal_heap *heap;

    pass = true;
    index = 1u;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, minimal_heap_node_find(heap, index), &pass);

    heap = unit_test_minimal_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(minimal_heap_link(heap, index),
        minimal_heap_node_find(heap, minimal_heap_nice(heap, index)), &pass);
    index = 0x144Eu;
    RESULT_CHECK_pointer(NULL, minimal_heap_node_find(heap, (sint64)index), &pass);

    index = 0x2u;
    RESULT_CHECK_pointer(minimal_heap_link(heap, index),
        minimal_heap_node_find(heap, minimal_heap_nice(heap, index)), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_find), pass);
}

static inline void
unit_test_minimal_heap_node_find_min(void)
{
    bool pass;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, minimal_heap_node_find_min(heap), &pass);

    heap = unit_test_minimal_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(minimal_heap_link(heap, 1u),
        minimal_heap_node_find_min(heap), &pass);

    RESULT_CHECK_pointer(minimal_heap_link(heap, 1u),
        minimal_heap_node_find_min(heap), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_find_min), pass);
}

static inline void
unit_test_minimal_heap_node_insert(void)
{
    bool pass;
    uint32 count;
    uint32 size;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;
    count = 0x82;

    minimal_heap_node_insert(heap, &pass, 0u);

    heap = unit_test_minimal_heap_sample(0x345, 0x44E);

    while (count--) {
        size = minimal_heap_size(heap);
        if (minimal_heap_node_find(heap, count)) {
            minimal_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size, minimal_heap_size(heap), &pass);
        } else {
            minimal_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size + 1, minimal_heap_size(heap), &pass);
        }
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_insert), pass);
}

static inline void
unit_test_minimal_heap_node_remove_min(void)
{
    bool pass;
    struct minimal_heap *heap;
    struct doubly_linked_list *minimal;

    pass = true;
    heap = NULL;

    minimal_heap_node_remove_min(heap);

    heap = unit_test_minimal_heap_sample(0x1435, 0x1D4E);
    minimal = minimal_heap_node_find_min(heap);
    RESULT_CHECK_pointer(minimal, minimal_heap_node_remove_min(heap), &pass);

    doubly_linked_list_destroy(&minimal);
    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_remove_min), pass);
}

static inline void
unit_test_minimal_heap_node_remove_min_and_destroy(void)
{
    bool pass;
    uint32 size;
    struct minimal_heap *heap;

    pass = true;
    heap = NULL;

    minimal_heap_node_remove_min_and_destroy(heap);

    heap = unit_test_minimal_heap_sample(0x1425, 0x10DE);
    size = minimal_heap_size(heap);

    minimal_heap_node_find_min(heap);
    minimal_heap_node_remove_min_and_destroy(heap);
    size--;
    RESULT_CHECK_uint32(size, minimal_heap_size(heap), &pass);

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_remove_min_and_destroy), pass);
}

static inline void
unit_test_minimal_heap_node_decrease_nice(void)
{
    bool pass;
    uint32 count;
    uint32 offset;
    sint64 nice;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;
    offset = 0;

    minimal_heap_node_decrease_nice(heap, 0, offset);

    heap = unit_test_minimal_heap_sample(0x345, 0x2E0);
    minimal_heap_node_decrease_nice(heap, 0, offset);
    offset = 0xa;

    while (count--) {
        tmp = minimal_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count - offset;
            if (!minimal_heap_node_find(heap, nice)) {
                minimal_heap_node_decrease_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, minimal_heap_node_find(heap, nice), &pass);
            } else {
                minimal_heap_node_decrease_nice(heap, count, offset);
            }
        } else {
            minimal_heap_node_decrease_nice(heap, count, offset);
        }
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_decrease_nice), pass);
}

static inline void
unit_test_minimal_heap_node_increase_nice(void)
{
    bool pass;
    uint32 count;
    uint32 offset;
    sint64 nice;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x32;
    heap = NULL;
    offset = 0;

    minimal_heap_node_increase_nice(heap, 0, offset);

    heap = unit_test_minimal_heap_sample(0x342, 0x423a);
    minimal_heap_node_increase_nice(heap, 0, offset);
    offset = 0x14;

    while (count--) {
        tmp = minimal_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count + offset;
            if (!minimal_heap_node_find(heap, nice)) {
                minimal_heap_node_increase_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, minimal_heap_node_find(heap, nice), &pass);
            } else {
                minimal_heap_node_increase_nice(heap, count, offset);
            }
        } else {
            minimal_heap_node_increase_nice(heap, count, offset);
        }
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_increase_nice), pass);
}

static inline void
unit_test_minimal_heap_node_remove(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;

    minimal_heap_node_remove(heap, 0);

    heap = unit_test_minimal_heap_sample(0x942, 0x73a);
    nice = 0x12345;
    RESULT_CHECK_pointer(NULL, minimal_heap_node_remove(heap, nice), &pass);

    nice = 0x7;
    while (count--) {
        tmp = minimal_heap_node_find(heap, nice);
        if (tmp) {
            RESULT_CHECK_pointer(tmp, minimal_heap_node_remove(heap, nice), &pass);
            doubly_linked_list_destroy(&tmp);
        } else {
            RESULT_CHECK_pointer(NULL, minimal_heap_node_remove(heap, nice), &pass);
        }
        nice--;
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_remove), pass);
}

static inline void
unit_test_minimal_heap_node_remove_and_destroy(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct minimal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;

    minimal_heap_node_remove(heap, 0);

    heap = unit_test_minimal_heap_sample(0x742, 0x23a);
    nice = 0x12345;
    minimal_heap_node_remove_and_destroy(heap, nice);

    nice = 0x8;
    while (count--) {
        tmp = minimal_heap_node_find(heap, nice);
        if (tmp) {
            minimal_heap_node_remove_and_destroy(heap, nice);
            RESULT_CHECK_pointer(NULL, minimal_heap_node_find(heap, nice), &pass);
        }
        nice--;
    }

    minimal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(minimal_heap_node_remove_and_destroy), pass);
}

