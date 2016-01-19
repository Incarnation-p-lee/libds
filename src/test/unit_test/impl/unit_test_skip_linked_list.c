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
#define TEST_LINKED_LIST_node_legal_p  utest_skip_linked_list_node_legal_p

#include "../unit_test_linked_list.h"

UT_LINKED_LIST_create(skip)
UT_LINKED_LIST_initial(skip)
UT_LINKED_LIST_destroy(skip)
UT_LINKED_LIST_length(skip)
UT_LINKED_LIST_node_by_index(skip)
UT_LINKED_LIST_iterate(skip)

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
#undef TEST_LINKED_LIST_node_legal_p

static inline bool
utest_skip_linked_list_node_legal_p(struct skip_linked_list *node)
{
    assert(!complain_null_pointer_p(node));

    if (NULL != skip_linked_list_val(node)) {
        return false;
    } else if (0 != skip_linked_list_key(node)) {
        return false;
    } else {
        return true;
    }
}

static void
utest_skip_linked_list_node_create(void)
{
    struct skip_linked_list *list;
    bool pass;
    sint32 key;

    pass = true;
    key = -1;

    list = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_pointer(&pass, skip_linked_list_val(list), &pass);
    RESULT_CHECK_sint32(key, skip_linked_list_key(list), &pass);

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_node_create, pass);
}

static void
utest_skip_linked_list_key_contains_p(void)
{
    bool pass;
    sint32 key;
    struct skip_linked_list *tmp;
    struct skip_linked_list *list;

    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, 0), &pass);
    list = test_skip_linked_list_sample(0xedbf, 0x103f);
    tmp = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, tmp->key), &pass);
    skip_linked_list_destroy(&tmp);

    key = 0xfff;
    tmp = skip_linked_list_find_key(list, key--);
    if (tmp) {
        RESULT_CHECK_bool(true, skip_linked_list_key_contains_p(list, tmp->key), &pass);
    }

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_key_contains_p, pass);
}


static void
utest_skip_linked_list_find_key(void)
{
    bool pass;
    sint32 key;
    struct skip_linked_list *tmp;
    struct skip_linked_list *list;

    pass = true;
    list = NULL;
    key = 0xfffff;

    RESULT_CHECK_pointer(NULL, skip_linked_list_find_key(list, key), &pass);
    list = test_skip_linked_list_sample(0xedbf, 0x103f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_find_key(list, key), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_node_create(&pass, key);
    skip_linked_list_insert(&list, tmp);

    RESULT_CHECK_pointer(tmp, skip_linked_list_find_key(tmp, key), &pass);

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_find_key, pass);
}

static void
utest_skip_linked_list_insert(void)
{
    bool pass;
    sint32 key;
    struct skip_linked_list *tmp;
    struct skip_linked_list *list;

    pass = true;
    list = NULL;

    RESULT_CHECK_pointer(NULL, skip_linked_list_insert(&list, NULL), &pass);
    list = test_skip_linked_list_sample(0x101f0, 0x103f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_insert(&list, NULL), &pass);

    key = 0x1ffff;
    while (key--) {
        if (NULL != skip_linked_list_find_key(list, key)) {
            break;
        }
    }

    tmp = skip_linked_list_find_key(list, key);
    RESULT_CHECK_pointer(NULL, skip_linked_list_insert(&list, tmp), &pass);

    tmp = skip_linked_list_node_create(&pass, key);
    RESULT_CHECK_pointer(tmp, skip_linked_list_insert(&list, tmp), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_node_create(&pass, key++);
    RESULT_CHECK_pointer(tmp, skip_linked_list_insert(&list, tmp), &pass);

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_insert, pass);
}

static void
utest_skip_linked_list_remove(void)
{
    bool pass;
    uint32 count;
    struct skip_linked_list *tmp;
    struct skip_linked_list *list;

    tmp = NULL;
    pass = true;
    list = NULL;
    count = 0x24;

    RESULT_CHECK_pointer(NULL, skip_linked_list_remove(&list, 0), &pass);
    list = test_skip_linked_list_sample(0x11f0, 0x103f);

    tmp = list;
    RESULT_CHECK_pointer(tmp, skip_linked_list_remove(&list, list->key), &pass);
    skip_linked_list_destroy(&tmp);
    RESULT_CHECK_pointer(NULL, skip_linked_list_remove(&list, 0x151f1), &pass);

    while (count--) {
        tmp = skip_linked_list_find_key(list, count);
        if (NULL != tmp) {
            RESULT_CHECK_pointer(tmp, skip_linked_list_remove(&list, tmp->key), &pass);
            skip_linked_list_destroy(&tmp);
        }
    }

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_remove, pass);
}

static void
utest_skip_linked_list_remove_and_destroy(void)
{
    bool pass;
    sint32 key;
    uint32 count;
    struct skip_linked_list *tmp;
    struct skip_linked_list *list;

    tmp = NULL;
    pass = true;
    list = NULL;
    count = 0x12;

    skip_linked_list_remove_and_destroy(&list, 0);
    list = test_skip_linked_list_sample(0x15f0, 0x103f);

    key = list->key;
    skip_linked_list_remove_and_destroy(&list, key);
    RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, key), &pass);
    skip_linked_list_remove_and_destroy(&list, 0x151f1);

    while (count--) {
        tmp = skip_linked_list_find_key(list, count);
        if (NULL != tmp) {
            key = tmp->key;
            skip_linked_list_remove_and_destroy(&list, key);

            if (skip_linked_list_find_key(list, count)) {
                RESULT_CHECK_bool(true, skip_linked_list_key_contains_p(list, key), &pass);
            } else {
                RESULT_CHECK_bool(false, skip_linked_list_key_contains_p(list, key), &pass);
            }
        }
    }

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_remove_and_destroy, pass);
}

static void
utest_skip_linked_list_merge(void)
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
        tmp = skip_linked_list_find_key(ln, iter->key);
        RESULT_CHECK_sint32(tmp->key, iter->key, &pass);
        iter = skip_linked_list_next(iter);
    }
    skip_linked_list_destroy(&lm);

    skip_linked_list_destroy(&ln);
    UNIT_TEST_RESULT(skip_linked_list_merge, pass);
}

