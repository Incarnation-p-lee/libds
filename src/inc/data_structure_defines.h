#ifndef HAVE_DATA_STRUCTURE_DEFINES_H
#define HAVE_DATA_STRUCTURE_DEFINES_H

/* Macro of struct field set and get.
   We _DO_ NOT use function here for the balance of performance
   and interface clean. */
/* DOUBLY LINKED LIST */
#define RESULT_CHECK_doubly_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->id, (ex)->id, (pass));              \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
        RESULT_CHECK_pointer((aim)->previous, (ex)->previous, (pass)); \
    } while (false)

#define doubly_linked_list_node_val(node) \
    (assert(node), (node)->val)

#define doubly_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define doubly_linked_list_node_id(node) \
    (assert(node), (node)->id)

#define doubly_linked_list_node_id_set(node, v) \
    (assert(node), (node)->id = (v))

#define doubly_linked_list_node_next(node) \
    (assert(node), (node)->next)

#define doubly_linked_list_node_next_set(node, v) \
    (assert(node), (node)->next = (v))

#define doubly_linked_list_node_previous(node) \
    (assert(node), (node)->previous)

#define doubly_linked_list_node_previous_set(node, v) \
    (assert(node), (node)->previous = (v))


/* SINGLE LINKED LIST */
#define RESULT_CHECK_single_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->id, (ex)->id, (pass));              \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
    } while (false)

#define single_linked_list_node_val(node) \
    (assert(node), (node)->val)

#define single_linked_list_node_val_set(node, v) \
    (assert(node), (node)->val = (v))

#define single_linked_list_node_id(node) \
    (assert(node), (node)->id)

#define single_linked_list_node_id_set(node, v) \
    (assert(node), (node)->id = (v))

#define single_linked_list_node_next(node) \
    (assert(node), (node)->next)

#define single_linked_list_node_next_set(node, v) \
    (assert(node), (node)->next = (v))

#endif
