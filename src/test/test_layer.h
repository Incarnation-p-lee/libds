#ifndef TEST_LAYER_H
#define TEST_LAYER_H

static const struct test_layer_table single_linked_list_interface[] = {
    {"struct_field",            NULL, {&unit_test_single_linked_list_struct_field,
                                       &performance_test_single_linked_list_struct_field},},
    {"initial",                 NULL, {&unit_test_single_linked_list_initial, NULL},},
    {"create",                  NULL, {&unit_test_single_linked_list_create, NULL},},
    {"node_initial",            NULL, {&unit_test_single_linked_list_node_initial, NULL},},
    {"node_create",             NULL, {&unit_test_single_linked_list_node_create, NULL},},
    {"node_copy",               NULL, {&unit_test_single_linked_list_node_copy, NULL},},
    {"node_append",             NULL, {&unit_test_single_linked_list_node_append, NULL},},
    {"node_previous",           NULL, {&unit_test_single_linked_list_node_previous, NULL},},
    {"node_insert_before",      NULL, {&unit_test_single_linked_list_node_insert_before, NULL},},
    {"node_insert_after",       NULL, {&unit_test_single_linked_list_node_insert_after, NULL},},
    {"node_by_index",           NULL, {&unit_test_single_linked_list_node_by_index, NULL},},
    {"node_remove",             NULL, {&unit_test_single_linked_list_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_single_linked_list_node_remove_and_destroy, NULL},},
    {"contains_p",              NULL, {&unit_test_single_linked_list_contains_p, NULL},},
    {"serialize",               NULL, {&unit_test_single_linked_list_serialize, NULL},},
    {"iterate",                 NULL, {&unit_test_single_linked_list_iterate, NULL},},
    {"destroy",                 NULL, {&unit_test_single_linked_list_destroy, NULL},},
    {"length",                  NULL, {&unit_test_single_linked_list_length, NULL},},
    {"merge",                   NULL, {&unit_test_single_linked_list_merge, NULL},},
    {NULL,                      NULL, {NULL, NULL},},
};

static const struct test_layer_table doubly_linked_list_interface[] = {
    {"struct_field",            NULL, {&unit_test_doubly_linked_list_struct_field, NULL},},
    {"initial",                 NULL, {&unit_test_doubly_linked_list_initial, NULL},},
    {"create",                  NULL, {&unit_test_doubly_linked_list_create, NULL},},
    {"node_initial",            NULL, {&unit_test_doubly_linked_list_node_initial, NULL},},
    {"node_create",             NULL, {&unit_test_doubly_linked_list_node_create, NULL},},
    {"node_copy",               NULL, {&unit_test_doubly_linked_list_node_copy, NULL},},
    {"node_append",             NULL, {&unit_test_doubly_linked_list_node_append, NULL},},
    {"node_insert_before",      NULL, {&unit_test_doubly_linked_list_node_insert_before, NULL},},
    {"node_insert_after",       NULL, {&unit_test_doubly_linked_list_node_insert_after, NULL},},
    {"node_by_index",           NULL, {&unit_test_doubly_linked_list_node_by_index, NULL},},
    {"node_remove",             NULL, {&unit_test_doubly_linked_list_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_doubly_linked_list_node_remove_and_destroy, NULL},},
    {"contains_p",              NULL, {&unit_test_doubly_linked_list_contains_p, NULL},},
    {"serialize",               NULL, {&unit_test_doubly_linked_list_serialize, NULL},},
    {"iterate",                 NULL, {&unit_test_doubly_linked_list_iterate, NULL},},
    {"destroy",                 NULL, {&unit_test_doubly_linked_list_destroy, NULL},},
    {"length",                  NULL, {&unit_test_doubly_linked_list_length, NULL},},
    {"merge",                   NULL, {&unit_test_doubly_linked_list_merge, NULL},},
    {NULL,                      NULL, {NULL, NULL},},
};

static const struct test_layer_table skip_linked_list_interface[] = {
    {"struct_field",            NULL, {&unit_test_skip_linked_list_struct_field, NULL},},
    {"create",                  NULL, {&unit_test_skip_linked_list_create, NULL},},
    {"initial",                 NULL, {&unit_test_skip_linked_list_initial, NULL},},
    {"node_create",             NULL, {&unit_test_skip_linked_list_node_create, NULL},},
    {"node_initial",            NULL, {&unit_test_skip_linked_list_node_initial, NULL},},
    {"destroy",                 NULL, {&unit_test_skip_linked_list_destroy, NULL},},
    {"length",                  NULL, {&unit_test_skip_linked_list_length, NULL},},
    {"contains_p",              NULL, {&unit_test_skip_linked_list_contains_p, NULL},},
    {"node_insert",             NULL, {&unit_test_skip_linked_list_node_insert, NULL},},
    {"node_find_key",           NULL, {&unit_test_skip_linked_list_node_find_key, NULL},},
    {"node_by_index",           NULL, {&unit_test_skip_linked_list_node_by_index, NULL},},
    {"node_remove",             NULL, {&unit_test_skip_linked_list_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_skip_linked_list_node_remove_and_destroy, NULL},},
    {"iterate",                 NULL, {&unit_test_skip_linked_list_iterate, NULL},},
    {"merge",                   NULL, {&unit_test_skip_linked_list_merge, NULL},},
    {NULL,                      NULL, {NULL, NULL},},
};

static const struct test_layer_table array_stack[] = {
    {"struct_field", NULL, {&unit_test_array_stack_struct_field, NULL},},
    {"create",       NULL, {&unit_test_array_stack_create, NULL},},
    {"destroy",      NULL, {&unit_test_array_stack_destroy, NULL},},
    {"space_expand", NULL, {&unit_test_array_stack_space_expand, NULL},},
    {"space_rest",   NULL, {&unit_test_array_stack_space_rest, NULL},},
    {"full_p",       NULL, {&unit_test_array_stack_full_p, NULL},},
    {"capacity",     NULL, {&unit_test_array_stack_capacity, NULL},},
    {"push",         NULL, {&unit_test_array_stack_push, NULL},},
    {"pop",          NULL, {&unit_test_array_stack_pop, NULL},},
    {"empty_p",      NULL, {&unit_test_array_stack_empty_p, NULL},},
    {"cleanup",      NULL, {&unit_test_array_stack_cleanup, NULL},},
    {"iterate",      NULL, {&unit_test_array_stack_iterate, NULL},},
    {NULL,           NULL, {NULL, NULL},},
};

static const struct test_layer_table linked_stack[] = {
    {"struct_field", NULL, {&unit_test_linked_stack_struct_field, NULL},},
    {"create",       NULL, {&unit_test_linked_stack_create, NULL},},
    {"destroy",      NULL, {&unit_test_linked_stack_destroy, NULL},},
    {"space_expand", NULL, {&unit_test_linked_stack_space_expand, NULL},},
    {"space_rest",   NULL, {&unit_test_linked_stack_space_rest, NULL},},
    {"full_p",       NULL, {&unit_test_linked_stack_full_p, NULL},},
    {"capacity",     NULL, {&unit_test_linked_stack_capacity, NULL},},
    {"push",         NULL, {&unit_test_linked_stack_push, NULL},},
    {"pop",          NULL, {&unit_test_linked_stack_pop, NULL},},
    {"empty_p",      NULL, {&unit_test_linked_stack_empty_p, NULL},},
    {"cleanup",      NULL, {&unit_test_linked_stack_cleanup, NULL},},
    {"iterate",      NULL, {&unit_test_linked_stack_iterate, NULL},},
    {NULL,           NULL, {NULL, NULL},},
};

static const struct test_layer_table array_queue[] = {
    {"struct_field", NULL, {&unit_test_array_queue_struct_field, NULL},},
    {"create",       NULL, {&unit_test_array_queue_create, NULL},},
    {"destroy",      NULL, {&unit_test_array_queue_destroy, NULL},},
    {"space_expand", NULL, {&unit_test_array_queue_space_expand, NULL},},
    {"space_rest",   NULL, {&unit_test_array_queue_space_rest, NULL},},
    {"full_p",       NULL, {&unit_test_array_queue_full_p, NULL},},
    {"capacity",     NULL, {&unit_test_array_queue_capacity, NULL},},
    {"enter",        NULL, {&unit_test_array_queue_enter, NULL},},
    {"leave",        NULL, {&unit_test_array_queue_leave, NULL},},
    {"empty_p",      NULL, {&unit_test_array_queue_empty_p, NULL},},
    {"cleanup",      NULL, {&unit_test_array_queue_cleanup, NULL},},
    {"iterate",      NULL, {&unit_test_array_queue_iterate, NULL},},
    {NULL,           NULL, {NULL, NULL},},
};

static const struct test_layer_table stacked_queue[] = {
    {"struct_field", NULL, {&unit_test_stacked_queue_struct_field, NULL},},
    {"create",       NULL, {&unit_test_stacked_queue_create, NULL},},
    {"destroy",      NULL, {&unit_test_stacked_queue_destroy, NULL},},
    {"space_expand", NULL, {&unit_test_stacked_queue_space_expand, NULL},},
    {"space_rest",   NULL, {&unit_test_stacked_queue_space_rest, NULL},},
    {"full_p",       NULL, {&unit_test_stacked_queue_full_p, NULL},},
    {"capacity",     NULL, {&unit_test_stacked_queue_capacity, NULL},},
    {"enter",        NULL, {&unit_test_stacked_queue_enter, NULL},},
    {"leave",        NULL, {&unit_test_stacked_queue_leave, NULL},},
    {"empty_p",      NULL, {&unit_test_stacked_queue_empty_p, NULL},},
    {"cleanup",      NULL, {&unit_test_stacked_queue_cleanup, NULL},},
    {"iterate",      NULL, {&unit_test_stacked_queue_iterate, NULL},},
    {NULL,           NULL, {NULL, NULL},},
};

static const struct test_layer_table doubly_end_queue[] = {
    {"struct_field", NULL, {&unit_test_doubly_end_queue_struct_field, NULL},},
    {"create",       NULL, {&unit_test_doubly_end_queue_create, NULL},},
    {"destroy",      NULL, {&unit_test_doubly_end_queue_destroy, NULL},},
    {"length",       NULL, {&unit_test_doubly_end_queue_length, NULL},},
    {"empty_p",      NULL, {&unit_test_doubly_end_queue_empty_p, NULL},},
    {"head_enter",   NULL, {&unit_test_doubly_end_queue_head_enter, NULL},},
    {"head_leave",   NULL, {&unit_test_doubly_end_queue_head_leave, NULL},},
    {"tail_enter",   NULL, {&unit_test_doubly_end_queue_tail_enter, NULL},},
    {"tail_leave",   NULL, {&unit_test_doubly_end_queue_tail_leave, NULL},},
    {"cleanup",      NULL, {&unit_test_doubly_end_queue_cleanup, NULL},},
    {"iterate",      NULL, {&unit_test_doubly_end_queue_iterate, NULL},},
    {NULL,           NULL, {NULL, NULL},},
};

static const struct test_layer_table binary_search_tree[] = {
    {"struct_field",            NULL, {&unit_test_binary_search_tree_struct_field, NULL},},
    {"create",                  NULL, {&unit_test_binary_search_tree_create, NULL},},
    {"node_create",             NULL, {&unit_test_binary_search_tree_node_create, NULL},},
    {"initial",                 NULL, {&unit_test_binary_search_tree_initial, NULL},},
    {"node_initial",            NULL, {&unit_test_binary_search_tree_node_initial, NULL},},
    {"destroy",                 NULL, {&unit_test_binary_search_tree_destroy, NULL},},
    {"node_find",               NULL, {&unit_test_binary_search_tree_node_find, NULL},},
    {"node_find_min",           NULL, {&unit_test_binary_search_tree_node_find_min, NULL},},
    {"node_find_max",           NULL, {&unit_test_binary_search_tree_node_find_max, NULL},},
    {"height",                  NULL, {&unit_test_binary_search_tree_height, NULL},},
    {"node_contains_p",         NULL, {&unit_test_binary_search_tree_node_contains_p, NULL},},
    {"node_insert",             NULL, {&unit_test_binary_search_tree_node_insert, NULL},},
    {"node_remove",             NULL, {&unit_test_binary_search_tree_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_binary_search_tree_node_remove_and_destroy, NULL},},
    {"iterate",                 NULL, {&unit_test_binary_search_tree_iterate, NULL},},
    {NULL,                      NULL, {NULL, NULL},},
};

static const struct test_layer_table avl_tree[] = {
    {"struct_field",            NULL, {&unit_test_avl_tree_struct_field, NULL},},
    {"create",                  NULL, {&unit_test_avl_tree_create, NULL},},
    {"node_create",             NULL, {&unit_test_avl_tree_node_create, NULL},},
    {"initial",                 NULL, {&unit_test_avl_tree_initial, NULL},},
    {"node_initial",            NULL, {&unit_test_avl_tree_node_initial, NULL},},
    {"destroy",                 NULL, {&unit_test_avl_tree_destroy, NULL},},
    {"node_find",               NULL, {&unit_test_avl_tree_node_find, NULL},},
    {"node_find_min",           NULL, {&unit_test_avl_tree_node_find_min, NULL},},
    {"node_find_max",           NULL, {&unit_test_avl_tree_node_find_max, NULL},},
    {"node_contains_p",         NULL, {&unit_test_avl_tree_node_contains_p, NULL},},
    {"balanced_p",              NULL, {&unit_test_avl_tree_balanced_p, NULL},},
    {"node_insert",             NULL, {&unit_test_avl_tree_node_insert, NULL},},
    {"node_remove",             NULL, {&unit_test_avl_tree_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_avl_tree_node_remove_and_destroy, NULL},},
    {"iterate",                 NULL, {&unit_test_avl_tree_iterate, NULL},},
    {NULL,                      NULL, {NULL,},},
};

static const struct test_layer_table splay_tree[] = {
    {"struct_field",            NULL, {&unit_test_splay_tree_struct_field, NULL},},
    {"create",                  NULL, {&unit_test_splay_tree_create, NULL},},
    {"node_create",             NULL, {&unit_test_splay_tree_node_create, NULL},},
    {"initial",                 NULL, {&unit_test_splay_tree_initial, NULL},},
    {"node_initial",            NULL, {&unit_test_splay_tree_node_initial, NULL},},
    {"destroy",                 NULL, {&unit_test_splay_tree_destroy, NULL},},
    {"node_find",               NULL, {&unit_test_splay_tree_node_find, NULL},},
    {"node_find_min",           NULL, {&unit_test_splay_tree_node_find_min, NULL},},
    {"node_find_max",           NULL, {&unit_test_splay_tree_node_find_max, NULL},},
    {"height",                  NULL, {&unit_test_splay_tree_height, NULL},},
    {"node_contains_p",         NULL, {&unit_test_splay_tree_node_contains_p, NULL},},
    {"node_insert",             NULL, {&unit_test_splay_tree_node_insert, NULL},},
    {"node_remove",             NULL, {&unit_test_splay_tree_node_remove, NULL},},
    {"node_remove_and_destroy", NULL, {&unit_test_splay_tree_node_remove_and_destroy, NULL},},
    {"iterate",                 NULL, {&unit_test_splay_tree_iterate, NULL},},
    {NULL,                      NULL, {NULL,},},
};

static const struct test_layer_table separate_chain_hash[] = {
    {"struct_field",          NULL, {&unit_test_separate_chain_hash_struct_field, NULL},},
    {"create",                NULL, {&unit_test_separate_chain_hash_create, NULL},},
    {"destroy",               NULL, {&unit_test_separate_chain_hash_destroy, NULL},},
    {"load_factor_calculate", NULL, {&unit_test_separate_chain_hash_load_factor_calculate, NULL},},
    {"insert",                NULL, {&unit_test_separate_chain_hash_insert, NULL},},
    {"remove",                NULL, {&unit_test_separate_chain_hash_remove, NULL},},
    {"find",                  NULL, {&unit_test_separate_chain_hash_find, NULL},},
    {"rehashing",             NULL, {&unit_test_separate_chain_hash_rehashing, NULL},},
    {NULL,                    NULL, {NULL, NULL},},
};

static const struct test_layer_table open_addressing_hash[] = {
    {"struct_field",          NULL, {&unit_test_open_addressing_hash_struct_field, NULL},},
    {"create",                NULL, {&unit_test_open_addressing_hash_create, NULL},},
    {"destroy",               NULL, {&unit_test_open_addressing_hash_destroy, NULL},},
    {"load_factor_calculate", NULL, {&unit_test_open_addressing_hash_load_factor_calculate, NULL},},
    {"insert",                NULL, {&unit_test_open_addressing_hash_insert, NULL},},
    {"remove",                NULL, {&unit_test_open_addressing_hash_remove, NULL},},
    {"find",                  NULL, {&unit_test_open_addressing_hash_find, NULL},},
    {"rehashing",             NULL, {&unit_test_open_addressing_hash_rehashing, NULL},},
    {NULL,                    NULL, {NULL, NULL},},
};

static const struct test_layer_table minimal_heap[] = {
    {"struct_field",                NULL, {&unit_test_minimal_heap_struc_field, NULL},},
    {"create",                      NULL, {&unit_test_minimal_heap_create, NULL},},
    {"destroy",                     NULL, {&unit_test_minimal_heap_destroy, NULL},},
    {"empty_p",                     NULL, {&unit_test_minimal_heap_empty_p, NULL},},
    {"full_p",                      NULL, {&unit_test_minimal_heap_full_p, NULL},},
    {"cleanup",                     NULL, {&unit_test_minimal_heap_cleanup, NULL},},
    {"node_find",                   NULL, {&unit_test_minimal_heap_node_find, NULL},},
    {"node_find_min",               NULL, {&unit_test_minimal_heap_node_find_min, NULL},},
    {"node_insert",                 NULL, {&unit_test_minimal_heap_node_insert, NULL},},
    {"node_remove_min",             NULL, {&unit_test_minimal_heap_node_remove_min, NULL},},
    {"node_remove_min_and_destroy", NULL, {&unit_test_minimal_heap_node_remove_min_and_destroy, NULL},},
    {"node_remove",                 NULL, {&unit_test_minimal_heap_node_remove, NULL},},
    {"node_remove_and_destroy",     NULL, {&unit_test_minimal_heap_node_remove_and_destroy, NULL},},
    {"node_decrease_nice",          NULL, {&unit_test_minimal_heap_node_decrease_nice, NULL},},
    {"node_increase_nice",          NULL, {&unit_test_minimal_heap_node_increase_nice, NULL},},
    {NULL,                          NULL, {NULL, NULL},},
};

static const struct test_layer_table maximal_heap[] = {
    {"struct_field",                NULL, {&unit_test_maximal_heap_struc_field, NULL},},
    {"create",                      NULL, {&unit_test_maximal_heap_create, NULL},},
    {"destroy",                     NULL, {&unit_test_maximal_heap_destroy, NULL},},
    {"empty_p",                     NULL, {&unit_test_maximal_heap_empty_p, NULL},},
    {"full_p",                      NULL, {&unit_test_maximal_heap_full_p, NULL},},
    {"cleanup",                     NULL, {&unit_test_maximal_heap_cleanup, NULL},},
    {"node_find",                   NULL, {&unit_test_maximal_heap_node_find, NULL},},
    {"node_find_max",               NULL, {&unit_test_maximal_heap_node_find_max, NULL},},
    {"node_insert",                 NULL, {&unit_test_maximal_heap_node_insert, NULL},},
    {"node_remove_max",             NULL, {&unit_test_maximal_heap_node_remove_max, NULL},},
    {"node_remove_max_and_destroy", NULL, {&unit_test_maximal_heap_node_remove_max_and_destroy, NULL},},
    {"node_remove",                 NULL, {&unit_test_maximal_heap_node_remove, NULL},},
    {"node_remove_and_destroy",     NULL, {&unit_test_maximal_heap_node_remove_and_destroy, NULL},},
    {"node_decrease_nice",          NULL, {&unit_test_maximal_heap_node_decrease_nice, NULL},},
    {"node_increase_nice",          NULL, {&unit_test_maximal_heap_node_increase_nice, NULL},},
    {NULL,                          NULL, {NULL, NULL},},
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
    {"binary_search", binary_search_tree, {NULL, NULL},},
    {"avl",           avl_tree,           {NULL, NULL},},
    {"splay",         splay_tree,         {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,            NULL,               {NULL, NULL},},
};

static const struct test_layer_table test_hash_implement[] = {
    {"separate_chain",  separate_chain_hash,  {NULL, NULL},},
    {"open_addressing", open_addressing_hash, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,              NULL,                 {NULL, NULL},},
};

static const struct test_layer_table test_heap_implement[] = {
    {"minimal", minimal_heap, {NULL, NULL},},
    {"maximal", maximal_heap, {NULL, NULL},},
    /* END POINT OF IMPLEMENT */
    {NULL,      NULL,         {NULL, NULL},},
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
    /* END POINT OF CATEGORY */
    {NULL,          NULL,                       {NULL, NULL},}
};
/*-----------------------------------------------------------------*/
/*--------------------------- END OF CATEGORY LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/

#endif
