#define HEAP                   maximal_heap
#define INDEX_LAST             maximal_heap_index_last
#define HEAP_val               maximal_heap_val
#define HEAP_nice              maximal_heap_nice
#define HEAP_size              maximal_heap_size
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
#define HEAP_decrease_nice     maximal_heap_decrease_nice
#define HEAP_increase_nice     maximal_heap_increase_nice
#define HEAP_build             maximal_heap_build

#include "../performance_test_heap.h"

PT_HEAP_create(maximal)
PT_HEAP_destroy(maximal)
PT_HEAP_empty_p(maximal)
PT_HEAP_full_p(maximal)
PT_HEAP_cleanup(maximal)
PT_HEAP_get_max(maximal)
PT_HEAP_insert(maximal)
PT_HEAP_remove(maximal)
PT_HEAP_remove_max(maximal)
PT_HEAP_decrease_nice(maximal)
PT_HEAP_increase_nice(maximal)
PT_HEAP_build(maximal)

#undef HEAP
#undef INDEX_LAST
#undef HEAP_val
#undef HEAP_nice
#undef HEAP_size
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
#undef HEAP_decrease_nice
#undef HEAP_increase_nice
#undef HEAP_build

