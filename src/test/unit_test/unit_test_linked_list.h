#ifndef HAVE_UNIT_TEST_LINKED_LIST_H
#define HAVE_UNIT_TEST_LINKED_LIST_H

#define UT_LINKED_LIST_create(name)                                 \
static void                                                         \
utest_##name##_linked_list_create(void)                             \
{                                                                   \
    bool pass;                                                      \
    struct LINKED_LIST *list;                                       \
                                                                    \
    pass = true;                                                    \
    list = LINKED_LIST_create();                                    \
    UNIT_TEST_BEGIN(name##_linked_list_create);                     \
                                                                    \
    RESULT_CHECK_bool(true, TEST_LINKED_LIST_legal_p(list), &pass); \
                                                                    \
    LINKED_LIST_destroy(&list);                                     \
    UNIT_TEST_RESULT(name##_linked_list_create, pass);              \
}

#define UT_LINKED_LIST_initial(name)                                \
static void                                                         \
utest_##name##_linked_list_initial(void)                            \
{                                                                   \
    bool pass;                                                      \
    struct LINKED_LIST *list;                                       \
                                                                    \
    pass = true;                                                    \
    list = memory_cache_allocate(sizeof(*list));                    \
    UNIT_TEST_BEGIN(name##_linked_list_initial);                    \
                                                                    \
    LINKED_LIST_initial(list);                                      \
    RESULT_CHECK_bool(true, TEST_LINKED_LIST_legal_p(list), &pass); \
                                                                    \
    LINKED_LIST_destroy(&list);                                     \
    UNIT_TEST_RESULT(name##_linked_list_initial, pass);             \
}

#define UT_LINKED_LIST_previous(name)                                     \
static void                                                               \
utest_##name##_linked_list_previous(void)                                 \
{                                                                         \
    bool pass;                                                            \
    struct LINKED_LIST *list;                                             \
    struct LINKED_LIST *prev;                                             \
                                                                          \
    pass = true;                                                          \
    UNIT_TEST_BEGIN(name##_linked_list_previous);                         \
                                                                          \
    RESULT_CHECK_pointer(PTR_INVALID, LINKED_LIST_previous(NULL), &pass); \
                                                                          \
    list = TEST_LINKED_LIST_sample(0x3f26, 0x1f19);                       \
    prev = LINKED_LIST_previous(list);                                    \
                                                                          \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(prev), &pass);            \
                                                                          \
    LINKED_LIST_destroy(&list);                                           \
    UNIT_TEST_RESULT(name##_linked_list_previous, pass);                  \
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
    UNIT_TEST_BEGIN(name##_linked_list_insert_after);                  \
                                                                       \
    LINKED_LIST_insert_after(NULL, NULL);                              \
    LINKED_LIST_insert_after(list, list);                              \
                                                                       \
    inserted = LINKED_LIST_create();                                   \
    next = LINKED_LIST_next(list);                                     \
    LINKED_LIST_insert_after(list, inserted);                          \
                                                                       \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(next), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(list), &pass);     \
    RESULT_CHECK_pointer(next, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_previous(inserted), &pass); \
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
    UNIT_TEST_BEGIN(name##_linked_list_insert_before);                 \
                                                                       \
    LINKED_LIST_insert_before(NULL, NULL);                             \
    LINKED_LIST_insert_before(list, list);                             \
                                                                       \
    inserted = LINKED_LIST_create();                                   \
    prev = LINKED_LIST_previous(list);                                 \
    LINKED_LIST_insert_before(list, inserted);                         \
                                                                       \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_previous(list), &pass); \
    RESULT_CHECK_pointer(inserted, LINKED_LIST_next(prev), &pass);     \
    RESULT_CHECK_pointer(list, LINKED_LIST_next(inserted), &pass);     \
    RESULT_CHECK_pointer(prev, LINKED_LIST_previous(inserted), &pass); \
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
    struct LINKED_LIST *list;                           \
    uint32 sizes[] = {1, 10, 100, 1000, 10000,};        \
                                                        \
    iter = sizes;                                       \
    pass = true;                                        \
    list = NULL;                                        \
    UNIT_TEST_BEGIN(name##_linked_list_destroy);        \
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

#define UT_LINKED_LIST_length(name)                             \
static void                                                     \
utest_##name##_linked_list_length(void)                         \
{                                                               \
    bool pass;                                                  \
    uint32 len;                                                 \
    struct LINKED_LIST *list;                                   \
                                                                \
    pass = true;                                                \
    len = LIST_SIZE_INVALID;                                    \
    UNIT_TEST_BEGIN(name##_linked_list_length);                 \
                                                                \
    RESULT_CHECK_uint32(len, LINKED_LIST_length(NULL), &pass);  \
                                                                \
    len = 0x2e2c;                                               \
    list = TEST_LINKED_LIST_sample(0x2e8, len);                 \
    RESULT_CHECK_uint32(len, LINKED_LIST_length(list), &pass);  \
    LINKED_LIST_destroy(&list);                                 \
                                                                \
    list = LINKED_LIST_create();                                \
    RESULT_CHECK_uint32(0x1u, LINKED_LIST_length(list), &pass); \
    LINKED_LIST_destroy(&list);                                 \
                                                                \
    UNIT_TEST_RESULT(name##_linked_list_length, pass);          \
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
    pass = true;                                              \
    UNIT_TEST_BEGIN(name##_linked_list_node_by_index);        \
                                                              \
    list = TEST_LINKED_LIST_sample(0x8fa, 0x3a2);             \
    len = LINKED_LIST_length(list);                           \
                                                              \
    tmp = LINKED_LIST_node_by_index(NULL, 0);                 \
    RESULT_CHECK_pointer(PTR_INVALID, tmp, &pass);            \
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
    UNIT_TEST_BEGIN(name##_linked_list_contains_p);                     \
                                                                        \
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

#define UT_LINKED_LIST_node_copy(name)                                     \
static void                                                                \
utest_##name##_linked_list_node_copy(void)                                 \
{                                                                          \
    bool pass;                                                             \
    struct LINKED_LIST *list;                                              \
    struct LINKED_LIST *tmp;                                               \
                                                                           \
    pass = true;                                                           \
    list = LINKED_LIST_create();                                           \
    UNIT_TEST_BEGIN(name##_linked_list_node_copy);                         \
                                                                           \
    RESULT_CHECK_pointer(PTR_INVALID, LINKED_LIST_node_copy(NULL), &pass); \
    tmp = LINKED_LIST_node_copy(list);                                     \
                                                                           \
    RESULT_CHECK_LINKED_LIST_node(tmp, list, &pass);                       \
    LINKED_LIST_next_set(tmp, tmp);                                        \
    LINKED_LIST_previous_set(tmp, tmp);                                    \
                                                                           \
    LINKED_LIST_destroy(&list);                                            \
    LINKED_LIST_destroy(&tmp);                                             \
    UNIT_TEST_RESULT(name##_linked_list_node_copy, pass);                  \
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
    UNIT_TEST_BEGIN(name##_linked_list_remove);                  \
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

#define UT_LINKED_LIST_iterate(name)                              \
static void                                                       \
utest_##name##_linked_list_iterate(void)                          \
{                                                                 \
    bool pass;                                                    \
    uint32 length;                                                \
    struct LINKED_LIST *list;                                     \
                                                                  \
    pass = true;                                                  \
    UNIT_TEST_BEGIN(name##_linked_list_iterate);                  \
    list = TEST_LINKED_LIST_sample(0x1F2, 0x381);                 \
    length = LINKED_LIST_length(list);                            \
                                                                  \
    LINKED_LIST_iterate(NULL, &linked_list_iterate_handler);      \
                                                                  \
    test_iterate_reference_clean();                               \
    LINKED_LIST_iterate(list, &linked_list_iterate_handler);      \
    RESULT_CHECK_uint32(test_iterate_reference(), length, &pass); \
                                                                  \
    LINKED_LIST_destroy(&list);                                   \
    UNIT_TEST_RESULT(name##_linked_list_iterate, pass);           \
}

#define UT_LINKED_LIST_merge(name)                                            \
static void                                                                   \
utest_##name##_linked_list_merge(void)                                        \
{                                                                             \
    bool pass;                                                                \
    uint32 length;                                                            \
    struct LINKED_LIST *list_m;                                               \
    struct LINKED_LIST *list_n;                                               \
    struct LINKED_LIST *list;                                                 \
                                                                              \
    pass = true;                                                              \
    UNIT_TEST_BEGIN(name##_linked_list_merge);                                \
    list_m = TEST_LINKED_LIST_sample(0x1F2, 0x381);                           \
    list_n = TEST_LINKED_LIST_sample(0x231, 0x4e2);                           \
                                                                              \
    RESULT_CHECK_pointer(PTR_INVALID, LINKED_LIST_merge(NULL, NULL), &pass);  \
    RESULT_CHECK_pointer(list_m, LINKED_LIST_merge(list_m, NULL), &pass);     \
    RESULT_CHECK_pointer(list_m, LINKED_LIST_merge(NULL, list_m), &pass);     \
                                                                              \
    length = LINKED_LIST_length(list_m) + LINKED_LIST_length(list_n);         \
    list_m = LINKED_LIST_merge(list_m, list_n);                               \
    RESULT_CHECK_uint32(length, LINKED_LIST_length(list_m), &pass);           \
                                                                              \
    list = list_n;                                                            \
    do {                                                                      \
        RESULT_CHECK_bool(true, LINKED_LIST_contains_p(list_m, list), &pass); \
        list = list->next;                                                    \
    } while (list != list_n);                                                 \
                                                                              \
    LINKED_LIST_destroy(&list_m);                                             \
    UNIT_TEST_RESULT(name##_linked_list_merge, pass);                         \
}

#endif

