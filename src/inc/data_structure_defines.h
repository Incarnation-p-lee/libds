#ifndef HAVE_DATA_STRUCTURE_DEFINES_H
#define HAVE_DATA_STRUCTURE_DEFINES_H

/* Macro of struct field set and get.
   We _DO_ NOT use function here for the balance of performance
   and interface clean. */
#define doubly_linked_list_node_val_get(node) \
    (assert(node), (node)->val)

#define doubly_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define doubly_linked_list_node_id_get(node) \
    (assert(node), (node)->id)

#define doubly_linked_list_node_id_set(node, v) \
    (assert(node), (node)->id = (v))

#define doubly_linked_list_node_next_get(node) \
    (assert(node), (node)->next)

#define doubly_linked_list_node_next_set(node, v) \
    (assert(node), (node)->next = (v))

#define doubly_linked_list_node_previous_get(node) \
    (assert(node), (node)->previous)

#define doubly_linked_list_node_previous_set(node, v) \
    (assert(node), (node)->previous = (v))

#endif
