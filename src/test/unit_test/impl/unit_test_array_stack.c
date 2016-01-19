#define STACK                  array_stack
#define STACK_sid              array_stack_sid
#define STACK_sid_set          array_stack_sid_set
#define STACK_space_dim        array_stack_space_dim
#define STACK_space_dim_set    array_stack_space_dim_set

#define STACK_create           array_stack_create
#define STACK_destroy          array_stack_destroy
#define STACK_space_expand     array_stack_space_expand
#define STACK_full_p           array_stack_full_p
#define STACK_capacity         array_stack_capacity
#define STACK_space_rest       array_stack_space_rest
#define STACK_push             array_stack_push
#define STACK_pop              array_stack_pop
#define STACK_empty_p          array_stack_empty_p
#define STACK_cleanup          array_stack_cleanup
#define STACK_iterate          array_stack_iterate

#include "../unit_test_stack.h"

UT_STACK_create(array)
UT_STACK_destroy(array)
UT_STACK_space_expand(array)
UT_STACK_full_p(array)
UT_STACK_capacity(array)
UT_STACK_space_rest(array)
UT_STACK_push(array)
UT_STACK_pop(array)
UT_STACK_empty_p(array)
UT_STACK_cleanup(array)
UT_STACK_iterate(array)

#undef STACK
#undef STACK_sid
#undef STACK_sid_set
#undef STACK_space_dim
#undef STACK_space_dim_set

#undef STACK_create
#undef STACK_destroy
#undef STACK_space_expand
#undef STACK_full_p
#undef STACK_capacity
#undef STACK_space_rest
#undef STACK_push
#undef STACK_pop
#undef STACK_empty_p
#undef STACK_cleanup
#undef STACK_iterate

