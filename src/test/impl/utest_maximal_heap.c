#define HEAP                   maximal_heap
#define HEAP_val               maximal_heap_val
#define HEAP_nice              maximal_heap_nice
#define HEAP_size              maximal_heap_size
#define HEAP_legal_p           maximal_heap_legal_p
#define HEAP_illegal_p         maximal_heap_illegal_p
#define HEAP_ordered_p         maximal_heap_ordered_p
#define HEAP_index_last        maximal_heap_index_last
#define HEAP_index_limit       maximal_heap_index_limit
#define TEST_HEAP_sample       test_maximal_heap_sample

#define HEAP_create            maximal_heap_create
#define HEAP_destroy           maximal_heap_destroy
#define HEAP_empty_p           maximal_heap_empty_p
#define HEAP_full_p            maximal_heap_full_p
#define HEAP_cleanup           maximal_heap_cleanup
#define HEAP_get_max           maximal_heap_get_max
#define HEAP_insert            maximal_heap_insert
#define HEAP_remove            maximal_heap_remove
#define HEAP_remove_max        maximal_heap_remove_max
#define HEAP_build             maximal_heap_build
#define HEAP_find_index        maximal_heap_find_index

#include "../utest_heap.h"

UT_HEAP_create(maximal)
UT_HEAP_destroy(maximal)
UT_HEAP_empty_p(maximal)
UT_HEAP_full_p(maximal)
UT_HEAP_cleanup(maximal)
UT_HEAP_get_max(maximal)
UT_HEAP_insert(maximal)
UT_HEAP_remove(maximal)
UT_HEAP_remove_max(maximal)
UT_HEAP_build(maximal)
UT_HEAP_find_index(maximal)

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

#undef HEAP_create
#undef HEAP_destroy
#undef HEAP_empty_p
#undef HEAP_full_p
#undef HEAP_cleanup
#undef HEAP_get_max
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_max
#undef HEAP_build
#undef HEAP_find_index


static inline void
utest_maximal_heap_decrease_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    s_maximal_heap_t *heap;

    pass = true;
    heap = NULL;
    offset = 0;

    maximal_heap_decrease_nice(heap, 0, offset);

    heap = test_maximal_heap_sample(0x345, 0x2E0);
    maximal_heap_decrease_nice(heap, 0, offset);

    offset = 0xa7ec;
    index = 0x123;
    nice = maximal_heap_nice(heap, index);

    maximal_heap_decrease_nice(heap, index, offset);
    RESULT_CHECK_NOT_LESS_sint64(maximal_heap_nice(heap, index),
        nice - offset, &pass);

    maximal_heap_destroy(&heap);
    UNIT_TEST_RESULT(maximal_heap_decrease_nice, pass);
}

static inline void
utest_maximal_heap_increase_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    s_maximal_heap_t *heap;

    pass = true;
    heap = NULL;
    offset = 0;

    maximal_heap_increase_nice(heap, 0, offset);

    heap = test_maximal_heap_sample(0x345, 0x2E0);
    maximal_heap_increase_nice(heap, 0, offset);

    offset = 0xa7ec;
    index = 0x123;
    nice = maximal_heap_nice(heap, index);

    maximal_heap_increase_nice(heap, index, offset);
    RESULT_CHECK_sint64(nice + offset, maximal_heap_nice(heap, HEAP_INDEX_ROOT),
        &pass);

    maximal_heap_destroy(&heap);
    UNIT_TEST_RESULT(maximal_heap_increase_nice, pass);
}

