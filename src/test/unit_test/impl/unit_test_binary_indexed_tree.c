static inline sint64 *
utest_binary_indexed_tree_data_sample(uint32 size)
{
    uint32 i;
    sint64 *retval;

    assert(!complain_zero_size_p(size));

    i = 0;
    retval = memory_cache_allocate(sizeof(*retval) * size);

    while (i < size) {
        retval[i++] = random_sint64();
    }

    return retval;
}

static inline void
utest_binary_indexed_tree_create(void)
{
    bool pass;
    sint64 *data;
    uint32 size;
    struct binary_indexed_tree *tree;

    pass = true;
    size = 0x1234;
    data = utest_binary_indexed_tree_data_sample(size);
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
    data = utest_binary_indexed_tree_data_sample(size);
    tree = binary_indexed_tree_create(data, size);

    binary_indexed_tree_destroy(NULL);
    binary_indexed_tree_destroy(&tree);
    RESULT_CHECK_pointer(NULL, tree, &pass);

    memory_cache_free(data);
    UNIT_TEST_RESULT(binary_indexed_tree_create, pass);
}


