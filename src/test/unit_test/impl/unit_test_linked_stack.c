#define STACK                  s_linked_stack_t
#define TEST_STACK_legal_p     linked_stack_structure_legal_p

#define STACK_create           linked_stack_create
#define STACK_destroy          linked_stack_destroy
#define STACK_resize           linked_stack_resize
#define STACK_full_p           linked_stack_full_p
#define STACK_capacity         linked_stack_capacity
#define STACK_rest             linked_stack_rest
#define STACK_push             linked_stack_push
#define STACK_pop              linked_stack_pop
#define STACK_top              linked_stack_top
#define STACK_empty_p          linked_stack_empty_p
#define STACK_cleanup          linked_stack_cleanup
#define STACK_iterate          linked_stack_iterate

#include "../unit_test_stack.h"

UT_STACK_create(linked)
UT_STACK_destroy(linked)
UT_STACK_resize(linked)
UT_STACK_full_p(linked)
UT_STACK_capacity(linked)
UT_STACK_rest(linked)
UT_STACK_push(linked)
UT_STACK_pop(linked)
UT_STACK_top(linked)
UT_STACK_empty_p(linked)
UT_STACK_cleanup(linked)
UT_STACK_iterate(linked)

#undef STACK
#undef TEST_STACK_legal_p

#undef STACK_create
#undef STACK_destroy
#undef STACK_resize
#undef STACK_full_p
#undef STACK_capacity
#undef STACK_rest
#undef STACK_push
#undef STACK_pop
#undef STACK_top
#undef STACK_empty_p
#undef STACK_cleanup
#undef STACK_iterate
#undef TEST_STACK_legal_p

