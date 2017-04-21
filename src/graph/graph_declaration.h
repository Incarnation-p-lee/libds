#ifndef HAVE_DEFINED_graph_H
#define HAVE_DEFINED_graph_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

#if defined DEBUG

static inline bool graph_edge_list_structure_legal_p(s_edge_list_t *edge_list);
static inline bool graph_structure_illegal_p(s_graph_t *graph);
static inline bool graph_structure_legal_p(s_graph_t *graph);
static inline bool graph_vertex_array_structure_illegal_p(s_vertex_array_t *vertex_array);
static inline bool graph_vertex_array_structure_legal_p(s_vertex_array_t *vertex_array);
static inline bool graph_vertex_structure_legal_p(s_vertex_t *vertex);

#endif

bool directed_graph_structure_legal_p(s_graph_t *graph);
bool indirected_graph_structure_legal_p(s_graph_t *graph);
s_graph_t * directed_graph_create(void);
s_graph_t * indirected_graph_create(void);
static inline bool graph_directed_p(s_graph_t *graph);
static inline bool graph_indirected_p(s_graph_t *graph);
static inline s_edge_list_t * graph_edge_list_next(s_edge_list_t *edge_list);
static inline s_graph_t * graph_create(void);
static inline s_vertex_array_t * graph_vertex_array_create(void);
static inline s_vertex_t * graph_vertex_array_vertex(s_vertex_array_t *vertex_array, uint32 i);
static inline uint32 graph_vertex_array_limit(s_vertex_array_t *vertex_array);
static inline void graph_attibute_directed_set(s_graph_t *graph, bool is_directed);
static inline void graph_destroy(s_graph_t *graph);
static inline void graph_edge_list_destroy(s_edge_list_t *edge_list);
static inline void graph_vertex_array_destroy(s_vertex_array_t *vertex_array);
static inline void graph_vertex_destroy(s_vertex_t *vertex);
void directed_graph_destroy(s_graph_t **graph);
void indirected_graph_destroy(s_graph_t **graph);

#endif
