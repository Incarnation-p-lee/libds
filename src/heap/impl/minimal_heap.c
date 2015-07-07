struct minimal_heap *
minimal_heap_create(uint32 capacity)
{
    struct minimal_heap *heap;

    heap = malloc_ds(sizeof(*heap));
    if (!heap) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        heap->bin_heap = binary_heap_create(capacity);
    }

    return heap;
}

void
minimal_heap_destroy(struct minimal_heap **heap)
{
    if (!*heap || !heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_destroy(&(*heap)->bin_heap);
        free_ds(*heap);
        *heap = NULL;
    }
}

bool
minimal_heap_empty_p(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_heap_empty_p(heap->bin_heap);
    }
}

bool
minimal_heap_full_p(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return binary_heap_full_p(heap->bin_heap);
    }
}

void
minimal_heap_cleanup(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_cleanup(heap->bin_heap);
    }
}

struct doubly_linked_list *
minimal_heap_node_find(struct minimal_heap *heap, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_find(heap->bin_heap, nice);
    }
}

struct doubly_linked_list *
minimal_heap_node_find_min(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_root(heap->bin_heap);
    }
}

void
minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice)
{
    struct doubly_linked_list *head;
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        head = minimal_heap_node_find(heap, nice);
        if (!head) {
            index = binary_heap_percolate_up(heap->bin_heap,
                minimal_heap_size(heap) + 1, nice);
            binary_heap_node_create_by_index(heap->bin_heap, index, nice, val);
        } else {
            doubly_linked_list_node_insert_after(head,
                doubly_linked_list_node_create(val, nice));
        }
    }
}

struct doubly_linked_list *
minimal_heap_node_remove_min(struct minimal_heap *heap)
{
    struct doubly_linked_list *retval;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        retval = binary_heap_node_destroy_by_index(heap->bin_heap, HEAP_ROOT_INDEX);
        binary_heap_percolate_down(heap->bin_heap, HEAP_ROOT_INDEX);
        return retval;
    }
}

void
minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    struct collision_chain *tmp;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        index = binary_heap_index_get_by_nice(heap->bin_heap, nice);
        if (0 == index) {
            pr_log_warn("No such the node of heap, nothing will be done.\n");
        } else {
            tmp = HEAP_CHAIN(heap->bin_heap, index);
            tmp->nice = nice - offset;
            HEAP_CHAIN(heap->bin_heap, index) = NULL;

            index = binary_heap_percolate_up(heap->bin_heap, index, tmp->nice);
            HEAP_CHAIN(heap->bin_heap, index) = tmp;
        }
    }
}
