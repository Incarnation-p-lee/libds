struct stacked_queue *
stacked_queue_create(void)
{
    struct stacked_queue *queue;
    uint32 capacity;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0u;
    }

    queue->spece_et = array_stack_create();
    queue->spece_lv = array_stack_create();

    capacity = array_stack_capacity(queue->space_et);
    assert(capacity == array_stack_capacity(queue->space_lv));
    queue->dim = capacity;

    return queue;
}

void
stacked_queue_destroy(struct stacked_queue **queue)
{
    if (queue && *queue) {
        array_stack_destroy(&queue->spece_et);
        array_stack_destroy(&queue->spece_lv);
        free_ds(*queue);
        *queue = NULL;
    }
    return;
}

void
stacked_queue_expand_space(struct stacked_queue *queue, uint32 extra)
{
    uint32 capacity;

    if (queue && extra > 0) {
        array_stack_expand_space(queue->space_et, extra);
        array_stack_expand_space(queue->space_lv, extra);

        capacity = array_stack_capacity(queue->space_et);
        assert(capacity == array_stack_capacity(queue->space_lv));
        queue->dim = capacity;
    }
    return;
}
