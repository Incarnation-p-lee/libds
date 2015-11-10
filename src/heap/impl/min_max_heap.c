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
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (INDEX_ROOT == INDEX_LAST(heap->alias)) {
        return HEAP_LINK(heap->alias, INDEX_ROOT);
    } else {
        index = binary_heap_child_big_nice_index(heap->alias, INDEX_ROOT);

        assert(INDEX_INVALID != index);
        return HEAP_LINK(heap->alias, index);
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
            &binary_heap_min_max_ordered_p);
    }
}

uint32
min_max_heap_node_depth(struct min_max_heap *heap, uint32 index)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (INDEX_INVALID == index || index > INDEX_LAST(heap->alias)) {
        pr_log_warn("Illegal index value of heap.\n");
        return DEPTH_INVALID;
    }

    return binary_heap_node_depth(index);
}

struct doubly_linked_list *
min_max_heap_node_remove_min(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        return binary_heap_node_remove_root(heap->alias,
            &binary_heap_min_max_ordered_p);
    }
}

void
min_max_heap_node_remove_min_and_destroy(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
    } else {
        binary_heap_node_remove_root_and_destroy(heap->alias,
            &binary_heap_min_max_ordered_p);
    }
}

static inline struct doubly_linked_list *
min_max_heap_node_remove_internal(struct min_max_heap *heap, uint32 index)
{
    sint64 nice;
    struct binary_heap *alias;
    struct collision_chain *tmp;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));
    assert(!binary_heap_empty_p(heap->alias));

    alias = heap->alias;

    tmp = HEAP_CHAIN(alias, index);
    HEAP_CHAIN(alias, index) = NULL;

    nice = HEAP_NICE(alias, INDEX_ROOT) - 1;
    assert(nice != HEAP_NICE_LOWER_LMT);

    /*
     * percolate current index node to root, then remove the root.
     */
    binary_heap_node_reorder(alias, index, nice, &binary_heap_min_max_ordered_p);
    assert(NULL == HEAP_CHAIN(alias, INDEX_ROOT));
    HEAP_CHAIN(alias, INDEX_ROOT) = tmp;

    return binary_heap_node_remove_root(alias, &binary_heap_min_max_ordered_p);
}

struct doubly_linked_list *
min_max_heap_node_remove(struct min_max_heap *heap, sint64 nice)
{
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
        return NULL;
    } else {
        return min_max_heap_node_remove_internal(heap, index);
    }
}

static inline void
min_max_heap_node_remove_and_destroy_internal(struct min_max_heap *heap,
    uint32 index)
{
    struct doubly_linked_list *removed;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));
    assert(binary_heap_index_legal_p(heap->alias, index));

    removed = min_max_heap_node_remove_internal(heap, index);
    doubly_linked_list_destroy(&removed);
}

void
min_max_heap_node_remove_and_destroy(struct min_max_heap *heap, sint64 nice)
{
    uint32 index;

    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else if (!binary_heap_node_contains_p(heap->alias, nice, &index)) {
        pr_log_warn("No such the node of heap, nothing will be done.\n");
    } else {
        min_max_heap_node_remove_and_destroy_internal(heap, index);
    }
}

static inline struct doubly_linked_list *
min_max_heap_node_remove_max_internal(struct min_max_heap *heap)
{
    uint32 max_index;
    struct binary_heap *alias;

    assert(NULL != heap);
    assert(binary_heap_structure_legal_p(heap->alias));

    alias = heap->alias;
    max_index = binary_heap_child_big_nice_index(alias, INDEX_ROOT);

    if (INDEX_INVALID == max_index) {
        return binary_heap_node_remove_root(alias,
            &binary_heap_min_max_ordered_p);
    } else {
        return min_max_heap_node_remove_internal(heap, max_index);
    }
}

struct doubly_linked_list *
min_max_heap_node_remove_max(struct min_max_heap *heap)
{
    if (!heap) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return NULL;
    } else if (binary_heap_empty_p(heap->alias)) {
        pr_log_warn("Attempt to remove node in empty heap.\n");
        return NULL;
    } else {
        return min_max_heap_node_remove_max_internal(heap);
    }
}

