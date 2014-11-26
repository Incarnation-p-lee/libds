static void
test_array_queue_create(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    if (0u != queue->sid) {
        is_passed = false;
    }

    if (queue->space.rest != queue->space.dim) {
        is_passed = false;
    }

    if (queue->space.base != queue->space.front
        || queue->space.base != queue->space.rear) {
        is_passed = false;
    }

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}

/*
static void
test_array_queue_create(void)
{
    bool is_passed;
    struct array_queue *queue;

    queue = array_queue_create();
    is_passed = true;

    array_queue_destroy(&queue);

    test_result_print(SYM_2_STR(array_queue_create), is_passed);
    return;
}
*/
