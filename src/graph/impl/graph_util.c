static inline void
graph_attribute_directed_set(s_graph_t *graph, bool is_directed)
{
    assert_exit(graph_structure_legal_p(graph));

    graph->attribute.is_directed = is_directed;
}

static inline bool
graph_attribute_directed_p(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->attribute.is_directed;
}

static inline bool
graph_attribute_indirected_p(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return !graph_attribute_directed_p(graph);
}

static inline sint32
graph_attibute_label_obtain(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->attribute.label_limit++;
}

static inline void *
graph_edge_vertex_0_value(s_edge_t *edge)
{
    s_vertex_t *vertex;

    assert_exit(graph_edge_structure_legal_p(edge));

    vertex = graph_edge_vertex_0(edge);

    return graph_vertex_value(vertex);
}

static inline s_vertex_t *
graph_edge_vertex_0(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->vertex_0;
}

static inline void *
graph_edge_vertex_1_value(s_edge_t *edge)
{
    s_vertex_t *vertex;

    assert_exit(graph_edge_structure_legal_p(edge));

    vertex = graph_edge_vertex_1(edge);

    return graph_vertex_value(vertex);
}

static inline s_vertex_t *
graph_edge_vertex_1(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->vertex_1;
}

static inline sint32
graph_edge_cost(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->cost;
}

// static inline void
// graph_edge_cost_set(s_edge_t *edge, sint32 cost)
// {
//     assert_exit(graph_edge_structure_legal_p(edge));
// 
//     edge->cost = cost;
// }

static inline uint32
graph_edge_array_limit(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->index;
}

static inline uint32
graph_edge_array_size(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->size;
}

static inline void
graph_edge_array_size_set(s_edge_array_t *edge_array, uint32 size)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(size);

    edge_array->size = size;
}

static inline s_edge_t *
graph_edge_array_edge(s_edge_array_t *edge_array, uint32 i)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(i < graph_edge_array_limit(edge_array));

    return edge_array->array[i];
}

// static inline bool
// graph_edge_array_empty_p(s_edge_array_t *edge_array)
// {
//     assert_exit(graph_edge_array_structure_legal_p(edge_array));
// 
//     return edge_array->edge_count == 0 ? true : false;
// }

static inline bool
graph_edge_array_full_p(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->index == edge_array->size ? true : false;
}

static inline void
graph_edge_array_append(s_edge_array_t *edge_array, s_edge_t *edge)
{
    uint32 bytes;
    uint32 new_size;

    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(graph_edge_structure_legal_p(edge));

    if (graph_edge_array_full_p(edge_array)) {
        new_size = graph_edge_array_size(edge_array) * 2;
        bytes = sizeof(*edge_array->array) * new_size;
        edge_array->array = memory_cache_re_allocate(edge_array->array, bytes);

        graph_edge_array_size_set(edge_array, new_size);
    }

    edge_array->array[edge_array->index++] = edge;
    edge_array->edge_count++;
}

static inline s_array_queue_t *
graph_vertex_array_queue(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    return vertex_array->queue;
}

static inline bool
graph_vertex_array_full_p(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    if (!array_queue_empty_p(vertex_array->queue)) {
        return false;
    } else if (vertex_array->index < vertex_array->size) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
graph_vertex_array_limit(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    return vertex_array->index;
}

static inline uint32
graph_vertex_array_size(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    return vertex_array->size;
}

static inline void
graph_vertex_array_size_set(s_vertex_array_t *vertex_array, uint32 size)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    vertex_array->size = size;
}

static inline s_vertex_t *
graph_vertex_array_vertex(s_vertex_array_t *vertex_array, uint32 i)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));
    assert_exit(i < graph_vertex_array_limit(vertex_array));

    return vertex_array->array[i];
}

static inline s_open_addressing_hash_t *
graph_vertex_hash(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->vertex_hash;
}

static inline void *
graph_vertex_value(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->value;
}

// static inline void
// graph_vertex_value_set(s_vertex_t *vertex, void *val)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     vertex->value = val;
// }

