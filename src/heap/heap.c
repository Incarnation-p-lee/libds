#include "types.h"
#include "depends.h"
#include "defines.h"
#include "util.h"
#include "data_structure_types.h"
#include "data_structure_defines.h"

#include "heap_declaration.h"
#include "heap.h"
#include "heap_optimize.h"

#if defined DEBUG
#include "impl/heap_debug.c"
#endif

#include "impl/binary_heap_order.c"
#include "impl/binary_heap_internal.c"
#include "impl/minimal_heap.c"
#include "impl/maximal_heap.c"
#include "impl/min_max_heap.c"
#include "impl/leftist_heap.c"

