#define HEAP                   min_max_heap
#define HEAP_val               min_max_heap_val
#define HEAP_nice              min_max_heap_nice
#define HEAP_size              min_max_heap_size
#define TEST_HEAP_sample       test_min_max_heap_sample

#define HEAP_create            min_max_heap_create
#define HEAP_destroy           min_max_heap_destroy
#define HEAP_empty_p           min_max_heap_empty_p
#define HEAP_full_p            min_max_heap_full_p
#define HEAP_cleanup           min_max_heap_cleanup
#define HEAP_depth             min_max_heap_depth
#define HEAP_get_min           min_max_heap_get_min
#define HEAP_get_max           min_max_heap_get_max
#define HEAP_insert            min_max_heap_insert
#define HEAP_remove            min_max_heap_remove
#define HEAP_remove_min        min_max_heap_remove_min
#define HEAP_remove_max        min_max_heap_remove_max
#define HEAP_decrease_nice     min_max_heap_decrease_nice
#define HEAP_increase_nice     min_max_heap_increase_nice

#include "../ptest_heap.h"

PT_HEAP_create(min_max)
PT_HEAP_destroy(min_max)
PT_HEAP_empty_p(min_max)
PT_HEAP_full_p(min_max)
PT_HEAP_cleanup(min_max)
PT_HEAP_depth(min_max)
PT_HEAP_get_min(min_max)
PT_HEAP_get_max(min_max)
PT_HEAP_insert(min_max)
PT_HEAP_remove(min_max)
PT_HEAP_remove_min(min_max)
PT_HEAP_remove_max(min_max)
PT_HEAP_decrease_nice(min_max)
PT_HEAP_increase_nice(min_max)

#undef HEAP
#undef HEAP_val
#undef HEAP_nice
#undef HEAP_size
#undef TEST_HEAP_sample

#undef HEAP_create
#undef HEAP_destroy
#undef HEAP_empty_p
#undef HEAP_full_p
#undef HEAP_cleanup
#undef HEAP_depth
#undef HEAP_get_min
#undef HEAP_get_max
#undef HEAP_insert
#undef HEAP_remove
#undef HEAP_remove_min
#undef HEAP_remove_max
#undef HEAP_decrease_nice
#undef HEAP_increase_nice

