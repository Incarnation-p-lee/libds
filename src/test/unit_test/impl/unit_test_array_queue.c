#define QUEUE                  array_queue

#define QUEUE_create           array_queue_create
#define QUEUE_destroy          array_queue_destroy
#define QUEUE_resize           array_queue_resize
#define QUEUE_full_p           array_queue_full_p
#define QUEUE_empty_p          array_queue_empty_p
#define QUEUE_capacity         array_queue_capacity
#define QUEUE_rest             array_queue_rest
#define QUEUE_enter            array_queue_enter
#define QUEUE_front            array_queue_front
#define QUEUE_rear             array_queue_rear
#define QUEUE_leave            array_queue_leave
#define QUEUE_cleanup          array_queue_cleanup
#define QUEUE_iterate          array_queue_iterate

#include "../unit_test_queue.h"

UT_QUEUE_create(array)
UT_QUEUE_destroy(array)
UT_QUEUE_resize(array)
UT_QUEUE_full_p(array)
UT_QUEUE_empty_p(array)
UT_QUEUE_capacity(array)
UT_QUEUE_rest(array)
UT_QUEUE_enter(array)
UT_QUEUE_leave(array)
UT_QUEUE_front(array)
UT_QUEUE_rear(array)
UT_QUEUE_cleanup(array)
UT_QUEUE_iterate(array)

#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_resize
#undef QUEUE_full_p
#undef QUEUE_empty_p
#undef QUEUE_capacity
#undef QUEUE_rest
#undef QUEUE_enter
#undef QUEUE_leave
#undef QUEUE_front
#undef QUEUE_rear
#undef QUEUE_cleanup
#undef QUEUE_iterate

