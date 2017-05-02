static inline void
ptest_avl_tree_create(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = avl_tree_create(&count, 0);
        avl_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_create);
}

static inline void
ptest_avl_tree_initial(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_initial);

    tree = avl_tree_create(&count, 0);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_initial(tree, &count, 0);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_initial);
}

static inline void
ptest_avl_tree_destroy(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = test_avl_tree_sample(0x15, 0xd);
        avl_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(avl_tree_destroy);
}

static inline void
ptest_avl_tree_find(uint32 count)
{
    sint64 nice;
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_find);

    tree = test_avl_tree_sample(0x93915, 0x7282d);
    nice = avl_tree_nice(avl_tree_find_max(tree));

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_find(tree, nice);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_find);
}

static inline void
ptest_avl_tree_find_min(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_find_min);

    tree = test_avl_tree_sample(0x93915, 0x7282d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_find_min(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_find_min);
}

static inline void
ptest_avl_tree_find_max(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_find_max);

    tree = test_avl_tree_sample(0x93915, 0x7282d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_find_max(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_find_max);
}

static inline void
ptest_avl_tree_height(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_height);

    tree = test_avl_tree_sample(0xa32, 0x12d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_height(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_height);
}

static inline void
ptest_avl_tree_contains_p(uint32 count)
{
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_contains_p);

    tree = test_avl_tree_sample(0xf2a32, 0xae12d);
    tmp = avl_tree_find_max(tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_contains_p(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_contains_p);
}

static inline void
ptest_avl_tree_insert(uint32 count)
{
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_insert);

    count = count >> 6;
    count = 0 == count ? 1000 : count;
    tree = avl_tree_create(&count, 0);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = avl_tree_create(&count, count);
        avl_tree_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_insert);
}

static inline void
ptest_avl_tree_remove(uint32 count)
{
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_remove);

    tree = test_avl_tree_sample(0xa3d3, 0x3f82);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = avl_tree_find_max(tree);
        avl_tree_remove(&tree, tmp);

        if (!tree) {
            tree = test_avl_tree_sample(0xa3d3, 0x3f82);
        }
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_remove);
}

static inline void
ptest_avl_tree_iterate(uint32 count)
{
    s_avl_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(avl_tree_iterate);

    tree = test_avl_tree_sample(0xd3, 0x82);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_iterate(tree, &tree_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_iterate);
}

static void
ptest_avl_tree_balanced_p(uint32 count)
{
    s_avl_tree_t *tree;

    tree = test_avl_tree_sample(0x2a9, 0x143);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        avl_tree_balanced_p(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    avl_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(avl_tree_balanced_p);
}

