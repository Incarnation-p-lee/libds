static inline struct single_linked_list *
test_single_linked_list_sample(uint32 range, uint32 node_count)
{
    struct single_linked_list *retval;
    struct single_linked_list *tmp;
    uint32 sid;
    uint32 i;

    retval = single_linked_list_create();
    single_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = single_linked_list_create();
        single_linked_list_node_initial(tmp, tmp, sid);
        single_linked_list_node_insert_after(retval, tmp);
        i++;
    }

    return retval;
}

static inline struct doubly_linked_list *
test_doubly_linked_list_sample(uint32 range, uint32 node_count)
{
    struct doubly_linked_list *retval;
    struct doubly_linked_list *tmp;
    uint32 sid;
    uint32 i;

    retval = doubly_linked_list_create();
    doubly_linked_list_node_initial(retval, retval, range);

    i = 1;
    while (i < node_count) {
        sid = (uint32)(rand() % range);
        tmp = doubly_linked_list_create();
        doubly_linked_list_node_initial(tmp, tmp, sid);
        doubly_linked_list_node_insert_before(retval, tmp);
        i++;
    }

    return retval;
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
