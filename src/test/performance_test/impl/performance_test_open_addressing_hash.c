#define HASH                       open_addressing_hash
#define TEST_HASH_sample           test_open_addressing_hash_sample

#define HASH_create                open_addressing_hash_create
#define HASH_destroy               open_addressing_hash_destroy
#define HASH_load_factor_calculate open_addressing_hash_load_factor_calculate
#define HASH_insert                open_addressing_hash_insert
#define HASH_remove                open_addressing_hash_remove
#define HASH_find                  open_addressing_hash_find
#define HASH_rehashing             open_addressing_hash_rehashing

#include "../performance_test_hash.h"

PT_HASH_create(open_addressing)
PT_HASH_destroy(open_addressing)
PT_HASH_load_factor_calculate(open_addressing)
PT_HASH_insert(open_addressing)
PT_HASH_remove(open_addressing)
PT_HASH_find(open_addressing)
PT_HASH_rehashing(open_addressing)

#undef HASH
#undef TEST_HASH_sample

#undef HASH_create
#undef HASH_destroy
#undef HASH_load_factor_calculate
#undef HASH_insert
#undef HASH_remove
#undef HASH_find
#undef HASH_rehashing

