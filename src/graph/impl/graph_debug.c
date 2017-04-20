// static inline bool
// graph_edge_structure_legal_p(s_edge_t *edge)
// {
//     if (NULL_PTR_P(edge)) {
//         return false;
//     } else if (NON_NULL_PTR_P(edge->precursor)) { /* include adjacent_0 */
//         return true;
//     } else if (NON_NULL_PTR_P(edge->successor)) { /* include adjacent_1 */
//         return true;
//     } else {
//         return false;
//     }
// }

// static inline bool
// graph_edge_structure_illegal_p(s_edge_t *edge)
// {
//     return !graph_edge_structure_legal_p(edge);
// }

static inline bool
graph_edge_list_structure_legal_p(s_edge_list_t *edge_list)
{
    if (NULL_PTR_P(edge_list)) {
        return false;
    } else {
        return true;
    }
}

// static inline bool
// graph_edge_list_structure_illegal_p(s_edge_list_t *edge_list)
// {
//     return !graph_edge_list_structure_legal_p(edge_list);
// }

static inline bool
graph_vertex_structure_legal_p(s_vertex_t *vertex)
{
    if (NULL_PTR_P(vertex)) {
        return false;
    } else if (graph_edge_list_structure_legal_p(vertex->precursor)) {
        return true; /* include adjacent of indirected */
    } else if (graph_edge_list_structure_legal_p(vertex->successor)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_vertex_array_structure_legal_p(s_vertex_array_t *vertex_array)
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
graph_vertex_array_structure_illegal_p(s_vertex_array_t *vertex_array)
{
    return !graph_vertex_array_structure_legal_p(vertex_array);
}

static inline bool
graph_structure_legal_p(s_graph_t *graph)
{
    if (NULL_PTR_P(graph)) {
        return false;
    } else if (NULL_PTR_P(graph->hash)) {
        return false;
    } else if (graph_vertex_array_structure_illegal_p(graph->vertex_array)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_structure_illegal_p(s_graph_t *graph)
{
    return !graph_structure_legal_p(graph);
}

