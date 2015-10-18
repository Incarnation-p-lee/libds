struct min_max_heap *
min_max_heap_create(uint32 capacity)
{
    struct min_max_heap *heap;

    heap = malloc_ds(sizeof(*heap));
    if (!heap) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        heap->alias = binary_heap_create(capacity);
    }

    return heap;
}

void
min_max_heap_destroy(struct min_max_heap **heap)
{
    if (!*heap || !heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_destroy(&(*heap)->alias);
        free_ds(*heap);
        *heap = NULL;
    }
}

bool
min_max_heap_empty_p(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return false;
    } else {
        return binary_heap_empty_p(heap->alias);
    }
}

bool
min_max_heap_full_p(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return binary_heap_full_p(heap->alias);
    }
}

void
min_max_heap_cleanup(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        binary_heap_cleanup(heap->alias);
    }
}

struct doubly_linked_list *
min_max_heap_node_find(struct min_max_heap *heap, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
        return NULL;
    } else {
        return binary_heap_node_find(heap->alias, nice);
    }
}

/*
 * minimal node is root node
 * foreach node in heap, if
 *     even, > grandfater > ... > depth 2 node > root
 *     odd,  > father > grandfater > ... > depth 2 node > root
 */
struct doubly_linked_list *
min_max_heap_node_find_min(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        return binary_heap_node_root(heap->alias);
    }
}

/*
 * minimal node is either left or right child of root
 * foreach node in heap, if
 *     even, < fater < grandfater < ... < depth 1 node > root
 *     odd,  < grandfather < ... < depth 1 node > root
 */
struct doubly_linked_list *
min_max_heap_node_find_max(struct min_max_heap *heap)
{
    uint32 idx;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else {
        idx = binary_heap_child_big_nice_index(heap->alias, HEAP_ROOT_INDEX);
        return HEAP_LINK(heap->alias, idx);
    }
}

void
min_max_heap_node_insert(struct min_max_heap *heap, void *val, sint64 nice)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (HEAP_NICE_LOWER_LMT == nice || HEAP_NICE_UPPER_LMT == nice) {
        pr_log_warn("Nice specificed reach the limit.\n");
    } else {
        binary_heap_node_insert(heap->alias, val, nice,
            &binary_heap_min_max_percolate_up_ordered_p);
    }
}

uint32
min_max_heap_node_depth(struct min_max_heap *heap, uint32 index)
{
    if (INDEX_INVALID == index || index > INDEX_LAST(heap->alias)) {
        pr_log_warn("Illegal index value of heap.\n");
        return DEPTH_INVALID;
    } else if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    }

    return binary_heap_node_depth(index);
}
