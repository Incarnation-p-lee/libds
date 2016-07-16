#define HEAP                   maximal_heap
#define INDEX_LAST             maximal_heap_index_last
#define HEAP_val               maximal_heap_val
#define HEAP_nice              maximal_heap_nice
#define HEAP_size              maximal_heap_size
#define HEAP_structure_legal_p utest_maximal_heap_structure_legal_p
#define TEST_HEAP_sample       test_maximal_heap_sample
#define TEST_HEAP_ordered_p    utest_maximal_heap_ordered_p

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

#include "../unit_test_heap.h"

UT_HEAP_structure_legal_p(maximal)
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

#undef HEAP
#undef INDEX_LAST
#undef HEAP_val
#undef HEAP_nice
#undef HEAP_size
#undef HEAP_structure_legal_p
#undef TEST_HEAP_sample
#undef TEST_HEAP_ordered_p

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


static inline bool
utest_maximal_heap_ordered_p(struct maximal_heap *heap)
{
    uint32 index;
    uint32 index_last;
    uint32 index_left;
    uint32 index_right;

    assert_exit(utest_maximal_heap_structure_legal_p(heap));

    index = HEAP_IDX_ROOT;
    index_last = maximal_heap_index_last(heap);

    while (index <= index_last) {
        index_left = HEAP_IDX_CHILD_L(index);
        index_right = HEAP_IDX_CHILD_R(index);

        if (index_left <= index_last &&
            maximal_heap_nice(heap, index) < maximal_heap_nice(heap, index_left)) {
            return false;
        }

        if (index_right <= index_last &&
            maximal_heap_nice(heap, index) < maximal_heap_nice(heap, index_right)) {
            return false;
        }

	index++;
    }

    return true;
}

static inline void
utest_maximal_heap_decrease_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    struct maximal_heap *heap;

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
    struct maximal_heap *heap;

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
    RESULT_CHECK_sint64(nice + offset,
        maximal_heap_nice(heap, HEAP_IDX_ROOT), &pass);

    maximal_heap_destroy(&heap);
    UNIT_TEST_RESULT(maximal_heap_increase_nice, pass);
}

