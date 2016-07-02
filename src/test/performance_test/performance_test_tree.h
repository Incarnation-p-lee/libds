#ifndef HAVE_DEFINED_PERFORMANCE_TEST_TREE_H
#define HAVE_DEFINED_PERFORMANCE_TEST_TREE_H

#define PT_TREE_create(name)                     \
static inline void                               \
ptest_##name##_tree_create(uint32 count)         \
{                                                \
    struct TREE *tree;                           \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        tree = TREE_create();                    \
        TREE_destroy(&tree);                     \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    PERFORMANCE_TEST_RESULT(name##_tree_create); \
}

#define PT_TREE_initial(name)                     \
static inline void                                \
ptest_##name##_tree_initial(uint32 count)         \
{                                                 \
    struct TREE *tree;                            \
                                                  \
    tree = TREE_create();                         \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        TREE_initial(tree, 0);                    \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_tree_initial); \
}

#define PT_TREE_destroy(name)                     \
static inline void                                \
ptest_##name##_tree_destroy(uint32 count)         \
{                                                 \
    struct TREE *tree;                            \
                                                  \
    PERFORMANCE_TEST_CHECKPOINT;                  \
                                                  \
    while (count--) {                             \
        tree = TEST_tree_sample(0x15, 0xd);       \
        TREE_destroy(&tree);                      \
    }                                             \
                                                  \
    PERFORMANCE_TEST_ENDPOINT;                    \
                                                  \
    PERFORMANCE_TEST_RESULT(name##_tree_destroy); \
}

#define PT_TREE_find(name)                     \
static inline void                             \
ptest_##name##_tree_find(uint32 count)         \
{                                              \
    struct TREE *tree;                         \
    sint64 nice;                               \
                                               \
    tree = TEST_tree_sample(0x93915, 0x7282d); \
    nice = TREE_nice(TREE_find_max(tree));     \
                                               \
    PERFORMANCE_TEST_CHECKPOINT;               \
                                               \
    while (count--) {                          \
        TREE_find(tree, nice);                 \
    }                                          \
                                               \
    PERFORMANCE_TEST_ENDPOINT;                 \
                                               \
    TREE_destroy(&tree);                       \
    PERFORMANCE_TEST_RESULT(name##_tree_find); \
}

#define PT_TREE_find_min(name)                     \
static inline void                                 \
ptest_##name##_tree_find_min(uint32 count)         \
{                                                  \
    struct TREE *tree;                             \
                                                   \
    tree = TEST_tree_sample(0x93915, 0x7282d);     \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        TREE_find_min(tree);                       \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    TREE_destroy(&tree);                           \
    PERFORMANCE_TEST_RESULT(name##_tree_find_min); \
}

#define PT_TREE_find_max(name)                     \
static inline void                                 \
ptest_##name##_tree_find_max(uint32 count)         \
{                                                  \
    struct TREE *tree;                             \
                                                   \
    tree = TEST_tree_sample(0x93915, 0x7282d);     \
                                                   \
    PERFORMANCE_TEST_CHECKPOINT;                   \
                                                   \
    while (count--) {                              \
        TREE_find_max(tree);                       \
    }                                              \
                                                   \
    PERFORMANCE_TEST_ENDPOINT;                     \
                                                   \
    TREE_destroy(&tree);                           \
    PERFORMANCE_TEST_RESULT(name##_tree_find_max); \
}

#define PT_TREE_height(name)                     \
static inline void                               \
ptest_##name##_tree_height(uint32 count)         \
{                                                \
    struct TREE *tree;                           \
                                                 \
    tree = TEST_tree_sample(0xa32, 0x12d);       \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        TREE_height(tree);                       \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    TREE_destroy(&tree);                         \
    PERFORMANCE_TEST_RESULT(name##_tree_height); \
}

#define PT_TREE_contains_p(name)                     \
static inline void                                   \
ptest_##name##_tree_contains_p(uint32 count)         \
{                                                    \
    struct TREE *tree;                               \
    struct TREE *tmp;                                \
                                                     \
    tree = TEST_tree_sample(0xf2a32, 0xae12d);       \
                                                     \
    tmp = tree;                                      \
    while (tmp->left) {                              \
        tmp = tmp->left;                             \
    }                                                \
                                                     \
    PERFORMANCE_TEST_CHECKPOINT;                     \
                                                     \
    while (count--) {                                \
        TREE_contains_p(tree, tmp);                  \
    }                                                \
                                                     \
    PERFORMANCE_TEST_ENDPOINT;                       \
                                                     \
    TREE_destroy(&tree);                             \
    PERFORMANCE_TEST_RESULT(name##_tree_contains_p); \
}

#define PT_TREE_insert(name)                     \
static inline void                               \
ptest_##name##_tree_insert(uint32 count)         \
{                                                \
    struct TREE *tree;                           \
    struct TREE *tmp;                            \
                                                 \
    count = count >> 6;                          \
    count = 0 == count ? 1000 : count;           \
    tree = TREE_create();                        \
                                                 \
    PERFORMANCE_TEST_CHECKPOINT;                 \
                                                 \
    while (count--) {                            \
        tmp = TREE_create();                     \
        TREE_initial(tmp, count);                \
        TREE_insert(&tree, tmp);                 \
    }                                            \
                                                 \
    PERFORMANCE_TEST_ENDPOINT;                   \
                                                 \
    TREE_destroy(&tree);                         \
    PERFORMANCE_TEST_RESULT(name##_tree_insert); \
}

#define PT_TREE_remove(name)                         \
static inline void                                   \
ptest_##name##_tree_remove(uint32 count)             \
{                                                    \
    struct TREE *tree;                               \
    struct TREE *tmp;                                \
                                                     \
    tree = TEST_tree_sample(0xa3d3, 0x3f82);         \
                                                     \
    PERFORMANCE_TEST_CHECKPOINT;                     \
                                                     \
    while (count--) {                                \
        tmp = TREE_find_max(tree);                   \
        TREE_remove(&tree, tmp);                     \
                                                     \
        if (!tree) {                                 \
            tree = TEST_tree_sample(0xa3d3, 0x3f82); \
        }                                            \
    }                                                \
                                                     \
    PERFORMANCE_TEST_ENDPOINT;                       \
                                                     \
    TREE_destroy(&tree);                             \
    PERFORMANCE_TEST_RESULT(name##_tree_remove);     \
}

#define PT_TREE_iterate(name)                                  \
static inline void                                             \
ptest_##name##_tree_iterate(uint32 count)                      \
{                                                              \
    struct TREE *tree;                                         \
                                                               \
    tree = TEST_tree_sample(0xd3, 0x82);                       \
                                                               \
    PERFORMANCE_TEST_CHECKPOINT;                               \
                                                               \
    while (count--) {                                          \
        TREE_iterate(tree, &tree_iterate_handler, ORDER_POST); \
        TREE_iterate(tree, &tree_iterate_handler, ORDER_PRE);  \
        TREE_iterate(tree, &tree_iterate_handler, ORDER_IN);   \
    }                                                          \
                                                               \
    PERFORMANCE_TEST_ENDPOINT;                                 \
                                                               \
    TREE_destroy(&tree);                                       \
    PERFORMANCE_TEST_RESULT(name##_tree_iterate);              \
}

#endif

