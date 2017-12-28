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

static inline void *
graph_edge_vertex_0_value(s_edge_t *edge)
{
    s_vertex_t *vertex;

    assert_exit(graph_edge_structure_legal_p(edge));

    vertex = graph_edge_vertex_0(edge);

    return graph_vertex_value(vertex);
}

static inline void *
graph_edge_successor_value(s_edge_t *edge)
{
    s_vertex_t *vertex;

    assert_exit(graph_edge_structure_legal_p(edge));

    vertex = graph_edge_successor(edge);

    return graph_vertex_value(vertex);
}

static inline void *
graph_edge_precursor_value(s_edge_t *edge)
{
    s_vertex_t *vertex;

    assert_exit(graph_edge_structure_legal_p(edge));

    vertex = graph_edge_precursor(edge);

    return graph_vertex_value(vertex);
}

static inline s_vertex_t *
graph_edge_vertex_0(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->vertex_0;
}

static inline s_vertex_t *
graph_edge_successor(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->successor;
}

static inline s_vertex_t *
graph_edge_precursor(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->precursor;
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

static inline void
graph_edge_cost_set(s_edge_t *edge, sint32 cost)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    edge->cost = cost;
}

static inline uint32
graph_edge_index(s_edge_t *edge)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    return edge->index;
}

static inline void
graph_edge_is_visited_set(s_edge_t *edge, bool is_visited)
{
    assert_exit(graph_edge_structure_legal_p(edge));

    edge->is_visited = is_visited;
}

// static inline bool
// graph_edge_is_visited_p(s_edge_t *edge)
// {
//     assert_exit(graph_edge_structure_legal_p(edge));
// 
//     return edge->is_visited;
// }

// static inline bool
// graph_edge_is_unvisited_p(s_edge_t *edge)
// {
//     assert_exit(graph_edge_structure_legal_p(edge));
// 
//     return !graph_edge_is_visited_p(edge);
// }

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

static inline bool
graph_edge_compatible_p(s_graph_t *graph, s_edge_t *edge)
{
    uint32 index;
    s_edge_t *edge_tmp;

    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph_edge_structure_legal_p(edge));

    index = graph_edge_index(edge);
    edge_tmp = graph_edge_array_edge(graph_edge_array(graph), index);

    if (edge_tmp == edge) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_edge_incompatible_p(s_graph_t *graph, s_edge_t *edge)
{
    return !graph_edge_compatible_p(graph, edge);
}

// static inline bool
// graph_edge_loop_p(s_graph_t *edge)
// {
//     assert_exit(graph_edge_structure_legal_p(edge));
// 
//     if (edge->precursor == edge->successor) { /* include vertex_0 and 1 */
//         return true;
//     } else {
//         return false;
//     }
// }

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
graph_adjacent_cleanup(s_adjacent_t *adjacent)
{
    assert_exit(graph_adjacent_structure_legal_p(adjacent));

    adjacent->index = adjacent->edge_count = 0;
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

static inline uint32
graph_vertex_array_count(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    return vertex_array->count;
}

static inline uint32
graph_vertex_count(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph_vertex_array_count(graph_vertex_array(graph));
}

static inline void
graph_vertex_array_inc(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));

    vertex_array->count++;
}

static inline void
graph_vertex_array_dec(s_vertex_array_t *vertex_array)
{
    assert_exit(graph_vertex_array_structure_legal_p(vertex_array));
    assert_exit(vertex_array->count);

    vertex_array->count--;
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

static inline void *
graph_vertex_data(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->data;
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

static inline s_topo_list_t *
graph_vertex_topo_list(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return &vertex->topo_list;
}

static inline s_adjacent_t *
graph_vertex_adjacent(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->adjacent;
}

static inline s_adjacent_t *
graph_vertex_precursor(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->precursor;
}

static inline s_adjacent_t *
graph_vertex_successor(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->successor;
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

static inline uint32
graph_edge_array_count(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    return edge_array->count;
}

static inline void
graph_edge_array_inc(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));

    edge_array->count++;
}

static inline void
graph_edge_array_dec(s_edge_array_t *edge_array)
{
    assert_exit(graph_edge_array_structure_legal_p(edge_array));
    assert_exit(edge_array->count);

    edge_array->count--;
}


static inline s_edge_array_t *
graph_edge_array(s_graph_t *graph)
{
    assert_exit(graph_structure_legal_p(graph));

    return graph->edge_array;
}

// static inline bool
// graph_vertex_is_visited_p(s_vertex_t *vertex)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     return vertex->is_visited;
// }

// static inline void
// graph_vertex_is_visited_set(s_vertex_t *vertex, bool is_visited)
// {
//     assert_exit(graph_vertex_structure_legal_p(vertex));
// 
//     vertex->is_visited = is_visited;
// }

static inline uint32
graph_vertex_label(s_vertex_t *vertex)
{
    assert_exit(graph_vertex_structure_legal_p(vertex));

    return vertex->label;
}

static inline bool
graph_vertex_compatible_p(s_graph_t *graph, s_vertex_t *vertex)
{
    uint32 index;
    s_vertex_t *vertex_tmp;

    assert_exit(graph_structure_legal_p(graph));
    assert_exit(graph_vertex_structure_legal_p(vertex));

    index = graph_vertex_index(vertex);
    vertex_tmp = graph_vertex_array_vertex(graph_vertex_array(graph), index);

    if (vertex_tmp == vertex) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_vertex_incompatible_p(s_graph_t *graph, s_vertex_t *vertex)
{
    return !graph_vertex_compatible_p(graph, vertex);
}

static inline void
graph_topo_list_initial(s_topo_list_t *topo_list, uint32 indegree)
{
    assert_exit(NON_NULL_PTR_P(topo_list));

    doubly_linked_list_initial(&topo_list->list);
    graph_topo_list_indegree_set(topo_list, indegree);
}

static inline uint32
graph_topo_list_indegree(s_topo_list_t *topo_list)
{
    assert_exit(graph_topo_list_structure_legal_p(topo_list));

    return topo_list->indegree;
}

static inline void
graph_topo_list_indegree_set(s_topo_list_t *topo_list, uint32 indegree)
{
    assert_exit(graph_topo_list_structure_legal_p(topo_list));

    topo_list->indegree = indegree;
}

static inline void
graph_topo_list_indegree_dec(s_topo_list_t *topo_list)
{
    assert_exit(graph_topo_list_structure_legal_p(topo_list));
    assert_exit(graph_topo_list_indegree(topo_list) != 0u);

    topo_list->indegree--;
}

static inline bool
graph_topo_list_no_indegree_p(s_topo_list_t *topo_list)
{
    assert_exit(graph_topo_list_structure_legal_p(topo_list));

    if (graph_topo_list_indegree(topo_list) == 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
graph_dijkstra_entry_legal_ip(s_dijkstra_entry_t *dj_entry)
{
    if (dj_entry == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_dijkstra_entry_illegal_ip(s_dijkstra_entry_t *dj_entry)
{
    return !graph_dijkstra_entry_legal_ip(dj_entry);
}

bool
graph_dijkstra_entry_legal_p(s_dijkstra_entry_t *dj_entry)
{
    return graph_dijkstra_entry_legal_ip(dj_entry);
}

bool
graph_dijkstra_entry_illegal_p(s_dijkstra_entry_t *dj_entry)
{
    return graph_dijkstra_entry_illegal_ip(dj_entry);
}

static inline s_vertex_t *
graph_dijkstra_entry_vertex(s_dijkstra_entry_t *dj_entry)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    return dj_entry->vertex;
}

static inline void
graph_dijkstra_entry_vertex_set(s_dijkstra_entry_t *dj_entry, s_vertex_t *v)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    dj_entry->vertex = v;
}

static inline s_vertex_t *
graph_dijkstra_entry_vertex_pre(s_dijkstra_entry_t *dj_entry)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    return dj_entry->vertex_pre;
}

static inline void
graph_dijkstra_entry_vertex_pre_set(s_dijkstra_entry_t *dj_entry,
    s_vertex_t *vertex_pre)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    dj_entry->vertex_pre = vertex_pre;
}

static inline bool
graph_dijkstra_entry_is_known_p(s_dijkstra_entry_t *dj_entry)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    return dj_entry->is_known;
}

// static inline bool
// graph_dijkstra_entry_is_unknown_p(s_dijkstra_entry_t *dj_entry)
// {
//     return !graph_dijkstra_entry_is_known_p(dj_entry);
// }

static inline void
graph_dijkstra_entry_is_known_set(s_dijkstra_entry_t *dj_entry, bool is_known)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    dj_entry->is_known = is_known;
}

static inline uint32
graph_dijkstra_entry_distance(s_dijkstra_entry_t *dj_entry)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    return dj_entry->distance;
}

static inline void
graph_dijkstra_entry_distance_set(s_dijkstra_entry_t *dj_entry, uint32 distance)
{
    assert_exit(graph_dijkstra_entry_legal_ip(dj_entry));

    dj_entry->distance = distance;
}

static inline bool
graph_dijkstra_table_legal_ip(s_dijkstra_table_t *dj_table)
{
    if (dj_table == NULL) {
        return false;
    } else if (dj_table->array == NULL) {
        return false;
    } else if (dj_table->size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_dijkstra_table_illegal_ip(s_dijkstra_table_t *dj_table)
{
    return !graph_dijkstra_table_legal_ip(dj_table);
}

bool
graph_dijkstra_table_legal_p(s_dijkstra_table_t *dj_table)
{
    return graph_dijkstra_table_legal_ip(dj_table);
}

bool
graph_dijkstra_table_illegal_p(s_dijkstra_table_t *dj_table)
{
    return graph_dijkstra_table_illegal_ip(dj_table);
}

static inline s_dijkstra_entry_t *
graph_dijkstra_table_array(s_dijkstra_table_t *dj_table)
{
    assert_exit(graph_dijkstra_table_legal_ip(dj_table));

    return dj_table->array;
}

static inline s_dijkstra_entry_t *
graph_dijkstra_table_entry(s_dijkstra_table_t *dj_table, uint32 i)
{
    s_dijkstra_entry_t *entry_array;

    assert_exit(i < graph_dijkstra_table_size(dj_table));
    assert_exit(graph_dijkstra_table_legal_ip(dj_table));

    entry_array = graph_dijkstra_table_array(dj_table);

    return &entry_array[i];
}

// static inline void
// graph_dijkstra_table_array_set(s_dijkstra_table_t *dj_table,
//     s_dijkstra_entry_t *array)
// {
//     assert_exit(graph_dijkstra_table_legal_ip(dj_table));
// 
//     dj_table->array = array;
// }

static inline uint32
graph_dijkstra_table_size(s_dijkstra_table_t *dj_table)
{
    assert_exit(graph_dijkstra_table_legal_ip(dj_table));

    return dj_table->size;
}

static inline uint32
graph_dijkstra_table_limit(s_dijkstra_table_t *dj_table)
{
    return graph_dijkstra_table_size(dj_table);
}

// static inline void
// graph_dijkstra_table_size_set(s_dijkstra_table_t *dj_table, uint32 size)
// {
//     assert_exit(graph_dijkstra_table_legal_ip(dj_table));
// 
//     dj_table->size = size;
// }

static inline s_dijkstra_entry_t *
graph_vertex_to_dijkstra_entry(s_vertex_t *vertex, s_dijkstra_table_t *dj_table)
{
    uint32 idx;

    assert_exit(graph_vertex_structure_legal_p(vertex));
    assert_exit(graph_dijkstra_table_legal_ip(dj_table));

    idx = (uint32)(ptr_t)graph_vertex_data(vertex);

    assert_exit(idx < graph_dijkstra_table_limit(dj_table));

    return graph_dijkstra_table_entry(dj_table, idx);
}

static inline bool
graph_paths_legal_ip(s_graph_paths_t *paths)
{
    if (NULL_PTR_P(paths)) {
        return false;
    } else if (paths->vertex_from == NULL) {
        return false;
    } else if (paths->vertex_to == NULL) {
        return false;
    } else if (array_queue_structure_illegal_p(paths->queue)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
graph_paths_illegal_ip(s_graph_paths_t *paths)
{
    return !graph_paths_legal_ip(paths);
}

static inline s_graph_paths_t *
graph_paths_create(s_vertex_t *vertex_from, s_vertex_t *vertex_to)
{
    s_graph_paths_t *paths;

    assert_exit(graph_vertex_structure_legal_p(vertex_from));
    assert_exit(graph_vertex_structure_legal_p(vertex_to));

    paths = memory_cache_allocate(sizeof(*paths));

    paths->vertex_from = vertex_from;
    paths->vertex_to = vertex_to;
    paths->queue = array_queue_create();

    return paths;
}

static inline void
graph_paths_destroy(s_graph_paths_t *graph_paths)
{
    s_array_queue_t *queue_paths, *path;

    assert_exit(graph_paths_legal_ip(graph_paths));

    queue_paths = graph_paths_queue(graph_paths);

    while (!array_queue_empty_p(queue_paths)) {
        path = array_queue_leave(queue_paths);
        array_queue_destroy(&path);
    }

    array_queue_destroy(&queue_paths);
    memory_cache_free(graph_paths);
}

static inline s_vertex_t *
graph_paths_vertex_from(s_graph_paths_t *paths)
{
    assert_exit(graph_paths_legal_ip(paths));

    return paths->vertex_from;
}

static inline s_vertex_t *
graph_paths_vertex_to(s_graph_paths_t *paths)
{
    assert_exit(graph_paths_legal_ip(paths));

    return paths->vertex_to;
}

static inline s_array_queue_t *
graph_paths_queue(s_graph_paths_t *paths)
{
    assert_exit(graph_paths_legal_ip(paths));

    return paths->queue;
}

