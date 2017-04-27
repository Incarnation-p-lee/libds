static inline void
utest_indirected_graph_create(void)
{
    bool pass;
    s_graph_t *graph;

    pass = true;
    graph = indirected_graph_create();
    UNIT_TEST_BEGIN(indirected_graph_create);

    RESULT_CHECK_bool(true, indirected_graph_structure_legal_p(graph), &pass);

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_create, pass);
}

static inline void
utest_indirected_graph_link(void)
{
    bool pass;
    void *tmp;
    sint32 cost;
    void *vertex_a;
    void *vertex_b;
    s_edge_t *edge;
    s_graph_t *graph;

    pass = true;
    cost = 0x234;
    vertex_a = &pass;
    vertex_b = &graph;
    graph = test_indirected_graph_sample(0x121, 0x1e3);
    UNIT_TEST_BEGIN(indirected_graph_link);

    edge = indirected_graph_link(NULL, vertex_a, vertex_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, NULL, vertex_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, vertex_b, NULL, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, vertex_a, vertex_b, cost);
    RESULT_CHECK_sint32(cost, indirected_graph_edge_cost(edge), &pass);

    tmp = indirected_graph_edge_vertex_0_value(edge);
    RESULT_CHECK_pointer(vertex_a, tmp, &pass);

    tmp = indirected_graph_edge_vertex_1_value(edge);
    RESULT_CHECK_pointer(vertex_b, tmp, &pass);

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_link, pass);
}


