#define STACK                  array_stack
#define STACK_sid              array_stack_sid
#define STACK_sid_set          array_stack_sid_set
#define TEST_STACK_legal_p     utest_array_stack_struct_legal_p

#define STACK_create           array_stack_create
#define STACK_destroy          array_stack_destroy
#define STACK_resize           array_stack_resize
#define STACK_full_p           array_stack_full_p
#define STACK_capacity         array_stack_capacity
#define STACK_rest             array_stack_rest
#define STACK_push             array_stack_push
#define STACK_pop              array_stack_pop
#define STACK_empty_p          array_stack_empty_p
#define STACK_cleanup          array_stack_cleanup
#define STACK_iterate          array_stack_iterate

#include "../unit_test_stack.h"

UT_STACK_create(array)
UT_STACK_destroy(array)
UT_STACK_resize(array)
UT_STACK_full_p(array)
UT_STACK_capacity(array)
UT_STACK_rest(array)
UT_STACK_push(array)
UT_STACK_pop(array)
UT_STACK_empty_p(array)
UT_STACK_cleanup(array)
UT_STACK_iterate(array)

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

static inline bool
utest_array_stack_struct_legal_p(struct array_stack *stack)
{
    assert(!complain_null_pointer_p(stack));

    if (DEFAULT_STACK_SPACE_SIZE != array_stack_space_dim(stack)) {
        return false;
    } else if (complain_null_pointer_p(stack->space.sp)) {
        return false;
    } else if (complain_null_pointer_p(stack->space.bp)) {
        return false;
    } else {
        return true;
    }
}

