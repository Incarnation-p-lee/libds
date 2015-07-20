#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "types.h"
#include "defines.h"
#include "util.h"
#include "data_structure_types.h"
#include "data_structure_defines.h"

#include "hash.h"
#include "impl/hashing_table_internal.h"

#include "impl/hashing_table_internal.c"
#include "impl/hashing_table_debug.c"
#include "impl/hashing_function.c"
#include "impl/separate_chain_hash.c"
#include "impl/open_addressing_hash.c"
