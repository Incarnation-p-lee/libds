#ifndef HAVE_DEFINED_GRAPH_H
#define HAVE_DEFINED_GRAPH_H

#define GRAPH_VERTEX_INVALID     (void *)PTR_INVALID
#define GRAPH_VERTEX_DEFAULT     128
#define GRAPH_VERTEX_MAX_DEFAULT 1024
/* Open addressing hash need at least (2 * n + 1) space */
#define GRAPH_VERTEX_HASH_SIZE   (GRAPH_VERTEX_MAX_DEFAULT * 2 + 1)

#define GRAPH_LABEL_INVALID      0
#define GRAPH_LABEL_FIRST        1

#define GRAPH_ADJACENT_DEFAULT   32
#define GRAPH_ADJACENT_LOAD_FCTR 20 /* 20% load factor of adjacent */
#define GRAPH_ADJACENT_REST_FCTR 30 /* 30% rest space of adjacent */

#define GRAPH_EDGE_DEFAULT       1024

#if defined DEBUG
    #define GRAPH_LEGAL_P(g)                graph_structure_legal_p(g)
    #define GRAPH_ILLEGAL_P(g)              graph_structure_illegal_p(g)
    #define GRAPH_EDGE_LEGAL_P(e)           graph_edge_structure_legal_p(e)
    #define GRAPH_EDGE_ILLEGAL_P(e)         graph_edge_structure_illegal_p(e)
    #define GRAPH_EDGE_ARRAY_LEGAL_P(e)     graph_edge_array_structure_legal_p(e)
    #define GRAPH_EDGE_ARRAY_ILLEGAL_P(e)   graph_edge_array_structure_illegal_p(e)
    #define GRAPH_VERTEX_LEGAL_P(v)         graph_vertex_structure_legal_p(v)
    #define GRAPH_VERTEX_ILLEGAL_P(v)       graph_vertex_structure_illegal_p(v)
    #define GRAPH_VERTEX_ARRAY_LEGAL_P(v)   graph_vertex_array_structure_legal_p(v)
    #define GRAPH_VERTEX_ARRAY_ILLEGAL_P(v) graph_vertex_array_structure_illegal_p(v)
    #define GRAPH_TOPO_LIST_LEGAL_P(t)      graph_topo_list_structure_legal_p(t)
    #define GRAPH_TOPO_LIST_ILLEGAL_P(t)    graph_topo_list_structure_illegal_p(t)
    #define DIRECTED_GRAPH_LEGAL_P(g)       directed_graph_structure_legal_p(g)
    #define DIRECTED_GRAPH_ILLEGAL_P(g)     directed_graph_structure_illegal_p(g)
    #define INDIRECTED_GRAPH_LEGAL_P(g)     indirected_graph_structure_legal_p(g)
    #define INDIRECTED_GRAPH_ILLEGAL_P(g)   indirected_graph_structure_illegal_p(g)
#else
    #define GRAPH_LEGAL_P(g)                NON_NULL_PTR_P(g)
    #define GRAPH_ILLEGAL_P(g)              NULL_PTR_P(g)
    #define GRAPH_EDGE_LEGAL_P(e)           NON_NULL_PTR_P(e)
    #define GRAPH_EDGE_ILLEGAL_P(e)         NULL_PTR_P(e)
    #define GRAPH_EDGE_ARRAY_LEGAL_P(e)     NON_NULL_PTR_P(e)
    #define GRAPH_EDGE_ARRAY_ILLEGAL_P(e)   NULL_PTR_P(e)
    #define GRAPH_VERTEX_LEGAL_P(v)         NON_NULL_PTR_P(v)
    #define GRAPH_VERTEX_ILLEGAL_P(v)       NULL_PTR_P(v)
    #define GRAPH_VERTEX_ARRAY_LEGAL_P(v)   NON_NULL_PTR_P(v)
    #define GRAPH_VERTEX_ARRAY_ILLEGAL_P(v) NULL_PTR_P(v)
    #define GRAPH_TOPO_LIST_LEGAL_P(t)      NON_NULL_PTR_P(t)
    #define GRAPH_TOPO_LIST_ILLEGAL_P(t)    NULL_PTR_P(t)
    #define DIRECTED_GRAPH_LEGAL_P(g)       NON_NULL_PTR_P(g)
    #define DIRECTED_GRAPH_ILLEGAL_P(g)     NULL_PTR_P(g)
    #define INDIRECTED_GRAPH_LEGAL_P(g)     NON_NULL_PTR_P(g)
    #define INDIRECTED_GRAPH_ILLEGAL_P(g)   NULL_PTR_P(g)
#endif

extern bool array_queue_structure_illegal_p(s_array_queue_t *queue);
extern bool array_queue_empty_p(s_array_queue_t *queue);
extern s_array_queue_t * array_queue_create(void);
extern s_open_addressing_hash_t * open_addressing_hash_create(uint32 size);
extern void array_queue_destroy(s_array_queue_t **queue);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void * array_queue_front(s_array_queue_t *queue);
extern void * array_queue_rear(s_array_queue_t *queue);
extern bool array_queue_structure_legal_p(s_array_queue_t *queue);
extern void open_addressing_hash_destroy(s_open_addressing_hash_t **hash);
extern void * open_addressing_hash_remove(s_open_addressing_hash_t *hash, void *key);
extern void * open_addressing_hash_find(s_open_addressing_hash_t *hash, void *key);
extern void * array_queue_leave(s_array_queue_t *queue);
extern void * open_addressing_hash_insert(s_open_addressing_hash_t *hash, void *key);
extern bool doubly_linked_list_structure_illegal_p(s_doubly_linked_list_t *list);
extern void doubly_linked_list_initial(s_doubly_linked_list_t *list);
extern void doubly_linked_list_insert_before(s_doubly_linked_list_t *list, s_doubly_linked_list_t *node);
extern s_doubly_linked_list_t * doubly_linked_list_remove(s_doubly_linked_list_t **list);
extern void array_stack_push(s_array_stack_t *stack, void *member);
extern void * array_stack_pop(s_array_stack_t *stack);
extern void * array_stack_top(s_array_stack_t *stack);
extern s_array_stack_t * array_stack_create(void);
extern void array_stack_destroy(s_array_stack_t **stack);
extern bool array_stack_structure_legal_p(s_array_stack_t *stack);
extern bool array_stack_empty_p(s_array_stack_t *stack);

#endif

