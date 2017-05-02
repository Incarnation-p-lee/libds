#ifndef HAVE_DEFINED_UNIT_TEST_GRAPH_H
#define HAVE_DEFINED_UNIT_TEST_GRAPH_H

#define UT_GRAPH_create(name)                                  \
static void                                                    \
utest_##name##_graph_create(void)                              \
{                                                              \
    bool pass;                                                 \
    GRAPH *graph;                                              \
                                                               \
    pass = true;                                               \
    graph = GRAPH_create();                                    \
    UNIT_TEST_BEGIN(name##_graph_create);                      \
                                                               \
    RESULT_CHECK_bool(true, TEST_graph_legal_p(graph), &pass); \
                                                               \
    GRAPH_destroy(&graph);                                     \
    UNIT_TEST_RESULT(name##_graph_create, pass);               \
}

#define UT_GRAPH_link(name)                                                 \
static void                                                                 \
utest_##name##_graph_link(void)                                             \
{                                                                           \
    bool pass;                                                              \
    sint32 cost;                                                            \
    GRAPH *graph;                                                           \
    void *vertex_a;                                                         \
    void *vertex_b;                                                         \
    s_edge_t *edge;                                                         \
                                                                            \
    pass = true;                                                            \
    graph = TEST_GRAPH_sample(0x003, 0x002);                                \
    vertex_a = &pass;                                                       \
    vertex_b = &graph;                                                      \
    cost = 0x234;                                                           \
                                                                            \
    UNIT_TEST_BEGIN(name##_graph_link);                                     \
                                                                            \
    edge = GRAPH_link(NULL, vertex_a, vertex_b, cost);                      \
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);                         \
                                                                            \
    edge = GRAPH_link(graph, NULL, vertex_b, cost);                         \
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);                         \
                                                                            \
    edge = GRAPH_link(graph, vertex_b, NULL, cost);                         \
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);                         \
                                                                            \
    edge = GRAPH_link(graph, vertex_a, vertex_b, cost);                     \
    RESULT_CHECK_sint32(cost, GRAPH_edge_cost(edge), &pass);                \
    RESULT_CHECK_pointer(vertex_a, GRAPH_edge_vertex_0_value(edge), &pass); \
    RESULT_CHECK_pointer(vertex_b, GRAPH_edge_vertex_1_value(edge), &pass); \
                                                                            \
    GRAPH_destroy(&graph);                                                  \
    UNIT_TEST_RESULT(name##_graph_link, pass);                              \
}

#endif

