static inline void
utest_directed_graph_create(void)
{
    bool pass;
    s_graph_t *graph;

    pass = true;
    graph = directed_graph_create();
    UNIT_TEST_BEGIN(directed_graph_create);

    RESULT_CHECK_bool(true, directed_graph_structure_legal_p(graph), &pass);

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_create, pass);
}

// static inline void
// utest_directed_graph_destroy(void)
// {
//     bool pass;
//     sint32 cost;
//     s_edge_t *edge;
//     s_graph_t *graph;
// 
//     pass = true;
//     cost = 0x234;
//     UNIT_TEST_BEGIN(directed_graph_destroy);
//     graph = test_directed_graph_sample(0x1e3d, 0x1002);
// 
//     directed_graph_destroy(NULL);
//     edge = directed_graph_link(graph, &edge, &graph, cost);
// 
//     directed_graph_edge_remove(graph, edge);
//     directed_graph_edge_destroy(&edge);
// 
//     directed_graph_destroy(&graph);
//     RESULT_CHECK_pointer(NULL, graph, &pass);
// 
//     UNIT_TEST_RESULT(directed_graph_destroy, pass);
// }

static inline void
utest_directed_graph_link(void)
{
    bool pass;
    void *tmp;
    sint32 cost;
    uint32 count;
    s_edge_t *edge;
    s_graph_t *graph;
    void *value_a, *value_b;

    pass = true;
    cost = 0x4d4;
    value_a = &pass;
    value_b = &graph;
    UNIT_TEST_BEGIN(directed_graph_link);
    graph = test_directed_graph_sample(0x2031, 0x1303);

    edge = directed_graph_link(NULL, value_a, value_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = directed_graph_link(graph, NULL, value_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = directed_graph_link(graph, value_b, NULL, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = directed_graph_link(graph, value_a, value_b, cost);
    RESULT_CHECK_sint32(cost, directed_graph_edge_cost(edge), &pass);

    tmp = directed_graph_edge_precursor_value(edge);
    RESULT_CHECK_pointer(value_a, tmp, &pass);

    tmp = directed_graph_edge_successor_value(edge);
    RESULT_CHECK_pointer(value_b, tmp, &pass);

    count = 0x3d1;
    while (count--) {
        edge = directed_graph_link(graph, value_a, value_b, cost);
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_link, pass);
}

