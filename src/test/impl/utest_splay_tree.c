static inline void
utest_splay_tree_create(void)
{
    bool pass;
    s_splay_tree_t *tree;

    pass = true;
    tree = splay_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(splay_tree_create);

    RESULT_CHECK_bool(true, splay_tree_structure_legal_p(tree), &pass);
    RESULT_CHECK_bool(false, splay_tree_structure_illegal_p(tree), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_create, pass);
}

static inline void
utest_splay_tree_initial(void)
{
    bool pass;
    sint64 nice;
    s_splay_tree_t *tree;
    s_doubly_linked_list_t *val_list;

    pass = true;
    nice = 0xfade;
    tree = splay_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(splay_tree_initial);

    splay_tree_initial(tree, &pass, nice);

    RESULT_CHECK_pointer(NULL, splay_tree_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_nice(tree), &pass);

    val_list = splay_tree_val_list(tree);

    RESULT_CHECK_uint32(1, doubly_linked_list_length(val_list), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(val_list), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_initial, pass);
}

static inline void
utest_splay_tree_destroy(void)
{
    bool pass;
    s_splay_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(splay_tree_destroy);
    tree = splay_tree_create(&pass, 0);

    splay_tree_destroy(NULL);
    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_splay_tree_sample(0x1234, 0x342);

    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    UNIT_TEST_RESULT(splay_tree_destroy, pass);
}

static inline void
utest_splay_tree_height(void)
{
    bool pass;
    sint32 left;
    sint32 right;
    s_splay_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(splay_tree_height);
    tree = test_splay_tree_sample(0x38f1, 0xf0C);

    RESULT_CHECK_sint32(-1, splay_tree_height(NULL), &pass);

    left = splay_tree_height(splay_tree_left(tree));
    right = splay_tree_height(splay_tree_right(tree));

    RESULT_CHECK_sint32(MAX_S32(left, right) + 1, splay_tree_height(tree), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_height, pass);
}

static inline void
utest_splay_tree_insert(void)
{
    bool pass;
    sint64 nice;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;
    s_splay_tree_t *node;

    pass = true;
    UNIT_TEST_BEGIN(splay_tree_insert);
    tree = test_splay_tree_sample(0x1321, 0xa2b);

    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_insert(NULL, NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, splay_tree_insert(&tree, NULL), &pass);

    nice = 0xFFFDEA;
    tmp = splay_tree_create(&pass, nice);

    RESULT_CHECK_pointer(tmp, splay_tree_insert(&tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_bool(true, splay_tree_contains_p(tree, tmp), &pass);

    tmp = splay_tree_right(splay_tree_left(tree));
    RESULT_CHECK_pointer(tmp, splay_tree_insert(&tree, tmp), &pass);

    tmp = splay_tree_create(&pass, nice);
    node = splay_tree_find(&tree, nice);
    RESULT_CHECK_pointer(node, splay_tree_insert(&tree, tmp), &pass);
    splay_tree_destroy(&tmp);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_insert, pass);
}

static inline void
utest_splay_tree_iterate_handler(void *val)
{
    uint32 *counter;
    s_splay_tree_t *binary_search;

    binary_search = val;

    assert_exit(splay_tree_structure_legal_p(binary_search));

    counter = doubly_linked_list_val(splay_tree_val_list(binary_search));

    *counter = *counter + 1;
}

static inline void
utest_splay_tree_iterate(void)
{
    uint32 i;
    bool pass;
    uint32 limit;
    uint32 counter;
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    pass = true;
    limit = 0x1de2;
    counter = i = 0;
    UNIT_TEST_BEGIN(splay_tree_iterate);

    splay_tree_iterate(NULL, NULL);
    splay_tree_iterate(tree, NULL);
    splay_tree_iterate(NULL, &utest_splay_tree_iterate_handler);

    tree = splay_tree_create(&counter, i++);

    while (i < limit) {
        tmp = splay_tree_create(&counter, i++);
        splay_tree_insert(&tree, tmp);
    }

    splay_tree_iterate(tree, &utest_splay_tree_iterate_handler);
    RESULT_CHECK_uint32(limit, counter, &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_iterate, pass);
}

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
    tmp = splay_tree_create(&tmp, 0x1234);

    RESULT_CHECK_bool(false, splay_tree_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_contains_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_contains_p(tree, tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_find_max(&tree);
    RESULT_CHECK_bool(true, splay_tree_contains_p(tree, tmp), &pass);

    fake = splay_tree_create(&fake, splay_tree_nice(tmp));
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

    tmp = splay_tree_create(&tmp, 0x7FFFFF);
    nice = splay_tree_nice(tmp);
    RESULT_CHECK_pointer(NULL, splay_tree_remove(&tree, tmp), &pass);
    splay_tree_destroy(&tmp);
    splay_tree_destroy(&tree);

    nice = 0x7fffff;
    tree = splay_tree_create(&tree, nice);
    tmp = tree;
    RESULT_CHECK_pointer(tmp, splay_tree_remove(&tree, tree), &pass);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    splay_tree_destroy(&tmp);
    UNIT_TEST_RESULT(splay_tree_remove, pass);
}

