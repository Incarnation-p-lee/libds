bool
indirected_graph_structure_legal_p(s_graph_t *graph)
{
    if (graph_structure_illegal_p(graph)) {
        return false;
    } else if (graph_attribute_directed_p(graph)) {
        return false;
    } else {
        return true;
    }
}

bool
indirected_graph_structure_illegal_p(s_graph_t *graph)
{
    return !indirected_graph_structure_legal_p(graph);
}

sint32
indirected_graph_edge_cost(s_edge_t *edge)
{
    if (graph_edge_structure_illegal_p(edge)) {
        return GRAPH_COST_INVALID;
    } else {
        return graph_edge_cost(edge);
    }
}

void *
indirected_graph_edge_vertex_0_value(s_edge_t *edge)
{
    if (graph_edge_structure_illegal_p(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_vertex_0_value(edge);
    }
}

void *
indirected_graph_edge_vertex_1_value(s_edge_t *edge)
{
    if (graph_edge_structure_illegal_p(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_vertex_1_value(edge);
    }
}

s_graph_t *
indirected_graph_create(void)
{
    s_graph_t *graph;

    graph = graph_create();

    graph_attribute_directed_set(graph, /* is_directed = */false);

    return graph;
}

void
indirected_graph_destroy(s_graph_t **graph)
{
    if (NON_NULL_PTR_P(graph) && indirected_graph_structure_legal_p(*graph)) {
        graph_destroy(*graph);
        *graph = NULL;
    }
}

static inline s_adjacent_t *
indirected_graph_vertex_adjacent(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->adjacent;
}

static inline void
indirected_graph_vertex_edge_append(s_vertex_t *vertex, s_edge_t *edge)
{
    s_adjacent_t *adjacent;

    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_edge_structure_legal_p(edge));

    adjacent = indirected_graph_vertex_adjacent(vertex);
    graph_adjacent_append(adjacent, edge);
}

static inline s_edge_t *
indirected_graph_edge_create(s_vertex_t *vertex_a, s_vertex_t *vertex_b,
    sint32 cost)
{
    s_edge_t *edge;

    assert_exit(graph_vertex_structure_legal_p(vertex_a));
    assert_exit(graph_vertex_structure_legal_p(vertex_b));

    edge = graph_edge_create(cost);

    edge->vertex_0 = vertex_a;
    edge->vertex_1 = vertex_b;

    return edge;
}

static inline s_edge_t *
indirected_graph_vertex_link(s_vertex_t *vertex_a, s_vertex_t *vertex_b,
    sint32 cost)
{
    s_edge_t *edge;

    assert_exit(graph_vertex_structure_legal_p(vertex_a));
    assert_exit(graph_vertex_structure_legal_p(vertex_b));

    edge = indirected_graph_edge_create(vertex_a, vertex_b, cost);

    indirected_graph_vertex_edge_append(vertex_a, edge);
    indirected_graph_vertex_edge_append(vertex_b, edge);

    return edge;
}

static inline s_vertex_t *
indirected_graph_vertex_create(s_graph_t *graph, void *value)
{
    s_vertex_t *vertex;

    assert_exit(indirected_graph_structure_legal_p(graph));

    vertex = graph_vertex_create(graph, value);
    vertex->adjacent = graph_adjacent_create();

    graph_vertex_array_add(graph->vertex_array, vertex);

    return vertex;
}

static inline s_edge_t *
indirected_graph_link_i(s_graph_t *graph, void *value_a, void *value_b,
    sint32 cost)
{
    s_vertex_t *vertex_a;
    s_vertex_t *vertex_b;
    s_open_addressing_hash_t *vertex_hash;

    assert_exit(indirected_graph_structure_legal_p(graph));
    assert_exit(value_a && value_b);

    vertex_hash = graph_vertex_hash(graph);

    if (open_addressing_hash_find(vertex_hash, value_a) == NULL) {
        vertex_a = indirected_graph_vertex_create(graph, value_a);
    }

    if (open_addressing_hash_find(vertex_hash, value_b) == NULL) {
        vertex_b = indirected_graph_vertex_create(graph, value_b);
    }

    return indirected_graph_vertex_link(vertex_a, vertex_b, cost);
}

s_edge_t *
indirected_graph_link(s_graph_t *graph, void *value_a, void *value_b,
    sint32 cost)
{
    if (indirected_graph_structure_illegal_p(graph)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_a)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_b)) {
        return PTR_INVALID;
    } else {
        return indirected_graph_link_i(graph, value_a, value_b, cost);
    }
}

