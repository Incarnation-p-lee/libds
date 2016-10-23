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
    trie->is_deleted = trie->is_terminal = false;

    return trie;
}

static inline void
trie_tree_node_destroy(s_trie_tree_t *trie)
{
    assert_exit(trie_tree_structure_legal_ip(trie));

    array_queue_destroy(&trie->sub_queue);
    dp_free(trie);
}

void
trie_tree_destroy(s_trie_tree_t **trie)
{
    s_trie_tree_t *trie_node;
    s_array_queue_t *sub_queue, *queue;

    if (complain_null_pointer_p(trie)) {
        return;
    } else if (trie_tree_structure_legal_ip(*trie)) {
        trie_node = *trie;
        queue = array_queue_create();
        array_queue_enter(queue, trie_node);

        while (!array_queue_empty_p(queue)) {
            trie_node = array_queue_leave(queue);
            sub_queue = trie_node->sub_queue;

            while (!array_queue_empty_p(sub_queue)) {
                array_queue_enter(queue, array_queue_leave(sub_queue));
            }

            trie_tree_node_destroy(trie_node);
        }

        array_queue_destroy(&queue);
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
trie_tree_scalar_insert(s_trie_tree_t *trie, uint32 val)
{
    s_trie_tree_t *trie_node;

    assert_exit(val != TRIE_TREE_ROOT);
    assert_exit(trie_tree_structure_legal_p(trie));

    trie_node = trie_tree_sub_queue_find(trie, val);

    if (trie_node == NULL) {
        trie_node = trie_tree_node_create(val);
        array_queue_enter(trie->sub_queue, trie_node);
    }

    return trie_node;
}

static inline void
trie_tree_sequence_insert_i(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
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
        trie_node = trie_tree_scalar_insert(trie_node, *seq);
        assert_exit(trie_node->val == *seq);
        seq++;
    }

    trie_node->is_terminal = true;
}

void
trie_tree_sequence_insert(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
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
        trie_tree_sequence_insert_i(trie, sequence, len);
    }
}

void
trie_tree_string_insert(s_trie_tree_t *trie, char *string)
{
    uint32 len;
    uint32 *sequence;

    if (!trie_tree_structure_legal_ip(trie)) {
        return;
    } else if (!trie_tree_root_node_p(trie)) {
        return;
    } else if (complain_null_string_p(string)) {
        return;
    } else {
        sequence = convert_string_to_uint32_array(string, &len);
        assert_exit(sequence != PTR_INVALID);

        trie_tree_sequence_insert_i(trie, sequence, len);
        dp_free(sequence);
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
    assert_exit(iterator != PTR_INVALID);

    iterator->fp_index_initial(sub_queue);
    while (iterator->fp_next_exist_p(sub_queue)) {
        sub_node = iterator->fp_next_obtain(sub_queue);

        if (sub_node->val == val && !sub_node->is_deleted) {
            return sub_node;
        }
    }

    return NULL;
}

bool
trie_tree_sequence_matched_p(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    if (complain_null_pointer_p(sequence)) {
        return false;
    } else if (complain_zero_size_p(len)) {
        return false;
    } else if (!trie_tree_structure_legal_ip(trie)) {
        return false;
    } else {
        return trie_tree_sequence_matched_ip(trie, sequence, len);
    }
}

bool
trie_tree_string_matched_p(s_trie_tree_t *trie, char *string)
{
    uint32 len;
    bool is_matched;
    uint32 *sequence;

    if (!trie_tree_structure_legal_ip(trie)) {
        return false;
    } else if (!trie_tree_root_node_p(trie)) {
        return false;
    } else if (complain_null_pointer_p(string)) {
        return false;
    } else if (complain_null_string_p(string)) {
        return false;
    } else {
        sequence = convert_string_to_uint32_array(string, &len);
        assert_exit(sequence != PTR_INVALID);

        is_matched = trie_tree_sequence_matched_ip(trie, sequence, len);
        dp_free(sequence);

        return is_matched;
    }
}

static inline bool
trie_tree_sub_queue_empty_p(s_trie_tree_t *trie)
{
    s_trie_tree_t *trie_node;
    s_array_queue_t *sub_queue;
    s_array_iterator_t *iterator;

    assert_exit(trie_tree_structure_legal_p(trie));

    sub_queue = trie->sub_queue;
    iterator = array_queue_iterator_obtain(sub_queue);

    iterator->fp_index_initial(sub_queue);
    while (iterator->fp_next_exist_p(sub_queue)) {
        trie_node = iterator->fp_next_obtain(sub_queue);

        if (trie_node->is_deleted == false) {
            return false;
        }
    }

    return true;
}

static inline void
trie_tree_sequence_remove_i(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
{
    uint32 *seq;
    s_array_stack_t *stack;
    s_trie_tree_t *trie_node;

    assert_exit(!complain_zero_size_p(len));
    assert_exit(trie_tree_root_node_p(trie));
    assert_exit(trie_tree_structure_legal_p(trie));
    assert_exit(!complain_null_pointer_p(sequence));

    seq = sequence;
    trie_node = trie;
    stack = array_stack_create();

    while (seq < sequence + len) {
        trie_node = trie_tree_sub_queue_find(trie_node, *seq);
        if (trie_node == NULL) {
            array_stack_destroy(&stack);
            return;
        } else {
            array_stack_push(stack, trie_node);
            seq++;
        }
    }

    while (!array_stack_empty_p(stack)) {
        trie_node = array_stack_pop(stack);
        if (trie_tree_sub_queue_empty_p(trie_node)) {
            trie_node->is_deleted = true;
        }
    }

    array_stack_destroy(&stack);
}

void
trie_tree_sequence_remove(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
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
        trie_tree_sequence_remove_i(trie, sequence, len);
    }
}

void
trie_tree_string_remove(s_trie_tree_t *trie, char *string)
{
    uint32 len;
    uint32 *sequence;

    if (!trie_tree_structure_legal_ip(trie)) {
        return;
    } else if (!trie_tree_root_node_p(trie)) {
        return;
    } else if (complain_null_string_p(string)) {
        return;
    } else {
        sequence = convert_string_to_uint32_array(string, &len);
        assert_exit(sequence != PTR_INVALID);

        trie_tree_sequence_remove_i(trie, sequence, len);
        dp_free(sequence);
    }
}

static inline bool
trie_tree_sequence_matched_ip(s_trie_tree_t *trie, uint32 *sequence, uint32 len)
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

