static void
unit_test_avl_tree_struct_field(void)
{
    bool pass;
    uint32 loop;
    sint64 nice;
    sint32 height;
    struct avl_tree *tree;
    struct avl_tree *tmp;

    

    loop = 0xf12345u;
    while (0 != loop--) {
        pass = true;
        nice = -0xfade;
        tree = avl_tree_create();
        tmp = avl_tree_node_create(NULL, nice);

        avl_tree_node_nice_set(tmp, nice);
        RESULT_CHECK_sint64(nice, avl_tree_node_nice(tmp), &pass);

        tree->alias.left = &tmp->alias;
        RESULT_CHECK_pointer(tmp, avl_tree_child_left(tree), &pass);

        nice = 0xfade;
        tmp = avl_tree_node_create(NULL, nice);
        tree->alias.right = &tmp->alias;
        RESULT_CHECK_pointer(tmp, avl_tree_child_right(tree), &pass);

        height = 0xbed;
        avl_tree_height_set(tree, height);
        RESULT_CHECK_sint32(height, avl_tree_height(tree), &pass);

        avl_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(avl_tree_struct_field), pass);
    return;
}

static inline struct avl_tree *
unit_test_avl_tree_sample(uint64 range, uint32 node_count)
{
    struct avl_tree *retval;
    struct avl_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = avl_tree_create();
    avl_tree_node_initial(retval, &reference, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = avl_tree_node_create(NULL, 0x0);
        avl_tree_node_initial(tmp, &reference, nice);
        if (tmp != avl_tree_node_insert(&retval, tmp)) {
            avl_tree_destroy(&tmp);
        }
        i++;
    }

    return retval;
}

static void
unit_test_avl_tree_create(void)
{
    bool pass;
    uint32 loop;
    struct avl_tree *tree;
    struct doubly_linked_list *link;

    

    loop = 0x22345afu;
    while (0 != loop--) {
        pass = true;
        tree = avl_tree_create();

        RESULT_CHECK_pointer(NULL, avl_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(0x0, avl_tree_node_nice(tree), &pass);

        link = avl_tree_node_link(tree);
        RESULT_CHECK_pointer(NULL, doubly_linked_list_node_val(link), &pass);

        avl_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(avl_tree_create), pass);
    return;
}

static void
unit_test_avl_tree_node_create(void)
{
    bool pass;
    uint32 loop;
    sint64 nice;
    struct avl_tree *tree;
    struct doubly_linked_list *link;

    

    loop = 0x22345afu;
    while (0 != loop--) {
        nice = 0xfade;
        pass = true;
        tree = avl_tree_node_create(&pass, nice);

        RESULT_CHECK_pointer(NULL, avl_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(nice, avl_tree_node_nice(tree), &pass);

        link = avl_tree_node_link(tree);
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

        avl_tree_destroy(&tree);
    }
    test_result_print(SYM_2_STR(avl_tree_node_create), pass);

    return;
}

static void
unit_test_avl_tree_initial(void)
{
    bool pass;
    uint32 loop;
    sint64 nice;
    struct avl_tree *tree;
    struct doubly_linked_list *link;

    

    tree = NULL;
    avl_tree_initial(tree);

    loop = 0x22345afu;
    while (0 != loop--) {
        pass = true;
        nice = 0xfade;
        tree = avl_tree_node_create(&pass, nice);
        avl_tree_initial(tree);

        RESULT_CHECK_pointer(NULL, avl_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(0x0, avl_tree_node_nice(tree), &pass);

        link = avl_tree_node_link(tree);
        RESULT_CHECK_pointer(NULL, doubly_linked_list_node_val(link), &pass);

        avl_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(avl_tree_initial), pass);
    return;
}

static void
unit_test_avl_tree_node_initial(void)
{
    bool pass;
    sint64 nice;
    uint32 loop;
    struct avl_tree *tree;
    struct doubly_linked_list *link;

    

    tree = NULL;
    nice = 0xfade;
    pass = true;
    avl_tree_node_initial(tree, &pass, nice);

    loop = 0x22345afu;
    while (0 != loop--) {
        pass = true;
        nice = 0xfade;
        tree = avl_tree_node_create(&pass, nice);
        avl_tree_node_initial(tree, &pass, nice);

        RESULT_CHECK_pointer(NULL, avl_tree_child_left(tree), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_child_right(tree), &pass);
        RESULT_CHECK_sint64(nice, avl_tree_node_nice(tree), &pass);

        link = avl_tree_node_link(tree);
        RESULT_CHECK_pointer(&pass, doubly_linked_list_node_val(link), &pass);

        avl_tree_destroy(&tree);
    }

    test_result_print(SYM_2_STR(avl_tree_node_initial), pass);
    return;
}

static void
unit_test_avl_tree_destroy(void)
{
    bool pass;
    struct avl_tree *tree;

    

    pass = true;
    tree = NULL;

    avl_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = avl_tree_create();
    avl_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    tree = unit_test_avl_tree_sample(0x1FBDE8, 0x1A27EF);
    avl_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    test_result_print(SYM_2_STR(avl_tree_destroy), pass);
    return;
}

static void
unit_test_avl_tree_node_find(void)
{
    bool pass;
    sint64 nice;
    struct avl_tree *tree;
    struct avl_tree *tmp;

    

    pass = true;
    tree = unit_test_avl_tree_sample(0x17F28A, 0x187D21);

    RESULT_CHECK_pointer(NULL, avl_tree_node_find(NULL, 0x0), &pass);

    nice = avl_tree_node_nice(tree);
    RESULT_CHECK_pointer(tree, avl_tree_node_find(tree, nice), &pass);

    nice = 0x7FFFFFF;
    RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);

    tmp = avl_tree_node_find_min(tree);
    nice = avl_tree_node_nice(tmp);
    RESULT_CHECK_pointer(tmp, avl_tree_node_find(tree, nice), &pass);

    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_node_find), pass);

    return;
}

static void
unit_test_avl_tree_node_find_min(void)
{
    bool pass;
    struct avl_tree *tree;
    struct avl_tree *tmp;

    

    pass = true;
    tree = unit_test_avl_tree_sample(0x139131, 0x1264DC);

    RESULT_CHECK_pointer(NULL, avl_tree_node_find_min(NULL), &pass);

    tmp = avl_tree_node_find_min(tree);
    RESULT_CHECK_pointer(NULL, avl_tree_child_left(tmp), &pass);

    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_node_find_min), pass);

    return;
}

static void
unit_test_avl_tree_node_find_max(void)
{
    bool pass;
    struct avl_tree *tree;
    struct avl_tree *tmp;

    

    pass = true;
    tree = unit_test_avl_tree_sample(0x13F1A1, 0x12E494);

    RESULT_CHECK_pointer(NULL, avl_tree_node_find_max(NULL), &pass);

    tmp = avl_tree_node_find_max(tree);
    RESULT_CHECK_pointer(NULL, avl_tree_child_right(tmp), &pass);

    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_node_find_max), pass);

    return;
}

static void
unit_test_avl_tree_node_contains_p(void)
{
    bool pass;
    struct avl_tree *tree;
    struct avl_tree *tmp;
    struct avl_tree *fake;

    

    pass = true;
    tree = unit_test_avl_tree_sample(0x1E28D1, 0x1C251F);
    tmp = avl_tree_node_create(&pass, 0x7FFFFFFF);

    RESULT_CHECK_bool(false, avl_tree_node_contains_p(NULL, tmp), &pass);
    RESULT_CHECK_bool(false, avl_tree_node_contains_p(tree, NULL), &pass);
    RESULT_CHECK_bool(false, avl_tree_node_contains_p(tree, tmp), &pass);
    avl_tree_destroy(&tmp);

    tmp = avl_tree_node_find_max(tree);
    RESULT_CHECK_bool(true, avl_tree_node_contains_p(tree, tmp), &pass);

    fake = avl_tree_node_create(tmp, avl_tree_node_nice(tmp));
    RESULT_CHECK_bool(false, avl_tree_node_contains_p(tree, fake), &pass);

    avl_tree_destroy(&fake);
    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_node_contains_p), pass);
    return;
}

static void
unit_test_avl_tree_iterate(void)
{
    bool pass;
    struct avl_tree *tree;
    uint32 cnt;

    

    pass = true;
    cnt = 0x10F3EC;
    tree = unit_test_avl_tree_sample(0x13813F, cnt);

    avl_tree_iterate(NULL, &tree_iterate_handler, ORDER_PRE);

    reference = 0;
    avl_tree_iterate(tree, &tree_iterate_handler, ORDER_END);
    RESULT_CHECK_uint32(0, reference, &pass);

    avl_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
    RESULT_CHECK_uint32(cnt, reference, &pass);

    reference = 0;
    avl_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
    RESULT_CHECK_uint32(cnt, reference, &pass);

    reference = 0;
    avl_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
    RESULT_CHECK_uint32(cnt, reference, &pass);

    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_iterate), pass);

    return;
}

static void
unit_test_avl_tree_balanced_p(void)
{
    bool pass;
    struct avl_tree *tree;
    struct avl_tree *tmp;

    

    pass = true;
    RESULT_CHECK_bool(true, avl_tree_balanced_p(NULL), &pass);

    tree = unit_test_avl_tree_sample(0xA83EA, 0xBD264);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_node_create(&pass, 0x1234);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);

    tmp = avl_tree_node_create(&pass, 0xFFFFFFE);
    avl_tree_node_insert(&tree, tmp);
    tmp = avl_tree_node_create(&pass, 0xFFFFFFF);
    avl_tree_node_insert(&tree, tmp);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_node_create(&pass, 0xFFFFFFF);
    avl_tree_node_insert(&tree, tmp);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);

    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_balanced_p), pass);

    return;
}

static void
unit_test_avl_tree_node_insert(void)
{
    bool pass;
    struct avl_tree *tree;
    struct avl_tree *tmp;
    struct avl_tree *inserted;

    

    pass = true;
    RESULT_CHECK_pointer(NULL, avl_tree_node_insert(NULL, NULL), &pass);
    tree = NULL;
    RESULT_CHECK_pointer(NULL, avl_tree_node_insert(&tree, tree), &pass);

    tree = unit_test_avl_tree_sample(0x12E345, 0x10EF4A);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    tmp = avl_tree_node_create(&pass, 0xFFEDAB);
    RESULT_CHECK_pointer(tmp, avl_tree_node_insert(&tree, tmp), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    RESULT_CHECK_pointer(tmp,
        avl_tree_node_find(tree, avl_tree_node_nice(tmp)),
        &pass);
    RESULT_CHECK_pointer(tmp, avl_tree_node_insert(&tree, tmp), &pass);

    inserted = tmp;
    tmp = avl_tree_node_create(&pass, 0xFFEDAB);
    RESULT_CHECK_pointer(inserted, avl_tree_node_insert(&tree, tmp), &pass);

    avl_tree_destroy(&tmp);
    avl_tree_destroy(&tree);
    test_result_print(SYM_2_STR(avl_tree_node_insert), pass);
    return;
}

static void
unit_test_avl_tree_node_remove(void)
{
    bool pass;
    sint64 nice;
    struct avl_tree *tree;
    struct avl_tree *tmp;
    uint32 count;

    

    nice = 0x0u;
    pass = true;
    tree = NULL;
    avl_tree_node_remove(&tree, nice);

    tree = unit_test_avl_tree_sample(0x13AEF, 0x30DE7);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    nice = avl_tree_node_nice(tree);
    tmp = avl_tree_node_remove(&tree, nice);

    RESULT_CHECK_sint64(nice, avl_tree_node_nice(tmp), &pass);
    RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    avl_tree_destroy(&tmp);
    avl_tree_destroy(&tree);

    tree = unit_test_avl_tree_sample(0x32DFBD, 0x13ABDE);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    count = 0x8u;
    while (0 != count) {
        tmp = avl_tree_node_find_min(tree);
        nice = avl_tree_node_nice(tmp);
        tmp = avl_tree_node_remove(&tree, nice);

        RESULT_CHECK_sint32(nice, avl_tree_node_nice(tmp), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
        avl_tree_destroy(&tmp);

        tmp = avl_tree_node_find_max(tree);
        nice = avl_tree_node_nice(tmp);
        tmp = avl_tree_node_remove(&tree, nice);

        RESULT_CHECK_sint32(nice, avl_tree_node_nice(tmp), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
        avl_tree_destroy(&tmp);

        count--;
    }
    avl_tree_destroy(&tree);

    tree = unit_test_avl_tree_sample(0x32FB, 0x22BE);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    count = 0x1000u;
    while (0 != count) {
        nice = avl_tree_node_nice(tree);
        tmp = avl_tree_node_remove(&tree, nice);

        RESULT_CHECK_sint64(nice, avl_tree_node_nice(tmp), &pass);
        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
        avl_tree_destroy(&tmp);

        count--;
    }

    tmp = avl_tree_node_create(&pass, 0x7FFFFFF);
    nice = avl_tree_node_nice(tmp);

    RESULT_CHECK_pointer(NULL, avl_tree_node_remove(&tree, nice), &pass);
    RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);
    avl_tree_destroy(&tree);

    test_result_print(SYM_2_STR(avl_tree_node_remove), pass);
    return;
}

static void
unit_test_avl_tree_node_remove_and_destroy(void)
{
    bool pass;
    sint64 nice;
    struct avl_tree *tree;
    struct avl_tree *tmp;
    uint32 count;

    

    nice = 0x0u;
    pass = true;
    tree = NULL;
    avl_tree_node_remove_and_destroy(&tree, nice);

    tree = unit_test_avl_tree_sample(0x13AEF, 0x30DE7);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    nice = avl_tree_node_nice(tree);
    avl_tree_node_remove_and_destroy(&tree, nice);

    RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tree);

    tree = unit_test_avl_tree_sample(0x32DFBD, 0x13ABDE);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    count = 0x8u;
    while (0 != count) {
        tmp = avl_tree_node_find_min(tree);
        nice = avl_tree_node_nice(tmp);
        avl_tree_node_remove_and_destroy(&tree, nice);

        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

        tmp = avl_tree_node_find_max(tree);
        nice = avl_tree_node_nice(tmp);
        avl_tree_node_remove_and_destroy(&tree, nice);

        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

        count--;
    }
    avl_tree_destroy(&tree);

    tree = unit_test_avl_tree_sample(0x32FB, 0x22BE);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

    count = 0x1000u;
    while (0 != count) {
        nice = avl_tree_node_nice(tree);
        avl_tree_node_remove_and_destroy(&tree, nice);

        RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
        RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);

        count--;
    }

    tmp = avl_tree_node_create(&pass, 0x7FFFFFF);
    nice = avl_tree_node_nice(tmp);

    RESULT_CHECK_pointer(NULL, avl_tree_node_find(tree, nice), &pass);
    RESULT_CHECK_bool(true, avl_tree_balanced_p(tree), &pass);
    avl_tree_destroy(&tmp);
    avl_tree_destroy(&tree);

    test_result_print(SYM_2_STR(avl_tree_node_remove_and_destroy), pass);
    return;
}

