static void
unit_test_binary_search_tree_struct_field(void)
{
    bool pass;
    sint64 nice;
    uint32 loop;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf12345u;
    while (0 != loop--) {
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
    }
    test_result_print(SYM_2_STR(binary_search_tree_struct_field), pass);

    return;
}

static inline struct binary_search_tree *
unit_test_binary_search_tree_sample(uint64 range, uint32 node_count)
{
    struct binary_search_tree *retval;
    struct binary_search_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = binary_search_tree_create();
    binary_search_tree_node_initial(retval, &reference, 0);
    retval->height = 0;
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_node_create(NULL, 0x0);
        binary_search_tree_node_initial(tmp, &reference, nice);
        if (tmp != binary_search_tree_node_insert(retval, tmp)) {
            binary_search_tree_destroy(&tmp);
        }
        i++;
    }

    return retval;
}


static void
unit_test_binary_search_tree_create(void)
{
    bool pass;
    uint32 loop;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x28345afu;
    while (0 != loop--) {
        pass = true;
        tmp = binary_search_tree_create();

        RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tmp), &pass);
        RESULT_CHECK_sint64(0x0, binary_search_tree_node_nice(tmp), &pass);

        binary_search_tree_destroy(&tmp);
    }

    test_result_print(SYM_2_STR(binary_search_tree_create), pass);
    return;
}

static void
unit_test_binary_search_tree_node_create(void)
{
    bool pass;
    sint64 nice;
    uint32 loop;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x25345afu;
    while (0 != loop--) {
        pass = true;
        nice = 0xfade;
        tree = binary_search_tree_node_create(&pass, nice);

        RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tree), &pass);

        link = binary_search_tree_node_link(tree);
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

        binary_search_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(binary_search_tree_node_create), pass);
    return;
}

static void
unit_test_binary_search_tree_initial(void)
{
    bool pass;
    sint64 nice;
    uint32 loop;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    TEST_PERFORMANCE_CHECKPOINT;

    binary_search_tree_initial(NULL);

    loop = 0x22345afu;
    while (0 != loop--) {
        pass = true;
        nice = 0xbed;
        tree = binary_search_tree_node_create(&pass, nice);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(nice, binary_search_tree_node_nice(tree), &pass);

        link = binary_search_tree_node_link(tree);
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

        binary_search_tree_initial(tree);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, binary_search_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(0x0, binary_search_tree_node_nice(tree), &pass);

        link = binary_search_tree_node_link(tree);
        RESULT_CHECK_pointer(NULL, doubly_linked_list_node_val(link), &pass);
        binary_search_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(binary_search_tree_initial), pass);
    return;
}


static void
unit_test_binary_search_tree_node_initial(void)
{
    bool pass;
    sint64 nice;
    uint32 loop;
    struct binary_search_tree *tree;
    struct doubly_linked_list *link;

    TEST_PERFORMANCE_CHECKPOINT;

    nice = 0xfade;
    pass = true;
    binary_search_tree_node_initial(NULL, &pass, nice);

    loop = 0x22345afu;
    while (0 != loop--) {
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
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

        binary_search_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(binary_search_tree_node_initial), pass);
    return;
}

static void
unit_test_binary_search_tree_destroy(void)
{
    bool pass;
    struct binary_search_tree *tree;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = NULL;

    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = binary_search_tree_create();
    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = unit_test_binary_search_tree_sample(0x212345, 0x3ABCDE);
    binary_search_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    test_result_print(SYM_2_STR(binary_search_tree_destroy), pass);

    return;
}

static void
unit_test_binary_search_tree_node_find(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x221234, 0x3BCDEF);

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
    test_result_print(SYM_2_STR(binary_search_tree_node_find), pass);

    return;
}


static void
unit_test_binary_search_tree_node_find_min(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x231234, 0x29ABCD);

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find_min(NULL), &pass);

    tmp = binary_search_tree_node_find_min(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);

    binary_search_tree_destroy(&tree);
    test_result_print(SYM_2_STR(binary_search_tree_node_find_min), pass);

    return;
}


static void
unit_test_binary_search_tree_node_find_max(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x231234, 0x29ABCD);

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find_max(NULL), &pass);

    tmp = binary_search_tree_node_find_min(tree);
    RESULT_CHECK_pointer(NULL, binary_search_tree_child_left(tmp), &pass);

    binary_search_tree_destroy(&tree);
    test_result_print(SYM_2_STR(binary_search_tree_node_find_max), pass);

    return;
}

static void
unit_test_binary_search_tree_height(void)
{
    bool pass;
    struct binary_search_tree *tree;
    sint32 child;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x3183F1, 0x31820C);

    RESULT_CHECK_sint32(-1, binary_search_tree_height(NULL), &pass);

    child = MAX_S(binary_search_tree_height(binary_search_tree_child_left(tree)),
        binary_search_tree_height(binary_search_tree_child_right(tree)));
    RESULT_CHECK_sint32(child + 1, binary_search_tree_height(tree), &pass);

    binary_search_tree_destroy(&tree);
    test_result_print(SYM_2_STR(binary_search_tree_height), pass);

    return;
}

static void
unit_test_binary_search_tree_node_contain_p(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;
    struct binary_search_tree *fake;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x237FD7, 0x3AD31D);
    tmp = binary_search_tree_node_create(&pass, 0x1234);

    RESULT_CHECK_bool(false, binary_search_tree_node_contain_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_node_contain_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, binary_search_tree_node_contain_p(tree, tmp), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_max(tree);
    RESULT_CHECK_bool(true, binary_search_tree_node_contain_p(tree, tmp), &pass);

    fake = binary_search_tree_node_create(tmp, binary_search_tree_node_nice(tmp));
    RESULT_CHECK_bool(false, binary_search_tree_node_contain_p(tree, fake), &pass);

    binary_search_tree_destroy(&fake);
    binary_search_tree_destroy(&tree);
    test_result_print(SYM_2_STR(binary_search_tree_node_contain_p), pass);

    return;
}

static void
unit_test_binary_search_tree_node_insert(void)
{
    bool pass;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;
    struct binary_search_tree *inserted;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = unit_test_binary_search_tree_sample(0x384321, 0x331A2B);
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
    test_result_print(SYM_2_STR(binary_search_tree_node_insert), pass);

    return;
}


static void
unit_test_binary_search_tree_node_remove(void)
{
    bool pass;
    sint64 nice;
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, binary_search_tree_node_remove(&tree, 0x0), &pass);

    tree = unit_test_binary_search_tree_sample(0x2F4321, 0x32ABCD);
    tmp = tree;
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_min(tree);
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_max(tree);
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_find(tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_create(&pass, 0x7FFFFF);
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(NULL, binary_search_tree_node_remove(&tree, nice), &pass);
    binary_search_tree_destroy(&tmp);
    binary_search_tree_destroy(&tree);

    tree = binary_search_tree_node_create(&pass, 0x7FFFFF);
    tmp = tree;
    nice = binary_search_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, binary_search_tree_node_remove(&tree, nice), &pass);
    binary_search_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_node_remove), pass);
    return;
}

static void
unit_test_binary_search_tree_iterate(void)
{
    bool pass;
    struct binary_search_tree *tree;
    uint32 cnt;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    cnt = 0x2C872D;
    binary_search_tree_iterate(NULL, &tree_iterate_handler, ORDER_PRE);

    reference = 0;
    tree = unit_test_binary_search_tree_sample(0x2AE328, cnt);
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
    test_result_print(SYM_2_STR(binary_search_tree_iterate), pass);

    return;
}
