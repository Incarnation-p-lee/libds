#define QUEUE                  s_array_queue_t

#define QUEUE_create           array_queue_create
#define QUEUE_destroy          array_queue_destroy
#define QUEUE_rest             array_queue_rest
#define QUEUE_resize           array_queue_resize
#define QUEUE_full_p           array_queue_full_p
#define QUEUE_capacity         array_queue_capacity
#define QUEUE_front            array_queue_front
#define QUEUE_rear             array_queue_rear
#define QUEUE_enter            array_queue_enter
#define QUEUE_leave            array_queue_leave
#define QUEUE_empty_p          array_queue_empty_p
#define QUEUE_cleanup          array_queue_cleanup
#define QUEUE_iterate          array_queue_iterate
#define QUEUE_copy             array_queue_copy
#define QUEUE_merge            array_queue_merge

#include "../performance_test_queue.h"

PT_QUEUE_create(array)
PT_QUEUE_destroy(array)
PT_QUEUE_resize(array)
PT_QUEUE_rest(array)
PT_QUEUE_full_p(array)
PT_QUEUE_capacity(array)
PT_QUEUE_front(array)
PT_QUEUE_rear(array)
PT_QUEUE_enter(array)
PT_QUEUE_leave(array)
PT_QUEUE_empty_p(array)
PT_QUEUE_cleanup(array)
PT_QUEUE_iterate(array)
PT_QUEUE_copy(array)
PT_QUEUE_merge(array)

#undef QUEUE

#undef QUEUE_create
#undef QUEUE_destroy
#undef QUEUE_rest
#undef QUEUE_resize
#undef QUEUE_full_p
#undef QUEUE_capacity
#undef QUEUE_front
#undef QUEUE_rear
#undef QUEUE_enter
#undef QUEUE_leave
#undef QUEUE_empty_p
#undef QUEUE_cleanup
#undef QUEUE_iterate
#undef QUEUE_copy
#undef QUEUE_merge

