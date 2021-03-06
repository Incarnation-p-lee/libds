#include "types.h"
#include "depends.h"
#include "defines.h"
#include "data_structure_types.h"
#include "universal.h"

#include "linked_list_declaration.h"
#include "linked_list.h"

#if DEBUG
    #include "impl/linked_list_debug.c"
#endif

#include "impl/single_linked_list.c"
#include "impl/doubly_linked_list.c"
#include "impl/skip_linked_list.c"
#include "impl/linked_list_optimize.c"
