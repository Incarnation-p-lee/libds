static inline void
utest_indirected_graph_util(void)
{
    bool pass;
    s_graph_t *graph;

    pass = true;
    graph = test_indirected_graph_sample(0xa, 0x6);

    UNIT_TEST_BEGIN(indirected_graph_util);

    RESULT_CHECK_bool(true, indirected_graph_legal_p(graph), &pass);
    RESULT_CHECK_bool(false, indirected_graph_legal_p(NULL), &pass);
    RESULT_CHECK_bool(false, indirected_graph_illegal_p(graph), &pass);

    graph->attribute.is_directed = true;
    RESULT_CHECK_bool(false, indirected_graph_legal_p(graph), &pass);
    RESULT_CHECK_bool(true, indirected_graph_illegal_p(graph), &pass);
    graph->attribute.is_directed = false;

    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_edge_array(NULL), &pass);
    RESULT_CHECK_uint32(SIZE_INVALID, indirected_graph_edge_array_limit(NULL), &pass);
    RESULT_CHECK_sint32(GRAPH_COST_INVALID, indirected_graph_edge_cost(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_edge_vertex_0_value(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_edge_vertex_1_value(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_edge_array_edge(NULL, 0), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_vertex_array(NULL), &pass);
    RESULT_CHECK_pointer(PTR_INVALID, indirected_graph_vertex_array_vertex(NULL, 0), &pass);
    RESULT_CHECK_uint32(SIZE_INVALID, indirected_graph_vertex_array_limit(NULL), &pass);
    RESULT_CHECK_uint32(SIZE_INVALID, indirected_graph_edge_array_limit(NULL), &pass);
    RESULT_CHECK_uint32(SIZE_INVALID, indirected_graph_edge_count(NULL), &pass);

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_util, pass);
}

static inline void
utest_indirected_graph_create(void)
{
    bool pass;
    s_graph_t *graph;

    pass = true;
    graph = indirected_graph_create();
    UNIT_TEST_BEGIN(indirected_graph_create);

    RESULT_CHECK_bool(true, indirected_graph_legal_p(graph), &pass);

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_create, pass);
}

static inline void
utest_indirected_graph_destroy(void)
{
    bool pass;
    sint32 cost;
    s_edge_t *edge;
    s_graph_t *graph;

    pass = true;
    cost = 0x234;
    UNIT_TEST_BEGIN(indirected_graph_destroy);
    graph = test_indirected_graph_sample(0x1098, 0x1de3);

    indirected_graph_destroy(NULL);
    edge = indirected_graph_link(graph, &edge, &graph, cost);

    indirected_graph_edge_remove(graph, edge);
    indirected_graph_edge_destroy(&edge);

    indirected_graph_destroy(&graph);
    RESULT_CHECK_pointer(NULL, graph, &pass);

    UNIT_TEST_RESULT(indirected_graph_destroy, pass);
}

static inline void
utest_indirected_graph_link(void)
{
    bool pass;
    void *tmp;
    sint32 cost;
    uint32 count;
    s_edge_t *edge;
    s_graph_t *graph;
    void *value_a, *value_b;

    pass = true;
    cost = 0x234;
    value_a = &pass;
    value_b = &graph;
    UNIT_TEST_BEGIN(indirected_graph_link);
    graph = test_indirected_graph_sample(0x2121, 0x11e3);

    edge = indirected_graph_link(NULL, value_a, value_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, NULL, value_b, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, value_b, NULL, cost);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_link(graph, value_a, value_b, cost);
    RESULT_CHECK_sint32(cost, indirected_graph_edge_cost(edge), &pass);

    tmp = indirected_graph_edge_vertex_0_value(edge);
    RESULT_CHECK_pointer(value_a, tmp, &pass);

    tmp = indirected_graph_edge_vertex_1_value(edge);
    RESULT_CHECK_pointer(value_b, tmp, &pass);

    count = 0x123;
    while (count--) {
        edge = indirected_graph_link(graph, value_a, value_b, cost);
    }

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_link, pass);
}

static inline void
utest_indirected_graph_edge_remove(void)
{
    bool pass;
    sint32 cost;
    s_edge_t *edge, *edge_tmp;
    s_edge_array_t *edge_array;
    s_graph_t *graph, *graph_tmp;
    uint32 i, limit, edge_count, count;

    pass = true;
    cost = 0x23d;
    UNIT_TEST_BEGIN(indirected_graph_edge_remove);
    graph = test_indirected_graph_sample(0x2ed, 0x10cd);

    edge = indirected_graph_edge_remove(NULL, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = indirected_graph_edge_remove(graph, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    graph_tmp = indirected_graph_create();
    edge = indirected_graph_link(graph_tmp, &pass, &cost, cost);
    edge_tmp = indirected_graph_edge_remove(graph, edge);
    RESULT_CHECK_pointer(PTR_INVALID, edge_tmp, &pass);
    indirected_graph_destroy(&graph_tmp);

    i = 0;
    edge_array = indirected_graph_edge_array(graph);
    limit = indirected_graph_edge_array_limit(edge_array);
    edge_count = indirected_graph_edge_count(graph);

    while (i < limit) {
        edge = indirected_graph_edge_array_edge(edge_array, i++);
        if (edge) {
            count = indirected_graph_edge_count(graph);
            RESULT_CHECK_uint32(edge_count--, count, &pass);
            edge_tmp = indirected_graph_edge_remove(graph, edge);
            RESULT_CHECK_pointer(edge_tmp, edge, &pass);
            indirected_graph_edge_destroy(&edge_tmp);
        }
    }

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_edge_remove, pass);
}

static inline void
utest_indirected_graph_vertex_remove(void)
{
    bool pass;
    s_graph_t *graph;
    s_vertex_array_t *vertex_array;
    s_vertex_t *vertex, *vertex_tmp;
    uint32 i, limit, vertex_count, count;

    pass = true;
    UNIT_TEST_BEGIN(indirected_graph_vertex_remove);
    graph = test_indirected_graph_sample(0x3ed, 0x12d9);
    vertex_array = indirected_graph_vertex_array(graph);

    vertex = indirected_graph_vertex_remove(NULL, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, vertex, &pass);

    vertex = indirected_graph_vertex_remove(graph, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, vertex, &pass);

    vertex = indirected_graph_vertex_array_vertex(vertex_array, 0);
    vertex->index++;
    vertex_tmp = indirected_graph_vertex_remove(graph, vertex);
    RESULT_CHECK_pointer(PTR_INVALID, vertex_tmp, &pass);
    vertex->index--;

    i = 0;
    limit = indirected_graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = indirected_graph_vertex_array_vertex(vertex_array, i++);

        if (vertex) {
            count = indirected_graph_vertex_count(graph);
            vertex_tmp = indirected_graph_vertex_remove(graph, vertex);
            vertex_count = indirected_graph_vertex_count(graph);
            RESULT_CHECK_uint32(count - 1, vertex_count, &pass);
            RESULT_CHECK_pointer(vertex_tmp, vertex, &pass);
            indirected_graph_link(graph, &count, vertex_tmp, 0);
            indirected_graph_vertex_destroy(&vertex_tmp);
        }
    }

    indirected_graph_destroy(&graph);
    UNIT_TEST_RESULT(indirected_graph_vertex_remove, pass);
}

