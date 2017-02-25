#define HEAP                   minimal_heap
#define INDEX_LAST             minimal_heap_index_last
#define HEAP_val               minimal_heap_val
#define HEAP_nice              minimal_heap_nice
#define HEAP_size              minimal_heap_size
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
#define HEAP_decrease_nice     minimal_heap_decrease_nice
#define HEAP_increase_nice     minimal_heap_increase_nice
#define HEAP_build             minimal_heap_build

#include "../ptest_heap.h"

PT_HEAP_create(minimal)
PT_HEAP_destroy(minimal)
PT_HEAP_empty_p(minimal)
PT_HEAP_full_p(minimal)
PT_HEAP_cleanup(minimal)
PT_HEAP_get_min(minimal)
PT_HEAP_insert(minimal)
PT_HEAP_remove(minimal)
PT_HEAP_remove_min(minimal)
PT_HEAP_decrease_nice(minimal)
PT_HEAP_increase_nice(minimal)
PT_HEAP_build(minimal)

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
#undef HEAP_get_min
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_min
#undef HEAP_decrease_nice
#undef HEAP_increase_nice
#undef HEAP_build

