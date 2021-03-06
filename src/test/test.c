#include "depends.h"
#include "defines.h"
#include "data_structure_interface.h"
#include "universal.h"

#include "test.h"
#include "ptest.h"
#include "utest.h"
#include "ptest_reference.h"
#include "test_result_check.h"
#include "test_declaration.h"

#include "impl/test_case_list.c"
#include "impl/test_main.c"
#include "impl/test_sample.c"
#include "impl/test_utilize.c"
#include "impl/test_result_check.c"
#include "impl/test_parameter.c"
#include "impl/test_case_filter.c"
#include "impl/test_common.c"
#include "impl/test_memory_maps.c"

#include "impl/utest_main.c"
#include "impl/ptest_main.c"
#include "impl/ptest_timing.c"
#include "impl/ptest_reference.c"

#include "impl/utest_separate_chain_hash.c"
#include "impl/utest_open_addressing_hash.c"
#include "impl/utest_bitmap.c"
#include "impl/ptest_open_addressing_hash.c"
#include "impl/ptest_separate_chain_hash.c"
#include "impl/ptest_bitmap.c"

#include "impl/utest_minimal_heap.c"
#include "impl/utest_maximal_heap.c"
#include "impl/utest_min_max_heap.c"
#include "impl/utest_leftist_heap.c"
#include "impl/ptest_minimal_heap.c"
#include "impl/ptest_maximal_heap.c"
#include "impl/ptest_min_max_heap.c"
#include "impl/ptest_leftist_heap.c"

#include "impl/utest_doubly_linked_list.c"
#include "impl/utest_single_linked_list.c"
#include "impl/utest_skip_linked_list.c"
#include "impl/ptest_doubly_linked_list.c"
#include "impl/ptest_single_linked_list.c"
#include "impl/ptest_skip_linked_list.c"

#include "impl/utest_array_queue.c"
#include "impl/utest_stacked_queue.c"
#include "impl/utest_doubly_end_queue.c"
#include "impl/ptest_array_queue.c"
#include "impl/ptest_stacked_queue.c"
#include "impl/ptest_doubly_end_queue.c"

#include "impl/utest_disjoint_set.c"
#include "impl/ptest_disjoint_set.c"

#include "impl/utest_insertion_sort.c"
#include "impl/utest_shell_sort.c"
#include "impl/utest_heap_sort.c"
#include "impl/utest_merge_sort.c"
#include "impl/utest_quick_sort.c"
#include "impl/ptest_insertion_sort.c"
#include "impl/ptest_shell_sort.c"
#include "impl/ptest_heap_sort.c"
#include "impl/ptest_merge_sort.c"
#include "impl/ptest_quick_sort.c"

#include "impl/utest_array_stack.c"
#include "impl/utest_linked_stack.c"
#include "impl/ptest_array_stack.c"
#include "impl/ptest_linked_stack.c"

#include "impl/utest_binary_search_tree.c"
#include "impl/utest_avl_tree.c"
#include "impl/utest_splay_tree.c"
#include "impl/utest_binary_indexed_tree.c"
#include "impl/utest_trie_tree.c"
#include "impl/ptest_binary_search_tree.c"
#include "impl/ptest_avl_tree.c"
#include "impl/ptest_splay_tree.c"
#include "impl/ptest_binary_indexed_tree.c"
#include "impl/ptest_trie_tree.c"

#include "impl/utest_indirected_graph.c"
#include "impl/utest_directed_graph.c"

#include "impl/utest_spin_lock.c"
#include "impl/utest_semaphore.c"
#include "impl/utest_mutex.c"
#include "impl/ptest_spin_lock.c"
#include "impl/ptest_semaphore.c"
#include "impl/ptest_mutex.c"

#include "test_layer.h"

