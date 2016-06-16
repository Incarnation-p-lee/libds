#define LINKED_LIST                    single_linked_list
#define LINKED_LIST_next               single_linked_list_next
#define LINKED_LIST_next_set           single_linked_list_next_set
#define LINKED_LIST_previous           single_linked_list_previous
#define LINKED_LIST_previous_set(l, v)
#define LINKED_LIST_val                single_linked_list_val
#define LINKED_LIST_val_set            single_linked_list_val_set

#define LINKED_LIST_create             single_linked_list_create
#define LINKED_LIST_initial            single_linked_list_initial
#define LINKED_LIST_node_create        single_linked_list_node_create
#define LINKED_LIST_insert_ptr_after   single_linked_list_insert_ptr_after
#define LINKED_LIST_insert_ptr_before  single_linked_list_insert_ptr_before
#define LINKED_LIST_insert_after       single_linked_list_insert_after
#define LINKED_LIST_insert_before      single_linked_list_insert_before
#define LINKED_LIST_destroy            single_linked_list_destroy
#define LINKED_LIST_length             single_linked_list_length
#define LINKED_LIST_node_by_index      single_linked_list_node_by_index
#define LINKED_LIST_contains_p         single_linked_list_contains_p
#define LINKED_LIST_node_copy          single_linked_list_node_copy
#define LINKED_LIST_remove             single_linked_list_remove
#define LINKED_LIST_remove_and_destroy single_linked_list_remove_and_destroy
#define LINKED_LIST_iterate            single_linked_list_iterate
#define LINKED_LIST_merge              single_linked_list_merge

#define TEST_LINKED_LIST_sample        test_single_linked_list_sample
#define RESULT_CHECK_LINKED_LIST_node  RESULT_CHECK_single_linked_list_node
#define TEST_LINKED_LIST_node_legal_p  utest_single_linked_list_node_legal_p

#include "../unit_test_linked_list.h"

UT_LINKED_LIST_create(single)
UT_LINKED_LIST_initial(single)
UT_LINKED_LIST_node_create(single)
UT_LINKED_LIST_previous(single)
UT_LINKED_LIST_insert_ptr_after(single)
UT_LINKED_LIST_insert_ptr_before(single)
UT_LINKED_LIST_insert_after(single)
UT_LINKED_LIST_insert_before(single)
UT_LINKED_LIST_destroy(single)
UT_LINKED_LIST_length(single)
UT_LINKED_LIST_node_by_index(single)
UT_LINKED_LIST_contains_p(single)
UT_LINKED_LIST_node_copy(single)
UT_LINKED_LIST_remove(single)
UT_LINKED_LIST_remove_and_destroy(single)
UT_LINKED_LIST_iterate(single)
UT_LINKED_LIST_merge(single)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_previous
#undef LINKED_LIST_previous_set
#undef LINKED_LIST_val
#undef LINKED_LIST_val_set

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_node_create
#undef LINKED_LIST_insert_ptr_after
#undef LINKED_LIST_insert_ptr_before
#undef LINKED_LIST_insert_after
#undef LINKED_LIST_insert_before
#undef LINKED_LIST_destroy
#undef LINKED_LIST_length
#undef LINKED_LIST_node_by_index
#undef LINKED_LIST_contains_p
#undef LINKED_LIST_node_copy
#undef LINKED_LIST_remove
#undef LINKED_LIST_remove_and_destroy
#undef LINKED_LIST_iterate
#undef LINKED_LIST_merge

#undef TEST_LINKED_LIST_sample
#undef RESULT_CHECK_LINKED_LIST_node
#undef TEST_LINKED_LIST_node_legal_p


static inline bool
utest_single_linked_list_node_legal_p(struct single_linked_list *node)
{
    dp_assert(!complain_null_pointer_p(node));

    if (node != single_linked_list_next(node)) {
        return false;
    } else if (node != single_linked_list_previous(node)) {
        return false;
    } else {
        return true;
    }
}

