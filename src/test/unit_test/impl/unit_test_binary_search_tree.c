static void
unit_test_binary_search_tree_struct_field(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    nice = -0xfade;
    tree = binary_search_tree_create();
    tmp = binary_search_tree_node_create(NULL, nice);

    binary_search_tree_node_nice_set(tmp, nice);
    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tmp), &pass);

    binary_search_tree_child_left_set(tree, tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_child_left(tree), &pass);

    nice = 0xfade;
    tmp = binary_search_tree_node_create(NULL, nice);
    binary_search_tree_child_right_set(tree, tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_child_right(tree), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_struct_field, pass);
}

static void
unit_test_binary_search_tree_create(void)
{
    bool pass;
    struct binary_search_tree *tmp;

    pass = true;
    tmp = binary_search_tree_create();

    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tmp), &pass);
    RESULT_CHECK_sint64(0x0, binary_search_tree_node_nice(tmp), &pass);

    binary_search_tree_destroy(&tmp);
    UNIT_TEST_RESULT(binary_search_tree_create, pass);
}

static void
unit_test_binary_search_tree_node_create(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    pass = true;
    nice = 0xfade;
    tree = binary_search_tree_node_create(&pass, nice);

    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tree), &pass);

    link = binary_search_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(link), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_create, pass);
}

static void
unit_test_binary_search_tree_initial(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    binary_search_tree_initial(NULL);

    pass = true;
    nice = 0xbed;
    tree = binary_search_tree_node_create(&pass, nice);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tree), &pass);

    link = binary_search_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(link), &pass);

    binary_search_tree_initial(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, binary_search_tree_node_nice(tree), &pass);

    link = binary_search_tree_node_link(tree);
    RESULT_CHECK_pointer(NULL, doubly_linked_list_val(link), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_initial, pass);
}


static void
unit_test_binary_search_tree_node_initial(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    nice = 0xfade;
    pass = true;
    binary_search_tree_node_initial(NULL, &pass, nice);

    nice = 0xfade;
    pass = true;

    tree = binary_search_tree_create();
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, binary_search_tree_node_nice(tree), &pass);

    binary_search_tree_node_initial(tree, &pass, nice);
    link = binary_search_tree_node_link(tree);

    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tree), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_val(link), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_initial, pass);
}

static void
unit_test_binary_search_tree_destroy(void)
{
    bool pass;
    struct binary_search_tree *tree;

    pass = true;
    tree = NULL;

    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = binary_search_tree_create();
    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = test_binary_search_tree_sample(0x2345, 0x3BDE);
    binary_search_tree_destroy(&tree);

    RESULT_CHECK_pointer(NULL, tree, &pass);
    UNIT_TEST_RESULT(binary_search_tree_destroy, pass);
}

static void
unit_test_binary_search_tree_node_find(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    tree = test_binary_search_tree_sample(0x2234, 0x3DEF);

    RESULT_CHECK_pointer(NULL,
        binary_search_tree_node_find(NULL, binary_search_tree_node_nice(tree)),
        &pass);

    RESULT_CHECK_pointer(tree,
        binary_search_tree_node_find(tree, binary_search_tree_node_nice(tree)),
        &pass);

    RESULT_CHECK_pointer(NULL,
        binary_search_tree_node_find(tree, 0xFFFFFFF),
        &pass);

    tmp = binary_search_tree_node_find_min(tree);
    RESULT_CHECK_pointer(tmp,
        binary_search_tree_node_find(tree, binary_search_tree_node_nice(tmp)),
        &pass);

    tmp = binary_search_tree_node_find_max(tree);
    RESULT_CHECK_pointer(tmp,
        binary_search_tree_node_find(tree, binary_search_tree_node_nice(tmp)),
        &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_find, pass);
}


static void
unit_test_binary_search_tree_node_find_min(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    tree = test_binary_search_tree_sample(0x3134, 0x2ABD);

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find_min(NULL), &pass);

    tmp = binary_search_tree_node_find_min(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_find_min, pass);
}


static void
unit_test_binary_search_tree_node_find_max(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    tree = test_binary_search_tree_sample(0x2134, 0x29AD);

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find_max(NULL), &pass);

    tmp = binary_search_tree_node_find_min(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_find_max, pass);
}

static void
unit_test_binary_search_tree_height(void)
{
    bool pass;
    struct binary_search_tree *tree;
    sint32 child;

    pass = true;
    tree = test_binary_search_tree_sample(0x38F1, 0x310C);

    RESULT_CHECK_sint32(-1, binary_search_tree_height(NULL), &pass);

    child = MAX_S(binary_search_tree_height(binary_search_tree_child_left(tree)),
        binary_search_tree_height(binary_search_tree_child_right(tree)));
    RESULT_CHECK_sint32(child + 1, binary_search_tree_height(tree), &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_height, pass);
}

static void
unit_test_binary_search_tree_node_contains_p(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;
    struct binary_search_tree *fake;

    pass = true;
    tree = test_binary_search_tree_sample(0x2FD7, 0x3A1D);
    tmp = binary_search_tree_node_create(&pass, 0x1234);

    RESULT_CHECK_bool(false, binary_search_tree_node_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_node_contains_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_node_contains_p(tree, tmp), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_max(tree);
    RESULT_CHECK_bool(true, binary_search_tree_node_contains_p(tree, tmp), &pass);

    fake = binary_search_tree_node_create(tmp, binary_search_tree_node_nice(tmp));
    RESULT_CHECK_bool(false, binary_search_tree_node_contains_p(tree, fake), &pass);

    binary_search_tree_destroy(&fake);
    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_contains_p, pass);
}

static void
unit_test_binary_search_tree_node_insert(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;
    struct binary_search_tree *inserted;

    pass = true;
    tree = test_binary_search_tree_sample(0x3321, 0x3A2B);
    tmp = binary_search_tree_node_create(&pass, 0xFFFDEA);

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_insert(tree, NULL), &pass);
    RESULT_CHECK_pointer(tmp, binary_search_tree_node_insert(tree, tmp), &pass);
    RESULT_CHECK_pointer(tmp,
        binary_search_tree_node_find(tree, binary_search_tree_node_nice(tmp)),
        &pass);

    RESULT_CHECK_pointer(tmp, binary_search_tree_node_insert(tree, tmp), &pass);

    inserted = tmp;
    tmp = binary_search_tree_node_create(&pass, 0xFFFDEA);
    RESULT_CHECK_pointer(inserted, binary_search_tree_node_insert(tree, tmp), &pass);

    binary_search_tree_destroy(&tmp);
    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_insert, pass);
}

static void
unit_test_binary_search_tree_node_remove(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_remove(&tree, 0x0), &pass);

    tree = test_binary_search_tree_sample(0x2F41, 0x32AD);
    nice = binary_search_tree_node_nice(tree);
    tmp = binary_search_tree_node_remove(&tree, nice);

    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_min(tree);
    nice = binary_search_tree_node_nice(tmp);
    tmp = binary_search_tree_node_remove(&tree, nice);

    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_max(tree);
    nice = binary_search_tree_node_nice(tmp);
    tmp = binary_search_tree_node_remove(&tree, nice);

    RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_create(&pass, 0x7FFFFF);
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_remove(&tree, nice), &pass);

    binary_search_tree_destroy(&tmp);
    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_remove, pass);
}

static void
unit_test_binary_search_tree_node_remove_and_destroy(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    pass = true;
    tree = NULL;

    binary_search_tree_node_remove_and_destroy(&tree, 0x0);

    tree = test_binary_search_tree_sample(0x1491, 0x10be);
    nice = binary_search_tree_node_nice(tree);
    binary_search_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);

    tmp = binary_search_tree_node_find_min(tree);
    nice = binary_search_tree_node_nice(tmp);
    binary_search_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);

    tmp = binary_search_tree_node_find_max(tree);
    nice = binary_search_tree_node_nice(tmp);
    binary_search_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);

    tmp = binary_search_tree_node_create(&pass, 0x7FFFFF);
    nice = binary_search_tree_node_nice(tmp);
    binary_search_tree_node_remove_and_destroy(&tree, nice);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_remove(&tree, nice), &pass);

    binary_search_tree_destroy(&tmp);
    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_node_remove_and_destroy, pass);
}

static void
unit_test_binary_search_tree_iterate(void)
{
    bool pass;
    struct binary_search_tree *tree;
    uint32 cnt;

    pass = true;
    cnt = 0x2C7D;
    binary_search_tree_iterate(NULL, &tree_iterate_handler, ORDER_PRE);

    reference = 0;
    tree = test_binary_search_tree_sample(0x2A28, cnt);
    binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    reference = 0;
    binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_END);
    RESULT_CHECK_uint32(0x0u, reference, &pass);

    binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    reference = 0;
    binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
    RESULT_CHECK_uint32(reference, cnt, &pass);

    binary_search_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_search_tree_iterate, pass);
}

