static inline s_single_linked_list_t *
test_single_linked_list_sample(uint32 node_count)
{
    uint32 i;
    s_single_linked_list_t *list;
    s_single_linked_list_t *node;

    assert_exit(node_count != 0);

    list = single_linked_list_create();
    i = 1;

    while (i < node_count) {
        node = single_linked_list_create();
        single_linked_list_insert_after(list, node);
        i++;
    }

    return list;
}

static inline s_doubly_linked_list_t *
test_doubly_linked_list_sample(uint32 node_count)
{
    uint32 i;
    s_doubly_linked_list_t *list;
    s_doubly_linked_list_t *node;

    assert_exit(node_count != 0);

    i = 1;
    list = doubly_linked_list_create();

    while (i < node_count) {
        node = doubly_linked_list_create();
        doubly_linked_list_insert_after(list, node);
        i++;
    }

    return list;
}

static inline s_skip_linked_list_t *
test_skip_linked_list_sample(uint32 node_count)
{
    uint32 i;
    sint32 key;
    s_skip_linked_list_t *list;
    s_skip_linked_list_t *tmp;

    assert_exit(node_count != 0);

    list = skip_linked_list_create();
    skip_linked_list_initial(list);

    i = 1;
    while (i < node_count) {
        key = (sint32)random_uint32_with_limit(node_count) - (sint32)node_count / 2;
        tmp = skip_linked_list_create_with_key(key);
        skip_linked_list_insert(&list, tmp);
        i++;
    }

    return list;
}

static inline s_doubly_end_queue_t *
test_doubly_end_queue_sample(uint32 count)
{
    s_doubly_end_queue_t *queue;

    assert_exit(0 != count);

    queue = doubly_end_queue_create();

    while (count--) {
        doubly_end_queue_front_enter(queue, queue);
    }

    return queue;
}

static inline s_binary_search_tree_t *
test_binary_search_tree_sample(uint64 range, uint32 count)
{
    uint32 i;
    sint64 nice;
    s_binary_search_tree_t *tmp;
    s_binary_search_tree_t *tree;

    i = 1;
    tree = binary_search_tree_create(&nice, 0);

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_create((void *)(ptr_t)i, nice);

        if (binary_search_tree_find(tree, nice) == NULL) {
            binary_search_tree_insert(tree, tmp);
        } else {
            binary_search_tree_insert(tree, tmp);
            binary_search_tree_destroy(&tmp);
        }

        i++;
    }

    return tree;
}

static inline struct avl_tree *
test_avl_tree_sample(uint64 range, uint32 count)
{
    uint32 i;
    sint64 nice;
    s_avl_tree_t *tmp;
    s_avl_tree_t *tree;

    i = 1;
    tree = avl_tree_create(&nice, 0);

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = avl_tree_create((void *)(ptr_t)i, nice);

        if (avl_tree_find(tree, nice) == NULL) {
            avl_tree_insert(&tree, tmp);
        } else {
            avl_tree_insert(&tree, tmp);
            avl_tree_destroy(&tmp);
        }

        i++;
    }

    return tree;
}

static inline struct splay_tree *
test_splay_tree_sample(uint64 range, uint32 node_count)
{
    struct splay_tree *tree;
    struct splay_tree *tmp;
    sint64 nice;
    uint32 i;

    tree = splay_tree_create(&nice, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = splay_tree_create(&nice, nice);

        if (tmp != splay_tree_insert(&tree, tmp)) {
            splay_tree_destroy(&tmp);
        }

        i++;
    }

    return tree;
}

static inline struct open_addressing_hash *
test_open_addressing_hash_sample(uint32 count)
{
    struct open_addressing_hash *hash;
    struct memory_maps *heap;
    uint64 iter;
    uint64 limit;

    hash = open_addressing_hash_create(0x11u);
    heap = memory_maps_entry_find("[heap]");

    assert_exit(!NULL_PTR_P(hash));
    assert_exit(!NULL_PTR_P(heap));

    iter = PTR_TO_UNSIGNED(heap->begin);
    limit = PTR_TO_UNSIGNED(heap->end);

    while (0 != count-- && iter < limit) {
        open_addressing_hash_insert(hash, UNSIGNED_TO_PTR(iter));
        iter += 4;
    }

    return hash;
}

static inline struct separate_chain_hash *
test_separate_chain_hash_sample(uint32 count)
{
    struct separate_chain_hash *hash;
    struct memory_maps *heap;
    uint64 iter;
    uint64 limit;

    hash = separate_chain_hash_create(0x11u);
    heap = memory_maps_entry_find("[heap]");

    assert_exit(NULL != hash);
    assert_exit(NULL != heap);

    iter = PTR_TO_UNSIGNED(heap->begin);
    limit = PTR_TO_UNSIGNED(heap->end);

    while (0 != count-- && iter < limit) {
        separate_chain_hash_insert(hash, UNSIGNED_TO_PTR(iter));
        iter += 4;
    }

    return hash;
}

static inline struct minimal_heap *
test_minimal_heap_sample(uint64 range, uint32 size)
{
    struct minimal_heap *heap;
    sint64 nice;
    uint32 i;

    assert_exit(0 != size);

    heap = minimal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((dp_rand() % range) - (range / 2));
        minimal_heap_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline struct maximal_heap *
test_maximal_heap_sample(uint64 range, uint32 size)
{
    struct maximal_heap *heap;
    sint64 nice;
    uint32 i;

    assert_exit(0 != size);

    heap = maximal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((dp_rand() % range) - (range / 2));
        maximal_heap_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline struct min_max_heap *
test_min_max_heap_sample(uint64 range, uint32 size)
{
    struct min_max_heap *heap;
    sint64 nice;
    uint32 i;

    assert_exit(0 != size);

    heap = min_max_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((dp_rand() % range) - (range / 2));
        min_max_heap_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline struct leftist_heap *
test_leftist_heap_sample(uint64 range, uint32 size)
{
    struct leftist_heap *heap;
    sint64 nice;
    uint32 i;

    assert_exit(0 != size);

    heap = leftist_heap_create();
    i = 0;
    while (i < size) {
        nice = (sint64)((dp_rand() % range) - (range / 2));
        heap = leftist_heap_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}

static inline s_graph_t *
test_indirected_graph_sample(uint64 range, uint32 size)
{
    uint32 i;
    void *vertex_a;
    void *vertex_b;
    s_graph_t *graph;

    assert_exit(size);

    i = 0;
    graph = indirected_graph_create();

    while (i < size) {
        vertex_a = (void *)(ptr_t)random_uint32_with_limit(range);
        vertex_b = (void *)(ptr_t)random_uint32_with_limit(range);

        indirected_graph_link(graph, vertex_a, vertex_b, i++);
    }

    return graph;
}

