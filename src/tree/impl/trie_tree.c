s_trie_tree_t *
trie_tree_create(void)
{
    return trie_tree_node_create(TRIE_TREE_SIZE_MIN, TRIE_TREE_ROOT);
}

static inline s_trie_tree_t *
trie_tree_node_create(uint32 sub_size, uint32 val)
{
    s_trie_tree_t *trie;
    uint32 sub_node_bytes;

    assert_exit(sub_size);

    trie = dp_malloc(sizeof(*trie));
    trie->val = val;
    trie->sub_size = sub_size;
    trie->is_terminal = false;

    sub_node_bytes = sizeof(trie) * sub_size;
    trie->sub_node = dp_malloc(sub_node_bytes);
    dp_memset(trie->sub_node, 0, sub_node_bytes);

    return trie;
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
    } else if (complain_zero_size_p(trie->sub_size)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
trie_tree_root_node_p(s_trie_tree_t *trie)
{
    assert_exit(trie_tree_structure_legal_ip(trie));

    return trie->val == TRIE_TREE_ROOT ? true : false;
}

static inline void
trie_tree_sub_node_expand(s_trie_tree_t *trie)
{
    uint32 sub_size;
    uint32 new_sub_size;
    s_trie_tree_t **new_sub_node;

    assert_exit(trie_tree_structure_legal_p(trie));

    sub_size = trie->sub_size;
    new_sub_size = sub_size * 2 + TRIE_TREE_SIZE_MIN;
    new_sub_node = dp_malloc(sizeof(*new_sub_node) * new_sub_size);
    dp_memset(new_sub_node, 0, sizeof(*new_sub_node) * new_sub_size);

    dp_memcpy(new_sub_node, trie->sub_node, sizeof(*new_sub_node) * sub_size);
    dp_free(trie->sub_node);

    trie->sub_node = new_sub_node;
    trie->sub_size = new_sub_size;
}

static inline s_trie_tree_t *
trie_tree_insert_sub_node(s_trie_tree_t *trie, uint32 val)
{
    uint32 index;
    s_trie_tree_t **sub_node;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    sub_node = trie->sub_node;
    index = trie_tree_sub_node_find_index(trie, val);

    if (index != TRIE_INDEX_INVALID && sub_node[index]) {
        return sub_node[index];
    } else if (index != TRIE_INDEX_INVALID && !sub_node[index]) {
        sub_node[index] = trie_tree_node_create(TRIE_TREE_SIZE_MIN, val);
        return sub_node[index];
    } else {  // Unfortunately, no space in sub_node for val
        index = trie->sub_size;
        trie_tree_sub_node_expand(trie);

        trie->sub_node[index] = trie_tree_node_create(TRIE_TREE_SIZE_MIN, val);
        return trie->sub_node[index];
    }
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

bool
trie_tree_sequence_match_p(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    return false;
}

/*
 * 1. find the index of sub node with given val.
 * 2. If no val, and not full of sub node, return the next index.
 * 3. Or return TRIE_INDEX_INVALID.
 */
static inline uint32
trie_tree_sub_node_find_index(s_trie_tree_t *trie, uint32 val)
{
    uint32 index;
    uint32 sub_size;
    s_trie_tree_t **sub_node;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    index = 0;
    sub_node = trie->sub_node;
    sub_size = trie->sub_size;

    while (index < sub_size) {
        if (sub_node[index]->val == val) {
            return index;
        }
        if (!sub_node[index]) {
            return index;
        }

        index++;
    }

    return TRIE_INDEX_INVALID;
}

static inline s_trie_tree_t *
trie_tree_sub_node_find(s_trie_tree_t *trie, uint32 val)
{
    uint32 index;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    index = trie_tree_sub_node_find_index(trie, val);
    if (index == TRIE_INDEX_INVALID) {
        return NULL;
    } else {
        /* May return NULL here */
        return trie->sub_node[index];
    }
}

static inline bool
trie_tree_sequence_match_ip(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    return false;
    // s_trie_tree_t *trie_node;

    // assert_exit(!complain_zero_size_p(len));
    // assert_exit(trie_tree_root_node_p(trie));
    // assert_exit(trie_tree_structure_legal_p(trie));
    // assert_exit(!complain_null_pointer_p(sequence));

    // i = 0;

    // while (sub_node < trie->sub_node + sub_size && *sub_node) {
    //     if (
    // }

}


