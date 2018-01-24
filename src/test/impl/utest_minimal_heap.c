#define HEAP                   minimal_heap
#define HEAP_val               minimal_heap_val
#define HEAP_nice              minimal_heap_nice
#define HEAP_size              minimal_heap_size
#define HEAP_legal_p           minimal_heap_legal_p
#define HEAP_illegal_p         minimal_heap_illegal_p
#define HEAP_ordered_p         minimal_heap_ordered_p
#define HEAP_index_last        minimal_heap_index_last
#define HEAP_index_limit       minimal_heap_index_limit
#define TEST_HEAP_sample       test_minimal_heap_sample

#define HEAP_create            minimal_heap_create
#define HEAP_destroy           minimal_heap_destroy
#define HEAP_empty_p           minimal_heap_empty_p
#define HEAP_full_p            minimal_heap_full_p
#define HEAP_cleanup           minimal_heap_cleanup
#define HEAP_get_min           minimal_heap_get_min
#define HEAP_insert            minimal_heap_insert
#define HEAP_remove            minimal_heap_remove
#define HEAP_remove_min        minimal_heap_remove_min
#define HEAP_build             minimal_heap_build
#define HEAP_find_index        minimal_heap_find_index

#include "../utest_heap.h"

UT_HEAP_create(minimal)
UT_HEAP_destroy(minimal)
UT_HEAP_empty_p(minimal)
UT_HEAP_full_p(minimal)
UT_HEAP_cleanup(minimal)
UT_HEAP_get_min(minimal)
UT_HEAP_insert(minimal)
UT_HEAP_remove(minimal)
UT_HEAP_remove_min(minimal)
UT_HEAP_build(minimal)
UT_HEAP_find_index(minimal)

#undef HEAP
#undef HEAP_val
#undef HEAP_nice
#undef HEAP_size
#undef HEAP_legal_p
#undef HEAP_illegal_p
#undef HEAP_ordered_p
#undef HEAP_index_last
#undef HEAP_index_limit
#undef TEST_HEAP_sample
#undef TEST_HEAP_ordered_p

#undef HEAP_create
#undef HEAP_destroy
#undef HEAP_empty_p
#undef HEAP_full_p
#undef HEAP_cleanup
#undef HEAP_get_min
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_min
#undef HEAP_build
#undef HEAP_find_index


static inline void
utest_minimal_heap_decrease_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    s_minimal_heap_t *heap;

    pass = true;
    heap = NULL;
    offset = 0;

    minimal_heap_decrease_nice(heap, 0, offset);

    heap = test_minimal_heap_sample(0x345, 0x2E0);
    minimal_heap_decrease_nice(heap, 0, offset);

    offset = 0xa7ec;
    index = 0x123;
    nice = minimal_heap_nice(heap, index);

    minimal_heap_decrease_nice(heap, index, offset);
    RESULT_CHECK_sint64(nice - offset, minimal_heap_nice(heap, HEAP_INDEX_ROOT),
        &pass);

    minimal_heap_destroy(&heap);
    UNIT_TEST_RESULT(minimal_heap_decrease_nice, pass);
}

static inline void
utest_minimal_heap_increase_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    s_minimal_heap_t *heap;

    pass = true;
    heap = NULL;
    offset = 0;

    minimal_heap_increase_nice(heap, 0, offset);

    heap = test_minimal_heap_sample(0x345, 0x2E0);
    minimal_heap_increase_nice(heap, 0, offset);

    offset = 0xa7ec;
    index = 0x123;
    nice = minimal_heap_nice(heap, index);

    minimal_heap_increase_nice(heap, index, offset);
    RESULT_CHECK_NOT_LESS_sint64(nice + offset,
        minimal_heap_nice(heap, index), &pass);

    minimal_heap_destroy(&heap);
    UNIT_TEST_RESULT(minimal_heap_increase_nice, pass);
}

