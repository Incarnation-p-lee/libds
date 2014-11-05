#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

void
linked_list_unit_test(void);
static void
doubly_linked_list_unit_test(void);
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
test_result_print(char *name, bool passed);
static int *
int_array_generate(int size);

#endif
