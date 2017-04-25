static inline s_graph_t *
graph_create(void)
{
    s_graph_t *graph;

    graph = memory_cache_allocate(sizeof(*graph));

    graph->vertex_array = graph_vertex_array_create();
    graph->vertex_hash = open_addressing_hash_create(GRAPH_VERTEX_HASH_SIZE);

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

    open_addressing_hash_destroy(&graph->vertex_hash);
    graph_vertex_array_destroy(graph->vertex_array);

    memory_cache_free(graph);
}

static inline s_vertex_t *
graph_vertex_create(s_graph_t *graph, void *value)
{
    s_vertex_t *vertex;

    assert_exit(graph_structure_legal_p(graph));

    vertex = memory_cache_allocate(sizeof(*vertex));

    vertex->value = value;
    vertex->label = graph_attibute_label_obtain(graph);
    vertex->precursor = vertex->successor = NULL;

    return vertex;
}

static inline void
graph_vertex_destroy(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    if (vertex->precursor) { /* include adjacent for indirected */
        graph_adjacent_destroy(vertex->precursor);
    }

    if (vertex->successor) {
        graph_adjacent_destroy(vertex->successor);
    }

    memory_cache_free(vertex);
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

    array_queue_destroy(&vertex_array->queue);
    memory_cache_free(vertex_array->array);
    memory_cache_free(vertex_array);
}

static inline void
graph_vertex_array_add(s_vertex_array_t *v_array, s_vertex_t *vertex)
{
    uint32 i;
    uint32 bytes;
    uint32 new_size;
    s_array_queue_t *queue;

    assert_exit(graph_vertex_array_structure_legal_p(v_array));
    assert_exit(graph_vertex_structure_legal_p(vertex));

    queue = graph_vertex_array_queue(v_array);

    if (!array_queue_empty_p(queue)) {
        i = (uint32)(ptr_t)array_queue_leave(queue);
        v_array->array[i] = vertex;
    } else if (graph_vertex_array_full_p(v_array)) {
        new_size = graph_vertex_array_size(v_array) * 2;
        bytes = sizeof(*v_array->array) * new_size;
        v_array->array = memory_cache_re_allocate(v_array->array, bytes);

        graph_vertex_array_size_set(v_array, new_size);
        v_array->array[v_array->index++] = vertex;
    } else {
        v_array->array[v_array->index++] = vertex;
    }
}

static inline s_edge_t *
graph_edge_create(sint32 cost)
{
    s_edge_t *edge;

    edge = memory_cache_allocate(sizeof(*edge));

    edge->cost = cost;
    edge->precursor = edge->successor = NULL; /* include vertex_0 */

    return edge;
}

static inline s_adjacent_t *
graph_adjacent_create(void)
{
    uint32 bytes_count;
    s_adjacent_t *adjacent;

    adjacent = memory_cache_allocate(sizeof(*adjacent));

    adjacent->index = adjacent->edge_count = 0;
    adjacent->size = GRAPH_EDGE_DEFAULT;

    bytes_count = sizeof(*adjacent->array) * adjacent->size;
    adjacent->array = memory_cache_allocate(bytes_count);

    return adjacent;
}

static inline void
graph_adjacent_destroy(s_adjacent_t *adjacent)
{
    uint32 i;
    uint32 limit;
    s_edge_t *edge;

    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    i = 0;
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) {
        edge = graph_adjacent_edge(adjacent, i++);

        if (edge) {
            memory_cache_free(edge);
        }
    }
}

