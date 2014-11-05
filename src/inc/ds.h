#ifndef HAVE_DATA_STRUCTURE_INCLUDE_H
#define HAVE_DATA_STRUCTURE_INCLUDE_H

/* BEGIN of ./src/inc/data_structure_types.h */
#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H

/*
   Implement the unify single_linked_list interface
 All other linked list will involved this structure
 for linker, such as
   struct A {
     int;
     struct single_linked_list next;
   };
   Then, we can only care about this linked list opertion
 for all other linked list.
   Both single_linked_list and doubly_linked_list are
 _CIRCULAR_ linked list.
 */
struct single_linked_list {
    int    index;
    struct single_linked_list *next;
};

struct doubly_linked_list {
    int    index;
    struct doubly_linked_list *next;
    struct doubly_linked_list *previous;
};

/*
 * sp point to top of stack
 * bp point to the first element of a array in void * type
 */
struct stack_loc {
    void **sp;
    void *bp;
};

struct array_stack {
    struct stack_loc loc;
    unsigned         rest;
    unsigned         size;
};

struct array_queue {
    unsigned size;
    unsigned rest;
    void     **front;
    void     **rear;
    void     *queue;
};

#endif
/* END of ./src/inc/data_structure_types.h */

/* BEGIN of ./src/inc/log.h */
#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

extern int
libds_log_initial(void);
extern void
libds_log_close(void);
extern void
libds_log_print(enum log_level lvl, const char *msg);

#endif
/* END of ./src/inc/log.h */

/* BEGIN of ./src/inc/linked_list.h */
#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void
libds_log_print(enum log_level lvl, const char *msg);

/* doubly linked list, Circular. */
extern struct doubly_linked_list *
dlinked_list_initial(void);
extern struct doubly_linked_list *
dlinked_list_generate(int *val, int size);
extern void
dlinked_list_append_node(struct doubly_linked_list *node, int value);
extern struct doubly_linked_list *
dlinked_list_next_node(struct doubly_linked_list *node);
extern struct doubly_linked_list *
dlinked_list_previous_node(struct doubly_linked_list *node);
extern void
dlinked_list_insert_after(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_insert_before(struct doubly_linked_list *cur,
    struct doubly_linked_list *node);
extern void
dlinked_list_destroy(struct doubly_linked_list **head);
extern int
dlinked_list_length(struct doubly_linked_list *head);
extern struct doubly_linked_list *
dlinked_list_get_node_by_index(struct doubly_linked_list *head, int index);
extern void
dlinked_list_print(FILE *fd, char *msg, struct doubly_linked_list *head);
extern void
dlinked_list_exchange_node(struct doubly_linked_list *fir,
    struct doubly_linked_list *sec);
extern bool
dlinked_list_is_contains(struct doubly_linked_list *tar,
    struct doubly_linked_list *node);
extern void
dlinked_list_serialize(struct doubly_linked_list *head);
extern struct doubly_linked_list *
dlinked_list_remove_node(struct doubly_linked_list *node);
extern void
dlinked_list_lazy_remove_node(struct doubly_linked_list *node);


/* single linked list, Circular. */
extern struct single_linked_list *
slinked_list_initial(void);
extern struct single_linked_list *
slinked_list_generate(int *val, int size);
extern void
slinked_list_append_node(struct single_linked_list *node, int value);
extern struct single_linked_list *
slinked_list_next_node(struct single_linked_list *node);
extern struct single_linked_list *
slinked_list_previous_node(struct single_linked_list *node);
extern void
slinked_list_insert_after(struct single_linked_list *cur,
    struct single_linked_list *node);
extern void
slinked_list_insert_before(struct single_linked_list *cur,
    struct single_linked_list *node);
extern void
slinked_list_destroy(struct single_linked_list **head);
extern int
slinked_list_length(struct single_linked_list *head);
extern struct single_linked_list *
slinked_list_get_node_by_index(struct single_linked_list *head, int index);
extern void
slinked_list_print(FILE *fd, char *msg, struct single_linked_list *head);
extern void
slinked_list_exchange_node(struct single_linked_list *fir,
    struct single_linked_list *sec);
extern bool
slinked_list_is_contains(struct single_linked_list *tar,
    struct single_linked_list *node);
extern void
slinked_list_serialize(struct single_linked_list *head);
extern struct single_linked_list *
slinked_list_remove_node(struct single_linked_list *node);
extern void
slinked_list_lazy_remove_node(struct single_linked_list *node);

#endif
/* END of ./src/inc/linked_list.h */

/* BEGIN of ./src/inc/defines.h */
#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H


#define true        1
#define false       0

#define DEFAULT_LOG_FILE    "./ds.log"
#define SYM_2_STR(symbol)   (#symbol)

#ifdef DEBUG
    #define pr_log_info(msg)    libds_log_print(INFO, msg);
    #define pr_log_warn(msg)    libds_log_print(WARN, msg);
    #define pr_log_debug(msg)   libds_log_print(DEBUG, msg);
#else
    #define pr_log_info(msg)
    #define pr_log_warn(msg)
    #define pr_log_debug(msg)
#endif

#ifdef DEBUG
    #define malloc_ds      malloc_wrap
    #define free_ds        free_wrap
#else
    #define malloc_ds      malloc
    #define free_ds        free
#endif

#define pr_log_err(msg)     \
    do {                             \
        libds_log_print(ERROR, msg); \
        exit(1);                     \
    } while (0);

#endif
/* END of ./src/inc/defines.h */

/* BEGIN of ./src/inc/types.h */
#ifndef HAVE_TYPES_H
#define HAVE_TYPES_H

typedef int bool;

enum log_level {
  INFO,
  WARN,
  ERROR,
};


#endif
/* END of ./src/inc/types.h */
#endif