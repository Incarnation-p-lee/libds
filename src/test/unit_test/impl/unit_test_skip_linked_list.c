static inline struct skip_linked_list *
unit_test_skip_linked_list_sample(uint32 range, uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;
    uint32 i;

    assert(0 != range);
    assert(0 != count);

    list = skip_linked_list_create();
    skip_linked_list_node_initial(list, list, 0);

    i = 1;
    while (i < count) {
        key = (sint32)(rand() % range) - (sint32)range / 2;
        if (!skip_linked_list_node_find_key(list, key)) {
            tmp = skip_linked_list_node_create(NULL, key);
            skip_linked_list_node_val_set(tmp, tmp);
            skip_linked_list_node_insert(&list, tmp);
        }
        i++;
    }

    return list;
}

static void
unit_test_skip_linked_list_struct_field(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xa234567u;
    pass = true;
    key = 0xfade;
    list = skip_linked_list_create();

    while (loop--) {
        skip_linked_list_node_key_set(list, key);
        RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);

        skip_linked_list_node_val_set(list, &pass);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);

        skip_linked_list_node_next_set(list, NULL);
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_next(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_struct_field), pass);
    return;
}

static void
unit_test_skip_linked_list_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567;
    pass = true;

    while (loop--) {
        list = skip_linked_list_create();
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);
        skip_linked_list_destroy(&list);
    }

    test_result_print(SYM_2_STR(skip_linked_list_create), pass);
    return;
}

static void
unit_test_skip_linked_list_initial(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf234567;
    pass = true;
    list = NULL;
    skip_linked_list_initial(list);

    list = skip_linked_list_create();
    while (loop--) {
        skip_linked_list_initial(list);
        RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_initial), pass);
    return;
}

static void
unit_test_skip_linked_list_node_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x3234567;
    pass = true;
    key = -1;

    while (loop--) {
        list = skip_linked_list_node_create(&pass, key);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);
        skip_linked_list_destroy(&list);
    }

    test_result_print(SYM_2_STR(skip_linked_list_node_create), pass);
    return;
}

static void
unit_test_skip_linked_list_node_initial(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xf234567;
    pass = true;
    list = NULL;
    skip_linked_list_node_initial(list, &pass, 1);

    list = skip_linked_list_create();
    while (loop--) {
        skip_linked_list_node_initial(list, &pass, (sint32)loop);
        RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
        RESULT_CHECK_sint32(loop, skip_linked_list_node_key(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_initial), pass);
    return;
}

static void
unit_test_skip_linked_list_destroy(void)
{
    struct skip_linked_list *list;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12;
    pass = true;
    list = NULL;

    skip_linked_list_destroy(&list);

    while (loop--) {
        list = unit_test_skip_linked_list_sample(0x6245, 0x3034);
        skip_linked_list_destroy(&list);
        RESULT_CHECK_pointer(NULL, list, &pass);
    }

    test_result_print(SYM_2_STR(skip_linked_list_destroy), pass);
    return;
}

static void
unit_test_skip_linked_list_length(void)
{
    struct skip_linked_list *list;
    register struct skip_linked_list *iter;
    bool pass;
    uint32 loop;
    uint32 len;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xa234;
    pass = true;
    list = NULL;

    RESULT_CHECK_uint32(0, skip_linked_list_length(list), &pass);
    list = unit_test_skip_linked_list_sample(0x6245, 0x3034);

    len = 0;
    iter = list;
    while (iter) {
        len++;
        iter = skip_linked_list_node_next(iter);
    }

    while (loop--) {
        RESULT_CHECK_uint32(len, skip_linked_list_length(list), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_length), pass);
    return;
}

static void
unit_test_skip_linked_list_node_find_key(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x32345;
    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_find_key(list, key), &pass);
    list = unit_test_skip_linked_list_sample(0xedbf, 0x303f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_find_key(list, key), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_node_create(&pass, key);
    skip_linked_list_node_insert(&list, tmp);

    while (loop--) {
        RESULT_CHECK_pointer(tmp, skip_linked_list_node_find_key(list, key), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_find_key), pass);
    return;
}

static void
unit_test_skip_linked_list_contains_p(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0xfff;
    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, NULL), &pass);
    list = unit_test_skip_linked_list_sample(0xedbf, 0x303f);
    tmp = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, tmp), &pass);
    skip_linked_list_destroy(&tmp);

    key = 0xfff;
    while (loop--) {
        tmp = skip_linked_list_node_find_key(list, key--);
        if (tmp) {
            RESULT_CHECK_bool(true, skip_linked_list_contains_p(list, tmp), &pass);
        }
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_contains_p), pass);
    return;
}

static void
unit_test_skip_linked_list_node_insert(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;
    sint32 key;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x123;
    pass = true;
    list = NULL;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_insert(&list, NULL), &pass);
    list = unit_test_skip_linked_list_sample(0x101f0, 0x403f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_insert(&list, NULL), &pass);

    key = 0x1ffff;
    while (key--) {
        if (NULL != skip_linked_list_node_find_key(list, key)) {
            break;
        }
    }

    tmp = skip_linked_list_node_find_key(list, key);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_insert(&list, tmp), &pass);

    tmp = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_insert(&list, tmp), &pass);
    skip_linked_list_destroy(&tmp);

    key = 0x1ffff;
    while (loop--) {
        tmp = skip_linked_list_node_create(&pass, key++);
        RESULT_CHECK_pointer(tmp, skip_linked_list_node_insert(&list, tmp), &pass);
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_insert), pass);
    return;
}

static void
unit_test_skip_linked_list_node_by_index(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tgt;
    bool pass;
    uint32 loop;
    uint32 tmp;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x0;
    pass = true;
    list = NULL;
    tmp = 0u;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_by_index(list, tmp), &pass);
    list = unit_test_skip_linked_list_sample(0x101f0, 0x403f);
    tmp = skip_linked_list_length(list);
    RESULT_CHECK_pointer(list, skip_linked_list_node_by_index(list, tmp), &pass);

    tgt = list;
    while (loop < tmp) {
        RESULT_CHECK_pointer(tgt, skip_linked_list_node_by_index(list, loop), &pass);
        tgt = skip_linked_list_node_next(tgt);
        loop++;
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_by_index), pass);
    return;
}

static void
unit_test_skip_linked_list_node_remove(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12;
    pass = true;
    list = NULL;
    tmp = NULL;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_remove(&list, 0), &pass);
    list = unit_test_skip_linked_list_sample(0x151f0, 0x803f);

    tmp = list;
    RESULT_CHECK_pointer(tmp, skip_linked_list_node_remove(&list, list->key), &pass);
    skip_linked_list_destroy(&tmp);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_remove(&list, 0x151f1), &pass);

    while (loop--) {
        tmp = skip_linked_list_node_find_key(list, loop);
        if (NULL != tmp) {
            RESULT_CHECK_pointer(tmp, skip_linked_list_node_remove(&list, tmp->key), &pass);
            skip_linked_list_destroy(&tmp);
        }
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_remove), pass);
    return;
}

static void
unit_test_skip_linked_list_node_remove_and_destroy(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x12;
    pass = true;
    list = NULL;
    tmp = NULL;

    skip_linked_list_node_remove_and_destroy(&list, 0);
    list = unit_test_skip_linked_list_sample(0x151f0, 0x803f);

    tmp = list;
    skip_linked_list_node_remove_and_destroy(&list, list->key);
    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, tmp), &pass);
    skip_linked_list_node_remove_and_destroy(&list, 0x151f1);

    while (loop--) {
        tmp = skip_linked_list_node_find_key(list, loop);
        if (NULL != tmp) {
            skip_linked_list_node_remove_and_destroy(&list, tmp->key);
            RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, tmp), &pass);
        }
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_node_remove_and_destroy), pass);
    return;
}

static void
unit_test_skip_linked_list_iterate(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *iter;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x5234;
    pass = true;
    list = NULL;

    skip_linked_list_iterate(list, &linked_list_iterate_handler);
    list = unit_test_skip_linked_list_sample(0x101f0, 0x403f);

    while (loop--) {
        iter = list;
        skip_linked_list_iterate(list, &linked_list_iterate_handler);
        while (iter) {
            RESULT_CHECK_sint32(0xdead, skip_linked_list_node_key(iter), &pass);
            iter = skip_linked_list_node_next(iter);
        }
    }
    skip_linked_list_destroy(&list);

    test_result_print(SYM_2_STR(skip_linked_list_iterate), pass);
    return;
}

static void
unit_test_skip_linked_list_merge(void)
{
    struct skip_linked_list *lm;
    struct skip_linked_list *ln;
    struct skip_linked_list *iter;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 loop;

    TEST_PERFORMANCE_CHECKPOINT;

    loop = 0x123;
    pass = true;
    lm = NULL;

    ln = unit_test_skip_linked_list_sample(0x7f1f0, 0x803f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_merge(lm, lm), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(lm, ln), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(ln, ln), &pass);

    while (loop--) {
        lm = skip_linked_list_node_create(NULL, 0x8e290 - loop);
        ln = skip_linked_list_merge(ln, lm);
        iter = lm;

        while (iter) {
            tmp = skip_linked_list_node_find_key(ln, iter->key);
            RESULT_CHECK_sint32(tmp->key, iter->key, &pass);
            iter = skip_linked_list_node_next(iter);
        }
        skip_linked_list_destroy(&lm);
    }
    skip_linked_list_destroy(&ln);

    test_result_print(SYM_2_STR(skip_linked_list_merge), pass);
    return;
}

