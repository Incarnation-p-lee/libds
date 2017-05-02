#define GRAPH                  s_graph_t
#define TEST_graph_legal_p     directed_graph_structure_legal_p

#define GRAPH_create           directed_graph_create
#define GRAPH_destroy          directed_graph_destroy

#include "../utest_graph.h"

UT_GRAPH_create(directed)

#undef GRAPH
#undef TEST_graph_legal_p

#undef GRAPH_create
#undef GRAPH_destroy

