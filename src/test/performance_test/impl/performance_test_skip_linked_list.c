#define LINKED_LIST                    s_skip_linked_list_t
#define LINKED_LIST_next               skip_linked_list_next
#define LINKED_LIST_next_set           skip_linked_list_next_set
#define LINKED_LIST_previous           skip_linked_list_previous
#define TEST_LINKED_LIST_sample        test_skip_linked_list_sample

#define LINKED_LIST_create             skip_linked_list_create
#define LINKED_LIST_initial            skip_linked_list_initial
#define LINKED_LIST_destroy            skip_linked_list_destroy
#define LINKED_LIST_length             skip_linked_list_length
#define LINKED_LIST_node_by_index      skip_linked_list_node_by_index
#define LINKED_LIST_iterate            skip_linked_list_iterate
#define LINKED_LIST_merge              skip_linked_list_merge

#include "../performance_test_linked_list.h"

PT_LINKED_LIST_create(skip)
PT_LINKED_LIST_initial(skip)
PT_LINKED_LIST_destroy(skip)
PT_LINKED_LIST_length(skip)
PT_LINKED_LIST_node_by_index(skip)
PT_LINKED_LIST_iterate(skip)
PT_LINKED_LIST_merge(skip)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_previous
#undef TEST_LINKED_LIST_sample

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_destroy
#undef LINKED_LIST_length
#undef LINKED_LIST_node_by_index
#undef LINKED_LIST_iterate
#undef LINKED_LIST_merge

static void
ptest_skip_linked_list_create_with_key(uint32 count)
{
    s_skip_linked_list_t *list;

    PERFORMANCE_TEST_BEGIN(skip_linked_list_create_with_key);
    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = skip_linked_list_create_with_key(0xfadeu);
        skip_linked_list_destroy(&list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(skip_linked_list_create_with_key);
}

static void
ptest_skip_linked_list_find_key(uint32 count)
{
    sint32 key;
    s_skip_linked_list_t *list;
    s_skip_linked_list_t *tmp;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_create_with_key(key);
    skip_linked_list_insert(&list, tmp);

    PERFORMANCE_TEST_BEGIN(skip_linked_list_find_key);
    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_find_key(list, key);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_find_key);
}

static void
ptest_skip_linked_list_contains_p(uint32 count)
{
    sint32 key;
    s_skip_linked_list_t *list;
    s_skip_linked_list_t *tmp;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_create_with_key(key);

    PERFORMANCE_TEST_BEGIN(skip_linked_list_contains_p);
    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_contains_p(list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&tmp);
    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_contains_p);
}

static void
ptest_skip_linked_list_insert(uint32 count)
{
    sint32 key;
    s_skip_linked_list_t *list;
    s_skip_linked_list_t *tmp;

    key = 0xfade;
    list = test_skip_linked_list_sample(0x1, 0x1);

    PERFORMANCE_TEST_BEGIN(skip_linked_list_insert);
    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_create_with_key(key);
        skip_linked_list_insert(&list, tmp);
        skip_linked_list_remove(&list, tmp);
        skip_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_insert);
}

static void
ptest_skip_linked_list_remove(uint32 count)
{
    s_skip_linked_list_t *list;
    s_skip_linked_list_t *tmp;

    list = test_skip_linked_list_sample(0x9e12, 0x1845);

    PERFORMANCE_TEST_BEGIN(skip_linked_list_remove);
    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_remove(&list, list);
        skip_linked_list_insert(&list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_remove);
}

