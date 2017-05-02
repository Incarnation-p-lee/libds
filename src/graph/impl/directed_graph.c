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


