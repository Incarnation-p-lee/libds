static void
unit_test_splay_tree_struct_field(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    nice = -0xfade;
    tree = splay_tree_create();
    tmp = splay_tree_node_create(NULL, nice);

    splay_tree_node_nice_set(tmp, nice);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tmp), &pass);

    tree->alias.left = &tmp->alias;
    RESULT_CHECK_pointer(tmp, splay_tree_child_left(tree), &pass);

    nice = 0xfade;
    tmp = splay_tree_node_create(NULL, nice);
    tree->alias.right = &tmp->alias;
    RESULT_CHECK_pointer(tmp, splay_tree_child_right(tree), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_struct_field, pass);
}


static void
unit_test_splay_tree_create(void)
{
    bool pass;
    struct splay_tree *tmp;

    pass = true;

    tmp = splay_tree_create();
    splay_tree_destroy(&tmp);

    tmp = splay_tree_create();
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tmp), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tmp), &pass);

    splay_tree_destroy(&tmp);
    UNIT_TEST_RESULT(splay_tree_create, pass);
}

static void
unit_test_splay_tree_node_create(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;

    pass = true;
    nice = 0xfade;

    tree = splay_tree_node_create(&pass, nice);
    splay_tree_destroy(&tree);

    tree = splay_tree_node_create(&pass, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);

    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_create, pass);
}

static void
unit_test_splay_tree_initial(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;

    pass = true;
    nice = 0xbed;

    tree = splay_tree_node_create(&pass, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);
    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_initial(NULL);
    splay_tree_initial(tree);

    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tree), &pass);

    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(NULL, doubly_linked_list_node_val(link), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_initial, pass);
}

static void
unit_test_splay_tree_node_initial(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;

    nice = 0xfade;
    pass = true;
    tree = splay_tree_create();

    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tree), &pass);

    splay_tree_node_initial(NULL, &pass, nice);
    splay_tree_node_initial(tree, &pass, nice);

    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_initial, pass);
}

static void
unit_test_splay_tree_destroy(void)
{
    bool pass;
    struct splay_tree *tree;

    pass = true;
    tree = NULL;

    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = splay_tree_create();
    splay_tree_destroy(&tree);

    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_splay_tree_sample(0xE2A4, 0xAC23);
    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    UNIT_TEST_RESULT(splay_tree_destroy, pass);
}

static void
unit_test_splay_tree_height(void)
{
    bool pass;
    struct splay_tree *tree;
    sint32 child;

    pass = true;
    tree = test_splay_tree_sample(0x372F, 0x3E24);

    RESULT_CHECK_sint32(-1, splay_tree_height(NULL), &pass);

    child = MAX_S(splay_tree_height(splay_tree_child_left(tree)),
        splay_tree_height(splay_tree_child_right(tree)));
    RESULT_CHECK_sint32(child + 1, splay_tree_height(tree), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_height, pass);
}

static void
unit_test_splay_tree_node_contains_p(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    struct splay_tree *fake;

    pass = true;
    tree = test_splay_tree_sample(0x14F0, 0x73BD);
    tmp = splay_tree_node_create(&pass, 0x1234);

    RESULT_CHECK_bool(false, splay_tree_node_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_node_contains_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_node_contains_p(tree, tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_max(&tree);
    RESULT_CHECK_bool(true, splay_tree_node_contains_p(tree, tmp), &pass);

    fake = splay_tree_node_create(tmp, splay_tree_node_nice(tmp));
    RESULT_CHECK_bool(false, splay_tree_node_contains_p(tree, fake), &pass);

    splay_tree_destroy(&fake);
    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_contains_p, pass);
}

static void
unit_test_splay_tree_node_find(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    tree = test_splay_tree_sample(0x13FA, 0x143A);

    RESULT_CHECK_pointer(NULL,
        splay_tree_node_find(NULL, splay_tree_node_nice(tree)),
        &pass);

    RESULT_CHECK_pointer(tree,
        splay_tree_node_find(&tree, splay_tree_node_nice(tree)), &pass);

    RESULT_CHECK_pointer(NULL,
        splay_tree_node_find(&tree, 0xFFFFFFF), &pass);

    tmp = splay_tree_node_find_min(&tree);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(tmp,
        splay_tree_node_find(&tree, splay_tree_node_nice(tmp)), &pass);

    tmp = splay_tree_node_find_max(&tree);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(tmp,
        splay_tree_node_find(&tree, splay_tree_node_nice(tmp)), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_find, pass);
}

static void
unit_test_splay_tree_node_find_min(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    tree = test_splay_tree_sample(0xF1C2, 0xD482);

    RESULT_CHECK_pointer(NULL, splay_tree_node_find_min(NULL), &pass);
    tmp = splay_tree_node_find_min(&tree);

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_find_min, pass);
}

static void
unit_test_splay_tree_node_find_max(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    tree = test_splay_tree_sample(0xF2E4, 0x9B2A);

    RESULT_CHECK_pointer(NULL, splay_tree_node_find_max(NULL), &pass);
    tmp = splay_tree_node_find_min(&tree);

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_find_max, pass);
}

static void
unit_test_splay_tree_node_insert(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    struct splay_tree *inserted;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, splay_tree_node_insert(&tree, NULL), &pass);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_splay_tree_sample(0x3B49, 0x2F2C);
    tmp = splay_tree_node_create(&pass, 0xFFFDEA);
    RESULT_CHECK_pointer(NULL, splay_tree_node_insert(&tree, NULL), &pass);

    RESULT_CHECK_pointer(tmp, splay_tree_node_insert(&tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(tmp, splay_tree_node_insert(&tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp, tree, &pass);

    inserted = tmp;
    tmp = splay_tree_node_create(&pass, 0xFFFDEA);
    RESULT_CHECK_pointer(inserted, splay_tree_node_insert(&tree, tmp), &pass);
    RESULT_CHECK_pointer(inserted, tree, &pass);

    splay_tree_destroy(&tmp);
    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_node_insert, pass);
}

static void
unit_test_splay_tree_node_remove(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, splay_tree_node_remove(&tree, 0x0), &pass);

    tree = test_splay_tree_sample(0x2421, 0x32CD);
    tmp = tree;
    nice = splay_tree_node_nice(tmp);
    tmp = splay_tree_node_remove(&tree, nice);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_min(&tree);
    nice = splay_tree_node_nice(tmp);
    tmp = splay_tree_node_remove(&tree, nice);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_max(&tree);
    nice = splay_tree_node_nice(tmp);
    tmp = splay_tree_node_remove(&tree, nice);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_create(&pass, 0x7FFFFF);
    nice = splay_tree_node_nice(tmp);
    RESULT_CHECK_pointer(NULL, splay_tree_node_remove(&tree, nice), &pass);
    splay_tree_destroy(&tmp);
    splay_tree_destroy(&tree);

    tree = splay_tree_node_create(&pass, 0x7FFFFF);
    tmp = tree;
    nice = splay_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, splay_tree_node_remove(&tree, nice), &pass);

    splay_tree_destroy(&tmp);
    UNIT_TEST_RESULT(splay_tree_node_remove, pass);
}

static void
unit_test_splay_tree_node_remove_and_destroy(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    pass = true;
    tree = NULL;

    splay_tree_node_remove_and_destroy(&tree, 0x0);

    tree = test_splay_tree_sample(0x2321, 0x32CD);
    tmp = tree;
    nice = splay_tree_node_nice(tmp);
    splay_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);

    tmp = splay_tree_node_find_min(&tree);
    nice = splay_tree_node_nice(tmp);
    splay_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);

    tmp = splay_tree_node_find_max(&tree);
    nice = splay_tree_node_nice(tmp);
    splay_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);

    tmp = splay_tree_node_create(&pass, 0x7FFFFF);
    nice = splay_tree_node_nice(tmp);
    splay_tree_node_remove_and_destroy(&tree, nice);

    splay_tree_destroy(&tree);
    splay_tree_destroy(&tmp);
    UNIT_TEST_RESULT(splay_tree_node_remove_and_destroy, pass);
}

static void
unit_test_splay_tree_iterate(void)
{
    bool pass;
    struct splay_tree *tree;
    uint32 cnt;

    pass = true;
    cnt = 0xC72D;

    splay_tree_iterate(NULL, &tree_iterate_handler, ORDER_PRE);

    reference = 0;
    splay_tree_iterate(tree, &tree_iterate_handler, ORDER_END);
    RESULT_CHECK_uint32(0x0u, reference, &pass);

    pass = true;
    cnt = 0xC72D;
    tree = test_splay_tree_sample(0x2328, cnt);

    reference = 0;
    splay_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    reference = 0;
    splay_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    reference = 0;
    splay_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    splay_tree_destroy(&tree);
    UNIT_TEST_RESULT(splay_tree_iterate, pass);
}

