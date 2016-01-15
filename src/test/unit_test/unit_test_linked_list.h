#ifndef HAVE_UNIT_TEST_LINKED_LIST_H
#define HAVE_UNIT_TEST_LINKED_LIST_H

#define UT_LINKED_LIST_create(name)                                \
static void                                                        \
utest_##name##_linked_list_create(void)                            \
{                                                                  \
    bool pass;                                                     \
    struct LINKED_LIST *list;                                      \
                                                                   \
    pass = true;                                                   \
    list = LINKED_LIST_create();                                   \
                                                                   \
    RESULT_CHECK_pointer(list,  LINKED_LIST_next(list), &pass);    \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(list), &pass); \
                                                                   \
    LINKED_LIST_destroy(&list);                                    \
    UNIT_TEST_RESULT(name##_linked_list_create, pass);             \
}

#define UT_LINKED_LIST_initial(name)                               \
static void                                                        \
utest_##name##_linked_list_initial(void)                           \
{                                                                  \
    bool pass;                                                     \
    struct LINKED_LIST *list;                                      \
                                                                   \
    pass = true;                                                   \
    list= memory_cache_allocate(sizeof(*list));                    \
                                                                   \
    LINKED_LIST_initial(list);                                     \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(list), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(list), &pass); \
                                                                   \
    LINKED_LIST_destroy(&list);                                    \
    UNIT_TEST_RESULT(name##_linked_list_initial, pass);            \
}

#define UT_LINKED_LIST_node_create(name)                           \
static void                                                        \
utest_##name##_linked_list_node_create(void)                       \
{                                                                  \
    bool pass;                                                     \
    struct LINKED_LIST *list;                                      \
                                                                   \
    pass = true;                                                   \
    list = LINKED_LIST_node_create(&list);                         \
                                                                   \
    RESULT_CHECK_pointer(&list, LINKED_LIST_val(list), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(list), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(list), &pass); \
                                                                   \
    LINKED_LIST_destroy(&list);                                    \
    UNIT_TEST_RESULT(name##_linked_list_node_create, pass);        \
}

#define UT_LINKED_LIST_previous(name)                              \
static void                                                        \
utest_##name##_linked_list_previous(void)                          \
{                                                                  \
    bool pass;                                                     \
    struct LINKED_LIST *list;                                      \
    struct LINKED_LIST *prev;                                      \
                                                                   \
    pass = true;                                                   \
    LINKED_LIST_previous(NULL);                                    \
                                                                   \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                \
    prev = LINKED_LIST_previous(list);                             \
                                                                   \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(prev), &pass);     \
                                                                   \
    LINKED_LIST_destroy(&list);                                    \
    UNIT_TEST_RESULT(name##_linked_list_previous, pass);           \
}

#define UT_LINKED_LIST_insert_ptr_after(name)                          \
static void                                                            \
utest_##name##_linked_list_insert_ptr_after(void)                      \
{                                                                      \
    bool pass;                                                         \
    struct LINKED_LIST *list;                                          \
    struct LINKED_LIST *next;                                          \
    struct LINKED_LIST *inserted;                                      \
                                                                       \
    LINKED_LIST_insert_ptr_after(NULL, NULL);                          \
                                                                       \
    pass = true;                                                       \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                    \
    LINKED_LIST_insert_ptr_after(list, list);                          \
                                                                       \
    inserted = LINKED_LIST_node_create(&pass);                         \
    next = LINKED_LIST_next(list);                                     \
    LINKED_LIST_insert_ptr_after(list, inserted);                      \
                                                                       \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(next), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(list), &pass);     \
    RESULT_CHECK_pointer(next, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(inserted), &pass); \
                                                                       \
    LINKED_LIST_destroy(&list);                                        \
    UNIT_TEST_RESULT(name##_linked_list_insert_ptr_after, pass);       \
}

#define UT_LINKED_LIST_insert_ptr_before(name)                         \
static void                                                            \
utest_##name##_linked_list_insert_ptr_before(void)                     \
{                                                                      \
    bool pass;                                                         \
    struct LINKED_LIST *list;                                          \
    struct LINKED_LIST *prev;                                          \
    struct LINKED_LIST *inserted;                                      \
                                                                       \
    LINKED_LIST_insert_ptr_before(NULL, NULL);                         \
                                                                       \
    pass = true;                                                       \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                    \
    LINKED_LIST_insert_ptr_before(list, list);                         \
                                                                       \
    inserted = LINKED_LIST_node_create(&pass);                         \
    prev = LINKED_LIST_previous(list);                                 \
    LINKED_LIST_insert_ptr_before(list, inserted);                     \
                                                                       \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(list), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(prev), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(prev, LINKED_LIST_previous(inserted), &pass); \
                                                                       \
    LINKED_LIST_destroy(&list);                                        \
    UNIT_TEST_RESULT(name##_linked_list_insert_ptr_before, pass);      \
}

#define UT_LINKED_LIST_insert_after(name)                              \
static void                                                            \
utest_##name##_linked_list_insert_after(void)                          \
{                                                                      \
    bool pass;                                                         \
    struct LINKED_LIST *list;                                          \
    struct LINKED_LIST *next;                                          \
    struct LINKED_LIST *inserted;                                      \
                                                                       \
    pass = true;                                                       \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                    \
                                                                       \
    LINKED_LIST_insert_after(NULL, &pass);                             \
    next = LINKED_LIST_next(list);                                     \
    RESULT_CHECK_pointer(next, LINKED_LIST_next(list), &pass);         \
                                                                       \
    next = LINKED_LIST_next(list);                                     \
    LINKED_LIST_insert_after(list, &pass);                             \
    inserted = LINKED_LIST_next(list);                                 \
                                                                       \
    RESULT_CHECK_pointer(next, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(inserted), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(list), &pass);     \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(next), &pass); \
    RESULT_CHECK_pointer(&pass, LINKED_LIST_val(inserted), &pass);     \
                                                                       \
    LINKED_LIST_destroy(&list);                                        \
    UNIT_TEST_RESULT(name##_linked_list_insert_after, pass);           \
}

#define UT_LINKED_LIST_insert_before(name)                             \
static void                                                            \
utest_##name##_linked_list_insert_before(void)                         \
{                                                                      \
    bool pass;                                                         \
    struct LINKED_LIST *list;                                          \
    struct LINKED_LIST *prev;                                          \
    struct LINKED_LIST *inserted;                                      \
                                                                       \
    pass = true;                                                       \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                    \
                                                                       \
    LINKED_LIST_insert_before(NULL, &pass);                            \
    prev = LINKED_LIST_previous(list);                                 \
    RESULT_CHECK_pointer(prev, LINKED_LIST_previous(list), &pass);     \
                                                                       \
    prev = LINKED_LIST_previous(list);                                 \
    LINKED_LIST_insert_before(list, &pass);                            \
    inserted = LINKED_LIST_previous(list);                             \
                                                                       \
    RESULT_CHECK_pointer(prev, LINKED_LIST_previous(inserted), &pass); \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(list), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(prev), &pass);     \
    RESULT_CHECK_pointer(&pass, LINKED_LIST_val(inserted), &pass);     \
                                                                       \
    LINKED_LIST_destroy(&list);                                        \
    UNIT_TEST_RESULT(name##_linked_list_insert_before, pass);          \
}

#define UT_LINKED_LIST_destroy(name)                    \
static void                                             \
utest_##name##_linked_list_destroy(void)                \
{                                                       \
    bool pass;                                          \
    uint32 len;                                         \
    uint32 *iter;                                       \
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};        \
    struct LINKED_LIST *list;                           \
                                                        \
    iter = sizes;                                       \
    pass = true;                                        \
    list = NULL;                                        \
                                                        \
    LINKED_LIST_destroy(&list);                         \
    RESULT_CHECK_pointer(NULL, list, &pass);            \
                                                        \
    iter = sizes;                                       \
    while (iter < sizes + array_sizeof(sizes)) {        \
        len = *iter++;                                  \
        list = TEST_LINKED_LIST_sample(0x316FA, len);   \
                                                        \
        LINKED_LIST_destroy(&list);                     \
        RESULT_CHECK_pointer(NULL, list, &pass);        \
    }                                                   \
                                                        \
    list = LINKED_LIST_create();                        \
    LINKED_LIST_destroy(&list);                         \
    RESULT_CHECK_pointer(NULL, list, &pass);            \
                                                        \
    UNIT_TEST_RESULT(name##_linked_list_destroy, pass); \
}

#define UT_LINKED_LIST_length(name)                                \
static void                                                        \
utest_##name##_linked_list_length(void)                            \
{                                                                  \
    bool pass;                                                     \
    uint32 len;                                                    \
    uint32 *iter;                                                  \
    struct LINKED_LIST *list;                                      \
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};                   \
                                                                   \
    pass = true;                                                   \
    iter = sizes;                                                  \
                                                                   \
    while (iter < sizes + array_sizeof(sizes)) {                   \
        len = *iter++;                                             \
        list = TEST_LINKED_LIST_sample(0x2e8, len);                \
        RESULT_CHECK_uint32(len, LINKED_LIST_length(list), &pass); \
        LINKED_LIST_destroy(&list);                                \
    }                                                              \
                                                                   \
    list = LINKED_LIST_create();                                   \
    RESULT_CHECK_uint32(0x1u, LINKED_LIST_length(list), &pass);    \
    LINKED_LIST_destroy(&list);                                    \
    RESULT_CHECK_uint32(0x0u, LINKED_LIST_length(NULL), &pass);    \
                                                                   \
    UNIT_TEST_RESULT(name##_linked_list_length, pass);             \
}

#define UT_LINKED_LIST_node_by_index(name)                    \
static void                                                   \
utest_##name##_linked_list_node_by_index(void)                \
{                                                             \
    bool pass;                                                \
    uint32 len;                                               \
    struct LINKED_LIST *list;                                 \
    struct LINKED_LIST *tmp;                                  \
                                                              \
    tmp = LINKED_LIST_node_by_index(NULL, 0);                 \
    RESULT_CHECK_pointer(NULL, tmp, &pass);                   \
                                                              \
    pass = true;                                              \
    list = TEST_LINKED_LIST_sample(0x8fa, 0x3a2);             \
    len = LINKED_LIST_length(list);                           \
                                                              \
    tmp = LINKED_LIST_node_by_index(list, 0);                 \
    RESULT_CHECK_pointer(list, tmp, &pass);                   \
                                                              \
    tmp = LINKED_LIST_node_by_index(list, len);               \
    RESULT_CHECK_pointer(list, tmp, &pass);                   \
    tmp = LINKED_LIST_node_by_index(list, len + 1);           \
    RESULT_CHECK_pointer(tmp, LINKED_LIST_next(list), &pass); \
                                                              \
    LINKED_LIST_destroy(&list);                               \
    UNIT_TEST_RESULT(name##_linked_list_node_by_index, pass); \
}

#define UT_LINKED_LIST_contains_p(name)                                 \
static void                                                             \
utest_##name##_linked_list_contains_p(void)                             \
{                                                                       \
    bool pass;                                                          \
    struct LINKED_LIST *tmp;                                            \
    struct LINKED_LIST *list;                                           \
                                                                        \
    pass = true;                                                        \
    list = TEST_LINKED_LIST_sample(0x1dd2, 0x28ae);                     \
    tmp = LINKED_LIST_next(list);                                       \
                                                                        \
    RESULT_CHECK_bool(false, LINKED_LIST_contains_p(NULL, tmp), &pass); \
                                                                        \
    tmp = LINKED_LIST_next(list);                                       \
    RESULT_CHECK_bool(true, LINKED_LIST_contains_p(list, tmp), &pass);  \
    tmp = LINKED_LIST_create();                                         \
    RESULT_CHECK_bool(false, LINKED_LIST_contains_p(list, tmp), &pass); \
                                                                        \
    LINKED_LIST_destroy(&tmp);                                          \
    LINKED_LIST_destroy(&list);                                         \
    UNIT_TEST_RESULT(name##_linked_list_contains_p, pass);              \
}

#define UT_LINKED_LIST_node_copy(name)                    \
static void                                               \
utest_##name##_linked_list_node_copy(void)                \
{                                                         \
    bool pass;                                            \
    struct LINKED_LIST *list;                             \
    struct LINKED_LIST *tmp;                              \
                                                          \
    pass = true;                                          \
    list = LINKED_LIST_node_create(&pass);                \
                                                          \
    LINKED_LIST_node_copy(NULL);                          \
    tmp = LINKED_LIST_node_copy(list);                    \
                                                          \
    RESULT_CHECK_LINKED_LIST_node(tmp, list, &pass);      \
    LINKED_LIST_next_set(tmp, tmp);                       \
    LINKED_LIST_previous_set(tmp, tmp);                   \
                                                          \
    LINKED_LIST_destroy(&list);                           \
    LINKED_LIST_destroy(&tmp);                            \
    UNIT_TEST_RESULT(name##_linked_list_node_copy, pass); \
}

#define UT_LINKED_LIST_remove(name)                              \
static void                                                      \
utest_##name##_linked_list_remove(void)                          \
{                                                                \
    bool pass;                                                   \
    struct LINKED_LIST *tmp;                                     \
    struct LINKED_LIST *list;                                    \
    struct LINKED_LIST *next;                                    \
                                                                 \
    LINKED_LIST_remove(NULL);                                    \
                                                                 \
    pass = true;                                                 \
    list = TEST_LINKED_LIST_sample(0x31e2, 0x28ed);              \
    tmp = list;                                                  \
    next = list->next;                                           \
                                                                 \
    RESULT_CHECK_pointer(tmp, LINKED_LIST_remove(&list), &pass); \
    RESULT_CHECK_pointer(next, list, &pass);                     \
    LINKED_LIST_destroy(&tmp);                                   \
    LINKED_LIST_destroy(&list);                                  \
                                                                 \
    list = LINKED_LIST_create();                                 \
    tmp = list;                                                  \
    RESULT_CHECK_pointer(tmp, LINKED_LIST_remove(&list), &pass); \
    RESULT_CHECK_pointer(NULL, list, &pass);                     \
                                                                 \
    LINKED_LIST_destroy(&tmp);                                   \
    UNIT_TEST_RESULT(name##_linked_list_remove, pass);           \
}

#define UT_LINKED_LIST_remove_and_destroy(name)                    \
static void                                                        \
utest_##name##_linked_list_remove_and_destroy(void)                \
{                                                                  \
    bool pass;                                                     \
    struct LINKED_LIST *list;                                      \
    struct LINKED_LIST *next;                                      \
                                                                   \
    LINKED_LIST_remove(NULL);                                      \
                                                                   \
    pass = true;                                                   \
    list = TEST_LINKED_LIST_sample(0x31e2, 0x28ed);                \
    next = list->next;                                             \
                                                                   \
    LINKED_LIST_remove_and_destroy(&list);                         \
    RESULT_CHECK_pointer(next, list, &pass);                       \
    LINKED_LIST_destroy(&list);                                    \
                                                                   \
    list = LINKED_LIST_create();                                   \
    LINKED_LIST_remove_and_destroy(&list);                         \
    RESULT_CHECK_pointer(NULL, list, &pass);                       \
                                                                   \
    UNIT_TEST_RESULT(name##_linked_list_remove_and_destroy, pass); \
}

#define UT_LINKED_LIST_iterate(name)                             \
static void                                                      \
utest_##name##_linked_list_iterate(void)                         \
{                                                                \
    bool pass;                                                   \
    uint32 refer;                                                \
    uint32 length;                                               \
    struct LINKED_LIST *tmp;                                     \
    struct LINKED_LIST *list;                                    \
                                                                 \
    refer = 0;                                                   \
    pass = true;                                                 \
    list = TEST_LINKED_LIST_sample(0x1F2, 0x381);                \
    length = LINKED_LIST_length(list);                           \
                                                                 \
    LINKED_LIST_iterate(NULL, &linked_list_iterate_handler);     \
                                                                 \
    tmp = list;                                                  \
    while (0 != length--) {                                      \
        LINKED_LIST_val_set(tmp, &refer);                        \
        tmp = LINKED_LIST_next(tmp);                             \
    }                                                            \
                                                                 \
    tmp = list;                                                  \
    LINKED_LIST_iterate(list, &linked_list_iterate_handler);     \
    RESULT_CHECK_uint32(refer, LINKED_LIST_length(list), &pass); \
                                                                 \
    LINKED_LIST_destroy(&list);                                  \
    UNIT_TEST_RESULT(name##_linked_list_iterate, pass);          \
}

#define UT_LINKED_LIST_merge(name)                                    \
static void                                                           \
utest_##name##_linked_list_merge(void)                                \
{                                                                     \
    bool pass;                                                        \
    struct LINKED_LIST *list;                                         \
    struct LINKED_LIST *list_n;                                       \
    uint32 raw[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x1};               \
                                                                      \
    pass = true;                                                      \
    list = LINKED_LIST_create();                                      \
    LINKED_LIST_val_set(list, raw);                                   \
    LINKED_LIST_insert_before(list, raw + 1);                         \
    LINKED_LIST_insert_before(list, raw + 2);                         \
                                                                      \
    list_n = LINKED_LIST_create();                                    \
    LINKED_LIST_val_set(list, raw + 3);                               \
    LINKED_LIST_insert_before(list_n, raw + 4);                       \
    LINKED_LIST_insert_before(list_n, raw + 5);                       \
                                                                      \
    RESULT_CHECK_pointer(NULL, LINKED_LIST_merge(NULL, NULL), &pass); \
    RESULT_CHECK_pointer(list, LINKED_LIST_merge(list, NULL), &pass); \
    RESULT_CHECK_pointer(list, LINKED_LIST_merge(NULL, list), &pass); \
                                                                      \
    list = LINKED_LIST_merge(list, list_n);                           \
    RESULT_CHECK_uint32(0x6u, LINKED_LIST_length(list), &pass);       \
                                                                      \
    list = LINKED_LIST_merge(list, list_n);                    \
                                                                      \
    LINKED_LIST_destroy(&list);                                       \
    LINKED_LIST_destroy(&list_n);                                     \
    UNIT_TEST_RESULT(name##_linked_list_merge, pass);                 \
}

#endif

