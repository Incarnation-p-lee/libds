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
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
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
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else {
        binary_heap_node_insert(heap->bin_heap, val, nice, &binary_heap_order_minimal);
    }
}

struct doubly_linked_list *
minimal_heap_node_remove(struct minimal_heap *heap, sint64 nice)
{
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (!binary_heap_node_contains_p(heap->bin_heap, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
        return NULL;
    } else {
        return binary_heap_node_remove(heap->bin_heap, index,
            &binary_heap_order_minimal);
    }
}

void
minimal_heap_node_remove_and_destroy(struct minimal_heap *heap, sint64 nice)
{
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (!binary_heap_node_contains_p(heap->bin_heap, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        binary_heap_node_remove_and_destroy(heap->bin_heap, index,
            &binary_heap_order_minimal);
    }
}

struct doubly_linked_list *
minimal_heap_node_remove_min(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_remove(heap->bin_heap, HEAP_ROOT_INDEX,
            &binary_heap_order_minimal);
    }
}

void
minimal_heap_node_remove_min_and_destroy(struct minimal_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_node_remove_and_destroy(heap->bin_heap, HEAP_ROOT_INDEX,
            &binary_heap_order_minimal);
    }
}

void
minimal_heap_node_decrease_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    uint32 tgt_index;
    sint64 new_nice;
    struct collision_chain *tmp;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else if (0 == offset) {
        pr_log_info("Zero offset of nice, nothing will be done.\n");
    } else if (!binary_heap_node_contains_p(heap->bin_heap, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        /*
         * index of nice has been set already.
         */
        new_nice = nice - offset;
        if (!binary_heap_node_contains_p(heap->bin_heap, new_nice, &tgt_index)) {
            tmp = HEAP_CHAIN(heap->bin_heap, index);
            HEAP_CHAIN(heap->bin_heap, index) = NULL;
            tmp->nice = new_nice;

            index = binary_heap_percolate_up(heap->bin_heap, index,
                tmp->nice, &binary_heap_order_minimal);
            assert(NULL == HEAP_CHAIN(heap->bin_heap, index));

            HEAP_CHAIN(heap->bin_heap, index) = tmp;
        } else {
            /*
             * decreased nice already contained.
             * merge conflict and remove node.
             */
            binary_heap_node_collision_merge(heap->bin_heap, tgt_index, index);
            binary_heap_node_remove_and_destroy(heap->bin_heap, index,
                &binary_heap_order_minimal);
        }
    }
}

void
minimal_heap_node_increase_nice(struct minimal_heap *heap, sint64 nice, uint32 offset)
{
    uint32 index;
    sint64 new_nice;
    uint32 tgt_index;
    struct collision_chain *tmp;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else if (0 == offset) {
        pr_log_info("Zero offset of nice, nothing will be done.\n");
    } else if (!binary_heap_node_contains_p(heap->bin_heap, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        /*
         * index of nice has been set already.
         */
        new_nice = nice + offset;
        if (!binary_heap_node_contains_p(heap->bin_heap, new_nice, &tgt_index)) {
            tmp = HEAP_CHAIN(heap->bin_heap, index);
            HEAP_CHAIN(heap->bin_heap, index) = NULL;
            tmp->nice = new_nice;

            index = binary_heap_percolate_down(heap->bin_heap, index, new_nice,
                &binary_heap_order_minimal);
            assert(NULL == HEAP_CHAIN(heap->bin_heap, index));

            HEAP_CHAIN(heap->bin_heap, index) = tmp;
        } else {
            /*
             * decreased nice already contained.
             * merge conflict and remove node.
             */
            binary_heap_node_collision_merge(heap->bin_heap, tgt_index, index);
            binary_heap_node_remove_and_destroy(heap->bin_heap, index,
                &binary_heap_order_minimal);
        }
    }
}

