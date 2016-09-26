#define TREE                   avl_tree
#define TREE_nice              avl_tree_nice
#define TREE_val               avl_tree_val
#define TREE_left              avl_tree_left
#define TREE_right             avl_tree_right
#define TEST_tree_sample       test_avl_tree_sample

#define TREE_create            avl_tree_create
#define TREE_initial           avl_tree_initial
#define TREE_destroy           avl_tree_destroy
#define TREE_find              avl_tree_find
#define TREE_find_min          avl_tree_find_min
#define TREE_find_max          avl_tree_find_max
#define TREE_height            avl_tree_height
#define TREE_contains_p        avl_tree_contains_p
#define TREE_insert            avl_tree_insert
#define TREE_remove            avl_tree_remove
#define TREE_iterate           avl_tree_iterate

#include "../unit_test_tree.h"

UT_TREE_create(avl)
UT_TREE_initial(avl)
UT_TREE_destroy(avl)
UT_TREE_find(avl)
UT_TREE_find_min(avl)
UT_TREE_find_max(avl)
UT_TREE_height(avl)
UT_TREE_contains_p(avl)
UT_TREE_insert(avl)
UT_TREE_remove(avl)
UT_TREE_iterate(avl)

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

static void
utest_avl_tree_balanced_p(void)
{
    bool pass;
    s_avl_tree_t *tree;
    s_avl_tree_t *tmp;

    pass = true;
    UNIT_TEST_BEGIN(avl_tree_balanced_p);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(NULL), &pass);

    tree = test_avl_tree_sample(0x48EA, 0x3D64);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_create();
    avl_tree_initial(tmp, 0x1234);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tmp), &pass);
    avl_tree_destroy(&tmp);

    tmp = avl_tree_create();
    avl_tree_initial(tmp, 0xFFFFFFE);
    avl_tree_insert(&tree, tmp);
    tmp = avl_tree_create();
    avl_tree_initial(tmp, 0xFFFFFFF);
    avl_tree_insert(&tree, tmp);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_create();
    avl_tree_initial(tmp, 0xFFFFFFF);
    avl_tree_insert(&tree, tmp);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_balanced_p, pass);
}

