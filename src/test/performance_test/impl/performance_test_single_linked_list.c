#define LINKED_LIST                    single_linked_list
#define LINKED_LIST_next               single_linked_list_next
#define LINKED_LIST_next_set           single_linked_list_next_set
#define LINKED_LIST_previous           single_linked_list_previous
#define LINKED_LIST_previous_set(l, v)
#define TEST_LINKED_LIST_sample        test_single_linked_list_sample

#define LINKED_LIST_create             single_linked_list_create
#define LINKED_LIST_initial            single_linked_list_initial
#define LINKED_LIST_insert_after       single_linked_list_insert_after
#define LINKED_LIST_insert_before      single_linked_list_insert_before
#define LINKED_LIST_destroy            single_linked_list_destroy
#define LINKED_LIST_length             single_linked_list_length
#define LINKED_LIST_node_by_index      single_linked_list_node_by_index
#define LINKED_LIST_contains_p         single_linked_list_contains_p
#define LINKED_LIST_node_copy          single_linked_list_node_copy
#define LINKED_LIST_remove             single_linked_list_remove
#define LINKED_LIST_iterate            single_linked_list_iterate
#define LINKED_LIST_merge              single_linked_list_merge

#include "../performance_test_linked_list.h"

PT_LINKED_LIST_create(single)
PT_LINKED_LIST_initial(single)
PT_LINKED_LIST_previous(single)
PT_LINKED_LIST_insert_after(single)
PT_LINKED_LIST_insert_before(single)
PT_LINKED_LIST_destroy(single)
PT_LINKED_LIST_length(single)
PT_LINKED_LIST_node_by_index(single)
PT_LINKED_LIST_contains_p(single)
PT_LINKED_LIST_node_copy(single)
PT_LINKED_LIST_remove(single)
PT_LINKED_LIST_iterate(single)
PT_LINKED_LIST_merge(single)

#undef LINKED_LIST
#undef LINKED_LIST_next
#undef LINKED_LIST_next_set
#undef LINKED_LIST_previous
#undef LINKED_LIST_previous_set
#undef TEST_LINKED_LIST_sample

#undef LINKED_LIST_create
#undef LINKED_LIST_initial
#undef LINKED_LIST_node_create
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

