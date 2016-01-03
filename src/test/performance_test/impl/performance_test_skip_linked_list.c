#include "../performance_test_linked_list.h"

#define LINKED_LIST                    skip_linked_list
#define LINKED_LIST_next               skip_linked_list_next
#define LINKED_LIST_next_set           skip_linked_list_next_set
#define LINKED_LIST_previous           skip_linked_list_previous
#define LINKED_LIST_val                skip_linked_list_val
#define LINKED_LIST_val_set            skip_linked_list_val_set

#define LINKED_LIST_create             skip_linked_list_create
#define LINKED_LIST_initial            skip_linked_list_initial
#define LINKED_LIST_destroy            skip_linked_list_destroy
#define LINKED_LIST_length             skip_linked_list_length
#define LINKED_LIST_node_by_index      skip_linked_list_node_by_index
#define LINKED_LIST_iterate            skip_linked_list_iterate

#define TEST_LINKED_LIST_sample        test_skip_linked_list_sample

PT_LINKED_LIST_create(skip)
PT_LINKED_LIST_initial(skip)
PT_LINKED_LIST_destroy(skip)
PT_LINKED_LIST_length(skip)
PT_LINKED_LIST_node_by_index(skip)
PT_LINKED_LIST_iterate(skip)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_previous
#undef LINKED_LIST_val
#undef LINKED_LIST_val_set

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_destroy
#undef LINKED_LIST_length
#undef LINKED_LIST_node_by_index
#undef LINKED_LIST_iterate

#undef TEST_LINKED_LIST_sample

static void
ptest_skip_linked_list_node_create(uint32 count)
{
    struct skip_linked_list *list;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = skip_linked_list_node_create(&count, 0xfadeu);
        skip_linked_list_destroy(&list);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(skip_linked_list_node_create);
}

static void
ptest_skip_linked_list_find_key(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_node_create(list, key);
    skip_linked_list_insert(&list, tmp);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_find_key(list, key);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_find_key);
}

static void
ptest_skip_linked_list_key_contains_p(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0xf45, 0x734);
    tmp = skip_linked_list_node_create(list, key);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        skip_linked_list_key_contains_p(list, tmp->key);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&tmp);
    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_key_contains_p);
}

static void
ptest_skip_linked_list_insert(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfade;
    list = test_skip_linked_list_sample(0x1, 0x1);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_node_create(list, key);
        skip_linked_list_insert(&list, tmp);
        skip_linked_list_remove_and_destroy(&list, skip_linked_list_key(tmp));
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_insert);
}

static void
ptest_skip_linked_list_remove(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;

    list = test_skip_linked_list_sample(0x9e12, 0x1845);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_remove(&list, skip_linked_list_key(list));
        skip_linked_list_insert(&list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_remove);
}

static void
ptest_skip_linked_list_remove_and_destroy(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;

    key = 0xfedf;
    list = test_skip_linked_list_sample(0x912, 0x345);

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        tmp = skip_linked_list_node_create(list, key++);
        skip_linked_list_remove_and_destroy(&list, skip_linked_list_key(list));
        skip_linked_list_insert(&list, tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    skip_linked_list_destroy(&list);
    PERFORMANCE_TEST_RESULT(skip_linked_list_remove_and_destroy);
}

static void
ptest_skip_linked_list_merge(uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        list = test_skip_linked_list_sample(0x912, 0x12);
        tmp = skip_linked_list_node_create(list, 0xdefe);
        list = skip_linked_list_merge(list, tmp);

        skip_linked_list_destroy(&list);
        skip_linked_list_destroy(&tmp);
    }

    PERFORMANCE_TEST_ENDPOINT;

    PERFORMANCE_TEST_RESULT(skip_linked_list_merge);
}

