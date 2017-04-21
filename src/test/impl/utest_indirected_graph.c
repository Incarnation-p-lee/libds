#define GRAPH                  s_graph_t
#define TEST_graph_legal_p     indirected_graph_structure_legal_p

#define GRAPH_create           indirected_graph_create
#define GRAPH_destroy          indirected_graph_destroy

#include "../utest_graph.h"

UT_GRAPH_create(indirected)

#undef GRAPH
#undef TEST_graph_legal_p

#undef GRAPH_create
#undef GRAPH_destroy

