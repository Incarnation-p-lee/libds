static inline void
utest_trie_tree_create(void)
{
    bool pass;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_create);

    pass = true;
    trie = trie_tree_create();

    RESULT_CHECK_uint32(TRIE_TREE_ROOT, trie->val, &pass);
    RESULT_CHECK_NOT_EQUAL_pointer(NULL, trie->sub_queue, &pass);
    RESULT_CHECK_bool(false, trie->is_terminal, &pass);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_create, pass);
}

static inline void
utest_trie_tree_destroy(void)
{
    bool pass;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_destroy);

    pass = true;

    trie = NULL;
    trie_tree_destroy(&trie);
    RESULT_CHECK_pointer(NULL, trie, &pass);

    trie = trie_tree_create();
    trie_tree_destroy(&trie);
    RESULT_CHECK_pointer(NULL, trie, &pass);

    UNIT_TEST_RESULT(utest_trie_tree_destroy, pass);
}

static inline void
utest_trie_tree_sequence_insert(void)
{
    bool pass;
    uint32 *sequence;
    uint32 len, limit;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_sequence_insert);

    pass = true;
    limit = 0xfff;
    trie = trie_tree_create();

    sequence = random_sequence_uint32_limited_obtain(1, 1);
    trie_tree_sequence_insert(NULL, NULL, 0);
    trie_tree_sequence_insert(trie, NULL, 0);
    trie_tree_sequence_insert(trie, sequence, 0);
    random_sequence_drop(sequence);

    len = 0x73b;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    // RESULT_CHECK_bool(
    random_sequence_drop(sequence);

    len = 0x124f;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    random_sequence_drop(sequence);

    len = 0x2be3;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    random_sequence_drop(sequence);

    len = 0x3a28;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    random_sequence_drop(sequence);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_sequence_insert, pass);
}

static inline void
utest_trie_tree_string_insert(void)
{
    bool pass;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_string_insert);

    pass = true;
    trie = trie_tree_create();

    trie_tree_string_insert(NULL, NULL);
    trie_tree_string_insert(trie, NULL);
    trie_tree_string_remove(trie, "");

    trie_tree_string_insert(trie, "");
    trie_tree_string_insert(trie, "asm");
    trie_tree_string_insert(trie, "auto");
    trie_tree_string_insert(trie, "break");
    trie_tree_string_insert(trie, "case");
    trie_tree_string_insert(trie, "char");
    trie_tree_string_insert(trie, "const");
    trie_tree_string_insert(trie, "continue");

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_string_insert, pass);
}

static inline void
utest_trie_tree_sequence_matched_p(void)
{
    bool pass;
    uint32 *sequence;
    uint32 len, limit;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_sequence_matched_p);

    pass = true;
    limit = 0xfff;
    trie = trie_tree_create();

    sequence = random_sequence_uint32_limited_obtain(1, 1);
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(NULL, NULL, 0), &pass);
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(trie, NULL, 0), &pass);
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(trie, sequence, 0), &pass);
    random_sequence_drop(sequence);

    len = 0x234;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    RESULT_CHECK_bool(true, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    random_sequence_drop(sequence);

    sequence = random_sequence_uint32_limited_obtain(len, limit);
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    random_sequence_drop(sequence);

    len = 0xf2de;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    RESULT_CHECK_bool(true, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    sequence[0]++;
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    random_sequence_drop(sequence);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_sequence_matched_p, pass);
}

static inline void
utest_trie_tree_string_matched_p(void)
{
    bool pass;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_string_matched_p);

    pass = true;
    trie = trie_tree_create();

    RESULT_CHECK_bool(false, trie_tree_string_matched_p(NULL, NULL), &pass);
    RESULT_CHECK_bool(false, trie_tree_string_matched_p(trie, NULL), &pass);

    trie_tree_string_insert(trie, "asm");
    trie_tree_string_insert(trie, "auto");
    trie_tree_string_insert(trie, "break");
    trie_tree_string_insert(trie, "case");
    trie_tree_string_insert(trie, "char");
    trie_tree_string_insert(trie, "const");
    trie_tree_string_insert(trie, "continue");

    RESULT_CHECK_bool(true, trie_tree_string_matched_p(trie, "asm"), &pass);
    RESULT_CHECK_bool(false, trie_tree_string_matched_p(trie, "as"), &pass);
    RESULT_CHECK_bool(true, trie_tree_string_matched_p(trie, "case"), &pass);
    RESULT_CHECK_bool(false, trie_tree_string_matched_p(trie, ""), &pass);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_string_matched_p, pass);
}

static inline void
utest_trie_tree_sequence_remove(void)
{
    bool pass;
    uint32 *sequence;
    uint32 len, limit;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_sequence_remove);

    pass = true;
    len = 0x123;
    limit = 0xfff;

    trie = trie_tree_create();
    sequence = random_sequence_uint32_limited_obtain(len, limit);

    trie_tree_sequence_remove(NULL, NULL, 0);
    trie_tree_sequence_remove(trie, NULL, 0);
    trie_tree_sequence_remove(trie, sequence, 0);
    random_sequence_drop(sequence);

    len = 0x12de;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);
    random_sequence_drop(sequence);

    len = 0x2d83;
    sequence = random_sequence_uint32_limited_obtain(len, limit);
    trie_tree_sequence_insert(trie, sequence, len);

    RESULT_CHECK_bool(true, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    trie_tree_sequence_remove(trie, sequence, len);
    RESULT_CHECK_bool(false, trie_tree_sequence_matched_p(trie, sequence, len), &pass);
    random_sequence_drop(sequence);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_sequence_remove, pass);
}

static inline void
utest_trie_tree_string_remove(void)
{
    bool pass;
    s_trie_tree_t *trie;

    UNIT_TEST_BEGIN(utest_trie_tree_string_remove);

    pass = true;
    trie = trie_tree_create();

    trie_tree_string_remove(NULL, NULL);
    trie_tree_string_remove(trie, NULL);
    trie_tree_string_remove(trie, "");

    trie_tree_string_insert(trie, "asm");
    trie_tree_string_insert(trie, "auto");
    trie_tree_string_insert(trie, "break");
    trie_tree_string_insert(trie, "case");
    trie_tree_string_insert(trie, "char");
    trie_tree_string_insert(trie, "const");
    trie_tree_string_insert(trie, "continue");

    RESULT_CHECK_bool(true, trie_tree_string_matched_p(trie, "asm"), &pass);
    trie_tree_string_remove(trie, "asm");
    RESULT_CHECK_bool(false, trie_tree_string_matched_p(trie, "asm"), &pass);

    RESULT_CHECK_bool(true, trie_tree_string_matched_p(trie, "char"), &pass);
    trie_tree_string_remove(trie, "char");
    RESULT_CHECK_bool(false, trie_tree_string_matched_p(trie, "char"), &pass);

    trie_tree_destroy(&trie);
    UNIT_TEST_RESULT(utest_trie_tree_string_remove, pass);
}

