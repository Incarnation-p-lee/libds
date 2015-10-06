static void
performance_test_splay_tree_struct_field(uint32 count)
{
    struct splay_tree *tree;

    tree = splay_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_nice_set(tree, 0x23);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_struct_field),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_create(uint32 count)
{
    struct splay_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = splay_tree_create();
        splay_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(splay_tree_create),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_create(uint32 count)
{
    struct splay_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = splay_tree_node_create(NULL, 0x23ed);
        splay_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(splay_tree_node_create),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_initial(uint32 count)
{
    struct splay_tree *tree;

    tree = splay_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_initial(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_initial(uint32 count)
{
    struct splay_tree *tree;

    tree = splay_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_initial(tree, NULL, 0x23d);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_initial),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_destroy(uint32 count)
{
    struct splay_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = test_splay_tree_sample(0x52, 0x9);
        splay_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(splay_tree_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_find(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x21352, 0x12de2);
    tmp = splay_tree_node_find_max(&tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_find(&tree, splay_tree_node_nice(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_find),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_find_min(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_find_min(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_find_min),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_find_max(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_find_max(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_find_max),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_height(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x352, 0x122);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_height(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_height),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_contains_p(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x352, 0x122);
    tmp = (struct splay_tree *)&count;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_node_contains_p(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_contains_p),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_insert(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    count = count >> 3;
    count = 0 == count ? 1000 : count;
    tree = splay_tree_node_create(NULL, -0x122);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_node_create(NULL, count);
        splay_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_insert),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_remove(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;
    sint64 nice;

    tree = test_splay_tree_sample(0x4234, 0x2823);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_node_find_max(&tree);
        nice = splay_tree_node_nice(tmp);
        tmp = splay_tree_node_remove(&tree, nice);
        splay_tree_destroy(&tmp);

        tmp = splay_tree_node_create(NULL, nice + 1);
        splay_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_remove),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_node_remove_and_destroy(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;
    sint64 nice;

    tree = test_splay_tree_sample(0x4234, 0x2823);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_node_find_max(&tree);
        nice = splay_tree_node_nice(tmp);
        splay_tree_node_remove_and_destroy(&tree, nice);

        tmp = splay_tree_node_create(NULL, nice + 1);
        splay_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_node_remove_and_destroy),
        performance_test_time_stamp_period());
}

static void
performance_test_splay_tree_iterate(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x44, 0x32);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
        splay_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
        splay_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    performance_test_result_print(SYM_2_STR(splay_tree_iterate),
        performance_test_time_stamp_period());
}

