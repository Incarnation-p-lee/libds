static inline s_graph_t *
graph_create(void)
{
    s_graph_t *graph;

    graph = memory_cache_allocate(sizeof(*graph));

    graph->vertex_array = graph_vertex_array_create();
    graph->edge_array = graph_edge_array_create();
    graph->vertex_hash = open_addressing_hash_create(GRAPH_VERTEX_HASH_SIZE);

    graph->attribute.is_directed = true;
    graph->attribute.label_limit = GRAPH_LABEL_FIRST;

    return graph;
}

static inline void
graph_destroy(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    graph_vertex_array_destroy(graph->vertex_array);
    graph_edge_array_destroy(graph->edge_array);
    open_addressing_hash_destroy(&graph->vertex_hash);

    memory_cache_free(graph);
}

static inline s_vertex_t *
graph_vertex_create(s_graph_t *graph, void *value)
{
    s_vertex_t *vertex;

    assert_exit(graph_structure_legal_p(graph));

    vertex = memory_cache_allocate(sizeof(*vertex));

    vertex->value = value;
    vertex->index = GRAPH_INDEX_INVALID;
    vertex->label = graph_attibute_label_obtain(graph);
    vertex->precursor = vertex->successor = NULL;
    vertex->is_visited = false;

    return vertex;
}

static inline void
graph_vertex_destroy(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    if (vertex->precursor) { /* include indirected graph adjacent */
        graph_adjacent_destroy(vertex->precursor);
    }

    if (vertex->successor) {
        graph_adjacent_destroy(vertex->successor);
    }

    memory_cache_free(vertex);
}

static inline void
graph_vertex_is_visited_set(s_vertex_t *vertex, bool is_visited)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    vertex->is_visited = is_visited;
}

// static inline bool
// graph_vertex_is_visited_p(s_vertex_t *vertex)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     return vertex->is_visited;
// }

// static inline bool
// graph_vertex_is_unvisited_p(s_vertex_t *vertex)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     return !graph_vertex_is_visited_p(vertex);
// }

static inline s_vertex_array_t *
graph_vertex_array_create(void)
{
    uint32 bytes_count;
    s_vertex_array_t *vertex_array;

    vertex_array = memory_cache_allocate(sizeof(*vertex_array));

    vertex_array->index = 0;
    vertex_array->count = 0;
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
    uint32 index;
    uint32 bytes;
    uint32 new_size;
    s_array_queue_t *queue;

    assert_exit(graph_vertex_array_structure_legal_p(v_array));
    assert_exit(graph_vertex_structure_legal_p(vertex));

    queue = graph_vertex_array_queue(v_array);
    graph_vertex_array_inc(v_array);

    if (!array_queue_empty_p(queue)) {
        index = (uint32)(ptr_t)array_queue_leave(queue);
        v_array->array[index] = vertex;
        graph_vertex_index_set(vertex, index);

        return;
    }

    if (graph_vertex_array_full_p(v_array)) {
        new_size = graph_vertex_array_size(v_array) * 2;
        bytes = sizeof(*v_array->array) * new_size;
        v_array->array = memory_cache_re_allocate(v_array->array, bytes);
        graph_vertex_array_size_set(v_array, new_size);
    }

    v_array->array[v_array->index] = vertex;
    graph_vertex_index_set(vertex, v_array->index);
    v_array->index++;
}

static inline s_vertex_t *
graph_vertex_array_find(s_vertex_array_t *vertex_array, void *value)
{
    uint32 i;
    uint32 limit;
    s_vertex_t *vertex;

    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    i = 0;
    limit = graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = graph_vertex_array_vertex(vertex_array, i++);

        if (vertex && graph_vertex_value(vertex) == value) {
            return vertex;
        }
    }

    return NULL;
}

static inline void
graph_vertex_array_queue_enter(s_vertex_array_t *vertex_array, void *val)
{
    s_array_queue_t *queue;

    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    queue = graph_vertex_array_queue(vertex_array);
    array_queue_enter(queue, val);
}

static inline void
graph_vertex_array_remove(s_vertex_array_t *vertex_array, uint32 i)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));
    assert_exit(i < graph_vertex_array_limit(vertex_array));

    graph_vertex_array_queue_enter(vertex_array, (void *)(ptr_t)i);
    graph_vertex_cleanup(vertex_array->array[i]);

    vertex_array->array[i] = NULL;
    graph_vertex_array_dec(vertex_array);
}

static inline s_edge_array_t *
graph_edge_array_create(void)
{
    uint32 bytes_count;
    s_edge_array_t *edge_array;

    edge_array = memory_cache_allocate(sizeof(*edge_array));

    edge_array->count = 0;
    edge_array->index = 0;
    edge_array->size = GRAPH_EDGE_DEFAULT;
    edge_array->queue = array_queue_create();

    bytes_count = sizeof(*edge_array->array) * edge_array->size;
    edge_array->array = memory_cache_allocate(bytes_count);

    return edge_array;
}

static inline void
graph_edge_array_destroy(s_edge_array_t *edge_array)
{
    uint32 i;
    uint32 limit;
    s_edge_t *edge;

    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    i = 0;
    limit = graph_edge_array_limit(edge_array);

    while (i < limit) {
        edge = graph_edge_array_edge(edge_array, i++);

        if (edge) {
            graph_edge_destroy(edge);
        }
    }

    array_queue_destroy(&edge_array->queue);
    memory_cache_free(edge_array->array);
    memory_cache_free(edge_array);
}

static inline void
graph_edge_array_edge_destroy(s_edge_array_t *edge_array, s_edge_t *edge)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(graph_edge_structure_legal_p(edge));

    graph_edge_array_remove(edge_array, graph_edge_index(edge));
    graph_edge_destroy(edge);
}

static inline void
graph_edge_array_add(s_edge_array_t *edge_array, s_edge_t *edge)
{
    uint32 index;
    uint32 bytes;
    uint32 new_size;
    s_array_queue_t *queue;

    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(graph_edge_structure_legal_p(edge));

    queue = graph_edge_array_queue(edge_array);
    graph_edge_array_inc(edge_array);

    if (!array_queue_empty_p(queue)) {
        index = (uint32)(ptr_t)array_queue_leave(queue);
        edge_array->array[index] = edge;
        graph_edge_index_set(edge, index);

        return;
    }

    if (graph_edge_array_full_p(edge_array)) {
        new_size = graph_edge_array_size(edge_array) * 2;
        bytes = sizeof(*edge_array->array) * new_size;
        edge_array->array = memory_cache_re_allocate(edge_array->array, bytes);
        graph_edge_array_size_set(edge_array, new_size);
    }

    edge_array->array[edge_array->index] = edge;
    graph_edge_index_set(edge, edge_array->index);
    edge_array->index++;
}

static inline void
graph_edge_array_queue_enter(s_edge_array_t *edge_array, void *val)
{
    s_array_queue_t *queue;

    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    queue = graph_edge_array_queue(edge_array);
    array_queue_enter(queue, val);
}

static inline void
graph_edge_array_remove(s_edge_array_t *edge_array, uint32 i)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(i < graph_edge_array_limit(edge_array));

    graph_edge_array_queue_enter(edge_array, (void *)(ptr_t)i);
    graph_edge_cleanup(edge_array->array[i]);

    edge_array->array[i] = NULL;
    graph_edge_array_dec(edge_array);
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

static inline void
graph_edge_destroy(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    memory_cache_free(edge);
}

static inline s_adjacent_t *
graph_adjacent_create(void)
{
    uint32 bytes_count;
    s_adjacent_t *adjacent;

    adjacent = memory_cache_allocate(sizeof(*adjacent));

    adjacent->index = adjacent->edge_count = 0;
    adjacent->size = GRAPH_ADJACENT_DEFAULT;

    bytes_count = sizeof(*adjacent->array) * adjacent->size;
    adjacent->array = memory_cache_allocate(bytes_count);

    return adjacent;
}

static inline void
graph_adjacent_destroy(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    memory_cache_free(adjacent->array);
    memory_cache_free(adjacent);
}

static inline void
graph_adjacent_edge_append(s_adjacent_t *adjacent, s_edge_t *edge)
{
    uint32 bytes;
    uint32 new_size;

    assert_exit(graph_adjacent_structure_legal_p(adjacent));
    assert_exit(graph_edge_structure_legal_p(edge));

    if (graph_adjacent_full_p(adjacent)) {
        new_size = graph_adjacent_size(adjacent) * 2;
        bytes = sizeof(*adjacent->array) * new_size;
        adjacent->array = memory_cache_re_allocate(adjacent->array, bytes);

        graph_adjacent_size_set(adjacent, new_size);
    }

    adjacent->array[adjacent->index++] = edge;
    adjacent->edge_count++;
}

static inline void
graph_adjacent_compress(s_adjacent_t *adjacent)
{
    uint32 i;
    uint32 k;
    uint32 limit;
    s_edge_t *edge;

    assert_exit(graph_adjacent_structure_legal_p(adjacent));
    assert_exit(graph_adjacent_sparse_p(adjacent));

    k = i = 0;
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) {
        edge = graph_adjacent_edge(adjacent, i);

        if (edge) {
            graph_adjacent_edge_set(adjacent, k, edge);
            k++;
        }

        i++;
    }

    graph_adjacent_index_set(adjacent, k);
}

static inline void
graph_adjacent_edge_remove(s_adjacent_t *adjacent, s_edge_t *edge)
{
    uint32 i, limit;
    s_edge_t *edge_tmp;

    assert_exit(graph_edge_structure_legal_p(edge));
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    i = 0;
    limit = graph_adjacent_limit(adjacent);

    while (i < limit) {
        edge_tmp = graph_adjacent_edge(adjacent, i);

        if (edge_tmp == NULL || edge_tmp != edge) {
            i++;
            continue;
        }

        graph_adjacent_edge_set(adjacent, i, NULL);
        graph_adjacent_edge_count_dec(adjacent);

        if (graph_adjacent_sparse_p(adjacent)) {
            graph_adjacent_compress(adjacent);
        }

        return;
    }

    pr_log_warn("No such of the edge in given vertex adjacent.\n");
}

static inline void
graph_topo_list_insert_before(s_topo_list_t *node, s_topo_list_t *inserted)
{
    assert_exit(graph_topo_list_structure_legal_p(node));
    assert_exit(graph_topo_list_structure_legal_p(inserted));

    doubly_linked_list_insert_before(&node->list, &inserted->list);
}

static inline s_topo_list_t *
graph_topo_list_next(s_topo_list_t *node)
{
    assert_exit(graph_topo_list_structure_legal_p(node));

    return CONTAINER_OF(node->list.next, s_topo_list_t, list);
}

static inline void
graph_topo_list_remove(s_topo_list_t *node)
{
    s_doubly_linked_list_t *list;

    assert_exit(graph_topo_list_structure_legal_p(node));

    list = &node->list;

    doubly_linked_list_remove(&list);
}

static inline void
graph_vertex_array_visited_cleanup(s_graph_t *graph)
{
    uint32 i, limit;
    s_vertex_t *vertex;
    s_vertex_array_t *vertex_array;

    assert_exit(graph_structure_legal_p(graph));

    i = 0;
    vertex_array = graph_vertex_array(graph);
    limit = graph_vertex_array_limit(vertex_array);

    while (i < limit) {
        vertex = graph_vertex_array_vertex(vertex_array, i);

        if (vertex) {
            graph_vertex_is_visited_set(vertex, false);
        }

        i++;
    }
}

static inline void
graph_edge_array_visited_cleanup(s_graph_t *graph)
{
    uint32 i, limit;
    s_edge_t *edge;
    s_edge_array_t *edge_array;

    assert_exit(graph_structure_legal_p(graph));

    i = 0;
    edge_array = graph_edge_array(graph);
    limit = graph_edge_array_limit(edge_array);

    while (i < limit) {
        edge = graph_edge_array_edge(edge_array, i);

        if (edge) {
            graph_edge_is_visited_set(edge, false);
        }

        i++;
    }
}

