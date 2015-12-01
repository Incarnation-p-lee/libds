static void
performance_test_avl_tree_struct_field(uint32 count)
{
    struct avl_tree *tree;

    tree = avl_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_nice_set(tree, 0);
        avl_tree_height_set(tree, 0);
        avl_tree_node_link_set(tree, avl_tree_node_link(tree));
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_struct_field);
}

static void
performance_test_avl_tree_create(uint32 count)
{
    struct avl_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = avl_tree_create();
        avl_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_create);
}

static void
performance_test_avl_tree_node_create(uint32 count)
{
    struct avl_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = avl_tree_node_create(NULL, 0);
        avl_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_node_create);
}

static void
performance_test_avl_tree_initial(uint32 count)
{
    struct avl_tree *tree;

    tree = avl_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_initial(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_initial);
}

static void
performance_test_avl_tree_node_initial(uint32 count)
{
    struct avl_tree *tree;

    tree = avl_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_initial(tree, NULL, 0xdfe);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_initial);
}

static void
performance_test_avl_tree_destroy(uint32 count)
{
    struct avl_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = test_avl_tree_sample(0x12, 0x7);
        avl_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_destroy);
}

static void
performance_test_avl_tree_node_find(uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;

    tree = test_avl_tree_sample(0x12a49, 0x5233);
    tmp = avl_tree_node_find_max(tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_find(tree, avl_tree_node_nice(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_find);
}

static void
performance_test_avl_tree_node_find_min(uint32 count)
{
    struct avl_tree *tree;

    tree = test_avl_tree_sample(0x62a49, 0x4233);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_find_min(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_find_min);
}

static void
performance_test_avl_tree_node_find_max(uint32 count)
{
    struct avl_tree *tree;

    tree = test_avl_tree_sample(0x62a49, 0x5233);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_find_max(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_find_max);
}

static void
performance_test_avl_tree_node_contains_p(uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;

    tree = test_avl_tree_sample(0x62a49, 0x6233);
    tmp = avl_tree_node_find_max(tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_node_contains_p(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_contains_p);
}

static void
performance_test_avl_tree_balanced_p(uint32 count)
{
    struct avl_tree *tree;

    tree = test_avl_tree_sample(0xa9, 0x33);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_balanced_p(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_balanced_p);
}

static void
performance_test_avl_tree_node_insert(uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;

    tree = avl_tree_node_create(NULL, -0x1f2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = avl_tree_node_create(NULL, count);
        avl_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_insert);
}

static void
performance_test_avl_tree_node_remove(uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;
    sint64 nice;

    tree = test_avl_tree_sample(0x2352, 0x21f2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = avl_tree_node_find_max(tree);
        nice = avl_tree_node_nice(tmp);

        tmp = avl_tree_node_remove(&tree, nice);
        avl_tree_destroy(&tmp);

        tmp = avl_tree_node_create(NULL, nice + 1);
        avl_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_remove);
}

static void
performance_test_avl_tree_node_remove_and_destroy(uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;
    sint64 nice;

    tree = test_avl_tree_sample(0x2352, 0x21f2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = avl_tree_node_find_max(tree);
        nice = avl_tree_node_nice(tmp);

        avl_tree_node_remove_and_destroy(&tree, nice);

        tmp = avl_tree_node_create(NULL, nice + 1);
        avl_tree_node_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_node_remove_and_destroy);
}

static void
performance_test_avl_tree_iterate(uint32 count)
{
    struct avl_tree *tree;

    tree = test_avl_tree_sample(0xa2, 0x32);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
        avl_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
        avl_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_iterate);
}

