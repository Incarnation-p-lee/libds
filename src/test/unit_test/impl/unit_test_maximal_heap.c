static inline void
unit_test_maximal_heap_struc_field(void)
{
    bool pass;
    uint32 index;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    index = 1;
    heap = test_maximal_heap_sample(0x3A2, 0x2F3);

    RESULT_CHECK_uint32(heap->alias->size, maximal_heap_size(heap), &pass);
    RESULT_CHECK_uint32(heap->alias->capacity, maximal_heap_capacity(heap), &pass);
    RESULT_CHECK_sint64(heap->alias->base[index]->nice,
        maximal_heap_nice(heap, index), &pass);
    RESULT_CHECK_pointer(heap->alias->base[index]->link,
        maximal_heap_link(heap, index), &pass);
    tmp = maximal_heap_link(heap, index);
    RESULT_CHECK_pointer(NULL, maximal_heap_link_set(heap, index, NULL), &pass);
    RESULT_CHECK_pointer(tmp, maximal_heap_link_set(heap, index, tmp), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_struc_field), pass);
}

static inline void
unit_test_maximal_heap_create(void)
{
    bool pass;
    uint32 capacity;
    struct maximal_heap *heap;
    struct collision_chain **iter;

    pass = true;
    capacity = 0u;

    heap = maximal_heap_create(capacity++);
    maximal_heap_destroy(&heap);

    heap = maximal_heap_create(capacity);
    RESULT_CHECK_uint32(capacity, maximal_heap_capacity(heap), &pass);
    RESULT_CHECK_uint32(0u, maximal_heap_size(heap), &pass);

    iter = heap->alias->base;
    while (iter < heap->alias->base + u_offset(heap->alias->capacity, 1)) {
        RESULT_CHECK_pointer(NULL, *iter++, &pass);
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_create), pass);
}

static inline void
unit_test_maximal_heap_destroy(void)
{
    bool pass;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    maximal_heap_destroy(&heap);

    heap = maximal_heap_create(0u);
    maximal_heap_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);

    unit_test_result_print(SYM_2_STR(maximal_heap_destroy), pass);
}

static inline void
unit_test_maximal_heap_empty_p(void)
{
    bool pass;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(false, maximal_heap_empty_p(heap), &pass);

    heap = test_maximal_heap_sample(0x234, 0x134);
    RESULT_CHECK_bool(false, maximal_heap_empty_p(heap), &pass);
    maximal_heap_destroy(&heap);

    heap = maximal_heap_create(0u);
    RESULT_CHECK_bool(true, maximal_heap_empty_p(heap), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_empty_p), pass);
}

static inline void
unit_test_maximal_heap_full_p(void)
{
    bool pass;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(true, maximal_heap_full_p(heap), &pass);

    heap = test_maximal_heap_sample(0x1, 0x1);
    RESULT_CHECK_bool(true, maximal_heap_full_p(heap), &pass);
    maximal_heap_destroy(&heap);

    heap = maximal_heap_create(0u);
    RESULT_CHECK_bool(false, maximal_heap_full_p(heap), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_full_p), pass);
}

static inline void
unit_test_maximal_heap_cleanup(void)
{
    bool pass;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    maximal_heap_cleanup(heap);

    heap = test_maximal_heap_sample(0x345, 0x80E);
    maximal_heap_cleanup(heap);

    RESULT_CHECK_bool(false, maximal_heap_full_p(heap), &pass);
    RESULT_CHECK_bool(true, maximal_heap_empty_p(heap), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_cleanup), pass);
}

static inline void
unit_test_maximal_heap_node_find(void)
{
    bool pass;
    uint32 index;
    struct maximal_heap *heap;

    pass = true;
    index = 1u;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, maximal_heap_node_find(heap, index), &pass);

    heap = test_maximal_heap_sample(0x345, 0x10E);
    RESULT_CHECK_pointer(maximal_heap_link(heap, index),
        maximal_heap_node_find(heap, maximal_heap_nice(heap, index)), &pass);
    index = 0x144Eu;
    RESULT_CHECK_pointer(NULL, maximal_heap_node_find(heap, (sint64)index), &pass);

    index = 0x2u;
    RESULT_CHECK_pointer(maximal_heap_link(heap, index),
        maximal_heap_node_find(heap, maximal_heap_nice(heap, index)), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_find), pass);
}

static inline void
unit_test_maximal_heap_node_find_max(void)
{
    bool pass;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, maximal_heap_node_find_max(heap), &pass);

    heap = test_maximal_heap_sample(0x134, 0x14E);
    RESULT_CHECK_pointer(maximal_heap_link(heap, 1u),
        maximal_heap_node_find_max(heap), &pass);

    RESULT_CHECK_pointer(maximal_heap_link(heap, 1u),
        maximal_heap_node_find_max(heap), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_find_max), pass);
}

static inline void
unit_test_maximal_heap_node_insert(void)
{
    bool pass;
    uint32 size;
    uint32 count;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;
    count = 0x72;

    maximal_heap_node_insert(heap, &pass, 0u);

    heap = test_maximal_heap_sample(0x345, 0x14E);
    while (count--) {
        size = maximal_heap_size(heap);
        if (maximal_heap_node_find(heap, count)) {
            maximal_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size, maximal_heap_size(heap), &pass);
        } else {
            maximal_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size + 1, maximal_heap_size(heap), &pass);
        }
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_insert), pass);
}

static inline void
unit_test_maximal_heap_node_remove_max(void)
{
    bool pass;
    struct maximal_heap *heap;
    struct doubly_linked_list *maximal;

    pass = true;
    heap = NULL;

    maximal_heap_node_remove_max(heap);

    heap = test_maximal_heap_sample(0x135, 0xD4E);
    maximal = maximal_heap_node_find_max(heap);
    RESULT_CHECK_pointer(maximal, maximal_heap_node_remove_max(heap), &pass);
    doubly_linked_list_destroy(&maximal);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_remove_max), pass);
}

static inline void
unit_test_maximal_heap_node_remove_max_and_destroy(void)
{
    bool pass;
    uint32 size;
    struct maximal_heap *heap;

    pass = true;
    heap = NULL;

    maximal_heap_node_remove_max_and_destroy(heap);

    heap = test_maximal_heap_sample(0x235, 0x14E);
    size = maximal_heap_size(heap);

    maximal_heap_node_find_max(heap);
    maximal_heap_node_remove_max_and_destroy(heap);
    size--;
    RESULT_CHECK_uint32(size, maximal_heap_size(heap), &pass);

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_remove_max_and_destroy), pass);
}

static inline void
unit_test_maximal_heap_node_decrease_nice(void)
{
    bool pass;
    uint32 offset;
    uint32 count;
    sint64 nice;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    heap = NULL;
    offset = 0;
    count = 0x29;

    maximal_heap_node_decrease_nice(heap, 0, offset);

    heap = test_maximal_heap_sample(0x345, 0x2E0);
    maximal_heap_node_decrease_nice(heap, 0, offset);
    offset = 0x3B;

    while (count--) {
        tmp = maximal_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count - offset;
            if (!maximal_heap_node_find(heap, nice)) {
                maximal_heap_node_decrease_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, maximal_heap_node_find(heap, nice), &pass);
            } else {
                maximal_heap_node_decrease_nice(heap, count, offset);
            }
        } else {
            maximal_heap_node_decrease_nice(heap, count, offset);
        }
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_decrease_nice), pass);
}

static inline void
unit_test_maximal_heap_node_increase_nice(void)
{
    bool pass;
    uint32 count;
    uint32 offset;
    sint64 nice;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x35;
    heap = NULL;
    offset = 0;

    maximal_heap_node_increase_nice(heap, 0, offset);

    heap = test_maximal_heap_sample(0x942, 0x73a);
    maximal_heap_node_increase_nice(heap, 0, offset);
    offset = 0x1234;

    while (count--) {
        tmp = maximal_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count + offset;
            if (!maximal_heap_node_find(heap, nice)) {
                maximal_heap_node_increase_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, maximal_heap_node_find(heap, nice), &pass);
            } else {
                maximal_heap_node_increase_nice(heap, count, offset);
            }
        } else {
            maximal_heap_node_increase_nice(heap, count, offset);
        }
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_increase_nice), pass);
}

static inline void
unit_test_maximal_heap_node_remove(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x19;
    heap = NULL;

    maximal_heap_node_remove(heap, 0);

    heap = test_maximal_heap_sample(0x942, 0x73a);
    nice = 0x12345;
    RESULT_CHECK_pointer(NULL, maximal_heap_node_remove(heap, nice), &pass);

    nice = 0x35;

    while (count--) {
        tmp = maximal_heap_node_find(heap, nice);
        if (tmp) {
            RESULT_CHECK_pointer(tmp, maximal_heap_node_remove(heap, nice), &pass);
            doubly_linked_list_destroy(&tmp);
        } else {
            RESULT_CHECK_pointer(NULL, maximal_heap_node_remove(heap, nice), &pass);
        }
        nice--;
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_remove), pass);
}

static inline void
unit_test_maximal_heap_node_remove_and_destroy(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct maximal_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x27;
    heap = NULL;

    maximal_heap_node_remove_and_destroy(heap, 0);

    heap = test_maximal_heap_sample(0x942, 0x73a);
    nice = 0x12345;
    maximal_heap_node_remove_and_destroy(heap, nice);

    nice = 0x20;
    while (count--) {
        tmp = maximal_heap_node_find(heap, nice);
        if (tmp) {
            maximal_heap_node_remove_and_destroy(heap, nice);
            RESULT_CHECK_pointer(NULL, maximal_heap_node_find(heap, nice), &pass);
        }
        nice--;
    }

    maximal_heap_destroy(&heap);
    unit_test_result_print(SYM_2_STR(maximal_heap_node_remove_and_destroy), pass);
}

