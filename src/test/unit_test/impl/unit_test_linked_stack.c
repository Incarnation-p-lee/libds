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

#include "../unit_test_stack.h"

UT_STACK_create(linked)
UT_STACK_destroy(linked)
UT_STACK_resize(linked)
UT_STACK_full_p(linked)
UT_STACK_capacity(linked)
UT_STACK_rest(linked)
UT_STACK_push(linked)
UT_STACK_pop(linked)
UT_STACK_empty_p(linked)
UT_STACK_cleanup(linked)
UT_STACK_iterate(linked)

#undef STACK
#undef STACK_sid
#undef STACK_sid_set

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
#undef TEST_STACK_legal_p

static inline bool
utest_linked_stack_struct_legal_p(struct linked_stack *stack)
{
    assert_exit(!complain_null_pointer_p(stack));

    if (stack->base != stack->top) {
        return false;
    } else if ((void *)stack->base->space.sp != stack->base->space.bp) {
        return false;
    } else {
        return true;
    }
}

