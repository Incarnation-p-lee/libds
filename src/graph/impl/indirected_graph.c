bool
indirected_graph_structure_legal_p(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
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
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return GRAPH_COST_INVALID;
    } else {
        return graph_edge_cost(edge);
    }
}

void *
indirected_graph_edge_vertex_0_value(s_edge_t *edge)
{
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_vertex_0_value(edge);
    }
}

void *
indirected_graph_edge_vertex_1_value(s_edge_t *edge)
{
    if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else {
        return graph_edge_vertex_1_value(edge);
    }
}

s_vertex_array_t *
indirected_graph_vertex_array(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else {
        return graph_vertex_array(graph);
    }
}

s_edge_array_t *
indirected_graph_edge_array(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else {
        return graph_edge_array(graph);
    }
}

uint32
indirected_graph_edge_array_limit(s_edge_array_t *edge_array)
{
    if (GRAPH_EDGE_ARRAY_ILLEGAL_P(edge_array)) {
        return SIZE_INVALID;
    } else {
        return graph_edge_array_limit(edge_array);
    }
}

s_edge_t *
indirected_graph_edge_array_edge(s_edge_array_t *edge_array, uint32 i)
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
indirected_graph_vertex_array_vertex(s_vertex_array_t *vertex_array, uint32 i)
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
indirected_graph_vertex_array_limit(s_vertex_array_t *vertex_array)
{
    if (GRAPH_VERTEX_ARRAY_ILLEGAL_P(vertex_array)) {
        return SIZE_INVALID;
    } else {
        return graph_vertex_array_limit(vertex_array);
    }
}

uint32
indirected_graph_vertex_count(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return SIZE_INVALID;
    } else {
        return graph_vertex_array_count(graph_vertex_array(graph));
    }
}

uint32
indirected_graph_edge_count(s_graph_t *graph)
{
    if (GRAPH_ILLEGAL_P(graph)) {
        return SIZE_INVALID;
    } else {
        return graph_edge_array_count(graph_edge_array(graph));
    }
}

static inline bool
indirected_graph_edge_vertex_contains_p(s_edge_t *edge, s_vertex_t *vertex)
{
    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_vertex_structure_legal_p(vertex));

    if (vertex == graph_edge_vertex_0(edge)) {
        return true;
    } else if (vertex == graph_edge_vertex_1(edge)) {
        return true;
    } else {
        return false;
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
    if (NON_NULL_PTR_P(graph) && INDIRECTED_GRAPH_LEGAL_P(*graph)) {
        graph_destroy(*graph);
        *graph = NULL;
    }
}

static inline s_edge_t *
indirected_graph_edge_create(s_graph_t *graph, s_vertex_t *vertex_a,
    s_vertex_t *vertex_b, sint32 cost)
{
    s_edge_t *edge;

    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph_vertex_structure_legal_p(vertex_a));
    assert_exit(graph_vertex_structure_legal_p(vertex_b));

    edge = graph_edge_create(cost);
    edge->vertex_0 = vertex_a;
    edge->vertex_1 = vertex_b;

    graph_edge_array_add(graph->edge_array, edge);

    return edge;
}

static inline s_vertex_t *
indirected_graph_vertex_create(s_graph_t *graph, void *value)
{
    s_vertex_t *vertex;

    assert_exit(indirected_graph_structure_legal_p(graph));

    vertex = graph_vertex_create(graph, value);
    vertex->adjacent = graph_adjacent_create();

    graph_vertex_array_add(graph_vertex_array(graph), vertex);
    open_addressing_hash_insert(graph_vertex_hash(graph), value);

    return vertex;
}

static inline void
indirected_graph_edge_link(s_edge_t *edge, s_vertex_t *vertex_a,
    s_vertex_t *vertex_b)
{
    s_adjacent_t *adjacent;

    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_vertex_structure_legal_p(vertex_a));
    assert_exit(graph_vertex_structure_legal_p(vertex_b));

    adjacent = graph_vertex_adjacent(vertex_a);
    graph_adjacent_edge_append(adjacent, edge);

    if (vertex_a != vertex_b) { /* loop edge append once */
        adjacent = graph_vertex_adjacent(vertex_b);
        graph_adjacent_edge_append(adjacent, edge);
    }
}

static inline s_vertex_t *
indirected_graph_vertex_obtain(s_graph_t *graph, void *value)
{
    s_vertex_array_t *vertex_array;

    assert_exit(indirected_graph_structure_legal_p(graph));

    vertex_array = graph_vertex_array(graph);

    if (graph_vertex_value_exist_p(graph, value)) {
        return graph_vertex_array_find(vertex_array, value);
    } else {
        return indirected_graph_vertex_create(graph, value);
    }
}

static inline s_edge_t *
indirected_graph_link_i(s_graph_t *graph, void *value_a, void *value_b,
    sint32 cost)
{
    s_edge_t *edge;
    s_vertex_t *vertex_a;
    s_vertex_t *vertex_b;

    assert_exit(indirected_graph_structure_legal_p(graph));
    assert_exit(value_a && value_b);

    vertex_a = indirected_graph_vertex_obtain(graph, value_a);
    vertex_b = indirected_graph_vertex_obtain(graph, value_b);
    edge = indirected_graph_edge_create(graph, vertex_a, vertex_b, cost);

    indirected_graph_edge_link(edge, vertex_a, vertex_b);

    return edge;
}

s_edge_t *
indirected_graph_link(s_graph_t *graph, void *value_a, void *value_b,
    sint32 cost)
{
    if (INDIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_a)) {
        return PTR_INVALID;
    } else if (NULL_PTR_P(value_b)) {
        return PTR_INVALID;
    } else {
        return indirected_graph_link_i(graph, value_a, value_b, cost);
    }
}

// static inline bool
// indirected_graph_vertex_alone_p(s_vertex_t *vertex)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     return graph_adjacent_empty_p(vertex->adjacent);
// }

static inline void
indirected_graph_vertex_edge_remove(s_vertex_t *vertex, s_edge_t *edge)
{
    uint32 i, limit;
    s_edge_t *edge_tmp;
    s_adjacent_t *adjacent;

    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_vertex_structure_legal_p(vertex));

    i = 0;
    adjacent = graph_vertex_adjacent(vertex);
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) {
        edge_tmp = graph_adjacent_edge(adjacent, i);

        if (edge_tmp != NULL && edge_tmp == edge) {
            graph_adjacent_edge_remove(adjacent, i);
            return;
        }

        i++;
    }

    pr_log_warn("No such of the edge in given vertex.\n");
}

static inline s_edge_t *
indirected_graph_edge_remove_i(s_graph_t *graph, s_edge_t *edge)
{
    uint32 index;
    s_vertex_t *vertex;
    s_edge_array_t *edge_array;

    assert_exit(indirected_graph_structure_legal_p(graph));
    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_edge_compatible_p(graph, edge));

    index = graph_edge_index(edge);
    vertex = graph_edge_vertex_0(edge);

    indirected_graph_vertex_edge_disconnet(vertex, edge);
    indirected_graph_vertex_edge_remove(vertex, edge);

    edge_array = graph_edge_array(graph);
    graph_edge_array_remove(edge_array, index);

    return edge;
}

s_edge_t *
indirected_graph_edge_remove(s_graph_t *graph, s_edge_t *edge)
{
    if (INDIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (GRAPH_EDGE_ILLEGAL_P(edge)) {
        return PTR_INVALID;
    } else if (graph_edge_incompatible_p(graph, edge)) {
        return PTR_INVALID;
    } else {
        return indirected_graph_edge_remove_i(graph, edge);
    }
}

static inline s_vertex_t *
indirected_graph_edge_linked_vertex(s_edge_t *edge, s_vertex_t *vertex)
{
    s_vertex_t *vertex_0;
    s_vertex_t *vertex_1;

    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(indirected_graph_edge_vertex_contains_p(edge, vertex));

    vertex_0 = graph_edge_vertex_0(edge);
    vertex_1 = graph_edge_vertex_1(edge);

    if (vertex_0 == vertex) {
        return vertex_1;
    } else {
        return vertex_0;
    }
}

static inline void
indirected_graph_vertex_edge_disconnet(s_vertex_t *vertex, s_edge_t *edge)
{
    s_vertex_t *vertex_linked;

    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(indirected_graph_edge_vertex_contains_p(edge, vertex));

    vertex_linked = indirected_graph_edge_linked_vertex(edge, vertex);

    indirected_graph_vertex_edge_remove(vertex_linked, edge);
}

static inline s_vertex_t *
indirected_graph_vertex_remove_i(s_graph_t *graph, s_vertex_t *vertex)
{
    uint32 i;
    uint32 limit;
    s_edge_t *edge;
    s_adjacent_t *adjacent;
    s_edge_array_t *edge_array;
    s_vertex_array_t *vertex_array;

    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_vertex_compatible_p(graph, vertex));

    i = 0;
    edge_array = graph_edge_array(graph);
    adjacent = graph_vertex_adjacent(vertex);
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) { /* remove all edge connected to vertex */
        edge = graph_adjacent_edge(adjacent, i);

        if (edge) {
            indirected_graph_vertex_edge_disconnet(vertex, edge);
            graph_edge_array_remove(edge_array, graph_edge_index(edge));
            graph_edge_destroy(edge);
        }

        i++;
    }

    i = graph_vertex_index(vertex);
    vertex_array = graph_vertex_array(graph);

    graph_vertex_array_remove(vertex_array, i);
    open_addressing_hash_remove(graph->vertex_hash, vertex->value);

    return vertex;
}

s_vertex_t *
indirected_graph_vertex_remove(s_graph_t *graph, s_vertex_t *vertex)
{
    if (INDIRECTED_GRAPH_ILLEGAL_P(graph)) {
        return PTR_INVALID;
    } else if (GRAPH_VERTEX_ILLEGAL_P(vertex)) {
        return PTR_INVALID;
    } else if (graph_vertex_incompatible_p(graph, vertex)) {
        return PTR_INVALID;
    } else {
        return indirected_graph_vertex_remove_i(graph, vertex);
    }
}

void
indirected_graph_edge_destroy(s_edge_t **edge)
{
    if (NON_NULL_PTR_P(edge) && GRAPH_EDGE_LEGAL_P(*edge)) {
        memory_cache_free(*edge);

        *edge = NULL;
    }
}

void
indirected_graph_vertex_destroy(s_vertex_t **vertex)
{
    if (NON_NULL_PTR_P(vertex) && GRAPH_VERTEX_LEGAL_P(*vertex)) {
        graph_adjacent_destroy((*vertex)->adjacent);
        memory_cache_free(*vertex);

        *vertex = NULL;
    }
}

