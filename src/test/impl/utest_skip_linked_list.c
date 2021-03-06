#define LINKED_LIST                    s_skip_linked_list_t
#define LINKED_LIST_next               skip_linked_list_next
#define LINKED_LIST_next_set           skip_linked_list_next_set
#define LINKED_LIST_val                skip_linked_list_val
#define LINKED_LIST_val_set            skip_linked_list_val_set

#define LINKED_LIST_create             skip_linked_list_create
#define LINKED_LIST_initial            skip_linked_list_initial
#define LINKED_LIST_destroy            skip_linked_list_destroy
#define LINKED_LIST_length             skip_linked_list_length
#define LINKED_LIST_node_by_index      skip_linked_list_node_by_index
#define LINKED_LIST_iterate            skip_linked_list_iterate
#define TEST_LINKED_LIST_sample        test_skip_linked_list_sample
#define TEST_LINKED_LIST_legal_p       skip_linked_list_structure_legal_p

#include "../utest_linked_list.h"

UT_LINKED_LIST_create(skip)
UT_LINKED_LIST_initial(skip)
UT_LINKED_LIST_destroy(skip)
UT_LINKED_LIST_length(skip)
UT_LINKED_LIST_node_by_index(skip)
UT_LINKED_LIST_iterate(skip)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_val
#undef LINKED_LIST_val_set

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_destroy
#undef LINKED_LIST_length
#undef LINKED_LIST_node_by_index
#undef LINKED_LIST_iterate
#undef TEST_LINKED_LIST_sample
#undef TEST_LINKED_LIST_legal_p

static void
utest_skip_linked_list_create_with_key(void)
{
    bool pass;
    sint32 key;
    s_skip_linked_list_t *list;

    pass = true;
    key = 0x431e2;
    UNIT_TEST_BEGIN(skip_linked_list_create_with_key);
    list = skip_linked_list_create_with_key(key);

    RESULT_CHECK_sint32(key, skip_linked_list_key(list), &pass);

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_create_with_key, pass);
}

static void
utest_skip_linked_list_contains_p(void)
{
    bool pass;
    sint32 key;
    s_skip_linked_list_t *tmp;
    s_skip_linked_list_t *list;

    pass = true;
    list = NULL;
    key = 0xfffff;
    UNIT_TEST_BEGIN(skip_linked_list_contains_p);

    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, NULL), &pass);
    list = test_skip_linked_list_sample(0x103f);
    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, NULL), &pass);

    tmp = skip_linked_list_create_with_key(0x2233);
    RESULT_CHECK_bool(false, skip_linked_list_contains_p(list, tmp), &pass);
    skip_linked_list_destroy(&tmp);

    key = 0xfff;
    while (key--) {
        tmp = skip_linked_list_find_key(list, key);
        if (tmp) {
            RESULT_CHECK_bool(true, skip_linked_list_contains_p(list, tmp), &pass);
        }
    }

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_contains_p, pass);
}


static void
utest_skip_linked_list_find_key(void)
{
    bool pass;
    sint32 key;
    s_skip_linked_list_t *tmp;
    s_skip_linked_list_t *list;

    pass = true;
    list = NULL;
    key = 0xfffff;
    UNIT_TEST_BEGIN(skip_linked_list_find_key);

    RESULT_CHECK_pointer(PTR_INVALID, skip_linked_list_find_key(list, key), &pass);
    list = test_skip_linked_list_sample(0x103f);
    RESULT_CHECK_pointer(NULL, skip_linked_list_find_key(list, key), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_create_with_key(key);
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
    s_skip_linked_list_t *tmp;
    s_skip_linked_list_t *list;

    pass = true;
    list = NULL;
    UNIT_TEST_BEGIN(skip_linked_list_insert);

    RESULT_CHECK_pointer(PTR_INVALID, skip_linked_list_insert(&list, NULL), &pass);
    list = test_skip_linked_list_sample(0x103f);
    RESULT_CHECK_pointer(PTR_INVALID, skip_linked_list_insert(&list, NULL), &pass);

    key = 0x1ffff;
    while (key--) {
        if (NULL != skip_linked_list_find_key(list, key)) {
            break;
        }
    }

    tmp = skip_linked_list_find_key(list, key);
    RESULT_CHECK_pointer(NULL, skip_linked_list_insert(&list, tmp), &pass);

    tmp = skip_linked_list_create_with_key(key);
    RESULT_CHECK_pointer(tmp, skip_linked_list_insert(&list, tmp), &pass);

    key = 0x1ffff;
    tmp = skip_linked_list_create_with_key(key);
    RESULT_CHECK_pointer(tmp, skip_linked_list_insert(&list, tmp), &pass);

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_insert, pass);
}

static void
utest_skip_linked_list_remove(void)
{
    bool pass;
    uint32 count;
    s_skip_linked_list_t *tmp;
    s_skip_linked_list_t *list;

    tmp = NULL;
    pass = true;
    list = NULL;
    count = 0x24;
    UNIT_TEST_BEGIN(skip_linked_list_remove);

    RESULT_CHECK_pointer(PTR_INVALID, skip_linked_list_remove(&list, 0), &pass);
    list = test_skip_linked_list_sample(0x103f);

    tmp = list;
    RESULT_CHECK_pointer(tmp, skip_linked_list_remove(&list, tmp), &pass);
    skip_linked_list_destroy(&tmp);

    tmp = skip_linked_list_create();
    RESULT_CHECK_pointer(NULL, skip_linked_list_remove(&list, tmp), &pass);
    skip_linked_list_destroy(&tmp);

    while (count--) {
        tmp = skip_linked_list_find_key(list, count);
        if (NULL != tmp) {
            RESULT_CHECK_pointer(tmp, skip_linked_list_remove(&list, tmp), &pass);
            skip_linked_list_destroy(&tmp);
        }
    }

    skip_linked_list_destroy(&list);
    UNIT_TEST_RESULT(skip_linked_list_remove, pass);
}

static void
utest_skip_linked_list_merge(void)
{
    bool pass;
    s_skip_linked_list_t *lm;
    s_skip_linked_list_t *ln;
    s_skip_linked_list_t *iter;
    s_skip_linked_list_t *tmp;

    pass = true;
    lm = NULL;
    UNIT_TEST_BEGIN(skip_linked_list_merge);

    ln = test_skip_linked_list_sample(0x103f);
    RESULT_CHECK_pointer(PTR_INVALID, skip_linked_list_merge(lm, lm), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(lm, ln), &pass);
    RESULT_CHECK_pointer(ln, skip_linked_list_merge(ln, ln), &pass);

    lm = skip_linked_list_create_with_key(0x8e290 - 0x245);
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

