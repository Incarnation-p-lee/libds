/*-----------------------------------------------------------------*/
/* INTERFACE LAYER OF LAYER TABLE ---------------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table single_linked_list_interface[] = {
    {"struct_field",       {&unit_test_single_linked_list_struct_field,},},
    {"initial",            {&unit_test_single_linked_list_initial,},},
    {"create",             {&unit_test_single_linked_list_create,},},
    {"generate",           {&unit_test_single_linked_list_generate,},},
    {"node_initial",       {&unit_test_single_linked_list_node_initial,},},
    {"node_create",        {&unit_test_single_linked_list_node_create,},},
    {"node_copy",          {&unit_test_single_linked_list_node_copy,},},
    {"node_append",        {&unit_test_single_linked_list_node_append,},},
    {"node_previous",      {&unit_test_single_linked_list_node_previous,},},
    {"node_insert_before", {&unit_test_single_linked_list_node_insert_before,},},
    {"node_insert_after",  {&unit_test_single_linked_list_node_insert_after,},},
    {"node_by_index",  {&unit_test_single_linked_list_node_by_index,},},
    {"node_exchange",      {&unit_test_single_linked_list_node_exchange,},},
    {"node_remove",        {&unit_test_single_linked_list_node_remove,},},
    {"node_lazy_remove",   {&unit_test_single_linked_list_node_lazy_remove,},},
    {"contains_p",         {&unit_test_single_linked_list_contains_p,},},
    {"serialize",          {&unit_test_single_linked_list_serialize,},},
    {"iterate",            {&unit_test_single_linked_list_iterate,},},
    {"destroy",            {&unit_test_single_linked_list_destroy,},},
    {"length",             {&unit_test_single_linked_list_length,},},
    {"join",               {&unit_test_single_linked_list_merge,},},
    {NULL,                 {NULL,},},
};

static const struct test_layer_table doubly_linked_list_interface[] = {
    {"struct_field",       {&unit_test_doubly_linked_list_struct_field,},},
    {"initial",            {&unit_test_doubly_linked_list_initial,},},
    {"create",             {&unit_test_doubly_linked_list_create,},},
    {"generate",           {&unit_test_doubly_linked_list_generate,},},
    {"node_initial",       {&unit_test_doubly_linked_list_node_initial,},},
    {"node_create",        {&unit_test_doubly_linked_list_node_create,},},
    {"node_copy",          {&unit_test_doubly_linked_list_node_copy,},},
    {"node_append",        {&unit_test_doubly_linked_list_node_append,},},
    {"node_insert_before", {&unit_test_doubly_linked_list_node_insert_before,},},
    {"node_insert_after",  {&unit_test_doubly_linked_list_node_insert_after,},},
    {"node_by_index",  {&unit_test_doubly_linked_list_node_by_index,},},
    {"node_exchange",      {&unit_test_doubly_linked_list_node_exchange,},},
    {"node_remove",        {&unit_test_doubly_linked_list_node_remove,},},
    {"node_lazy_remove",   {&unit_test_doubly_linked_list_node_lazy_remove,},},
    {"contains_p",         {&unit_test_doubly_linked_list_contains_p,},},
    {"serialize",          {&unit_test_doubly_linked_list_serialize,},},
    {"iterate",            {&unit_test_doubly_linked_list_iterate,},},
    {"destroy",            {&unit_test_doubly_linked_list_destroy,},},
    {"length",             {&unit_test_doubly_linked_list_length,},},
    {"join",               {&unit_test_doubly_linked_list_merge,},},
    {NULL,                 {NULL,},},
};

static const struct test_layer_table array_stack[] = {
    {"struct_field", {&unit_test_array_stack_struct_field,},},
    {"create",       {&unit_test_array_stack_create,},},
    {"destroy",      {&unit_test_array_stack_destroy,},},
    {"space_expand", {&unit_test_array_stack_space_expand,},},
    {"space_rest",   {&unit_test_array_stack_space_rest,},},
    {"full_p",       {&unit_test_array_stack_full_p,},},
    {"capacity",     {&unit_test_array_stack_capacity,},},
    {"push",         {&unit_test_array_stack_push,},},
    {"pop",          {&unit_test_array_stack_pop,},},
    {"empty_p",      {&unit_test_array_stack_empty_p,},},
    {"cleanup",      {&unit_test_array_stack_cleanup,},},
    {"iterate",      {&unit_test_array_stack_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table linked_stack[] = {
    {"struct_field", {&unit_test_linked_stack_struct_field,},},
    {"create",       {&unit_test_linked_stack_create,},},
    {"destroy",      {&unit_test_linked_stack_destroy,},},
    {"space_expand", {&unit_test_linked_stack_space_expand,},},
    {"space_rest",   {&unit_test_linked_stack_space_rest,},},
    {"full_p",       {&unit_test_linked_stack_full_p,},},
    {"capacity",     {&unit_test_linked_stack_capacity,},},
    {"push",         {&unit_test_linked_stack_push,},},
    {"pop",          {&unit_test_linked_stack_pop,},},
    {"empty_p",      {&unit_test_linked_stack_empty_p,},},
    {"cleanup",      {&unit_test_linked_stack_cleanup,},},
    {"iterate",      {&unit_test_linked_stack_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table array_queue[] = {
    {"struct_field", {&unit_test_array_queue_struct_field,},},
    {"create",       {&unit_test_array_queue_create,},},
    {"destroy",      {&unit_test_array_queue_destroy,},},
    {"space_expand", {&unit_test_array_queue_space_expand,},},
    {"space_rest",   {&unit_test_array_queue_space_rest,},},
    {"full_p",       {&unit_test_array_queue_full_p,},},
    {"capacity",     {&unit_test_array_queue_capacity,},},
    {"enter",        {&unit_test_array_queue_enter,},},
    {"leave",        {&unit_test_array_queue_leave,},},
    {"empty_p",      {&unit_test_array_queue_empty_p,},},
    {"cleanup",      {&unit_test_array_queue_cleanup,},},
    {"iterate",      {&unit_test_array_queue_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table stacked_queue[] = {
    {"struct_field", {&unit_test_stacked_queue_struct_field,},},
    {"create",       {&unit_test_stacked_queue_create,},},
    {"destroy",      {&unit_test_stacked_queue_destroy,},},
    {"space_expand", {&unit_test_stacked_queue_space_expand,},},
    {"space_rest",   {&unit_test_stacked_queue_space_rest,},},
    {"full_p",       {&unit_test_stacked_queue_full_p,},},
    {"capacity",     {&unit_test_stacked_queue_capacity,},},
    {"enter",        {&unit_test_stacked_queue_enter,},},
    {"leave",        {&unit_test_stacked_queue_leave,},},
    {"empty_p",      {&unit_test_stacked_queue_empty_p,},},
    {"cleanup",      {&unit_test_stacked_queue_cleanup,},},
    {"iterate",      {&unit_test_stacked_queue_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table doubly_end_queue[] = {
    {"struct_field", {&unit_test_doubly_end_queue_struct_field,},},
    {"create",       {&unit_test_doubly_end_queue_create,},},
    {"destroy",      {&unit_test_doubly_end_queue_destroy,},},
    {"length",       {&unit_test_doubly_end_queue_length,},},
    {"empty_p",      {&unit_test_doubly_end_queue_empty_p,},},
    {"head_enter",   {&unit_test_doubly_end_queue_head_enter,},},
    {"head_leave",   {&unit_test_doubly_end_queue_head_leave,},},
    {"tail_enter",   {&unit_test_doubly_end_queue_tail_enter,},},
    {"tail_leave",   {&unit_test_doubly_end_queue_tail_leave,},},
    {"cleanup",      {&unit_test_doubly_end_queue_cleanup,},},
    {"iterate",      {&unit_test_doubly_end_queue_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table binary_search_tree[] = {
    {"struct_field",   {&unit_test_binary_search_tree_struct_field,},},
    {"create",         {&unit_test_binary_search_tree_create,},},
    {"node_create",    {&unit_test_binary_search_tree_node_create,},},
    {"initial",        {&unit_test_binary_search_tree_initial,},},
    {"node_initial",   {&unit_test_binary_search_tree_node_initial,},},
    {"destroy",        {&unit_test_binary_search_tree_destroy,},},
    {"node_find",      {&unit_test_binary_search_tree_node_find,},},
    {"node_find_min",  {&unit_test_binary_search_tree_node_find_min,},},
    {"node_find_max",  {&unit_test_binary_search_tree_node_find_max,},},
    {"height",         {&unit_test_binary_search_tree_height,},},
    {"node_contain_p", {&unit_test_binary_search_tree_node_contain_p,},},
    {"node_insert",    {&unit_test_binary_search_tree_node_insert,},},
    {"node_remove",    {&unit_test_binary_search_tree_node_remove,},},
    {"iterate",        {&unit_test_binary_search_tree_iterate,},},
    {NULL,             {NULL,},},
};

static const struct test_layer_table avl_tree[] = {
    {"struct_field",   {&unit_test_avl_tree_struct_field,},},
    {"create",         {&unit_test_avl_tree_create,},},
    {"node_create",    {&unit_test_avl_tree_node_create,},},
    {"initial",        {&unit_test_avl_tree_initial,},},
    {"node_initial",   {&unit_test_avl_tree_node_initial,},},
    {"destroy",        {&unit_test_avl_tree_destroy,},},
    {"node_find",      {&unit_test_avl_tree_node_find,},},
    {"node_find_min",  {&unit_test_avl_tree_node_find_min,},},
    {"node_find_max",  {&unit_test_avl_tree_node_find_max,},},
    {"node_contain_p", {&unit_test_avl_tree_node_contain_p,},},
    {"balanced_p",     {&unit_test_avl_tree_balanced_p,},},
    {"node_insert",    {&unit_test_avl_tree_node_insert,},},
    {"node_remove",    {&unit_test_avl_tree_node_remove,},},
    {"iterate",        {&unit_test_avl_tree_iterate,},},
    {NULL,             {NULL,},},
};

static const struct test_layer_table splay_tree[] = {
    {"struct_field",   {&unit_test_splay_tree_struct_field,},},
    {"create",         {&unit_test_splay_tree_create,},},
    {"node_create",    {&unit_test_splay_tree_node_create,},},
    {"initial",        {&unit_test_splay_tree_initial,},},
    {"node_initial",   {&unit_test_splay_tree_node_initial,},},
    {"destroy",        {&unit_test_splay_tree_destroy,},},
    {"node_find",      {&unit_test_splay_tree_node_find,},},
    {"node_find_min",  {&unit_test_splay_tree_node_find_min,},},
    {"node_find_max",  {&unit_test_splay_tree_node_find_max,},},
    {"height",         {&unit_test_splay_tree_height,},},
    {"node_contain_p", {&unit_test_splay_tree_node_contain_p,},},
    {"node_insert",    {&unit_test_splay_tree_node_insert,},},
    {"node_remove",    {&unit_test_splay_tree_node_remove,},},
    {"iterate",        {&unit_test_splay_tree_iterate,},},
    {NULL,             {NULL,},},
};

static const struct test_layer_table separate_chain_hash[] = {
    {"struct_field",          {&unit_test_separate_chain_hash_struct_field,},},
    {"create",                {&unit_test_separate_chain_hash_create,},},
    {"destroy",               {&unit_test_separate_chain_hash_destroy,},},
    {"load_factor_calculate", {&unit_test_separate_chain_hash_load_factor_calculate,},},
    {"insert",                {&unit_test_separate_chain_hash_insert,},},
    {"remove",                {&unit_test_separate_chain_hash_remove,},},
    {"find",                  {&unit_test_separate_chain_hash_find,},},
    {"rehashing",             {&unit_test_separate_chain_hash_rehashing,},},
    {NULL,                    {NULL,},},
};

static const struct test_layer_table open_addressing_hash[] = {
    {"struct_field",          {&unit_test_open_addressing_hash_struct_field,},},
    {"create",                {&unit_test_open_addressing_hash_create,},},
    {"destroy",               {&unit_test_open_addressing_hash_destroy,},},
    {"load_factor_calculate", {&unit_test_open_addressing_hash_load_factor_calculate,},},
    {"insert",                {&unit_test_open_addressing_hash_insert,},},
    {"remove",                {&unit_test_open_addressing_hash_remove,},},
    {"find",                  {&unit_test_open_addressing_hash_find,},},
    {"rehashing",             {&unit_test_open_addressing_hash_rehashing,},},
    {NULL,                    {NULL,},},
};

static const struct test_layer_table minimal_heap[] = {
    {"struct_field",          {&unit_test_minimal_heap_struc_field,},},
    {"create",                {&unit_test_minimal_heap_create,},},
    // {"destroy",               {&unit_test_open_addressing_hash_destroy,},},
    // {"load_factor_calculate", {&unit_test_open_addressing_hash_load_factor_calculate,},},
    // {"insert",                {&unit_test_open_addressing_hash_insert,},},
    // {"remove",                {&unit_test_open_addressing_hash_remove,},},
    // {"find",                  {&unit_test_open_addressing_hash_find,},},
    // {"rehashing",             {&unit_test_open_addressing_hash_rehashing,},},
    {NULL,                    {NULL,},},
};
/*-----------------------------------------------------------------*/
/*-------------------------- END OF INTERFACE LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* IMPLEMENTATION LAYER OF LAYER TABLE ----------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table unit_test_linked_list_implement[] = {
    {"single", {single_linked_list_interface,},},
    {"doubly", {doubly_linked_list_interface,},},
    /* END POINT OF IMPLEMENT */
    {NULL,     {NULL,},},
};

static const struct test_layer_table unit_test_stack_implement[] = {
    {"array",  {array_stack,},},
    {"linked", {linked_stack,},},
    /* END POINT OF IMPLEMENT */
    {NULL,     {NULL,},},
};

static const struct test_layer_table unit_test_queue_implement[] = {
    {"array",      {array_queue,},},
    {"stacked",    {stacked_queue},},
    {"doubly_end", {doubly_end_queue,},},
    /* END POINT OF IMPLEMENT */
    {NULL,         {NULL,},},
};

static const struct test_layer_table unit_test_tree_implement[] = {
    {"binary_search", {binary_search_tree,},},
    {"avl",           {avl_tree,},},
    {"splay",         {splay_tree,},},
    /* END POINT OF IMPLEMENT */
    {NULL,            {NULL,},},
};

static const struct test_layer_table unit_test_hash_implement[] = {
    {"separate_chain",  {separate_chain_hash,},},
    {"open_addressing", {open_addressing_hash,},},
    /* END POINT OF IMPLEMENT */
    {NULL,             {NULL,},},
};

static const struct test_layer_table unit_test_heap_implement[] = {
    {"minimal_heap",  {minimal_heap,},},
    // {"open_addressing", {open_addressing_hash,},},
    /* END POINT OF IMPLEMENT */
    {NULL,             {NULL,},},
};
/*-----------------------------------------------------------------*/
/*--------------------- END OF IMPLEMENTATION LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* CATEGORY LAYER OF LAYER TABLE ----------------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table unit_test_category[] = {
    {"linked_list", {unit_test_linked_list_implement,},},
    {"stack",       {unit_test_stack_implement,},},
    {"queue",       {unit_test_queue_implement,},},
    {"tree",        {unit_test_tree_implement,},},
    {"hash",        {unit_test_hash_implement,},},
    {"heap",        {unit_test_heap_implement,},},
    /* END POINT OF CATEGORY */
    {NULL,          {NULL,},}
};
/*-----------------------------------------------------------------*/
/*--------------------------- END OF CATEGORY LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/
