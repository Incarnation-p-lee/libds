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
utest_directed_graph_valid_path_p(s_array_queue_t *queue)
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

static inline bool
utest_directed_graph_paths_exist_p(s_graph_paths_t *paths)
{
    s_array_queue_t *path;
    s_array_queue_t *paths_queue;
    s_array_iterator_t *iterator;

    assert_exit(directed_graph_paths_legal_p(paths));

    paths_queue = directed_graph_paths_queue(paths);
    iterator = array_queue_iterator_obtain(paths_queue);
    assert_exit(NON_NULL_PTR_P(iterator));

    iterator->fp_index_initial(paths_queue);

    while (iterator->fp_next_exist_p(paths_queue)) {
        path = iterator->fp_next_obtain(paths_queue);

        if (!utest_directed_graph_valid_path_p(path)) {
            return false;
        }
    }

    return true;
}

static inline void
utest_directed_graph_paths_find(void)
{
    bool pass;
    bool is_existed;
    uint32 i, limit;
    s_graph_t *graph;
    s_graph_paths_t *paths;
    s_vertex_array_t *vertex_array;
    s_vertex_t *vertex_from, *vertex_to, *vertex;

    pass = true;
    vertex_from = vertex_to = NULL;
    UNIT_TEST_BEGIN(directed_graph_paths_find);

    graph = test_directed_graph_sample(0x36d2, 0x2576);
    paths = directed_graph_paths_find(graph, NULL, NULL);
    RESULT_CHECK_pointer(PTR_INVALID, paths, &pass);

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
            paths = directed_graph_paths_find(graph, vertex_from, vertex_to);

            if (directed_graph_paths_legal_p(paths)) {
                is_existed = utest_directed_graph_paths_exist_p(paths);
                RESULT_CHECK_bool(true, is_existed, &pass);

                vertex_from = vertex_to;
                vertex_to = NULL;
            }

            directed_graph_paths_destroy(&paths);
        }

        i++;
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_paths_find, pass);
}

static inline uint32
utest_directed_graph_minimal_path(s_graph_paths_t *paths)
{
    uint32 len, len_tmp;
    s_array_queue_t *path;
    s_array_queue_t *paths_queue;
    s_array_iterator_t *iterator;

    assert_exit(directed_graph_paths_legal_p(paths));

    len = U32_MAX;

    paths_queue = directed_graph_paths_queue(paths);
    iterator = array_queue_iterator_obtain(paths_queue);

    iterator->fp_index_initial(paths_queue);

    while (iterator->fp_next_exist_p(paths_queue)) {
        path = iterator->fp_next_obtain(paths_queue);
        len_tmp = directed_graph_path_length(path);

        if (len_tmp < len) {
            len = len_tmp;
        }
    }

    return len;
}

static inline bool
utest_directed_graph_dijkstra_valid_p(s_graph_t *graph, s_vertex_t *vertex,
    s_dijkstra_table_t *dj_table)
{
    uint32 i, limit;
    uint32 distance, len;
    s_graph_paths_t *paths;
    s_dijkstra_entry_t *dj_entry;
    s_vertex_t *vertex_from, *vertex_to;

    assert_exit(directed_graph_structure_legal_p(graph));
    assert_exit(directed_graph_dijkstra_table_legal_p(dj_table));

    vertex_from = vertex;

    limit = directed_graph_dijkstra_table_limit(dj_table);

    for (i = 0; i < limit; i++) {
        dj_entry = directed_graph_dijkstra_table_entry(dj_table, i);
        vertex_to = directed_graph_dijkstra_entry_vertex(dj_entry);

        if (vertex_to == vertex_from) {
            continue;
        }

        paths = directed_graph_paths_find(graph, vertex_from, vertex_to);

        if (directed_graph_paths_legal_p(paths)) {
            len = utest_directed_graph_minimal_path(paths);
            distance = directed_graph_dijkstra_entry_distance(dj_entry);

            if (len != distance) {
                return false;
            }
        }

        directed_graph_paths_destroy(&paths);
    }

    return true;
}

static inline void
utest_directed_graph_dijkstra(void)
{
    uint32 i, limit;
    s_graph_t *graph;
    s_vertex_t *vertex;
    bool pass, is_valid;
    s_dijkstra_table_t *table;
    s_vertex_array_t *vertex_array;

    UNIT_TEST_BEGIN(directed_graph_dijkstra);

    pass = true;
    graph = test_directed_graph_connected_sample(0x120, 0x27);

    vertex = NULL;
    vertex_array = directed_graph_vertex_array(graph);
    limit = directed_graph_vertex_array_limit(vertex_array);

    for (i = 0; i < limit; i++) {
        vertex = directed_graph_vertex_array_vertex(vertex_array, i);

        if (vertex == NULL) {
            continue;
        }

        table = directed_graph_dijkstra(graph, vertex);
        is_valid = utest_directed_graph_dijkstra_valid_p(graph, vertex, table);
        RESULT_CHECK_bool(true, is_valid, &pass);
        directed_graph_dijkstra_table_destroy(&table);
    }

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_dijkstra, pass);
}

