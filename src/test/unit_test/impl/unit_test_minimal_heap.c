#define HEAP                   minimal_heap
#define HEAP_val               minimal_heap_val
#define HEAP_nice              minimal_heap_nice
#define HEAP_size              minimal_heap_size
#define HEAP_structure_legal_p utest_minimal_heap_structure_legal_p
#define TEST_HEAP_sample       test_minimal_heap_sample
#define TEST_HEAP_ordered_p    utest_minimal_heap_ordered_p

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

#include "../unit_test_heap.h"

UT_HEAP_structure_legal_p(minimal)
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

#undef HEAP
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
#undef HEAP_get_min
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_min
#undef HEAP_build


static inline bool
utest_minimal_heap_ordered_p(struct minimal_heap *heap)
{
    uint32 index;
    uint32 index_last;
    uint32 index_left;
    uint32 index_right;

    dp_assert(utest_minimal_heap_structure_legal_p(heap));

    index = INDEX_ROOT;
    index_last = minimal_heap_index_last(heap);

    while (index <= index_last) {
        index_left = INDEX_L_CHILD(index);
        index_right = INDEX_R_CHILD(index);

        if (index_left <= index_last &&
            minimal_heap_nice(heap, index) > minimal_heap_nice(heap, index_left)) {
            return false;
        }

        if (index_right <= index_last &&
            minimal_heap_nice(heap, index) > minimal_heap_nice(heap, index_right)) {
            return false;
        }

	index++;
    }

    return true;
}

static inline void
utest_minimal_heap_decrease_nice(void)
{
    bool pass;
    sint64 nice;
    uint32 index;
    uint32 offset;
    struct minimal_heap *heap;

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
    RESULT_CHECK_sint64(nice - offset, minimal_heap_nice(heap, INDEX_ROOT),
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
    struct minimal_heap *heap;

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

