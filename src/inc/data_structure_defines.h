#ifndef HAVE_DATA_STRUCTURE_DEFINES_H
#define HAVE_DATA_STRUCTURE_DEFINES_H

/* Macro of struct field set and get.
   We _DO_ NOT use function here for the balance of performance
   and interface clean.
   _Attention_, _DO_ _NOT_ use const parameters for following macro. */
/* DOUBLY LINKED LIST */
#define RESULT_CHECK_doubly_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
        RESULT_CHECK_pointer((aim)->previous, (ex)->previous, (pass)); \
    } while (false)

#define doubly_linked_list_val(node) \
    (dp_assert(NULL != node), (node)->val)
#define doubly_linked_list_val_set(node, v) \
    (dp_assert(NULL != node), (node)->val = (v))

#define doubly_linked_list_next(node) \
    (dp_assert(NULL != node), (node)->next)
#define doubly_linked_list_next_set(node, v) \
    (dp_assert(NULL != node), (node)->next = (v))

#define doubly_linked_list_previous(node) \
    (dp_assert(NULL != node), (node)->previous)
#define doubly_linked_list_previous_set(node, v) \
    (dp_assert(NULL != node), (node)->previous = (v))


/* SINGLE LINKED LIST */
#define RESULT_CHECK_single_linked_list_node(aim, ex, pass)            \
    do {                                                               \
        RESULT_CHECK_pointer((aim)->val, (ex)->val, (pass));           \
        RESULT_CHECK_pointer((aim)->next, (ex)->next, (pass));         \
    } while (false)

#define single_linked_list_val(node) \
    (dp_assert(NULL != node), (node)->val)
#define single_linked_list_val_set(node, v) \
    (dp_assert(NULL != node), (node)->val = (v))

#define single_linked_list_next(node) \
    (dp_assert(NULL != node), (node)->next)
#define single_linked_list_next_set(node, v) \
    (dp_assert(NULL != node), (node)->next = (v))

/*
 * Single linked list previous set not supported.
 */
#define single_linked_list_previous_set(node, v)


/* SKIP LINKED LIST */
#define skip_linked_list_key(node) \
    (dp_assert(NULL != node), (node)->key)
#define skip_linked_list_key_set(node, k) \
    (dp_assert(NULL != node), (node)->key = (k))

#define skip_linked_list_val(node) \
    (dp_assert(NULL != node), (node)->val)
#define skip_linked_list_val_set(node, v) \
    (dp_assert(NULL != node), (node)->val = (v))

#define skip_linked_list_next(node) \
    (dp_assert(NULL != node), (node)->next)
#define skip_linked_list_next_set(node, n) \
    (dp_assert(NULL != node), (node)->next = (n))

/*
 * Skip linked list previous not supported.
 */
#define skip_linked_list_previous(node) \
    (node)

/* ARRAY STACK */
#define RESULT_CHECK_array_stack(aim, ex, pass)                        \
    do {                                                               \
        RESULT_CHECK_uint32((aim)->sid, (ex)->sid, (pass))             \
        RESULT_CHECK_uint32((aim)->space.dim, (ex)->space.dim, (pass)) \
    } while (false)
    /* We do check sp, bp field here, they should not export to user */

#define array_stack_sid(stack) \
    (dp_assert(NULL != stack), (stack)->sid)
#define array_stack_sid_set(stack, v) \
    (dp_assert(NULL != stack), (stack)->sid = (v))

#define array_stack_space_dim(stack) \
    (dp_assert(NULL != stack), (stack)->space.dim)
#define array_stack_space_dim_set(stack, v) \
    (dp_assert(NULL != stack), (stack)->space.dim = (v))

/* LINKED STACK */
#define linked_stack_sid(stack) \
    (dp_assert(NULL != stack), (stack)->sid)
#define linked_stack_sid_set(stack, v) \
    (dp_assert(NULL != stack), (stack)->sid = (v))

/* ARRAY QUEUE */
#define array_queue_rest_m(queue) \
    (dp_assert(NULL != queue), (queue)->space.rest)

#define array_queue_dim_m(queue) \
    (dp_assert(NULL != queue), (queue)->space.dim)
#define array_queue_dim_set_m(queue, size) \
    (dp_assert(NULL != queue), (queue)->space.dim = (size))

/* STACKED QUEUE */
#define stacked_queue_sid(queue) \
    (dp_assert(NULL != queue), (queue)->sid)
#define stacked_queue_sid_set(queue, v) \
    (dp_assert(NULL != queue), (queue)->sid = (v))

#define stacked_queue_dim(queue) \
    (dp_assert(NULL != queue), (queue)->dim)

/* DOUBLY END QUEUE */
#define doubly_end_queue_sid(queue) \
    (dp_assert(NULL != queue), (queue)->sid)
#define doubly_end_queue_sid_set(queue, v) \
    (dp_assert(NULL != queue), (queue)->sid = (v))

/* BINARY SEARCH TREE */
#define binary_search_tree_node_nice(tree) \
    (dp_assert(NULL != tree), (tree)->chain.nice)
#define binary_search_tree_node_nice_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->chain.nice = (v))

#define binary_search_tree_child_left(tree) \
    (dp_assert(NULL != tree), (tree)->left)
#define binary_search_tree_child_left_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->left = (v))

#define binary_search_tree_child_right(tree) \
    (dp_assert(NULL != tree), (tree)->right)
#define binary_search_tree_child_right_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->right = (v))

#define binary_search_tree_node_link(tree) \
    (dp_assert(NULL != tree), ((tree)->chain).link)
#define binary_search_tree_child_link_set(tree, v) \
    (dp_assert(NULL != tree), ((tree)->chain).link = (v))

/* AVL TREE */
#define avl_tree_node_nice(tree) \
    (dp_assert(NULL != tree), (tree)->alias.chain.nice)
#define avl_tree_node_nice_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->alias.chain.nice = (v))

#define avl_tree_child_left(tree) \
    (dp_assert(NULL != tree), avl_tree_ptr_binary_to_avl(tree->alias.left))

#define avl_tree_child_right(tree) \
    (dp_assert(NULL != tree), avl_tree_ptr_binary_to_avl(tree->alias.right))

#define avl_tree_node_link(tree) \
    (dp_assert(NULL != tree), (tree)->alias.chain.link)
#define avl_tree_node_link_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->alias.chain.link = (v))

#define avl_tree_height(tree) \
    (dp_assert(NULL != tree), (tree)->height)
#define avl_tree_height_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->height = (v))

/* SPLAY TREE */
#define splay_tree_node_nice(tree) \
    (dp_assert(NULL != tree), (tree)->alias.chain.nice)
#define splay_tree_node_nice_set(tree, v) \
    (dp_assert(NULL != tree), (tree)->alias.chain.nice = (v))

#define splay_tree_child_left(tree) \
    (dp_assert(NULL != tree), splay_tree_ptr_container_of(tree->alias.left))

#define splay_tree_child_right(tree) \
    (dp_assert(NULL != tree), splay_tree_ptr_container_of(tree->alias.right))

#define splay_tree_node_link(tree) \
    (dp_assert(NULL != tree), (tree)->alias.chain.link)


/* BINARY INDEXED TREE */
#define binary_indexed_tree_size(tree) \
    (dp_assert(NULL != tree), (tree)->size)

#define binary_indexed_tree_value(tree, number) \
    (dp_assert(NULL != tree), dp_assert(0 != number), (tree)->data[number])

/* HASHING TABLE */
#define hashing_table_size(hash) \
    (dp_assert(NULL != hash), (hash)->size)

#define hashing_table_load_factor(hash) \
    (dp_assert(NULL != hash), (hash)->load_factor)
#define hashing_table_load_factor_set(hash, factor) \
    (dp_assert(NULL != hash), (hash)->load_factor = (factor))

/* SEPARATE CHAIN HASHING */
#define separate_chain_hash_size(hash) \
    (dp_assert(NULL != hash), hashing_table_size((hash)->table))

#define separate_chain_hash_load_factor(hash) \
    (dp_assert(NULL != hash), hashing_table_load_factor((hash)->table))
#define separate_chain_hash_load_factor_set(hash, factor) \
    (dp_assert(NULL != hash), hashing_table_load_factor_set((hash)->table, factor))

/* OPEN ADDRESSING HASHING */
#define open_addressing_hash_size(hash) \
    (dp_assert(NULL != hash), hashing_table_size((hash)->table))

#define open_addressing_hash_load_factor(hash) \
    (dp_assert(NULL != hash), hashing_table_load_factor((hash)->table))
#define open_addressing_hash_load_factor_set(hash, factor) \
    (dp_assert(NULL != hash), hashing_table_load_factor_set((hash)->table, factor))

/* MINIMAL HEAP */
#define minimal_heap_size(heap) \
    (dp_assert(NULL !=  heap), (heap)->alias->size)

#define minimal_heap_capacity(heap) \
    (dp_assert(NULL !=  heap), (heap)->alias->capacity)

#define minimal_heap_nice(heap, index) \
    (dp_assert(NULL !=  heap), HEAP_NICE(heap->alias, index))

#define minimal_heap_val(heap, index) \
    (dp_assert(NULL !=  heap), HEAP_VAL(heap->alias, index))
#define minimal_heap_val_set(heap, index, val) \
    (dp_assert(NULL !=  heap), HEAP_VAL(heap->alias, index) = (val))

#define minimal_heap_index_last(heap) \
    (dp_assert(NULL !=  heap), INDEX_LAST(heap->alias))

/* MAXIMAL HEAP */
#define maximal_heap_size(heap) \
    (dp_assert(NULL != heap), (heap)->alias->size)

#define maximal_heap_capacity(heap) \
    (dp_assert(NULL != heap), (heap)->alias->capacity)

#define maximal_heap_nice(heap, index) \
    (dp_assert(NULL != heap), HEAP_NICE(heap->alias, index))

#define maximal_heap_val(heap, index) \
    (dp_assert(NULL != heap), HEAP_VAL(heap->alias, index))
#define maximal_heap_val_set(heap, index, val) \
    (dp_assert(NULL != heap), HEAP_VAL(heap->alias, index) = (val))

#define maximal_heap_index_last(heap) \
    (dp_assert(NULL != heap), INDEX_LAST(heap->alias))

/* MIN_MAX HEAP */
#define min_max_heap_size(heap) \
    (dp_assert(NULL != heap), (heap)->alias->size)

#define min_max_heap_capacity(heap) \
    (dp_assert(NULL != heap), (heap)->alias->capacity)

#define min_max_heap_nice(heap, index) \
    (dp_assert(NULL != heap), HEAP_NICE(heap->alias, index))

#define min_max_heap_val(heap, index) \
    (dp_assert(NULL != heap), HEAP_VAL(heap->alias, index))
#define min_max_heap_val_set(heap, index, val) \
    (dp_assert(NULL != heap), HEAP_VAL(heap->alias, index) = (val))

#define min_max_heap_index_last(heap) \
    (dp_assert(NULL != heap), INDEX_LAST(heap->alias))


/* LEFTIST HEAP */
#define leftist_heap_nice(heap) \
    (dp_assert(NULL != heap), (heap)->data.nice)
#define leftist_heap_nice_set(heap, v) \
    (dp_assert(NULL != heap), (heap)->data.nice = (v))

#define leftist_heap_left(heap) \
    (dp_assert(NULL != heap), (heap)->left)

#define leftist_heap_right(heap) \
    (dp_assert(NULL != heap), (heap)->right)

#define leftist_heap_npl(heap) \
    (dp_assert(NULL != heap), (heap)->npl)
#define leftist_heap_npl_set(heap, v) \
    (dp_assert(NULL != heap), (heap)->npl = (v))

#define leftist_heap_val(heap) \
    (dp_assert(NULL != heap), (heap)->data.val)
#define leftist_heap_val_set(heap, v) \
    (dp_assert(NULL != heap), (heap)->data.val = (v))

#endif

