#ifndef HAVE_TREE_H
#define HAVE_TREE_H

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

#define TREE_NUMBER_INVALID   0
#define TREE_SUM_INVALID      (sint64)0x8000000000000000
#define TREE_NICE_PLUS_LMT    0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT   (-TREE_NICE_PLUS_LMT - 1)

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false

extern bool complain_no_memory_p(void *ptr);
extern bool complain_null_pointer_p(void *ptr);
extern bool complain_zero_size_p(uint32 size);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *));
extern void * memory_cache_allocate(uint32 size);
extern void memory_cache_free(void *addr);

static sint32 direct = 0;

#endif

