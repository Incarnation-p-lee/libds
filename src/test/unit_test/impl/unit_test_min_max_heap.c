static inline void
unit_test_min_max_heap_struct_field(void)
{
    bool pass;
    uint32 index;
    struct min_max_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    index = 1;
    heap = test_min_max_heap_sample(0x6bca, 0x3ed1);

    RESULT_CHECK_uint32(heap->alias->size, min_max_heap_size(heap), &pass);
    RESULT_CHECK_uint32(heap->alias->capacity, min_max_heap_capacity(heap), &pass);
    RESULT_CHECK_sint64(heap->alias->base[index]->nice,
        min_max_heap_nice(heap, index), &pass);
    RESULT_CHECK_pointer(heap->alias->base[index]->link,
        min_max_heap_link(heap, index), &pass);
    tmp = min_max_heap_link(heap, index);
    RESULT_CHECK_pointer(NULL, min_max_heap_link_set(heap, index, NULL), &pass);
    RESULT_CHECK_pointer(tmp, min_max_heap_link_set(heap, index, tmp), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_struc_field, pass);
}

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
    UNIT_TEST_RESULT(min_max_heap_create, pass);
}

static inline void
unit_test_min_max_heap_destroy(void)
{
    bool pass;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    min_max_heap_destroy(&heap);

    heap = min_max_heap_create(0u);
    min_max_heap_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);
    UNIT_TEST_RESULT(min_max_heap_destroy, pass);
}

static inline void
unit_test_min_max_heap_empty_p(void)
{
    bool pass;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(false, min_max_heap_empty_p(heap), &pass);

    heap = test_min_max_heap_sample(0x4234, 0x2234);
    RESULT_CHECK_bool(false, min_max_heap_empty_p(heap), &pass);
    min_max_heap_destroy(&heap);

    heap = min_max_heap_create(0u);
    RESULT_CHECK_bool(true, min_max_heap_empty_p(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_empty_p, pass);
}

static inline void
unit_test_min_max_heap_full_p(void)
{
    bool pass;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_bool(true, min_max_heap_full_p(heap), &pass);

    heap = test_min_max_heap_sample(0x1, 0x1);
    RESULT_CHECK_bool(true, min_max_heap_full_p(heap), &pass);
    min_max_heap_destroy(&heap);

    heap = min_max_heap_create(0u);
    RESULT_CHECK_bool(false, min_max_heap_full_p(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_full_p, pass);
}

static inline void
unit_test_min_max_heap_cleanup(void)
{
    bool pass;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    min_max_heap_cleanup(heap);

    heap = test_min_max_heap_sample(0x3345, 0x204E);
    min_max_heap_cleanup(heap);

    RESULT_CHECK_bool(false, min_max_heap_full_p(heap), &pass);
    RESULT_CHECK_bool(true, min_max_heap_empty_p(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_cleanup, pass);
}

static inline void
unit_test_min_max_heap_node_find(void)
{
    bool pass;
    uint32 index;
    struct min_max_heap *heap;

    pass = true;
    index = 1u;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, min_max_heap_node_find(heap, index), &pass);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(min_max_heap_link(heap, index),
        min_max_heap_node_find(heap, min_max_heap_nice(heap, index)), &pass);
    index = 0x144Eu;
    RESULT_CHECK_pointer(NULL, min_max_heap_node_find(heap, (sint64)index), &pass);

    index = 0x2u;
    RESULT_CHECK_pointer(min_max_heap_link(heap, index),
        min_max_heap_node_find(heap, min_max_heap_nice(heap, index)), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_find, pass);
}

static inline void
unit_test_min_max_heap_node_find_min(void)
{
    bool pass;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, min_max_heap_node_find_min(heap), &pass);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    RESULT_CHECK_pointer(min_max_heap_link(heap, 1u),
        min_max_heap_node_find_min(heap), &pass);

    RESULT_CHECK_pointer(min_max_heap_link(heap, 1u),
        min_max_heap_node_find_min(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_find_min, pass);
}

static inline void
unit_test_min_max_heap_node_find_max(void)
{
    bool pass;
    uint32 index;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(NULL, min_max_heap_node_find_min(heap), &pass);

    heap = test_min_max_heap_sample(0x1345, 0x104E);

    index = INDEX_ROOT;
    if (min_max_heap_nice(heap, INDEX_L_CHILD(index)) >
        min_max_heap_nice(heap, INDEX_R_CHILD(index))) {
        index = INDEX_L_CHILD(index);
    } else {
        index = INDEX_R_CHILD(index);
    }

    RESULT_CHECK_pointer(min_max_heap_link(heap, index),
        min_max_heap_node_find_max(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_find_min, pass);
}

static inline void
unit_test_min_max_heap_node_depth(void)
{
    bool pass;
    uint32 index;
    struct min_max_heap *heap;

    index = 3u;
    pass = true;
    heap = NULL;

    RESULT_CHECK_uint32(DEPTH_INVALID, min_max_heap_node_depth(heap, index), &pass);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    index = INDEX_INVALID;
    RESULT_CHECK_uint32(DEPTH_INVALID, min_max_heap_node_depth(heap, index), &pass);

    index = INDEX_LAST(heap->alias) + 1;
    RESULT_CHECK_uint32(DEPTH_INVALID, min_max_heap_node_depth(heap, index), &pass);

    index = 1 << 7;
    RESULT_CHECK_uint32(7, min_max_heap_node_depth(heap, index), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_depth, pass);
}

static inline void
unit_test_min_max_heap_node_insert(void)
{
    bool pass;
    uint32 count;
    uint32 size;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;
    count = 0x82;

    min_max_heap_node_insert(heap, &pass, 0u);

    heap = test_min_max_heap_sample(0x345, 0x44E);

    while (count--) {
        size = min_max_heap_size(heap);
        if (min_max_heap_node_find(heap, count)) {
            min_max_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size, min_max_heap_size(heap), &pass);
        } else {
            min_max_heap_node_insert(heap, &pass, count);
            RESULT_CHECK_uint32(size + 1, min_max_heap_size(heap), &pass);
        }
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_insert, pass);
}

static inline void
unit_test_min_max_heap_node_remove_min(void)
{
    bool pass;
    struct min_max_heap *heap;
    struct doubly_linked_list *minimal;

    pass = true;
    heap = NULL;

    min_max_heap_node_remove_min(heap);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    minimal = min_max_heap_node_find_min(heap);
    RESULT_CHECK_pointer(minimal, min_max_heap_node_remove_min(heap), &pass);

    doubly_linked_list_destroy(&minimal);
    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_remove_min, pass);
}

static inline void
unit_test_min_max_heap_node_remove_min_and_destroy(void)
{
    bool pass;
    uint32 size;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    min_max_heap_node_remove_min_and_destroy(heap);

    heap = test_min_max_heap_sample(0x1425, 0x10DE);
    size = min_max_heap_size(heap);

    min_max_heap_node_find_min(heap);
    min_max_heap_node_remove_min_and_destroy(heap);
    size--;
    RESULT_CHECK_uint32(size, min_max_heap_size(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_remove_min_and_destroy, pass);
}

static inline void
unit_test_min_max_heap_node_remove(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct min_max_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;

    min_max_heap_node_remove(heap, 0);

    heap = test_min_max_heap_sample(0x942, 0x73a);
    nice = 0x12345;
    RESULT_CHECK_pointer(NULL, min_max_heap_node_remove(heap, nice), &pass);

    nice = 0x7;
    while (count--) {
        tmp = min_max_heap_node_find(heap, nice);
        if (tmp) {
            RESULT_CHECK_pointer(tmp, min_max_heap_node_remove(heap, nice), &pass);
            doubly_linked_list_destroy(&tmp);
        } else {
            RESULT_CHECK_pointer(NULL, min_max_heap_node_remove(heap, nice), &pass);
        }
        nice--;
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_remove, pass);
}

static inline void
unit_test_min_max_heap_node_remove_and_destroy(void)
{
    bool pass;
    uint32 count;
    sint64 nice;
    struct min_max_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;

    min_max_heap_node_remove(heap, 0);

    heap = test_min_max_heap_sample(0x742, 0x23a);
    nice = 0x12345;
    min_max_heap_node_remove_and_destroy(heap, nice);

    nice = 0x8;
    while (count--) {
        tmp = min_max_heap_node_find(heap, nice);
        if (tmp) {
            min_max_heap_node_remove_and_destroy(heap, nice);
            RESULT_CHECK_pointer(NULL, min_max_heap_node_find(heap, nice), &pass);
        }
        nice--;
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_remove_and_destroy, pass);
}

static inline void
unit_test_min_max_heap_node_remove_max(void)
{
    bool pass;
    struct min_max_heap *heap;
    struct doubly_linked_list *maximal;

    pass = true;
    heap = NULL;

    min_max_heap_node_remove_max(heap);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    maximal = min_max_heap_node_find_max(heap);
    RESULT_CHECK_pointer(maximal, min_max_heap_node_remove_max(heap), &pass);
    doubly_linked_list_destroy(&maximal);
    min_max_heap_destroy(&heap);

    heap = test_min_max_heap_sample(0x5, 0x1);
    maximal = min_max_heap_node_find_max(heap);
    RESULT_CHECK_pointer(maximal, min_max_heap_node_remove_max(heap), &pass);
    doubly_linked_list_destroy(&maximal);
    min_max_heap_destroy(&heap);

    UNIT_TEST_RESULT(min_max_heap_node_remove_max, pass);
}

static inline void
unit_test_min_max_heap_node_remove_max_and_destroy(void)
{
    bool pass;
    uint32 size;
    struct min_max_heap *heap;

    pass = true;
    heap = NULL;

    min_max_heap_node_remove_max_and_destroy(heap);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    size = min_max_heap_size(heap);
    min_max_heap_node_remove_max_and_destroy(heap);
    size--;
    RESULT_CHECK_uint32(size, min_max_heap_size(heap), &pass);
    min_max_heap_destroy(&heap);

    heap = test_min_max_heap_sample(0x1345, 0x1);
    size = min_max_heap_size(heap);
    min_max_heap_node_remove_max_and_destroy(heap);
    size--;
    RESULT_CHECK_uint32(size, min_max_heap_size(heap), &pass);
    min_max_heap_destroy(&heap);

    UNIT_TEST_RESULT(min_max_heap_node_remove_max_and_destroy, pass);
}

static inline void
unit_test_min_max_heap_node_decrease_nice(void)
{
    bool pass;
    uint32 count;
    uint32 offset;
    sint64 nice;
    struct min_max_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x12;
    heap = NULL;
    offset = 0;

    min_max_heap_node_decrease_nice(heap, 0, offset);

    heap = test_min_max_heap_sample(0x345, 0x2E0);
    min_max_heap_node_decrease_nice(heap, 0, offset);
    offset = 0xa;

    while (count--) {
        tmp = min_max_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count - offset;
            if (!min_max_heap_node_find(heap, nice)) {
                min_max_heap_node_decrease_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, min_max_heap_node_find(heap, nice), &pass);
            } else {
                min_max_heap_node_decrease_nice(heap, count, offset);
            }
        } else {
            min_max_heap_node_decrease_nice(heap, count, offset);
        }
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_decrease_nice, pass);
}

static inline void
unit_test_min_max_heap_node_increase_nice(void)
{
    bool pass;
    uint32 count;
    uint32 offset;
    sint64 nice;
    struct min_max_heap *heap;
    struct doubly_linked_list *tmp;

    pass = true;
    count = 0x32;
    heap = NULL;
    offset = 0;

    min_max_heap_node_increase_nice(heap, 0, offset);

    heap = test_min_max_heap_sample(0x342, 0x423a);
    min_max_heap_node_increase_nice(heap, 0, offset);
    offset = 0x14;

    while (count--) {
        tmp = min_max_heap_node_find(heap, count);
        if (tmp) {
            nice = (sint64)count + offset;
            if (!min_max_heap_node_find(heap, nice)) {
                min_max_heap_node_increase_nice(heap, count, offset);
                RESULT_CHECK_pointer(tmp, min_max_heap_node_find(heap, nice), &pass);
            } else {
                min_max_heap_node_increase_nice(heap, count, offset);
            }
        } else {
            min_max_heap_node_increase_nice(heap, count, offset);
        }
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_node_increase_nice, pass);
}

