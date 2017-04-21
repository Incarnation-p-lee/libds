bool
directed_graph_structure_legal_p(s_graph_t *graph)
{
    if (graph_structure_illegal_p(graph)) {
        return false;
    } else if (graph_indirected_p(graph)) {
        return false;
    } else {
        return true;
    }
}

s_graph_t *
directed_graph_create(void)
{
    s_graph_t *graph;

    graph = graph_create();

    graph_attibute_directed_set(graph, /* is_directed = */true);

    return graph;
}

void
directed_graph_destroy(s_graph_t **graph)
{
    if (NON_NULL_PTR_P(graph) && directed_graph_structure_legal_p(*graph)) {
        graph_destroy(*graph);
        *graph = NULL;
    }
}


