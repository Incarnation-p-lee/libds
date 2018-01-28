#define HEAP                   min_max_heap
#define HEAP_val               min_max_heap_val
#define HEAP_nice              min_max_heap_nice
#define HEAP_size              min_max_heap_size
#define HEAP_legal_p           min_max_heap_legal_p
#define HEAP_illegal_p         min_max_heap_illegal_p
#define HEAP_index_last        min_max_heap_index_last
#define HEAP_index_limit       min_max_heap_index_limit
#define TEST_HEAP_sample       test_min_max_heap_sample

#define HEAP_create            min_max_heap_create
#define HEAP_destroy           min_max_heap_destroy
#define HEAP_empty_p           min_max_heap_empty_p
#define HEAP_full_p            min_max_heap_full_p
#define HEAP_cleanup           min_max_heap_cleanup
#define HEAP_get_min           min_max_heap_get_min
#define HEAP_get_max           min_max_heap_get_max
#define HEAP_insert            min_max_heap_insert
#define HEAP_remove            min_max_heap_remove
#define HEAP_remove_min        min_max_heap_remove_min
#define HEAP_remove_max        min_max_heap_remove_max

#include "../utest_heap.h"

UT_HEAP_create(min_max)
UT_HEAP_destroy(min_max)
UT_HEAP_empty_p(min_max)
UT_HEAP_full_p(min_max)
UT_HEAP_cleanup(min_max)
UT_HEAP_get_min(min_max)
UT_HEAP_insert(min_max)
UT_HEAP_remove(min_max)
UT_HEAP_remove_min(min_max)
UT_HEAP_remove_max(min_max)

#undef HEAP
#undef HEAP_val
#undef HEAP_nice
#undef HEAP_size
#undef HEAP_legal_p
#undef HEAP_illegal_p
#undef HEAP_index_last
#undef HEAP_index_limit
#undef TEST_HEAP_sample

#undef HEAP_create
#undef HEAP_destroy
#undef HEAP_empty_p
#undef HEAP_full_p
#undef HEAP_cleanup
#undef HEAP_get_min
#undef HEAP_get_max
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_min
#undef HEAP_remove_max


static inline void
utest_min_max_heap_get_max(void)
{
    bool pass;
    void *val, *val_tmp;
    s_min_max_heap_t *heap;

    pass = true;
    heap = NULL;

    UNIT_TEST_BEGIN(min_max_heap_get_max);

    RESULT_CHECK_pointer(PTR_INVALID, min_max_heap_get_max(heap), &pass);

    heap = test_min_max_heap_sample(0x732, 1);
    val = min_max_heap_val(heap, HEAP_INDEX_ROOT);
    RESULT_CHECK_pointer(val, min_max_heap_get_max(heap), &pass);
    min_max_heap_destroy(&heap);

    heap = test_min_max_heap_sample(0x1022, 0x83a);
    val = min_max_heap_val(heap, HEAP_INDEX_ROOT + 1);
    val_tmp = min_max_heap_val(heap, HEAP_INDEX_ROOT + 2);

    if (min_max_heap_nice(heap, HEAP_INDEX_ROOT + 1)
        < min_max_heap_nice(heap, HEAP_INDEX_ROOT + 2)) {
        val = val_tmp;
    }

    RESULT_CHECK_pointer(val, min_max_heap_get_max(heap), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_get_max, pass);
}

static inline void
utest_min_max_heap_depth(void)
{
    bool pass;
    uint32 index;
    s_min_max_heap_t *heap;

    index = 3u;
    pass = true;
    heap = NULL;

    RESULT_CHECK_uint32(SIZE_INVALID, min_max_heap_depth(heap, index), &pass);

    heap = test_min_max_heap_sample(0x1345, 0x104E);
    index = HEAP_INDEX_INVALID;
    RESULT_CHECK_uint32(SIZE_INVALID, min_max_heap_depth(heap, index), &pass);

    index = min_max_heap_index_last(heap) + 1;
    RESULT_CHECK_uint32(SIZE_INVALID, min_max_heap_depth(heap, index), &pass);

    index = 1 << 7;
    RESULT_CHECK_uint32(7, min_max_heap_depth(heap, index), &pass);

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_depth, pass);
}

static inline void
utest_min_max_heap_decrease_nice(void)
{
    void *val;
    bool pass;
    uint32 count;
    uint32 offset;
    s_min_max_heap_t *heap;

    pass = true;
    heap = NULL;

    heap = test_min_max_heap_sample(0x3d21, 0x102a);

    min_max_heap_decrease_nice(NULL, 0, 0);
    min_max_heap_decrease_nice(heap, 1, 0);
    min_max_heap_decrease_nice(heap, 0, 1);

    count = 0x12;
    offset = 0x4321;
    while (count-- > 1) {
        val = min_max_heap_val(heap, count);
        min_max_heap_decrease_nice(heap, count, offset);
        RESULT_CHECK_pointer(min_max_heap_get_min(heap), val, &pass);
        offset <<= 1;
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_decrease_nice, pass);
}

static inline void
utest_min_max_heap_increase_nice(void)
{
    void *val;
    bool pass;
    uint32 count;
    uint32 offset;
    s_min_max_heap_t *heap;

    pass = true;
    heap = NULL;

    heap = test_min_max_heap_sample(0x3d21, 0x102a);

    min_max_heap_increase_nice(NULL, 0, 0);
    min_max_heap_increase_nice(heap, 1, 0);
    min_max_heap_increase_nice(heap, 0, 1);

    count = 0x12;
    offset = 0x4321;
    while (count-- > 1) {
        val = min_max_heap_val(heap, count);
        min_max_heap_increase_nice(heap, count, offset);
        RESULT_CHECK_pointer(min_max_heap_get_max(heap), val, &pass);
        offset <<= 1;
    }

    min_max_heap_destroy(&heap);
    UNIT_TEST_RESULT(min_max_heap_increase_nice, pass);
}

