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

static inline void
utest_directed_graph_destroy(void)
{
    bool pass;
    sint32 cost;
    s_edge_t *edge;
    s_graph_t *graph;

    pass = true;
    cost = 0x234;
    UNIT_TEST_BEGIN(directed_graph_destroy);
    graph = test_directed_graph_sample(0x1e3d, 0x1002);

    directed_graph_destroy(NULL);
    edge = directed_graph_link(graph, &edge, &graph, cost);

    directed_graph_edge_remove(graph, edge);
    directed_graph_edge_destroy(&edge);

    directed_graph_destroy(&graph);
    RESULT_CHECK_pointer(NULL, graph, &pass);

    UNIT_TEST_RESULT(directed_graph_destroy, pass);
}

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
static inline void
utest_directed_graph_edge_remove(void)
{
    bool pass;
    sint32 cost;
    s_edge_t *edge, *edge_tmp;
    s_edge_array_t *edge_array;
    s_graph_t *graph, *graph_tmp;
    uint32 i, limit, edge_count, count;

    pass = true;
    cost = 0x20d;
    UNIT_TEST_BEGIN(directed_graph_edge_remove);
    graph = test_directed_graph_sample(0x1f2, 0x2d1e);

    edge = directed_graph_edge_remove(NULL, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    edge = directed_graph_edge_remove(graph, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, edge, &pass);

    graph_tmp = directed_graph_create();
    edge = directed_graph_link(graph_tmp, &pass, &cost, cost);
    edge_tmp = directed_graph_edge_remove(graph, edge);
    RESULT_CHECK_pointer(PTR_INVALID, edge_tmp, &pass);
    directed_graph_destroy(&graph_tmp);

    i = 0;
    edge_array = directed_graph_edge_array(graph);
    limit = directed_graph_edge_array_limit(edge_array);
    edge_count = directed_graph_edge_count(graph);

    while (i < limit) {
        edge = directed_graph_edge_array_edge(edge_array, i++);
        if (edge) {
            count = directed_graph_edge_count(graph);
            RESULT_CHECK_uint32(edge_count--, count, &pass);
            edge_tmp = directed_graph_edge_remove(graph, edge);
            RESULT_CHECK_pointer(edge_tmp, edge, &pass);
            directed_graph_edge_destroy(&edge_tmp);
        }
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_edge_remove, pass);
}

static inline void
utest_directed_graph_vertex_remove(void)
{
    bool pass;
    s_graph_t *graph;
    s_vertex_array_t *vertex_array;
    s_vertex_t *vertex, *vertex_tmp;
    uint32 i, limit, vertex_count, count;

    pass = true;
    UNIT_TEST_BEGIN(directed_graph_vertex_remove);
    graph = test_directed_graph_sample(0x1002, 0x2023);
    vertex_array = directed_graph_vertex_array(graph);

    vertex = directed_graph_vertex_remove(NULL, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, vertex, &pass);

    vertex = directed_graph_vertex_remove(graph, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, vertex, &pass);

    vertex = directed_graph_vertex_array_vertex(vertex_array, 0);
    vertex->index++;
    vertex_tmp = directed_graph_vertex_remove(graph, vertex);
    RESULT_CHECK_pointer(PTR_INVALID, vertex_tmp, &pass);
    vertex->index--;

    i = 0;
    limit = directed_graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = directed_graph_vertex_array_vertex(vertex_array, i++);

        if (vertex) {
            count = directed_graph_vertex_count(graph);
            vertex_tmp = directed_graph_vertex_remove(graph, vertex);
            vertex_count = directed_graph_vertex_count(graph);
            RESULT_CHECK_uint32(count - 1, vertex_count, &pass);
            RESULT_CHECK_pointer(vertex_tmp, vertex, &pass);
            directed_graph_link(graph, &count, vertex_tmp, 0);
            directed_graph_vertex_destroy(&vertex_tmp);
        }
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_vertex_remove, pass);
}

static inline void
utest_directed_graph_topo_sort(void)
{
    bool pass;
    bool is_succ;
    uint32 count;
    s_graph_t *graph;
    s_vertex_t *vertex, *v_succ;
    s_topo_list_t *topo_list, *topo_node;

    pass = true;
    count = 0x18;
    UNIT_TEST_BEGIN(directed_graph_topo_sort);

    RESULT_CHECK_pointer(PTR_INVALID, directed_graph_topo_sort(NULL), &pass);

    while (count--) {
        graph = test_directed_graph_sample(0x6d2 + count, 0x576 + count);
        topo_list = directed_graph_topo_sort(graph);

        if (topo_list) {
            topo_node = topo_list;
            vertex = directed_graph_topo_list_to_vertex(topo_node);

            while (directed_graph_topo_list_next(topo_node) != topo_list) {
                topo_node = directed_graph_topo_list_next(topo_node);
                v_succ = directed_graph_topo_list_to_vertex(topo_node);

                is_succ = directed_graph_vertex_successor_p(v_succ, vertex);
                RESULT_CHECK_bool(false, is_succ, &pass);

                vertex = v_succ;
            }
        }

        directed_graph_destroy(&graph);
    }

    graph = directed_graph_create();
    topo_list = directed_graph_topo_sort(graph);
    RESULT_CHECK_pointer(NULL, topo_list, &pass);

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_topo_sort, pass);
}

static inline bool
utest_directed_graph_path_exist_p(s_array_queue_t *queue)
{
    bool is_succ;
    s_vertex_t *vertex;
    s_vertex_t *v_successor;

    assert_exit(queue);

    vertex = array_queue_leave(queue);

    while (!array_queue_empty_p(queue)) {
        v_successor = array_queue_leave(queue);

        is_succ = directed_graph_vertex_successor_p(vertex, v_successor);

        if (!is_succ) {
            return false;
        }

        vertex = v_successor;
    }

    return true;
}

static inline void
utest_directed_graph_path_find(void)
{
    bool pass;
    bool is_existed;
    uint32 i, limit;
    s_graph_t *graph;
    s_array_queue_t *path;
    s_vertex_array_t *vertex_array;
    s_vertex_t *vertex_from, *vertex_to, *vertex;

    pass = true;
    vertex_from = vertex_to = NULL;
    UNIT_TEST_BEGIN(directed_graph_path_find);

    graph = test_directed_graph_sample(0x36d2, 0x2576);
    RESULT_CHECK_pointer(PTR_INVALID, directed_graph_path_find(NULL, NULL), &pass);

    i = 0;
    vertex_array = directed_graph_vertex_array(graph);
    limit = directed_graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = directed_graph_vertex_array_vertex(vertex_array, i);

        if (vertex && vertex_from == NULL) {
            vertex_from = vertex;
        } else if (vertex && vertex_to == NULL) {
            vertex_to = vertex;
        } else {
            path = directed_graph_path_find(vertex_from, vertex_to);

            if (path) {
                is_existed = utest_directed_graph_path_exist_p(path);
                RESULT_CHECK_bool(true, is_existed, &pass);

                vertex_from = vertex_to;
                vertex_to = NULL;
            }
        }

        i++;
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_path_find, pass);
}

static inline void
utest_directed_graph_dijkstra(void)
{
    bool pass;
    uint32 i, limit;
    s_graph_t *graph;
    s_vertex_t *vertex;
    s_dijkstra_table_t *dj_table;
    s_vertex_array_t *vertex_array;

    UNIT_TEST_BEGIN(directed_graph_dijkstra);

    pass = true;
    graph = test_directed_graph_sample(0x10, 0x9);

    i = 0;
    vertex_array = directed_graph_vertex_array(graph);
    limit = directed_graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = directed_graph_vertex_array_vertex(vertex_array);

        if (vertex) {
            break;
        }

        i++;
    }

    dj_table = directed_graph_dijkstra(graph, vertex);

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_dijkstra, pass);
}

