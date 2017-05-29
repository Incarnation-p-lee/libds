static inline bool
graph_structure_legal_p(s_graph_t *graph)
{
    if (NULL_PTR_P(graph)) {
        return false;
    } else if (NULL_PTR_P(graph->vertex_hash)) {
        return false;
    } else if (graph_vertex_array_structure_illegal_p(graph->vertex_array)) {
        return false;
    } else if (graph_edge_array_structure_illegal_p(graph->edge_array)) {
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

static inline bool
graph_edge_array_structure_legal_p(s_edge_array_t *edge_array)
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
graph_edge_array_structure_illegal_p(s_edge_array_t *edge_array)
{
    return !graph_edge_array_structure_legal_p(edge_array);
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
graph_edge_structure_legal_p(s_edge_t *edge)
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
graph_edge_structure_illegal_p(s_edge_t *edge)
{
    return !graph_edge_structure_legal_p(edge);
}

static inline bool
graph_adjacent_structure_legal_p(s_adjacent_t *adjacent)
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
graph_vertex_structure_legal_p(s_vertex_t *vertex)
{
    if (NULL_PTR_P(vertex)) {
        return false;
    } else if (graph_adjacent_structure_legal_p(vertex->precursor)) {
        return true; /* include adjacent of indirected */
    } else if (graph_adjacent_structure_legal_p(vertex->successor)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_vertex_structure_illegal_p(s_vertex_t *vertex)
{
    return !graph_vertex_structure_legal_p(vertex);
}

static inline bool
graph_topo_list_structure_legal_p(s_topo_list_t *topo_list)
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
graph_topo_list_structure_illegal_p(s_topo_list_t *topo_list)
{
    return !graph_topo_list_structure_legal_p(topo_list);
}

