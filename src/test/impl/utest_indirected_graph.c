#define GRAPH                     s_graph_t
#define GRAPH_edge_cost           indirected_graph_edge_cost
#define GRAPH_edge_vertex_0_value indirected_graph_edge_vertex_0_value
#define GRAPH_edge_vertex_1_value indirected_graph_edge_vertex_1_value
#define TEST_GRAPH_sample         test_indirected_graph_sample
#define TEST_graph_legal_p        indirected_graph_structure_legal_p

#define GRAPH_create              indirected_graph_create
#define GRAPH_destroy             indirected_graph_destroy
#define GRAPH_link                indirected_graph_link

#include "../utest_graph.h"

UT_GRAPH_create(indirected)
UT_GRAPH_link(indirected)

#undef GRAPH
#undef TEST_graph_legal_p
#undef GRAPH_edge_cost
#undef GRAPH_edge_vertex_0_value
#undef GRAPH_edge_vertex_1_value
#undef TEST_GRAPH_sample
#undef TEST_graph_legal_p

#undef GRAPH_create
#undef GRAPH_destroy
#undef GRAPH_link

