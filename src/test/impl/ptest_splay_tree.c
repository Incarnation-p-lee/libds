static inline void
ptest_splay_tree_create(uint32 count)
{
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_create);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = splay_tree_create(&count, 0);
        splay_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(splay_tree_create);
}

static inline void
ptest_splay_tree_initial(uint32 count)
{
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_initial);

    tree = splay_tree_create(&count, 0);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_initial(tree, &count, 0);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(splay_tree_initial);
}

static inline void
ptest_splay_tree_destroy(uint32 count)
{
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_destroy);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tree = test_splay_tree_sample(0x15, 0xd);
        splay_tree_destroy(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(splay_tree_destroy);
}

static inline void
ptest_splay_tree_height(uint32 count)
{
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_height);

    tree = test_splay_tree_sample(0xa32, 0x12d);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_height(tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_height);
}

static inline void
ptest_splay_tree_contains_p(uint32 count)
{
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_contains_p);

    tree = test_splay_tree_sample(0xf2a32, 0xae12d);
    tmp = splay_tree_find_max(&tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_contains_p(tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_contains_p);
}

static inline void
ptest_splay_tree_insert(uint32 count)
{
    s_splay_tree_t *tmp;
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_insert);

    count = count >> 6;
    count = 0 == count ? 1000 : count;
    tree = splay_tree_create(&count, 0);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_create(&count, count);
        splay_tree_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_insert);
}

static inline void
ptest_splay_tree_iterate(uint32 count)
{
    s_splay_tree_t *tree;

    PERFORMANCE_TEST_BEGIN(splay_tree_iterate);

    tree = test_splay_tree_sample(0xd3, 0x82);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_iterate(tree, &tree_iterate_handler);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_iterate);
}


static void
ptest_splay_tree_find(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x21352, 0x12de2);
    tmp = splay_tree_find_max(&tree);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find(&tree, splay_tree_nice(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find);
}

static void
ptest_splay_tree_find_min(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find_min(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find_min);
}

static void
ptest_splay_tree_find_max(uint32 count)
{
    struct splay_tree *tree;

    tree = test_splay_tree_sample(0x51352, 0x42de2);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        splay_tree_find_max(&tree);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_find_max);
}

static void
ptest_splay_tree_remove(uint32 count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;

    tree = test_splay_tree_sample(0x4234, 0x2823);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = splay_tree_find_max(&tree);
        splay_tree_remove(&tree, tmp);
        splay_tree_destroy(&tmp);

        tmp = splay_tree_create(&tmp, count);
        splay_tree_insert(&tree, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    splay_tree_destroy(&tree);
    PERFORMANCE_TEST_RESULT(splay_tree_remove);
}

