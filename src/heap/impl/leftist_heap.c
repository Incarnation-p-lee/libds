static inline struct leftist_heap *
leftist_heap_create_internal(void *val, sint32 npl)
{
    struct leftist_heap *heap;

    assert(NPL_NULL != npl);

    heap = malloc_ds(sizeof(*heap));

    if (!complain_no_memory_p(heap)) {
        heap->alias.chain.link = malloc_ds(sizeof(*heap->alias.chain.link));

        if (!complain_no_memory_p(heap->alias.chain.link)) {
            heap->alias.left = NULL;
            heap->alias.right = NULL;
            heap->npl = npl;

            doubly_linked_list_initial(heap->alias.chain.link);
            doubly_linked_list_node_val_set(heap->alias.chain.link, val);
        }
    }

    return heap;
}

struct leftist_heap *
leftist_heap_create(void)
{
    return leftist_heap_create_internal(NULL, 0);
}

struct leftist_heap *
leftist_heap_node_create(void *val, sint32 nlp)
{
    return leftist_heap_create_internal(val, nlp);
}

static inline void
leftist_heap_node_destroy(struct leftist_heap *node)
{
    assert(NULL != node);
    assert(NULL == leftist_heap_left(node));
    assert(NULL == leftist_heap_right(node));

    doubly_linked_list_destroy(&node->alias.chain.link);
    free_ds(node);
}

static inline void
leftist_heap_destroy_internal(struct leftist_heap *heap)
{
    if (heap) {
        leftist_heap_destroy_internal(leftist_heap_left(heap));
        leftist_heap_destroy_internal(leftist_heap_left(heap));

        heap->alias.left = NULL;
        heap->alias.right = NULL;
        leftist_heap_node_destroy(heap);
    }
}

void
leftist_heap_destroy(struct leftist_heap **heap)
{
    if (!complain_null_pointer_p(heap) && !complain_null_pointer_p(*heap)) {
        leftist_heap_destroy_internal(*heap);
        *heap = NULL;
    }
}

struct leftist_heap *
leftist_heap_ptr_container_of(struct binary_search_tree *node)
{
    if (complain_null_pointer_p(node)) {
        return NULL;
    } else {
        return CONTAINER_OF(node, struct leftist_heap, alias);
    }
}


