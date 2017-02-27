static void
ptest_binary_indexed_tree_create(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0x1ea;
    data = test_sint64_data_array(size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = binary_indexed_tree_create(data, size);
        binary_indexed_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_create);
}

static void
ptest_binary_indexed_tree_destroy(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0x4a;
    data = test_sint64_data_array(size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = binary_indexed_tree_create(data, size);
        binary_indexed_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_destroy);
}

static void
ptest_binary_indexed_tree_add(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0xb2182;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_indexed_tree_add(tree, count % size, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_add);
}

static void
ptest_binary_indexed_tree_sub(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0xe31a2;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_indexed_tree_sub(tree, count % size, count);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_sub);
}

static void
ptest_binary_indexed_tree_sum(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0x2f31a2;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_indexed_tree_sum(tree, size);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_sum);
}

static void
ptest_binary_indexed_tree_range_sum(uint32 count)
{
    uint32 size;
    sint64 *data;
    struct binary_indexed_tree *tree;

    size = 0x2f31a2;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        binary_indexed_tree_range_sum(tree, count % size, size);
    }

    PERFORMANCE_TEST_ENDPOINT;

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(binary_indexed_tree_range_sum);
}

