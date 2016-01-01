#ifndef HAVE_PERFORMANCE_TEST_LINKED_LIST_H
#define HAVE_PERFORMANCE_TEST_LINKED_LIST_H

#define PT_LINKED_LIST_create(name)                     \
static void                                             \
ptest_##name##_linked_list_create(uint32 count)         \
{                                                       \
    struct LINKED_LIST *list;                           \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    while (count--) {                                   \
        list = LINKED_LIST_create();                    \
        LINKED_LIST_destroy(&list);                     \
    }                                                   \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    PERFORMANCE_TEST_RESULT(name##_linked_list_create); \
}

#define PT_LINKED_LIST_initial(name)                     \
static void                                              \
ptest_##name##_linked_list_initial(uint32 count)         \
{                                                        \
    struct LINKED_LIST *list;                            \
                                                         \
    list = LINKED_LIST_create();                         \
                                                         \
    PERFORMANCE_TEST_CHECKPOINT;                         \
                                                         \
    while (count--) {                                    \
        LINKED_LIST_initial(list);                       \
    }                                                    \
                                                         \
    PERFORMANCE_TEST_ENDPOINT;                           \
                                                         \
    LINKED_LIST_destroy(&list);                          \
    PERFORMANCE_TEST_RESULT(name##_linked_list_initial); \
}

#define PT_LINKED_LIST_node_create(name)                     \
static void                                                  \
ptest_##name##_linked_list_node_create(uint32 count)         \
{                                                            \
    struct LINKED_LIST *list;                                \
                                                             \
    PERFORMANCE_TEST_CHECKPOINT;                             \
                                                             \
    while (count--) {                                        \
        list = LINKED_LIST_node_create(&count);              \
        LINKED_LIST_destroy(&list);                          \
    }                                                        \
                                                             \
    PERFORMANCE_TEST_ENDPOINT;                               \
                                                             \
    PERFORMANCE_TEST_RESULT(name##_linked_list_node_create); \
}

#define PT_LINKED_LIST_insert_ptr_before(name)                     \
static void                                                        \
ptest_##name##_linked_list_insert_ptr_before(uint32 count)         \
{                                                                  \
    struct LINKED_LIST *list;                                      \
    struct LINKED_LIST *tmp;                                       \
                                                                   \
    count = count >> 6;                                            \
    count = 0u == count ? 1000 : count;                            \
    list = TEST_LINKED_LIST_sample(0x722, 0x342);                  \
                                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                                   \
                                                                   \
    while (count--) {                                              \
        tmp = LINKED_LIST_create();                                \
        LINKED_LIST_insert_ptr_before(list, tmp);                  \
        LINKED_LIST_remove_and_destroy(&list);                     \
    }                                                              \
                                                                   \
    PERFORMANCE_TEST_ENDPOINT;                                     \
                                                                   \
    LINKED_LIST_destroy(&list);                                    \
    PERFORMANCE_TEST_RESULT(name##_linked_list_insert_ptr_before); \
}

#define PT_LINKED_LIST_insert_ptr_after(name)                     \
static void                                                       \
ptest_##name##_linked_list_insert_ptr_after(uint32 count)         \
{                                                                 \
    struct LINKED_LIST *list;                                     \
    struct LINKED_LIST *tmp;                                      \
                                                                  \
    count = count >> 6;                                           \
    count = 0u == count ? 1000 : count;                           \
    list = TEST_LINKED_LIST_sample(0x722, 0x342);                 \
                                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                                  \
                                                                  \
    while (count--) {                                             \
        tmp = LINKED_LIST_create();                               \
        LINKED_LIST_insert_ptr_after(list, tmp);                  \
        LINKED_LIST_remove_and_destroy(&list);                    \
    }                                                             \
                                                                  \
    PERFORMANCE_TEST_ENDPOINT;                                    \
                                                                  \
    LINKED_LIST_destroy(&list);                                   \
    PERFORMANCE_TEST_RESULT(name##_linked_list_insert_ptr_after); \
}

#define PT_LINKED_LIST_insert_before(name)                     \
static void                                                    \
ptest_##name##_linked_list_insert_before(uint32 count)         \
{                                                              \
    struct LINKED_LIST *list;                                  \
                                                               \
    count = count >> 6;                                        \
    count = 0u == count ? 1000 : count;                        \
    list = TEST_LINKED_LIST_sample(0x722, 0x342);              \
                                                               \
    PERFORMANCE_TEST_CHECKPOINT;                               \
                                                               \
    while (count--) {                                          \
        LINKED_LIST_insert_before(list, &list);                \
        LINKED_LIST_remove_and_destroy(&list);                 \
    }                                                          \
                                                               \
    PERFORMANCE_TEST_ENDPOINT;                                 \
                                                               \
    LINKED_LIST_destroy(&list);                                \
    PERFORMANCE_TEST_RESULT(name##_linked_list_insert_before); \
}

#define PT_LINKED_LIST_insert_after(name)                     \
static void                                                   \
ptest_##name##_linked_list_insert_after(uint32 count)         \
{                                                             \
    struct LINKED_LIST *list;                                 \
                                                              \
    count = count >> 6;                                       \
    count = 0u == count ? 1000 : count;                       \
    list = TEST_LINKED_LIST_sample(0x722, 0x342);             \
                                                              \
    PERFORMANCE_TEST_CHECKPOINT;                              \
                                                              \
    while (count--) {                                         \
        LINKED_LIST_insert_after(list, &list);                \
        LINKED_LIST_remove_and_destroy(&list);                \
    }                                                         \
                                                              \
    PERFORMANCE_TEST_ENDPOINT;                                \
                                                              \
    LINKED_LIST_destroy(&list);                               \
    PERFORMANCE_TEST_RESULT(name##_linked_list_insert_after); \
}

#define PT_LINKED_LIST_destroy(name)                     \
static void                                              \
ptest_##name##_linked_list_destroy(uint32 count)         \
{                                                        \
    struct LINKED_LIST *list;                            \
                                                         \
    PERFORMANCE_TEST_CHECKPOINT;                         \
                                                         \
    while (count--) {                                    \
        list = TEST_LINKED_LIST_sample(0x22, 0x9);       \
        LINKED_LIST_destroy(&list);                      \
    }                                                    \
                                                         \
    PERFORMANCE_TEST_ENDPOINT;                           \
                                                         \
    PERFORMANCE_TEST_RESULT(name##_linked_list_destroy); \
}

#define PT_LINKED_LIST_length(name)                     \
static void                                             \
ptest_##name##_linked_list_length(uint32 count)         \
{                                                       \
    struct LINKED_LIST *list;                           \
                                                        \
    list = TEST_LINKED_LIST_sample(0xe3e, 0x9a7);       \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    while (count--) {                                   \
        LINKED_LIST_length(list);                       \
    }                                                   \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    LINKED_LIST_destroy(&list);                         \
    PERFORMANCE_TEST_RESULT(name##_linked_list_length); \
}

#define PT_LINKED_LIST_node_by_index(name)                     \
static void                                                    \
ptest_##name##_linked_list_node_by_index(uint32 count)         \
{                                                              \
    struct LINKED_LIST *list;                                  \
    uint32 length;                                             \
                                                               \
    list = TEST_LINKED_LIST_sample(0xfde, 0x4af);              \
    length = LINKED_LIST_length(list);                         \
    length /= 2;                                               \
                                                               \
    PERFORMANCE_TEST_CHECKPOINT;                               \
                                                               \
    while (count--) {                                          \
        LINKED_LIST_node_by_index(list, length);               \
    }                                                          \
                                                               \
    PERFORMANCE_TEST_ENDPOINT;                                 \
                                                               \
    LINKED_LIST_destroy(&list);                                \
    PERFORMANCE_TEST_RESULT(name##_linked_list_node_by_index); \
}

#define PT_LINKED_LIST_contains_p(name)                     \
static void                                                 \
ptest_##name##_linked_list_contains_p(uint32 count)         \
{                                                           \
    struct LINKED_LIST *list;                               \
                                                            \
    list = TEST_LINKED_LIST_sample(0xfde, 0x4af);           \
    list = list;                                            \
                                                            \
    PERFORMANCE_TEST_CHECKPOINT;                            \
                                                            \
    while (count--) {                                       \
        LINKED_LIST_contains_p(list, list);                 \
        list = LINKED_LIST_next(list);                      \
    }                                                       \
                                                            \
    PERFORMANCE_TEST_ENDPOINT;                              \
                                                            \
    LINKED_LIST_destroy(&list);                             \
    PERFORMANCE_TEST_RESULT(name##_linked_list_contains_p); \
}

#define PT_LINKED_LIST_node_copy(name)                     \
static void                                                \
ptest_##name##_linked_list_node_copy(uint32 count)         \
{                                                          \
    struct LINKED_LIST *list;                              \
    struct LINKED_LIST *tmp;                               \
                                                           \
    list = LINKED_LIST_node_create(&count);                \
                                                           \
    PERFORMANCE_TEST_CHECKPOINT;                           \
                                                           \
    while (count--) {                                      \
        tmp = LINKED_LIST_node_copy(list);                 \
        LINKED_LIST_next_set(tmp, tmp);                    \
        LINKED_LIST_previous_set(tmp, tmp);                \
        LINKED_LIST_destroy(&tmp);                         \
    }                                                      \
                                                           \
    PERFORMANCE_TEST_ENDPOINT;                             \
                                                           \
    LINKED_LIST_destroy(&list);                            \
    PERFORMANCE_TEST_RESULT(name##_linked_list_node_copy); \
}

#define PT_LINKED_LIST_remove(name)                     \
static void                                             \
ptest_##name##_linked_list_remove(uint32 count)         \
{                                                       \
    struct LINKED_LIST *list;                           \
    struct LINKED_LIST *removed;                        \
                                                        \
    list = TEST_LINKED_LIST_sample(0xe0d, 0x493);       \
                                                        \
    PERFORMANCE_TEST_CHECKPOINT;                        \
                                                        \
    while (count--) {                                   \
        removed = LINKED_LIST_remove(&list);            \
        LINKED_LIST_insert_before(list, &list);         \
        LINKED_LIST_destroy(&removed);                  \
    }                                                   \
                                                        \
    PERFORMANCE_TEST_ENDPOINT;                          \
                                                        \
    LINKED_LIST_destroy(&list);                         \
    PERFORMANCE_TEST_RESULT(name##_linked_list_remove); \
}

#define PT_LINKED_LIST_remove_and_destroy(name)                     \
static void                                                         \
ptest_##name##_linked_list_remove_and_destroy(uint32 count)         \
{                                                                   \
    struct LINKED_LIST *list;                                       \
                                                                    \
    list = TEST_LINKED_LIST_sample(0xe0d, 0x493);                   \
                                                                    \
    PERFORMANCE_TEST_CHECKPOINT;                                    \
                                                                    \
    while (count--) {                                               \
        LINKED_LIST_remove_and_destroy(&list);                      \
        LINKED_LIST_insert_after(list, &list);                      \
    }                                                               \
                                                                    \
    PERFORMANCE_TEST_ENDPOINT;                                      \
                                                                    \
    LINKED_LIST_destroy(&list);                                     \
    PERFORMANCE_TEST_RESULT(name##_linked_list_remove_and_destroy); \
}

#define PT_LINKED_LIST_iterate(name)                             \
static void                                                      \
ptest_##name##_linked_list_iterate(uint32 count)                 \
{                                                                \
    uint32 refer;                                                \
    struct LINKED_LIST *tmp;                                     \
    struct LINKED_LIST *list;                                    \
                                                                 \
    list = TEST_LINKED_LIST_sample(0xe0d, 0x493);                \
    tmp = list;                                                  \
    do {                                                         \
        LINKED_LIST_val_set(tmp, &refer);                        \
        tmp = LINKED_LIST_next(tmp);                             \
    } while (tmp != list);                                       \
                                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                                 \
                                                                 \
    while (count--) {                                            \
        LINKED_LIST_iterate(list, &linked_list_iterate_handler); \
    }                                                            \
                                                                 \
    PERFORMANCE_TEST_ENDPOINT;                                   \
                                                                 \
    LINKED_LIST_destroy(&list);                                  \
    PERFORMANCE_TEST_RESULT(name##_linked_list_iterate);         \
}

#define PT_LINKED_LIST_merge(name)                     \
static void                                            \
ptest_##name##_linked_list_merge(uint32 count)         \
{                                                      \
    struct LINKED_LIST *list;                          \
    struct LINKED_LIST *head;                          \
                                                       \
    PERFORMANCE_TEST_CHECKPOINT;                       \
                                                       \
    while (count--) {                                  \
        head = TEST_LINKED_LIST_sample(0xe0d, 0xd);    \
        list = TEST_LINKED_LIST_sample(0xfe0d, 0xf);   \
        LINKED_LIST_merge(list, list);                 \
        LINKED_LIST_destroy(&head);                    \
        LINKED_LIST_destroy(&list);                    \
    }                                                  \
                                                       \
    PERFORMANCE_TEST_ENDPOINT;                         \
                                                       \
    PERFORMANCE_TEST_RESULT(name##_linked_list_merge); \
}

#endif

