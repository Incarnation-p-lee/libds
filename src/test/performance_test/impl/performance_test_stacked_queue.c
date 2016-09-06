#define QUEUE                  s_stacked_queue_t

#define QUEUE_create           stacked_queue_create
#define QUEUE_destroy          stacked_queue_destroy
#define QUEUE_rest             stacked_queue_rest
#define QUEUE_resize           stacked_queue_resize
#define QUEUE_full_p           stacked_queue_full_p
#define QUEUE_capacity         stacked_queue_capacity
#define QUEUE_front            stacked_queue_front
#define QUEUE_rear             stacked_queue_rear
#define QUEUE_enter            stacked_queue_enter
#define QUEUE_leave            stacked_queue_leave
#define QUEUE_empty_p          stacked_queue_empty_p
#define QUEUE_cleanup          stacked_queue_cleanup
#define QUEUE_iterate          stacked_queue_iterate



#include "../performance_test_queue.h"

PT_QUEUE_create(stacked)
PT_QUEUE_destroy(stacked)
PT_QUEUE_resize(stacked)
PT_QUEUE_rest(stacked)
PT_QUEUE_full_p(stacked)
PT_QUEUE_capacity(stacked)
PT_QUEUE_front(stacked)
PT_QUEUE_rear(stacked)
PT_QUEUE_enter(stacked)
PT_QUEUE_leave(stacked)
PT_QUEUE_empty_p(stacked)
PT_QUEUE_cleanup(stacked)
PT_QUEUE_iterate(stacked)


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

