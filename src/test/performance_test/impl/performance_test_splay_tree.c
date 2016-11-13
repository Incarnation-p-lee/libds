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

#include "../performance_test_tree.h"

PT_TREE_create(splay)
PT_TREE_initial(splay)
PT_TREE_destroy(splay)
PT_TREE_height(splay)
PT_TREE_contains_p(splay)
PT_TREE_insert(splay)
PT_TREE_iterate(splay)

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
ptest_splay_tree_find(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x21352, 0x12de2);
    tmp = splay_tree_find_max(&tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find(&tree, splay_tree_nice(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find);
}

static void
ptest_splay_tree_find_min(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find_min(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find_min);
}

static void
ptest_splay_tree_find_max(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find_max(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find_max);
}

static void
ptest_splay_tree_remove(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x4234, 0x2823);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_find_max(&tree);
        splay_tree_remove(&tree, tmp);
        splay_tree_destroy(&tmp);

        tmp = splay_tree_create();
        splay_tree_initial(tmp, count);
        splay_tree_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_remove);
}

