#include "types.h"
#include "depends.h"
#include "defines.h"
#include "data_structure_types.h"
#include "universal.h"

#include "hash.h"
#include "hash_declaration.h"

#if defined DEBUG
#include "impl/hashing_table_debug.c"
#endif

#include "impl/hashing_table_internal.c"
#include "impl/hashing_function.c"
#include "impl/separate_chain_hash.c"
#include "impl/open_addressing_hash.c"
