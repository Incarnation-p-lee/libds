static inline s_graph_t *
graph_create(void)
{
    s_graph_t *graph;

    graph = memory_cache_allocate(sizeof(*graph));

    graph->vertex_array = graph_vertex_array_create();
    graph->hash = open_addressing_hash_create(GRAPH_VERTEX_HASH_SIZE);

    graph->attribute.edge_count = 0;
    graph->attribute.vertex_count = 0;
    graph->attribute.is_directed = true;
    graph->attribute.label_limit = GRAPH_LABEL_FIRST;

    return graph;
}

static inline void
graph_destroy(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    open_addressing_hash_destroy(&graph->hash);
    graph_vertex_array_destroy(graph->vertex_array);

    memory_cache_free(graph);
}

// static inline s_edge_list_t *
// graph_edge_list_create(void)
// {
//     s_edge_list_t *edge_list;
// 
//     edge_list = memory_cache_allocate(sizeof(*edge_list));
//     doubly_linked_list_initial(&edge_list->list);
// 
//     return edge_list;
// }

// static inline s_vertex_t *
// graph_vertex_create(void)
// {
//     s_vertex_t *vertex;
// 
//     vertex = memory_cache_allocate(sizeof(*vertex));
// 
//     vertex->value = NULL;
//     vertex->label = GRAPH_LABEL_INVALID;
//     vertex->precursor = vertex->successor = NULL;
// 
//     return vertex;
// }

static inline void
graph_vertex_destroy(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    if (vertex->precursor) { /* include adjacent for indirected */
        graph_edge_list_destroy(vertex->precursor);
    }

    if (vertex->successor) {
        graph_edge_list_destroy(vertex->successor);
    }

    memory_cache_free(vertex);
}

static inline s_edge_list_t *
graph_edge_list_next(s_edge_list_t *edge_list)
{
    assert_exit(graph_edge_list_structure_legal_p(edge_list));

    return CONTAINER_OF(edge_list->list.next, s_edge_list_t, list);
}

static inline void
graph_edge_list_destroy(s_edge_list_t *edge_list)
{
    s_edge_list_t *edge_tmp;
    s_edge_list_t *edge_next;

    assert_exit(graph_edge_list_structure_legal_p(edge_list));

    edge_tmp = edge_list;

    do {
        edge_next = graph_edge_list_next(edge_tmp);
        memory_cache_free(edge_tmp);
        edge_tmp = edge_next;
    } while (edge_tmp != edge_list);
}

static inline s_vertex_array_t *
graph_vertex_array_create(void)
{
    uint32 bytes_count;
    s_vertex_array_t *vertex_array;

    vertex_array = memory_cache_allocate(sizeof(*vertex_array));

    vertex_array->index = 0;
    vertex_array->size = GRAPH_VERTEX_DEFAULT;
    vertex_array->queue = array_queue_create();

    bytes_count = sizeof(*vertex_array->array) * vertex_array->size;
    vertex_array->array = memory_cache_allocate(bytes_count);

    return vertex_array;
}

static inline void
graph_vertex_array_destroy(s_vertex_array_t *vertex_array)
{
    uint32 i;
    uint32 limit;
    s_vertex_t *vertex;

    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    i = 0;
    limit = graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = graph_vertex_array_vertex(vertex_array, i++);

        if (vertex) {
            graph_vertex_destroy(vertex);
        }
    }

    memory_cache_free(vertex_array->array);
    array_queue_destroy(&vertex_array->queue);
}

