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
        return graph_vertex_array_count(graph_vertex_array(graph));
    }
}

uint32
directed_graph_edge_count(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return SIZE_INVALID;
    } else {
        return graph_edge_array_count(graph_edge_array(graph));
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

    return edge;
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

    precursor = graph_vertex_precursor(vertex_to);
    successor = graph_vertex_successor(vertex_from);

    graph_adjacent_edge_append(precursor, edge);
    graph_adjacent_edge_append(successor, edge);
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

static inline s_edge_t *
directed_graph_edge_remove_i(s_graph_t *graph, s_edge_t *edge)
{
    uint32 index;
    s_adjacent_t *adjacent;
    s_edge_array_t *edge_array;
    s_vertex_t *v_precursor, *v_successor;

    assert_exit(directed_graph_structure_legal_p(graph));
    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_edge_compatible_p(graph, edge));

    v_precursor = graph_edge_precursor(edge);
    v_successor = graph_edge_successor(edge);

    adjacent = graph_vertex_successor(v_precursor);
    graph_adjacent_edge_remove(adjacent, edge);

    adjacent = graph_vertex_precursor(v_successor);
    graph_adjacent_edge_remove(adjacent, edge);

    index = graph_edge_index(edge);
    edge_array = graph_edge_array(graph);
    graph_edge_array_remove(edge_array, index);

    return edge;
}

s_edge_t *
directed_graph_edge_remove(s_graph_t *graph, s_edge_t *edge)
{
    if (DIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else if (graph_edge_incompatible_p(graph, edge)) {
        return PTR_INVALID;
    } else {
        return directed_graph_edge_remove_i(graph, edge);
    }
}

static inline void
directed_graph_vertex_cleanup(s_vertex_t *vertex, s_edge_array_t *edge_array)
{
    s_edge_t *edge;
    uint32 i, limit;
    s_adjacent_t *adj_precursor, *adj_successor, *adjacent;

    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    adj_precursor = graph_vertex_precursor(vertex);
    adj_successor = graph_vertex_successor(vertex);

    i = 0;
    limit = graph_adjacent_limit(adj_precursor);
    /* cleanup precursor */
    while (i < limit) {
        edge = graph_adjacent_edge(adj_precursor, i);

        if (edge) {
            adjacent = graph_vertex_successor(graph_edge_precursor(edge));
            graph_adjacent_edge_remove(adjacent, edge);
            graph_edge_array_edge_destroy(edge_array, edge);
        }

        i++;
    }

    i = 0;
    limit = graph_adjacent_limit(adj_successor);
    /* cleanup successor */
    while (i < limit) {
        edge = graph_adjacent_edge(adj_successor, i);

        if (edge) {
            adjacent = graph_vertex_precursor(graph_edge_successor(edge));
            graph_adjacent_edge_remove(adjacent, edge);
            graph_edge_array_edge_destroy(edge_array, edge);
        }

        i++;
    }

    graph_adjacent_cleanup(adj_precursor);
    graph_adjacent_cleanup(adj_successor);
}

static inline s_vertex_t *
directed_graph_vertex_remove_i(s_graph_t *graph, s_vertex_t *vertex)
{
    uint32 i;
    s_edge_array_t *edge_array;
    s_vertex_array_t *vertex_array;

    assert_exit(directed_graph_structure_legal_p(graph));
    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_vertex_compatible_p(graph, vertex));

    edge_array = graph_edge_array(graph);
    directed_graph_vertex_cleanup(vertex, edge_array);

    i = graph_vertex_index(vertex);
    vertex_array = graph_vertex_array(graph);

    graph_vertex_array_remove(vertex_array, i);
    open_addressing_hash_remove(graph_vertex_hash(graph), vertex->value);

    return vertex;
}

s_vertex_t *
directed_graph_vertex_remove(s_graph_t *graph, s_vertex_t *vertex)
{
    if (DIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (GRAPH_VERTEX_ILLEGAL_P(vertex)) {
        return PTR_INVALID;
    } else if (graph_vertex_incompatible_p(graph, vertex)) {
        return PTR_INVALID;
    } else {
        return directed_graph_vertex_remove_i(graph, vertex);
    }
}

void
directed_graph_edge_destroy(s_edge_t **edge)
{
    if (NON_NULL_PTR_P(edge) && GRAPH_EDGE_LEGAL_P(*edge)) {
        graph_edge_destroy(*edge);

        *edge = NULL;
    }
}

void
directed_graph_vertex_destroy(s_vertex_t **vertex)
{
    if (NON_NULL_PTR_P(vertex) && GRAPH_VERTEX_LEGAL_P(*vertex)) {
        graph_adjacent_destroy((*vertex)->precursor);
        graph_adjacent_destroy((*vertex)->successor);
        memory_cache_free(*vertex);

        *vertex = NULL;
    }
}

