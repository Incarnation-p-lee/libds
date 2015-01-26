#ifndef HAVE_TREE_H
#define HAVE_TREE_H

#ifdef DEBUG
    extern void * malloc_wrap(size_t size);
    extern void free_wrap(void *ptr);
#endif

extern void libds_log_print(enum log_level lvl, const char *msg);
extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern void doubly_linked_list_node_set_val(struct doubly_linked_list *node, void *val);
extern void * doubly_linked_list_node_get_val(struct doubly_linked_list *node);

/* BINARY SEARCH TREE */
struct binary_search_tree * binary_search_tree_create(void);
struct binary_search_tree * binary_search_tree_node_create(void *val, sint64 nice);
void binary_search_tree_initial(struct binary_search_tree *root);
void binary_search_tree_node_initial(struct binary_search_tree *node, void *val, sint64 nice);
void binary_search_tree_destory(struct binary_search_tree **root);


/* END OF BINARY SEARCH TREE */

#endif
