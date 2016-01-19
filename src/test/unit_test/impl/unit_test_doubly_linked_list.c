#define LINKED_LIST                    doubly_linked_list
#define LINKED_LIST_next               doubly_linked_list_next
#define LINKED_LIST_next_set           doubly_linked_list_next_set
#define LINKED_LIST_previous           doubly_linked_list_previous
#define LINKED_LIST_previous_set       doubly_linked_list_previous_set
#define LINKED_LIST_val                doubly_linked_list_val
#define LINKED_LIST_val_set            doubly_linked_list_val_set

#define LINKED_LIST_create             doubly_linked_list_create
#define LINKED_LIST_initial            doubly_linked_list_initial
#define LINKED_LIST_node_create        doubly_linked_list_node_create
#define LINKED_LIST_insert_ptr_after   doubly_linked_list_insert_ptr_after
#define LINKED_LIST_insert_ptr_before  doubly_linked_list_insert_ptr_before
#define LINKED_LIST_insert_after       doubly_linked_list_insert_after
#define LINKED_LIST_insert_before      doubly_linked_list_insert_before
#define LINKED_LIST_destroy            doubly_linked_list_destroy
#define LINKED_LIST_length             doubly_linked_list_length
#define LINKED_LIST_node_by_index      doubly_linked_list_node_by_index
#define LINKED_LIST_contains_p         doubly_linked_list_contains_p
#define LINKED_LIST_node_copy          doubly_linked_list_node_copy
#define LINKED_LIST_remove             doubly_linked_list_remove
#define LINKED_LIST_remove_and_destroy doubly_linked_list_remove_and_destroy
#define LINKED_LIST_iterate            doubly_linked_list_iterate
#define LINKED_LIST_merge              doubly_linked_list_merge

#define TEST_LINKED_LIST_sample        test_doubly_linked_list_sample
#define RESULT_CHECK_LINKED_LIST_node  RESULT_CHECK_doubly_linked_list_node
#define TEST_LINKED_LIST_node_legal_p  utest_doubly_linked_list_node_legal_p

#include "../unit_test_linked_list.h"

UT_LINKED_LIST_create(doubly)
UT_LINKED_LIST_initial(doubly)
UT_LINKED_LIST_node_create(doubly)
UT_LINKED_LIST_insert_ptr_after(doubly)
UT_LINKED_LIST_insert_ptr_before(doubly)
UT_LINKED_LIST_insert_after(doubly)
UT_LINKED_LIST_insert_before(doubly)
UT_LINKED_LIST_destroy(doubly)
UT_LINKED_LIST_length(doubly)
UT_LINKED_LIST_node_by_index(doubly)
UT_LINKED_LIST_contains_p(doubly)
UT_LINKED_LIST_node_copy(doubly)
UT_LINKED_LIST_remove(doubly)
UT_LINKED_LIST_remove_and_destroy(doubly)
UT_LINKED_LIST_iterate(doubly)
UT_LINKED_LIST_merge(doubly)

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
utest_doubly_linked_list_node_legal_p(struct doubly_linked_list *node)
{
    assert(!complain_null_pointer_p(node));

    if (node != doubly_linked_list_next(node)) {
        return false;
    } else if (node != doubly_linked_list_previous(node)) {
        return false;
    } else {
        return true;
    }
}

