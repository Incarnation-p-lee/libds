static inline bool
graph_legal_p(s_graph_t *graph)
{
    if (NULL_PTR_P(graph)) {
        return false;
    } else if (NULL_PTR_P(graph->vertex_hash)) {
        return false;
    } else if (graph_vertex_array_illegal_p(graph->vertex_array)) {
        return false;
    } else if (graph_edge_array_illegal_p(graph->edge_array)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_illegal_p(s_graph_t *graph)
{
    return !graph_legal_p(graph);
}

static inline bool
graph_edge_array_legal_p(s_edge_array_t *edge_array)
{
    if (NULL_PTR_P(edge_array)) {
        return false;
    } else if (edge_array->index > edge_array->size) {
        return false;
    } else if (array_queue_structure_illegal_p(edge_array->queue)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_edge_array_illegal_p(s_edge_array_t *edge_array)
{
    return !graph_edge_array_legal_p(edge_array);
}

static inline bool
graph_vertex_array_legal_p(s_vertex_array_t *vertex_array)
{
    if (NULL_PTR_P(vertex_array)) {
        return false;
    } else if (vertex_array->index > vertex_array->size) {
        return false;
    } else if (array_queue_structure_illegal_p(vertex_array->queue)) {
        return false;
    } else if (NULL_PTR_P(vertex_array->array)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_vertex_array_illegal_p(s_vertex_array_t *vertex_array)
{
    return !graph_vertex_array_legal_p(vertex_array);
}

static inline bool
graph_edge_legal_p(s_edge_t *edge)
{
    if (NULL_PTR_P(edge)) {
        return false;
    } else if (NON_NULL_PTR_P(edge->precursor)) { /* include vertex_0 */
        return true;
    } else if (NON_NULL_PTR_P(edge->successor)) { /* include vertex_1 */
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_edge_illegal_p(s_edge_t *edge)
{
    return !graph_edge_legal_p(edge);
}

static inline bool
graph_adjacent_legal_p(s_adjacent_t *adjacent)
{
    if (NULL_PTR_P(adjacent)) {
        return false;
    } else if (adjacent->index > adjacent->size) {
        return false;
    } else if (adjacent->edge_count > adjacent->index) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_adjacent_illegal_p(s_adjacent_t *adjacent)
{
    return !graph_adjacent_legal_p(adjacent);
}

static inline bool
graph_vertex_legal_p(s_vertex_t *vertex)
{
    if (NULL_PTR_P(vertex)) {
        return false;
    } else if (graph_adjacent_legal_p(vertex->precursor)) {
        return true; /* include adjacent of indirected */
    } else if (graph_adjacent_legal_p(vertex->successor)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_vertex_illegal_p(s_vertex_t *vertex)
{
    return !graph_vertex_legal_p(vertex);
}

static inline bool
graph_topo_list_legal_p(s_topo_list_t *topo_list)
{
    if (NULL_PTR_P(topo_list)) {
        return false;
    } else if (doubly_linked_list_structure_illegal_p(&topo_list->list)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_topo_list_illegal_p(s_topo_list_t *topo_list)
{
    return !graph_topo_list_legal_p(topo_list);
}

static inline void
graph_vertex_print(s_vertex_t *vertex)
{
    s_edge_t *edge;
    uint32 i, limit;
    s_vertex_t *v_succ;
    s_adjacent_t *adjacent;

    assert_exit(graph_vertex_legal_p(vertex));

    printf("  vertex %p [label %4d, value %8p]:\n",
        vertex, graph_vertex_label(vertex), graph_vertex_value(vertex));

    i = 0;
    adjacent = graph_vertex_adjacent(vertex);
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) {
        edge = graph_adjacent_edge(adjacent, i);

        if (edge) {
            v_succ = graph_edge_successor(edge);
            printf("    [edge %p, cost %8d, successor %p %4d]\n",
                edge, graph_edge_cost(edge),
                v_succ, graph_vertex_label(v_succ));
        }

        i++;
    }
}

static inline void
graph_print_i(s_graph_t *graph)
{
    uint32 i, limit;
    s_vertex_t *vertex;
    s_vertex_array_t *vertex_array;

    assert_exit(graph_legal_p(graph));

    printf("Graph %p layout:\n", graph);

    i = 0;
    vertex_array = graph_vertex_array(graph);
    limit = graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = graph_vertex_array_vertex(vertex_array, i);

        if (vertex) {
            graph_vertex_print(vertex);
        }

        i++;
    }
}

void
graph_print(s_graph_t *graph)
{
    if (graph_legal_p(graph)) {
        graph_print_i(graph);
    }
}

static inline void
graph_dijkstra_table_print_i(s_dijkstra_table_t *dj_table)
{
    uint32 i, limit;
    s_dijkstra_entry_t *dj_entry;
    s_vertex_t *vertex, *vertex_pre;

    assert_exit(graph_dijkstra_table_legal_ip(dj_table));

    printf("Graph dijkstra table:\n");

    i = 0;
    limit = graph_dijkstra_table_limit(dj_table);

    while (i < limit) {
        dj_entry = graph_dijkstra_table_entry(dj_table, i);
        vertex = graph_dijkstra_entry_vertex(dj_entry);
        vertex_pre = graph_dijkstra_entry_vertex_pre(dj_entry);

        printf("    [Vertex %p %4d, Distance %8d, Previous %p %4d]\n",
               vertex, graph_vertex_label(vertex),
               graph_dijkstra_entry_distance(dj_entry),
               vertex_pre, graph_vertex_label(vertex_pre));

        i++;
    }
}

void
graph_dijkstra_table_print(s_dijkstra_table_t *dj_table)
{
    if (graph_dijkstra_table_legal_ip(dj_table)) {
        graph_dijkstra_table_print_i(dj_table);
    }
}

