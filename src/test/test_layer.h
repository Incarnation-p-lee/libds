#ifndef TEST_LAYER_H
#define TEST_LAYER_H

static const struct test_layer_table single_linked_list_interface[] = {
    {
        "initial", NULL,
        {
            &utest_single_linked_list_initial,
            &ptest_single_linked_list_initial,
        },
    },
    {
        "create", NULL,
        {
            &utest_single_linked_list_create,
            &ptest_single_linked_list_create,
        },
    },
    {
        "previous", NULL,
        {
            &utest_single_linked_list_previous,
            &ptest_single_linked_list_previous,
        },
    },
    {
        "insert_before", NULL,
        {
            &utest_single_linked_list_insert_before,
            &ptest_single_linked_list_insert_before,
        },
    },
    {
        "insert_after", NULL,
        {
            &utest_single_linked_list_insert_after,
            &ptest_single_linked_list_insert_after,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_single_linked_list_destroy,
            &ptest_single_linked_list_destroy,
        },
    },
    {
        "length", NULL,
        {
            &utest_single_linked_list_length,
            &ptest_single_linked_list_length,
        },
    },
    {
        "node_by_index", NULL,
        {
            &utest_single_linked_list_node_by_index,
            &ptest_single_linked_list_node_by_index,
        },
    },
    {
        "contains_p", NULL,
        {
            &utest_single_linked_list_contains_p,
            &ptest_single_linked_list_contains_p,
        },
    },
    {
        "node_copy", NULL,
        {
            &utest_single_linked_list_node_copy,
            &ptest_single_linked_list_node_copy,
        },
    },
    {
        "remove", NULL,
        {
            &utest_single_linked_list_remove,
            &ptest_single_linked_list_remove,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_single_linked_list_iterate,
            &ptest_single_linked_list_iterate,
        },
    },
    {
        "merge", NULL,
        {
            &utest_single_linked_list_merge,
            &ptest_single_linked_list_merge,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table doubly_linked_list_interface[] = {
    {
        "create", NULL,
        {
            &utest_doubly_linked_list_create,
            &ptest_doubly_linked_list_create,
        },
    },
    {
        "initial", NULL,
        {
            &utest_doubly_linked_list_initial,
            &ptest_doubly_linked_list_initial,
        },
    },
    {
        "insert_before", NULL,
        {
            &utest_doubly_linked_list_insert_before,
            &ptest_doubly_linked_list_insert_before,
        },
    },
    {
        "insert_after", NULL,
        {
            &utest_doubly_linked_list_insert_after,
            &ptest_doubly_linked_list_insert_after,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_doubly_linked_list_destroy,
            &ptest_doubly_linked_list_destroy,
        },
    },
    {
        "length", NULL,
        {
            &utest_doubly_linked_list_length,
            &ptest_doubly_linked_list_length,
        },
    },
    {
        "node_by_index", NULL,
        {
            &utest_doubly_linked_list_node_by_index,
            &ptest_doubly_linked_list_node_by_index,
        },
    },
    {
        "contains_p", NULL,
        {
            &utest_doubly_linked_list_contains_p,
            &ptest_doubly_linked_list_contains_p,
        },
    },
    {
        "node_copy", NULL,
        {
            &utest_doubly_linked_list_node_copy,
            &ptest_doubly_linked_list_node_copy,
        },
    },
    {
        "remove", NULL,
        {
            &utest_doubly_linked_list_remove,
            &ptest_doubly_linked_list_remove,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_doubly_linked_list_iterate,
            &ptest_doubly_linked_list_iterate,
        },
    },
    {
        "merge", NULL,
        {
            &utest_doubly_linked_list_merge,
            &ptest_doubly_linked_list_merge,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table skip_linked_list_interface[] = {
    {
        "create", NULL,
        {
            &utest_skip_linked_list_create,
            &ptest_skip_linked_list_create,
        },
    },
    {
        "initial", NULL,
        {
            &utest_skip_linked_list_initial,
            &ptest_skip_linked_list_initial,
        },
    },
    {
        "create_with_key", NULL,
        {
            &utest_skip_linked_list_create_with_key,
            &ptest_skip_linked_list_create_with_key,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_skip_linked_list_destroy,
            &ptest_skip_linked_list_destroy,
        },
    },
    {
        "length",
        NULL,
        {
            &utest_skip_linked_list_length,
            &ptest_skip_linked_list_length,
        },
    },
    {
        "find_key",
        NULL,
        {
            &utest_skip_linked_list_find_key,
            &ptest_skip_linked_list_find_key,
        },
    },
    {
        "contains_p",
        NULL,
        {
            &utest_skip_linked_list_contains_p,
            &ptest_skip_linked_list_contains_p,
        },
    },
    {
        "insert",
        NULL,
        {
            &utest_skip_linked_list_insert,
            &ptest_skip_linked_list_insert,
        },
    },
    {
        "node_by_index",
        NULL,
        {
            &utest_skip_linked_list_node_by_index,
            &ptest_skip_linked_list_node_by_index,
        },
    },
    {
        "remove",
        NULL,
        {
            &utest_skip_linked_list_remove,
            &ptest_skip_linked_list_remove,
        },
    },
    {
        "iterate",
        NULL,
        {
            &utest_skip_linked_list_iterate,
            &ptest_skip_linked_list_iterate,
        },
    },
    {
        "merge", NULL,
        {
            &utest_skip_linked_list_merge,
            &ptest_skip_linked_list_merge,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table array_stack[] = {
    {
        "create", NULL,
        {
            &utest_array_stack_create,
            &ptest_array_stack_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_array_stack_destroy,
            &ptest_array_stack_destroy,
        },
    },
    {
        "resize", NULL,
        {
            &utest_array_stack_resize,
            &ptest_array_stack_resize,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_array_stack_full_p,
            &ptest_array_stack_full_p,
        },
    },
    {
        "capacity", NULL,
        {
            &utest_array_stack_capacity,
            &ptest_array_stack_capacity,
        },
    },
    {
        "rest", NULL,
        {
            &utest_array_stack_rest,
            &ptest_array_stack_rest,
        },
    },
    {
        "push", NULL,
        {
            &utest_array_stack_push,
            &ptest_array_stack_push,
        },
    },
    {
        "pop", NULL,
        {
            &utest_array_stack_pop,
            &ptest_array_stack_pop,
        },
    },
    {
        "top", NULL,
        {
            &utest_array_stack_top,
            &ptest_array_stack_top,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_array_stack_empty_p,
            &ptest_array_stack_empty_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_array_stack_cleanup,
            &ptest_array_stack_cleanup,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_array_stack_iterate,
            &ptest_array_stack_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table linked_stack[] = {
    {
        "create", NULL,
        {
            &utest_linked_stack_create,
            &ptest_linked_stack_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_linked_stack_destroy,
            &ptest_linked_stack_destroy,
        },
    },
    {
        "resize", NULL,
        {
            &utest_linked_stack_resize,
            &ptest_linked_stack_resize,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_linked_stack_full_p,
            &ptest_linked_stack_full_p,
        },
    },
    {
        "rest", NULL,
        {
            &utest_linked_stack_rest,
            &ptest_linked_stack_rest,
        },
    },
    {
        "capacity", NULL,
        {
            &utest_linked_stack_capacity,
            &ptest_linked_stack_capacity,
        },
    },
    {
        "push", NULL,
        {
            &utest_linked_stack_push,
            &ptest_linked_stack_push,
        },
    },
    {
        "pop", NULL,
        {
            &utest_linked_stack_pop,
            &ptest_linked_stack_pop,
        },
    },
    {
        "top", NULL,
        {
            &utest_linked_stack_top,
            &ptest_linked_stack_top,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_linked_stack_empty_p,
            &ptest_linked_stack_empty_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_linked_stack_cleanup,
            &ptest_linked_stack_cleanup,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_linked_stack_iterate,
            &ptest_linked_stack_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table array_queue[] = {
    {
        "create", NULL,
        {
            &utest_array_queue_create,
            &ptest_array_queue_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_array_queue_destroy,
            &ptest_array_queue_destroy,
        },
    },
    {
        "resize", NULL,
        {
            &utest_array_queue_resize,
            &ptest_array_queue_resize,
        },
    },
    {
        "rest", NULL,
        {
            &utest_array_queue_rest,
            &ptest_array_queue_rest,
        },
    },
    {
        "capacity", NULL,
        {
            &utest_array_queue_capacity,
            &ptest_array_queue_capacity,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_array_queue_full_p,
            &ptest_array_queue_full_p,
        },
    },
    {
        "enter", NULL,
        {
            &utest_array_queue_enter,
            &ptest_array_queue_enter,
        },
    },
    {
        "leave", NULL,
        {
            &utest_array_queue_leave,
            &ptest_array_queue_leave,
        },
    },
    {
        "front", NULL,
        {
            &utest_array_queue_front,
            &ptest_array_queue_front,
        },
    },
    {
        "rear", NULL,
        {
            &utest_array_queue_rear,
            &ptest_array_queue_rear,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_array_queue_empty_p,
            &ptest_array_queue_empty_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_array_queue_cleanup,
            &ptest_array_queue_cleanup,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_array_queue_iterate,
            &ptest_array_queue_iterate,
        },
    },
    {
        "iterator", NULL,
        {
            &utest_array_queue_iterator,
            NULL,
        },
    },
    {
        "copy", NULL,
        {
            &utest_array_queue_copy,
            &ptest_array_queue_copy,
        },
    },
    {
        "merge", NULL,
        {
            &utest_array_queue_merge,
            &ptest_array_queue_merge,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table stacked_queue[] = {
    {
        "create", NULL,
        {
            &utest_stacked_queue_create,
            &ptest_stacked_queue_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_stacked_queue_destroy,
            &ptest_stacked_queue_destroy,
        },
    },
    {
        "resize", NULL,
        {
            &utest_stacked_queue_resize,
            &ptest_stacked_queue_resize,
        },
    },
    {
        "rest", NULL,
        {
            &utest_stacked_queue_rest,
            &ptest_stacked_queue_rest,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_stacked_queue_full_p,
            &ptest_stacked_queue_full_p,
        },
    },
    {
        "capacity", NULL,
        {
            &utest_stacked_queue_capacity,
            &ptest_stacked_queue_capacity,
        },
    },
    {
        "enter", NULL,
        {
            &utest_stacked_queue_enter,
            &ptest_stacked_queue_enter,
        },
    },
    {
        "leave", NULL,
        {
            &utest_stacked_queue_leave,
            &ptest_stacked_queue_leave,
        },
    },
    {
        "front", NULL,
        {
            &utest_stacked_queue_front,
            &ptest_stacked_queue_front,
        },
    },
    {
        "rear", NULL,
        {
            &utest_stacked_queue_rear,
            &ptest_stacked_queue_rear,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_stacked_queue_empty_p,
            &ptest_stacked_queue_empty_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_stacked_queue_cleanup,
            &ptest_stacked_queue_cleanup,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_stacked_queue_iterate,
            &ptest_stacked_queue_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table doubly_end_queue[] = {
    {
        "create", NULL,
        {
            &utest_doubly_end_queue_create,
            &ptest_doubly_end_queue_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_doubly_end_queue_destroy,
            &ptest_doubly_end_queue_destroy,
        },
    },
    {
        "length", NULL,
        {
            &utest_doubly_end_queue_length,
            &ptest_doubly_end_queue_length,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_doubly_end_queue_empty_p,
            &ptest_doubly_end_queue_empty_p,
        },
    },
    {
        "front", NULL,
        {
            &utest_doubly_end_queue_front,
            &ptest_doubly_end_queue_front,
        },
    },
    {
        "front_enter", NULL,
        {
            &utest_doubly_end_queue_front_enter,
            &ptest_doubly_end_queue_front_enter,
        },
    },
    {
        "front_leave", NULL,
        {
            &utest_doubly_end_queue_front_leave,
            &ptest_doubly_end_queue_front_leave,
        },
    },
    {
        "rear", NULL,
        {
            &utest_doubly_end_queue_rear,
            &ptest_doubly_end_queue_rear,
        },
    },
    {
        "rear_enter", NULL,
        {
            &utest_doubly_end_queue_rear_enter,
            &ptest_doubly_end_queue_rear_enter,
        },
    },
    {
        "rear_leave", NULL,
        {
            &utest_doubly_end_queue_rear_leave,
            &ptest_doubly_end_queue_rear_leave,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_doubly_end_queue_cleanup,
            &ptest_doubly_end_queue_cleanup,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_doubly_end_queue_iterate,
            &ptest_doubly_end_queue_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table binary_search_tree[] = {
    {
        "create", NULL,
        {
            &utest_binary_search_tree_create,
            &ptest_binary_search_tree_create,
        },
    },
    {
        "initial", NULL,
        {
            &utest_binary_search_tree_initial,
            &ptest_binary_search_tree_initial,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_binary_search_tree_destroy,
            &ptest_binary_search_tree_destroy,
        },
    },
    {
        "find", NULL,
        {
            &utest_binary_search_tree_find,
            &ptest_binary_search_tree_find,
        },
    },
    {
        "find_min", NULL,
        {
            &utest_binary_search_tree_find_min,
            &ptest_binary_search_tree_find_min,
        },
    },
    {
        "find_max", NULL,
        {
            &utest_binary_search_tree_find_max,
            &ptest_binary_search_tree_find_max,
        },
    },
    {
        "height", NULL,
        {
            &utest_binary_search_tree_height,
            &ptest_binary_search_tree_height,
        },
    },
    {
        "contains_p", NULL,
        {
            &utest_binary_search_tree_contains_p,
            &ptest_binary_search_tree_contains_p,
        },
    },
    {
        "insert", NULL,
        {
            &utest_binary_search_tree_insert,
            &ptest_binary_search_tree_insert,
        },
    },
    {
        "remove", NULL,
        {
            &utest_binary_search_tree_remove,
            &ptest_binary_search_tree_remove,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_binary_search_tree_iterate,
            &ptest_binary_search_tree_iterate,
        },},
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table avl_tree[] = {
    {
        "create", NULL,
        {
            &utest_avl_tree_create,
            &ptest_avl_tree_create,
        },
    },
    {
        "initial", NULL,
        {
            &utest_avl_tree_initial,
            &ptest_avl_tree_initial,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_avl_tree_destroy,
            &ptest_avl_tree_destroy,
        },
    },
    {
        "find", NULL,
        {
            &utest_avl_tree_find,
            &ptest_avl_tree_find,
        },
    },
    {
        "find_min", NULL,
        {
            &utest_avl_tree_find_min,
            &ptest_avl_tree_find_min,
        },
    },
    {
        "find_max", NULL,
        {
            &utest_avl_tree_find_max,
            &ptest_avl_tree_find_max,
        },
    },
    {
        "height", NULL,
        {
            &utest_avl_tree_height,
            &ptest_avl_tree_height,
        },
    },
    {
        "contains_p", NULL,
        {
            &utest_avl_tree_contains_p,
            &ptest_avl_tree_contains_p,
        },
    },
    {
        "balanced_p", NULL,
        {
            &utest_avl_tree_balanced_p,
            &ptest_avl_tree_balanced_p,
        },
    },
    {
        "insert", NULL,
        {
            &utest_avl_tree_insert,
            &ptest_avl_tree_insert,
        },
    },
    {
        "remove", NULL,
        {
            &utest_avl_tree_remove,
            &ptest_avl_tree_remove,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_avl_tree_iterate,
            &ptest_avl_tree_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL, },},
};

static const struct test_layer_table splay_tree[] = {
    {
        "create", NULL,
        {
            &utest_splay_tree_create,
            &ptest_splay_tree_create,
        },
    },
    {
        "initial", NULL,
        {
            &utest_splay_tree_initial,
            &ptest_splay_tree_initial,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_splay_tree_destroy,
            &ptest_splay_tree_destroy,
        },
    },
    {
        "find", NULL,
        {
            &utest_splay_tree_find,
            &ptest_splay_tree_find,
        },
    },
    {
        "find_min", NULL,
        {
            &utest_splay_tree_find_min,
            &ptest_splay_tree_find_min,
        },
    },
    {
        "find_max", NULL,
        {
            &utest_splay_tree_find_max,
            &ptest_splay_tree_find_max,
        },
    },
    {
        "height", NULL,
        {
            &utest_splay_tree_height,
            &ptest_splay_tree_height,
        },
    },
    {
        "contains_p", NULL,
        {
            &utest_splay_tree_contains_p,
            &ptest_splay_tree_contains_p,
        },
    },
    {
        "insert", NULL,
        {
            &utest_splay_tree_insert,
            &ptest_splay_tree_insert,
        },
    },
    {
        "remove", NULL,
        {
            &utest_splay_tree_remove,
            &ptest_splay_tree_remove,
        },
    },
    {
        "iterate", NULL,
        {
            &utest_splay_tree_iterate,
            &ptest_splay_tree_iterate,
        },
    },
    {NULL, NULL, {NULL, NULL,},},
};

static const struct test_layer_table binary_indexed_tree[] = {
    {
        "create", NULL,
        {
            &utest_binary_indexed_tree_create,
            &ptest_binary_indexed_tree_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_binary_indexed_tree_destroy,
            &ptest_binary_indexed_tree_destroy,
        },
    },
    {
        "add", NULL,
        {
            &utest_binary_indexed_tree_add,
            &ptest_binary_indexed_tree_add,
        },
    },
    {
        "sub", NULL,
        {
            &utest_binary_indexed_tree_sub,
            &ptest_binary_indexed_tree_sub,
        },
    },
    {
        "sum", NULL,
        {
            &utest_binary_indexed_tree_sum,
            &ptest_binary_indexed_tree_sum,
        },
    },
    {
        "range_sum", NULL,
        {
            &utest_binary_indexed_tree_range_sum,
            &ptest_binary_indexed_tree_range_sum,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table trie_tree[] = {
    {
        "create", NULL,
        {
            &utest_trie_tree_create,
            &ptest_trie_tree_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_trie_tree_destroy,
            &ptest_trie_tree_destroy,
        },
    },
    {
        "sequence_insert", NULL,
        {
            &utest_trie_tree_sequence_insert,
            &ptest_trie_tree_sequence_insert,
        },
    },
    {
        "string_insert", NULL,
        {
            &utest_trie_tree_string_insert,
            &ptest_trie_tree_string_insert,
        },
    },
    {
        "sequence_remove", NULL,
        {
            &utest_trie_tree_sequence_remove,
            &ptest_trie_tree_sequence_remove,
        },
    },
    {
        "string_remove", NULL,
        {
            &utest_trie_tree_string_remove,
            &ptest_trie_tree_string_remove,
        },
    },
    {
        "sequence_matched_p", NULL,
        {
            &utest_trie_tree_sequence_matched_p,
            &ptest_trie_tree_sequence_matched_p,
        },
    },
    {
        "string_matched_p", NULL,
        {
            &utest_trie_tree_string_matched_p,
            &ptest_trie_tree_string_matched_p,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table separate_chain_hash[] = {
    {
        "create", NULL,
        {
            &utest_separate_chain_hash_create,
            &ptest_separate_chain_hash_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_separate_chain_hash_destroy,
            &ptest_separate_chain_hash_destroy,
        },
    },
    {
        "load_factor", NULL,
        {
            &utest_separate_chain_hash_load_factor,
            &ptest_separate_chain_hash_load_factor,
        },
    },
    {
        "insert", NULL,
        {
            &utest_separate_chain_hash_insert,
            &ptest_separate_chain_hash_insert,
        },
    },
    {
        "remove", NULL,
        {
            &utest_separate_chain_hash_remove,
            &ptest_separate_chain_hash_remove,
        },
    },
    {
        "find", NULL,
        {
            &utest_separate_chain_hash_find,
            &ptest_separate_chain_hash_find,
        },
    },
    {
        "rehashing", NULL,
        {
            &utest_separate_chain_hash_rehashing,
            &ptest_separate_chain_hash_rehashing,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table open_addressing_hash[] = {
    {
        "create", NULL,
        {
            &utest_open_addressing_hash_create,
            &ptest_open_addressing_hash_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_open_addressing_hash_destroy,
            &ptest_open_addressing_hash_destroy,
        },
    },
    {
        "load_factor", NULL,
        {
            &utest_open_addressing_hash_load_factor,
            &ptest_open_addressing_hash_load_factor,
        },
    },
    {
        "insert", NULL,
        {
            &utest_open_addressing_hash_insert,
            &ptest_open_addressing_hash_insert,
        },
    },
    {
        "remove", NULL,
        {
            &utest_open_addressing_hash_remove,
            &ptest_open_addressing_hash_remove,
        },
    },
    {
        "find", NULL,
        {
            &utest_open_addressing_hash_find,
            &ptest_open_addressing_hash_find,
        },
    },
    {
        "rehashing", NULL,
        {
            &utest_open_addressing_hash_rehashing,
            &ptest_open_addressing_hash_rehashing,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table bitmap[] = {
    {
        "create", NULL,
        {
            &utest_bitmap_create,
            &ptest_bitmap_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_bitmap_destroy,
            &ptest_bitmap_destroy,
        },
    },
    {
        "bit_get", NULL,
        {
            &utest_bitmap_bit_get,
            &ptest_bitmap_bit_get,
        },
    },
    {
        "bit_set", NULL,
        {
            &utest_bitmap_bit_set,
            &ptest_bitmap_bit_set,
        },
    },
    {
        "bit_clear_p", NULL,
        {
            &utest_bitmap_bit_clear_p,
            &ptest_bitmap_bit_clear_p,
        },
    },
    {
        "bit_set_p", NULL,
        {
            &utest_bitmap_bit_set_p,
            &ptest_bitmap_bit_set_p,
        },
    },
    {
        "bit_clear", NULL,
        {
            &utest_bitmap_bit_clear,
            &ptest_bitmap_bit_clear,
        },
    },
    {
        "map_cleanup", NULL,
        {
            &utest_bitmap_map_cleanup,
            &ptest_bitmap_map_cleanup,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table minimal_heap[] = {
    {
        "create", NULL,
        {
            &utest_minimal_heap_create,
            &ptest_minimal_heap_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_minimal_heap_destroy,
            &ptest_minimal_heap_destroy,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_minimal_heap_empty_p,
            &ptest_minimal_heap_empty_p,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_minimal_heap_full_p,
            &ptest_minimal_heap_full_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_minimal_heap_cleanup,
            &ptest_minimal_heap_cleanup,
        },
    },
    {
        "get_min", NULL,
        {
            &utest_minimal_heap_get_min,
            &ptest_minimal_heap_get_min,
        },
    },
    {
        "insert", NULL,
        {
            &utest_minimal_heap_insert,
            &ptest_minimal_heap_insert,
        },
    },
    {
        "remove_min", NULL,
        {
            &utest_minimal_heap_remove_min,
            &ptest_minimal_heap_remove_min,
        },
    },
    {
        "remove", NULL,
        {
            &utest_minimal_heap_remove,
            &ptest_minimal_heap_remove,
        },
    },
    {
        "decrease_nice", NULL,
        {
            &utest_minimal_heap_decrease_nice,
            &ptest_minimal_heap_decrease_nice,
        },
    },
    {
        "increase_nice", NULL,
        {
            &utest_minimal_heap_increase_nice,
            &ptest_minimal_heap_increase_nice,
        },
    },
    {
        "build", NULL,
        {
            &utest_minimal_heap_build,
            &ptest_minimal_heap_build,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table maximal_heap[] = {
    {
        "create", NULL,
        {
            &utest_maximal_heap_create,
            &ptest_maximal_heap_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_maximal_heap_destroy,
            &ptest_maximal_heap_destroy,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_maximal_heap_empty_p,
            &ptest_maximal_heap_empty_p,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_maximal_heap_full_p,
            &ptest_maximal_heap_full_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_maximal_heap_cleanup,
            &ptest_maximal_heap_cleanup,
        },
    },
    {
        "get_max", NULL,
        {
            &utest_maximal_heap_get_max,
            &ptest_maximal_heap_get_max,
        },
    },
    {
        "insert", NULL,
        {
            &utest_maximal_heap_insert,
            &ptest_maximal_heap_insert,
        },
    },
    {
        "remove_min", NULL,
        {
            &utest_maximal_heap_remove_max,
            &ptest_maximal_heap_remove_max,
        },
    },
    {
        "remove", NULL,
        {
            &utest_maximal_heap_remove,
            &ptest_maximal_heap_remove,
        },
    },
    {
        "decrease_nice", NULL,
        {
            &utest_maximal_heap_decrease_nice,
            &ptest_maximal_heap_decrease_nice,
        },
    },
    {
        "increase_nice", NULL,
        {
            &utest_maximal_heap_increase_nice,
            &ptest_maximal_heap_increase_nice,
        },
    },
    {
        "build", NULL,
        {
            &utest_maximal_heap_build,
            &ptest_maximal_heap_build,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table min_max_heap[] = {
    {
        "create", NULL,
        {
            &utest_min_max_heap_create,
            &ptest_min_max_heap_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_min_max_heap_destroy,
            &ptest_min_max_heap_destroy,
        },
    },
    {
        "empty_p", NULL,
        {
            &utest_min_max_heap_empty_p,
            &ptest_min_max_heap_empty_p,
        },
    },
    {
        "full_p", NULL,
        {
            &utest_min_max_heap_full_p,
            &ptest_min_max_heap_full_p,
        },
    },
    {
        "cleanup", NULL,
        {
            &utest_min_max_heap_cleanup,
            &ptest_min_max_heap_cleanup,
        },
    },
    {
        "get_min", NULL,
        {
            &utest_min_max_heap_get_min,
            &ptest_min_max_heap_get_min,
        },
    },
    {
        "get_max", NULL,
        {
            &utest_min_max_heap_get_max,
            &ptest_min_max_heap_get_max,
        },
    },
    {
        "insert", NULL,
        {
            &utest_min_max_heap_insert,
            &ptest_min_max_heap_insert,
        },
    },
    {
        "depth", NULL,
        {
            &utest_min_max_heap_depth,
            &ptest_min_max_heap_depth,
        },
    },
    {
        "remove_min", NULL,
        {
            &utest_min_max_heap_remove_min,
            &ptest_min_max_heap_remove_min,
        },
    },
    {
        "remove_max", NULL,
        {
            &utest_min_max_heap_remove_max,
            &ptest_min_max_heap_remove_max,
        },
    },
    {
        "remove", NULL,
        {
            &utest_min_max_heap_remove,
            &ptest_min_max_heap_remove,
        },
    },
    {
        "decrease_nice", NULL,
        {
            &utest_min_max_heap_decrease_nice,
            &ptest_min_max_heap_decrease_nice,
        },
    },
    {
        "increase_nice", NULL,
        {
            &utest_min_max_heap_increase_nice,
            &ptest_min_max_heap_increase_nice,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table leftist_heap[] = {
    {
        "struct_field", NULL,
        {
            &unit_test_leftist_heap_struct_field,
            &performance_test_leftist_heap_struct_field,
        },
    },
    {
        "create", NULL,
        {
            &unit_test_leftist_heap_create,
            &performance_test_leftist_heap_create,
        },
    },
    {
        "node_create", NULL,
        {
            &unit_test_leftist_heap_node_create,
            &performance_test_leftist_heap_node_create,
        },
    },
    {
        "destroy", NULL,
        {
            &unit_test_leftist_heap_destroy,
            &performance_test_leftist_heap_destroy,
        },
    },
    {
        "get_min", NULL,
        {
            &unit_test_leftist_heap_get_min,
            &performance_test_leftist_heap_get_min,
        },
    },
    {
        "insert", NULL,
        {
            &unit_test_leftist_heap_insert,
            &performance_test_leftist_heap_insert,
        },
    },
    {
        "merge", NULL,
        {
            &unit_test_leftist_heap_merge,
            &performance_test_leftist_heap_merge,
        },
    },
    {
        "remove_min", NULL,
        {
            &unit_test_leftist_heap_remove_min,
            &performance_test_leftist_heap_remove_min,
        },
    },
    {
        "remove_min_and_destroy", NULL,
        {
            &unit_test_leftist_heap_remove_min_and_destroy,
            &performance_test_leftist_heap_remove_min_and_destroy,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table sort_collection[] = {
    {
        "insertion", NULL,
        {
            &utest_insertion_sort,
            &ptest_insertion_sort,
        },
    },
    {
        "shell", NULL,
        {
            &utest_shell_sort,
            &ptest_shell_sort,
        },
    },
    {
        "heap", NULL,
        {
            &utest_heap_sort,
            &ptest_heap_sort,
        },
    },
    {
        "merge", NULL,
        {
            &utest_merge_sort,
            &ptest_merge_sort,
        },
    },
    {
        "quick", NULL,
        {
            &utest_quick_sort,
            &ptest_quick_sort,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table disjoint_set[] = {
    {
        "create", NULL,
        {
            &utest_disjoint_set_create,
            &ptest_disjoint_set_create,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_disjoint_set_destroy,
            &ptest_disjoint_set_destroy,
        },
    },
    {
        "find", NULL,
        {
            &utest_disjoint_set_find,
            &ptest_disjoint_set_find,
        },
    },
    {
        "union", NULL,
        {
            &utest_disjoint_set_union,
            &ptest_disjoint_set_union,
        },
    },
    {
        "equivalent_p", NULL,
        {
            &utest_disjoint_set_equivalent_p,
            &ptest_disjoint_set_equivalent_p,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table indirected_graph[] = {
    {
        "create", NULL,
        {
            &utest_indirected_graph_create,
            NULL,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_indirected_graph_destroy,
            NULL,
        },
    },
    {
        "link", NULL,
        {
            &utest_indirected_graph_link,
            NULL,
        },
    },
    {
        "edge_remove", NULL,
        {
            &utest_indirected_graph_edge_remove,
            NULL,
        },
    },
    {
        "vertex_remove", NULL,
        {
            &utest_indirected_graph_vertex_remove,
            NULL,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

static const struct test_layer_table directed_graph[] = {
    {
        "create", NULL,
        {
            &utest_directed_graph_create,
            NULL,
        },
    },
    {
        "destroy", NULL,
        {
            &utest_directed_graph_destroy,
            NULL,
        },
    },
    {
        "link", NULL,
        {
            &utest_directed_graph_link,
            NULL,
        },
    },
    {
        "edge_remove", NULL,
        {
            &utest_directed_graph_edge_remove,
            NULL,
        },
    },
    {
        "vertex_remove", NULL,
        {
            &utest_directed_graph_vertex_remove,
            NULL,
        },
    },
    {
        "topo_sort", NULL,
        {
            &utest_directed_graph_topo_sort,
            NULL,
        },
    },
    {
        "paths_find", NULL,
        {
            &utest_directed_graph_paths_find,
            NULL,
        },
    },
    {
        "dijkstra", NULL,
        {
            &utest_directed_graph_dijkstra,
            NULL,
        },
    },
    {NULL, NULL, {NULL, NULL},},
};

/*-----------------------------------------------------------------*/
/*-------------------------- END OF INTERFACE LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* IMPLEMENTATION LAYER OF LAYER TABLE ----------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table test_linked_list_implement[] = {
    {"single", single_linked_list_interface, {NULL, NULL},},
    {"doubly", doubly_linked_list_interface, {NULL, NULL},},
    {"skip",   skip_linked_list_interface,   {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,     NULL,                         {NULL, NULL},},
};

static const struct test_layer_table test_stack_implement[] = {
    {"array",  array_stack,  {NULL, NULL},},
    {"linked", linked_stack, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,     NULL,         {NULL, NULL},},
};

static const struct test_layer_table test_queue_implement[] = {
    {"array",      array_queue,      {NULL, NULL},},
    {"stacked",    stacked_queue,    {NULL, NULL},},
    {"doubly_end", doubly_end_queue, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,         NULL,             {NULL, NULL},},
};

static const struct test_layer_table test_tree_implement[] = {
    {"binary_search",  binary_search_tree,  {NULL, NULL},},
    {"avl",            avl_tree,            {NULL, NULL},},
    {"splay",          splay_tree,          {NULL, NULL},},
    {"binary_indexed", binary_indexed_tree, {NULL, NULL},},
    {"trie",           trie_tree,           {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,            NULL,                 {NULL, NULL},},
};

static const struct test_layer_table test_hash_implement[] = {
    {"separate_chain",  separate_chain_hash,  {NULL, NULL},},
    {"open_addressing", open_addressing_hash, {NULL, NULL},},
    {"bitmap",          bitmap,               {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,              NULL,                 {NULL, NULL},},
};

static const struct test_layer_table test_heap_implement[] = {
    {"minimal", minimal_heap, {NULL, NULL},},
    {"maximal", maximal_heap, {NULL, NULL},},
    {"min_max", min_max_heap, {NULL, NULL},},
    {"leftist", leftist_heap, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,      NULL,         {NULL, NULL},},
};

static const struct test_layer_table test_sort_implement[] = {
    {"sort", sort_collection, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,   NULL,            {NULL, NULL},},
};

static const struct test_layer_table test_set_implement[] = {
    {"disjoint", disjoint_set,    {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,       NULL,            {NULL, NULL},},
};

static const struct test_layer_table test_graph_implement[] = {
    {"indirected", indirected_graph, {NULL, NULL},},
    {"directed",   directed_graph,   {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,       NULL,               {NULL, NULL},},
};
/*-----------------------------------------------------------------*/
/*--------------------- END OF IMPLEMENTATION LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* CATEGORY LAYER OF LAYER TABLE ----------------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table test_category[] = {
    {"linked_list", test_linked_list_implement, {NULL, NULL},},
    {"stack",       test_stack_implement,       {NULL, NULL},},
    {"queue",       test_queue_implement,       {NULL, NULL},},
    {"tree",        test_tree_implement,        {NULL, NULL},},
    {"hash",        test_hash_implement,        {NULL, NULL},},
    {"heap",        test_heap_implement,        {NULL, NULL},},
    {"sort",        test_sort_implement,        {NULL, NULL},},
    {"set",         test_set_implement,         {NULL, NULL},},
    {"graph",       test_graph_implement,       {NULL, NULL},},
    /* END POINT OF CATEGORY */
    {NULL,          NULL,                       {NULL, NULL},}
};
/*-----------------------------------------------------------------*/
/*--------------------------- END OF CATEGORY LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/

#endif
