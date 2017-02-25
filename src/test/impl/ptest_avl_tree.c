#define TREE                   s_avl_tree_t
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

#include "../ptest_tree.h"

PT_TREE_create(avl)
PT_TREE_initial(avl)
PT_TREE_destroy(avl)
PT_TREE_find(avl)
PT_TREE_find_min(avl)
PT_TREE_find_max(avl)
PT_TREE_height(avl)
PT_TREE_contains_p(avl)
PT_TREE_insert(avl)
PT_TREE_remove(avl)
PT_TREE_iterate(avl)

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
ptest_avl_tree_balanced_p(uint32 count)
{
    struct avl_tree *tree;

    tree = test_avl_tree_sample(0xa9, 0x43);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_balanced_p(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_balanced_p);
}

