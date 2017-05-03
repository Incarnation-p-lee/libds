static inline void
utest_avl_tree_create(void)
{
    bool pass;
    s_avl_tree_t *tree;

    pass = true;
    tree = avl_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(avl_tree_create);

    RESULT_CHECK_bool(true, avl_tree_structure_legal_p(tree), &pass);
    RESULT_CHECK_bool(false, avl_tree_structure_illegal_p(tree), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_create, pass);
}

static inline void
utest_avl_tree_initial(void)
{
    bool pass;
    sint64 nice;
    s_avl_tree_t *tree;
    s_doubly_linked_list_t *val_list;

    pass = true;
    nice = 0xfade;
    tree = avl_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(avl_tree_initial);

    avl_tree_initial(tree, &pass, nice);

    RESULT_CHECK_pointer(NULL, avl_tree_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, avl_tree_right(tree), &pass);
    RESULT_CHECK_sint64(nice, avl_tree_nice(tree), &pass);

    val_list = avl_tree_val_list(tree);

    RESULT_CHECK_uint32(1, doubly_linked_list_length(val_list), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(val_list), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_initial, pass);
}

static inline void
utest_avl_tree_destroy(void)
{
    bool pass;
    s_avl_tree_t *tree;

    pass = true;
    tree = avl_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(avl_tree_destroy);

    avl_tree_destroy(NULL);
    avl_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_avl_tree_sample(0x1234, 0x342);

    avl_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    UNIT_TEST_RESULT(avl_tree_destroy, pass);
}

static inline void
utest_avl_tree_find(void)
{
    bool pass;
    sint64 nice;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    tree = test_avl_tree_sample(0x2234, 0x1DEF);
    UNIT_TEST_BEGIN(avl_tree_find);

    nice = avl_tree_nice(tree);
    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_find(NULL, nice), &pass);
    RESULT_CHECK_pointer(tree, avl_tree_find(tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, avl_tree_find(tree, 0xFFFFFFF), &pass);

    tmp = avl_tree_find_min(tree);
    nice = avl_tree_nice(tmp);
    RESULT_CHECK_pointer(tmp, avl_tree_find(tree, nice), &pass);

    tmp = avl_tree_find_max(tree);
    nice = avl_tree_nice(tmp);
    RESULT_CHECK_pointer(tmp, avl_tree_find(tree, nice), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_find, pass);
}

static inline void
utest_avl_tree_find_min(void)
{
    bool pass;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    tree = test_avl_tree_sample(0x3134, 0xABD);
    UNIT_TEST_BEGIN(avl_tree_find_min);

    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_find_min(NULL), &pass);

    tmp = avl_tree_find_min(tree);
    RESULT_CHECK_pointer(NULL, avl_tree_left(tmp), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_find_min, pass);
}

static inline void
utest_avl_tree_find_max(void)
{
    bool pass;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    tree = test_avl_tree_sample(0x10dc, 0x73f);
    UNIT_TEST_BEGIN(avl_tree_find_max);

    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_find_max(NULL), &pass);

    tmp = avl_tree_find_max(tree);
    RESULT_CHECK_pointer(NULL, avl_tree_right(tmp), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_find_max, pass);
}

static inline void
utest_avl_tree_height(void)
{
    bool pass;
    sint32 left;
    sint32 right;
    s_avl_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(avl_tree_height);
    tree = test_avl_tree_sample(0x38f1, 0xf0C);

    RESULT_CHECK_sint32(-1, avl_tree_height(NULL), &pass);

    left = avl_tree_height(avl_tree_left(tree));
    right = avl_tree_height(avl_tree_right(tree));

    RESULT_CHECK_sint32(MAX_S32(left, right) + 1, avl_tree_height(tree), &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_height, pass);
}

static inline void
utest_avl_tree_contains_p(void)
{
    bool pass;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;
    s_avl_tree_t *fake;

    pass = true;
    UNIT_TEST_BEGIN(avl_tree_contains_p);
    tree = test_avl_tree_sample(0x2fd7, 0x3a1d);

    RESULT_CHECK_bool(false, avl_tree_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, avl_tree_contains_p(NULL, NULL), &pass);

    tmp = avl_tree_create(&pass, 0);
    RESULT_CHECK_bool(false, avl_tree_contains_p(tree, tmp), &pass);
    avl_tree_destroy(&tmp);

    tmp = avl_tree_find_max(tree);
    RESULT_CHECK_bool(true, avl_tree_contains_p(tree, tmp), &pass);

    fake = avl_tree_create(NULL, avl_tree_nice(tmp));
    RESULT_CHECK_bool(false, avl_tree_contains_p(tree, fake), &pass);

    avl_tree_destroy(&fake);
    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_contains_p, pass);
}

static void
utest_avl_tree_balanced_p(void)
{
    bool pass;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(avl_tree_balanced_p);
    tree = test_avl_tree_sample(0x28ea, 0x3d64);

    RESULT_CHECK_bool(true, avl_tree_balanced_p(NULL), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_create(&pass, 0);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tmp), &pass);

    tmp->left = tree;
    RESULT_CHECK_bool(false, avl_tree_balanced_p(tmp), &pass);
    tmp->left = NULL;

    avl_tree_destroy(&tmp);
    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_balanced_p, pass);
}

static inline void
utest_avl_tree_insert(void)
{
    bool pass;
    sint64 nice;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;
    s_avl_tree_t *node;

    pass = true;
    UNIT_TEST_BEGIN(avl_tree_insert);
    tree = test_avl_tree_sample(0x1321, 0xa2b);

    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_insert(NULL, NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_insert(&tree, NULL), &pass);

    nice = 0xFFFDEA;
    tmp = avl_tree_create(&pass, nice);

    RESULT_CHECK_pointer(tmp, avl_tree_insert(&tree, tmp), &pass);
    RESULT_CHECK_bool(true, avl_tree_contains_p(tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp, avl_tree_insert(&tree, tmp), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_create(&pass, nice);
    node = avl_tree_find(tree, nice);
    RESULT_CHECK_pointer(node, avl_tree_insert(&tree, tmp), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_insert, pass);
}

static inline void
utest_avl_tree_remove(void)
{
    bool pass;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    tree = NULL;
    UNIT_TEST_BEGIN(avl_tree_remove);
    tree = test_avl_tree_sample(0x2214, 0x1632);

    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_remove(NULL, NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, avl_tree_remove(&tree, NULL), &pass);

    tmp = avl_tree_create(&pass, 0);
    RESULT_CHECK_pointer(NULL, avl_tree_remove(&tree, tmp), &pass);
    avl_tree_destroy(&tmp);

    tmp = avl_tree_find_min(tree);
    RESULT_CHECK_pointer(tmp, avl_tree_remove(&tree, tmp), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);

    while (tree) {
        tmp = tree;
        RESULT_CHECK_pointer(tmp, avl_tree_remove(&tree, tree), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
        avl_tree_destroy(&tmp);
    }

    UNIT_TEST_RESULT(avl_tree_remove, pass);
}

static inline void
utest_avl_tree_iterate_handler(void *val)
{
    uint32 *counter;
    s_avl_tree_t *avl;

    avl = val;

    assert_exit(avl_tree_structure_legal_p(avl));

    counter = doubly_linked_list_val(avl_tree_val_list(avl));

    *counter = *counter + 1;
}

static inline void
utest_avl_tree_iterate(void)
{
    uint32 i;
    bool pass;
    uint32 limit;
    uint32 counter;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    pass = true;
    limit = 0x1de2;
    counter = i = 0;
    UNIT_TEST_BEGIN(avl_tree_iterate);

    avl_tree_iterate(NULL, NULL);
    avl_tree_iterate(tree, NULL);
    avl_tree_iterate(NULL, &utest_avl_tree_iterate_handler);

    tree = avl_tree_create(&counter, i++);

    while (i < limit) {
        tmp = avl_tree_create(&counter, i++);
        avl_tree_insert(&tree, tmp);
    }

    avl_tree_iterate(tree, &utest_avl_tree_iterate_handler);
    RESULT_CHECK_uint32(limit, counter, &pass);

    avl_tree_destroy(&tree);
    UNIT_TEST_RESULT(avl_tree_iterate, pass);
}

