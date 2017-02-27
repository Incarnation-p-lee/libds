#define LINKED_LIST                    s_doubly_linked_list_t
#define LINKED_LIST_next               doubly_linked_list_next
#define LINKED_LIST_next_set           doubly_linked_list_next_set
#define LINKED_LIST_previous           doubly_linked_list_previous
#define LINKED_LIST_previous_set       doubly_linked_list_previous_set
#define TEST_LINKED_LIST_sample        test_doubly_linked_list_sample

#define LINKED_LIST_create             doubly_linked_list_create
#define LINKED_LIST_initial            doubly_linked_list_initial
#define LINKED_LIST_insert_after       doubly_linked_list_insert_after
#define LINKED_LIST_insert_before      doubly_linked_list_insert_before
#define LINKED_LIST_destroy            doubly_linked_list_destroy
#define LINKED_LIST_length             doubly_linked_list_length
#define LINKED_LIST_node_by_index      doubly_linked_list_node_by_index
#define LINKED_LIST_contains_p         doubly_linked_list_contains_p
#define LINKED_LIST_node_copy          doubly_linked_list_node_copy
#define LINKED_LIST_remove             doubly_linked_list_remove
#define LINKED_LIST_iterate            doubly_linked_list_iterate
#define LINKED_LIST_merge              doubly_linked_list_merge


#include "../ptest_linked_list.h"

PT_LINKED_LIST_create(doubly)
PT_LINKED_LIST_initial(doubly)
PT_LINKED_LIST_insert_after(doubly)
PT_LINKED_LIST_insert_before(doubly)
PT_LINKED_LIST_destroy(doubly)
PT_LINKED_LIST_length(doubly)
PT_LINKED_LIST_node_by_index(doubly)
PT_LINKED_LIST_contains_p(doubly)
PT_LINKED_LIST_node_copy(doubly)
PT_LINKED_LIST_remove(doubly)
PT_LINKED_LIST_iterate(doubly)
PT_LINKED_LIST_merge(doubly)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_previous
#undef LINKED_LIST_previous_set
#undef TEST_LINKED_LIST_sample

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_insert_after
#undef LINKED_LIST_insert_before
#undef LINKED_LIST_destroy
#undef LINKED_LIST_length
#undef LINKED_LIST_node_by_index
#undef LINKED_LIST_contains_p
#undef LINKED_LIST_node_copy
#undef LINKED_LIST_remove
#undef LINKED_LIST_iterate
#undef LINKED_LIST_merge

