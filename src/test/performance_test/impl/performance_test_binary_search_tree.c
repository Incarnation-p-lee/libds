static void
performance_test_binary_search_tree_struct_field(uint32 count)
{
    struct binary_search_tree *tree;

    tree = binary_search_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_search_tree_nice_set(tree, 0);
        binary_search_tree_left_set(tree, NULL);
        binary_search_tree_right_set(tree, NULL);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_struct_field);
}

static void
performance_test_binary_search_tree_create(uint32 count)
{
    struct binary_search_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = binary_search_tree_create();
        binary_search_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(binary_search_tree_create);
}

static void
performance_test_binary_search_tree_node_create(uint32 count)
{
    // struct binary_search_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // tree = binary_search_tree_node_create(NULL, 0x23);
        // binary_search_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(binary_search_tree_node_create);
}

static void
performance_test_binary_search_tree_initial(uint32 count)
{
    struct binary_search_tree *tree;

    tree = binary_search_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_search_tree_initial(tree, 0, tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_initial);
}

static void
performance_test_binary_search_tree_node_initial(uint32 count)
{
    struct binary_search_tree *tree;

    tree = binary_search_tree_create();

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_node_initial(tree, NULL, 0x39);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_initial);
}

static void
performance_test_binary_search_tree_destroy(uint32 count)
{
    struct binary_search_tree *tree;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = test_binary_search_tree_sample(0x15, 0xd);
        binary_search_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(binary_search_tree_destroy);
}

static void
performance_test_binary_search_tree_node_find(uint32 count)
{
    struct binary_search_tree *tree;
    // struct binary_search_tree *tmp;

    tree = test_binary_search_tree_sample(0x93915, 0x7282d);
    // tmp = binary_search_tree_find_max(tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_node_find(tree, binary_search_tree_node_nice(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_find);
}

static void
performance_test_binary_search_tree_node_find_min(uint32 count)
{
    struct binary_search_tree *tree;

    tree = test_binary_search_tree_sample(0x93915, 0x8282d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_node_find_min(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_find_min);
}

static void
performance_test_binary_search_tree_node_find_max(uint32 count)
{
    struct binary_search_tree *tree;

    tree = test_binary_search_tree_sample(0xa3915, 0x9282d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_node_find_max(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_find_max);
}

static void
performance_test_binary_search_tree_height(uint32 count)
{
    struct binary_search_tree *tree;

    tree = test_binary_search_tree_sample(0xa32, 0x12d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_height(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_height);
}

static void
performance_test_binary_search_tree_node_contains_p(uint32 count)
{
    struct binary_search_tree *tree;
    // struct binary_search_tree *tmp;

    tree = test_binary_search_tree_sample(0xf2a32, 0xae12d);
    // tmp = binary_search_tree_find_max(tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // binary_search_tree_node_contains_p(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_contains_p);
}

static void
performance_test_binary_search_tree_node_insert(uint32 count)
{
    struct binary_search_tree *tree;
    // struct binary_search_tree *tmp;

    count = count >> 6;
    count = 0 == count ? 1000 : count;
    tree = binary_search_tree_create();
    binary_search_tree_initial(tree, -0xfade, NULL);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // tmp = binary_search_tree_node_create(NULL, count);
        // binary_search_tree_node_insert(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_insert);
}

static void
performance_test_binary_search_tree_node_remove(uint32 count)
{
    struct binary_search_tree *tree;
    // struct binary_search_tree *tmp;
    // sint64 nice;

    tree = test_binary_search_tree_sample(0xa3d3, 0x3f82);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // tmp = binary_search_tree_node_find_max(tree);
        // nice = binary_search_tree_node_nice(tmp);

        // tmp = binary_search_tree_node_remove(&tree, nice);
        // binary_search_tree_destroy(&tmp);

        // tmp = binary_search_tree_node_create(NULL, nice + 1);
        // binary_search_tree_node_insert(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_remove);
}

static void
performance_test_binary_search_tree_node_remove_and_destroy(uint32 count)
{
    struct binary_search_tree *tree;
    // struct binary_search_tree *tmp;
    // sint64 nice;

    tree = test_binary_search_tree_sample(0x93d3, 0x4f82);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        // tmp = binary_search_tree_node_find_max(tree);
        // nice = binary_search_tree_node_nice(tmp);

        // binary_search_tree_node_remove_and_destroy(&tree, nice);

        // tmp = binary_search_tree_node_create(NULL, nice + 1);
        // binary_search_tree_node_insert(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_node_remove_and_destroy);
}

static void
performance_test_binary_search_tree_iterate(uint32 count)
{
    struct binary_search_tree *tree;

    tree = test_binary_search_tree_sample(0xa9, 0x3f);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_POST);
        binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_PRE);
        binary_search_tree_iterate(tree, &tree_iterate_handler, ORDER_IN);
    }

    PERFORMANCE_TEST_ENDPOINT;

    binary_search_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_search_tree_iterate);
}

