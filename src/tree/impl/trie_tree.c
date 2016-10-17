s_trie_tree_t *
trie_tree_create(void)
{
    return trie_tree_node_create(TRIE_TREE_ROOT);
}

static inline s_trie_tree_t *
trie_tree_node_create(uint32 val)
{
    s_trie_tree_t *trie;

    trie = dp_malloc(sizeof(*trie));
    trie->sub_queue = array_queue_create();

    trie->val = val;
    trie->is_terminal = false;

    return trie;
}

void
trie_tree_destroy(s_trie_tree_t **trie)
{
    if (complain_null_pointer_p(trie)) {
        return;
    } else if (trie_tree_structure_legal_ip(*trie)) {
        array_queue_destroy(&(*trie)->sub_queue);
        dp_free(*trie);

        *trie = NULL;
    }
}

bool
trie_tree_structure_legal_p(s_trie_tree_t *trie)
{
    return trie_tree_structure_legal_ip(trie);
}

static inline bool
trie_tree_structure_legal_ip(s_trie_tree_t *trie)
{
    if (complain_null_pointer_p(trie)) {
        return false;
    } else {
        return array_queue_structure_legal_p(trie->sub_queue);
    }
}

static inline bool
trie_tree_root_node_p(s_trie_tree_t *trie)
{
    assert_exit(trie_tree_structure_legal_ip(trie));

    return trie->val == TRIE_TREE_ROOT ? true : false;
}

static inline s_trie_tree_t *
trie_tree_insert_sub_node(s_trie_tree_t *trie, uint32 val)
{
    s_trie_tree_t *sub_node;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    sub_node = trie_tree_sub_queue_find(trie, val);

    if (sub_node == NULL) {
        sub_node = trie_tree_node_create(val);
        array_queue_enter(trie->sub_queue, sub_node);
    }

    return sub_node;
}

static inline void
trie_tree_insert_i(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    uint32 *seq;
    s_trie_tree_t *trie_node;

    assert_exit(!complain_zero_size_p(len));
    assert_exit(trie_tree_root_node_p(trie));
    assert_exit(trie_tree_structure_legal_p(trie));
    assert_exit(!complain_null_pointer_p(sequence));

    seq = sequence;
    trie_node = trie;

    while (seq < sequence + len) {
        trie_node = trie_tree_insert_sub_node(trie_node, *seq);
        assert_exit(trie_node->val == *seq);
        seq++;
    }

    trie_node->is_terminal = true;
}

void
trie_tree_insert_uint32(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    if (!trie_tree_structure_legal_ip(trie)) {
        return;
    } else if (!trie_tree_root_node_p(trie)) {
        return;
    } else if (complain_zero_size_p(len)) {
        return;
    } else if (complain_null_pointer_p(sequence)) {
        return;
    } else {
        trie_tree_insert_i(trie, sequence, len);
    }
}

/*
 * will return len
 */
static inline uint32 *
trie_tree_string_to_uint32_array(char *string, uint32 *len)
{
    uint32 i, string_len;
    uint32 *translated;

    assert_exit(string);

    string_len = dp_strlen(string);
    translated = dp_malloc(sizeof(*translated) * string_len);

    i = 0;
    while (i < string_len) {
        translated[i] = (uint32)string[i];
        i++;
    }

    *len = string_len;
    return translated;
}

void
trie_tree_insert_char(s_trie_tree_t *trie, char *string)
{
    uint32 len;
    uint32 *seq_translated;

    if (!trie_tree_structure_legal_ip(trie)) {
        return;
    } else if (!trie_tree_root_node_p(trie)) {
        return;
    } else if (complain_null_pointer_p(string)) {
        return;
    } else {
        seq_translated = trie_tree_string_to_uint32_array(string, &len);
        trie_tree_insert_i(trie, seq_translated, len);
        dp_free(seq_translated);
    }
}

static inline s_trie_tree_t *
trie_tree_sub_queue_find(s_trie_tree_t *trie, uint32 val)
{
    s_trie_tree_t *sub_node;
    s_array_queue_t *sub_queue;
    s_array_iterator_t *iterator;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    sub_queue = trie->sub_queue;
    iterator = array_queue_iterator_obtain(sub_queue);
    assert_exit(PTR_INVALID == iterator);

    iterator->fp_index_initial(sub_queue);
    while (iterator->fp_next_exist_p(sub_queue)) {
        sub_node = iterator->fp_next_obtain(sub_queue);
        if (sub_node->val == val) {
            return sub_node;
        }
    }

    return NULL;
}

bool
trie_tree_sequence_match_p(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    if (complain_null_pointer_p(sequence)) {
        return false;
    } else if (complain_zero_size_p(len)) {
        return false;
    } else if (!trie_tree_structure_legal_ip(trie)) {
        return false;
    } else {
        return trie_tree_sequence_match_ip(trie, sequence, len);
    }
}

bool
trie_tree_sequence_char_matched_p(s_trie_tree_t *trie, char *string)
{
    uint32 len;
    bool is_matched;
    uint32 *seq_translated;

    if (!trie_tree_structure_legal_ip(trie)) {
        return false;
    } else if (!trie_tree_root_node_p(trie)) {
        return false;
    } else if (complain_null_pointer_p(string)) {
        return false;
    } else {
        seq_translated = trie_tree_string_to_uint32_array(string, &len);
        is_matched = trie_tree_sequence_match_ip(trie, seq_translated, len);
        dp_free(seq_translated);

        return is_matched;
    }
}

static inline bool
trie_tree_sequence_match_ip(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    uint32 i;
    s_trie_tree_t *trie_node;

    assert_exit(!complain_zero_size_p(len));
    assert_exit(trie_tree_root_node_p(trie));
    assert_exit(trie_tree_structure_legal_p(trie));
    assert_exit(!complain_null_pointer_p(sequence));

    trie_node = trie;

    i = 0;
    while (i < len) {
        trie_node = trie_tree_sub_queue_find(trie_node, sequence[i]);
        if (trie_node == NULL) {
            return false;
        }
        i++;
    }

    return trie_node->is_terminal;
}


