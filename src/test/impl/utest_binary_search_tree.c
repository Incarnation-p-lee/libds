#define TREE                   s_binary_search_tree_t
#define TREE_nice              binary_search_tree_nice
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
#define TREE_remove            binary_search_tree_remove
#define TREE_iterate           binary_search_tree_iterate

#include "../utest_tree.h"

UT_TREE_create(binary_search)
UT_TREE_initial(binary_search)
UT_TREE_destroy(binary_search)
UT_TREE_find(binary_search)
UT_TREE_find_min(binary_search)
UT_TREE_find_max(binary_search)
UT_TREE_height(binary_search)
UT_TREE_contains_p(binary_search)
UT_TREE_remove(binary_search)
UT_TREE_iterate(binary_search)

#undef TREE
#undef TREE_nice
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
#undef TREE_remove
#undef TREE_iterate

static void
utest_binary_search_tree_insert(void)
{
    bool pass;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    UNIT_TEST_BEGIN(binary_search_tree_insert);

    pass = true;
    tree = test_binary_search_tree_sample(0x3321, 0xA2B);
    tmp = binary_search_tree_create();
    binary_search_tree_initial(tmp, 0xFFFDEA);

    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_insert(tree, NULL), &pass);
    RESULT_CHECK_pointer(tmp, binary_search_tree_insert(tree, tmp), &pass);
    RESULT_CHECK_bool(true, binary_search_tree_contains_p(tree, tmp), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_insert(tree, tmp), &pass);

    tmp = binary_search_tree_create();
    binary_search_tree_initial(tmp, 0xFFFDEA);
    RESULT_CHECK_pointer(tmp, binary_search_tree_insert(tree, tmp), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_insert, pass);
}

