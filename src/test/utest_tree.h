#ifndef HAVE_UNIT_TEST_TREE_H
#define HAVE_UNIT_TEST_TREE_H

#define UT_TREE_create(name)                                   \
static void                                                    \
utest_##name##_tree_create(void)                               \
{                                                              \
    bool pass;                                                 \
    TREE *tree;                                                \
                                                               \
    pass = true;                                               \
    tree = TREE_create();                                      \
    UNIT_TEST_BEGIN(name##_tree_create);                       \
                                                               \
    RESULT_CHECK_NOT_EQUAL_pointer(NULL, tree, &pass);         \
                                                               \
    TREE_destroy(&tree);                                       \
    UNIT_TEST_RESULT(name##_tree_create, pass);                \
}

#define UT_TREE_initial(name)                                  \
static void                                                    \
utest_##name##_tree_initial(void)                              \
{                                                              \
    bool pass;                                                 \
    sint64 nice;                                               \
    TREE *tree;                                                \
                                                               \
    pass = true;                                               \
    nice = 0xfade;                                             \
    tree = TREE_create();                                      \
    TREE_initial(tree, nice);                                  \
    UNIT_TEST_BEGIN(name##_tree_initial);                      \
                                                               \
    RESULT_CHECK_pointer(NULL, TREE_left(tree), &pass);        \
    RESULT_CHECK_pointer(NULL, TREE_right(tree), &pass);       \
    RESULT_CHECK_sint64(nice, TREE_nice(tree), &pass);         \
                                                               \
    TREE_destroy(&tree);                                       \
    UNIT_TEST_RESULT(name##_tree_initial, pass);               \
}

#define UT_TREE_destroy(name)                                  \
static void                                                    \
utest_##name##_tree_destroy(void)                              \
{                                                              \
    bool pass;                                                 \
    TREE *tree;                                                \
                                                               \
    pass = true;                                               \
    tree = TREE_create();                                      \
    UNIT_TEST_BEGIN(name##_tree_destroy);                      \
                                                               \
    TREE_destroy(NULL);                                        \
    TREE_destroy(&tree);                                       \
    RESULT_CHECK_pointer(NULL, tree, &pass);                   \
                                                               \
    UNIT_TEST_RESULT(name##_tree_destroy, pass);               \
}

#define UT_TREE_find(name)                                                      \
static void                                                                     \
utest_##name##_tree_find(void)                                                  \
{                                                                               \
    bool pass;                                                                  \
    sint64 nice;                                                                \
    TREE *tree;                                                                 \
    TREE *tmp;                                                                  \
                                                                                \
    pass = true;                                                                \
    UNIT_TEST_BEGIN(name##_tree_find);                                          \
    tree = TEST_tree_sample(0x2234, 0xDEF);                                     \
                                                                                \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_find(NULL, TREE_nice(tree)), &pass); \
    RESULT_CHECK_pointer(tree, TREE_find(tree, TREE_nice(tree)), &pass);        \
    RESULT_CHECK_pointer(NULL, TREE_find(tree, 0xFFFFFFF), &pass);              \
                                                                                \
    tmp = TREE_find_min(tree);                                                  \
    nice = TREE_nice(tree);                                                     \
    tmp = TREE_find(tree, nice);                                                \
    RESULT_CHECK_sint64(nice, TREE_nice(tmp), &pass);                           \
                                                                                \
    tmp = TREE_find_max(tree);                                                  \
    nice = TREE_nice(tree);                                                     \
    tmp = TREE_find(tree, nice);                                                \
    RESULT_CHECK_sint64(nice, TREE_nice(tmp), &pass);                           \
                                                                                \
    TREE_destroy(&tree);                                                        \
    UNIT_TEST_RESULT(name##_tree_find, pass);                                   \
}

#define UT_TREE_find_min(name)                                     \
static void                                                        \
utest_##name##_tree_find_min(void)                                 \
{                                                                  \
    bool pass;                                                     \
    TREE *tree;                                                    \
    TREE *tmp;                                                     \
                                                                   \
    pass = true;                                                   \
    UNIT_TEST_BEGIN(name##_tree_find_min);                         \
    tree = TEST_tree_sample(0x3134, 0xABD);                        \
                                                                   \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_find_min(NULL), &pass); \
                                                                   \
    tmp = TREE_find_min(tree);                                     \
    RESULT_CHECK_pointer(NULL, TREE_left(tmp), &pass);             \
                                                                   \
    TREE_destroy(&tree);                                           \
    UNIT_TEST_RESULT(name##_tree_find_min, pass);                  \
}

#define UT_TREE_find_max(name)                                     \
static void                                                        \
utest_##name##_tree_find_max(void)                                 \
{                                                                  \
    bool pass;                                                     \
    TREE *tree;                                                    \
    TREE *tmp;                                                     \
                                                                   \
    pass = true;                                                   \
    UNIT_TEST_BEGIN(name##_tree_find_max);                         \
    tree = TEST_tree_sample(0x3134, 0xABD);                        \
                                                                   \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_find_max(NULL), &pass); \
                                                                   \
    tmp = TREE_find_max(tree);                                     \
    RESULT_CHECK_pointer(NULL, TREE_right(tmp), &pass);            \
                                                                   \
    TREE_destroy(&tree);                                           \
    UNIT_TEST_RESULT(name##_tree_find_max, pass);                  \
}

#define UT_TREE_height(name)                                  \
static void                                                   \
utest_##name##_tree_height(void)                              \
{                                                             \
    bool pass;                                                \
    TREE *tree;                                               \
    sint32 child;                                             \
                                                              \
    pass = true;                                              \
    UNIT_TEST_BEGIN(name##_tree_height);                      \
    tree = TEST_tree_sample(0x38F1, 0xF0C);                   \
                                                              \
    RESULT_CHECK_sint32(-1, TREE_height(NULL), &pass);        \
                                                              \
    child = MAX_S32(TREE_height(TREE_left(tree)),             \
        TREE_height(TREE_right(tree)));                       \
    RESULT_CHECK_sint32(child + 1, TREE_height(tree), &pass); \
                                                              \
    TREE_destroy(&tree);                                      \
    UNIT_TEST_RESULT(name##_tree_height, pass);               \
}

#define UT_TREE_contains_p(name)                                  \
static void                                                       \
utest_##name##_tree_contains_p(void)                              \
{                                                                 \
    bool pass;                                                    \
    TREE *tree;                                                   \
    TREE *tmp;                                                    \
    TREE *fake;                                                   \
                                                                  \
    pass = true;                                                  \
    UNIT_TEST_BEGIN(name##_tree_contains_p);                      \
    tree = TEST_tree_sample(0x2FD7, 0xA1D);                       \
    tmp = TREE_create();                                          \
    TREE_initial(tmp, 0x1234);                                    \
                                                                  \
    RESULT_CHECK_bool(false, TREE_contains_p(tree, NULL), &pass); \
    RESULT_CHECK_bool(false, TREE_contains_p(NULL, NULL), &pass); \
    RESULT_CHECK_bool(false, TREE_contains_p(tree, tmp), &pass);  \
    TREE_destroy(&tmp);                                           \
                                                                  \
    tmp = TREE_find_max(tree);                                    \
    RESULT_CHECK_bool(true, TREE_contains_p(tree, tmp), &pass);   \
                                                                  \
    fake = TREE_create();                                         \
    TREE_initial(fake, TREE_nice(tmp));                           \
    RESULT_CHECK_bool(false, TREE_contains_p(tree, fake), &pass); \
                                                                  \
    TREE_destroy(&fake);                                          \
    TREE_destroy(&tree);                                          \
    UNIT_TEST_RESULT(name##_tree_contains_p, pass);               \
}

#define UT_TREE_insert(name)                                            \
static void                                                             \
utest_##name##_tree_insert(void)                                        \
{                                                                       \
    bool pass;                                                          \
    TREE *tree;                                                         \
    TREE *tmp;                                                          \
                                                                        \
    pass = true;                                                        \
    UNIT_TEST_BEGIN(name##_tree_insert);                                \
    tree = TEST_tree_sample(0x3321, 0xA2B);                             \
    tmp = TREE_create();                                                \
    TREE_initial(tmp, 0xFFFDEA);                                        \
                                                                        \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_insert(&tree, NULL), &pass); \
    RESULT_CHECK_pointer(tmp, TREE_insert(&tree, tmp), &pass);          \
    RESULT_CHECK_bool(true, TREE_contains_p(tree, tmp), &pass);         \
    RESULT_CHECK_pointer(NULL, TREE_insert(&tree, tmp), &pass);         \
                                                                        \
    tmp = TREE_create();                                                \
    TREE_initial(tmp, 0xFFFDEA);                                        \
    RESULT_CHECK_pointer(tmp, TREE_insert(&tree, tmp), &pass);          \
                                                                        \
    TREE_destroy(&tree);                                                \
    UNIT_TEST_RESULT(name##_tree_insert, pass);                         \
}

#define UT_TREE_remove(name)                                            \
static void                                                             \
utest_##name##_tree_remove(void)                                        \
{                                                                       \
    bool pass;                                                          \
    TREE *tmp;                                                          \
    TREE *tree;                                                         \
                                                                        \
    pass = true;                                                        \
    tree = NULL;                                                        \
    tmp = TREE_create();                                                \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_remove(&tree, tmp), &pass);  \
    TREE_destroy(&tmp);                                                 \
    UNIT_TEST_BEGIN(name##_tree_remove);                                \
                                                                        \
    tree = TEST_tree_sample(0x3321, 0xA2B);                             \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_remove(NULL, NULL), &pass);  \
    RESULT_CHECK_pointer(PTR_INVALID, TREE_remove(&tree, NULL), &pass); \
                                                                        \
    tmp = tree;                                                         \
    RESULT_CHECK_pointer(tmp, TREE_remove(&tree, tree), &pass);         \
    TREE_destroy(&tmp);                                                 \
                                                                        \
    tmp = TREE_find_min(tree);                                          \
    RESULT_CHECK_pointer(tmp, TREE_remove(&tree, tmp), &pass);          \
    TREE_destroy(&tmp);                                                 \
                                                                        \
    tmp = TREE_find_max(tree);                                          \
    RESULT_CHECK_pointer(tmp, TREE_remove(&tree, tmp), &pass);          \
    TREE_destroy(&tmp);                                                 \
                                                                        \
    tmp = TREE_create();                                                \
    TREE_initial(tmp, 0x7FFFFFFF);                                      \
    RESULT_CHECK_pointer(NULL, TREE_remove(&tree, tmp), &pass);         \
    TREE_destroy(&tmp);                                                 \
                                                                        \
    TREE_destroy(&tree);                                                \
    UNIT_TEST_RESULT(name##_tree_remove, pass);                         \
}

#define UT_TREE_iterate(name)                    \
static void                                      \
utest_##name##_tree_iterate(void)                \
{                                                \
    bool pass;                                   \
    TREE *tree;                                  \
    uint32 cnt;                                  \
                                                 \
    UNIT_TEST_BEGIN(name##_tree_iterate);        \
                                                 \
    pass = true;                                 \
    cnt = 0xC7D;                                 \
    TREE_iterate(NULL, &tree_iterate_handler);   \
                                                 \
    tree = TEST_tree_sample(0x2A28, cnt);        \
    TREE_iterate(tree, NULL);                    \
                                                 \
    test_iterate_reference_clean();              \
    TREE_iterate(tree, &tree_iterate_handler);   \
    RESULT_CHECK_uint32(reference, cnt, &pass);  \
    TREE_destroy(&tree);                         \
                                                 \
    cnt = 0xe1D;                                 \
    tree = TEST_tree_sample(0x2A28, cnt);        \
    test_iterate_reference_clean();              \
    TREE_iterate(tree, &tree_iterate_handler);   \
    RESULT_CHECK_uint32(reference, cnt, &pass);  \
    TREE_destroy(&tree);                         \
                                                 \
    UNIT_TEST_RESULT(name##_tree_iterate, pass); \
}

#endif
