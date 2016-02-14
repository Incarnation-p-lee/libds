#define STACK                  linked_stack
#define STACK_sid              linked_stack_sid
#define STACK_sid_set          linked_stack_sid_set
#define TEST_STACK_legal_p     utest_linked_stack_struct_legal_p

#define STACK_create           linked_stack_create
#define STACK_destroy          linked_stack_destroy
#define STACK_resize           linked_stack_resize
#define STACK_full_p           linked_stack_full_p
#define STACK_capacity         linked_stack_capacity
#define STACK_rest             linked_stack_rest
#define STACK_push             linked_stack_push
#define STACK_pop              linked_stack_pop
#define STACK_empty_p          linked_stack_empty_p
#define STACK_cleanup          linked_stack_cleanup
#define STACK_iterate          linked_stack_iterate

#include "../performance_test_stack.h"

PT_STACK_create(linked)
PT_STACK_destroy(linked)
PT_STACK_resize(linked)
PT_STACK_full_p(linked)
PT_STACK_capacity(linked)
PT_STACK_rest(linked)
PT_STACK_push(linked)
PT_STACK_pop(linked)
PT_STACK_empty_p(linked)
PT_STACK_cleanup(linked)
PT_STACK_iterate(linked)

#undef STACK
#undef STACK_sid
#undef STACK_sid_set
#undef TEST_STACK_legal_p

#undef STACK_create
#undef STACK_destroy
#undef STACK_resize
#undef STACK_full_p
#undef STACK_capacity
#undef STACK_rest
#undef STACK_push
#undef STACK_pop
#undef STACK_empty_p
#undef STACK_cleanup
#undef STACK_iterate


