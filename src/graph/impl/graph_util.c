// static inline s_edge_t *
// graph_edge_list_edge(s_edge_list_t *edge_list)
// {
//     assert_exit(graph_edge_list_structure_legal_p(edge_list));
// 
//     return &edge_list->edge;
// }

static inline void
graph_attibute_directed_set(s_graph_t *graph, bool is_directed)
{
    assert_exit(graph_structure_legal_p(graph));

    graph->attribute.is_directed = is_directed;
}

static inline bool
graph_directed_p(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->attribute.is_directed;
}

static inline bool
graph_indirected_p(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return !graph_directed_p(graph);
}

static inline uint32
graph_vertex_array_limit(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    return vertex_array->index;
}

static inline s_vertex_t *
graph_vertex_array_vertex(s_vertex_array_t *vertex_array, uint32 i)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));
    assert_exit(i < graph_vertex_array_limit(vertex_array));

    return vertex_array->array[i];
}

