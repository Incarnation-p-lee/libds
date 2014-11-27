#ifndef HAVE_UNIT_TEST_H
#define HAVE_UNIT_TEST_H

static uint32 malloc_cnt = 0;
static uint32 free_cnt = 0;
static uint32 realloc_cnt = 0;

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
void
queue_unit_test(void);


static void
doubly_linked_list_unit_test(void);
static void
single_linked_list_unit_test(void);
static void
array_stack_unit_test(void);
static void
linked_stack_unit_test(void);
static void
array_queue_unit_test(void);


static void
test_result_print(char *name, bool passed);
static sint32 *
int_array_generate(sint32 size);
static void
dlinked_list_iterate_handler(struct doubly_linked_list *node);
static void
slinked_list_iterate_handler(struct single_linked_list *node);
static void
stack_iterate_handler(void *ptr);
static void
queue_iterate_handler(void *ptr);

#endif
