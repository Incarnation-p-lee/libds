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
