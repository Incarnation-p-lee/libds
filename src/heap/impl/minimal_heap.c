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

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        head = minimal_heap_node_find(heap, nice);
        if (!head) {
            binary_heap_percolate_up(heap->bin_heap, val, nice);
        } else {
            doubly_linked_list_node_insert_after(head,
                doubly_linked_list_node_create(val, nice));
        }
    }
}
