#include "depends.h"
#include "types.h"
#include "defines.h"
#include "util.h"
#include "data_structure_types.h"
#include "data_structure_defines.h"

#include "hash.h"
#include "hash_declaration.h"

#if defined DEBUG
#include "impl/hashing_table_debug.c"
#endif

#include "impl/hashing_table_internal.c"
#include "impl/hashing_function.c"
#include "impl/separate_chain_hash.c"
#include "impl/open_addressing_hash.c"
