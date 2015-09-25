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


