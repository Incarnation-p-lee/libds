static inline bool
indirected_graph_structure_legal_p(s_graph_t *graph)
{
    if (graph_structure_illegal_p(graph)) {
        return false;
    } else if (graph_directed_p(graph)) {
        return false;
    } else {
        return true;
    }
}

s_graph_t *
indirected_graph_create(void)
{
    s_graph_t *graph;

    graph = graph_create();

    graph_attibute_directed_set(graph, /* is_directed = */false);

    return graph;
}

void
indirected_graph_destroy(s_graph_t *graph)
{
    if (indirected_graph_structure_legal_p(graph)) {
        graph_destroy(graph);
    }
}

