static inline void
ptest_trie_tree_create(uint32 count)
{
    s_trie_tree_t *trie;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(trie_tree_create);
}

static inline void
ptest_trie_tree_destroy(uint32 count)
{
    s_trie_tree_t *trie;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        trie_tree_string_insert(trie, "Assemble!");
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(trie_tree_destroy);
}

static inline void
ptest_trie_tree_sequence_insert(uint32 count)
{
    uint32 len;
    uint32 *sequence;
    s_trie_tree_t *trie;

    len = 0x21;
    count = count >> 3 == 0 ? 1000 : count >> 3;
    sequence = random_sequence_uint32_obtain(len);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        trie_tree_sequence_insert(trie, sequence, len);
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    random_sequence_drop(sequence);
    PERFORMANCE_TEST_RESULT(trie_tree_sequence_insert);
}

static inline void
ptest_trie_tree_string_insert(uint32 count)
{
    s_trie_tree_t *trie;

    count = count >> 1 == 0 ? 1000 : count >> 3;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        trie_tree_string_insert(trie, "test_trie_string_insert");
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(trie_tree_string_insert);
}

static inline void
ptest_trie_tree_sequence_matched_p(uint32 count)
{
    uint32 len;
    uint32 *sequence;
    s_trie_tree_t *trie;

    len = 0x38;
    trie = trie_tree_create();
    sequence = random_sequence_uint32_obtain(len);
    trie_tree_sequence_insert(trie, sequence, len);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie_tree_sequence_matched_p(trie, sequence, len);
    }

    PERFORMANCE_TEST_ENDPOINT;

    random_sequence_drop(sequence);
    trie_tree_destroy(&trie);
    PERFORMANCE_TEST_RESULT(trie_tree_sequence_matched_p);
}

static inline void
ptest_trie_tree_string_matched_p(uint32 count)
{
    s_trie_tree_t *trie;

    trie = trie_tree_create();
    trie_tree_string_insert(trie, "abcdefghijklmn");

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie_tree_string_matched_p(trie, "abcdefghijklnz");
    }

    PERFORMANCE_TEST_ENDPOINT;

    trie_tree_destroy(&trie);
    PERFORMANCE_TEST_RESULT(trie_tree_string_matched_p);
}

static inline void
ptest_trie_tree_sequence_remove(uint32 count)
{
    uint32 len;
    uint32 *sequence;
    s_trie_tree_t *trie;

    len = 0x21;
    count = count >> 3 == 0 ? 1000 : count >> 3;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        sequence = random_sequence_uint32_obtain(len);

        trie_tree_sequence_insert(trie, sequence, len);
        trie_tree_sequence_remove(trie, sequence, len);

        random_sequence_drop(sequence);
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(trie_tree_sequence_remove);
}

static inline void
ptest_trie_tree_string_remove(uint32 count)
{
    s_trie_tree_t *trie;

    count = count >> 1 == 0 ? 1000 : count >> 3;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        trie = trie_tree_create();
        trie_tree_string_insert(trie, "test_trie_string_insert");
        trie_tree_string_remove(trie, "test_trie_string_insert");
        trie_tree_destroy(&trie);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(trie_tree_string_remove);
}

