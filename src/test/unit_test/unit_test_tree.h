#ifndef HAVE_UNIT_TEST_TREE_H
#define HAVE_UNIT_TEST_TREE_H

#define UT_TREE_create(name)                                   \
static void                                                    \
utest_##name##_tree_create(void)                               \
{                                                              \
    bool pass;                                                 \
    struct TREE *tree;                                         \
                                                               \
    pass = true;                                               \
    tree = TREE_create();                                      \
                                                               \
    RESULT_CHECK_pointer(NULL, TREE_child_left(tree), &pass);  \
    RESULT_CHECK_pointer(NULL, TREE_child_right(tree), &pass); \
    RESULT_CHECK_sint64(0x0, TREE_node_nice(tree), &pass);     \
                                                               \
    TREE_destroy(&tree);                                       \
    UNIT_TEST_RESULT(name##_tree_create, pass);                \
}

#define UT_TREE_node_create(name)                                   \
static void                                                    \
utest_##name##_tree_node_create(void)                               \
{                                                              \
    bool pass;
    sint64 nice;
    struct TREE *tree;
    struct doubly_linked_list *link;

    pass = true;
    nice = 0xfade;
    tree = TREE_node_create(&pass, nice);

    RESULT_CHECK_pointer(NULL, TREE_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, TREE_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, TREE_node_nice(tree), &pass);

    link = TREE_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(link), &pass);

    TREE_destroy(&tree);
    UNIT_TEST_RESULT(name##_tree_node_create, pass);
}




#endif

