#include "types.h"
#include "depends.h"
#include "defines.h"
#include "data_structure_types.h"
#include "universal.h"

#include "graph.h"
#include "graph_declaration.h"

#if defined DEBUG
    #include "impl/graph_debug.c"
#endif

#include "impl/graph_util.c"
#include "impl/graph_internal.c"
#include "impl/directed_graph.c"
#include "impl/indirected_graph.c"

