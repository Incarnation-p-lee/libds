#define TREE                   binary_search_tree
#define TREE_nice              binary_search_tree_nice
#define TREE_val               binary_search_tree_val
#define TREE_left              binary_search_tree_left
#define TREE_right             binary_search_tree_right
#define TEST_tree_sample       test_binary_search_tree_sample

#define TREE_create            binary_search_tree_create
#define TREE_initial           binary_search_tree_initial
#define TREE_destroy           binary_search_tree_destroy
#define TREE_find              binary_search_tree_find
#define TREE_find_min          binary_search_tree_find_min
#define TREE_find_max          binary_search_tree_find_max
#define TREE_height            binary_search_tree_height
#define TREE_contains_p        binary_search_tree_contains_p
#define TREE_insert            binary_search_tree_insert
#define TREE_remove            binary_search_tree_remove
#define TREE_iterate           binary_search_tree_iterate

#include "../performance_test_tree.h"

PT_TREE_create(binary_search)
PT_TREE_initial(binary_search)
PT_TREE_destroy(binary_search)
PT_TREE_find(binary_search)
PT_TREE_find_min(binary_search)
PT_TREE_find_max(binary_search)
PT_TREE_height(binary_search)
PT_TREE_contains_p(binary_search)
PT_TREE_insert(binary_search)
PT_TREE_remove(binary_search)
PT_TREE_iterate(binary_search)

#undef TREE
#undef TREE_nice
#undef TREE_val
#undef TREE_left
#undef TREE_right
#undef TEST_tree_sample

#undef TREE_create
#undef TREE_initial
#undef TREE_destroy
#undef TREE_find
#undef TREE_find_min
#undef TREE_find_max
#undef TREE_height
#undef TREE_contains_p
#undef TREE_insert
#undef TREE_remove
#undef TREE_iterate

