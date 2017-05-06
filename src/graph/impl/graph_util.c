static inline s_vertex_array_t *
graph_vertex_array(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->vertex_array;
}

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

static inline void
graph_attribute_vertex_inc(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    graph->attribute.vertex_count++;
}

static inline void
graph_attribute_edge_dec(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph->attribute.edge_count);

    graph->attribute.edge_count--;
}

static inline void
graph_attribute_vertex_dec(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph->attribute.vertex_count);

    graph->attribute.vertex_count--;
}

static inline void
graph_attribute_edge_inc(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    graph->attribute.edge_count++;
}

static uint32
graph_attribute_vertex_count(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->attribute.vertex_count;
}

static uint32
graph_attribute_edge_count(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->attribute.edge_count;
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
graph_edge_index(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->index;
}

static inline void
graph_edge_cleanup(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    edge->index = GRAPH_INDEX_INVALID;
    edge->cost = GRAPH_COST_INVALID;
}

static inline void
graph_edge_index_set(s_edge_t *edge, uint32 index)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    edge->index = index;
}

static inline s_array_queue_t *
graph_edge_array_queue(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->queue;
}

static inline uint32
graph_edge_array_limit(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->index;
}

static inline s_edge_t *
graph_edge_array_edge(s_edge_array_t *edge_array, uint32 i)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(i < graph_edge_array_limit(edge_array));

    return edge_array->array[i];
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

    edge_array->size = size;
}

static inline bool
graph_edge_array_full_p(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    if (!array_queue_empty_p(edge_array->queue)) {
        return false;
    } else if (edge_array->index < edge_array->size) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
graph_adjacent_count(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    return adjacent->edge_count;
}

static inline uint32
graph_adjacent_limit(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    return adjacent->index;
}

static inline void
graph_adjacent_index_set(s_adjacent_t *adjacent, uint32 index)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    adjacent->index = index;
}

static inline s_edge_t *
graph_adjacent_edge(s_adjacent_t *adjacent, uint32 i)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));
    assert_exit(i < graph_adjacent_limit(adjacent));

    return adjacent->array[i];
}

static inline void
graph_adjacent_edge_set(s_adjacent_t *adjacent, uint32 i, s_edge_t *edge)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));
    assert_exit(i < graph_adjacent_limit(adjacent));

    adjacent->array[i] = edge;
}

static inline uint32
graph_adjacent_size(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    return adjacent->size;
}

static inline void
graph_adjacent_size_set(s_adjacent_t *adjacent, uint32 size)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));
    assert_exit(size);

    adjacent->size = size;
}

// static inline bool
// graph_adjacent_empty_p(s_adjacent_t *adjacent)
// {
//     assert_exit(graph_adjacent_structure_legal_p(adjacent));
// 
//     return adjacent->edge_count == 0 ? true : false;
// }

static inline void
graph_adjacent_edge_count_dec(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    adjacent->edge_count--;
}

static inline bool
graph_adjacent_full_p(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    return adjacent->index == adjacent->size ? true : false;
}

static inline uint32
graph_adjacent_load_factor(s_adjacent_t *adj)
{
    assert_exit(graph_adjacent_structure_legal_p(adj));

    return graph_adjacent_count(adj) * 100 / graph_adjacent_limit(adj);
}

static inline uint32
graph_adjacent_rest(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    return graph_adjacent_size(adjacent) - graph_adjacent_limit(adjacent);
}

static inline uint32
graph_adjacent_rest_factor(s_adjacent_t *adj)
{
    assert_exit(graph_adjacent_structure_legal_p(adj));

    return graph_adjacent_rest(adj) * 100 / graph_adjacent_size(adj);
}

static inline bool
graph_adjacent_sparse_p(s_adjacent_t *adjacent)
{
    uint32 load_factor;
    uint32 rest_factor;

    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    load_factor = graph_adjacent_load_factor(adjacent);
    rest_factor = graph_adjacent_rest_factor(adjacent);

    if (load_factor >= GRAPH_ADJACENT_LOAD_FCTR) {
        return false;
    } else if (rest_factor >= GRAPH_ADJACENT_REST_FCTR) {
        return false;
    } else {
        return true;
    }
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

static inline s_adjacent_t *
graph_vertex_adjacent(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->adjacent;
}


// static inline void
// graph_vertex_value_set(s_vertex_t *vertex, void *val)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     vertex->value = val;
// }

static inline uint32
graph_vertex_index(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->index;
}

static inline void
graph_vertex_index_set(s_vertex_t *vertex, uint32 index)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    vertex->index = index;
}

static inline bool
graph_vertex_value_exist_p(s_graph_t *graph, void *value)
{
    s_open_addressing_hash_t *vertex_hash;

    assert_exit(graph_structure_legal_p(graph));

    vertex_hash = graph_vertex_hash(graph);

    if (open_addressing_hash_find(vertex_hash, value) == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline void
graph_vertex_cleanup(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    vertex->index = GRAPH_INDEX_INVALID;
    vertex->label = GRAPH_LABEL_INVALID;
}

static inline s_edge_array_t *
graph_edge_array(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->edge_array;
}

