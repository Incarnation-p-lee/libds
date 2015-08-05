struct maximal_heap *
maximal_heap_create(uint32 capacity)
{
    struct maximal_heap *heap;

    heap = malloc_ds(sizeof(*heap));
    if (!heap) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        heap->bin_heap = binary_heap_create(capacity);
    }

    return heap;
}

void
maximal_heap_destroy(struct maximal_heap **heap)
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
maximal_heap_empty_p(struct maximal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_heap_empty_p(heap->bin_heap);
    }
}

bool
maximal_heap_full_p(struct maximal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return binary_heap_full_p(heap->bin_heap);
    }
}

void
maximal_heap_cleanup(struct maximal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_cleanup(heap->bin_heap);
    }
}

struct doubly_linked_list *
maximal_heap_node_find(struct maximal_heap *heap, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
        return NULL;
    } else {
        return binary_heap_node_find(heap->bin_heap, nice);
    }
}

struct doubly_linked_list *
maximal_heap_node_find_max(struct maximal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_root(heap->bin_heap);
    }
}

void
maximal_heap_node_insert(struct maximal_heap *heap, void *val, sint64 nice)
{
    struct doubly_linked_list *head;
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else {
        head = maximal_heap_node_find(heap, nice);

        if (!head) {
            index = binary_heap_percolate_up(heap->bin_heap,
                heap->bin_heap->size + 1, nice, &binary_heap_order_maximal);
            binary_heap_node_create_by_index(heap->bin_heap, index, nice, val);
            heap->bin_heap->size++;
        } else {
            /*
             * conflict nice.
             */
            doubly_linked_list_node_insert_after(head,
                doubly_linked_list_node_create(val, nice));
        }
    }
}

