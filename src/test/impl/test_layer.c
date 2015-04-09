/*-----------------------------------------------------------------*/
/* INTERFACE LAYER OF LAYER TABLE ---------------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table single_linked_list_interface[] = {
    {"initial",            {&test_single_linked_list_initial,},},
    {"create",             {&test_single_linked_list_create,},},
    {"generate",           {&test_single_linked_list_generate,},},
    {"node_initial",       {&test_single_linked_list_node_initial,},},
    {"node_create",        {&test_single_linked_list_node_create,},},
    {"node_set_val",       {&test_single_linked_list_node_set_val,},},
    {"node_get_val",       {&test_single_linked_list_node_get_val,},},
    {"node_append",        {&test_single_linked_list_node_append,},},
    {"node_next",          {&test_single_linked_list_node_next,},},
    {"node_previous",      {&test_single_linked_list_node_previous,},},
    {"node_insert_before", {&test_single_linked_list_node_insert_before,},},
    {"node_insert_after",  {&test_single_linked_list_node_insert_after,},},
    {"node_get_by_index",  {&test_single_linked_list_node_get_by_index,},},
    {"node_exchange",      {&test_single_linked_list_node_exchange,},},
    {"node_remove",        {&test_single_linked_list_node_remove,},},
    {"node_lazy_remove",   {&test_single_linked_list_node_lazy_remove,},},
    {"contains_p",         {&test_single_linked_list_contains_p,},},
    {"serialize",          {&test_single_linked_list_serialize,},},
    {"iterate",            {&test_single_linked_list_iterate,},},
    {"destroy",            {&test_single_linked_list_destroy,},},
    {"length",             {&test_single_linked_list_length,},},
    {"join",               {&test_single_linked_list_join,},},
    {NULL,                 {NULL,},},
};

static const struct test_layer_table doubly_linked_list_interface[] = {
    {"initial",            {&test_doubly_linked_list_initial,},},
    {"create",             {&test_doubly_linked_list_create,},},
    {"generate",           {&test_doubly_linked_list_generate,},},
    {"node_initial",       {&test_doubly_linked_list_node_initial,},},
    {"node_create",        {&test_doubly_linked_list_node_create,},},
    {"node_set_val",       {&test_doubly_linked_list_node_set_val,},},
    {"node_get_val",       {&test_doubly_linked_list_node_get_val,},},
    {"node_append",        {&test_doubly_linked_list_node_append,},},
    {"node_next",          {&test_doubly_linked_list_node_next,},},
    {"node_previous",      {&test_doubly_linked_list_node_previous,},},
    {"node_insert_before", {&test_doubly_linked_list_node_insert_before,},},
    {"node_insert_after",  {&test_doubly_linked_list_node_insert_after,},},
    {"node_get_by_index",  {&test_doubly_linked_list_node_get_by_index,},},
    {"node_exchange",      {&test_doubly_linked_list_node_exchange,},},
    {"node_remove",        {&test_doubly_linked_list_node_remove,},},
    {"node_lazy_remove",   {&test_doubly_linked_list_node_lazy_remove,},},
    {"contains_p",         {&test_doubly_linked_list_contains_p,},},
    {"serialize",          {&test_doubly_linked_list_serialize,},},
    {"iterate",            {&test_doubly_linked_list_iterate,},},
    {"destroy",            {&test_doubly_linked_list_destroy,},},
    {"length",             {&test_doubly_linked_list_length,},},
    {"join",               {&test_doubly_linked_list_join,},},
    {NULL,                 {NULL,},},
};

static const struct test_layer_table array_stack[] = {
    {"create",       {&test_array_stack_create,},},
    {"destroy",      {&test_array_stack_destroy,},},
    {"space_expand", {&test_array_stack_space_expand,},},
    {"space_rest",   {&test_array_stack_space_rest,},},
    {"full_p",       {&test_array_stack_full_p,},},
    {"capacity",     {&test_array_stack_capacity,},},
    {"push",         {&test_array_stack_push,},},
    {"pop",          {&test_array_stack_pop,},},
    {"empty_p",      {&test_array_stack_empty_p,},},
    {"cleanup",      {&test_array_stack_cleanup,},},
    {"iterate",      {&test_array_stack_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table linked_stack[] = {
    {"create",       {&test_linked_stack_create,},},
    {"destroy",      {&test_linked_stack_destroy,},},
    {"space_expand", {&test_linked_stack_space_expand,},},
    {"space_rest",   {&test_linked_stack_space_rest,},},
    {"full_p",       {&test_linked_stack_full_p,},},
    {"capacity",     {&test_linked_stack_capacity,},},
    {"push",         {&test_linked_stack_push,},},
    {"pop",          {&test_linked_stack_pop,},},
    {"empty_p",      {&test_linked_stack_empty_p,},},
    {"cleanup",      {&test_linked_stack_cleanup,},},
    {"iterate",      {&test_linked_stack_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table array_queue[] = {
    {"create",       {&test_array_queue_create,},},
    {"destroy",      {&test_array_queue_destroy,},},
    {"space_expand", {&test_array_queue_space_expand,},},
    {"space_rest",   {&test_array_queue_space_rest,},},
    {"full_p",       {&test_array_queue_full_p,},},
    {"capacity",     {&test_array_queue_capacity,},},
    {"enter",        {&test_array_queue_enter,},},
    {"leave",        {&test_array_queue_leave,},},
    {"empty_p",      {&test_array_queue_empty_p,},},
    {"cleanup",      {&test_array_queue_cleanup,},},
    {"iterate",      {&test_array_queue_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table stacked_queue[] = {
    {"create",       {&test_stacked_queue_create,},},
    {"destroy",      {&test_stacked_queue_destroy,},},
    {"space_expand", {&test_stacked_queue_space_expand,},},
    {"space_rest",   {&test_stacked_queue_space_rest,},},
    {"full_p",       {&test_stacked_queue_full_p,},},
    {"capacity",     {&test_stacked_queue_capacity,},},
    {"enter",        {&test_stacked_queue_enter,},},
    {"leave",        {&test_stacked_queue_leave,},},
    {"empty_p",      {&test_stacked_queue_empty_p,},},
    {"cleanup",      {&test_stacked_queue_cleanup,},},
    {"iterate",      {&test_stacked_queue_iterate,},},
    {NULL,           {NULL,},},
};

static const struct test_layer_table doubly_end_queue[] = {
    {"create",     {&test_doubly_end_queue_create,},},
    {"destroy",    {&test_doubly_end_queue_destroy,},},
    {"length",     {&test_doubly_end_queue_length,},},
    {"empty_p",    {&test_doubly_end_queue_empty_p,},},
    {"head_enter", {&test_doubly_end_queue_head_enter,},},
    {"head_leave", {&test_doubly_end_queue_head_leave,},},
    {"tail_enter", {&test_doubly_end_queue_tail_enter,},},
    {"tail_leave", {&test_doubly_end_queue_tail_leave,},},
    {"cleanup",    {&test_doubly_end_queue_cleanup,},},
    {"iterate",    {&test_doubly_end_queue_iterate,},},
    {NULL,         {NULL,},},
};

static const struct test_layer_table binary_search_tree[] = {
    {"create",         {&test_binary_search_tree_create,},},
    {"node_create",    {&test_binary_search_tree_node_create,},},
    {"initial",        {&test_binary_search_tree_initial,},},
    {"node_initial",   {&test_binary_search_tree_node_initial,},},
    {"destroy",        {&test_binary_search_tree_destroy,},},
    {"node_find",      {&test_binary_search_tree_node_find,},},
    {"node_find_min",  {&test_binary_search_tree_node_find_min,},},
    {"node_find_max",  {&test_binary_search_tree_node_find_max,},},
    {"height",         {&test_binary_search_tree_height,},},
    {"node_contain_p", {&test_binary_search_tree_node_contain_p,},},
    {"node_insert",    {&test_binary_search_tree_node_insert,},},
    {"node_remove",    {&test_binary_search_tree_node_remove,},},
    {"iterate",        {&test_binary_search_tree_iterate,},},
    {NULL,             {NULL,},},
};

static const struct test_layer_table avl_tree[] = {
    {"create",         {&test_avl_tree_create,},},
    {"node_create",    {&test_avl_tree_node_create,},},
    {"initial",        {&test_avl_tree_initial,},},
    {"node_initial",   {&test_avl_tree_node_initial,},},
    {"destroy",        {&test_avl_tree_destroy,},},
    {"node_find",      {&test_avl_tree_node_find,},},
    {"node_find_min",  {&test_avl_tree_node_find_min,},},
    {"node_find_max",  {&test_avl_tree_node_find_max,},},
    {"height",         {&test_avl_tree_height,},},
    {"node_contain_p", {&test_avl_tree_node_contain_p,},},
    {"balanced_p",     {&test_avl_tree_balanced_p,},},
    {"node_insert",    {&test_avl_tree_node_insert,},},
    // {"node_remove", {   &test_avl_tree_node_remove, NULL,},
    {"iterate",        {&test_avl_tree_iterate,},},
    {NULL,             {NULL,},},
};
/*-----------------------------------------------------------------*/
/*-------------------------- END OF INTERFACE LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* IMPLEMENTATION LAYER OF LAYER TABLE ----------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table linked_list_implement[] = {
    {"single", {single_linked_list_interface,},},
    {"doubly", {doubly_linked_list_interface,},},
    /* END POINT OF IMPLEMENT */
    {NULL,     {NULL,},},
};

static const struct test_layer_table stack_implement[] = {
    {"array",  {array_stack,},},
    {"linked", {linked_stack,},},
    /* END POINT OF IMPLEMENT */
    {NULL,     {NULL,},},
};

static const struct test_layer_table queue_implement[] = {
    {"array",      {array_queue,},},
    {"stacked",    {stacked_queue},},
    {"doubly_end", {doubly_end_queue,},},
    /* END POINT OF IMPLEMENT */
    {NULL,         {NULL,},},
};

static const struct test_layer_table tree_implement[] = {
    {"binary_search", {binary_search_tree,},},
    {"avl", {avl_tree,},},
    /* END POINT OF IMPLEMENT */
    {NULL,     {NULL,},},
};
/*-----------------------------------------------------------------*/
/*--------------------- END OF IMPLEMENTATION LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/
/* CATEGORY LAYER OF LAYER TABLE ----------------------------------*/
/*-----------------------------------------------------------------*/
static const struct test_layer_table unit_test_category[] = {
    {"linked_list", {linked_list_implement,},},
    {"stack",       {stack_implement,},},
    {"queue",       {queue_implement,},},
    {"tree",        {tree_implement,},},
    /* END POINT OF CATEGORY */
    {NULL,          {NULL,},}
};
/*-----------------------------------------------------------------*/
/*--------------------------- END OF CATEGORY LAYER OF LAYER TABLE */
/*-----------------------------------------------------------------*/
