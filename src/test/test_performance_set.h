#ifndef HAVE_TEST_PERFORMANCE_SET_H
#define HAVE_TEST_PERFORMANCE_SET_H

static struct test_performance unit_test_performance[] = {
    {"single_linked_list_struct_field",            0x0u, 0x0u},
    {"single_linked_list_initial",                 0x0u, 0x0u},
    {"single_linked_list_create",                  0x0u, 0x0u},
    {"single_linked_list_generate",                0x0u, 0x0u},
    {"single_linked_list_node_initial",            0x0u, 0x0u},
    {"single_linked_list_node_create",             0x0u, 0x0u},
    {"single_linked_list_node_copy",               0x0u, 0x0u},
    {"single_linked_list_node_append",             0x0u, 0x0u},
    {"single_linked_list_node_previous",           0x0u, 0x0u},
    {"single_linked_list_node_insert_before",      0x0u, 0x0u},
    {"single_linked_list_node_insert_after",       0x0u, 0x0u},
    {"single_linked_list_node_by_index",           0x0u, 0x0u},
    {"single_linked_list_node_exchange",           0x0u, 0x0u},
    {"single_linked_list_node_remove",             0x0u, 0x0u},
    {"single_linked_list_node_lazy_remove",        0x0u, 0x0u},
    {"single_linked_list_contains_p",              0x0u, 0x0u},
    {"single_linked_list_serialize",               0x0u, 0x0u},
    {"single_linked_list_iterate",                 0x0u, 0x0u},
    {"single_linked_list_destroy",                 0x0u, 0x0u},
    {"single_linked_list_length",                  0x0u, 0x0u},
    {"single_linked_list_merge",                   0x0u, 0x0u},
    {"doubly_linked_list_struct_field",            0x0u, 0x0u},
    {"doubly_linked_list_initial",                 0x0u, 0x0u},
    {"doubly_linked_list_create",                  0x0u, 0x0u},
    {"doubly_linked_list_generate",                0x0u, 0x0u},
    {"doubly_linked_list_node_initial",            0x0u, 0x0u},
    {"doubly_linked_list_node_create",             0x0u, 0x0u},
    {"doubly_linked_list_node_copy",               0x0u, 0x0u},
    {"doubly_linked_list_node_append",             0x0u, 0x0u},
    {"doubly_linked_list_node_insert_before",      0x0u, 0x0u},
    {"doubly_linked_list_node_insert_after",       0x0u, 0x0u},
    {"doubly_linked_list_node_by_index",           0x0u, 0x0u},
    {"doubly_linked_list_node_exchange",           0x0u, 0x0u},
    {"doubly_linked_list_node_remove",             0x0u, 0x0u},
    {"doubly_linked_list_node_lazy_remove",        0x0u, 0x0u},
    {"doubly_linked_list_contains_p",              0x0u, 0x0u},
    {"doubly_linked_list_serialize",               0x0u, 0x0u},
    {"doubly_linked_list_iterate",                 0x0u, 0x0u},
    {"doubly_linked_list_destroy",                 0x0u, 0x0u},
    {"doubly_linked_list_length",                  0x0u, 0x0u},
    {"doubly_linked_list_merge",                   0x0u, 0x0u},
    {"skip_linked_list_struct_field",              0x0u, 0x0u},
    {"skip_linked_list_create",                    0x0u, 0x0u},
    {"skip_linked_list_initial",                   0x0u, 0x0u},
    {"skip_linked_list_node_create",               0x0u, 0x0u},
    {"skip_linked_list_node_initial",              0x0u, 0x0u},
    {"skip_linked_list_destroy",                   0x0u, 0x0u},
    {"skip_linked_list_length",                    0x0u, 0x0u},
    {"skip_linked_list_contains_p",                0x0u, 0x0u},
    {"skip_linked_list_node_insert",               0x0u, 0x0u},
    {"skip_linked_list_node_find_key",             0x0u, 0x0u},
    {"skip_linked_list_node_by_index",             0x0u, 0x0u},
    {"skip_linked_list_node_remove",               0x0u, 0x0u},
    {"skip_linked_list_iterate",                   0x0u, 0x0u},
    {"array_stack_struct_field",                   0x0u, 0x0u},
    {"array_stack_create",                         0x0u, 0x0u},
    {"array_stack_destroy",                        0x0u, 0x0u},
    {"array_stack_space_expand",                   0x0u, 0x0u},
    {"array_stack_space_rest",                     0x0u, 0x0u},
    {"array_stack_full_p",                         0x0u, 0x0u},
    {"array_stack_capacity",                       0x0u, 0x0u},
    {"array_stack_push",                           0x0u, 0x0u},
    {"array_stack_pop",                            0x0u, 0x0u},
    {"array_stack_empty_p",                        0x0u, 0x0u},
    {"array_stack_cleanup",                        0x0u, 0x0u},
    {"array_stack_iterate",                        0x0u, 0x0u},
    {"linked_stack_struct_field",                  0x0u, 0x0u},
    {"linked_stack_create",                        0x0u, 0x0u},
    {"linked_stack_destroy",                       0x0u, 0x0u},
    {"linked_stack_space_expand",                  0x0u, 0x0u},
    {"linked_stack_space_rest",                    0x0u, 0x0u},
    {"linked_stack_full_p",                        0x0u, 0x0u},
    {"linked_stack_capacity",                      0x0u, 0x0u},
    {"linked_stack_push",                          0x0u, 0x0u},
    {"linked_stack_pop",                           0x0u, 0x0u},
    {"linked_stack_empty_p",                       0x0u, 0x0u},
    {"linked_stack_cleanup",                       0x0u, 0x0u},
    {"linked_stack_iterate",                       0x0u, 0x0u},
    {"array_queue_struct_field",                   0x0u, 0x0u},
    {"array_queue_create",                         0x0u, 0x0u},
    {"array_queue_destroy",                        0x0u, 0x0u},
    {"array_queue_space_expand",                   0x0u, 0x0u},
    {"array_queue_space_rest",                     0x0u, 0x0u},
    {"array_queue_full_p",                         0x0u, 0x0u},
    {"array_queue_capacity",                       0x0u, 0x0u},
    {"array_queue_enter",                          0x0u, 0x0u},
    {"array_queue_leave",                          0x0u, 0x0u},
    {"array_queue_empty_p",                        0x0u, 0x0u},
    {"array_queue_cleanup",                        0x0u, 0x0u},
    {"array_queue_iterate",                        0x0u, 0x0u},
    {"stacked_queue_struct_field",                 0x0u, 0x0u},
    {"stacked_queue_create",                       0x0u, 0x0u},
    {"stacked_queue_destroy",                      0x0u, 0x0u},
    {"stacked_queue_space_expand",                 0x0u, 0x0u},
    {"stacked_queue_space_rest",                   0x0u, 0x0u},
    {"stacked_queue_full_p",                       0x0u, 0x0u},
    {"stacked_queue_capacity",                     0x0u, 0x0u},
    {"stacked_queue_enter",                        0x0u, 0x0u},
    {"stacked_queue_leave",                        0x0u, 0x0u},
    {"stacked_queue_empty_p",                      0x0u, 0x0u},
    {"stacked_queue_cleanup",                      0x0u, 0x0u},
    {"stacked_queue_iterate",                      0x0u, 0x0u},
    {"doubly_end_queue_struct_field",              0x0u, 0x0u},
    {"doubly_end_queue_create",                    0x0u, 0x0u},
    {"doubly_end_queue_destroy",                   0x0u, 0x0u},
    {"doubly_end_queue_length",                    0x0u, 0x0u},
    {"doubly_end_queue_empty_p",                   0x0u, 0x0u},
    {"doubly_end_queue_head_enter",                0x0u, 0x0u},
    {"doubly_end_queue_head_leave",                0x0u, 0x0u},
    {"doubly_end_queue_tail_enter",                0x0u, 0x0u},
    {"doubly_end_queue_tail_leave",                0x0u, 0x0u},
    {"doubly_end_queue_cleanup",                   0x0u, 0x0u},
    {"doubly_end_queue_iterate",                   0x0u, 0x0u},
    {"binary_search_tree_struct_field",            0x0u, 0x0u},
    {"binary_search_tree_create",                  0x0u, 0x0u},
    {"binary_search_tree_node_create",             0x0u, 0x0u},
    {"binary_search_tree_initial",                 0x0u, 0x0u},
    {"binary_search_tree_node_initial",            0x0u, 0x0u},
    {"binary_search_tree_destroy",                 0x0u, 0x0u},
    {"binary_search_tree_node_find",               0x0u, 0x0u},
    {"binary_search_tree_node_find_min",           0x0u, 0x0u},
    {"binary_search_tree_node_find_max",           0x0u, 0x0u},
    {"binary_search_tree_height",                  0x0u, 0x0u},
    {"binary_search_tree_node_contains_p",         0x0u, 0x0u},
    {"binary_search_tree_node_insert",             0x0u, 0x0u},
    {"binary_search_tree_node_remove",             0x0u, 0x0u},
    {"binary_search_tree_node_remove_and_destroy", 0x0u, 0x0u},
    {"binary_search_tree_iterate",                 0x0u, 0x0u},
    {"avl_tree_struct_field",                      0x0u, 0x0u},
    {"avl_tree_create",                            0x0u, 0x0u},
    {"avl_tree_node_create",                       0x0u, 0x0u},
    {"avl_tree_initial",                           0x0u, 0x0u},
    {"avl_tree_node_initial",                      0x0u, 0x0u},
    {"avl_tree_destroy",                           0x0u, 0x0u},
    {"avl_tree_node_find",                         0x0u, 0x0u},
    {"avl_tree_node_find_min",                     0x0u, 0x0u},
    {"avl_tree_node_find_max",                     0x0u, 0x0u},
    {"avl_tree_node_contains_p",                   0x0u, 0x0u},
    {"avl_tree_balanced_p",                        0x0u, 0x0u},
    {"avl_tree_node_insert",                       0x0u, 0x0u},
    {"avl_tree_node_remove",                       0x0u, 0x0u},
    {"avl_tree_iterate",                           0x0u, 0x0u},
    {"splay_tree_struct_field",                    0x0u, 0x0u},
    {"splay_tree_create",                          0x0u, 0x0u},
    {"splay_tree_node_create",                     0x0u, 0x0u},
    {"splay_tree_initial",                         0x0u, 0x0u},
    {"splay_tree_node_initial",                    0x0u, 0x0u},
    {"splay_tree_destroy",                         0x0u, 0x0u},
    {"splay_tree_node_contains_p",                 0x0u, 0x0u},
    {"splay_tree_node_find",                       0x0u, 0x0u},
    {"splay_tree_node_find_min",                   0x0u, 0x0u},
    {"splay_tree_node_find_max",                   0x0u, 0x0u},
    {"splay_tree_height",                          0x0u, 0x0u},
    {"splay_tree_node_insert",                     0x0u, 0x0u},
    {"splay_tree_node_remove",                     0x0u, 0x0u},
    {"splay_tree_iterate",                         0x0u, 0x0u},
    {"separate_chain_hash_struct_field",           0x0u, 0x0u},
    {"separate_chain_hash_create",                 0x0u, 0x0u},
    {"separate_chain_hash_destroy",                0x0u, 0x0u},
    {"separate_chain_hash_load_factor_calculate",  0x0u, 0x0u},
    {"separate_chain_hash_insert",                 0x0u, 0x0u},
    {"separate_chain_hash_remove",                 0x0u, 0x0u},
    {"separate_chain_hash_find",                   0x0u, 0x0u},
    {"separate_chain_hash_rehashing",              0x0u, 0x0u},
    {"open_addressing_hash_struct_field",          0x0u, 0x0u},
    {"open_addressing_hash_create",                0x0u, 0x0u},
    {"open_addressing_hash_destroy",               0x0u, 0x0u},
    {"open_addressing_hash_load_factor_calculate", 0x0u, 0x0u},
    {"open_addressing_hash_insert",                0x0u, 0x0u},
    {"open_addressing_hash_remove",                0x0u, 0x0u},
    {"open_addressing_hash_find",                  0x0u, 0x0u},
    {"open_addressing_hash_rehashing",             0x0u, 0x0u},
    {"minimal_heap_struc_field",                   0x0u, 0x0u},
    {"minimal_heap_create",                        0x0u, 0x0u},
    {"minimal_heap_destroy",                       0x0u, 0x0u},
    {"minimal_heap_empty_p",                       0x0u, 0x0u},
    {"minimal_heap_full_p",                        0x0u, 0x0u},
    {"minimal_heap_cleanup",                       0x0u, 0x0u},
    {"minimal_heap_node_find",                     0x0u, 0x0u},
    {"minimal_heap_node_find_min",                 0x0u, 0x0u},
    {"minimal_heap_node_insert",                   0x0u, 0x0u},
    {"minimal_heap_node_remove_min",               0x0u, 0x0u},
    {"minimal_heap_node_remove",                   0x0u, 0x0u},
    {"minimal_heap_node_decrease_nice",            0x0u, 0x0u},
    {"minimal_heap_node_increase_nice",            0x0u, 0x0u},
    {NULL,                                         0x0u, 0x0u},
};

#endif
