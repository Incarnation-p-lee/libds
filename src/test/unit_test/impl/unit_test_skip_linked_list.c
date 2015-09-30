static void
unit_test_skip_linked_list_struct_field(void)
{
    struct skip_linked_list *list;
    bool pass;
    sint32 key;

    pass = true;
    key = 0xfade;
    list = skip_linked_list_create();

    skip_linked_list_node_key_set(list, key);
    RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);

    skip_linked_list_node_val_set(list, &pass);
    RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);

    skip_linked_list_node_next_set(list, NULL);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_next(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_struct_field), pass);
}

static void
unit_test_skip_linked_list_create(void)
{
    struct skip_linked_list *list;
    bool pass;

    pass = true;

    list = skip_linked_list_create();
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
    RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_create), pass);
}

static void
unit_test_skip_linked_list_initial(void)
{
    struct skip_linked_list *list;
    bool pass;

    pass = true;
    list = NULL;
    skip_linked_list_initial(list);

    list = skip_linked_list_create();
    skip_linked_list_initial(list);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_val(list), &pass);
    RESULT_CHECK_sint32(0, skip_linked_list_node_key(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_initial), pass);
}

static void
unit_test_skip_linked_list_node_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    sint32 key;

    pass = true;
    key = -1;

    list = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
    RESULT_CHECK_sint32(key, skip_linked_list_node_key(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_create), pass);
}

static void
unit_test_skip_linked_list_node_initial(void)
{
    struct skip_linked_list *list;
    bool pass;

    pass = true;
    list = NULL;
    skip_linked_list_node_initial(list, &pass, 1);

    list = skip_linked_list_create();
    skip_linked_list_node_initial(list, &pass, (sint32)0xfade);
    RESULT_CHECK_pointer(&pass, skip_linked_list_node_val(list), &pass);
    RESULT_CHECK_sint32(0xfade, skip_linked_list_node_key(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_initial), pass);
}

static void
unit_test_skip_linked_list_destroy(void)
{
    struct skip_linked_list *list;
    bool pass;

    pass = true;
    list = NULL;

    skip_linked_list_destroy(&list);

    list = test_skip_linked_list_sample(0x6245, 0x1034);
    skip_linked_list_destroy(&list);
    RESULT_CHECK_pointer(NULL, list, &pass);

    unit_test_result_print(SYM_2_STR(skip_linked_list_destroy), pass);
}

static void
unit_test_skip_linked_list_length(void)
{
    struct skip_linked_list *list;
    register struct skip_linked_list *iter;
    bool pass;
    uint32 len;

    pass = true;
    list = NULL;

    RESULT_CHECK_uint32(0, skip_linked_list_length(list), &pass);
    list = test_skip_linked_list_sample(0x6245, 0x1034);

    len = 0;
    iter = list;
    while (iter) {
        len++;
        iter = skip_linked_list_node_next(iter);
    }
    RESULT_CHECK_uint32(len, skip_linked_list_length(list), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_length), pass);
}

static void
unit_test_skip_linked_list_node_find_key(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    sint32 key;

    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_find_key(list, key), &pass);
    list = test_skip_linked_list_sample(0xedbf, 0x103f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_find_key(list, key), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_node_create(&pass, key);
    skip_linked_list_node_insert(&list, tmp);

    RESULT_CHECK_pointer(tmp, skip_linked_list_node_find_key(list, key), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_find_key), pass);
}

static void
unit_test_skip_linked_list_key_contains_p(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    sint32 key;

    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, 0), &pass);
    list = test_skip_linked_list_sample(0xedbf, 0x103f);
    tmp = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, tmp->key), &pass);
    skip_linked_list_destroy(&tmp);

    key = 0xfff;
    tmp = skip_linked_list_node_find_key(list, key--);
    if (tmp) {
        RESULT_CHECK_bool(true, skip_linked_list_key_contains_p(list, tmp->key), &pass);
    }

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_key_contains_p), pass);
}

static void
unit_test_skip_linked_list_node_insert(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    sint32 key;

    pass = true;
    list = NULL;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_insert(&list, NULL), &pass);
    list = test_skip_linked_list_sample(0x101f0, 0x103f);
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
    tmp = skip_linked_list_node_create(&pass, key++);
    RESULT_CHECK_pointer(tmp, skip_linked_list_node_insert(&list, tmp), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_insert), pass);
}

static void
unit_test_skip_linked_list_node_by_index(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tgt;
    bool pass;
    uint32 tmp;

    pass = true;
    list = NULL;
    tmp = 0u;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_by_index(list, tmp), &pass);
    list = test_skip_linked_list_sample(0x101f0, 0x103f);
    tmp = skip_linked_list_length(list);
    RESULT_CHECK_pointer(list, skip_linked_list_node_by_index(list, tmp), &pass);

    tgt = list;
    RESULT_CHECK_pointer(tgt, skip_linked_list_node_by_index(list, 0u), &pass);

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_by_index), pass);
}

static void
unit_test_skip_linked_list_node_remove(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 count;

    pass = true;
    list = NULL;
    tmp = NULL;
    count = 0x24;

    RESULT_CHECK_pointer(NULL, skip_linked_list_node_remove(&list, 0), &pass);
    list = test_skip_linked_list_sample(0x11f0, 0x103f);

    tmp = list;
    RESULT_CHECK_pointer(tmp, skip_linked_list_node_remove(&list, list->key), &pass);
    skip_linked_list_destroy(&tmp);
    RESULT_CHECK_pointer(NULL, skip_linked_list_node_remove(&list, 0x151f1), &pass);

    while (count--) {
        tmp = skip_linked_list_node_find_key(list, count);
        if (NULL != tmp) {
            RESULT_CHECK_pointer(tmp, skip_linked_list_node_remove(&list, tmp->key), &pass);
            skip_linked_list_destroy(&tmp);
        }
    }

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_remove), pass);
}

static void
unit_test_skip_linked_list_node_remove_and_destroy(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    bool pass;
    uint32 count;

    count = 0x12;
    pass = true;
    list = NULL;
    tmp = NULL;

    skip_linked_list_node_remove_and_destroy(&list, 0);
    list = test_skip_linked_list_sample(0x15f0, 0x103f);

    tmp = list;
    skip_linked_list_node_remove_and_destroy(&list, list->key);
    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, tmp->key), &pass);
    skip_linked_list_node_remove_and_destroy(&list, 0x151f1);

    while (count--) {
        tmp = skip_linked_list_node_find_key(list, count);
        if (NULL != tmp) {
            skip_linked_list_node_remove_and_destroy(&list, tmp->key);
            RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, tmp->key), &pass);
        }
    }

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_node_remove_and_destroy), pass);
}

static void
unit_test_skip_linked_list_iterate(void)
{
    struct skip_linked_list *list;
    struct skip_linked_list *iter;
    bool pass;

    pass = true;
    list = NULL;

    skip_linked_list_iterate(list, &linked_list_iterate_handler);
    list = test_skip_linked_list_sample(0x61f0, 0x103f);

    iter = list;
    skip_linked_list_iterate(list, &linked_list_iterate_handler);
    while (iter) {
        RESULT_CHECK_sint32(0xdead, skip_linked_list_node_key(iter), &pass);
        iter = skip_linked_list_node_next(iter);
    }

    skip_linked_list_destroy(&list);
    unit_test_result_print(SYM_2_STR(skip_linked_list_iterate), pass);
}

static void
unit_test_skip_linked_list_merge(void)
{
    struct skip_linked_list *lm;
    struct skip_linked_list *ln;
    struct skip_linked_list *iter;
    struct skip_linked_list *tmp;
    bool pass;

    pass = true;
    lm = NULL;

    ln = test_skip_linked_list_sample(0x71f0, 0x103f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_merge(lm, lm), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(lm, ln), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(ln, ln), &pass);

    lm = skip_linked_list_node_create(NULL, 0x8e290 - 0x245);
    ln = skip_linked_list_merge(ln, lm);
    iter = lm;

    while (iter) {
        tmp = skip_linked_list_node_find_key(ln, iter->key);
        RESULT_CHECK_sint32(tmp->key, iter->key, &pass);
        iter = skip_linked_list_node_next(iter);
    }
    skip_linked_list_destroy(&lm);

    skip_linked_list_destroy(&ln);
    unit_test_result_print(SYM_2_STR(skip_linked_list_merge), pass);
}

