#include "types.h"
#include "depends.h"
#include "defines.h"
#include "data_structure_types.h"
#include "universal.h"

#include "queue.h"
#include "queue_optimize.h"
#include "queue_declaration.h"

#if defined DEBUG
    #include "impl/queue_debug.c"
#endif

#include "impl/array_queue.c"
#include "impl/stacked_queue.c"
#include "impl/doubly_end_queue.c"
