static inline struct single_linked_list *
test_single_linked_list_sample(uint32 range, uint32 node_count)
{
    struct single_linked_list *list;
    struct single_linked_list *tmp;
    uint32 sid;
    uint32 i;

    list = single_linked_list_create();
    single_linked_list_node_initial(list, list, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = single_linked_list_create();
        single_linked_list_node_initial(tmp, tmp, sid);
        single_linked_list_node_insert_after(list, tmp);
        i++;
    }

    return list;
}

static inline struct doubly_linked_list *
test_doubly_linked_list_sample(uint32 range, uint32 node_count)
{
    struct doubly_linked_list *list;
    struct doubly_linked_list *tmp;
    uint32 sid;
    uint32 i;

    list = doubly_linked_list_create();
    doubly_linked_list_node_initial(list, list, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_initial(tmp, tmp, sid);
        doubly_linked_list_node_insert_before(list, tmp);
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
    skip_linked_list_node_initial(list, list, 0);

    i = 1;
    while (i < count) {
        key = (sint32)(rand() % range) - (sint32)range / 2;
        if (!skip_linked_list_node_find_key(list, key)) {
            tmp = skip_linked_list_node_create(NULL, key);
            skip_linked_list_node_val_set(tmp, tmp);
            skip_linked_list_node_insert(&list, tmp);
        }
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
    binary_search_tree_node_initial(tree, &reference, 0);
    i = 1;

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_node_create(NULL, 0x0);
        binary_search_tree_node_initial(tmp, &reference, nice);
        if (tmp != binary_search_tree_node_insert(tree, tmp)) {
            binary_search_tree_destroy(&tmp);
        }
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
    avl_tree_node_initial(tree, &reference, 0);
    i = 1;

    while (i < count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = avl_tree_node_create(NULL, 0x0);
        avl_tree_node_initial(tmp, &reference, nice);
        if (tmp != avl_tree_node_insert(&tree, tmp)) {
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

    hash = open_addressing_hash_create(0x11u);
    heap = memory_maps_entry_find("[heap]");

    assert(NULL != hash);
    assert(NULL != heap);

    iter = (uint64)heap->begin;
    limit = (uint64)heap->end;
    while (0 != count-- && iter < limit) {
        open_addressing_hash_insert(&hash, (void *)iter);
        iter += 4;
    }

    return hash;
}

