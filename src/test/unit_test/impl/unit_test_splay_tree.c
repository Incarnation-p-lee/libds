static void
unit_test_splay_tree_struct_field(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x22345678u;
    pass = true;
    nice = -0xfade;
    tree = splay_tree_create();
    tmp = splay_tree_node_create(NULL, nice);

    while (0 != loop--) {
        splay_tree_node_nice_set(tmp, nice);
        RESULT_CHECK_sint64(nice, splay_tree_node_nice(tmp), &pass);

        splay_tree_child_left_set(tree, tmp);
        RESULT_CHECK_pointer(tmp, splay_tree_child_left(tree), &pass);
    }

    nice = 0xfade;
    tmp = splay_tree_node_create(NULL, nice);
    splay_tree_child_right_set(tree, tmp);
    RESULT_CHECK_pointer(tmp, splay_tree_child_right(tree), &pass);
    splay_tree_destroy(&tree);

    test_result_print(SYM_2_STR(splay_tree_struct_field), pass);
    return;
}

static inline struct splay_tree *
unit_test_splay_tree_sample(uint64 range, uint32 node_count)
{
    struct splay_tree *retval;
    struct splay_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = splay_tree_create();
    splay_tree_node_initial(retval, &reference, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = splay_tree_node_create(NULL, 0x0);
        splay_tree_node_initial(tmp, &reference, nice);
        if (tmp != splay_tree_node_insert(&retval, tmp)) {
            splay_tree_destroy(&tmp);
        }
        i++;
    }

    return retval;
}

static void
unit_test_splay_tree_create(void)
{
    bool pass;
    struct splay_tree *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567u;
    pass = true;

    while (0 != loop--) {
        tmp = splay_tree_create();
        splay_tree_destroy(&tmp);
    }

    tmp = splay_tree_create();
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tmp), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tmp), &pass);

    splay_tree_destroy(&tmp);
    test_result_print(SYM_2_STR(splay_tree_create), pass);

    return;
}

static void
unit_test_splay_tree_node_create(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567u;
    pass = true;
    nice = 0xfade;
    while (0 != loop--) {
        tree = splay_tree_node_create(&pass, nice);
        splay_tree_destroy(&tree);
    }

    tree = splay_tree_node_create(&pass, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);

    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_destroy(&tree);
    test_result_print(SYM_2_STR(splay_tree_node_create), pass);

    return;
}

static void
unit_test_splay_tree_initial(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf234567u;
    pass = true;
    nice = 0xbed;

    tree = splay_tree_node_create(&pass, nice);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);
    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_initial(NULL);
    while (0 != loop--) {
        splay_tree_initial(tree);
    }
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tree), &pass);

    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(NULL, doubly_linked_list_node_val(link), &pass);
    splay_tree_destroy(&tree);

    test_result_print(SYM_2_STR(splay_tree_initial), pass);
    return;
}

static void
unit_test_splay_tree_node_initial(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct doubly_linked_list *link;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    nice = 0xfade;
    pass = true;
    tree = splay_tree_create();

    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(0x0, splay_tree_node_nice(tree), &pass);

    splay_tree_node_initial(NULL, &pass, nice);
    while (0 != loop--) {
        splay_tree_node_initial(tree, &pass, nice);
    }
    link = splay_tree_node_link(tree);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tree), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_right(tree), &pass);
    RESULT_CHECK_sint64(nice, splay_tree_node_nice(tree), &pass);
    RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

    splay_tree_destroy(&tree);
    test_result_print(SYM_2_STR(splay_tree_node_initial), pass);

    return;
}

static void
unit_test_splay_tree_destroy(void)
{
    bool pass;
    struct splay_tree *tree;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x2234567u;
    pass = true;
    tree = NULL;

    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    while (0 != loop--) {
        tree = splay_tree_create();
        splay_tree_destroy(&tree);
    }
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = unit_test_splay_tree_sample(0xE2A47, 0xA0C23);
    splay_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    test_result_print(SYM_2_STR(splay_tree_destroy), pass);
    return;
}

static void
unit_test_splay_tree_height(void)
{
    bool pass;
    struct splay_tree *tree;
    sint32 child;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x534u;
    pass = true;
    tree = unit_test_splay_tree_sample(0x3726F, 0x3CE24);

    RESULT_CHECK_sint32(-1, splay_tree_height(NULL), &pass);

    child = MAX_S(splay_tree_height(splay_tree_child_left(tree)),
        splay_tree_height(splay_tree_child_right(tree)));
    while (0 != loop--) {
        RESULT_CHECK_sint32(child + 1, splay_tree_height(tree), &pass);
    }

    splay_tree_destroy(&tree);
    test_result_print(SYM_2_STR(splay_tree_height), pass);

    return;
}

static void
unit_test_splay_tree_node_contain_p(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    struct splay_tree *fake;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    pass = true;
    tree = unit_test_splay_tree_sample(0x124F0, 0x873BD);
    tmp = splay_tree_node_create(&pass, 0x1234);

    RESULT_CHECK_bool(false, splay_tree_node_contain_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_node_contain_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, splay_tree_node_contain_p(tree, tmp), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_max(&tree);
    while (0 != loop--) {
        RESULT_CHECK_bool(true, splay_tree_node_contain_p(tree, tmp), &pass);
    }

    fake = splay_tree_node_create(tmp, splay_tree_node_nice(tmp));
    RESULT_CHECK_bool(false, splay_tree_node_contain_p(tree, fake), &pass);

    splay_tree_destroy(&fake);
    splay_tree_destroy(&tree);

    test_result_print(SYM_2_STR(splay_tree_node_contain_p), pass);
    return;
}

static void
unit_test_splay_tree_node_find(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    pass = true;
    tree = unit_test_splay_tree_sample(0x103FA, 0x1743A);

    RESULT_CHECK_pointer(NULL,
        splay_tree_node_find(NULL, splay_tree_node_nice(tree)),
        &pass);

    while (0 != loop--) {
        RESULT_CHECK_pointer(tree,
            splay_tree_node_find(&tree, splay_tree_node_nice(tree)), &pass);
    }

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
    test_result_print(SYM_2_STR(splay_tree_node_find), pass);

    return;
}

static void
unit_test_splay_tree_node_find_min(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    pass = true;
    tree = unit_test_splay_tree_sample(0xF17C2, 0xBD482);

    RESULT_CHECK_pointer(NULL, splay_tree_node_find_min(NULL), &pass);
    while (0 != loop--) {
        tmp = splay_tree_node_find_min(&tree);
    }

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);
    splay_tree_destroy(&tree);

    test_result_print(SYM_2_STR(splay_tree_node_find_min), pass);
    return;
}

static void
unit_test_splay_tree_node_find_max(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12345678u;
    pass = true;
    tree = unit_test_splay_tree_sample(0x3F2E4, 0x90B2A);

    RESULT_CHECK_pointer(NULL, splay_tree_node_find_max(NULL), &pass);
    while (0 != loop--) {
        tmp = splay_tree_node_find_min(&tree);
    }

    RESULT_CHECK_pointer(tmp, tree, &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_child_left(tmp), &pass);
    splay_tree_destroy(&tree);

    test_result_print(SYM_2_STR(splay_tree_node_find_max), pass);
    return;
}

static void
unit_test_splay_tree_node_insert(void)
{
    bool pass;
    struct splay_tree *tree;
    struct splay_tree *tmp;
    struct splay_tree *inserted;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, splay_tree_node_insert(&tree, NULL), &pass);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = unit_test_splay_tree_sample(0x3B4C29, 0x271F2C);
    tmp = splay_tree_node_create(&pass, 0xFFFDEA);

    RESULT_CHECK_pointer(NULL, splay_tree_node_insert(&tree, NULL), &pass);

    tree = unit_test_splay_tree_sample(0x3B4C29, 0x271F2C);
    tmp = splay_tree_node_create(&pass, 0xFFFDEA);

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

    test_result_print(SYM_2_STR(splay_tree_node_insert), pass);
    return;
}

static void
unit_test_splay_tree_node_remove(void)
{
    bool pass;
    sint64 nice;
    struct splay_tree *tree;
    struct splay_tree *tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    pass = true;
    tree = NULL;

    RESULT_CHECK_pointer(NULL, splay_tree_node_remove(&tree, 0x0), &pass);

    tree = unit_test_splay_tree_sample(0x2F4321, 0x32ABCD);
    tmp = tree;
    nice = splay_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, splay_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_min(&tree);
    nice = splay_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, splay_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, splay_tree_node_find(&tree, nice), &pass);
    splay_tree_destroy(&tmp);

    tmp = splay_tree_node_find_max(&tree);
    nice = splay_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, splay_tree_node_remove(&tree, nice), &pass);
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

    test_result_print(SYM_2_STR(splay_tree_node_remove), pass);
    return;
}

static void
unit_test_splay_tree_iterate(void)
{
    bool pass;
    struct splay_tree *tree;
    uint32 cnt;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3u;
    pass = true;
    cnt = 0xC872D;

    splay_tree_iterate(NULL, &tree_iterate_handler, ORDER_PRE);

    reference = 0;
    splay_tree_iterate(tree, &tree_iterate_handler, ORDER_END);
    RESULT_CHECK_uint32(0x0u, reference, &pass);

    while (0 != loop--) {
        pass = true;
        cnt = 0xC872D;
        tree = unit_test_splay_tree_sample(0xAE328, cnt);

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
    }

    test_result_print(SYM_2_STR(splay_tree_iterate), pass);
    return;
}
