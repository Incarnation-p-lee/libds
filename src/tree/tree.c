#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "types.h"
#include "defines.h"
#include "util.h"
#include "data_structure_types.h"
#include "data_structure_defines.h"

#include "tree.h"
#include "tree_declaration.h"
#include "tree_optimize.h"

#if defined DEBUG
    #include "impl/binary_search_tree_debug.c"
    #include "impl/avl_tree_debug.c"
    #include "impl/splay_tree_debug.c"
#endif

#include "impl/binary_search_tree.c"
#include "impl/avl_tree.c"
#include "impl/splay_tree.c"
#include "impl/binary_indexed_tree.c"

