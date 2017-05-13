bool
directed_graph_structure_legal_p(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return false;
    } else if (graph_attribute_indirected_p(graph)) {
        return false;
    } else {
        return true;
    }
}

bool
directed_graph_structure_illegal_p(s_graph_t *graph)
{
    return !directed_graph_structure_legal_p(graph);
}

sint32
directed_graph_edge_cost(s_edge_t *edge)
{
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return GRAPH_COST_INVALID;
    } else {
        return graph_edge_cost(edge);
    }
}

void *
directed_graph_edge_successor_value(s_edge_t *edge)
{
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_successor_value(edge);
    }
}

void *
directed_graph_edge_precursor_value(s_edge_t *edge)
{
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_precursor_value(edge);
    }
}

s_vertex_array_t *
directed_graph_vertex_array(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else {
        return graph_vertex_array(graph);
    }
}

s_edge_array_t *
directed_graph_edge_array(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else {
        return graph_edge_array(graph);
    }
}

uint32
directed_graph_edge_array_limit(s_edge_array_t *edge_array)
{
    if (GRAPH_EDGE_ARRAY_ILLEGAL_P(edge_array)) {
        return SIZE_INVALID;
    } else {
        return graph_edge_array_limit(edge_array);
    }
}

s_edge_t *
directed_graph_edge_array_edge(s_edge_array_t *edge_array, uint32 i)
{
    if (GRAPH_EDGE_ARRAY_ILLEGAL_P(edge_array)) {
        return PTR_INVALID;
    } else if (i > graph_edge_array_limit(edge_array)) {
        return PTR_INVALID;
    } else {
        return graph_edge_array_edge(edge_array, i);
    }
}

s_vertex_t *
directed_graph_vertex_array_vertex(s_vertex_array_t *vertex_array, uint32 i)
{
    if (GRAPH_VERTEX_ARRAY_ILLEGAL_P(vertex_array)) {
        return PTR_INVALID;
    } else if (i > graph_vertex_array_limit(vertex_array)) {
        return PTR_INVALID;
    } else {
        return graph_vertex_array_vertex(vertex_array, i);
    }
}

uint32
directed_graph_vertex_array_limit(s_vertex_array_t *vertex_array)
{
    if (GRAPH_VERTEX_ARRAY_ILLEGAL_P(vertex_array)) {
        return SIZE_INVALID;
    } else {
        return graph_vertex_array_limit(vertex_array);
    }
}

uint32
directed_graph_vertex_count(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return SIZE_INVALID;
    } else {
        return graph_attribute_vertex_count(graph);
    }
}

uint32
directed_graph_edge_count(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return SIZE_INVALID;
    } else {
        return graph_attribute_edge_count(graph);
    }
}

s_graph_t *
directed_graph_create(void)
{
    s_graph_t *graph;

    graph = graph_create();

    graph_attribute_directed_set(graph, /* is_directed = */true);

    return graph;
}

void
directed_graph_destroy(s_graph_t **graph)
{
    if (NON_NULL_PTR_P(graph) && DIRECTED_GRAPH_LEGAL_P(*graph)) {
        graph_destroy(*graph);
        *graph = NULL;
    }
}

static inline s_vertex_t *
directed_graph_vertex_create(s_graph_t *graph, void *value)
{
    s_vertex_t *vertex;

    assert_exit(directed_graph_structure_legal_p(graph));

    vertex = graph_vertex_create(graph, value);
    vertex->precursor = graph_adjacent_create();
    vertex->successor = graph_adjacent_create();

    graph_vertex_array_add(graph_vertex_array(graph), vertex);
    open_addressing_hash_insert(graph_vertex_hash(graph), value);
    graph_attribute_vertex_inc(graph);

    return vertex;
}

static inline s_edge_t *
directed_graph_edge_create(s_graph_t *graph, s_vertex_t *vertex_from,
    s_vertex_t *vertex_to, sint32 cost)
{
    s_edge_t *edge;

    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph_vertex_structure_legal_p(vertex_from));
    assert_exit(graph_vertex_structure_legal_p(vertex_to));

    edge = graph_edge_create(cost);
    edge->precursor = vertex_from;
    edge->successor = vertex_to;

    graph_edge_array_add(graph_edge_array(graph), edge);
    graph_attribute_edge_inc(graph);

    return edge;
}

static inline s_adjacent_t *
directed_graph_vertex_precursor(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->precursor;
}

static inline s_adjacent_t *
directed_graph_vertex_successor(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->successor;
}

static inline void
directed_graph_edge_link(s_edge_t *edge, s_vertex_t *vertex_from,
    s_vertex_t *vertex_to)
{
    s_adjacent_t *precursor;
    s_adjacent_t *successor;

    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_vertex_structure_legal_p(vertex_from));
    assert_exit(graph_vertex_structure_legal_p(vertex_to));

    precursor = directed_graph_vertex_precursor(vertex_to);
    successor = directed_graph_vertex_successor(vertex_from);

    graph_adjacent_append(precursor, edge);
    graph_adjacent_append(successor, edge);
}

static inline s_vertex_t *
directed_graph_vertex_obtain(s_graph_t *graph, void *value)
{
    s_vertex_array_t *vertex_array;

    assert_exit(directed_graph_structure_legal_p(graph));

    vertex_array = graph_vertex_array(graph);

    if (graph_vertex_value_exist_p(graph, value)) {
        return graph_vertex_array_find(vertex_array, value);
    } else {
        return directed_graph_vertex_create(graph, value);
    }
}

static inline s_edge_t *
directed_graph_link_i(s_graph_t *graph, void *value_from, void *value_to,
    sint32 cost)
{
    s_edge_t *edge;
    s_vertex_t *vertex_to;
    s_vertex_t *vertex_from;

    assert_exit(directed_graph_structure_legal_p(graph));
    assert_exit(value_from && value_to);

    vertex_from = directed_graph_vertex_obtain(graph, value_from);
    vertex_to = directed_graph_vertex_obtain(graph, value_to);
    edge = directed_graph_edge_create(graph, vertex_from, vertex_to, cost);

    directed_graph_edge_link(edge, vertex_from, vertex_to);

    return edge;
}

s_edge_t *
directed_graph_link(s_graph_t *graph, void *value_from, void *value_to,
    sint32 cost)
{
    if (DIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_from)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_to)) {
        return PTR_INVALID;
    } else {
        return directed_graph_link_i(graph, value_from, value_to, cost);
    }
}


