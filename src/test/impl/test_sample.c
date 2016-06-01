static inline struct single_linked_list *
test_single_linked_list_sample(uint32 range, uint32 node_count)
{
    struct single_linked_list *list;
    uint32 i;

    list = single_linked_list_create();

    i = 1;
    while (i < node_count) {
        single_linked_list_insert_after(list, list);
        i++;
    }

    return list;
}

static inline struct doubly_linked_list *
test_doubly_linked_list_sample(uint32 range, uint32 node_count)
{
    uint32 i;
    struct doubly_linked_list *list;

    list = doubly_linked_list_create();

    i = 1;
    while (i < node_count) {
        doubly_linked_list_insert_after(list, list);
        i++;
    }

    return list;
}

static inline struct skip_linked_list *
test_skip_linked_list_sample(uint32 range, uint32 count)
{
    struct skip_linked_list *list;
    struct skip_linked_list *tmp;
    sint32 key;
    uint32 i;

    assert(0 != range);
    assert(0 != count);

    list = skip_linked_list_create();
    skip_linked_list_initial(list);

    i = 1;
    while (i < count) {
        key = (sint32)(rand() % range) - (sint32)range / 2;
        tmp = skip_linked_list_node_create(NULL, key);

        skip_linked_list_val_set(tmp, tmp);
        skip_linked_list_insert(&list, tmp);
        i++;
    }

    return list;
}

static inline struct doubly_end_queue *
test_doubly_end_queue_sample(uint32 count)
{
    struct doubly_end_queue *queue;

    assert(0 != count);

    queue = doubly_end_queue_create();

    while (count--) {
        doubly_end_queue_head_enter(queue, queue);
    }

    return queue;
}

static inline struct binary_search_tree *
test_binary_search_tree_sample(uint64 range, uint32 count)
{
    struct binary_search_tree *tree;
    struct binary_search_tree *tmp;
    sint64 nice;
    uint32 i;

    tree = binary_search_tree_create();
    binary_search_tree_initial(tree, 0);
    i = 1;

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_create();
        binary_search_tree_initial(tmp, nice);
        binary_search_tree_insert(&tree, tmp);
        i++;
    }

    return tree;
}

static inline struct avl_tree *
test_avl_tree_sample(uint64 range, uint32 count)
{
    struct avl_tree *tree;
    struct avl_tree *tmp;
    sint64 nice;
    uint32 i;

    tree = avl_tree_create();
    avl_tree_initial(tree, 0);
    i = 1;

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = avl_tree_create();
        avl_tree_initial(tmp, nice);
        avl_tree_insert(&tree, tmp);
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

    tree = splay_tree_create();
    splay_tree_node_initial(tree, &reference, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = splay_tree_node_create(NULL, 0x0);
        splay_tree_node_initial(tmp, &reference, nice);
        if (tmp != splay_tree_node_insert(&tree, tmp)) {
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

    hash = open_addressing_hash_create(0);
    heap = memory_maps_entry_find("[heap]");

    assert(NULL != hash);
    assert(NULL != heap);

    iter = PTR_TO_UNSIGNED(heap->begin);
    limit = PTR_TO_UNSIGNED(heap->end);

    while (0 != count-- && iter < limit) {
        open_addressing_hash_insert(&hash, UNSIGNED_TO_PTR(iter));
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

    assert(NULL != hash);
    assert(NULL != heap);

    iter = PTR_TO_UNSIGNED(heap->begin);
    limit = PTR_TO_UNSIGNED(heap->end);
    while (0 != count-- && iter < limit) {
        separate_chain_hash_insert(&hash, UNSIGNED_TO_PTR(iter));
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

    assert(0 != size);

    heap = minimal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
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

    assert(0 != size);

    heap = maximal_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
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

    assert(0 != size);

    heap = min_max_heap_create(size);
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
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

    assert(0 != size);

    heap = leftist_heap_create();
    i = 0;
    while (i < size) {
        nice = (sint64)((rand() % range) - (range / 2));
        heap = leftist_heap_insert(heap, &heap, nice);
        i++;
    }

    return heap;
}


