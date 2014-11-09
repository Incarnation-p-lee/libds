#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

static int malloc_cnt = 0;
static int free_cnt = 0;
static int realloc_cnt = 0;

void *
malloc_wrap(size_t size);
void *
realloc_wrap(void *ptr, size_t size);
void
free_wrap(void *ptr);
void
memory_trace_print(void);

void
linked_list_unit_test(void);
void
stack_unit_test(void);


static void
doubly_linked_list_unit_test(void);
static void
single_linked_list_unit_test(void);
static void
array_stack_unit_test(void);

static void
test_result_print(char *name, bool passed);
static int *
int_array_generate(int size);
static void
dlinked_list_iterate_handler(struct doubly_linked_list *node);
static void
slinked_list_iterate_handler(struct single_linked_list *node);
static void
array_stack_iterate_handler(void *);

#endif
