#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

static int malloc_cnt = 0;
static int free_cnt = 0;

void *
malloc_wrap(size_t size);
void
free_wrap(void *ptr);
void
memory_trace_print(void);

void
linked_list_unit_test(void);
static void
doubly_linked_list_unit_test(void);
static void
single_linked_list_unit_test(void);


static void
test_dlinked_list_initial(void);
static void
test_dlinked_list_generate(void);
static void
test_dlinked_list_append_node(void);
static void
test_dlinked_list_next_node(void);
static void
test_dlinked_list_previous_node(void);
static void
test_dlinked_list_insert_before(void);
static void
test_dlinked_list_insert_after(void);
static void
test_dlinked_list_destroy(void);
static void
test_dlinked_list_length(void);
static void
test_dlinked_list_get_node_by_index(void);
static void
test_dlinked_list_exchange_node(void);
static void
test_dlinked_list_is_contains(void);
static void
test_dlinked_list_serialize(void);
static void
test_dlinked_list_remove_node(void);
static void
test_dlinked_list_lazy_remove_node(void);


static void
test_slinked_list_initial(void);
static void
test_slinked_list_generate(void);
static void
test_slinked_list_append_node(void);
static void
test_slinked_list_next_node(void);
static void
test_slinked_list_previous_node(void);
static void
test_slinked_list_insert_before(void);
static void
test_slinked_list_insert_after(void);
static void
test_slinked_list_destroy(void);
static void
test_slinked_list_length(void);
static void
test_slinked_list_get_node_by_index(void);
static void
test_slinked_list_exchange_node(void);
static void
test_slinked_list_is_contains(void);
static void
test_slinked_list_serialize(void);
static void
test_slinked_list_remove_node(void);
static void
test_slinked_list_lazy_remove_node(void);



static void
test_result_print(char *name, bool passed);
static int *
int_array_generate(int size);

#endif
