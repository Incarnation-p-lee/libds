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
    PERFORMANCE_TEST_RESULT(splay_tree_struct_field);
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

    PERFORMANCE_TEST_RESULT(splay_tree_create);
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

    PERFORMANCE_TEST_RESULT(splay_tree_node_create);
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
    PERFORMANCE_TEST_RESULT(splay_tree_initial);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_initial);
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

    PERFORMANCE_TEST_RESULT(splay_tree_destroy);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_find);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_find_min);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_find_max);
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
    PERFORMANCE_TEST_RESULT(splay_tree_height);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_contains_p);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_insert);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_remove);
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
    PERFORMANCE_TEST_RESULT(splay_tree_node_remove_and_destroy);
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
    PERFORMANCE_TEST_RESULT(splay_tree_iterate);
}

