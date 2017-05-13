static inline void
utest_binary_search_tree_create(void)
{
    bool pass;
    s_binary_search_tree_t *tree;

    pass = true;
    tree = binary_search_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(binary_search_tree_create);

    RESULT_CHECK_bool(true, binary_search_tree_structure_legal_p(tree), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_structure_illegal_p(tree), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_create, pass);
}

static inline void
utest_binary_search_tree_initial(void)
{
    bool pass;
    sint64 nice;
    s_binary_search_tree_t *tree;
    s_doubly_linked_list_t *val_list;

    pass = true;
    nice = 0xfade;
    tree = binary_search_tree_create(&pass, 0);
    UNIT_TEST_BEGIN(binary_search_tree_initial);

    binary_search_tree_initial(tree, &pass, nice);

    RESULT_CHECK_pointer(NULL, binary_search_tree_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_right(tree), &pass);
    RESULT_CHECK_sint64(nice, binary_search_tree_nice(tree), &pass);

    val_list = binary_search_tree_val_list(tree);

    RESULT_CHECK_uint32(1, doubly_linked_list_length(val_list), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(val_list), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_initial, pass);
}

static inline void
utest_binary_search_tree_destroy(void)
{
    bool pass;
    s_binary_search_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_destroy);
    tree = binary_search_tree_create(&pass, 0);

    binary_search_tree_destroy(NULL);
    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_binary_search_tree_sample(0x1234, 0x342);

    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    UNIT_TEST_RESULT(binary_search_tree_destroy, pass);
}

static inline void
utest_binary_search_tree_find(void)
{
    bool pass;
    sint64 nice;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_find);
    tree = test_binary_search_tree_sample(0x2234, 0x1DEF);

    nice = binary_search_tree_nice(tree);
    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_find(NULL, nice), &pass);
    RESULT_CHECK_pointer(tree, binary_search_tree_find(tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_find(tree, 0xFFFFFFF), &pass);

    tmp = binary_search_tree_find_min(tree);
    nice = binary_search_tree_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_find(tree, nice), &pass);

    tmp = binary_search_tree_find_max(tree);
    nice = binary_search_tree_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_find(tree, nice), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_find, pass);
}

static inline void
utest_binary_search_tree_find_min(void)
{
    bool pass;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_find_min);
    tree = test_binary_search_tree_sample(0x3134, 0xABD);

    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_find_min(NULL), &pass);

    tmp = binary_search_tree_find_min(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_left(tmp), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_find_min, pass);
}

static inline void
utest_binary_search_tree_find_max(void)
{
    bool pass;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_find_max);
    tree = test_binary_search_tree_sample(0x10dc, 0x73f);

    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_find_max(NULL), &pass);

    tmp = binary_search_tree_find_max(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_right(tmp), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_find_max, pass);
}

static inline void
utest_binary_search_tree_height(void)
{
    bool pass;
    sint32 left;
    sint32 right;
    s_binary_search_tree_t *tree;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_height);
    tree = test_binary_search_tree_sample(0x38f1, 0xf0C);

    RESULT_CHECK_sint32(-1, binary_search_tree_height(NULL), &pass);

    left = binary_search_tree_height(binary_search_tree_left(tree));
    right = binary_search_tree_height(binary_search_tree_right(tree));

    RESULT_CHECK_sint32(MAX_S32(left, right) + 1, binary_search_tree_height(tree), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_height, pass);
}

static inline void
utest_binary_search_tree_contains_p(void)
{
    bool pass;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;
    s_binary_search_tree_t *fake;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_contains_p);
    tree = test_binary_search_tree_sample(0x2fd7, 0x3a1d);

    RESULT_CHECK_bool(false, binary_search_tree_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_contains_p(NULL, NULL), &pass);

    tmp = binary_search_tree_create(&pass, 0);
    RESULT_CHECK_bool(false, binary_search_tree_contains_p(tree, tmp), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_find_max(tree);
    RESULT_CHECK_bool(true, binary_search_tree_contains_p(tree, tmp), &pass);

    tmp = binary_search_tree_find_min(tree);
    RESULT_CHECK_bool(true, binary_search_tree_contains_p(tree, tmp), &pass);

    fake = binary_search_tree_create(NULL, binary_search_tree_nice(tmp));
    RESULT_CHECK_bool(false, binary_search_tree_contains_p(tree, fake), &pass);

    binary_search_tree_destroy(&fake);
    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_contains_p, pass);
}

static inline void
utest_binary_search_tree_insert(void)
{
    bool pass;
    sint64 nice;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;
    s_binary_search_tree_t *node;

    pass = true;
    UNIT_TEST_BEGIN(binary_search_tree_insert);
    tree = test_binary_search_tree_sample(0x1321, 0xa2b);

    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_insert(NULL, NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_insert(tree, NULL), &pass);

    nice = 0xFFFDEA;
    tmp = binary_search_tree_create(&pass, nice);

    RESULT_CHECK_pointer(tmp, binary_search_tree_insert(tree, tmp), &pass);
    RESULT_CHECK_bool(true, binary_search_tree_contains_p(tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp, binary_search_tree_insert(tree, tmp), &pass);

    tmp = binary_search_tree_create(&pass, nice);
    node = binary_search_tree_find(tree, nice);
    RESULT_CHECK_pointer(node, binary_search_tree_insert(tree, tmp), &pass);
    binary_search_tree_destroy(&tmp);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_insert, pass);
}

static inline void
utest_binary_search_tree_remove(void)
{
    bool pass;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    pass = true;
    tree = NULL;
    UNIT_TEST_BEGIN(binary_search_tree_remove);
    tree = test_binary_search_tree_sample(0x3214, 0x2632);

    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_remove(NULL, NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, binary_search_tree_remove(&tree, NULL), &pass);

    tmp = binary_search_tree_create(&pass, 0);
    RESULT_CHECK_pointer(NULL, binary_search_tree_remove(&tree, tmp), &pass);
    binary_search_tree_destroy(&tmp);

    while (tree->left) {
        tmp = tree->left;
        RESULT_CHECK_pointer(tmp, binary_search_tree_remove(&tree, tmp), &pass);
        binary_search_tree_destroy(&tmp);
    }

    while (tree->right) {
        tmp = tree->right;
        RESULT_CHECK_pointer(tmp, binary_search_tree_remove(&tree, tmp), &pass);
        binary_search_tree_destroy(&tmp);
    }

    binary_search_tree_destroy(&tree);

    tree = test_binary_search_tree_sample(0x432c, 0x1039);

    while (tree) {
        tmp = tree;
        RESULT_CHECK_pointer(tmp, binary_search_tree_remove(&tree, tree), &pass);
        binary_search_tree_destroy(&tmp);
    }

    UNIT_TEST_RESULT(binary_search_tree_remove, pass);
}

static inline void
utest_binary_search_tree_iterate_handler(void *val)
{
    uint32 *counter;
    s_binary_search_tree_t *binary_search;

    binary_search = val;

    assert_exit(binary_search_tree_structure_legal_p(binary_search));

    counter = doubly_linked_list_val(binary_search_tree_val_list(binary_search));

    *counter = *counter + 1;
}

static inline void
utest_binary_search_tree_iterate(void)
{
    uint32 i;
    bool pass;
    uint32 limit;
    uint32 counter;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    pass = true;
    limit = 0x1de2;
    counter = i = 0;
    UNIT_TEST_BEGIN(binary_search_tree_iterate);

    binary_search_tree_iterate(NULL, NULL);
    binary_search_tree_iterate(tree, NULL);
    binary_search_tree_iterate(NULL, &utest_binary_search_tree_iterate_handler);

    tree = binary_search_tree_create(&counter, i++);

    while (i < limit) {
        tmp = binary_search_tree_create(&counter, i++);
        binary_search_tree_insert(tree, tmp);
    }

    binary_search_tree_iterate(tree, &utest_binary_search_tree_iterate_handler);
    RESULT_CHECK_uint32(limit, counter, &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_iterate, pass);
}


