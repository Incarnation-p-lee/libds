static inline void
utest_binary_indexed_tree_create(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    struct binary_indexed_tree *tree;

    pass = true;
    size = 0x1234;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    RESULT_CHECK_pointer(NULL, binary_indexed_tree_create(NULL, size), &pass);
    RESULT_CHECK_pointer(NULL, binary_indexed_tree_create(data, 0), &pass);

    RESULT_CHECK_uint32(size, binary_indexed_tree_size(tree), &pass);
    RESULT_CHECK_sint64(data[0], binary_indexed_tree_value(tree, 1), &pass);

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_indexed_tree_create, pass);
}

static inline void
utest_binary_indexed_tree_destroy(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    struct binary_indexed_tree *tree;

    pass = true;
    size = 0x2de4;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    binary_indexed_tree_destroy(NULL);
    binary_indexed_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    memory_cache_free(data);
    UNIT_TEST_RESULT(binary_indexed_tree_destroy, pass);
}

static inline void
utest_binary_indexed_tree_add(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    uint32 number;
    struct binary_indexed_tree *tree;
    struct binary_indexed_tree *ref;

    pass = true;
    size = 0x1f8a;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    binary_indexed_tree_add(NULL, 1, 0x372);
    binary_indexed_tree_add(tree, 0, 0x372);
    binary_indexed_tree_add(tree, 0x7fffffff, 0x372);

    number = 1;
    binary_indexed_tree_add(tree, 1, 0x372);
    data[number - 1] += 0x372;

    ref = binary_indexed_tree_create(data, size);
    number = size;
    while (number > 0) {
        RESULT_CHECK_sint64(tree->data[number], ref->data[number], &pass);
        number--;
    }

    memory_cache_free(data);
    binary_indexed_tree_destroy(&ref);
    binary_indexed_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_indexed_tree_add, pass);
}

static inline void
utest_binary_indexed_tree_sub(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    uint32 number;
    struct binary_indexed_tree *tree;
    struct binary_indexed_tree *ref;

    pass = true;
    size = 0x390e;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    binary_indexed_tree_sub(NULL, 1, 0x372);
    binary_indexed_tree_sub(tree, 0, 0x372);
    binary_indexed_tree_sub(tree, 0x7fffffff, 0x372);

    number = 1;
    binary_indexed_tree_sub(tree, 1, 0x372);
    data[number - 1] -= 0x372;

    ref = binary_indexed_tree_create(data, size);
    number = size;
    while (number > 0) {
        RESULT_CHECK_sint64(tree->data[number], ref->data[number], &pass);
        number--;
    }

    memory_cache_free(data);
    binary_indexed_tree_destroy(&ref);
    binary_indexed_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_indexed_tree_sub, pass);
}

static inline void
utest_binary_indexed_tree_sum(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    uint32 number;
    struct binary_indexed_tree *tree;

    pass = true;
    size = 0x4b23;
    number = 1;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    RESULT_CHECK_sint64(TREE_SUM_INVALID,
        binary_indexed_tree_sum(NULL, number), &pass);
    RESULT_CHECK_sint64(0, binary_indexed_tree_sum(tree, TREE_NUMBER_INVALID), &pass);

    while (number <= size) {
        RESULT_CHECK_sint64(test_sint64_data_sum(data, 0, number - 1, size),
            binary_indexed_tree_sum(tree, number), &pass);
        number++;
    }

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_indexed_tree_sum, pass);
}

static inline void
utest_binary_indexed_tree_range_sum(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    uint32 number_s;
    uint32 number_e;
    struct binary_indexed_tree *tree;

    pass = true;
    size = 0x793;
    number_s = 1;
    number_e = 1;
    data = test_sint64_data_array(size);
    tree = binary_indexed_tree_create(data, size);

    RESULT_CHECK_sint64(TREE_SUM_INVALID,
        binary_indexed_tree_range_sum(NULL, number_s, number_e), &pass);
    RESULT_CHECK_sint64(TREE_SUM_INVALID,
        binary_indexed_tree_range_sum(tree, TREE_NUMBER_INVALID, number_e), &pass);
    RESULT_CHECK_sint64(TREE_SUM_INVALID,
        binary_indexed_tree_range_sum(tree, number_s, TREE_NUMBER_INVALID), &pass);

    while (number_s <= size) {
        number_e = number_s;
        while (number_e <= size) {
            RESULT_CHECK_sint64(
                test_sint64_data_sum(data, number_s - 1, number_e - 1, size),
                binary_indexed_tree_range_sum(tree, number_s, number_e),
                &pass);
            number_e++;
        }
        number_s++;
    }

    memory_cache_free(data);
    binary_indexed_tree_destroy(&tree);
    UNIT_TEST_RESULT(binary_indexed_tree_range_sum, pass);
}

