static uint32
test_iterate_reference(void)
{
    return reference;
}

static void
linked_list_iterate_handler(void *ptr)
{
    reference++;
}

static void
stack_iterate_handler(void *ptr)
{
    if (ptr) {
        *(sint32 *)ptr += 1;
    }
}

static void
queue_iterate_handler(void *ptr)
{
    if (ptr) {
        *(uint32 *)ptr += 1;
    }
}

static void
tree_iterate_handler(void *ptr)
{
    reference++;
}

static void
test_iterate_reference_clean(void)
{
    reference = 0;
}

