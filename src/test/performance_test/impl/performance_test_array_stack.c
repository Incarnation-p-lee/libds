#define STACK                  s_array_stack_t
#define STACK_create           array_stack_create
#define STACK_destroy          array_stack_destroy
#define STACK_resize           array_stack_resize
#define STACK_full_p           array_stack_full_p
#define STACK_capacity         array_stack_capacity
#define STACK_rest             array_stack_rest
#define STACK_push             array_stack_push
#define STACK_pop              array_stack_pop
#define STACK_top              array_stack_top
#define STACK_empty_p          array_stack_empty_p
#define STACK_cleanup          array_stack_cleanup
#define STACK_iterate          array_stack_iterate

#include "../performance_test_stack.h"

PT_STACK_create(array)
PT_STACK_destroy(array)
PT_STACK_resize(array)
PT_STACK_full_p(array)
PT_STACK_capacity(array)
PT_STACK_rest(array)
PT_STACK_push(array)
PT_STACK_pop(array)
PT_STACK_top(array)
PT_STACK_empty_p(array)
PT_STACK_cleanup(array)
PT_STACK_iterate(array)

#undef STACK
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

