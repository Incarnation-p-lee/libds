#ifndef HAVE_QUEUE_H
#define HAVE_QUEUE_H

#define DEFAULT_QUEUE_SPACE_SIZE   128
#define EXPAND_QUEUE_SPACE_MIN     32

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void * realloc_wrap(void *ptr, size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);

struct array_queue *
array_queue_create(void);
void
array_queue_destroy(struct array_queue **queue);
void
array_queue_expand_space(struct array_queue *queue, uint32 extra);
uint32
array_queue_capacity(struct array_queue *queue);
uint32
array_queue_rest_space(struct array_queue *queue);
bool
array_queue_is_full(struct array_queue *queue);
bool
array_queue_is_empty(struct array_queue *queue);
void
array_queue_enter(struct array_queue *queue, void *member);
void *
array_queue_leave(struct array_queue *queue);
void
array_queue_cleanup(struct array_queue *queue);
void
array_queue_iterate(struct array_queue *queue, void (*handler)(void *));

#endif
