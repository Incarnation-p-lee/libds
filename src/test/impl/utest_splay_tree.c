#define TREE                   s_splay_tree_t
#define TREE_nice              splay_tree_nice
#define TREE_val               splay_tree_val
#define TREE_left              splay_tree_left
#define TREE_right             splay_tree_right
#define TEST_tree_sample       test_splay_tree_sample

#define TREE_create            splay_tree_create
#define TREE_initial           splay_tree_initial
#define TREE_destroy           splay_tree_destroy
#define TREE_height            splay_tree_height
#define TREE_contains_p        splay_tree_contains_p
#define TREE_insert            splay_tree_insert
#define TREE_iterate           splay_tree_iterate

#include "../utest_tree.h"

UT_TREE_create(splay)
UT_TREE_initial(splay)
UT_TREE_destroy(splay)
UT_TREE_height(splay)
UT_TREE_insert(splay)
UT_TREE_iterate(splay)

#undef TREE
#undef TREE_nice
#undef TREE_val
#undef TREE_left
#undef TREE_right
#undef TEST_tree_sample

#undef TREE_create
#undef TREE_initial
#undef TREE_destroy
#undef TREE_height
#undef TREE_contains_p
#undef TREE_insert
#undef TREE_iterate

static void
utest_splay_tree_find(void)
{
    bool pass;
    sint64 nice;
    s_splay_tree_t *tree;
    s_splay_tree_t *tmp;

    pass = true;
    tree = test_splay_tree_sample(0x13FA, 0x143A);

    nice = splay_tree_nice(tree);
    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_find(NULL, nice), &pass);
    RESULT_CHECK_pointer(tree, splay_tree_find(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_find(&tree, 0xFFFFFFF), &pass);

    tmp = splay_tree_find_min(&tree);
    nice = splay_tree_nice(tree);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(tmp, splay_tree_find(&tree, nice), &pass);

    tmp = splay_tree_find_max(&tree);
    nice = splay_tree_nice(tree);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(tmp, splay_tree_find(&tree, nice), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_find, pass);
}

static void
utest_splay_tree_find_min(void)
{
    bool pass;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    pass = true;
    tree = test_splay_tree_sample(0xF1C2, 0xD482);

    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_find_min(NULL), &pass);
    tmp = splay_tree_find_min(&tree);

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_left(tmp), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_find_min, pass);
}

static void
utest_splay_tree_find_max(void)
{
    bool pass;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    pass = true;
    tree = test_splay_tree_sample(0xF2E4, 0x9B2A);

    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_find_max(NULL), &pass);
    tmp = splay_tree_find_max(&tree);

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_right(tmp), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_find_max, pass);
}

static void
utest_splay_tree_contains_p(void)
{
    bool pass;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;
    s_splay_tree_t *fake;

    pass = true;
    tree = test_splay_tree_sample(0x14F0, 0x73BD);
    tmp = splay_tree_create();
    splay_tree_initial(tmp, 0x1234);

    RESULT_CHECK_bool(false, splay_tree_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_contains_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_contains_p(tree, tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_find_max(&tree);
    RESULT_CHECK_bool(true, splay_tree_contains_p(tree, tmp), &pass);

    fake = splay_tree_create();
    splay_tree_initial(fake, splay_tree_nice(tmp));
    RESULT_CHECK_bool(false, splay_tree_contains_p(tree, fake), &pass);

    splay_tree_destroy(&fake);
    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_contains_p, pass);
}

static void
utest_splay_tree_remove(void)
{
    bool pass;
    sint64 nice;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_remove(&tree, NULL), &pass);

    tree = test_splay_tree_sample(0x2421, 0x32CD);
    tmp = tree;
    nice = splay_tree_nice(tmp);
    tmp = splay_tree_remove(&tree, tree);
    RESULT_CHECK_sint64(nice, splay_tree_nice(tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_find_min(&tree);
    nice = splay_tree_nice(tmp);
    tmp = splay_tree_remove(&tree, tmp);
    RESULT_CHECK_sint64(nice, splay_tree_nice(tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_find_max(&tree);
    nice = splay_tree_nice(tmp);
    tmp = splay_tree_remove(&tree, tmp);
    RESULT_CHECK_sint64(nice, splay_tree_nice(tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_create();
    splay_tree_initial(tmp, 0x7FFFFF);
    nice = splay_tree_nice(tmp);
    RESULT_CHECK_pointer(NULL, splay_tree_remove(&tree, tmp), &pass);
    splay_tree_destroy(&tmp);
    splay_tree_destroy(&tree);

    tree = splay_tree_create();
    nice = 0x7fffff;
    splay_tree_initial(tree, nice);
    tmp = tree;
    RESULT_CHECK_pointer(tmp, splay_tree_remove(&tree, tree), &pass);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    splay_tree_destroy(&tmp);
    UNIT_TEST_RESULT(splay_tree_remove, pass);
}

